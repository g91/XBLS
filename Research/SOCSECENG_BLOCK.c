// SOCSECENG_BLOCK structure

typedef union _SECENG_FAULT_ISOLATION {
	QWORD AsULONGLONG; // 0x0 sz:0x8
	struct{
		QWORD IntegrityViolation : 1; // 0x0 bfo:0x63
		QWORD Reserved1 : 63; // 0x0 bfo:0x0
	}AsBits;
} SECENG_FAULT_ISOLATION, *PSECENG_FAULT_ISOLATION; // size 8
//C_ASSERT(sizeof(SECENG_FAULT_ISOLATION) == 0x8);

typedef struct _SECENG_KEYS { 
	QWORD WhiteningKey0High; // 0x0 sz:0x8
	QWORD WhiteningKey0Low; // 0x8 sz:0x8
	QWORD WhiteningKey1High; // 0x10 sz:0x8
	QWORD WhiteningKey1Low; // 0x18 sz:0x8
	QWORD WhiteningKey2High; // 0x20 sz:0x8
	QWORD WhiteningKey2Low; // 0x28 sz:0x8
	QWORD WhiteningKey3High; // 0x30 sz:0x8
	QWORD WhiteningKey3Low; // 0x38 sz:0x8
	QWORD AESKey0High; // 0x40 sz:0x8
	QWORD AESKey0Low; // 0x48 sz:0x8
	QWORD AESKey1High; // 0x50 sz:0x8
	QWORD AESKey1Low; // 0x58 sz:0x8
	QWORD AESKey2High; // 0x60 sz:0x8
	QWORD AESKey2Low; // 0x68 sz:0x8
	QWORD AESKey3High; // 0x70 sz:0x8
	QWORD AESKey3Low; // 0x78 sz:0x8
	QWORD HashKey0High; // 0x80 sz:0x8
	QWORD HashKey0Low; // 0x88 sz:0x8
	QWORD HashKey1High; // 0x90 sz:0x8
	QWORD HashKey1Low; // 0x98 sz:0x8
} SECENG_KEYS, *PSECENG_KEYS; // size 160
//C_ASSERT(sizeof(SECENG_KEYS) == 0xA0);

typedef struct _SOCSECENG_BLOCK { //Addr = 80000200_00024000
	SECENG_KEYS WritePathKeys; // 0x0 sz:0xA0
	QWORD TraceLogicArrayWritePathControl; // 0xA0 sz:0x8
	QWORD qwUnkn1;
	QWORD Reserved1[0x1EA]; // 0xA8 sz:0xF58
	SECENG_KEYS ReadPathKeys; // 0x1000 sz:0xA0
	QWORD TraceLogicArrayReadPathControl; // 0x10A0 sz:0x8
	SECENG_FAULT_ISOLATION FaultIsolationMask; // 0x10A8 sz:0x8
	SECENG_FAULT_ISOLATION FaultIsolation; // 0x10B0 sz:0x8 - set to zero in CB
	QWORD IntegrityViolationSignature; // 0x10B8 sz:0x8
	QWORD qwUnkn2;
	QWORD Reserved2[0x1E7]; // 0x10C0 sz:0xF40
} SOCSECENG_BLOCK, *PSOCSECENG_BLOCK; // size 8192
//C_ASSERT(sizeof(SOCSECENG_BLOCK) == 0x2000);

// the security engine contains multiple keys, this is important
// 0x00000X**_00000000 X = region, ** = key select
// x = 0 should be physical
// x = 1 should be hashed
// x = 2 should be SoC
// x = 3 should be encrypted

// notes on where this is referenced and what is inside

// sub_4D10 in CB, i think this function sets up more than just the security engine soc
SOCSECENG_BLOCK->FaultIsolationMask // sets the IntegrityViolation bit to one in CB
SOCSECENG_BLOCK->FaultIsolation // set to zero in CB

// sub_5348 in CB sets up initial values
// in sub_5348 you can see many relationships to the hypervisor functions that deal with security
// deals with that XeCryptHammingWeight thing i dont understand yet
// here is a little reversing:
void InitializeSecurityEngine() {
	post_output(0x22/*INITIALIZE_SECURITY_ENGINE*/);
	
	PSOCSECENG_BLOCK pSecEng = (PSOCSECENG_BLOCK)0x8000020000024000; // r25
	void *r27 = 0x8000020000060000; // r27 another hardware thing that i dont yet know
	// 0x8000020000060000 seems to be the random number generater
	
	// does some shit with generating some random values, loops and does math
	// im certain var_A0 and var_140 are random values, uses the time base register to generate and some random values
	
	// transform the random values to not be easily predictable
	XeCryptSha(var_140, 0xA0, var_A0, 0x60, 0, 0, var_160, 0x14);
	XeCryptRc4(var_160, var_140, 0xA0);
	
	PQWORD pqwRandomData = (PQWORD)var_140;
	PSECENG_KEYS pWritePathKeys = &pSecEng.WritePathKeys; // r29
	PSECENG_KEYS pReadPathKeys = &pSecEng.ReadPathKeys; // r30
	
	PQWORD pqwWriteKeys = (PQWORD)pWritePathKeys;
	PQWORD pqwReadKeys = (PQWORD)pReadPathKeys;
	
	// set the whitening keys
	for(DWORD X /* r11 */ = 8; X > 0; X--) {
		// set random keys
		QWORD qwRandom = *pqwRandomData;
		*pqwWriteKeys = qwRandom;
		*pqwReadKeys = qwRandom;
		
		// increment values
		pqwWriteKeys++;
		pqwReadKeys++;
		pqwRandomData++;
	}
	
	// set the aes keys, this is WRONG there is something with r27
	for(DWORD X /* r28 */ = 4; X > 0; X--) {
		// set the read path keys, they are decryption keys so no need to schedule with the shits
		pqwReadKeys[0] = pqwRandomData[0];
		pqwReadKeys[1] = pqwRandomData[1];
		
		// generate sbox
		_create_aes_sbox_128bit((PBYTE)qwRandom, r26 + 0x140); // r4 isnt that important its just the rijandael initial schedule array shit
		
		// set write key
		pqwWriteKeys[0] = pqwRandomData[0];
		pqwWriteKeys[1] = pqwRandomData[1];
		
		// increment values
		// 2 qwords equal to 0x10
		qwRandom += 2;
		pqwWriteKeys += 2;
		pqwReadKeys += 2;
	}
	
	// set the hash keys
	// dont need to write this you know whats up

	// does some weird time wait, maybe to try and prevent glitching?
	// the time wait is dependant on the random values
}


// sub_20B0 in HV deals with it again (changes keys for different security hashes)
// see research.h file for full reversal of sub_20B0
// only references the WritePathKeys and ReadPathKeys, only sets WhiteningKey0, AESKey0, and HashKey0

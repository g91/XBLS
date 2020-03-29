.include "macros1.s"
.set PPE_TLB_VPN, 949
.set HRMOR, 313
.set SRR1, 27
.set SRR0, 26
.set CTR, 9
.set LR, 8

.globl _start
_start:

MakePatch 0x22D8
0:
	.long 0x4800B527 # bla X
9:

MakePatch 0xB524
0:
	lis %r30, 0 # Zero patches register
	ori %r30, %r30, 0xB600 # Patches address
patchLoop:
	ld %r31, 0(%r30) # Read address
	cmpwi %cr6, %r31, -1 # Check if end of patches
	beq %cr6, dumpCleanCache
	lwz %r11, 8(%r30) # Read length
	mtspr CTR, %r11
	addi %r30, %r30, 12 # Skip past what we have already read
patchDataLoop:
	lwz %r3, 0(%r30) # Read data
	stw %r3, 0(%r31) # Store data
	dcbst %r0, %r31 # Update cache
	sync
	isync
	addi %r30, %r30, 4
	addi %r31, %r31, 4
	bdnz+ patchDataLoop
	b patchLoop
	
dumpCleanCache:
	li %r30, 0x200
	oris %r30, %r30, 0x8000
	sldi %r30, %r30, 32
	addis %r30, %r30, 1
	li %r11, 0x1000
	mtspr CTR, %r11
cachePrintLoop:
	lbz %r3, 0(%r30)
	
putChar:
	lis %r4, 0x8000
	ori %r4, %r4, 0x200
	rldicr %r4, %r4, 32,31
	oris %r4, %r4, 0xEA00
waitloop:
	lwz %r5, 0x1018(%r4)
	rlwinm. %r5, %r5, 0,6,6
	beq waitloop
	slwi %r3, %r3, 24
	stw %r3, 0x1014(%r4)
	
	addi %r30, %r30, 1
	bdnz+ cachePrintLoop
	
freezeLoop:
	nop
	b freezeLoop
9:

.long 0xFFFFFFFF
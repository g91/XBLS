MakePatch 0x5090
0: 
	li %r5, 0x200
	oris %r5, %r5, 0x8000
	sldi %r5, %r5, 32
	oris %r5, %r5, 0xC800
	lbz %r4, 0x4D(%r5)
	isync
	cmplwi %r4, 0
	beq loc_A4
	lis %r3, -0x51FF
	lis %r4, -0x8000
	ori %r4, %r4, 0x200
	sldi %r4, %r4, 32
	oris %r4, %r4, 0xEA00
	stw %r3, 0x101C(%r4)

loc_A4:
	mfspr %r12, LR
	bl putDot
	mtspr LR, %r12
	li %r8, 0x200
	oris %r8, %r8, 0x8000
	sldi %r8, %r8, 32
	oris %r8, %r8, 0xEA00
	lis %r9, 0x400
	lis %r10, 0x100
	li %r11, 0
	stw %r9, 0x1084(%r8)
	stw %r10, 0x1080(%r8)
	stw %r11, 0x1080(%r8)
	stw %r11, 0x1080(%r8)
	stw %r11, 0x1080(%r8)
	stw %r11, 0x1084(%r8)

loc_E4:
	lwz %r12, 0x1094(%r8)
	and. %r12, %r12, %r9
	beq loc_E4
	stw %r9, 0x1094(%r8)
	lwz %r12, 0x1090(%r8)
	lwz %r3, 0x1090(%r8)
	lwz %r3, 0x1090(%r8)
	lwz %r3, 0x1090(%r8)
	stw %r11, 0x1094(%r8)
	srwi %r3, %r12, 24
	cmpwi %r3, 1
	bne loc_E4
	extrwi %r3, %r12, 8,8
	cmpwi %r3, 0
	beq loc_138
	lbz %r4, 0x4F(%r5)
	cmplw %r3, %r4
	beq loc_140
	lbz %r4, 0x4E(%r5)
	cmplw %r3, %r4
	beq loc_140

loc_138:
	lis %r3, 0x300
	blr

loc_140:
	li %r7, 0x200
	oris %r7, %r7, 0x8000
	sldi %r7, %r7, 32
	oris %r7, %r7, 6
	ori %r7, %r7, 0x1010
	li %r3, 0x10
	sldi %r3, %r3, 56
	std %r3, 0(%r7)
	bl sub_1E8
	li %r5, 0x200
	oris %r5, %r5, 0x8000
	sldi %r5, %r5, 32
	oris %r5, %r5, 0xC807
	ori %r5, %r5, 0
	lis %r6, -0x8000
	sldi %r6, %r6, 32
	oris %r6, %r6, 0x1C00
	mr %r9, %r6
	mtspr HRMOR, %r11
	li %r3, 0x11
	sldi %r3, %r3, 56
	std %r3, 0(%r7)
	lis %r4, 1
	mtspr CTR, %r4

loc_1A0:
	lwz %r8, 0(%r5)
	stw %r8, 0(%r6)
	dcbst %r0, %r6
	icbi %r0, %r6
	sync
	isync
	addi %r6, %r6, 4
	addi %r5, %r5, 4
	bdnz loc_1A0
	li %r3, 0x12
	sldi %r3, %r3, 56
	std %r3, 0(%r7)
	li %r4, 0x30
	mfmsr %r3
	andc %r3, %r3, %r4
	mtspr SRR1, %r3
	.long 0x7D3A03A6 # mtspr SR, %r0
	rfid

sub_1E8:
	lis %r3, -0x8000
	ori %r3, %r3, 0x17C
	sldi %r3, %r3, 32
	oris %r3, %r3, 0x400
	ori %r3, %r3, 0x525C
	li %r30, 0x200
	oris %r30, %r30, 0x8000
	sldi %r30, %r30, 32

loc_208:
	lwzu %r4, 4(%r3)
	cmplwi %r4, 0
	beqlr
	lwzu %r31, 4(%r3)
	stwbrx %r31, %r30, %r4
	li %r31, 0xFF
	andc %r4, %r4, %r31
	ori %r4, %r4, 4
	lwbrx %r31, %r30, %r4
	lwzu %r29, 4(%r3)
	or %r31, %r31, %r29
	stwbrx %r31, %r30, %r4
	b loc_208

 .quad 0xD0000010EA000000
 .quad 0x156D0008010
 .quad 0xE000000000000002
 .quad 0xD0010010EC800000
 .quad 0x2D0100010
 .quad 0xEA00180000000002
 .quad 0xD0108010EA001200
 .quad 0x6D0108014
 .quad 0xEA00122000000006
 .quad 0xD0110010EA001300
 .quad 0x6D0110014
 .quad 0xEA00132000000006
 .quad 0xD0120010EA002000
 .quad 0x156D0121010
 .quad 0xEA00300000000106
 .quad 0xD0128010EA004000
 .quad 0x156D0129010
 .quad 0xEA00500000000106
 .quad 0xD0138010EA001400
 .quad 0x6D0140010
 .quad 0xEA00C00000000006
 .quad 0xD0140014C8000000
 .quad 0x6D0148010
 .quad 0xEA00160000000006
 .quad 0xD0150010EA001000
 .quad 0x200000000

putDot:
	li %r3, '.'
	lis %r4, -0x8000
	ori %r4, %r4, 0x200
	sldi %r4, %r4, 32
	oris %r4, %r4, 0xEA00
	slwi %r3, %r3, 24
	stw %r3, 0x1014(%r4)
putDotLoop:
	lwz %r3, 0x1018(%r4)
	rlwinm. %r3, %r3, 0,6,6
	beq putDotLoop
	blr

	mfmsr %r7
	li %r8, 0x10
	andc %r8, %r7, %r8
	mtmsrd %r8, 0
	bl putDot
	li %r5, 0x200
	oris %r5, %r5, 0x8000
	sldi %r5, %r5, 32
	oris %r5, %r5, 0xC800
	ori %r5, %r5, 0
	lwz %r6, 0x70(%r5)
	lwz %r4, 0x64(%r5)
	cmplwi %r6, 0
	bne loc_374
	lis %r6, 1

loc_374:
	add %r4, %r4, %r6
	addi %r4, %r4, 0xC
	or %r3, %r5, %r4
	isync

loc_384:
	mtmsrd %r8, 0
	isync
	lwzu %r4, 4(%r3)
	cmpwi %r4, -1
	beq loc_3CC
	addi %r4, %r4, -4
	lwzu %r6, 4(%r3)
	mtspr CTR, %r6

loc_3A4:
	mtmsrd %r8, 0
	isync
	lwzu %r6, 4(%r3)
	mtmsrd %r7, 0
	isync
	stwu %r6, 4(%r4)
	dcbst %r0, %r4
	icbi %r0, %r4
	bdnz loc_3A4
	b loc_384

loc_3CC:
	sync
	isync
	mtmsrd %r7, 0
	rfid
9:

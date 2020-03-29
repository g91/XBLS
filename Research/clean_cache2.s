# Clean cache lines dump, which is what is basicly hashed in sub_2210
# http://i.gyazo.com/342bc86bfab45c620cca5dc4b0f55ae7.gif
# 4/6/15

MakePatch 0x22D8
0:
	.long 0x4800B527 # bla X
9:

MakePatch 0xB524
0:
	lis %r30, 0 # Zero patches register
	ori %r30, %r30, 0xB600 # Patches address
patchLoop:
	lwz %r31, 0(%r30) # Read address
	cmpwi %cr6, %r31, -1 # Check if end of patches
	beq %cr6, dumpCleanCache
	lwz %r11, 8(%r30) # Read length
	mtspr CTR, %r11
	addi %r30, %r30, 12 # Skip past what we have already read
patchDataLoop:
	lwz %r3, 0(%r30) # Read data
	stw %r3, 0(%r31) # Store data
	addi %r30, %r30, 4
	addi %r31, %r31, 4
	bdnz+ patchDataLoop
	b patchLoop
	
dumpCleanCache:
	li %r3, 0x80
	li %r4, 0x1FF
	.long 0x48000EE7 # bla 0xEE4
	
	addis %r3, %r2, 1
	addi %r3, %r3, 0x400
	li %r4, 0xB8
	.long 0x48000EE7 # bla 0xEE4
	
	addis %r3, %r2, 1
	addi %r3, %r3, 0x6D80
	li %r4, 0x125
	.long 0x48000EE7 # bla 0xEE4
	
	lis %r3, 2
	ori %r3, %r3, 1
	sldi %r3, %r3, 17
	li %r4, 0x200
	.long 0x48000EE7 # bla 0xEE4
	
	lis %r3, 6
	ori %r3, %r3, 3
	sldi %r3, %r3, 16
	li %r4, 0x200
	.long 0x48000EE7 # bla 0xEE4
	
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

# Patches that undo dirty patches :)
MakePatch 0xB600
0:
	# Reverse what I have done
	.quad 0x22D8
	.long 1
	.long 0x38610050 # addi %r3, %r1, 0x50
	
	# Reverse xeBuild patches
	.quad 0x1880
	.long 1
	.long 0x4BFFEA59 # bl build_68_01f50000
	
	#.quad 0x11BC
	#.long 1
	#.long 0x7C35EBA6 # mtspr 0x3B5, r1
	
	#.quad 0x154C
	#.long 4
	#.quad 0, 0 # Undo code cave
	
	#.quad 0x3120
	#.long 1
	#.long 0x4BFFEB31 # bl sub_1C50
	
	#.quad 0xA560 # HvxBlowFuses
	#.long 2
	#.long 0x7D8802A6 # mfspr %r12, LR
	#.long 0x48000299 # bl __savegplr_12
	
	#.quad 0x40002A30C
	#.long 2
	#.long 0x2F030000 # cmpwi %cr6, %r3, 0
	#.long 0x409A00C0 # bne %cr6, loc_2A3D0
	
	#.quad 0x40002AA80
	#.long 1
	#.long 0x4198022C # blt %cr6, loc_2ACAC
	
	#.quad 0x40002AA8C
	#.long 1
	#.long 0x41980220 # blt %cr6, loc_2ACAC
	
	#.quad 0xB4F8
	#.long 0x07
	#.long 0, 0, 0, 0, 0, 0, 0 # Undo code cave
	
	#.quad 0x6BB0 # HvxSecurityGetDetected
	#.long 2
	#.long 0x7D8802A6 # mfspr %r12, LR
	#.long 0xF981FFF8 # std %r12, -0x08(%r1)
	
	#.quad 0x6C48 # HvxSecuritySetActivated
	#.long 2
	#.long 0x3D620001 # addis %r11, %r2, 1
	#.long 0xA16B6914 # lhz %r11, 0x6914(%r11)
	
	#.quad 0x6C98 # HvxSecurityGetActivated
	#.long 2
	#.long 0x7D8802A6 # mfspr %r12, LR
	#.long 0xF981FFF8 # std %r12, -0x08(%r1)
	
	#.quad 0x6D08 # HvxSecuritySetStat
	#.long 2
	#.long 0x3D620001 # addis %r11, %r2, 1
	#.long 0xA16B6914 # lhz %r11, 0x6914(%r11)
	
	#.quad 0x6D58 # HvxGetProtectedFlags
	#.long 2
	#.long 0x7D8802A6 # mfspr %r12, LR
	#.long 0xF981FFF8 # std %r12, -0x08(%r1)
	
	#.quad 0x813C
	#.long 1
	#.long 0x419A0028 # beq %cr6, loc_8164
	
	#.quad 0x70BC
	#.long 1
	#.long 0x48004305 # bl XeCryptBnQwBeSigVerify
	
	#.quad 0x7268
	#.long 1
	#.long 0x48004201 # bl sub_B468
	
	#.quad 0x72B4
	#.long 1
	#.long 0x4BFF8F65 # bl MachineCheck
	
	#.quad 0x72C4
	#.long 1
	#.long 0x4BFF8F55 # bl MachineCheck
	
	#.quad 0x72EC
	#.long 2
	#.long 0x4BFF8F2D # bl MachineCheck
	#.long 0x817D03B0 # lwz %r11, 0x3B0(%r29)
	
	#.quad 0x400024D58
	#.long 2
	#.long 0x7D8802A6 # mfspr %r12, LR
	#.long 0xF981FFF8 # std %r12, -0x08(%r1)
	
	#.quad 0x4000264F0
	#.long 1
	#.long 0x480038DB # bla HvpPkcs1Verify
	
	#.quad 0x400029B08
	#.long 14
	#.long 0x2F030000 # cmpwi %cr6, %r3, 0
	#.long 0x409A0010 # bne %cr6, loc_29B1C
	#.long 0x3FE0C000 # lis %r31, -0x4000
	#.long 0x63FF0221 # ori %r31, %r31, 0x221
	#.long 0x48000028 # b loc_29B40
	#.long 0x2B3C0000 # cmpldi %cr6, %r28, 0
	#.long 0x419A001C # beq %cr6, loc_29B3C
	#.long 0x2B1D0000 # cmplwi %cr6, %r29, 0
	#.long 0x389F0440 # addi %r4, %r31, 0x440
	#.long 0x409A0008 # bne %cr6, loc_29B34
	#.long 0x38800054 # li %r4, 0x54 ('T')
	#.long 0x7F83E378 # mr %r3, %r28
	#.long 0x4BFF65C1 # bl XeCryptAesKey
	#.long 0x3BE00000 # li %r31, 0
	
	#.quad 0x40002C088
	#.long 1
	#.long 0x48000889 # bl sub_2C910
	
	#.quad 0x40002C378
	#.long 1
	#.long 0x419AFFDC # beq %cr6, loc_2C354
	
	#.quad 0x60003089C
	#.long 4
	#.long 0x419AFF40 # beq %cr6, loc_307DC
	#.long 0x817F0008 # lwz %r11, 8(%r31)
	#.long 0x7F0BE040 # cmplw %cr6, %r11, %r28
	#.long 0x4199FF34 # bgt %cr6, loc_307DC
	
	#.quad 0x6000304E8
	#.long 1
	#.long 0x409AFFC4 # bne %cr6, loc_304AC
	
	#.quad 0x6000304FC
	#.long 1
	#.long 0x409AFFB0 # bne %cr6, loc_304AC
	
	.quad 0xFFFFFFFF # End of patches
9:

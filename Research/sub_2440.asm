# =============== S U B	R O U T	I N E =======================================


sub_2440:

.set var_C0, -0xC0
.set var_A0, -0xA0
.set var_20, -0x20
.set var_10, -0x10
.set var_8, -8

		mflr	  r12
		std	  	r12, -8(r1)
		std	  r31, -0x10(r1)
		stdu	  r1, -0x110(r1)
		addis	  r11, r2, 1
		li	  r4, 0x14
		addi	  r3, r1, 0x50
		lwz	  r11, 0(r11)
		stw	  r11, 0xF0(r1)
		bl	  sub_B488
		addis	  r11, r2, 1
		addi	  r8, r1, 0x50
		addi	  r3, r11, 0x100
		li	  r7, 0
		li	  r6, 0x80 # '€'
		addi	  r5, r1, 0x70
		li	  r4, 0x30 # '0'
		bl	  sub_B428
		cmpwi	  cr6, r3, 0
		beq	  cr6, loc_24F0
		li	  r4, 0x80 # '€'
		addi	  r3, r1, 0x70
		bl	  sub_B480
		li	  r5, 0x10
		addi	  r4, r1, 0x70
		addi	  r3, r1, 0x70
		bl	  sub_B3A8
		addis	  r11, r2, 1
		addi	  r3, r1, 0x70
		addi	  r5, r11, 0x350
		addis	  r11, r2, 1
		addi	  r31, r11, 0x40
		mr	  r4, r31
		bl	  sub_B3E8
		cmpwi	  cr6, r3, 0
		mr	  r3, r31
		bne	  cr6, loc_24E4
		li	  r5, 0x80 # '€'
		li	  r4, 0
		bl	  sub_AD20
		b	  loc_24F0
# ---------------------------------------------------------------------------

loc_24E4:
		li	  r5, 0x10
		mr	  r4, r31
		bl	  sub_B3A8

loc_24F0:
		lwz	  r3, 0xF0(r1)
		bl	  sub_204
		addi	  r1, r1, 0x110
		ld	  r12, -8(r1)
		mtlr	  r12
		ld	  r31, -0x10(r1)
		blr
# End of function sub_2440

# ---------------------------------------------------------------------------

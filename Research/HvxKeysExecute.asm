#
# +-------------------------------------------------------------------------+
# |   This file	has been generated by The Interactive Disassembler (IDA)    |
# |	      Copyright	(c) 2011 Hex-Rays, <support@hex-rays.com>	    |
# |			 License info: B3-432E-F558-21			    |
# |				Ilfak Guilfanov				    |
# +-------------------------------------------------------------------------+
#



# =============== S U B	R O U T	I N E =======================================


HvxKeysExecute:				# DATA XREF: ROM:SC_40o

.set var_3E0, -0x3E0
.set var_3D4, -0x3D4
.set var_3D0, -0x3D0
.set var_2C0, -0x2C0
.set var_1B0, -0x1B0
.set var_1A0, -0x1A0
.set var_180, -0x180
.set var_80, -0x80

		mflr	  r12
		bl	  sub_EF80
		stdu	  r1, -0x430(r1)
		addis	  r11, r2, 1
		mr	  r24, r3
		mr	  r26, r4
		clrlwi	  r10, r24, 25
		mr	  r21, r5
		lwz	  r11, 0(r11)
		mr	  r20, r6
		mr	  r19, r7
		mr	  r18, r8
		cmplwi	  cr6, r10, 0
		stw	  r11, 0x430+var_80(r1)
		bne	  cr6, loc_8D78
		clrlwi	  r11, r26, 25
		cmplwi	  cr6, r11, 0
		bne	  cr6, loc_8D78
		addi	  r11, r26, -0x120
		cmplwi	  cr6, r11, 0xFEE0
		bgt	  cr6, loc_8D78
		add	  r11, r24, r26
		addi	  r11, r11, -1
		xor	  r11, r11, r24
		clrrwi	  r11, r11, 16
		cmplwi	  cr6, r11, 0
		bne	  cr6, loc_8D78
		bl	  sub_7C30
		mr	  r31, r3
		cmpldi	  cr6, r31, 0
		bne	  cr6, loc_8B00
		lwz	  r3, 0x430+var_80(r1)
		bl	  sub_1B4
		lis	  r3, -0x3800 #	0xC8000031
		ori	  r3, r3, 0x31 # 0xC8000031
		b	  loc_8D88
# ---------------------------------------------------------------------------

loc_8B00:				# CODE XREF: HvxKeysExecute+78j
		addi	  r3, r1, 0x430+var_3D0
		li	  r5, 0x110
		mr	  r4, r31
		bl	  sub_F020
		addi	  r11, r31, 0x148
		addi	  r10, r1, 0x430+var_1B0
		li	  r9, 0x10
		mtctr	  r9

loc_8B20:				# CODE XREF: HvxKeysExecute+C0j
		lbz	  r9, 0(r11)
		addi	  r11, r11, 1
		stb	  r9, 0(r10)
		addi	  r10, r10, 1
		bdnz	  loc_8B20
		addis	  r11, r2, 2
		addi	  r22, r11, -0x220
		mr	  r3, r22
		bl	  loc_A7C
		li	  r5, 0x3E # '>'
		mr	  r4, r26
		mr	  r3, r24
		bl	  loc_2DC0
		mr	  r31, r3
		li	  r23, 0
		lhz	  r11, 0(r31)
		clrlwi	  r10, r11, 20
		rlwinm	  r10, r10, 0,28,23
		cmplwi	  cr6, r10, 0xD0D
		beq	  cr6, loc_8BE0
		lis	  r30, -0x3800 # 0xC8000032
		ori	  r30, r30, 0x32 # 0xC8000032

loc_8B78:				# CODE XREF: HvxKeysExecute+18Cj
					# HvxKeysExecute+274j ...
		addi	  r11, r1, 0x430+var_180
		mr	  r9, r23
		li	  r10, 0x20 # ' '
		mtctr	  r10

loc_8B88:				# CODE XREF: HvxKeysExecute+120j
		std	  r9, 0(r11)
		addi	  r11, r11, 8
		bdnz	  loc_8B88

loc_8B94:				# CODE XREF: HvxKeysExecute+304j
		mr	  r4, r26
		mr	  r3, r31
		bl	  sub_494
		mr	  r4, r26
		mr	  r3, r24
		bl	  sub_2710
		srwi	  r4, r26, 7
		mr	  r31, r3
		bl	  loc_B6C
		addi	  r3, r31, 0x20
		addi	  r4, r1, 0x430+var_180
		li	  r5, 0x100
		bl	  sub_F020
		mr	  r3, r22
		bl	  loc_AAC
		lwz	  r3, 0x430+var_80(r1)
		bl	  sub_1B4
		mr	  r3, r30
		b	  loc_8D88
# ---------------------------------------------------------------------------

loc_8BE0:				# CODE XREF: HvxKeysExecute+FCj
		lhz	  r10, word_0
		xor	  r11, r10, r11
		rlwinm	  r11, r11, 0,16,19
		cmplwi	  cr6, r11, 0
		beq	  cr6, loc_8C00
		lis	  r30, -0x3800 # 0xC8000033
		ori	  r30, r30, 0x33 # 0xC8000033
		b	  loc_8B78
# ---------------------------------------------------------------------------

loc_8C00:				# CODE XREF: HvxKeysExecute+180j
		lwz	  r27, 0xC(r31)
		addi	  r11, r27, 0xF
		cmplwi	  cr6, r27, 0x120
		clrrwi	  r28, r11, 4
		blt	  cr6, loc_8D54
		cmplw	  cr6, r28, r27
		blt	  cr6, loc_8D54
		cmplw	  cr6, r28, r26
		bgt	  cr6, loc_8D54
		lwz	  r25, 8(r31)
		clrlwi	  r11, r25, 30
		cmplwi	  cr6, r11, 0
		bne	  cr6, loc_8D48
		cmplwi	  cr6, r25, 0x120
		blt	  cr6, loc_8D48
		clrrwi	  r11, r27, 2
		cmplw	  cr6, r25, r11
		bge	  cr6, loc_8D48
		addi	  r11, r1, 0x430+var_1B0
		li	  r6, 0x10
		addi	  r29, r31, 0x10
		li	  r10, 0
		li	  r9, 0
		li	  r8, 0
		std	  r11, 0x430+var_3E0(r1)
		li	  r7, 0
		stw	  r6, 0x430+var_3D4(r1)
		li	  r4, 0x10
		addi	  r3, r1, 0x430+var_1B0
		mr	  r5, r29
		bl	  sub_F808
		li	  r5, 0x10
		addi	  r4, r1, 0x430+var_1B0
		addi	  r3, r1, 0x430+var_2C0
		bl	  sub_F850
		addi	  r30, r31, 0x20
		addi	  r5, r28, -0x20
		addi	  r3, r1, 0x430+var_2C0
		mr	  r4, r30
		bl	  sub_F848
		li	  r8, 0x14
		addi	  r7, r1, 0x430+var_1A0
		addi	  r6, r28, -0x120
		addi	  r5, r31, 0x120
		li	  r4, 0x10
		mr	  r3, r31
		bl	  sub_F868
		addis	  r11, r2, 1
		addi	  r6, r1, 0x430+var_3D0
		addi	  r5, r11, 0x11B0
		addi	  r4, r1, 0x430+var_1A0
		mr	  r3, r30
		bl	  sub_F780
		cmpwi	  cr6, r3, 0
		bne	  cr6, loc_8CE8
		lis	  r30, -0x3800 # 0xC8000036
		ori	  r30, r30, 0x36 # 0xC8000036
		b	  loc_8B78
# ---------------------------------------------------------------------------

loc_8CE8:				# CODE XREF: HvxKeysExecute+268j
		std	  r23, 0(r29)
		li	  r5, 0x100
		li	  r4, 0
		std	  r23, 8(r29)
		mr	  r3, r30
		bl	  sub_F4C0
		cmplw	  cr6, r27, r26
		bge	  cr6, loc_8D1C
		clrldi	  r11, r27, 32
		subf	  r5, r27, r26
		li	  r4, 0
		add	  r3, r11, r31
		bl	  sub_F4C0

loc_8D1C:				# CODE XREF: HvxKeysExecute+294j
		clrldi	  r11, r25, 32
		mr	  r7, r18
		mr	  r6, r19
		mr	  r5, r20
		mr	  r4, r21
		mr	  r3, r31
		add	  r11, r11, r31
		mtctr	  r11
		bctrl
		mr	  r30, r3
		b	  loc_8D5C
# ---------------------------------------------------------------------------

loc_8D48:				# CODE XREF: HvxKeysExecute+1C0j
					# HvxKeysExecute+1C8j ...
		lis	  r30, -0x3800 # 0xC8000035
		ori	  r30, r30, 0x35 # 0xC8000035
		b	  loc_8B78
# ---------------------------------------------------------------------------

loc_8D54:				# CODE XREF: HvxKeysExecute+1A0j
					# HvxKeysExecute+1A8j ...
		lis	  r30, -0x3800 # 0xC8000034
		ori	  r30, r30, 0x34 # 0xC8000034

loc_8D5C:				# CODE XREF: HvxKeysExecute+2D4j
		cmpwi	  cr6, r30, 0
		bne	  cr6, loc_8B78
		addi	  r4, r31, 0x20
		addi	  r3, r1, 0x430+var_180
		li	  r5, 0x100
		bl	  sub_F020
		b	  loc_8B94
# ---------------------------------------------------------------------------

loc_8D78:				# CODE XREF: HvxKeysExecute+38j
					# HvxKeysExecute+44j ...
		lwz	  r3, 0x430+var_80(r1)
		bl	  sub_1B4
		lis	  r3, -0x3800 #	0xC8000030
		ori	  r3, r3, 0x30 # 0xC8000030

loc_8D88:				# CODE XREF: HvxKeysExecute+8Cj
					# HvxKeysExecute+16Cj
		addi	  r1, r1, 0x430
		b	  loc_EFD0
# End of function HvxKeysExecute


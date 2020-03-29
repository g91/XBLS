.macro MakePatch PatchAddress
	.set _PatchAddress, \PatchAddress
	.long _PatchAddress
	.long (9f - 0f) / 4
.endm

.macro MakeNOP Address
	.set _Address, \Address
	.long _Address
	.long 1
	nop
.endm

.macro MakeZeroReturn Address
	.set _Address, \Address
	.long _Address
	.long 2
	li %r3, 0
	blr
.endm

.macro MakeOneReturn Address
	.set _Address, \Address
	.long _Address
	.long 2
	li %r3, 1
	blr
.endm

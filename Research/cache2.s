    .globl _start
_start:

######### SET VARIABLES #########
.set codeLoc, 0xB618 # where our code will be in the HV, it has to be empty space
.set hashGen, 0x364 # location where 100F0 will be generated
.set callLoc, 0x1958 # call to hashGen address, may change with dash version
.set callOrig, 0x4182EA0D # original bits at the call location
######### END VARIABLES #########

.set size,	(6f-0f) # don't change this

#########  JUMP TO OUR CODE  #########
.long callLoc 
.long 0x1
    ba codeLoc
#########  END OF JUMP  #########

.long codeLoc
.long (9f-0f)/4
0:
#########  COPY FROM 0xB618 IN HV TO MEMORY  #########
    # r20 source address # 0xB618
    lis %r20, 0
    ori %r20, %r20, codeLoc
    addi %r20, %r20, size # 0xB618 + size

    # r21 destination # 0x800000001C040000
    lis %r21, 0x3808
    ori %r21, %r21, 1
    extldi %r21, %r21, 64,63

    li %r11, 0x1000 # size of the instructions
    mtctr %r11
loop_3:
    lbz %r22, 0(%r20)
    stb %r22, 0(%r21)
    sync
    isync
    addi %r20, %r20, 1
    addi %r21, %r21, 1
    bdnz loop_3
#########  END OF COPY  #########

    # Restore original bits 0x4BFFFE61 at address 0x23B0
    lis %r11, callOrig@h		
    ori %r11, %r11, callOrig@l
    li %r20, callLoc
    stw %r11, 0(%r20)

    ####################################

    # Jump to memory location to continue our code
    lis %r20, 0x3808
    ori %r20, %r20, 1
    extldi %r20, %r20, 64,63
    mtlr %r20
    blr
6:
#########  START MEMORY CODE #########
    # Clear our code from HV location 0xB618
    lis %r20, 0x8000
    ori %r20, %r20, 0x100
    sldi %r20, %r20, 32
    ori %r20, %r20, codeLoc  # 0x800001000000B618

    li %r11, 0x1000 # 
    addi %r11, %r11, size # 0x1000 + size of the code until 6:
    mtctr %r11
loop6_1:
    lis %r21, 0
    stb %r21, 0(%r20)
    addi %r20, %r20, 1
    bdnz loop6_1

    # After clearing our code from hypervisor, we are
    # ready to call 0x2210 to generate the 0x100F0 hash
    lis %r20, 0x8000
    ori %r20, %r20, 0x100
    sldi %r20, %r20, 32
    ori %r20, %r20, hashGen # 0x8000010000002210

    mtlr %r20
    blrl
7:
    # this will output the 100F0 hash
    lis %r3, 1
    lis %r29, -0x8000
    ori %r29, %r29, 0x102
    insrdi %r3, %r29, 32,0
    ori %r3, %r3, 0xF0	# 0x80000102000100F0
    li %r4, 0x10
    bl printAddress
	
	lis %r3, 1
	lis %r29, -0x8000
	ori %r29, %r29, 0x0200
	insrdi %r3, %r29, 32,0
	ori %r3, %r3, 0xF810 #0x800002000001f811
    li %r4, 0x10
    bl printAddress	
    blr

printAddress:
    mr %r30, %r3
    mr %r11, %r4 # text size
    mtctr %r11
cachePrintLoop:
    lbz %r3, 0(%r30)
putChar:
    lis %r4, 0x8000
    ori %r4, %r4, 0x200
    rldicr %r4, %r4, 32,31
    oris %r4, %r4, 0xEA00
waitloop:
    lwz %r5, 0x1018(%r4) # wait until character is sent
    rlwinm. %r5, %r5, 0, 6, 6
    beq waitloop
    slwi %r3, %r3, 24
    stw %r3, 0x1014(%r4) # send the character
    addi %r30, %r30, 1
    bdnz+ cachePrintLoop
    blr
9:
typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef unsigned long long    qword;
typedef unsigned char    undefined1;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    word;



undefined* _v_RESET(void) {
  ushort *puVar1;
  int iVar2;
  QWORD uVar3;
  undefined8 uVar4;
  uint uVar5;
  uint uVar6;
  QWORD *puVar7;
  int iVar8;
  QWORD uVar9;
  QWORD in_spr130;
  int in_spr131;
  QWORD in_spr139;
  QWORD in_spr399;
  QWORD in_spr3f1;
  uint in_PIR;
  
  uVar3 = in_spr3f1 & 0xf3ffffbfffffffff | 0xc00004000000000;
  sync(0);
  sync(0);
  instructionSynchronize();
  if (in_spr131 == 0) {
    uVar6 = in_PIR & 7;
    uVar9 = (QWORD)uVar6;
    if (uVar6 == 0) {
      uVar4 = FUN_000002d8(uVar3);
      HvpZeroCacheLines(uVar4,0x200);
      uVar4 = FUN_000002e8();
      uVar3 = HvpZeroCacheLines(uVar4,0x200);
    }
    if (in_spr130 == 0) {
      if ((in_PIR & 1) != 0) {
        instructionSynchronize();
        instructionSynchronize();
      }
      uVar3 = uVar9 & 1;
      if ((in_PIR & 1) == 0) {
        instructionSynchronize();
        uVar3 = in_spr399 & 0xffffffff07f2ffff | 0xd0000;
        instructionSynchronize();
        instructionSynchronize();
      }
      if (uVar6 != 0) {
        uVar3 = uVar9 & 1;
      }
    }
    uVar5 = FUN_000002e8(uVar3,0x62);
    *(undefined *)(((in_PIR & 7) << 0xd | uVar5 & 0xffff0000) + 0x80) = (char)uVar6;
    iVar2 = 0;
    if (uVar6 == 0) {
      iVar2 = 0;
      FUN_00000364();
    }
    iVar8 = 0;
    slbInvalidateAll();
    do {
      puVar1 = (ushort *)(iVar8 + 0x8e0);
      iVar8 = iVar8 + 2;
      slbMoveToEntry();
    } while (*puVar1 >> 0xc != 0xf);
    if (uVar6 == 0) {
      uVar4 = 0x6801f50000;
      uVar3 = FUN_00000280();
      uVar6 = (uint)((in_spr139 | uVar3) >> 10) & 0xffffffe0 | 0xf;
      *(uint *)((int)uVar4 + 0x3800) = uVar6;
      *(int *)((int)uVar4 + 0x3804) = uVar6 + 0x40;
      uVar3 = FUN_00000298();
      *(uint *)((int)uVar4 + 0x380c) = (uint)((in_spr139 | uVar3) >> 10) & 0xffffffe0 | 0xf;
      uVar3 = FUN_000002a8();
      *(uint *)((int)uVar4 + 0x3814) = (uint)((in_spr139 | uVar3) >> 10) & 0xffffffe0 | 0xf;
      uVar3 = FUN_000002b8();
      *(uint *)((int)uVar4 + 0x4000) = (uint)((in_spr139 | uVar3) >> 10) & 0xffffffe0 | 0xf;
      *(uint *)(&0x10004 + iVar2) =
           ((uint)(in_spr139 >> 0x10) | (uint)((QWORD)uVar4 >> 0x10)) & 0x3ffffff;
    }
    HvxFlushEntireTb();
    puVar7 = (QWORD *)((in_PIR & 7) << 0xc | 0x50000);
    puVar7[0xe] = 0x7c;
    eieioOp();
    puVar7[1] = 0x7c;
    eieioOp();
    *puVar7 = (QWORD)(uint)(1 << uVar9);
    eieioOp();
    sync(0);
    instructionSynchronize();
    returnFromInterrupt();
    return &0x0d81e;
  }
  if (*(char *)(in_spr131 + 0x83) == '\0') {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(undefined *)(in_spr131 + 0x83) = 0;
  return (undefined *)0;
}


void _V_RESET()
{
	QWORD HID1 = mfspr(SPR_HID1);
	HID1 = (HID1 & 0xF3FFFFBFFFFFFFFF) | (3 << 58) | (1 << 38);
	// s
	mtspr(SPR_HID1, HID1);

	PTHREAD_STATE pThreadState = (PTHREAD_STATE)HSPRG1;

	// if HSPRG1 has not been set up, this is a Power On Reset
	if(!pThreadState)
		POR();

	// if HSPRG1 has been set up but the thread was not suspended, this reset is an error
	if(!pThreadState->SUSPENDED)
		MACHINE_CHECK();

	pThreadState->SUSPENDED = 0;

	// HvpSleepThread saves SRR0 and SRR1 to these registers
	mtspr(SPR_SRR0, r7);
	mtspr(SPR_SRR1, r8);
	_cctpm()

	return;
}

// sub_150
void HvpSleepThread(void) {
  int in_spr131;
  uint in_PIR;
  
  *(undefined *)(in_spr131 + 0x83) = 1;
  sync(0);
  instructionSynchronize();
  if ((in_PIR & 1) != 1) {
    sync(0);
    sync(0);
    instructionSynchronize();
  }
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}

// sub_150
void HvpSleepThread()
{
	// save some context
	QWORD PIR = mfspr(SPR_PIR);
	QWORD SRR0 = mfspr(SPR_SRR0);
	QWORD SRR1 = mfspr(SPR_SRR1);
	PTHREAD_STATE pThreadState = (PTHREAD_STATE)mfspr(HSPRG1);

	// set the state
	pThreadState->SUSPENDED = 1;

	PIR = PIR & 1;
	if(!PIR)
	{
		QWORD HID1 = mfspr(SPR_HID1);
		HID1 = (HID1 & 0xF3FFFFFFFFFFFFFF) | ((PIR & 3) << 58); 
		// s
		mtspr(SPR_HID1, HID1); // s_is
	}

	// wait until sys reset to resume
	for(;;)
		mtspr(SPR_CTRL, 0);
}


void HvpAquireSpinLock(undefined8 param_1) {
  int iVar1;
  int iVar2;
  int *piVar3;
  char in_RESERVE;
  
  do {
    piVar3 = (int *)param_1;
    iVar1 = *piVar3;
    if (iVar1 == 0) {
      if (in_RESERVE != '\0') {
        iVar2 = storeWordConditionalIndexed(param_1,0,param_1);
        *piVar3 = iVar2;
      }
      if (iVar1 == 0) {
        sync(1);
        return;
      }
    }
    do {
    } while (*piVar3 != 0);
  } while( true );
}



void HvpReleaseSpinLock(undefined4 *param_1)

{
  sync(1);
  *param_1 = 0;
  return;
}



void _v_MACHINE_CHECK(void)

{
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void FUN_00000204(int param_1)

{
  int in_r2;
  
  if (param_1 == *(int *)(in_r2 + 0x10000)) {
    return;
  }
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void _v_MACHINE_CHECK_0(void)

{
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



undefined8 FUN_00000270(void)

{
  return 0x7601ee0000;
}



undefined8 FUN_00000280(void)

{
  return 0x8000030001ef0000;
}



undefined8 thunk_FUN_00000298(void)

{
  return 0x6401f10000;
}



undefined8 FUN_00000298(void)

{
  return 0x6401f10000;
}



undefined8 FUN_000002a8(void)

{
  return 0x6601f20000;
}



undefined8 FUN_000002b8(void)

{
  return 0x6e01f30000;
}



undefined8 FUN_000002c8(void)

{
  return 0x6c01f40000;
}



undefined8 FUN_000002d8(void)

{
  return 0x6801f50000;
}



undefined8 FUN_000002e8(void)

{
  return 0x6a01f60000;
}



// WARNING: Type propagation algorithm not settling

undefined8 _v_DATA_STORAGE(undefined8 param_1,undefined8 param_2,undefined8 param_3){
  ushort uVar1;
  uint uVar2;
  QWORD uVar3;
  ushort *puVar4;
  uint uVar5;
  byte bVar6;
  QWORD *puVar7;
  undefined *puVar9;
  QWORD uVar8;
  int iVar10;
  uint *puVar11;
  undefined8 in_r13;
  QWORD uVar12;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  uint in_DSISR;
  uint in_DAR;
  uint in_SRR0;
  QWORD in_SRR1;
  uint in_spr130;
  QWORD in_spr131;
  word back_chain;
  
  *(QWORD *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(byte *)(in_spr130 + 0xf) = in_cr0 & 0xf;
  if (!SUB41((in_DSISR << 1) >> 0x1f,0)) goto LAB_0000163c;
  if ((bool)(((byte)((uint)((int)in_SRR1 << 0x10) >> 0x18) & 0x40) >> 6)) {
    iVar10 = (*(uint *)(in_spr130 + 0x58) & 2) * 8;
    uVar12 = *(QWORD *)(&0x10338 + iVar10) << 0x20;
    uVar3 = (QWORD)in_DAR;
    if (*(QWORD *)(&0x10330 + iVar10) != 0) {
      uVar5 = (uint)(*(QWORD *)(&0x10338 + iVar10) >> (in_DAR >> 0x1b & 0x1e) + 0x20) & 3;
      uVar2 = (uint)*(QWORD *)(&0x10330 + iVar10);
      if (uVar5 < 2) {
        uVar1 = *(ushort *)(in_DAR >> 0x16 & 0x3fe | uVar2 & 0xfffffc01);
        puVar11 = (uint *)((uint)uVar1 << 0xd | in_DAR >> 10 & 0x1ffc);
        if (uVar1 != 0) {
          puVar9 = (undefined *)*puVar11;
          if (puVar9 != (undefined *)0x0) {
            uVar2 = (uint)puVar9 & 0x80;
            if (((uint)puVar9 & 4) == 0) {
              puVar9 = (undefined *)((uint)puVar9 | 3);
            }
            if ((uVar2 == 0) && ((in_DSISR & 0x2000000) != 0)) {
              *puVar11 = (uint)puVar9 | 0x80;
              TLBInvalidateEntryLocal(uVar12 | uVar3 & 0xfffffffffffff000);
              eieioOp();
              sync(2);
            }
            goto LAB_00001188;
          }
        }
      }
      else {
        if (uVar5 < 3) {
          uVar1 = *(ushort *)((in_DAR >> 0x1a & 0x3e | uVar2 & 0xffffffc1) + 0x800);
          puVar11 = (uint *)((uint)uVar1 << 0xd | in_DAR >> 0xe & 0x1ffc);
          if (uVar1 != 0) {
            uVar2 = *puVar11;
            uVar8 = (QWORD)uVar2;
            if (uVar2 != 0) {
              if ((uVar2 & 4) == 0) {
                uVar8 = uVar8 | 3;
              }
              if (((uVar2 & 0x80) == 0) && ((in_DSISR & 0x2000000) != 0)) {
                *puVar11 = (uint)(uVar8 | 0x80);
                TLBInvalidateEntryLocal(uVar12 | uVar3 & 0xffffffffffff0000,uVar8 | 0x80,0,0,0);
                eieioOp();
                sync(2);
              }
              goto LAB_00001188;
            }
          }
        }
        else {
          uVar5 = in_DAR >> 0x16 & 0x3fc | uVar2 & 0xfffffc03;
          uVar2 = *(uint *)(uVar5 + 0x400);
          uVar8 = (QWORD)uVar2;
          if (uVar2 != 0) {
            if ((uVar2 & 4) == 0) {
              uVar8 = uVar8 | 3;
            }
            if (((uVar2 & 0x80) == 0) && ((in_DSISR & 0x2000000) != 0)) {
              *(int *)(uVar5 + 0x400) = (int)(uVar8 | 0x80);
              TLBInvalidateEntryLocal
                        (uVar12 | uVar3 & 0xffffffffff000000 | 0x1000,uVar8 | 0x80,0,0,0);
              eieioOp();
              sync(2);
            }
            goto LAB_00001188;
          }
        }
      }
    }
    goto LAB_0000163c;
  }
  switch(in_DAR >> 0x1b & 0x1e) {
  default:
    uVar2 = *(uint *)(in_DAR >> 0x14 & 0xffc | (in_spr130 & 0xffff0000) + 0x10000);
    if ((uVar2 & 1) != 0) {
      uVar2 = *(uint *)((in_DAR >> 10 & 0xffc) + (uVar2 & 0x1ffff000));
      goto joined_r0x00001274;
    }
    goto LAB_00001018;
  case 8:
  case 10:
  case 0xc:
  case 0xe:
    uVar2 = in_DAR >> 0xe & 0xfffc;
    if (uVar2 == 0xfffc) goto LAB_00001188;
    uVar2 = *(uint *)(uVar2 + 0x1f70000);
joined_r0x00001274:
    if ((uVar2 & 1) != 0) goto LAB_00001188;
LAB_00001018:
    if (in_SRR0 == 0x80075f90) {
      returnFromInterrupt();
      return *(undefined8 *)(in_spr130 + 0x40);
    }
    goto LAB_0000163c;
  case 0x10:
    if (7 < (*(uint *)((in_DAR >> 0xe & 0x7ffc) + 0x1f50000) & 0xf)) goto LAB_00001188;
    goto LAB_0000163c;
  case 0x12:
    if ((*(uint *)((in_DAR >> 0xe & 0x7ffc) + 0x1f50000) & 0xf) < 8) goto LAB_0000163c;
    bVar6 = *(byte *)(in_DAR >> 0xd & 0xffff | 0x1f50000) >> (QWORD)(in_DAR >> 10 & 4);
    break;
  case 0x14:
  case 0x16:
    bVar6 = (byte)(&0x11000)[(in_DAR >> 0x11 & 0xfff) + (in_spr130 & 0xffff0000)] >>
            (QWORD)(in_DAR >> 0xe & 4);
    break;
  case 0x18:
  case 0x1a:
    bVar6 = (byte)(&0x10c00)[(in_DAR >> 0x19 & 0xf) + (in_spr130 & 0xffff0000)] >>
            (QWORD)(in_DAR >> 0x16 & 4);
    break;
  case 0x1c:
  case 0x1e:
    if ((*(uint *)((in_DAR + 0x1000 >> 10 & 0x7fffc) + 0x1f80000) & 3) == 3) goto LAB_00001188;
    goto LAB_0000163c;
  }
  if ((bVar6 & 0xf) != 0) {
LAB_00001188:
    uVar2 = (uint)in_spr131 >> 7 & 0x40;
    uVar12 = (QWORD)(((uint)in_spr131 & 0x1000) << 1) |
             (QWORD)uVar2 | in_spr131 & 0xffffffffffffdfbf;
    puVar7 = (QWORD *)uVar12;
    *puVar7 = uVar12;
    sync(1);
    if (*(QWORD *)((uint)puVar7 ^ 0x40) != 0) {
      if (uVar2 == 0) {
        do {
        } while (puVar7[8] != 0);
      }
      else {
        do {
          *puVar7 = 0;
          sync(1);
          do {
          } while (puVar7[-8] != 0);
          *puVar7 = uVar12;
          sync(1);
        } while (puVar7[-8] != 0);
      }
    }
    *puVar7 = 0;
    returnFromInterrupt();
    return *(undefined8 *)(in_spr130 + 0x40);
  }
LAB_0000163c:
  *(uint *)(in_spr130 + 100) = in_DSISR;
  *(uint *)(in_spr130 + 0x60) = in_DAR;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(QWORD *)(in_spr130 + 0x28) =
       (QWORD)
       ((uint)*(byte *)(in_spr130 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | (QWORD)in_SRR0;
  if (!(bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    returnFromInterrupt();
    return *(undefined8 *)(in_spr130 + 0x40);
  }
  *(undefined8 *)(in_spr130 + 0x50) = *(undefined8 *)(in_spr130 + 0x50);
  *(undefined8 *)(in_spr130 + 0x40) = *(undefined8 *)(in_spr130 + 0x40);
  iVar10 = 0;
  slbInvalidateAll();
  do {
    puVar4 = (ushort *)(iVar10 + 0x8e0);
    iVar10 = iVar10 + 2;
    slbMoveToEntry();
  } while (*puVar4 >> 0xc != 0xf);
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}

void FUN_00000364(void) {
  int in_r2;
  
  FUN_0000b158();
  FUN_00001f60();
  FUN_00002bc0();
  FUN_0000a120();
  FUN_00003f88();
  FUN_00001b10();
  FUN_00001c50();
  FUN_00002dd8();
  FUN_00002e90();
  FUN_00002ff0();
  if ((*(ushort *)(&0x16a9c + in_r2) & 0x8000) == 0) {
    FUN_00003040();
  }
  return;
}



void _v_DATA_SEGMENT(void)

{
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



undefined8 HvpSetRMCIEx(undefined param_1,QWORD param_2,QWORD param_3)

{
  if (((param_2 | param_3) >> 0x29 & 1) == 0) {
    return (undefined8)_param_1;
  }
  instructionSynchronize();
  instructionSynchronize();
  TLBInvalidateEntryLocal(0x3ff00000000,ZEXT48(register0x0000000c),0,0,0);
  sync(0);
  instructionSynchronize();
  return 0x3ff00000000;
}



undefined8 HvpSetRMCI(void)

{
  instructionSynchronize();
  instructionSynchronize();
  TLBInvalidateEntryLocal(0x3ff00000000,ZEXT48(register0x0000000c),0,0,0);
  sync(0);
  instructionSynchronize();
  return 0x3ff00000000;
}



QWORD HvpZeroCacheLines(QWORD param_1,QWORD param_2)

{
  undefined8 in_r0;
  
  if (param_2 == 0) {
    return param_1;
  }
  do {
    DataCaseBlockSetToZero(in_r0,param_1);
    param_1 = param_1 + 0x80;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return param_1;
}



void FUN_000003e0(void)

{
  return;
}



void FUN_000003f0(void)

{
  return;
}



// WARNING: Removing unreachable block (ram,0x000014c0)
// WARNING: Removing unreachable block (ram,0x00001440)
// WARNING: Removing unreachable block (ram,0x0000152c)
// WARNING: Type propagation algorithm not settling

undefined8 _v_INSTRUCTION_STORAGE(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ushort uVar1;
  ushort *puVar2;
  QWORD *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined8 in_r13;
  QWORD uVar7;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  uint in_SRR0;
  QWORD in_SRR1;
  int in_spr130;
  QWORD in_spr131;
  
  *(QWORD *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(undefined *)(in_spr130 + 0xf) = (char)((uint)in_cr0 & 0xf);
  if (SUB41((uint)((int)in_SRR1 << 1) >> 0x1f,0)) {
    if ((bool)(((byte)((uint)((int)in_SRR1 << 0x10) >> 0x18) & 0x40) >> 6)) {
      iVar6 = (*(uint *)(in_spr130 + 0x58) & 2) * 8;
      if (*(QWORD *)(&0x10330 + iVar6) != 0) {
        uVar4 = (uint)(*(QWORD *)(&0x10338 + iVar6) >> (in_SRR0 >> 0x1b & 0x1e) + 0x20) & 3
        ;
        uVar5 = (uint)*(QWORD *)(&0x10330 + iVar6);
        if (uVar4 < 2) {
          uVar1 = *(ushort *)((in_SRR0 & 0xff800000) >> 0x16 | uVar5 & 0xfffffc01);
          if (uVar1 == 0) goto LAB_00001634;
          iVar6 = *(int *)((uint)uVar1 << 0xd | (in_SRR0 & 0x7ff000) >> 10);
        }
        else {
          if (uVar4 < 3) {
            uVar1 = *(ushort *)(((in_SRR0 & 0xf8000000) >> 0x1a | uVar5 & 0xffffffc1) + 0x800);
            if (uVar1 == 0) goto LAB_00001634;
            iVar6 = *(int *)((uint)uVar1 << 0xd | (in_SRR0 & 0x7ff0000) >> 0xe);
          }
          else {
            iVar6 = *(int *)(((in_SRR0 & 0xff000000) >> 0x16 | uVar5 & 0xfffffc03) + 0x400);
          }
        }
        if (iVar6 != 0) goto LAB_00001188;
      }
    }
    else {
      if (in_SRR0 >> 0x1c == 8) {
        if (7 < (*(uint *)((in_SRR0 >> 0xe & 0x7ffc) + 0x1f50000) & 0xf)) goto LAB_00001188;
      }
      else {
        if (((in_SRR0 >> 0x1c == 9) &&
            (7 < (*(uint *)((in_SRR0 >> 0xe & 0x7ffc) + 0x1f50000) & 0xf))) &&
           ((*(byte *)(in_SRR0 >> 0xd & 0xffff | 0x1f50000) >> (QWORD)(in_SRR0 >> 10 & 4) & 0xf)
            != 0)) {
LAB_00001188:
          uVar5 = (uint)in_spr131 >> 7 & 0x40;
          uVar7 = (QWORD)(((uint)in_spr131 & 0x1000) << 1) |
                  (QWORD)uVar5 | in_spr131 & 0xffffffffffffdfbf;
          puVar3 = (QWORD *)uVar7;
          *puVar3 = uVar7;
          sync(1);
          if (*(QWORD *)((uint)puVar3 ^ 0x40) != 0) {
            if (uVar5 == 0) {
              do {
              } while (puVar3[8] != 0);
            }
            else {
              do {
                *puVar3 = 0;
                sync(1);
                do {
                } while (puVar3[-8] != 0);
                *puVar3 = uVar7;
                sync(1);
              } while (puVar3[-8] != 0);
            }
          }
          *puVar3 = 0;
          returnFromInterrupt();
          return *(undefined8 *)(in_spr130 + 0x40);
        }
      }
    }
  }
LAB_00001634:
  *(uint *)(in_spr130 + 100) = (uint)in_cr0 & 0xf;
  *(uint *)(in_spr130 + 0x60) = in_SRR0;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(QWORD *)(in_spr130 + 0x28) =
       (QWORD)
       ((uint)*(byte *)(in_spr130 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | (QWORD)in_SRR0;
  if ((bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    *(undefined8 *)(in_spr130 + 0x50) = *(undefined8 *)(in_spr130 + 0x50);
    *(undefined8 *)(in_spr130 + 0x40) = *(undefined8 *)(in_spr130 + 0x40);
    iVar6 = 0;
    slbInvalidateAll();
    do {
      puVar2 = (ushort *)(iVar6 + 0x8e0);
      iVar6 = iVar6 + 2;
      slbMoveToEntry();
    } while (*puVar2 >> 0xc != 0xf);
    returnFromInterrupt();
    return *(undefined8 *)(in_spr130 + 0x40);
  }
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}



undefined8 FUN_00000464(void)

{
  return 0x300001a3680;
}



void _v_INSTRUCTION_SEGMENT(void)

{
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void CopyBy64(int param_1,undefined8 *param_2,QWORD param_3)

{
  param_1 = param_1 - (int)param_2;
  do {
    *(undefined8 *)(param_1 + (int)param_2) = *param_2;
    param_2 = param_2 + 1;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  return;
}



void Sleep(QWORD param_1)

{
  do {
  } while ((param_1 & 0xffffffff) * 0x32 != 0);
  return;
}



QWORD FUN_000004cc(void)

{
  QWORD in_LR;
  
  return in_LR & 0xffffffffffff0000;
}



void HvpGetTimebase(void)

{
  int in_TBLr;
  
  do {
  } while (in_TBLr == 0);
  return;
}



void FUN_000004e8(int param_1,QWORD param_2,QWORD *param_3)

{
  QWORD uVar1;
  
  uVar1 = ((QWORD)(uint)(param_1 << 0x10) | param_2 & 0xffffffff0000ffff) << 0x20 |
          (QWORD)(uint)(param_1 << 0x10) | param_2 & 0xffff;
  *param_3 = uVar1;
  param_3[1] = uVar1;
  return;
}



undefined8 _v_EXTERNAL(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ushort *puVar1;
  int iVar2;
  undefined8 in_r13;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  QWORD in_SRR0;
  QWORD in_SRR1;
  int in_spr130;
  
  *(QWORD *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((QWORD)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(QWORD *)(in_spr130 + 0x28) =
       (QWORD)
       ((uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14 |
        (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
        (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 | in_SRR1 & 0xffffffff;
  if (!(bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    returnFromInterrupt();
    return param_1;
  }
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  iVar2 = 0;
  slbInvalidateAll();
  do {
    puVar1 = (ushort *)(iVar2 + 0x8e0);
    iVar2 = iVar2 + 2;
    slbMoveToEntry();
  } while (*puVar1 >> 0xc != 0xf);
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}



QWORD FUN_0000057c(uint param_1)

{
  if (1 < (param_1 >> 0x1c) - 8) {
    return 0;
  }
  return (QWORD)(param_1 >> 0xe & 0x7ffc) | 0x6801f50000;
}



undefined8 FUN_000005a8(void)

{
  return 0x6801f58000;
}



undefined8 FUN_000005c0(void)

{
  return 0x6a01f6c000;
}



undefined8 _v_ALIGNMENT(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ushort *puVar1;
  int iVar2;
  undefined8 in_r13;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  undefined4 in_DSISR;
  undefined4 in_DAR;
  QWORD in_SRR0;
  QWORD in_SRR1;
  int in_spr130;
  
  *(QWORD *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((QWORD)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(QWORD *)(in_spr130 + 0x28) =
       (QWORD)
       ((uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14 |
        (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
        (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 | in_SRR1 & 0xffffffff;
  *(undefined4 *)(in_spr130 + 0x60) = in_DAR;
  *(undefined4 *)(in_spr130 + 100) = in_DSISR;
  if (!(bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    returnFromInterrupt();
    return param_1;
  }
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  iVar2 = 0;
  slbInvalidateAll();
  do {
    puVar1 = (ushort *)(iVar2 + 0x8e0);
    iVar2 = iVar2 + 2;
    slbMoveToEntry();
  } while (*puVar1 >> 0xc != 0xf);
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}



undefined8 HvpGetFlashBase(void)

{
  return 0x80000200c8000000;
}



int HvpGetSocMMIORegs(int param_1)

{
  return (int)&WORD_00000000 + param_1;
}



QWORD HvpBuildPciConfigRegs(QWORD param_1)

{
  return param_1 + -0x7ffffdff30000000;
}



QWORD HvpGetHostBridgeRegs(QWORD param_1)

{
  return param_1 + -0x7ffffdff20000000;
}



undefined8 _v_PROGRAM(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ushort *puVar1;
  int iVar2;
  undefined8 in_r13;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  QWORD in_SRR0;
  QWORD in_SRR1;
  int in_spr130;
  
  *(QWORD *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((QWORD)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(QWORD *)(in_spr130 + 0x28) =
       (QWORD)
       ((uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14 |
        (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
        (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 | in_SRR1 & 0xffffffff;
  if (!(bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    returnFromInterrupt();
    return param_1;
  }
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  iVar2 = 0;
  slbInvalidateAll();
  do {
    puVar1 = (ushort *)(iVar2 + 0x8e0);
    iVar2 = iVar2 + 2;
    slbMoveToEntry();
  } while (*puVar1 >> 0xc != 0xf);
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}



void jt1_jumper(void)

{
  int in_r11;
  
                    // WARNING: Could not recover jumptable at 0x000007d4. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)((int)&PTR_FUN_0000ae80 + in_r11))();
  return;
}



undefined8 _v_FPU_UNAVAILABLE(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ushort *puVar1;
  int iVar2;
  undefined8 in_r13;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  QWORD in_SRR0;
  QWORD in_SRR1;
  int in_spr130;
  qword pre_back_chain;
  qword back_chain;
  
  *(QWORD *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  if ((QWORD)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  if ((*(uint *)(in_spr130 + 4) & 0x2000) != 0) {
    returnFromInterrupt();
    return param_1;
  }
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  *(QWORD *)(in_spr130 + 0x28) =
       (QWORD)
       ((uint)in_cr0 << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14 |
        (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
        (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 | in_SRR1 & 0xffffffff;
  if (!(bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    returnFromInterrupt();
    return param_1;
  }
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  iVar2 = 0;
  slbInvalidateAll();
  do {
    puVar1 = (ushort *)(iVar2 + 0x8e0);
    iVar2 = iVar2 + 2;
    slbMoveToEntry();
  } while (*puVar1 >> 0xc != 0xf);
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}



undefined8 _v_SYSTEM_CALL(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  code *pcVar1;
  uint uVar2;
  ushort *puVar3;
  uint uVar4;
  QWORD in_r0;
  undefined8 uVar5;
  undefined8 in_r2;
  int iVar6;
  undefined8 *puVar7;
  undefined8 in_r13;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  QWORD in_SRR0;
  QWORD in_SRR1;
  int in_spr130;
  int in_spr131;
  
  *(QWORD *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  uVar2 = (uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14
          | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc |
          (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf);
  if (-1 < (QWORD)in_SRR1) {
    if ((bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
      *(QWORD *)(in_spr130 + 0x28) = (QWORD)uVar2 << 0x20 | in_SRR1 & 0xffffffff;
      *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
      *(undefined8 *)(in_spr130 + 0x30) = in_r13;
      if (in_r0 < 2) {
        uVar2 = *(uint *)(in_spr130 + 0x58);
        uVar4 = (uint)in_r0 & 1;
        *(uint *)(in_spr130 + 0x58) = uVar4 | uVar2 & 0xfffffffe;
        slbInvalidateAll();
        puVar7 = (undefined8 *)(&0x10130 + (uVar4 | uVar2 & 2) * 0x80);
        do {
          uVar5 = *puVar7;
          puVar7 = puVar7 + 1;
          slbMoveToEntry();
        } while (((uint)uVar5 >> 0xc & 0xf) != 0xf);
        returnFromInterrupt();
        return param_1;
      }
      *(undefined8 *)(in_spr130 + 0x50) = param_3;
      *(undefined8 *)(in_spr130 + 0x40) = param_1;
      iVar6 = 0;
      slbInvalidateAll();
      do {
        puVar3 = (ushort *)(iVar6 + 0x8e0);
        iVar6 = iVar6 + 2;
        slbMoveToEntry();
      } while (*puVar3 >> 0xc != 0xf);
      returnFromInterrupt();
      return *(undefined8 *)(in_spr130 + 0x40);
    }
    if ((undefined *)register0x0000000c == (undefined *)0x0) {
      if ((bool)(((byte)(*(uint *)(in_spr130 + 0x2c) >> 0xc) & 0xf) >> 2 & 1)) {
        *(undefined8 *)(in_spr130 + 0x50) = param_3;
        slbInvalidateAll();
        puVar7 = (undefined8 *)(&0x10130 + (*(uint *)(in_spr130 + 0x58) & 3) * 0x80);
        do {
          uVar5 = *puVar7;
          puVar7 = puVar7 + 1;
          slbMoveToEntry();
        } while (((uint)uVar5 >> 0xc & 0xf) != 0xf);
      }
      returnFromInterrupt();
      return param_1;
    }
    if (0x77 < (in_r0 & 0xffffffff)) {
      *(QWORD *)(in_spr130 + 0x28) = (QWORD)uVar2 << 0x20 | in_SRR1 & 0xffffffff;
      *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
      returnFromInterrupt();
      return param_1;
    }
    *(QWORD *)(in_spr130 + 0x28) = (QWORD)uVar2;
    *(QWORD *)(in_spr130 + 0x20) = in_LR;
    pcVar1 = (code *)(&_SyscallTable)[(uint)in_r0];
    if (pcVar1 < &0x10000) {
      uVar5 = *(undefined8 *)(in_spr130 + 0x48);
      *(undefined8 *)(in_spr131 + 0x1ef8) = in_r2;
      uVar5 = (*pcVar1)(param_1,uVar5);
      returnFromInterrupt();
      return uVar5;
    }
  }
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



undefined8 HvxSetTimeBaseToZero(void)

{
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void HvxStartupProcessors(void)

{
  int in_PIR;
  
  if (in_PIR != 0) {
    _0x1fff0 = 0;
    _0x1fff8 = 0;
    return;
  }
                    // WARNING: Read-only address (ram,0x0001fff8) is written
                    // WARNING: Read-only address (ram,0x0001fff0) is written
  sync(0);
  eieioOp();
  eieioOp();
  eieioOp();
  eieioOp();
  eieioOp();
  eieioOp();
  eieioOp();
  _0x1fff0 = 0x3fffc0003fffc00;
  _0x1fff8 = 0x3fffc0003fffc00;
  uRam00050010 = 0x140078;
  uRam00052000 = 4;
  uRam00052008 = 0;
  uRam00052070 = 0x7c;
  uRam00054000 = 0x10;
  uRam00054008 = 0;
  uRam00054070 = 0x7c;
  return;
}



undefined8 _v_TRACE(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ushort *puVar1;
  int iVar2;
  undefined8 in_r13;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  QWORD in_SRR0;
  QWORD in_SRR1;
  int in_spr130;
  
  *(QWORD *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((QWORD)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(QWORD *)(in_spr130 + 0x28) =
       (QWORD)
       ((uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14 |
        (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
        (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 | in_SRR1 & 0xffffffff;
  if (!(bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    returnFromInterrupt();
    return param_1;
  }
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  iVar2 = 0;
  slbInvalidateAll();
  do {
    puVar1 = (ushort *)(iVar2 + 0x8e0);
    iVar2 = iVar2 + 2;
    slbMoveToEntry();
  } while (*puVar1 >> 0xc != 0xf);
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}



QWORD HvpInvalidateCachelines(QWORD param_1,int param_2)

{
  QWORD uVar1;
  QWORD lVar2;
  
  if (param_2 == 0) {
    return param_1;
  }
  lVar2 = (QWORD)
          ((((uint)param_1 + param_2) - 1 & 0xffffff80) - ((uint)param_1 & 0xffffff80) >> 7) + 1;
  uVar1 = param_1 & 0x7fffffffffffff80 | 0x8000000000000000;
  do {
    dataCacheBlockFlush(uVar1);
    instructionCacheBlockInvalidate(uVar1);
    uVar1 = uVar1 + 0x80;
    lVar2 = lVar2 + -1;
  } while (lVar2 != 0);
  sync(0);
  instructionSynchronize();
  return uVar1;
}



QWORD FUN_00000dc8(QWORD param_1,int param_2)

{
  QWORD uVar1;
  QWORD lVar2;
  
  if (param_2 == 0) {
    return param_1;
  }
  lVar2 = (QWORD)
          ((((uint)param_1 + param_2) - 1 & 0xffffff80) - ((uint)param_1 & 0xffffff80) >> 7) + 1;
  uVar1 = param_1 & 0x7fffffffffffff80 | 0x8000000000000000;
  do {
    dataCacheBlockStore(uVar1);
    instructionCacheBlockInvalidate(uVar1);
    uVar1 = uVar1 + 0x80;
    lVar2 = lVar2 + -1;
  } while (lVar2 != 0);
  sync(0);
  instructionSynchronize();
  return uVar1;
}



void HvpRelocateCacheLines(undefined8 param_1,QWORD param_2,QWORD param_3)

{
  undefined8 in_r0;
  QWORD lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  QWORD lVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  QWORD lVar20;
  
  lVar1 = __Save_R12_16_thru_31();
  lVar4 = 0;
  lVar20 = param_3;
  do {
    dataCacheBlockStore(lVar1 + lVar4);
    lVar4 = lVar4 + 0x80;
    lVar20 = lVar20 + -1;
  } while (lVar20 != 0);
  sync(0);
  instructionSynchronize();
  do {
    puVar2 = (undefined8 *)lVar1;
    uVar5 = puVar2[1];
    uVar6 = puVar2[2];
    uVar7 = puVar2[3];
    uVar8 = puVar2[4];
    uVar9 = puVar2[5];
    uVar10 = puVar2[6];
    uVar11 = puVar2[7];
    uVar12 = puVar2[8];
    uVar13 = puVar2[9];
    uVar14 = puVar2[10];
    uVar15 = puVar2[0xb];
    uVar16 = puVar2[0xc];
    uVar17 = puVar2[0xd];
    uVar18 = puVar2[0xe];
    uVar19 = puVar2[0xf];
    dataCacheBlockFlush(lVar1);
    instructionCacheBlockInvalidate(lVar1);
    lVar1 = lVar1 + 0x80;
    DataCaseBlockSetToZero(in_r0,param_2);
    puVar3 = (undefined8 *)param_2;
    *puVar3 = *puVar2;
    puVar3[1] = uVar5;
    puVar3[2] = uVar6;
    puVar3[3] = uVar7;
    puVar3[4] = uVar8;
    puVar3[5] = uVar9;
    puVar3[6] = uVar10;
    puVar3[7] = uVar11;
    puVar3[8] = uVar12;
    puVar3[9] = uVar13;
    puVar3[10] = uVar14;
    puVar3[0xb] = uVar15;
    puVar3[0xc] = uVar16;
    puVar3[0xd] = uVar17;
    puVar3[0xe] = uVar18;
    puVar3[0xf] = uVar19;
    instructionCacheBlockInvalidate(param_2);
    param_2 = param_2 + 0x80;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  sync(0);
  instructionSynchronize();
  return;
}


void HvpSaveCachelines(QWORD param_1,QWORD param_2) {
  do {
    *(undefined *)param_1 = *(undefined *)param_1;
    dataCacheBlockStore(param_1);
    param_1 = param_1 + 0x80;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  sync(0);
  instructionSynchronize();
  return;
}

VOID HvpSaveCachelines(PQWORD Address, DWORD BlockSize) {
    while (BlockSize != NULL)
    {
        QWORD _Address = *(PQWORD)Address;
        __dcbst(_Address, NULL);
        _Address += 0x80;
        BlockSize += -0x01;
    }

    __sync();
    __isync();

    return;
}

undefined8 _v_VPU_UNAVAILABLE(undefined8 param_1,undefined8 param_2,undefined8 param_3){
  ushort *puVar1;
  int iVar2;
  undefined8 in_r13;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  QWORD in_SRR0;
  QWORD in_SRR1;
  int in_spr130;
  
  *(QWORD *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  if ((QWORD)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  if ((*(uint *)(in_spr130 + 4) & 0x2000000) != 0) {
    returnFromInterrupt();
    return param_1;
  }
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  *(QWORD *)(in_spr130 + 0x28) =
       (QWORD)
       ((uint)in_cr0 << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14 |
        (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
        (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 | in_SRR1 & 0xffffffff;
  if (!(bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    returnFromInterrupt();
    return param_1;
  }
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  iVar2 = 0;
  slbInvalidateAll();
  do {
    puVar1 = (ushort *)(iVar2 + 0x8e0);
    iVar2 = iVar2 + 2;
    slbMoveToEntry();
  } while (*puVar1 >> 0xc != 0xf);
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}



QWORD FUN_00000fd4(void) {
  undefined8 in_r0;
  QWORD lVar1;
  QWORD lVar2;
  
  lVar1 = -0x7ffffffffe090000;
  lVar2 = 0x200;
  do {
    DataCaseBlockSetToZero(in_r0,lVar1);
    lVar1 = lVar1 + 0x80;
    lVar2 = lVar2 + -1;
  } while (lVar2 != 0);
  lVar1 = -0x7ffffffffe080000;
  lVar2 = 0x1000;
  do {
    DataCaseBlockSetToZero(in_r0,lVar1);
    lVar1 = lVar1 + 0x80;
    lVar2 = lVar2 + -1;
  } while (lVar2 != 0);
  return lVar1;
}

undefined8 FUN_00001070(uint param_1) {
  uint uVar1;
  ushort *puVar2;
  QWORD *puVar3;
  int iVar4;
  uint in_r13;
  QWORD uVar5;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  undefined4 in_DSISR;
  uint in_SRR0;
  QWORD in_SRR1;
  undefined8 in_SPRG0;
  int in_spr130;
  QWORD in_spr131;
  dword back_chain;
  
  uVar1 = *(uint *)(param_1 >> 0x14 & 0xffc | (in_r13 & 0xffff0000) + 0x10000);
  if (((uVar1 & 1) != 0) && ((*(uint *)((param_1 >> 10 & 0xffc) + (uVar1 & 0x1ffff000)) & 1) != 0))
  {
    uVar1 = (uint)in_spr131 >> 7 & 0x40;
    uVar5 = (QWORD)(((uint)in_spr131 & 0x1000) << 1) |
            (QWORD)uVar1 | in_spr131 & 0xffffffffffffdfbf;
    puVar3 = (QWORD *)uVar5;
    *puVar3 = uVar5;
    sync(1);
    if (*(QWORD *)((uint)puVar3 ^ 0x40) != 0) {
      if (uVar1 == 0) {
        do {
        } while (puVar3[8] != 0);
      }
      else {
        do {
          *puVar3 = 0;
          sync(1);
          do {
          } while (puVar3[-8] != 0);
          *puVar3 = uVar5;
          sync(1);
        } while (puVar3[-8] != 0);
      }
    }
    *puVar3 = 0;
    returnFromInterrupt();
    return *(undefined8 *)(in_spr130 + 0x40);
  }
  if (in_SRR0 == 0x80075f90) {
    returnFromInterrupt();
    return *(undefined8 *)(in_r13 + 0x40);
  }
  *(undefined4 *)(in_r13 + 100) = in_DSISR;
  *(uint *)(in_r13 + 0x60) = param_1;
  *(undefined8 *)(in_r13 + 0x30) = in_SPRG0;
  *(QWORD *)(in_r13 + 0x28) =
       (QWORD)
       ((uint)*(byte *)(in_r13 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(QWORD *)(in_r13 + 0x20) = in_LR << 0x20 | (QWORD)in_SRR0;
  if ((bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    *(undefined8 *)(in_r13 + 0x50) = *(undefined8 *)(in_r13 + 0x50);
    *(undefined8 *)(in_r13 + 0x40) = *(undefined8 *)(in_r13 + 0x40);
    iVar4 = 0;
    slbInvalidateAll();
    do {
      puVar2 = (ushort *)(iVar4 + 0x8e0);
      iVar4 = iVar4 + 2;
      slbMoveToEntry();
    } while (*puVar2 >> 0xc != 0xf);
    returnFromInterrupt();
    return *(undefined8 *)(in_r13 + 0x40);
  }
  returnFromInterrupt();
  return *(undefined8 *)(in_r13 + 0x40);
}

undefined8 FUN_00001124(int param_1) {
  ushort *puVar1;
  QWORD *puVar2;
  uint uVar3;
  int iVar4;
  int in_r13;
  QWORD uVar5;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  undefined4 in_DSISR;
  QWORD in_SRR0;
  QWORD in_SRR1;
  undefined8 in_SPRG0;
  int in_spr130;
  QWORD in_spr131;
  
  if ((*(uint *)((param_1 + 0x1000U >> 10 & 0x7fffc) + 0x1f80000) & 3) == 3) {
    uVar3 = (uint)in_spr131 >> 7 & 0x40;
    uVar5 = (QWORD)(((uint)in_spr131 & 0x1000) << 1) |
            (QWORD)uVar3 | in_spr131 & 0xffffffffffffdfbf;
    puVar2 = (QWORD *)uVar5;
    *puVar2 = uVar5;
    sync(1);
    if (*(QWORD *)((uint)puVar2 ^ 0x40) != 0) {
      if (uVar3 == 0) {
        do {
        } while (puVar2[8] != 0);
      }
      else {
        do {
          *puVar2 = 0;
          sync(1);
          do {
          } while (puVar2[-8] != 0);
          *puVar2 = uVar5;
          sync(1);
        } while (puVar2[-8] != 0);
      }
    }
    *puVar2 = 0;
    returnFromInterrupt();
    return *(undefined8 *)(in_spr130 + 0x40);
  }
  *(undefined4 *)(in_r13 + 100) = in_DSISR;
  *(int *)(in_r13 + 0x60) = param_1;
  *(undefined8 *)(in_r13 + 0x30) = in_SPRG0;
  *(QWORD *)(in_r13 + 0x28) =
       (QWORD)
       ((uint)*(byte *)(in_r13 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(QWORD *)(in_r13 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    *(undefined8 *)(in_r13 + 0x50) = *(undefined8 *)(in_r13 + 0x50);
    *(undefined8 *)(in_r13 + 0x40) = *(undefined8 *)(in_r13 + 0x40);
    iVar4 = 0;
    slbInvalidateAll();
    do {
      puVar1 = (ushort *)(iVar4 + 0x8e0);
      iVar4 = iVar4 + 2;
      slbMoveToEntry();
    } while (*puVar1 >> 0xc != 0xf);
    returnFromInterrupt();
    return *(undefined8 *)(in_r13 + 0x40);
  }
  returnFromInterrupt();
  return *(undefined8 *)(in_r13 + 0x40);
}



undefined8 FUN_00001160(void) {
  QWORD *puVar1;
  uint uVar2;
  QWORD uVar3;
  int in_spr130;
  QWORD in_spr131;
  
  uVar2 = (uint)in_spr131 >> 7 & 0x40;
  uVar3 = (QWORD)(((uint)in_spr131 & 0x1000) << 1) |
          (QWORD)uVar2 | in_spr131 & 0xffffffffffffdfbf;
  puVar1 = (QWORD *)uVar3;
  *puVar1 = uVar3;
  sync(1);
  if (*(QWORD *)((uint)puVar1 ^ 0x40) != 0) {
    if (uVar2 == 0) {
      do {
      } while (puVar1[8] != 0);
    }
    else {
      do {
        *puVar1 = 0;
        sync(1);
        do {
        } while (puVar1[-8] != 0);
        *puVar1 = uVar3;
        sync(1);
      } while (puVar1[-8] != 0);
    }
  }
  *puVar1 = 0;
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}



undefined8 FUN_00001248(uint param_1)

{
  ushort *puVar1;
  QWORD *puVar2;
  uint uVar3;
  int iVar4;
  QWORD uVar5;
  int in_r13;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  undefined4 in_DSISR;
  uint in_SRR0;
  QWORD in_SRR1;
  undefined8 in_SPRG0;
  int in_spr130;
  QWORD in_spr131;
  
  uVar3 = param_1 >> 0xe & 0xfffc;
  if ((uVar3 == 0xfffc) || ((*(uint *)(uVar3 + 0x1f70000) & 1) != 0)) {
    uVar3 = (uint)in_spr131 >> 7 & 0x40;
    uVar5 = (QWORD)(((uint)in_spr131 & 0x1000) << 1) |
            (QWORD)uVar3 | in_spr131 & 0xffffffffffffdfbf;
    puVar2 = (QWORD *)uVar5;
    *puVar2 = uVar5;
    sync(1);
    if (*(QWORD *)((uint)puVar2 ^ 0x40) != 0) {
      if (uVar3 == 0) {
        do {
        } while (puVar2[8] != 0);
      }
      else {
        do {
          *puVar2 = 0;
          sync(1);
          do {
          } while (puVar2[-8] != 0);
          *puVar2 = uVar5;
          sync(1);
        } while (puVar2[-8] != 0);
      }
    }
    *puVar2 = 0;
    returnFromInterrupt();
    return *(undefined8 *)(in_spr130 + 0x40);
  }
  if (in_SRR0 == 0x80075f90) {
    returnFromInterrupt();
    return *(undefined8 *)(in_r13 + 0x40);
  }
  *(undefined4 *)(in_r13 + 100) = in_DSISR;
  *(uint *)(in_r13 + 0x60) = param_1;
  *(undefined8 *)(in_r13 + 0x30) = in_SPRG0;
  *(QWORD *)(in_r13 + 0x28) =
       (QWORD)
       ((uint)*(byte *)(in_r13 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(QWORD *)(in_r13 + 0x20) = in_LR << 0x20 | (QWORD)in_SRR0;
  if ((bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    *(undefined8 *)(in_r13 + 0x50) = *(undefined8 *)(in_r13 + 0x50);
    *(undefined8 *)(in_r13 + 0x40) = *(undefined8 *)(in_r13 + 0x40);
    iVar4 = 0;
    slbInvalidateAll();
    do {
      puVar1 = (ushort *)(iVar4 + 0x8e0);
      iVar4 = iVar4 + 2;
      slbMoveToEntry();
    } while (*puVar1 >> 0xc != 0xf);
    returnFromInterrupt();
    return *(undefined8 *)(in_r13 + 0x40);
  }
  returnFromInterrupt();
  return *(undefined8 *)(in_r13 + 0x40);
}



undefined8 FUN_000012a8(void)

{
  QWORD *puVar1;
  uint uVar2;
  QWORD uVar3;
  int in_spr130;
  QWORD in_spr131;
  
  uVar2 = (uint)in_spr131 >> 7 & 0x40;
  uVar3 = (QWORD)(((uint)in_spr131 & 0x1000) << 1) |
          (QWORD)uVar2 | in_spr131 & 0xffffffffffffdfbf;
  puVar1 = (QWORD *)uVar3;
  *puVar1 = uVar3;
  sync(1);
  if (*(QWORD *)((uint)puVar1 ^ 0x40) != 0) {
    if (uVar2 == 0) {
      do {
      } while (puVar1[8] != 0);
    }
    else {
      do {
        *puVar1 = 0;
        sync(1);
        do {
        } while (puVar1[-8] != 0);
        *puVar1 = uVar3;
        sync(1);
      } while (puVar1[-8] != 0);
    }
  }
  *puVar1 = 0;
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}



undefined8 FUN_000012f0(uint param_1)

{
  ushort *puVar1;
  QWORD *puVar2;
  uint uVar3;
  int iVar4;
  QWORD uVar5;
  uint in_r13;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  undefined4 in_DSISR;
  QWORD in_SRR0;
  QWORD in_SRR1;
  undefined8 in_SPRG0;
  int in_spr130;
  QWORD in_spr131;
  
  if (((byte)(&0x11000)[(param_1 >> 0x11 & 0xfff) + (in_r13 & 0xffff0000)] >>
       (QWORD)(param_1 >> 0xe & 4) & 0xf) != 0) {
    uVar3 = (uint)in_spr131 >> 7 & 0x40;
    uVar5 = (QWORD)(((uint)in_spr131 & 0x1000) << 1) |
            (QWORD)uVar3 | in_spr131 & 0xffffffffffffdfbf;
    puVar2 = (QWORD *)uVar5;
    *puVar2 = uVar5;
    sync(1);
    if (*(QWORD *)((uint)puVar2 ^ 0x40) != 0) {
      if (uVar3 == 0) {
        do {
        } while (puVar2[8] != 0);
      }
      else {
        do {
          *puVar2 = 0;
          sync(1);
          do {
          } while (puVar2[-8] != 0);
          *puVar2 = uVar5;
          sync(1);
        } while (puVar2[-8] != 0);
      }
    }
    *puVar2 = 0;
    returnFromInterrupt();
    return *(undefined8 *)(in_spr130 + 0x40);
  }
  *(undefined4 *)(in_r13 + 100) = in_DSISR;
  *(uint *)(in_r13 + 0x60) = param_1;
  *(undefined8 *)(in_r13 + 0x30) = in_SPRG0;
  *(QWORD *)(in_r13 + 0x28) =
       (QWORD)
       ((uint)*(byte *)(in_r13 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(QWORD *)(in_r13 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    *(undefined8 *)(in_r13 + 0x50) = *(undefined8 *)(in_r13 + 0x50);
    *(undefined8 *)(in_r13 + 0x40) = *(undefined8 *)(in_r13 + 0x40);
    iVar4 = 0;
    slbInvalidateAll();
    do {
      puVar1 = (ushort *)(iVar4 + 0x8e0);
      iVar4 = iVar4 + 2;
      slbMoveToEntry();
    } while (*puVar1 >> 0xc != 0xf);
    returnFromInterrupt();
    return *(undefined8 *)(in_r13 + 0x40);
  }
  returnFromInterrupt();
  return *(undefined8 *)(in_r13 + 0x40);
}



void _v_MAINTENANCE(void)

{
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



undefined8 _v_VMX_ASSIST(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ushort *puVar1;
  int iVar2;
  undefined8 in_r13;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  QWORD in_LR;
  QWORD in_SRR0;
  QWORD in_SRR1;
  int in_spr130;
  
  *(QWORD *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(QWORD *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((QWORD)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(QWORD *)(in_spr130 + 0x28) =
       (QWORD)
       ((uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14 |
        (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
        (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 | in_SRR1 & 0xffffffff;
  if (!(bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    returnFromInterrupt();
    return param_1;
  }
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  iVar2 = 0;
  slbInvalidateAll();
  do {
    puVar1 = (ushort *)(iVar2 + 0x8e0);
    iVar2 = iVar2 + 2;
    slbMoveToEntry();
  } while (*puVar1 >> 0xc != 0xf);
  returnFromInterrupt();
  return *(undefined8 *)(in_spr130 + 0x40);
}



undefined8 FUN_0000177c(void)

{
  return 0;
}



void _v_THERMAL_MANAGEMENT(void)

{
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



QWORD HvpFlushSingleTb(QWORD param_1,uint param_2)

{
  QWORD uVar1;
  
  uVar1 = param_1 & 0xfffffffffffff000;
  param_2 = param_2 >> (QWORD)((uint)param_1 >> 0x1b & 0x1e);
  if ((param_2 & 3) == 0) {
    TLBInvalidateEntryLocal(uVar1);
  }
  else {
    uVar1 = (QWORD)((param_2 & 1) << 0xc) | param_1 & 0xffffffffffffe000;
    TLBInvalidateEntryLocal(uVar1,ZEXT48(register0x0000000c),0,0,0);
  }
  eieioOp();
  sync(2);
  return uVar1;
}



void HvxFlushEntireTb(void)

{
  QWORD lVar1;
  QWORD lVar2;
  
  lVar1 = 0xc00;
  lVar2 = 0x100;
  do {
    TLBInvalidateEntryLocal(lVar1);
    lVar1 = lVar1 + 0x1000;
    lVar2 = lVar2 + -1;
  } while (lVar2 != 0);
  eieioOp();
  sync(2);
  TLBInvalidateEntryLocal(0x3ff00000000,ZEXT48(register0x0000000c),0,0,0);
  eieioOp();
  sync(2);
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_00001b10(void)
{
  uint uVar1;
  QWORD in_r2;
  int iVar2;
  QWORD lVar3;
  int iVar4;
  dword dVar5;
  qword back_chain;
  qword local_3a0;
  dword local_394;
  word local_390;
  word local_230;
  dword local_228;
  dword local_224;
  word local_220;
  word local_210;
  dword local_110;
  dword local_10c;
  dword local_100;
  word local_30;
  dword local_1c;
  qword local_10;
  qword local_8;
  
  iVar2 = (int)in_r2;
  uVar1 = *(uint *)(iVar2 + 0x10000);
  if (((&0x16615)[iVar2] == '\0') || ((&0x16615)[iVar2] == '\x02')) {
    dVar5 = 0xffffffff;
  }
  else {
    dVar5 = 0;
    lVar3 = HvpGetFlashBase();
    CopyBy64(&local_230,lVar3 + 0x200, 0x40);
    iVar2 = (int)in_r2;
    if (((local_230 == 0xdb4b) && (local_228 == 0x120)) && (local_224 == 0x200)) {
      j_XeCryptAesKey(&local_390, 0x20);
      j_XeCryptAesCbc(&local_390,&local_110,0xe0,&local_110,&local_220,0);
      j_XeCryptHmacSha(0x20,0x10,&local_230,0x10,&local_110,0xe0,0,0);
      iVar2 = (int)in_r2;
      iVar4 = j_XeCryptBnQwBeSigVerify(&local_210,&local_30,ZEXT48(&0x10704) + in_r2,
                           ZEXT48(&0x16400) + in_r2);
      if (((iVar4 != 0) && (local_110 == 1)) && (local_10c != 0)) {
        dVar5 = local_100;
      }
    }
  }
  *(dword *)(&0x16aac + iVar2) = dVar5;
  FUN_00000204((QWORD)uVar1);
  return;
}



// WARNING: Removing unreachable block (ram,0x00001c60)

void FUN_00001c50(void)

{
  byte bVar1;
  int in_r2;
  
  bVar1 = (&0x16615)[in_r2];
  if (bVar1 == 0xff) {
    return;
  }
  if (bVar1 < 5) {
    if ((*(uint *)(&0x16aac + in_r2) & 1) != 0) {
      return;
    }
    if ((byte)(&0x105e8)[(uint)bVar1 + in_r2] <= (byte)(&0x163a0)[in_r2]) {
      return;
    }
  }
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



undefined8 HvxGetVersions(void)

{
  return 0x760000044970000;
}



void FUN_00001ce0(void)

{
  uint uVar1;
  QWORD lVar2;
  int in_r2;
  undefined8 uVar3;
  QWORD *puVar5;
  int iVar6;
  QWORD uVar4;
  undefined8 *puVar7;
  QWORD uVar8;
  uint uVar9;
  QWORD *puVar10;
  QWORD in_TBLr;
  qword back_chain;
  word local_150;
  word local_f0;
  word local_50;
  dword local_3c;
  
  uVar3 = __Save_R12_26_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  puVar5 = (QWORD *)HvpGetSocMMIORegs(0x26000);
  iVar6 = HvpGetSocMMIORegs(0x20000);
  uVar8 = 0;
  puVar7 = (undefined8 *)&local_150;
  do {
    lVar2 = uVar8 << 3;
    uVar8 = uVar8 + 0x40;
    *puVar7 = *(undefined8 *)((int)lVar2 + iVar6);
    puVar7 = puVar7 + 1;
  } while ((uVar8 & 0xffffffff) < 0x300);
  uVar8 = 0;
  puVar10 = (QWORD *)&local_f0;
  iVar6 = 0x14;
  do {
    uVar9 = 0;
    do {
      do {
      } while ((*puVar5 & 0x8000000000000000) != 0);
      uVar8 = puVar5[1] ^ uVar8;
    } while ((((uVar9 < 3) || (uVar4 = FUN_0000b450(uVar8), (uVar4 & 0xffffffff) < 0x1a)) ||
             (0x26 < (uVar4 & 0xffffffff))) && (uVar9 = uVar9 + 1, uVar9 < 100));
    iVar6 = iVar6 + -1;
    uVar4 = (QWORD)(uint)((int)uVar8 + (int)(uVar8 / 0x1d) * -0x1d) & 0x3f;
    uVar8 = (in_TBLr << uVar4 | in_TBLr >> 0x40 - uVar4) & 1 ^ uVar8;
    *puVar10 = uVar8;
    puVar10 = puVar10 + 1;
  } while (iVar6 != 0);
  j_XeCryptSha(&local_f0,0xa0,&local_150,0x60,0x18,8,&local_50,0x14);
  j_XeCryptRc4Key(uVar3,&local_50,0x14);
  FUN_00000204((QWORD)uVar1);
  return;
}



void FUN_00001e08(void)
{
  short sVar1;
  uint uVar2;
  uint uVar3;
  QWORD in_r2;
  QWORD lVar4;
  short *psVar5;
  qword back_chain;
  qword local_a0;
  word local_90;
  dword local_38;
  
  __Save_R12_27_thru_31();
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  j_XeCryptShaInit(&local_90);
  lVar4 = ZEXT48(&0x10710) + in_r2;
  while( true ) {
    psVar5 = (short *)lVar4;
    sVar1 = *psVar5;
    if ((sVar1 == 3) && (3 < *(uint *)(psVar5 + 2))) break;
    uVar3 = *(uint *)(psVar5 + 2);
    if (psVar5[1] != 0) {
      uVar3 = *(uint *)(&0x16ab8 + ((uint)(ushort)psVar5[1] - 1) * 4 + (int)in_r2) | uVar3;
    }
    if (sVar1 == 0) {
      HvpGetSocMMIORegs((QWORD)uVar3);
    }
    else {
      if (sVar1 == 1) {
        HvpGetSocMMIORegs((QWORD)uVar3);
      }
    }
    j_XeCryptShaUpdate(&local_90,&local_a0,8);
    if (sVar1 == 3) {
      j_XeCryptShaFinal(&local_90,(QWORD)uVar3 * 0x10 + ZEXT48(&0x100c0) + in_r2,0x10);
      j_XeCryptShaInit(&local_90);
    }
    lVar4 = lVar4 + 8;
  }
  FUN_00000204((QWORD)uVar2);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00001f60(void)

{
  undefined uVar1;
  undefined uVar2;
  uint uVar3;
  int in_r2;
  int iVar4;
  undefined8 uVar5;
  undefined *puVar6;
  byte *pbVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  QWORD in_PVR;
  qword back_chain;
  word local_a0;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar3 = *(uint *)(in_r2 + 0x10000);
  uVar5 = HvpGetFlashBase();
  CopyBy64(&local_a0,uVar5,0x10);
  *(QWORD *)(&0x16aa0 + in_r2) = in_PVR & 0xffffffff;
  puVar6 = (undefined *)HvpBuildPciConfigRegs(0x8000);
  if (CONCAT11(puVar6[1],*puVar6) == -0x1415) {
    *(ushort *)(&0x16a9c + in_r2) = *(ushort *)(&0x16a9c + in_r2) | 0x8000;
  }
  iVar4 = in_r2;
  puVar6 = (undefined *)HvpBuildPciConfigRegs(&0x10002);
  uVar1 = puVar6[1];
  uVar2 = *puVar6;
  pbVar7 = (byte *)HvpBuildPciConfigRegs(&0x10008);
  *(uint *)(&0x16ab0 + iVar4) = (uint)CONCAT11(uVar1,uVar2) << 0x10 | (uint)*pbVar7;
  if ((local_a0 & 0xf0) == 0x60) {
    *(ushort *)(&0x16a9c + in_r2) = *(ushort *)(&0x16a9c + in_r2) | 2;
  }
  iVar8 = HvpGetSocMMIORegs(0x1ff00);
  if (*(int *)(iVar8 + 0x20) == 0x42440302) {
    uVar10 = *(uint *)(iVar8 + 0x24);
    uVar9 = uVar10 >> 0x18 & 0xf;
    *(ushort *)(&0x16a9c + in_r2) = *(ushort *)(&0x16a9c + in_r2) | 4;
    uVar10 = uVar10 >> 0x1c;
  }
  else {
    uVar10 = 0;
    uVar9 = 1;
  }
  *(uint *)(&0x16ab8 + iVar4) = uVar10 << 0x14;
  *(uint *)(&0x16abc + iVar4) = uVar9 << 0x14;
  FUN_00001e08();
  FUN_00000204((QWORD)uVar3);
  return;
}


void FUN_000020b0(int param_1){
  int iVar1;
  QWORD in_r2;
  QWORD lVar2;
  Pbyte *puVar3;
  qword *pqVar4;
  undefined *puVar5;
  QWORD lVar6;
  QWORD lVar7;
  QWORD lVar8;
  qword back_chain;
  qword local_30;
  qword local_28;
  qword local_18;
  qword local_10;
  qword local_8;
  
  puVar3 = (byte*)HvpGetSocMMIORegs(0x24000);
  lVar7 = ZEXT48(&0x10100) + in_r2;
  lVar2 = in_r2;
  if (param_1 == 0) {
    lVar8 = 0xc;
    lVar6 = lVar7;
    do {
      *(undefined4 *)lVar6 = 0x55555555;
      lVar6 = lVar6 + 4;
      lVar8 = lVar8 + -1;
    } while (lVar8 != 0);
  }
  else {
    J_XeCryptRandom(lVar7, 0x30);
  }
  *puVar3 = *(byte*)lVar7;
  eieioOp();
  iVar1 = (int)in_r2;
  puVar3[1] = *(byte *)(&0x10108 + iVar1);
  eieioOp();
  puVar3[0x200] = *(byte*)lVar7;
  eieioOp();
  puVar3[0x201] = *(byte *)(&0x10108 + iVar1);
  eieioOp();
  puVar3[0x208] = *(byte *)(&0x10110 + iVar1);
  eieioOp();
  puVar3[0x209] = *(byte *)(&0x10118 + iVar1);
  eieioOp();
  pqVar4 = &local_30;
  in_r2 = ZEXT48(&0x10110) + in_r2;
  lVar7 = 0x10;
  do {
    puVar5 = (undefined *)in_r2;
    in_r2 = in_r2 + 1;
    *(undefined *)pqVar4 = *puVar5;
    pqVar4 = (qword *)((int)pqVar4 + 1);
    lVar7 = lVar7 + -1;
  } while (lVar7 != 0);
  j_XeCryptAesKeyExpand128(&local_30, ZEXT48(&0x105f0) + lVar2);
  puVar3[8] = local_30;
  eieioOp();
  puVar3[9] = local_28;
  eieioOp();
  puVar3[0x10] = *(byte *)(&0x10120 + iVar1);
  eieioOp();
  puVar3[0x11] = *(byte *)(&0x10128 + iVar1);
  eieioOp();
  puVar3[0x210] = *(byte *)(&0x10120 + iVar1);
  eieioOp();
  puVar3[0x211] = *(byte *)(&0x10128 + iVar1);
  eieioOp();
  instructionSynchronize();
  instructionSynchronize();
  return;
}


void FUN_00002210(void) {
  uint uVar1;
  uint uVar2;
  QWORD in_r2;
  undefined8 uVar3;
  undefined8 uVar4;
  QWORD uVar5;
  QWORD uVar6;
  uint uVar7;
  uint uVar8;
  QWORD lVar9;
  undefined8 in_spr131;
  qword back_chain;
  word local_90;
  dword local_38;
  
  __Save_R12_28_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  j_XeCryptShaInit(&local_90);
  uVar8 = 0;
  lVar9 = ZEXT48(&0x10878) + in_r2;
  do {
    uVar7 = *(int *)lVar9 + 0x7f;
    uVar6 = (QWORD)(((int *)lVar9)[1] & 0xffffff80);
    uVar2 = uVar7 & 0xffffff80;
    if (uVar2 < uVar6) {
      uVar6 = uVar6 - uVar2;
      uVar5 = uVar6 >> 7 & 0x1ffffff;
      HvpSaveCachelines((QWORD)(uVar7 >> 0x10) * 0x200010000 + ((QWORD)uVar2 & 0xffff));
      if (0x3ffff < uVar2) {
        uVar3 = _v_MACHINE_CHECK_0();
        FUN_000084a8(0,0x200);
        FUN_000084a8(&0x10000,0x200);
        FUN_000084a8(FUN_00020000,0x200);
        FUN_000084a8(&0x30000,0x200);
        FUN_000084a8(in_spr131,0x200);
        uVar4 = FUN_000002d8();
        FUN_000084a8(uVar4,0x200);
        FUN_000084a8(uVar3,0x200);
        FUN_000020b0(uVar5);
        if ((uVar5 & 0xffffffff) == 0) {
          FUN_00002210();
        }
        else {
          HvpSaveCachelines(0,0x200);
          HvpSaveCachelines(&0x10000,0x200);
          HvpSaveCachelines(FUN_00020000,0x200);
          HvpSaveCachelines(&0x30000,0x200);
          HvpSaveCachelines(in_spr131,0x200);
          uVar4 = FUN_000002d8();
          HvpSaveCachelines(uVar4,0x200);
          HvpSaveCachelines(uVar3,0x200);
        }
        return;
      }
      uVar3 = HvpGetSocMMIORegs((QWORD)(uVar2 >> 6) + 0x10000);
      j_XeCryptShaUpdate(&local_90,uVar3,uVar6 >> 6 & 0x3ffffff);
    }
    uVar8 = uVar8 + 1;
    lVar9 = lVar9 + 8;
  } while (uVar8 < 6);
  j_XeCryptShaFinal(&local_90,ZEXT48(&0x100f0) + in_r2,0x10);
  FUN_00000204((QWORD)uVar1);
  return;
}

void FUN_000022f8(undefined8 param_1,QWORD param_2){
  undefined8 uVar1;
  undefined8 in_spr131;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  FUN_000084a8(0,0x200);
  FUN_000084a8(&0x10000,0x200);
  FUN_000084a8(FUN_00020000,0x200);
  FUN_000084a8(&0x30000,0x200);
  FUN_000084a8(in_spr131,0x200);
  uVar1 = FUN_000002d8();
  FUN_000084a8(uVar1,0x200);
  FUN_000084a8(param_1,0x200);
  FUN_000020b0(param_2);
  if ((param_2 & 0xffffffff) == 0) {
    FUN_00002210();
  }
  else {
    HvpSaveCachelines(0,0x200);
    HvpSaveCachelines(&0x10000,0x200);
    HvpSaveCachelines(FUN_00020000,0x200);
    HvpSaveCachelines(&0x30000,0x200);
    HvpSaveCachelines(in_spr131,0x200);
    uVar1 = FUN_000002d8();
    HvpSaveCachelines(uVar1,0x200);
    HvpSaveCachelines(param_1,0x200);
  }
  return;
}


void ComputeRSAOutput(PBYTE Key, PBYTE clientSession, PBYTE buffer)
{
	BYTE RsaFinal[0x80];
	BYTE RsaData[0x80]; 
	BYTE shaSalt[0x14]	= { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, clientSession[04], clientSession[02] };
	memset(RsaFinal, 0x00, 0x80); 

	HvSetupMemEncryptionKey(Key, shaSalt, RsaData);
	RSAEncryptSignature(RsaData, RsaFinal);
	memcpy(buffer, RsaFinal, 0x80);
}

void RSAEncryptSignature(PBYTE Input, PBYTE buffer) {
		byte signature[0x80];
		memcpy(signature, Input, 0x80);

		ReverseData(signature, 0x80);
		XeCryptBnQw_SwapDwQwLeBe((const u64*)signature, (u64*)signature, 0x10);
		if (XeCryptBnQwNeRsaPubCrypt((const u64*)signature, (u64*)signature, (XeRsaKey*)ChalKey)) {
			XeCryptBnQw_SwapDwQwLeBe((const u64*)signature, (u64*)signature, 0x10);
			memcpy(buffer, signature, 0x80);
		}else{
			printf("XeCryptBnQwNeRsaPubCrypt FAILED!\n");
			memset(buffer, 0x0, 0x80);
		}
	}

	
void ComputeRSAOutput(void) {
  uint uVar1;
  QWORD in_r2;
  int iVar2;
  QWORD lVar3;
  qword back_chain;
  word local_c0;
  word local_a0;
  dword local_20;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  J_XeCryptRandom(&local_c0, 0x14);
  iVar2 = j_HvSetupMemEncryptionKey(ZEXT48(&0x10100) + in_r2, 0x30, &local_a0, 0x80, 0, &local_c0);
  if (iVar2 != 0) {
    FUN_0000b498(&local_a0, 0x80);
    j_XeCryptBnQw_SwapDwQwLeBe(&local_a0,&local_a0,0x10);
    lVar3 = ZEXT48(&0x10040) + in_r2;
    iVar2 = j_XeCryptBnQwNeRsaPubCrypt(&local_a0,lVar3,ZEXT48(&0x104b8) + in_r2);
    if (iVar2 == 0) {
      memset(lVar3,0,0x80);
    }
    else {
      j_XeCryptBnQw_SwapDwQwLeBe(lVar3,lVar3,0x10);
    }
  }
  FUN_00000204((QWORD)uVar1);
  return;
}

undefined8 HvxFlushSingleTb(QWORD param_1){
  qword back_chain;
  qword local_8;
  
  HvpFlushSingleTb(param_1 & 0xffffffff,0xfa2aa00);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 HvxPostOutput(QWORD param_1) {
  int iVar1;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  iVar1 = HvpGetSocMMIORegs(0x61000);
  *(QWORD *)(iVar1 + 0x10) = param_1 << 0x38;
  eieioOp();
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x000025fc)
// WARNING: Removing unreachable block (ram,0x0000260c)
// WARNING: Removing unreachable block (ram,0x0000261c)
// WARNING: Removing unreachable block (ram,0x0000262c)
// WARNING: Removing unreachable block (ram,0x0000263c)
// WARNING: Removing unreachable block (ram,0x0000264c)
// WARNING: Removing unreachable block (ram,0x0000265c)
// WARNING: Removing unreachable block (ram,0x0000266c)
// WARNING: Removing unreachable block (ram,0x0000267c)
// WARNING: Removing unreachable block (ram,0x0000268c)

undefined8 HvxGetSocRegister(uint param_1)

{
  int in_r2;
  undefined8 *puVar2;
  undefined8 uVar1;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  if ((((param_1 & 7) == 0) &&
      ((*(QWORD *)(&0x16aa0 + in_r2) < 0x710700 || (0xffff < param_1 - 0x40000)))) &&
     ((param_1 == 0x61198 || (param_1 == 0x61190)))) {
    puVar2 = (undefined8 *)HvpGetSocMMIORegs((QWORD)param_1);
    uVar1 = *puVar2;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00002730)
// WARNING: Removing unreachable block (ram,0x00002740)
// WARNING: Removing unreachable block (ram,0x00002750)
// WARNING: Removing unreachable block (ram,0x00002760)
// WARNING: Removing unreachable block (ram,0x00002770)
// WARNING: Removing unreachable block (ram,0x00002780)
// WARNING: Removing unreachable block (ram,0x000027a8)
// WARNING: Removing unreachable block (ram,0x000027ac)
// WARNING: Removing unreachable block (ram,0x000027b4)

undefined8 HvxSetSocRegister(uint param_1,undefined8 param_2)

{
  int in_r2;
  undefined8 *puVar1;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (((param_1 & 7) == 0) &&
     (((*(QWORD *)(&0x16aa0 + in_r2) < 0x710700 || (0xffff < param_1 - 0x40000)) &&
      (param_1 == 0x61198)))) {
    puVar1 = (undefined8 *)HvpGetSocMMIORegs(0x61198);
    *puVar1 = param_2;
    eieioOp();
  }
  return 0;
}



undefined8 HvxDvdAuthBuildNVPage(void)

{
  int in_r2;
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 in_spr131;
  qword back_chain;
  
  __Save_R12_28_thru_31();
  uVar3 = 0;
  iVar1 = HvpGetSocMMIORegs(0x30000);
  iVar2 = HvpGetSocMMIORegs(0x40000);
  if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
    if ((*(QWORD *)(iVar2 + 0x3000) & 0x400000000000) != 0) {
      if (*(uint *)(&0x16ab0 + in_r2) < 0x58110012) {
        uVar3 = FUN_000004cc();
        FUN_000084a8(uVar3,0x200);
        FUN_000084a8(in_spr131,0x40);
        *(undefined8 *)(iVar2 + 0x7120) = 0x40000000000;
        eieioOp();
        do {
        } while ((*(QWORD *)(iVar2 + 0x7100) >> 0x20 & 0xf) != 0xe);
        uVar3 = 1;
      }
      *(QWORD *)(iVar2 + 0x3000) =
           *(QWORD *)(iVar2 + 0x3000) & 0xffff9bffffffffff | 0x180000000000;
      eieioOp();
      *(undefined8 *)(iVar1 + 0x3010) = 0xfffffdffffffffff;
      eieioOp();
    }
    *(QWORD *)(iVar2 + 0x3010) = ~*(QWORD *)(iVar2 + 0x3200);
    eieioOp();
    *(undefined8 *)(iVar2 + 0x3200) = 0;
    eieioOp();
  }
  *(QWORD *)(iVar1 + 0x3010) = ~*(QWORD *)(iVar1 + 0x3200);
  eieioOp();
  *(undefined8 *)(iVar1 + 0x3200) = 0;
  eieioOp();
  return uVar3;
}



undefined8 HvxDvdAuthVerifyNVPage(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, QWORD param_5)
{
  QWORD in_r2;
  QWORD uVar1;
  int iVar2;
  int iVar3;
  QWORD uVar4;
  qword back_chain;
  
  uVar1 = __Save_R12_26_thru_31();
  HvpAquireSpinLock(ZEXT48(&0x16aa8) + in_r2);
  iVar2 = 0;
  uVar4 = 0;
  iVar3 = 8;
  do {
    if ((1 << (uVar4 & 0x7f) & param_5 >> 0x38) != 0) {
      iVar2 = iVar2 + 1;
    }
    iVar3 = iVar3 + -1;
    uVar4 = uVar4 + 1;
  } while (iVar3 != 0);
  if ((iVar2 < 1) || (3 < iVar2)) {
    sync(0);
    if ((uVar1 & 0xffffffff) == 0) {
      FUN_000003e0();
    }
    else {
      FUN_000003f0(param_2,param_3,param_4);
    }
    iVar2 = HvpGetSocMMIORegs(0x60000);
    *(QWORD *)(iVar2 + 0x300) = param_5;
    eieioOp();
    sync(0);
  }
  HvpReleaseSpinLock(ZEXT48(&0x16aa8) + in_r2);
  return 0;
}

// sub_29d8
QWORD HvpPhysicalToReal(uint param_1,uint param_2)
{
  if ((param_1 - 0x40000 < 0x1ffc0000) && (param_2 <= 0x20000000 - param_1)) {
    return (QWORD)param_1 | 0x8000000000000000;
  }
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



QWORD HvpPhysicalToReal(uint param_1,uint param_2)
{
  uint in_r10;
  uint in_r11;
  
  if ((in_r10 <= (in_r11 | 0xffff)) && (param_2 <= 0x20000000 - param_1)) {
    return (QWORD)param_1 | 0x8000000000000000;
  }
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



QWORD FUN_00002a18(uint param_1,uint param_2)

{
  undefined8 uVar1;
  
  if ((param_1 + 0x80000000 < 0x20000000) && (param_2 <= 0xa0000000 - param_1)) {
                    // WARNING: Treating indirect jump as call
    uVar1 = FUN_0002afe0();
    return uVar1;
  }
  if ((param_1 - 0x40000 < 0x1ffc0000) && (param_2 <= 0x20000000 - param_1)) {
    return (QWORD)param_1 | 0x8000000000000000;
  }
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



undefined8 HvxFlushDcacheRange(uint param_1,uint param_2)
{
  uint uVar1;
  qword back_chain;
  qword local_8;
  
  if (param_1 < 0x40000) {
    uVar1 = 0x40000 - param_1;
    if (param_2 <= uVar1) {
      return 0;
    }
    param_1 = 0x40000;
    param_2 = param_2 - uVar1;
  }
  if (param_1 < 0x20000000) {
    if (0x20000000 - param_1 < param_2) {
      param_2 = 0x20000000 - param_1;
    }
    if (param_2 != 0) {
      HvpInvalidateCachelines((QWORD)param_1);
    }
  }
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00002b90)
// WARNING: Removing unreachable block (ram,0x00002ba8)

QWORD HvxZeroPage(QWORD param_1)

{
  uint uVar1;
  QWORD lVar2;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  lVar2 = 0x40000;
  if (0x3ffff < (param_1 & 0xffffffff)) {
    _v_MACHINE_CHECK_0();
  }
  uVar1 = (int)param_1 << 0xc;
  if ((((QWORD)uVar1 - lVar2 & 0xffffffff) < 0x1ffc0000) &&
     (0xfff < (0x20000000 - (QWORD)uVar1 & 0xffffffff))) {
    HvpZeroCacheLines((QWORD)uVar1 | 0x8000000000000000,0x20);
    return param_1;
  }
  _v_MACHINE_CHECK_0();
  return 0;
}



undefined8 FUN_00002bb8(void)

{
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_00002bc0(void) {
  int in_r2;
  QWORD *puVar1;
  QWORD *puVar2;
  int iVar3;
  int iVar4;
  QWORD *puVar5;
  qword back_chain;
  
  __Save_R12_28_thru_31();
  HvxPostOutput(0x59);
  puVar1 = (QWORD *)HvpGetSocMMIORegs(0x30000);
  puVar2 = (QWORD *)HvpGetSocMMIORegs(0x40000);
  iVar3 = HvpGetSocMMIORegs(0x24000);
  iVar4 = HvpGetSocMMIORegs(0x60000);
  puVar5 = (QWORD *)HvpGetSocMMIORegs(0x48000);
  if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
    puVar2[0x600] = puVar2[0x600] & 0xffff9bffffffffff | 0x180000000000;
    eieioOp();
    if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
      puVar2[0x622] = 0xffffbfffffffffff;
      eieioOp();
    }
  }
  puVar1[0x622] = 0xfffffdffffffffff;
  eieioOp();
  *(QWORD *)(iVar4 + 0x700) = *(QWORD *)(iVar4 + 0x700) | 0xe0000000000000;
  eieioOp();
  *(QWORD *)(iVar4 + 0x840) =
       *(QWORD *)(iVar4 + 0x840) & 0xffffbfffffffffff | 0x3c0000000000;
  eieioOp();
  if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
    *puVar2 = *puVar2 & 0x1ff03fffffffffff | 0x4009000000000000;
    eieioOp();
    if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
      *puVar5 = *puVar5 & 0xa1ffffffffffffff | 0x100400000000000;
      eieioOp();
    }
  }
  *puVar1 = *puVar1 | 0x4000000000000000;
  eieioOp();
  if (*(QWORD *)(&0x16aa0 + in_r2) - 0x710500U < 0x200) {
    puVar2[0xc00] = 0x1e00000000;
    eieioOp();
    instructionSynchronize();
    puVar2[0xc20] = puVar2[0xc40] | 0x8000000000000000;
    eieioOp();
    instructionSynchronize();
    puVar2[0xc00] = 0xe0000000000;
    eieioOp();
    instructionSynchronize();
  }
  _0x00018 = *(undefined8 *)(iVar3 + 0x10b8);
                    // WARNING: Read-only address (ram,0x00000018) is written
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_00002dd8(void){
  byte bVar1;
  QWORD in_r2;
  ushort *puVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  HvxPostOutput(0x5a);
  FUN_00000fd4();
  puVar5 = (uint *)FUN_000002d8();
  puVar2 = (ushort *)FUN_000005c0();
  in_r2 = ZEXT48(&0x105a8) + in_r2;
  uVar4 = 0;
  do {
    bVar1 = *(byte *)in_r2;
    if (bVar1 != 0) {
      uVar3 = (((uint)bVar1 & 0x3fc0) << 0x12 | uVar4 & 0x3fff) << 6 | (uint)bVar1 & 0x3ff0003f;
      if ((((uint)bVar1 & 0x3fc0) == 0x40) && (3 < uVar4)) {
        uVar3 = uVar3 | 0x18800000;
      }
      *puVar5 = uVar3;
      *puVar2 = *puVar2 | 0x800;
    }
    uVar4 = uVar4 + 1;
    puVar5 = puVar5 + 1;
    puVar2 = puVar2 + 1;
    in_r2 = in_r2 + 1;
  } while (uVar4 < 0x40);
  return;
}



void FUN_00002e90(void){
  uint uVar1;
  uint uVar2;
  int in_r2;
  undefined8 uVar3;
  undefined *puVar4;
  uint *puVar5;
  QWORD uVar6;
  qword back_chain;
  word local_130;
  dword local_2c;
  
  __Save_R12_28_thru_31();
  uVar6 = 0;
  uVar1 = *(uint *)(in_r2 + 0x10000);
  HvxPostOutput(0x5b);
  FUN_0000b0f0();
  FUN_00001ce0(&local_130);
  HvpSetRMCI(0);
  puVar5 = (uint *)FUN_0000057c(0xffffffff80040000);
  puVar4 = (undefined *)0x40000;
  while( true ) {
    HvpRelocateCacheLines(puVar4,((QWORD)*puVar5 & 0x3fffffffffffc0) << 10 | 0x8000000000000000,0x200);
    uVar2 = *puVar5;
    if ((uVar2 & 0xc0000000) == 0x40000000) {
      uVar6 = ((QWORD)uVar2 & 0xffffffc0) << 10 | 0x8000000000000000;
    }
    if ((uVar2 & 0x20) != 0) break;
    puVar5 = puVar5 + 1;
    puVar4 = &0x10000 + (int)puVar4;
  }
  HvpSetRMCI(1);
  FUN_000022f8(uVar6,0);
  FUN_000022f8(uVar6,1);
  HvpSetRMCI(0);
  FUN_0000b0c8(0x80060000,0);
  uVar3 = FUN_00000464();
  memcpy(uVar3,&local_130,0x102);
  uVar3 = FUN_00000270();
  HvpZeroCacheLines(uVar3,0x200);
  uVar3 = FUN_00000280();
  HvpZeroCacheLines(uVar3,0x400);
  uVar3 = FUN_00000298();
  HvpZeroCacheLines(uVar3,0x200);
  uVar3 = FUN_000002a8();
  HvpZeroCacheLines(uVar3,0x200);
  uVar3 = FUN_000002b8();
  HvpZeroCacheLines(uVar3,0x200);
  uVar3 = FUN_000002c8();
  HvpZeroCacheLines(uVar3,0x200);
  ComputeRSAOutput();
  HvpSetRMCI(1);
  FUN_00000204((QWORD)uVar1);
  return;
}

void FUN_00002ff0(void) {
  qword back_chain;
  qword local_8;
  
  HvxPostOutput(0x5c);
  FUN_0000b0c0();
  FUN_0000b0b0();
  FUN_0000b0d0();
  FUN_0000b0e8();
  FUN_0000b0f8();
  FUN_0000b110();
  FUN_00008478();
  FUN_0000b118();
  FUN_0000b128();
  FUN_0000b160();
  return;
}

void FUN_00003040(void) {
  int in_r2;
  int iVar1;
  qword back_chain;
  qword local_8;
  
  HvxPostOutput(0x5e);
  FUN_0000b150();
  if ((*(QWORD *)(&0x16aa0 + in_r2) - 0x710500U < 0x200) &&
     (0x5831000f < *(uint *)(&0x16ab0 + in_r2))) {
    iVar1 = HvpGetSocMMIORegs(0x40000);
    *(undefined8 *)(iVar1 + 0x6100) = 0x80021000ffffffff;
    eieioOp();
    instructionSynchronize();
    *(undefined8 *)(iVar1 + 0x6000) = 0xe00ffffffff;
    eieioOp();
    instructionSynchronize();
  }
  HvxPostOutput(0x5f);
  return;
}


void FUN_00003100(void) {
  int in_r2;
  qword back_chain;
  qword local_8;
  
  FUN_00001f60();
  FUN_00002bc0();
  FUN_0000a120();
  FUN_00003f88();
  FUN_00001b10();
  FUN_00001c50();
  FUN_00002dd8();
  FUN_00002e90();
  FUN_00002ff0();
  if ((*(ushort *)(&0x16a9c + in_r2) & 0x8000) == 0) {
    FUN_00003040();
  }
  return;
}



// WARNING: Control flow encountered bad instruction data
// WARNING: Variable defined which should be unmapped: local_10

undefined8 HvxRelocateAndFlush(QWORD param_1,uint param_2,uint param_3)

{
  uint uVar1;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  if ((param_1 & 0xffffffff) < 0x40000000) {
    uVar1 = 0x1000;
  }
  else {
    if (0x7fffffff < (param_1 & 0xffffffff)) {
      return 0;
    }
    uVar1 = 0x10000;
  }
  if ((param_2 - 0x40000 < 0x1ffc0000) && (uVar1 <= 0x20000000 - param_2)) {
    if ((param_3 - 0x40000 < 0x1ffc0000) && (uVar1 <= 0x20000000 - param_3)) {
      memcpy((QWORD)param_3 | 0x8000000000000000);
      HvpFlushSingleTb(param_1 & 0xffffffff,0xfa2aa00);
      return 0;
    }
    _v_MACHINE_CHECK_0(param_1,(QWORD)param_2 | 0x8000000000000000);
  }
  _v_MACHINE_CHECK_0();
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



// WARNING: Control flow encountered bad instruction data
// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

QWORD FUN_00003280(QWORD param_1,QWORD param_2)

{
  QWORD uVar1;
  qword back_chain;
  qword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if ((((param_1 & 0x7f) == 0) && ((param_2 & 0xffffffff) != 0)) && ((param_2 & 0x7f) == 0)) {
    if (((param_1 - 0x40000 & 0xffffffff) < 0x1ffc0000) &&
       ((param_2 & 0xffffffff) <= (0x20000000 - param_1 & 0xffffffff))) {
      J_XeCryptRandom(&local_20,8);
      uVar1 = local_20 & 0xffc0000000 | (QWORD)((uint)(param_1 & 0xffffffff) & 0x3fffff80) |
              0x8000030000000000;
      HvpRelocateCacheLines
                (param_1 & 0xffffffff | 0x8000000000000000,uVar1,param_2 >> 7 & 0x1ffffff);
      return uVar1;
    }
    _v_MACHINE_CHECK_0();
  }
  _v_MACHINE_CHECK_0();
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



void HvpRelocateEncryptedToPhysical(QWORD param_1,uint param_2)

{
  uint uVar1;
  undefined8 in_r0;
  QWORD lVar2;
  undefined8 *puVar3;
  undefined8 *puVar5;
  QWORD uVar4;
  QWORD uVar6;
  QWORD lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  QWORD uVar23;
  
  if (((((param_1 & 0x7f) == 0) && (param_2 != 0)) && ((param_2 & 0x7f) == 0)) &&
     (((param_1 >> 0x28 == 0x800003 &&
       (uVar1 = (uint)param_1 & 0x3fffffff, uVar1 - 0x40000 < 0x1ffc0000)) &&
      (param_2 <= 0x20000000 - uVar1)))) {
    uVar6 = (QWORD)(param_2 >> 7);
    uVar4 = (QWORD)uVar1 | 0x8000000000000000;
    lVar2 = __Save_R12_16_thru_31();
    lVar7 = 0;
    uVar23 = uVar6;
    do {
      dataCacheBlockStore(lVar2 + lVar7);
      lVar7 = lVar7 + 0x80;
      uVar23 = uVar23 - 1;
    } while (uVar23 != 0);
    sync(0);
    instructionSynchronize();
    do {
      puVar3 = (undefined8 *)lVar2;
      uVar8 = puVar3[1];
      uVar9 = puVar3[2];
      uVar10 = puVar3[3];
      uVar11 = puVar3[4];
      uVar12 = puVar3[5];
      uVar13 = puVar3[6];
      uVar14 = puVar3[7];
      uVar15 = puVar3[8];
      uVar16 = puVar3[9];
      uVar17 = puVar3[10];
      uVar18 = puVar3[0xb];
      uVar19 = puVar3[0xc];
      uVar20 = puVar3[0xd];
      uVar21 = puVar3[0xe];
      uVar22 = puVar3[0xf];
      dataCacheBlockFlush(lVar2);
      instructionCacheBlockInvalidate(lVar2);
      lVar2 = lVar2 + 0x80;
      DataCaseBlockSetToZero(in_r0,uVar4);
      puVar5 = (undefined8 *)uVar4;
      *puVar5 = *puVar3;
      puVar5[1] = uVar8;
      puVar5[2] = uVar9;
      puVar5[3] = uVar10;
      puVar5[4] = uVar11;
      puVar5[5] = uVar12;
      puVar5[6] = uVar13;
      puVar5[7] = uVar14;
      puVar5[8] = uVar15;
      puVar5[9] = uVar16;
      puVar5[10] = uVar17;
      puVar5[0xb] = uVar18;
      puVar5[0xc] = uVar19;
      puVar5[0xd] = uVar20;
      puVar5[0xe] = uVar21;
      puVar5[0xf] = uVar22;
      instructionCacheBlockInvalidate(uVar4);
      uVar4 = uVar4 + 0x80;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
    sync(0);
    instructionSynchronize();
    return;
  }
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



// WARNING: Control flow encountered bad instruction data
// WARNING: Variable defined which should be unmapped: local_10

QWORD HvpRelocatePhysicalToProtected(uint param_1,undefined *param_2,QWORD param_3)

{
  QWORD uVar1;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  if ((((((param_1 & 0x7f) == 0) && (param_2 != (undefined *)0x0)) && (((uint)param_2 & 0x7f) == 0))
      && ((param_2 < &0x10001 &&
          ((((uint)(param_2 + (param_1 - 1)) ^ param_1) & 0xffff0000) == 0)))) &&
     ((param_3 - 5U & 0xffffffff) < 0x3b)) {
    if ((param_1 - 0x40000 < 0x1ffc0000) && (param_2 <= (undefined *)(0x20000000 - param_1))) {
      uVar1 = param_3 << 0x21 | (QWORD)(param_1 & 0x3fffff80) | 0x8000010000000000;
      HvpRelocateCacheLines
                ((QWORD)param_1 | 0x8000000000000000,uVar1,(QWORD)((uint)param_2 >> 7));
      return uVar1;
    }
    _v_MACHINE_CHECK_0();
  }
  _v_MACHINE_CHECK_0();
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



void FUN_000034b8(QWORD param_1,QWORD param_2,int param_3)

{
  uint uVar1;
  undefined8 in_r0;
  QWORD lVar2;
  undefined8 *puVar3;
  undefined8 *puVar5;
  QWORD uVar4;
  QWORD uVar6;
  QWORD lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  QWORD uVar23;
  
  if ((((((param_1 & 0x7f) == 0) && ((param_2 & 0xffffffff) != 0)) && ((param_2 & 0x7f) == 0)) &&
      (((param_2 & 0xffffffff) < ZEXT48(&0x10001) &&
       (((((param_2 & 0xffffffff) + param_1) - 1 ^ param_1) & 0xffffffffffff0000) == 0)))) &&
     ((param_3 - 4U < 0x3c && (param_1 >> 0x20 == ((QWORD)(uint)(param_3 << 1) | 0x80000100)))))
  {
    uVar1 = (uint)param_1 & 0x3fffffff;
    if ((((QWORD)uVar1 - 0x40000 & 0xffffffff) < 0x1ffc0000) &&
       ((param_2 & 0xffffffff) <= (0x20000000 - (QWORD)uVar1 & 0xffffffff))) {
      uVar6 = param_2 >> 7 & 0x1ffffff;
      uVar4 = (QWORD)uVar1 | 0x8000000000000000;
      lVar2 = __Save_R12_16_thru_31();
      lVar7 = 0;
      uVar23 = uVar6;
      do {
        dataCacheBlockStore(lVar2 + lVar7);
        lVar7 = lVar7 + 0x80;
        uVar23 = uVar23 - 1;
      } while (uVar23 != 0);
      sync(0);
      instructionSynchronize();
      do {
        puVar3 = (undefined8 *)lVar2;
        uVar8 = puVar3[1];
        uVar9 = puVar3[2];
        uVar10 = puVar3[3];
        uVar11 = puVar3[4];
        uVar12 = puVar3[5];
        uVar13 = puVar3[6];
        uVar14 = puVar3[7];
        uVar15 = puVar3[8];
        uVar16 = puVar3[9];
        uVar17 = puVar3[10];
        uVar18 = puVar3[0xb];
        uVar19 = puVar3[0xc];
        uVar20 = puVar3[0xd];
        uVar21 = puVar3[0xe];
        uVar22 = puVar3[0xf];
        dataCacheBlockFlush(lVar2);
        instructionCacheBlockInvalidate(lVar2);
        lVar2 = lVar2 + 0x80;
        DataCaseBlockSetToZero(in_r0,uVar4);
        puVar5 = (undefined8 *)uVar4;
        *puVar5 = *puVar3;
        puVar5[1] = uVar8;
        puVar5[2] = uVar9;
        puVar5[3] = uVar10;
        puVar5[4] = uVar11;
        puVar5[5] = uVar12;
        puVar5[6] = uVar13;
        puVar5[7] = uVar14;
        puVar5[8] = uVar15;
        puVar5[9] = uVar16;
        puVar5[10] = uVar17;
        puVar5[0xb] = uVar18;
        puVar5[0xc] = uVar19;
        puVar5[0xd] = uVar20;
        puVar5[0xe] = uVar21;
        puVar5[0xf] = uVar22;
        instructionCacheBlockInvalidate(uVar4);
        uVar4 = uVar4 + 0x80;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
      sync(0);
      instructionSynchronize();
      return;
    }
  }
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



QWORD FUN_00003570(byte *param_1,int param_2)

{
  byte bVar1;
  QWORD uVar2;
  undefined8 uVar3;
  
  uVar2 = 0;
  while (param_2 != 0) {
    bVar1 = *param_1;
    param_2 = param_2 + -1;
    param_1 = param_1 + 1;
    uVar2 = bVar1 | uVar2;
  }
  uVar3 = countLeadingZeros((int)uVar2);
  return (QWORD)((uint)uVar3 >> 5 & 1);
}



undefined8 FUN_000035a0(void)

{
  return 0;
}



// WARNING: Removing unreachable block (ram,0x000035d0)
// WARNING: Removing unreachable block (ram,0x000035e8)

undefined8 FUN_000035b0(undefined8 param_1,int param_2)

{
  if ((param_2 != 0) && (param_2 == 0)) {
    return 1;
  }
  return 0;
}



void FUN_00003620(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  int in_r2;
  QWORD lVar2;
  qword back_chain;
  word local_e0;
  dword local_30;
  
  lVar2 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  j_XeCryptHmacShaInit(&local_e0,  0x20,			0x10);
  j_XeCryptHmacShaUpdate(&local_e0, lVar2 + 0x1c,   0xd4);
  j_XeCryptHmacShaUpdate(&local_e0, lVar2 + 0x100,  0x1cf8);
  j_XeCryptHmacShaUpdate(&local_e0, lVar2 + 0x1ef8, 0x2108);
  j_XeCryptHmacShaFinal(&local_e0,	param_2,		param_3);
  FUN_00000204((QWORD)uVar1);
  return;
}



void FUN_000036a8(void)

{
  uint uVar1;
  int in_r2;
  QWORD lVar2;
  QWORD lVar3;
  qword back_chain;
  qword local_60;
  dword local_54;
  word local_50;
  word local_40;
  dword local_30;
  
  lVar2 = __Save_R12_29_thru_31();
  lVar3 = lVar2 + 0x10;
  uVar1 = *(uint *)(in_r2 + 0x10000);
  J_XeCryptRandom(lVar3,8);
  j_XeCryptHmacSha(0x20,0x10,lVar3,0x3ff0,&local_50,2,0,0);
  j_XeCryptHmacSha(0x20,0x10,lVar2,0x10,0,0,0,0);
  j_XeCryptRc4(&local_40,0x10,lVar3,0x3ff0);
  FUN_00000204((QWORD)uVar1);
  return;
}



QWORD FUN_00003760(void)

{
  uint uVar1;
  int in_r2;
  QWORD lVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  qword back_chain;
  qword local_70;
  dword local_64;
  word local_60;
  word local_50;
  word local_40;
  dword local_30;
  
  lVar2 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  j_XeCryptHmacSha(0x20,0x10,lVar2,0x10,0,0,0,0);
  j_XeCryptRc4(&local_50,0x10,lVar2 + 0x10,0x3ff0);
  j_XeCryptHmacSha(0x20,0x10,lVar2 + 0x10,0x3ff0,&local_60,2,0,0);
  uVar3 = J_XeCryptMemDiff(lVar2,&local_40,0x10);
  uVar4 = countLeadingZeros(uVar3);
  FUN_00000204((QWORD)uVar1);
  return (QWORD)((uint)uVar4 >> 5 & 1);
}



void FUN_00003830(undefined8 param_1,uint param_2)
{
  QWORD in_r2;
  int iVar1;
  uint uVar2;
  qword back_chain;
  
  uVar2 = __Save_R12_29_thru_31();
  iVar1 = (int)in_r2;
  HvpAquireSpinLock(ZEXT48(&0x1665c) + in_r2);
  DWORD_00000030 = (uVar2 | 0x21281d3) & ~param_2;
                    // WARNING: Read-only address (ram,0x00000030) is written
  if (*(QWORD *)(&0x162d0 + iVar1) != 0) {
    *(dword *)((int)*(QWORD *)(&0x162d0 + iVar1) + 0x610) = 0x21281d3;
  }
  HvpReleaseSpinLock(ZEXT48(&0x1665c) + in_r2);
  return;
}



undefined8 FUN_000038d8(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  uint uVar2;
  int in_r2;
  undefined8 uVar3;
  int iVar4;
  QWORD uVar5;
  qword back_chain;
  word local_230;
  dword local_30;
  
  uVar3 = __Save_R12_28_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  uVar2 = *(uint *)param_3 << 3;
  if (uVar2 < 0x201) {
    uVar5 = (QWORD)(*(uint *)param_3 & 0x1fffffff);
    j_XeCryptBnQw_SwapDwQwLeBe(param_2,&local_230,uVar5);
    iVar4 = j_XeCryptBnQwNeRsaPubCrypt(&local_230,&local_230,param_3);
    if (iVar4 != 0) {
      j_XeCryptBnQw_SwapDwQwLeBe(&local_230,&local_230,uVar5);
      uVar3 = j_XeCryptBnDwLePkcs1Verify(uVar3,&local_230,(QWORD)uVar2);
      FUN_00000204((QWORD)uVar1);
      return uVar3;
    }
  }
  FUN_00000204((QWORD)uVar1);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00003980(undefined8 param_1,undefined8 param_2,int param_3)

{
  QWORD in_r2;
  undefined8 uVar1;
  qword back_chain;
  word local_180;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (param_3 == 0x10) {
    uVar1 = HvpPhysicalToReal(param_2,0x10);
    j_XeCryptAesKey(&local_180,ZEXT48(&0x16510) + in_r2);
    j_XeCryptAesEcb(&local_180,uVar1, param_1, 0);
    uVar1 = 0;
  }
  else {
    uVar1 = 0xffffffffc8000004;
  }
  return uVar1;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00003af0)

undefined8 FUN_00003a00(undefined8 param_1,int param_2)

{
  uint uVar1;
  QWORD in_r2;
  undefined8 uVar2;
  QWORD uVar3;
  QWORD lVar4;
  qword back_chain;
  word local_120;
  dword local_20;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if (param_2 == 0x100) {
    uVar2 = HvpPhysicalToReal(param_1,0x100);
    memcpy(&local_120,uVar2,0x100);
    lVar4 = ZEXT48(&0x16640) + in_r2;
    uVar3 = FUN_000038d8(lVar4,&local_120,ZEXT48(&0x11a78) + in_r2);
    if (((uVar3 & 0xffffffff) == 0) &&
       ((*(int *)(&0x109c8 + (int)in_r2) != 0x20 ||
        (uVar3 = FUN_000038d8(lVar4,&local_120,ZEXT48(&0x109c8) + in_r2),
        (uVar3 & 0xffffffff) == 0)))) {
      FUN_00000204((QWORD)uVar1);
      uVar2 = 0xffffffffc8000005;
    }
    else {
      FUN_00003830(0x80000,0);
      FUN_00000204((QWORD)uVar1);
      uVar2 = 0;
    }
  }
  else {
    FUN_00000204((QWORD)uVar1);
    uVar2 = 0xffffffffc8000004;
  }
  return uVar2;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00003b10(undefined8 param_1,undefined8 param_2,int param_3)

{
  uint uVar1;
  QWORD in_r2;
  QWORD lVar2;
  undefined8 uVar3;
  qword back_chain;
  word local_d0;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if (param_3 == 0x10) {
    uVar3 = HvpPhysicalToReal(param_2,0x10);
    j_XeCryptHmacShaInit(&local_d0,uVar3,0x10);
    lVar2 = in_r2;
    j_XeCryptHmacShaUpdate(&local_d0,ZEXT48(&0x16400) + in_r2,0x110);
    j_XeCryptHmacShaUpdate(&local_d0,ZEXT48(&0x16510) + in_r2,0x10);
    j_XeCryptHmacShaUpdate(&local_d0,ZEXT48(&0x11b98) + lVar2,10);
    j_XeCryptHmacShaUpdate(&local_d0,0x18,8);
    j_XeCryptHmacShaUpdate(&local_d0,ZEXT48(&0x108b8) + lVar2,0x590);
    j_XeCryptHmacShaUpdate(&local_d0,0x54,0x10);
    j_XeCryptHmacShaUpdate(&local_d0,ZEXT48(&0x11008) + lVar2,0x10);
    j_XeCryptHmacShaUpdate(&local_d0,*(QWORD *)(&0x163c0 + (int)lVar2) + 0xf0,0x10);
    j_XeCryptHmacShaUpdate(&local_d0,ZEXT48(&0x10ff8) + lVar2,0x10);
    j_XeCryptHmacShaFinal(&local_d0,param_1,0x10);
    FUN_00000204((QWORD)uVar1);
    uVar3 = 0;
  }
  else {
    FUN_00000204((QWORD)uVar1);
    uVar3 = 0xffffffffc8000004;
  }
  return uVar3;
}



// WARNING: Removing unreachable block (ram,0x00003c90)

undefined8 FUN_00003c50(undefined8 param_1,QWORD param_2)

{
  undefined uVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  QWORD in_r2;
  int iVar5;
  QWORD uVar6;
  QWORD lVar7;
  word *pwVar8;
  undefined *puVar9;
  QWORD lVar10;
  uint *puVar12;
  undefined8 uVar11;
  QWORD lVar13;
  qword back_chain;
  qword local_1c0;
  dword local_1b4;
  word local_1b0;
  word local_50;
  word local_40;
  dword local_2c;
  
  uVar6 = __Save_R12_29_thru_31();
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  if (((uVar6 & 0xfff) != 0) || ((param_2 & 0xffffffff) != 0x1000)) {
    FUN_00000204((QWORD)uVar2);
    return 0xffffffffc8000004;
  }
  lVar10 = ZEXT48(&0x16a98) + in_r2;
  HvpAquireSpinLock(lVar10);
  lVar7 = HvpRelocatePhysicalToProtected(uVar6,0x1000,0x3a);
  pwVar8 = &local_50;
  puVar9 = (undefined *)(lVar7._4_4_ + 0x100);
  lVar13 = 0x10;
  do {
    uVar1 = *puVar9;
    puVar9 = puVar9 + 1;
    *(undefined *)pwVar8 = uVar1;
    pwVar8 = (word *)((int)pwVar8 + 1);
    lVar13 = lVar13 + -1;
  } while (lVar13 != 0);
  j_XeCryptAesKey(&local_1b0,0x20);
  puVar12 = (uint *)(lVar7._4_4_ + 0x110);
  j_XeCryptAesCbc(&local_1b0,puVar12,0xef0,lVar7 + 0x110,&local_50,0);
  j_XeCryptHmacSha(0x20,0x10,puVar12,0xef0,0,0,0,0);
  iVar5 = (int)in_r2;
  if ((*puVar12 & 1) == 0) {
    puVar9 = &0x11318;
  }
  else {
    puVar9 = &0x10ad8;
  }
  uVar6 = FUN_000038d8(&local_40,lVar7._4_4_,ZEXT48(puVar9) + in_r2);
  if ((uVar6 & 0xffffffff) == 0) {
    uVar11 = 0xffffffffc800000d;
    goto LAB_00003e30;
  }
  if (*(int *)(lVar7._4_4_ + 0x114) == 1) {
    if ((*(uint *)(lVar7._4_4_ + 0x11c) == 0) ||
       (bVar3 = false, *(uint *)(lVar7._4_4_ + 0x11c) < 0x4498)) {
      bVar3 = true;
    }
    if ((*(uint *)(lVar7._4_4_ + 0x120) == 0) ||
       (bVar4 = false, 0x4497 < *(uint *)(lVar7._4_4_ + 0x120))) {
      bVar4 = true;
    }
    if ((!bVar3) || (!bVar4)) {
      uVar11 = 0xffffffffc800000f;
      goto LAB_00003e30;
    }
    if (*(QWORD *)(lVar7._4_4_ + 0x128) ==
        *(QWORD *)((int)*(undefined8 *)(&0x162d0 + iVar5) + 0x20)) {
      uVar11 = FUN_0000b140(lVar7._4_4_ + 0x130,(QWORD)*(uint *)(lVar7._4_4_ + 0x124));
      goto LAB_00003e30;
    }
  }
  uVar11 = 0xffffffffc800000e;
LAB_00003e30:
  HvpZeroCacheLines(lVar7._4_4_,0x20);
  FUN_000034b8(lVar7._4_4_,0x1000,0x3a);
  HvpReleaseSpinLock(lVar10);
  FUN_00000204((QWORD)uVar2);
  return uVar11;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_00003e80(uint param_1)

{
  undefined uVar1;
  uint uVar2;
  QWORD in_r2;
  QWORD lVar3;
  QWORD lVar4;
  word *pwVar5;
  qword back_chain;
  qword local_1b0;
  qword local_1a8;
  word local_1a0;
  word local_40;
  word local_30;
  dword local_20;
  qword local_10;
  qword local_8;
  
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  if ((param_1 & 0x8000000) == 0) {
    do {
      J_XeCryptRandom(&local_40,0x10);
      j_XeCryptAesKey(&local_1a0,&local_40);
      j_XeCryptAesEcb(&local_1a0,&local_30,&local_1b0,0);
      lVar3 = FUN_0000b450(local_1b0);
      lVar4 = FUN_0000b450(local_1a8);
    } while ((lVar4 + lVar3 & 0xffffffffU) != 0x40);
  }
  else {
    local_1b0 = 0xffffffffffffffff;
    local_1a8 = 0xffffffffffffffff;
  }
  lVar3 = ZEXT48(&0x163b0) + in_r2;
  pwVar5 = &local_40;
  lVar4 = 0x10;
  do {
    uVar1 = *(undefined *)pwVar5;
    pwVar5 = (word *)((int)pwVar5 + 1);
    *(undefined *)lVar3 = uVar1;
    lVar3 = lVar3 + 1;
    lVar4 = lVar4 + -1;
  } while (lVar4 != 0);
  *(qword *)(&0x165f0 + (int)in_r2) = local_1b0;
  *(qword *)(&0x165f8 + (int)in_r2) = local_1a8;
  FUN_00000204((QWORD)uVar2);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x000042c0)

QWORD FUN_00003f88(void)

{
  undefined2 uVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  QWORD in_r2;
  QWORD lVar5;
  int iVar7;
  undefined8 uVar6;
  undefined *puVar8;
  byte bVar9;
  QWORD lVar10;
  byte *pbVar11;
  QWORD uVar12;
  QWORD lVar13;
  undefined2 *puVar14;
  undefined *puVar15;
  word *pwVar16;
  QWORD lVar17;
  qword back_chain;
  qword local_190;
  dword local_184;
  word local_180;
  qword local_18;
  qword local_10;
  qword local_8;
  
  lVar5 = FUN_00000270();
  lVar10 = ZEXT48(&0x10cf8) + in_r2;
  uVar12 = 0x10;
  bVar9 = 0;
  iVar7 = (int)in_r2;
  *(QWORD *)(&0x163c0 + iVar7) = lVar5;
  *(QWORD *)(&0x16398 + iVar7) = lVar5 + 0x4000;
  *(QWORD *)(&0x16628 + iVar7) = lVar5 + 0xf800;
  *(QWORD *)(&0x16630 + iVar7) = ZEXT48(&0x0fd80) + lVar5;
  do {
    pbVar11 = (byte *)lVar10;
    uVar12 = uVar12 - 1;
    lVar10 = lVar10 + 1;
    bVar9 = *pbVar11 | bVar9;
  } while ((uVar12 & 0xffffffff) != 0);
  lVar10 = in_r2;
  if (bVar9 != 0) {
    lVar5 = j_XeCryptHmacSha(0x18,8,ZEXT48(&0x10cf8) + in_r2,0x10,0,0,uVar12,0);
  }
  iVar7 = 0x10;
  bVar9 = 0;
  lVar13 = ZEXT48(&0x10e28) + in_r2;
  do {
    pbVar11 = (byte *)lVar13;
    iVar7 = iVar7 + -1;
    lVar13 = lVar13 + 1;
    bVar9 = *pbVar11 | bVar9;
  } while (iVar7 != 0);
  if (bVar9 != 0) {
    lVar5 = j_XeCryptHmacSha(0x18,8,ZEXT48(&0x10e28) + in_r2,0x10,0,0,0,0);
  }
  iVar7 = 0x10;
  bVar9 = 0;
  lVar13 = ZEXT48(&0x10e38) + in_r2;
  do {
    pbVar11 = (byte *)lVar13;
    iVar7 = iVar7 + -1;
    lVar13 = lVar13 + 1;
    bVar9 = *pbVar11 | bVar9;
  } while (iVar7 != 0);
  if (bVar9 != 0) {
    lVar5 = j_XeCryptHmacSha(0x18,8,ZEXT48(&0x10e38) + in_r2,0x10,0,0,0,0);
  }
  pwVar16 = (word *)(ZEXT48(&0x163e0) + lVar10);
  uVar2 = *pwVar16 & 0xfff;
  if (((uVar2 != 0x342) && (uVar2 != 0x362)) && (uVar2 != 0x344)) {
    uVar12 = 0;
    lVar13 = lVar10;
    memset(ZEXT48(&0x163e0) + lVar10,0,0x200);
    iVar7 = HvpGetSocMMIORegs(0);
    uVar3 = *(uint *)(iVar7 + 0xfc);
    if ((0x5e98 < uVar3) || ((uVar3 & 7) != 0)) {
      _v_MACHINE_CHECK_0();
      if ((uVar12 & 0xffffffff) < 0x14) {
        uVar6 = 0xffffffffc8000003;
      }
      else {
        puVar8 = (undefined *)HvpPhysicalToReal();
        lVar13 = ZEXT48(&0x16640) + lVar13;
        lVar5 = 0x14;
        do {
          puVar15 = (undefined *)lVar13;
          lVar13 = lVar13 + 1;
          *puVar8 = *puVar15;
          puVar8 = puVar8 + 1;
          lVar5 = lVar5 + -1;
        } while (lVar5 != 0);
        uVar6 = 0;
      }
      return uVar6;
    }
    lVar5 = ZEXT48(&0x163e6) + lVar10;
    iVar7 = uVar3 + iVar7;
    puVar14 = (undefined2 *)(iVar7 + 0x158);
    *pwVar16 = 0x4e4e;
    iVar4 = (int)lVar10;
    *(undefined2 *)(&0x163e2 + iVar4) = 0x4497;
    lVar17 = 5;
    do {
      uVar1 = *puVar14;
      puVar14 = puVar14 + 1;
      *(undefined2 *)lVar5 = uVar1;
      lVar5 = lVar5 + 2;
      lVar17 = lVar17 + -1;
    } while (lVar17 != 0);
    *(undefined8 *)(&0x163f0 + iVar4) = *(undefined8 *)(iVar7 + 0x148);
    *(undefined8 *)(&0x163f8 + iVar4) = *(undefined8 *)(iVar7 + 0x150);
    lVar5 = memcpy(ZEXT48(&0x16400) + lVar10,iVar7,0x110);
    uVar2 = *(ushort *)(&0x16a9c + (int)lVar13);
    *(undefined8 *)(&0x16408 + iVar4) = 0xfd336b67936aa211;
    if ((uVar2 & 2) == 0) {
      *(undefined8 *)(&0x16510 + iVar4) = *(undefined8 *)(&0x163f0 + iVar4);
      *(undefined8 *)(&0x16518 + iVar4) = *(undefined8 *)(&0x163f8 + iVar4);
    }
    else {
      j_XeCryptAesKey(&local_180,ZEXT48(&0x163f0) + lVar10);
      lVar5 = j_XeCryptAesEcb(&local_180,ZEXT48(&0x11b88) + lVar13,ZEXT48(&0x16510) + lVar10,
                           0);
    }
  }
  return lVar5;
}



// WARNING: Removing unreachable block (ram,0x000042c0)

undefined8 HvxKeysSaveBootLoader(undefined8 param_1,uint param_2)

{
  QWORD in_r2;
  undefined8 uVar1;
  undefined *puVar2;
  undefined *puVar3;
  QWORD lVar4;
  qword back_chain;
  qword local_8;
  
  if (param_2 < 0x14) {
    uVar1 = 0xffffffffc8000003;
  }
  else {
    puVar2 = (undefined *)HvpPhysicalToReal();
    in_r2 = ZEXT48(&0x16640) + in_r2;
    lVar4 = 0x14;
    do {
      puVar3 = (undefined *)in_r2;
      in_r2 = in_r2 + 1;
      *puVar2 = *puVar3;
      puVar2 = puVar2 + 1;
      lVar4 = lVar4 + -1;
    } while (lVar4 != 0);
    uVar1 = 0;
  }
  return uVar1;
}



// WARNING: Removing unreachable block (ram,0x00004324)
// WARNING: Removing unreachable block (ram,0x00004334)
// WARNING: Removing unreachable block (ram,0x00004358)
// WARNING: Removing unreachable block (ram,0x00004360)
// WARNING: Removing unreachable block (ram,0x00004f60)
// WARNING: Removing unreachable block (ram,0x0000436c)
// WARNING: Removing unreachable block (ram,0x00004378)
// WARNING: Removing unreachable block (ram,0x00004384)
// WARNING: Removing unreachable block (ram,0x0000438c)
// WARNING: Removing unreachable block (ram,0x000043a0)
// WARNING: Removing unreachable block (ram,0x000043b4)
// WARNING: Removing unreachable block (ram,0x000043c0)
// WARNING: Removing unreachable block (ram,0x000043cc)
// WARNING: Removing unreachable block (ram,0x00004f4c)
// WARNING: Removing unreachable block (ram,0x000043d4)
// WARNING: Removing unreachable block (ram,0x000043f0)
// WARNING: Removing unreachable block (ram,0x0000441c)
// WARNING: Removing unreachable block (ram,0x00004f10)
// WARNING: Removing unreachable block (ram,0x00004428)
// WARNING: Removing unreachable block (ram,0x00004444)
// WARNING: Removing unreachable block (ram,0x0000444c)
// WARNING: Removing unreachable block (ram,0x00004f04)
// WARNING: Removing unreachable block (ram,0x00004454)
// WARNING: Removing unreachable block (ram,0x00004480)
// WARNING: Removing unreachable block (ram,0x0000448c)
// WARNING: Removing unreachable block (ram,0x000044d4)
// WARNING: Removing unreachable block (ram,0x000044e4)
// WARNING: Removing unreachable block (ram,0x000044ec)
// WARNING: Removing unreachable block (ram,0x000044fc)
// WARNING: Removing unreachable block (ram,0x00004554)
// WARNING: Removing unreachable block (ram,0x00004568)
// WARNING: Removing unreachable block (ram,0x00004570)
// WARNING: Removing unreachable block (ram,0x00004578)
// WARNING: Removing unreachable block (ram,0x000045cc)
// WARNING: Removing unreachable block (ram,0x000045e0)
// WARNING: Removing unreachable block (ram,0x0000460c)
// WARNING: Removing unreachable block (ram,0x00004614)
// WARNING: Removing unreachable block (ram,0x00004630)
// WARNING: Removing unreachable block (ram,0x000045f8)
// WARNING: Removing unreachable block (ram,0x00004634)
// WARNING: Removing unreachable block (ram,0x000046d8)
// WARNING: Removing unreachable block (ram,0x000046e4)
// WARNING: Removing unreachable block (ram,0x00004700)
// WARNING: Removing unreachable block (ram,0x00004718)
// WARNING: Removing unreachable block (ram,0x00004750)
// WARNING: Removing unreachable block (ram,0x000048dc)
// WARNING: Removing unreachable block (ram,0x00004758)
// WARNING: Removing unreachable block (ram,0x00004548)
// WARNING: Removing unreachable block (ram,0x000047ac)
// WARNING: Removing unreachable block (ram,0x000047c0)
// WARNING: Removing unreachable block (ram,0x000047c8)
// WARNING: Removing unreachable block (ram,0x000048d0)
// WARNING: Removing unreachable block (ram,0x000047d0)
// WARNING: Removing unreachable block (ram,0x000047f8)
// WARNING: Removing unreachable block (ram,0x000047ec)
// WARNING: Removing unreachable block (ram,0x00004800)
// WARNING: Removing unreachable block (ram,0x000048a4)
// WARNING: Removing unreachable block (ram,0x000048c0)
// WARNING: Removing unreachable block (ram,0x000048cc)
// WARNING: Removing unreachable block (ram,0x000048e8)
// WARNING: Removing unreachable block (ram,0x000048f8)
// WARNING: Removing unreachable block (ram,0x00004904)
// WARNING: Removing unreachable block (ram,0x00004920)
// WARNING: Removing unreachable block (ram,0x0000470c)
// WARNING: Removing unreachable block (ram,0x0000492c)
// WARNING: Removing unreachable block (ram,0x0000493c)
// WARNING: Removing unreachable block (ram,0x00004950)
// WARNING: Removing unreachable block (ram,0x00004988)
// WARNING: Removing unreachable block (ram,0x00004994)
// WARNING: Removing unreachable block (ram,0x0000499c)
// WARNING: Removing unreachable block (ram,0x00004a10)
// WARNING: Removing unreachable block (ram,0x00004a50)
// WARNING: Removing unreachable block (ram,0x00004a64)
// WARNING: Removing unreachable block (ram,0x00004a6c)
// WARNING: Removing unreachable block (ram,0x00004b84)
// WARNING: Removing unreachable block (ram,0x00004a74)
// WARNING: Removing unreachable block (ram,0x00004b34)
// WARNING: Removing unreachable block (ram,0x00004b3c)
// WARNING: Removing unreachable block (ram,0x00004b78)
// WARNING: Removing unreachable block (ram,0x00004b90)
// WARNING: Removing unreachable block (ram,0x00004ba4)
// WARNING: Removing unreachable block (ram,0x00004bac)
// WARNING: Removing unreachable block (ram,0x00004ef8)
// WARNING: Removing unreachable block (ram,0x00004bb4)
// WARNING: Removing unreachable block (ram,0x00004c5c)
// WARNING: Removing unreachable block (ram,0x00004c6c)
// WARNING: Removing unreachable block (ram,0x00004c78)
// WARNING: Removing unreachable block (ram,0x00004c88)
// WARNING: Removing unreachable block (ram,0x00004c98)
// WARNING: Removing unreachable block (ram,0x00004cc8)
// WARNING: Removing unreachable block (ram,0x00004a04)
// WARNING: Removing unreachable block (ram,0x00004cf0)
// WARNING: Removing unreachable block (ram,0x00004d30)
// WARNING: Removing unreachable block (ram,0x00004d3c)
// WARNING: Removing unreachable block (ram,0x00004d50)
// WARNING: Removing unreachable block (ram,0x00004d58)
// WARNING: Removing unreachable block (ram,0x00004eec)
// WARNING: Removing unreachable block (ram,0x00004f18)
// WARNING: Removing unreachable block (ram,0x00004d60)
// WARNING: Removing unreachable block (ram,0x00004d6c)
// WARNING: Removing unreachable block (ram,0x00004e10)
// WARNING: Removing unreachable block (ram,0x00004dd8)
// WARNING: Removing unreachable block (ram,0x00004e18)
// WARNING: Removing unreachable block (ram,0x00004f28)

undefined8 HvxKeysSetKey(void)

{
  int in_r2;
  qword back_chain;
  qword local_300;
  dword local_2f4;
  word local_2f0;
  dword local_2e4;
  qword local_2e0;
  dword local_2d8;
  word local_2d0;
  word local_2c0;
  word local_2b0;
  word local_1a0;
  word local_19e;
  word local_19c;
  dword local_198;
  dword local_194;
  dword local_128;
  dword local_124;
  word local_120;
  word local_110;
  word local_100;
  word local_f0;
  word local_e0;
  word local_d0;
  word local_c0;
  word local_b0;
  dword local_a0;
  
  __Save_R12_14_thru_31();
  FUN_00000204((QWORD)*(uint *)(in_r2 + 0x10000));
                    // WARNING: Read-only address (ram,0x00000010) is written
                    // WARNING: Read-only address (ram,0x00000014) is written
  return 0xffffffffc8000010;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00004fd8)
// WARNING: Removing unreachable block (ram,0x00004fec)
// WARNING: Removing unreachable block (ram,0x00005030)
// WARNING: Removing unreachable block (ram,0x0000503c)
// WARNING: Removing unreachable block (ram,0x00004fe0)

undefined8 HvxKeysGetKey(void)

{
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  return 0xffffffffc8000007;
}



QWORD HvxKeysGenerateRandomKey(QWORD param_1)

{
  int iVar1;
  int in_r2;
  undefined *puVar2;
  
  if ((param_1 & 0xffffffff) < 0x39) {
    puVar2 = &0x10ec0 + in_r2;
    iVar1 = (int)(param_1 << 2);
  }
  else {
    if (0xd < (param_1 - 0x100 & 0xffffffff)) {
      return 0;
    }
    iVar1 = ((int)param_1 + -0x100) * 4;
    puVar2 = (undefined *)((int)&_XeKeys_Properties_Table_2 + in_r2);
  }
  return (QWORD)*(uint *)(puVar2 + iVar1);
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00005190)

undefined8 HvxKeysHmacSha(undefined8 param_1,QWORD param_2)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  qword back_chain;
  word local_30;
  dword local_1c;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)(in_r2 + 0x10000);
  if ((param_2 & 0xffffffff) < 0x15) {
    j_XeCryptSha(*(QWORD *)(&0x163c0 + in_r2) + 0x18,0x3fe8,0,0,0,0,&local_30,0x14);
    uVar2 = HvpPhysicalToReal(param_1,param_2);
    memcpy(uVar2,&local_30,param_2);
    FUN_00000204((QWORD)uVar1);
    uVar2 = 0;
  }
  else {
    FUN_00000204((QWORD)uVar1);
    uVar2 = 0xffffffffc8000004;
  }
  return uVar2;
}



// WARNING: Removing unreachable block (ram,0x00005338)

undefined8
HvxKeysAesCbc(undefined8 param_1,undefined8 param_2,QWORD param_3,undefined8 param_4,
             QWORD param_5)

{
  QWORD uVar1;
  undefined *puVar2;
  int in_r2;
  QWORD uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  int iVar6;
  QWORD lVar7;
  uint uVar8;
  qword back_chain;
  
  uVar3 = __Save_R12_26_thru_31();
  if ((uVar3 & 0xffffffff) < 0x39) {
    uVar1 = uVar3 & 0xffffffff;
    puVar2 = &0x10e48;
    uVar8 = *(uint *)(&0x10ec0 + (int)(uVar1 << 2) + in_r2);
    lVar7 = *(QWORD *)(&0x163c0 + in_r2);
  }
  else {
    if (0xd < (uVar3 - 0x100 & 0xffffffff)) {
      return 0xffffffffc8000001;
    }
    puVar2 = &0x10fa4;
    uVar1 = uVar3 - 0x100 & 0xffffffff;
    uVar8 = *(uint *)((int)&_XeKeys_Properties_Table_2 + (int)(uVar1 << 2) + in_r2);
    lVar7 = *(QWORD *)(&0x16398 + in_r2);
  }
  lVar7 = (QWORD)*(ushort *)(puVar2 + (int)(uVar1 << 1) + in_r2) + lVar7 + 0x18;
  if ((uVar3 & 0xffffffff) == 0x35) {
    uVar4 = 0;
  }
  else {
    if ((uVar3 & 0xffffffff) != 0x34) goto LAB_000052b0;
    uVar4 = 1;
  }
  uVar3 = FUN_0000b100(uVar4);
  if ((uVar3 & 0xffffffff) == 0) {
    return 0xffffffffc8000002;
  }
LAB_000052b0:
  if ((uVar8 & 0x200000) == 0) {
    return 0xffffffffc8000002;
  }
  if (((param_3 & 0xffffffff) == (param_5 & 0xffffffff)) &&
     ((param_3 & 0xffffffff) == (QWORD)*(uint *)lVar7 << 3)) {
    uVar4 = HvpPhysicalToReal(param_2,param_3);
    uVar5 = HvpPhysicalToReal(param_4,param_5);
    iVar6 = j_XeCryptBnQwNeRsaPrvCrypt(uVar4,uVar5,lVar7);
    if (iVar6 != 0) {
      return 0;
    }
    return 0xffffffffc8000006;
  }
  return 0xffffffffc8000004;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x000054fc)

undefined8
FUN_00005348(QWORD param_1,uint param_2,undefined8 param_3,int param_4,undefined *param_5)

{
  undefined uVar1;
  undefined8 unaff_100001b4;
  QWORD in_r2;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  undefined *puVar5;
  uint uVar6;
  QWORD lVar7;
  QWORD lVar8;
  qword back_chain;
  word local_170;
  qword local_10;
  qword local_8;
  
  iVar2 = (int)in_r2;
  if ((param_1 & 0xffffffff) == 0) {
    if (param_4 == 0x10) {
      puVar5 = (undefined *)HvpPhysicalToReal(param_3,0x10);
      lVar7 = 0x10;
      puVar4 = param_5;
      do {
        uVar1 = *puVar5;
        puVar5 = puVar5 + 1;
        *puVar4 = uVar1;
        puVar4 = puVar4 + 1;
        lVar7 = lVar7 + -1;
      } while (lVar7 != 0);
      j_XeCryptAesKey(&local_170,*(QWORD *)(&0x163c0 + iVar2) + 0xe0);
      j_XeCryptAesEcb(&local_170,param_5,unaff_100001b4,0);
      return 0;
    }
    return 0xffffffffc8000004;
  }
  if ((param_1 & 0xffffffff) < 0x39) {
    uVar6 = *(uint *)(&0x10ec0 + (int)((param_1 & 0xffffffff) << 2) + iVar2);
    uVar3 = uVar6 & 0xffff;
    lVar7 = (QWORD)*(ushort *)(&0x10e48 + (int)((param_1 & 0xffffffff) << 1) + iVar2) +
            *(QWORD *)(&0x163c0 + iVar2) + 0x18;
    goto LAB_000054a4;
  }
  if ((param_1 & 0xffffffff) == 0x43) {
    puVar4 = &0x10ff8;
LAB_0000545c:
    lVar7 = ZEXT48(puVar4) + in_r2;
    uVar6 = 0x510000;
  }
  else {
    if ((param_1 & 0xffffffff) == 0x47) {
      puVar4 = &0x16600;
      goto LAB_0000545c;
    }
    if (7 < (param_1 - 0xe0 & 0xffffffff)) {
      return 0xffffffffc8000001;
    }
    uVar6 = 0xd10000;
    lVar7 = ((param_1 - 0xe0) * 0x10 & 0xffffffff0) + *(QWORD *)(&0x16630 + iVar2);
  }
  uVar3 = 0x10;
LAB_000054a4:
  if (((uVar6 & (param_2 | 0x10000)) == (param_2 | 0x10000)) && (0xf < uVar3)) {
    lVar8 = 0x10;
    do {
      puVar4 = (undefined *)lVar7;
      lVar7 = lVar7 + 1;
      *param_5 = *puVar4;
      param_5 = param_5 + 1;
      lVar8 = lVar8 + -1;
    } while (lVar8 != 0);
    return 0;
  }
  return 0xffffffffc8000002;
}



undefined8
HvxKeysDes2Cbc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
              undefined8 param_5,undefined8 param_6,QWORD param_7)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  undefined8 uVar3;
  qword back_chain;
  qword local_60;
  dword local_54;
  word local_50;
  dword local_40;
  
  uVar2 = __Save_R12_27_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  uVar2 = FUN_00005348(uVar2,0x800000,param_2,param_3,&local_50);
  if ((int)uVar2 == 0) {
    if (0x14 < (param_7 & 0xffffffff)) {
      FUN_00000204((QWORD)uVar1);
      return 0xffffffffc8000004;
    }
    uVar3 = HvpPhysicalToReal(param_4,param_5);
    HvpPhysicalToReal(param_6,param_7);
    j_XeCryptHmacSha(&local_50,0x10,uVar3,param_5,0,0,0,0);
  }
  FUN_00000204((QWORD)uVar1);
  return uVar2;
}



undefined8
HvxKeysDesCbc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             QWORD param_5,undefined8 param_6,undefined8 param_7,QWORD param_8)

{
  uint uVar1;
  QWORD in_r2;
  QWORD uVar2;
  undefined8 uVar3;
  QWORD uVar4;
  QWORD lVar5;
  QWORD lVar6;
  undefined8 uVar7;
  uint uVar8;
  qword back_chain;
  word local_1d0;
  word local_70;
  dword local_60;
  
  uVar2 = __Save_R12_23_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  uVar3 = FUN_00005348(uVar2 >> 0x20,0x400000,param_2,param_3,&local_70);
  if ((int)uVar3 == 0) {
    if (((int)(uVar2 >> 0x20) == 0x1b) && (uVar4 = FUN_0000b100(8), (uVar4 & 0xffffffff) == 0)) {
      FUN_00000204((QWORD)uVar1);
      return 0xffffffffc8000002;
    }
    if ((param_5 & 0xf) != 0) {
      FUN_00000204((QWORD)uVar1);
      return 0xffffffffc8000004;
    }
    HvpAquireSpinLock(ZEXT48(&0x16920) + in_r2);
    lVar5 = FUN_00002a18(param_4,param_5);
    lVar6 = FUN_00002a18(param_6,param_5);
    HvpSetRMCIEx(0,lVar5,lVar6);
    j_XeCryptAesKey(&local_1d0,&local_70);
    if ((param_8 & 0xffffffff) == 0) {
      uVar8 = (uint)param_5 >> 4;
      while (uVar8 != 0) {
        j_XeCryptAesEcb(&local_1d0,lVar5,lVar6,uVar2 & 0xffffffff);
        uVar8 = uVar8 - 1;
        lVar5 = lVar5 + 0x10;
        lVar6 = lVar6 + 0x10;
      }
    }
    else {
      if ((param_8 & 0xffffffff) == 0x10) {
        uVar7 = HvpPhysicalToReal(param_7,0x10);
        j_XeCryptAesCbc(&local_1d0,lVar5,param_5,lVar6,uVar7,uVar2 & 0xffffffff);
      }
      else {
        uVar3 = 0xffffffffc8000004;
      }
    }
    HvpSetRMCIEx(1,lVar5,lVar6);
    HvpReleaseSpinLock(ZEXT48(&0x16920) + in_r2);
  }
  FUN_00000204((QWORD)uVar1);
  return uVar3;
}



undefined8
HvxKeysObscureKey(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, QWORD param_5,undefined8 param_6,undefined8 param_7,QWORD param_8)
{
  uint uVar1;
  int in_r2;
  QWORD uVar2;
  undefined8 uVar3;
  QWORD uVar4;
  QWORD lVar5;
  QWORD lVar6;
  undefined8 uVar7;
  uint uVar8;
  qword back_chain;
  word local_1f0;
  qword local_70;
  qword local_60;
  dword local_58;
  
  uVar2 = __Save_R12_24_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  uVar3 = FUN_00005348(uVar2 >> 0x20,0x400000,param_2,param_3,&local_70);
  if ((int)uVar3 == 0) {
    if (((int)(uVar2 >> 0x20) == 0x1b) && (uVar4 = FUN_0000b100(8), (uVar4 & 0xffffffff) == 0)) {
      FUN_00000204((QWORD)uVar1);
      return 0xffffffffc8000002;
    }
    if ((param_5 & 7) != 0) {
LAB_0000580c:
      FUN_00000204((QWORD)uVar1);
      return 0xffffffffc8000004;
    }
    lVar5 = HvpPhysicalToReal(param_4,param_5);
    lVar6 = HvpPhysicalToReal(param_6,param_5);
    j_XeCryptDesParity(&local_70,0x18,&local_70);
    FUN_0000b418(&local_1f0,&local_70);
    if ((param_8 & 0xffffffff) == 0) {
      uVar8 = (uint)param_5 >> 3;
      while (uVar8 != 0) {
        j_XeCryptDes3Ecb(&local_1f0,lVar5,lVar6,uVar2 & 0xffffffff);
        uVar8 = uVar8 - 1;
        lVar5 = lVar5 + 8;
        lVar6 = lVar6 + 8;
      }
    }
    else {
      if ((param_8 & 0xffffffff) != 8) goto LAB_0000580c;
      uVar7 = HvpPhysicalToReal(param_7,8);
      j_XeCryptDes3Cbc(&local_1f0,lVar5,param_5,lVar6,uVar7,uVar2 & 0xffffffff);
    }
  }
  FUN_00000204((QWORD)uVar1);
  return uVar3;
}



undefined8
HvxSyscall_3F(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             QWORD param_5,undefined8 param_6,undefined8 param_7,QWORD param_8)

{
  uint uVar1;
  int in_r2;
  QWORD uVar2;
  undefined8 uVar3;
  QWORD lVar4;
  QWORD lVar5;
  undefined8 uVar6;
  uint uVar7;
  qword back_chain;
  word local_e0;
  word local_60;
  dword local_50;
  
  uVar2 = __Save_R12_25_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  uVar3 = FUN_00005348(uVar2 >> 0x20,0x4000000,param_2,param_3,&local_60);
  if ((int)uVar3 == 0) {
    if ((param_5 & 7) != 0) {
LAB_00005950:
      FUN_00000204((QWORD)uVar1);
      return 0xffffffffc8000004;
    }
    lVar4 = HvpPhysicalToReal(param_4,param_5);
    lVar5 = HvpPhysicalToReal(param_6,param_5);
    j_XeCryptDesParity(&local_60,8,&local_60);
    j_XeCryptDesKey(&local_e0,&local_60);
    if ((param_8 & 0xffffffff) == 0) {
      uVar7 = (uint)param_5 >> 3;
      while (uVar7 != 0) {
        j_XeCryptDesEcb(&local_e0,lVar4,lVar5,uVar2 & 0xffffffff);
        uVar7 = uVar7 - 1;
        lVar4 = lVar4 + 8;
        lVar5 = lVar5 + 8;
      }
    }
    else {
      if ((param_8 & 0xffffffff) != 8) goto LAB_00005950;
      uVar6 = HvpPhysicalToReal(param_7,8);
      j_XeCryptDesCbc(&local_e0,lVar4,param_5,lVar5,uVar6,uVar2 & 0xffffffff);
    }
  }
  FUN_00000204((QWORD)uVar1);
  return uVar3;
}



// WARNING: Removing unreachable block (ram,0x00005b24)

undefined8 HvxSyscall_40(undefined8 param_1,QWORD param_2,undefined8 param_3,QWORD param_4)

{
  undefined uVar1;
  uint uVar2;
  int in_r2;
  undefined8 uVar3;
  word *pwVar4;
  undefined *puVar5;
  undefined *puVar6;
  QWORD lVar7;
  qword back_chain;
  word local_1a0;
  word local_40;
  dword local_30;
  
  __Save_R12_29_thru_31();
  uVar2 = *(uint *)(in_r2 + 0x10000);
  if (((param_2 & 0xffffffff) < 0x10) || ((param_4 & 0xffffffff) < 0x10)) {
    FUN_00000204((QWORD)uVar2);
    uVar3 = 0xffffffffc8000003;
  }
  else {
    puVar6 = (undefined *)HvpPhysicalToReal();
    puVar5 = (undefined *)HvpPhysicalToReal(param_3,param_4);
    pwVar4 = &local_40;
    lVar7 = 0x10;
    do {
      uVar1 = *puVar6;
      puVar6 = puVar6 + 1;
      *(undefined *)pwVar4 = uVar1;
      pwVar4 = (word *)((int)pwVar4 + 1);
      lVar7 = lVar7 + -1;
    } while (lVar7 != 0);
    j_XeCryptAesKey(&local_1a0,*(QWORD *)(&0x163c0 + in_r2) + 0xe0);
    j_XeCryptAesEcb(&local_1a0,&local_40,&local_40,1);
    pwVar4 = &local_40;
    lVar7 = 0x10;
    do {
      uVar1 = *(undefined *)pwVar4;
      pwVar4 = (word *)((int)pwVar4 + 1);
      *puVar5 = uVar1;
      puVar5 = puVar5 + 1;
      lVar7 = lVar7 + -1;
    } while (lVar7 != 0);
    FUN_00000204((QWORD)uVar2);
    uVar3 = 0;
  }
  return uVar3;
}



undefined8 HvxKeysObscureKey(void)

{
  return 0x21281d3;
}



// WARNING: Removing unreachable block (ram,0x00005e38)
// WARNING: Removing unreachable block (ram,0x00005d18)
// WARNING: Removing unreachable block (ram,0x00005bac)
// WARNING: Removing unreachable block (ram,0x00005d54)
// WARNING: Removing unreachable block (ram,0x00005f4c)

undefined8 HvxKeysSaveSystemUpdate(undefined8 param_1,QWORD param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  QWORD in_r2;
  int iVar4;
  QWORD uVar5;
  ushort *puVar6;
  word *pwVar7;
  QWORD lVar8;
  undefined *puVar9;
  ushort *puVar10;
  ushort *puVar11;
  undefined8 uVar12;
  QWORD lVar13;
  qword back_chain;
  qword local_3a0;
  dword local_394;
  word local_390;
  word local_280;
  word local_270;
  word local_260;
  dword local_60;
  
  uVar5 = __Save_R12_23_thru_31();
  iVar4 = (int)in_r2;
  uVar1 = *(uint *)(iVar4 + 0x10000);
  if (((uVar5 & 0xffff) != 0) || ((param_2 & 0xffffffff) != 0x10000)) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc8000021;
  }
  pwVar7 = &local_270;
  lVar8 = ZEXT48(&0x16510) + in_r2;
  lVar13 = 0x10;
  do {
    puVar9 = (undefined *)lVar8;
    lVar8 = lVar8 + 1;
    *(undefined *)pwVar7 = *puVar9;
    pwVar7 = (word *)((int)pwVar7 + 1);
    lVar13 = lVar13 + -1;
  } while (lVar13 != 0);
  HvpAquireSpinLock(ZEXT48(&0x16610) + in_r2);
  puVar6 = (ushort *)HvpRelocatePhysicalToProtected(uVar5,0x10000,0x3c);
  if ((*puVar6 & 0xfff) == 0x346) {
    uVar2 = *(uint *)(puVar6 + 6);
    uVar3 = uVar2 + 0xf & 0xfffffff0;
    if (((uVar2 < 0x360) || ((QWORD)uVar3 < (QWORD)uVar2)) || (0x10000 < uVar3)) {
      uVar12 = 0xffffffffc8000024;
    }
    else {
      if (((*puVar6 ^ 0x4e4e) & 0xf000) == 0) {
        if (*(int *)(puVar6 + 8) == 0x7600000) {
          uVar2 = *(uint *)(puVar6 + 10);
          if (((uVar2 & 0x8000) == 0) &&
             ((uVar5 = FUN_000035b0(1,0), (uVar5 & 0xffffffff) != 0 || (0x44970000 < uVar2)))) {
            puVar11 = puVar6 + 0x18;
            memcpy(&local_260,puVar11,0x200);
            uVar12 = 0;
            puVar10 = puVar6 + 0x10;
            j_XeCryptHmacSha(&local_270,0x10,puVar10,0x10,0,0,0,0);
            j_XeCryptRc4Key(&local_390,&local_280,0x10);
            lVar8 = (QWORD)uVar3 - 0x30;
            j_XeCryptRc4Ecb(&local_390,puVar11,lVar8);
            memset(puVar11,0,0x200);
            memcpy(puVar11,&local_260,0x1c0);
            *(undefined *)((int)puVar6 + 0x21b) = 1;
            *(uint *)(puVar6 + 0x10e) = (uint)(byte)(&0x16620)[iVar4] | 0xc81cb400;
            if ((((puVar6[3] & 0x4000) != 0) &&
                ((byte)(&0x16620)[iVar4] < (byte)(&0x16658)[iVar4])) &&
               (0x4496ffff < uVar2)) {
              *(int *)(puVar6 + 0x10e) = *(int *)(puVar6 + 0x10e) + 1;
            }
            J_XeCryptRandom(puVar10,0x10);
            j_XeCryptHmacSha(&local_270,0x10,puVar10,0x10,0,0,0,0);
            j_XeCryptHmacSha(0x20,0x10,puVar6,0x20,&local_280,0x10,puVar11,0x1f0);
            j_XeCryptRc4Key(&local_390,&local_280,0x10);
            j_XeCryptRc4Ecb(&local_390,puVar11,lVar8);
            goto LAB_00005f10;
          }
          uVar12 = 0xffffffffc8000027;
        }
        else {
          uVar12 = 0xffffffffc8000026;
        }
      }
      else {
        uVar12 = 0xffffffffc8000025;
      }
    }
  }
  else {
    uVar12 = 0xffffffffc8000023;
  }
  HvpZeroCacheLines(puVar6,0x200);
LAB_00005f10:
  FUN_000034b8(puVar6,0x10000,0x3c);
  HvpReleaseSpinLock(ZEXT48(&0x16610) + in_r2);
  FUN_00000204((QWORD)uVar1);
  return uVar12;
}



//undefined8
//HvxKeysExecute(undefined8 param_1,QWORD param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6)
QWORD HvxKeysExecute(PBYTE pbPayload, DWORD cbPayload, QWORD Arg1, QWORD Arg2, QWORD Arg3, QWORD Arg4)
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  QWORD in_r2;
  QWORD uVar4;
  ushort *puVar5;
  int iVar6;
  undefined8 *puVar7;
  QWORD lVar8;
  QWORD uVar9;
  undefined8 uVar10;
  ushort *puVar11;
  QWORD lVar12;
  qword back_chain;
  qword local_2e0;
  dword local_2d4;
  word local_2d0;
  word local_1c0;
  word local_1b0;
  word local_190;
  dword local_90;
  
  uVar4 = __Save_R12_17_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if (((((uVar4 & 0x7f) != 0) || ((param_2 & 0x7f) != 0)) ||
      (ZEXT48(&0x0fee0) < (param_2 - 0x120 & 0xffffffff))) ||
     (((((uint)uVar4 + (uint)param_2) - 1 ^ (uint)uVar4) & 0xffff0000) != 0)) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc8000030;
  }
  lVar8 = ZEXT48(&0x165e0) + in_r2;
  HvpAquireSpinLock(lVar8);
  puVar5 = (ushort *)HvpRelocatePhysicalToProtected(uVar4,param_2,0x3e);
  if ((*puVar5 & 0xf0f) == 0xd0d) {
    if (((*puVar5 ^ 0x4e4e) & 0xf000) == 0) {
      uVar2 = *(uint *)(puVar5 + 6);
      uVar9 = (QWORD)(uVar2 + 0xf & 0xfffffff0);
      if (((uVar2 < 0x120) || (uVar9 < uVar2)) || ((param_2 & 0xffffffff) < uVar9)) {
        uVar10 = 0xffffffffc8000034;
LAB_00006208:
        if ((int)uVar10 == 0) {
          memcpy(&local_190,puVar5 + 0x10,0x100);
          goto LAB_00006034;
        }
      }
      else {
        uVar3 = *(uint *)(puVar5 + 4);
        if ((((uVar3 & 3) == 0) && (0x11f < uVar3)) && (uVar3 < (uVar2 & 0xfffffffc))) {
          lVar12 = in_r2;
          j_XeCryptHmacSha(ZEXT48(&0x16510) + in_r2,0x10,puVar5 + 8,0x10,0,0,0,0);
          j_XeCryptRc4Key(&local_2d0,&local_1c0,0x10);
          puVar11 = puVar5 + 0x10;
          j_XeCryptRc4Ecb(&local_2d0,puVar11,uVar9 - 0x20);
          j_XeCryptRotSumSha(puVar5,0x10,puVar5 + 0x90,uVar9 - 0x120,&local_1b0,0x14);
          iVar6 = j_XeCryptBnQwBeSigVerify(puVar11,&local_1b0,ZEXT48(&0x11ba4) + lVar12,
                               ZEXT48(&0x16400) + in_r2);
          if (iVar6 != 0) {
            *(undefined8 *)(puVar5 + 8) = 0;
            *(undefined8 *)(puVar5 + 0xc) = 0;
            memset(puVar11,0,0x100);
            if ((QWORD)uVar2 < (param_2 & 0xffffffff)) {
              memset(uVar2 + (int)puVar5,0,param_2 - uVar2);
            }
            uVar10 = (*(code *)(uVar3 + (int)puVar5))(puVar5,param_3,param_4,param_5,param_6);
            goto LAB_00006208;
          }
          uVar10 = 0xffffffffc8000036;
        }
        else {
          uVar10 = 0xffffffffc8000035;
        }
      }
    }
    else {
      uVar10 = 0xffffffffc8000033;
    }
  }
  else {
    uVar10 = 0xffffffffc8000032;
  }
  puVar7 = (undefined8 *)&local_190;
  lVar12 = 0x20;
  do {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
    lVar12 = lVar12 + -1;
  } while (lVar12 != 0);
LAB_00006034:
  HvpInvalidateCachelines(puVar5,param_2);
  lVar12 = HvpPhysicalToReal(uVar4,param_2);
  HvpZeroCacheLines(lVar12,(QWORD)((uint)param_2 >> 7));
  memcpy(lVar12 + 0x20,&local_190,0x100);
  HvpReleaseSpinLock(lVar8);
  FUN_00000204((QWORD)uVar1);
  return uVar10;
}





// WARNING: Removing unreachable block (ram,0x0000626c)
// WARNING: Removing unreachable block (ram,0x0000627c)

undefined8 HvxDvdAuthTestMode(void)

{
  qword back_chain;
  qword local_8;
  
  return 0xffffffffc8000007;
}



// WARNING: Removing unreachable block (ram,0x000062f0)
// WARNING: Removing unreachable block (ram,0x00006300)
// WARNING: Removing unreachable block (ram,0x00006318)
// WARNING: Removing unreachable block (ram,0x0000632c)
// WARNING: Removing unreachable block (ram,0x000063a8)
// WARNING: Removing unreachable block (ram,0x00006368)
// WARNING: Removing unreachable block (ram,0x00006380)
// WARNING: Removing unreachable block (ram,0x00006320)
// WARNING: Removing unreachable block (ram,0x0000630c)

undefined8 HvxSyscall_4F(void)

{
  qword back_chain;
  
  __Save_R12_29_thru_31();
  return 0xffffffffc8000002;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x0000647c)

undefined8 HvxGetUpdateSequence(QWORD param_1,int param_2)

{
  int in_r2;
  undefined8 uVar1;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  if ((param_1 & 0xfff) == 0) {
    if (param_2 == 0x4000) {
      HvpSetRMCI(0);
      uVar1 = FUN_00003280(param_1,0x4000);
      memcpy(uVar1,*(undefined8 *)(&0x16398 + in_r2),0x4000);
      FUN_000036a8(uVar1);
      HvpRelocateEncryptedToPhysical(uVar1,0x4000);
      HvpSetRMCI(1);
      uVar1 = 0;
    }
    else {
      uVar1 = 0xffffffffc8000008;
    }
  }
  else {
    uVar1 = 0xffffffffc8000009;
  }
  return uVar1;
}



// WARNING: Removing unreachable block (ram,0x000065d8)

undefined8 HvxSecurityInitialize(undefined8 param_1,undefined8 param_2,QWORD param_3)

{
  ushort uVar1;
  uint uVar2;
  int in_r2;
  QWORD lVar3;
  QWORD uVar4;
  undefined8 uVar5;
  QWORD lVar6;
  qword back_chain;
  
  lVar3 = __Save_R12_28_thru_31();
  if (0xd < (lVar3 - 0x100U & 0xffffffff)) {
    return 0xffffffffc8000001;
  }
  if (((lVar3 - 0x103U & 0xffffffff) < 6) && (uVar4 = FUN_0000b100(8), (uVar4 & 0xffffffff) == 0)) {
    return 0xffffffffc8000002;
  }
  uVar4 = lVar3 - 0x100U & 0xffffffff;
  uVar2 = *(uint *)((int)&_XeKeys_Properties_Table_2 + (int)(uVar4 << 2) + in_r2);
  uVar1 = *(ushort *)(&0x10fa4 + (int)(uVar4 << 1) + in_r2);
  uVar4 = (QWORD)(uVar2 & 0xffff);
  lVar6 = *(QWORD *)(&0x16398 + in_r2);
  lVar3 = (QWORD)uVar1 + lVar6 + 0x18;
  uVar5 = HvpPhysicalToReal(param_2,param_3);
  if ((uVar2 & 0x10000) == 0) {
    if (((param_3 & 0xffffffff) <= uVar4) && (1 < (uVar4 - param_3 & 0xffffffff))) {
      memset(lVar3,0,uVar4);
      *(undefined2 *)lVar3 = (short)param_3;
      lVar3 = (QWORD)uVar1 + lVar6 + 0x1a;
      uVar4 = param_3;
      goto LAB_000065bc;
    }
  }
  else {
    if ((param_3 & 0xffffffff) == uVar4) {
LAB_000065bc:
      memcpy(lVar3,uVar5,uVar4);
      return 0;
    }
  }
  return 0xffffffffc8000004;
}



// WARNING: Removing unreachable block (ram,0x0000672c)

undefined8 HvxSyscall_52(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  int in_r2;
  QWORD uVar4;
  uint *puVar6;
  undefined8 uVar5;
  QWORD lVar7;
  QWORD lVar8;
  ushort *puVar9;
  QWORD uVar10;
  qword back_chain;
  
  uVar4 = __Save_R12_27_thru_31();
  if ((uVar4 - 0x100 & 0xffffffff) < 0xe) {
    if (((uVar4 & 0xffffffff) == 0x103) || ((uVar4 & 0xffffffff) == 0x104)) {
      uVar5 = 0xffffffffc8000002;
    }
    else {
      uVar4 = uVar4 - 0x100 & 0xffffffff;
      uVar2 = *(uint *)((int)&_XeKeys_Properties_Table_2 + (int)(uVar4 << 2) + in_r2);
      uVar1 = *(ushort *)(&0x10fa4 + (int)(uVar4 << 1) + in_r2);
      uVar3 = uVar2 & 0xffff;
      uVar4 = (QWORD)uVar3;
      lVar7 = *(QWORD *)(&0x16398 + in_r2);
      lVar8 = (QWORD)uVar1 + lVar7 + 0x18;
      puVar6 = (uint *)HvpPhysicalToReal(param_3,4);
      uVar10 = (QWORD)*puVar6;
      uVar5 = HvpPhysicalToReal(param_2,uVar10);
      if ((uVar2 & 0x10000) == 0) {
        if (uVar3 < 2) {
          uVar4 = 0;
        }
        else {
          puVar9 = (ushort *)lVar8;
          uVar4 = uVar4 - 2;
          lVar8 = (QWORD)uVar1 + lVar7 + 0x1a;
          if ((QWORD)*puVar9 < (uVar4 & 0xffffffff)) {
            uVar4 = (QWORD)*puVar9;
          }
          if (uVar10 < (uVar4 & 0xffffffff)) {
            return 0xffffffffc8000003;
          }
        }
      }
      else {
        if (uVar10 != uVar4) {
          return 0xffffffffc8000004;
        }
      }
      memcpy(uVar5,lVar8,uVar4);
      uVar5 = 0;
      *puVar6 = (uint)uVar4;
    }
  }
  else {
    uVar5 = 0xffffffffc8000001;
  }
  return uVar5;
}



// WARNING: Removing unreachable block (ram,0x00006750)

undefined8 HvxSyscall_53(void)

{
  return 0;
}



QWORD FUN_00006760(void)

{
  uint uVar1;
  int in_r2;
  QWORD lVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  qword back_chain;
  qword local_60;
  dword local_54;
  word local_50;
  word local_40;
  dword local_30;
  
  lVar2 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  j_XeCryptHmacSha(0x20,0x10,lVar2,0x10,0,0,0,0);
  j_XeCryptRc4(&local_50,0x10,lVar2 + 0x10,0x3f0);
  j_XeCryptHmacSha(0x20,0x10,lVar2 + 0x10,0x3f0,0,0,0,0);
  uVar3 = J_XeCryptMemDiff(lVar2,&local_40,0x10);
  uVar4 = countLeadingZeros(uVar3);
  FUN_00000204((QWORD)uVar1);
  return (QWORD)((uint)uVar4 >> 5 & 1);
}



void FUN_00006828(void)

{
  uint uVar1;
  int in_r2;
  QWORD lVar2;
  QWORD lVar3;
  qword back_chain;
  qword local_50;
  dword local_44;
  word local_40;
  dword local_30;
  
  lVar2 = __Save_R12_29_thru_31();
  lVar3 = lVar2 + 0x10;
  uVar1 = *(uint *)(in_r2 + 0x10000);
  J_XeCryptRandom(lVar3,8);
  j_XeCryptHmacSha(0x20,0x10,lVar3,0x3f0,0,0,0,0);
  j_XeCryptHmacSha(0x20,0x10,lVar2,0x10,0,0,0,0);
  j_XeCryptRc4(&local_40,0x10,lVar3,0x3f0);
  FUN_00000204((QWORD)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00006914)

undefined8 HvxSyscall_54(void)

{
  qword back_chain;
  qword local_10;
  qword local_8;
  
  return 0xffffffffc8000040;
}



undefined8 HvxSyscall_56(undefined8 param_1,QWORD param_2,undefined8 param_3)

{
  int in_r2;
  int iVar1;
  QWORD uVar2;
  undefined8 uVar3;
  qword back_chain;
  
  uVar2 = __Save_R12_29_thru_31();
  if (*(char *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x18) == '\0') {
    uVar3 = 0xffffffffc8000040;
  }
  else {
    if ((param_2 & 0xffffffff) == 0x400) {
      if ((uVar2 & 0xfff) == 0) {
        iVar1 = in_r2;
        HvpSetRMCI(0);
        uVar3 = FUN_00003280(uVar2,0x400);
        *(undefined *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x19) = (&0x16620)[iVar1];
        uVar2 = func_0x00002b70();
        if ((uVar2 & 0xffffffff) != 0) {
          *(char *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x19) =
               *(char *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x19) + '\x01';
        }
        *(undefined8 *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x20) = param_3;
        memcpy(uVar3,*(undefined8 *)(&0x16628 + in_r2),0x400);
        FUN_00006828(uVar3);
        HvpRelocateEncryptedToPhysical(uVar3,0x400);
        HvpSetRMCI(1);
        uVar3 = 0;
      }
      else {
        uVar3 = 0xffffffffc8000042;
      }
    }
    else {
      uVar3 = 0xffffffffc8000041;
    }
  }
  return uVar3;
}



// WARNING: Removing unreachable block (ram,0x00006a84)
// WARNING: Removing unreachable block (ram,0x00006a98)
// WARNING: Removing unreachable block (ram,0x00006aa4)
// WARNING: Removing unreachable block (ram,0x00006ab0)
// WARNING: Removing unreachable block (ram,0x00006abc)
// WARNING: Removing unreachable block (ram,0x00006afc)
// WARNING: Removing unreachable block (ram,0x00006b20)
// WARNING: Removing unreachable block (ram,0x00006b2c)
// WARNING: Removing unreachable block (ram,0x00006b10)
// WARNING: Removing unreachable block (ram,0x00006b3c)
// WARNING: Removing unreachable block (ram,0x00006b68)
// WARNING: Removing unreachable block (ram,0x00006b48)
// WARNING: Removing unreachable block (ram,0x00006b88)

undefined8 HvxSyscall_55(void)

{
  qword back_chain;
  
  __Save_R12_28_thru_31();
  return 0xffffffffc8000040;
}



undefined8 HvxSyscall_57(QWORD param_1)

{
  int iVar1;
  int in_r2;
  undefined8 uVar2;
  qword back_chain;
  qword local_8;
  
  iVar1 = (int)*(undefined8 *)(&0x16628 + in_r2);
  if (*(char *)(iVar1 + 0x18) == '\0') {
    uVar2 = 0xffffffffc8000040;
  }
  else {
    if ((param_1 & 0xffffffff) < 0x40) {
      if ((*(ushort *)(&0x16a94 + in_r2) & 1) == 0) {
        *(QWORD *)(iVar1 + 0x28) = 1 << (param_1 & 0x7f) | *(QWORD *)(iVar1 + 0x28);
        FUN_0000b138();
      }
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffffffffc8000044;
    }
  }
  return uVar2;
}



undefined8 HvxSyscall_58(void)

{
  int in_r2;
  
  if ((*(ushort *)(&0x16a94 + in_r2) & 1) != 0) {
    return 0;
  }
  if (*(char *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x18) != '\0') {
    return *(undefined8 *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x28);
  }
  return 0xffffffffffffffff;
}



undefined8 HvxSyscall_59(undefined8 param_1)

{
  int in_r2;
  undefined8 uVar1;
  qword back_chain;
  qword local_8;
  
  if (*(char *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x18) == '\0') {
    uVar1 = 0xffffffffc8000040;
  }
  else {
    if ((*(ushort *)(&0x16a94 + in_r2) & 1) == 0) {
      *(undefined8 *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x30) = param_1;
      FUN_0000b138();
    }
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 HvxSyscall_5A(void)

{
  int in_r2;
  
  if ((*(ushort *)(&0x16a94 + in_r2) & 1) != 0) {
    return 0;
  }
  if (*(char *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x18) != '\0') {
    return *(undefined8 *)((int)*(undefined8 *)(&0x16628 + in_r2) + 0x30);
  }
  return 0xffffffffffffffff;
}



undefined8 HvxSyscall_5B(uint param_1)

{
  int iVar1;
  int iVar2;
  int in_r2;
  undefined8 uVar3;
  qword back_chain;
  qword local_8;
  
  iVar1 = (int)*(undefined8 *)(&0x16628 + in_r2);
  if (*(char *)(iVar1 + 0x18) == '\0') {
    uVar3 = 0xffffffffc8000040;
  }
  else {
    if (param_1 < 5) {
      iVar2 = (param_1 + 0xe) * 4;
      *(int *)(iVar2 + iVar1) = *(int *)(iVar2 + iVar1) + 1;
      FUN_0000b138();
      uVar3 = 0;
    }
    else {
      uVar3 = 0xffffffffc8000045;
    }
  }
  return uVar3;
}



undefined8 HvxSyscall_5C(void)

{
  int in_r2;
  
  return *(undefined8 *)(&0x16618 + in_r2);
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 HvxSyscall_5D(QWORD param_1,int param_2)

{
  int in_r2;
  int iVar1;
  QWORD uVar2;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if ((param_1 & 0xffffffff) < 3) {
    uVar2 = 1 << (param_1 & 0x7f);
    if (param_2 == 0) {
      uVar2 = *(QWORD *)(&0x16618 + in_r2) & ~uVar2;
    }
    else {
      uVar2 = uVar2 | *(QWORD *)(&0x16618 + in_r2);
    }
    *(QWORD *)(&0x16618 + in_r2) = uVar2;
  }
  iVar1 = in_r2;
  HvpAquireSpinLock(&0x162c4 + in_r2);
  *(undefined8 *)((int)*(undefined8 *)(&0x162d0 + iVar1) + 0x678) =
       *(undefined8 *)(&0x16618 + in_r2);
  HvpReleaseSpinLock(&0x162c4 + in_r2);
  return 0;
}



// WARNING: Removing unreachable block (ram,0x00007340)
// WARNING: Heritage AFTER dead removal. Example location: s0xfffffc50 : 0x00006f64
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_00006e68(void)

{
  undefined uVar1;
  int iVar2;
  QWORD in_r2;
  uint uVar3;
  ushort *puVar4;
  int iVar5;
  uint uVar6;
  word *pwVar7;
  undefined8 uVar8;
  QWORD lVar9;
  undefined *puVar10;
  QWORD uVar11;
  ushort *puVar12;
  QWORD unaff_r19;
  QWORD unaff_r21;
  word *pwVar13;
  QWORD uVar14;
  QWORD lVar15;
  QWORD lVar16;
  qword back_chain;
  qword local_3c0;
  dword local_3b4;
  word local_3b0;
  dword local_3a4;
  word local_3a0;
  word local_390;
  word local_280;
  word local_170;
  dword local_168;
  word local_f0;
  word local_e0;
  word local_d0;
  word local_b0;
  word local_a0;
  word local_90;
  dword local_7c;
  
  puVar4 = (ushort *)__Save_R12_18_thru_31();
  uVar6 = *(uint *)((int)in_r2 + 0x10000);
  lVar16 = in_r2;
  memcpy(&local_390,ZEXT48(&0x16400) + in_r2,0x110);
  pwVar13 = &local_a0;
  lVar9 = ZEXT48(&0x163f0) + in_r2;
  lVar15 = 0x10;
  do {
    puVar10 = (undefined *)lVar9;
    lVar9 = lVar9 + 1;
    *(undefined *)pwVar13 = *puVar10;
    pwVar13 = (word *)((int)pwVar13 + 1);
    lVar15 = lVar15 + -1;
  } while (lVar15 != 0);
  pwVar13 = &local_e0;
  in_r2 = ZEXT48(&0x163e6) + in_r2;
  lVar9 = 10;
  do {
    puVar10 = (undefined *)in_r2;
    in_r2 = in_r2 + 1;
    *(undefined *)pwVar13 = *puVar10;
    pwVar13 = (word *)((int)pwVar13 + 1);
    lVar9 = lVar9 + -1;
  } while (lVar9 != 0);
  pwVar13 = (word *)0x0;
  lVar9 = HvpGetFlashBase();
  CopyBy64(&local_170,lVar9,0x10);
  uVar11 = (QWORD)local_168;
  if (((uVar11 != (uVar11 + 0xf & 0xfffffffffffffff0)) ||
      (unaff_r21 = 0x7ffff7f, 0x7ffff7f < uVar11 - 0x80)) ||
     (unaff_r19 = 0x8000000, 0x8000000 - uVar11 < 0x11)) {
    _v_MACHINE_CHECK_0();
  }
  CopyBy64(&local_3b0,uVar11 + lVar9,2);
  if ((local_3b0 & 0xf0f) != 0x302) {
    _v_MACHINE_CHECK_0();
  }
  uVar3 = local_3a4 + 0xf & 0xfffffff0;
  uVar14 = (QWORD)uVar3;
  if (((uVar11 != (uVar11 + 0xf & 0xfffffffffffffff0)) || (unaff_r21 < uVar11 - 0x80)) ||
     ((unaff_r19 - uVar11 <= (QWORD)uVar3 || (0x10000 < local_3a4)))) {
LAB_0000730c:
    _v_MACHINE_CHECK_0();
    if (*(char *)((int)*(undefined8 *)(&0x163c0 + (int)lVar16) + 0x18) != '\0') {
      if (*(char *)((int)*(undefined8 *)(&0x163c0 + (int)lVar16) + 0x18) == '\0') {
        uVar6 = 0x200;
        uVar8 = 8;
      }
      else {
        uVar6 = 0;
        uVar8 = 0x208;
      }
      uVar3 = __Save_R12_29_thru_31(uVar8);
      iVar2 = (int)lVar16;
      HvpAquireSpinLock(ZEXT48(&0x1665c) + lVar16);
      DWORD_00000030 = (uVar3 | 0x21281d3) & ~uVar6;
                    // WARNING: Read-only address (ram,0x00000030) is written
      if (*(QWORD *)(&0x162d0 + iVar2) != 0) {
        *(dword *)((int)*(QWORD *)(&0x162d0 + iVar2) + 0x610) = 0x21281d3;
      }
      HvpReleaseSpinLock(ZEXT48(&0x1665c) + lVar16);
      return;
    }
    return;
  }
  CopyBy64(puVar4,uVar11 + lVar9,(QWORD)(uVar3 >> 3));
  iVar2 = (int)lVar16;
  if ((*puVar4 & 0xf0) == 0x40) {
    pwVar7 = (word *)0x0;
    uVar8 = 0;
  }
  else {
    if ((*puVar4 & 0xf0) != 0x60) {
      _v_MACHINE_CHECK_0();
      goto LAB_0000730c;
    }
    uVar8 = 0x10;
    pwVar7 = (word *)&0x00020;
    if ((puVar4[3] & 0x8000) == 0) {
      pwVar7 = &local_b0;
    }
  }
  j_XeCryptHmacSha(&local_a0,0x10,puVar4 + 8,0x10,pwVar7,uVar8,0,0);
  j_XeCryptRc4Key(&local_280,&local_f0,0x10);
  j_XeCryptRc4Ecb(&local_280,puVar4 + 0x10,uVar14 - 0x20);
  j_XeCryptRotSumSha(puVar4,0x10,puVar4 + 0xa0,uVar14 - 0x140,&local_d0,0x14);
  iVar5 = j_XeCryptBnQwBeSigVerify(puVar4 + 0x20,&local_d0,&local_e0,&local_390);
  if (iVar5 == 0) {
    _v_MACHINE_CHECK_0();
  }
  if ((puVar4[3] & 0x800) != 0) {
    if ((puVar4[3] & 0x1000) == 0) {
      uVar8 = 0;
    }
    else {
      pwVar13 = &local_3a0;
      uVar8 = 0x10;
    }
    puVar12 = puVar4 + 0x1ce;
    pwVar7 = &local_90;
    lVar16 = 0x14;
    do {
      uVar1 = *(undefined *)puVar12;
      puVar12 = (ushort *)((int)puVar12 + 1);
      *(undefined *)pwVar7 = uVar1;
      pwVar7 = (word *)((int)pwVar7 + 1);
      lVar16 = lVar16 + -1;
    } while (lVar16 != 0);
    uVar11 = uVar14 + uVar11 & 0xffffffff;
    if (((uVar11 != (uVar11 + 0xf & 0xfffffffffffffff0)) || (unaff_r21 < uVar11 - 0x80)) ||
       (unaff_r19 - uVar11 < 0x11)) {
      _v_MACHINE_CHECK_0();
    }
    CopyBy64(&local_3b0,uVar11 + lVar9,2);
    if ((local_3b0 & 0xf0f) != 0x302) {
      _v_MACHINE_CHECK_0();
    }
    uVar3 = local_3a4 + 0xf & 0xfffffff0;
    if ((((uVar11 == (uVar11 + 0xf & 0xfffffffffffffff0)) && (uVar11 - 0x80 <= unaff_r21)) &&
        ((QWORD)uVar3 < unaff_r19 - uVar11)) && (local_3a4 < &0x10001)) {
      CopyBy64(puVar4,uVar11 + lVar9,(QWORD)(uVar3 >> 3));
      if ((local_3b0 & 0xf000) == 0x4000) {
        pwVar7 = (word *)&0x00020;
      }
      else {
        pwVar7 = &local_b0;
      }
      j_XeCryptHmacSha(&local_f0,0x10,puVar4 + 8,0x10,pwVar7,0x10,pwVar13,uVar8);
      j_XeCryptRc4Key(&local_280,&local_f0,0x10);
      j_XeCryptRc4Ecb(&local_280,puVar4 + 0x10,(QWORD)uVar3 - 0x20);
      j_XeCryptRotSumSha(puVar4,0x10,puVar4 + 0xa0,(QWORD)uVar3 - 0x140,&local_d0,0x14);
      iVar5 = J_XeCryptMemDiff(&local_90,&local_d0,0x14);
      if (iVar5 == 0) goto LAB_0000727c;
      _v_MACHINE_CHECK_0();
    }
    _v_MACHINE_CHECK_0();
  }
LAB_0000727c:
  if (((&0x16615)[iVar2] != '\0') || (0x74b < puVar4[1])) {
    if (*(char *)(puVar4 + 0x1d8) != (&0x16615)[iVar2]) {
      _v_MACHINE_CHECK_0();
    }
    uVar11 = (QWORD)*(byte *)((int)puVar4 + 0x3b1);
    if (0x10 < *(byte *)((int)puVar4 + 0x3b1)) {
      _v_MACHINE_CHECK_0();
    }
    if (((uVar11 & 0xffffffff) != 0) &&
       (((QWORD)(uint)(1 << uVar11 - 1) & (QWORD)puVar4[0x1d9]) == 0)) {
      _v_MACHINE_CHECK_0();
    }
    DWORD_00000074 = *(dword *)(puVar4 + 0x1d8);
                    // WARNING: Read-only address (ram,0x00000074) is written
  }
  FUN_00000204((QWORD)uVar6);
                    // WARNING: Read-only address (ram,0x00000030) is written
                    // WARNING: Read-only address (ram,0x00000074) is written
  return;
}



// WARNING: Removing unreachable block (ram,0x00007340)

void FUN_00007310(void)

{
  int iVar1;
  QWORD in_r2;
  uint uVar3;
  undefined8 uVar2;
  uint uVar4;
  
  if (*(char *)((int)*(undefined8 *)(&0x163c0 + (int)in_r2) + 0x18) != '\0') {
    if (*(char *)((int)*(undefined8 *)(&0x163c0 + (int)in_r2) + 0x18) == '\0') {
      uVar4 = 0x200;
      uVar2 = 8;
    }
    else {
      uVar4 = 0;
      uVar2 = 0x208;
    }
    uVar3 = __Save_R12_29_thru_31(uVar2);
    iVar1 = (int)in_r2;
    HvpAquireSpinLock(ZEXT48(&0x1665c) + in_r2);
    DWORD_00000030 = (uVar3 | 0x21281d3) & ~uVar4;
                    // WARNING: Read-only address (ram,0x00000030) is written
    if (*(QWORD *)(&0x162d0 + iVar1) != 0) {
      *(dword *)((int)*(QWORD *)(&0x162d0 + iVar1) + 0x610) = 0x21281d3;
    }
    HvpReleaseSpinLock(ZEXT48(&0x1665c) + in_r2);
    return;
  }
  DWORD_00000030 = 0x21281d3;
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

QWORD FUN_000073c0(int param_1)

{
  int in_r2;
  undefined8 uVar1;
  undefined8 uVar2;
  byte bVar3;
  QWORD lVar4;
  byte *pbVar5;
  uint uVar6;
  QWORD uVar7;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  uVar7 = 0;
  if (param_1 != 0) {
    do {
      bVar3 = 0;
      if ((*(uint *)(&0x10ec0 + (int)((uVar7 & 0xffffffff) << 2) + in_r2) & 0x80000000) == 0) {
        uVar6 = *(uint *)(&0x10ec0 + (int)((uVar7 & 0xffffffff) << 2) + in_r2) & 0xffff;
        lVar4 = (QWORD)*(ushort *)(&0x10e48 + (int)((uVar7 & 0xffffffff) << 1) + in_r2) +
                *(QWORD *)(&0x163c0 + in_r2) + 0x18;
        while (uVar6 != 0) {
          pbVar5 = (byte *)lVar4;
          uVar6 = uVar6 - 1;
          lVar4 = lVar4 + 1;
          bVar3 = *pbVar5 | bVar3;
        }
        if (bVar3 == 0) break;
      }
      uVar7 = uVar7 + 1;
    } while ((uVar7 & 0xffffffff) < 0x39);
    if (0x38 < (uVar7 & 0xffffffff)) {
      uVar2 = 0;
      uVar1 = 0x80;
      goto LAB_00007474;
    }
  }
  uVar2 = 0x80;
  uVar1 = 0;
LAB_00007474:
  FUN_00003830(uVar1,uVar2);
  FUN_00007310();
  return uVar7;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00007498(QWORD param_1)

{
  uint uVar1;
  QWORD in_r2;
  undefined8 uVar2;
  qword back_chain;
  word local_30;
  dword local_1c;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  FUN_00003620(param_1,&local_30,0x14);
  uVar2 = FUN_000038d8(&local_30,param_1 + 0x1df8,ZEXT48(&0x11318) + in_r2);
  FUN_00000204((QWORD)uVar1);
  return uVar2;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00007500(undefined8 param_1,undefined8 param_2)

{
  undefined *puVar1;
  QWORD in_r2;
  undefined8 uVar2;
  int iVar3;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  FUN_00003830(0,0x100000);
  uVar2 = HvpGetSocMMIORegs(0);
  j_XeCryptSha(uVar2,0x5c00,0,0,0,0,param_1,param_2);
  if (*(QWORD *)(&0x16aa0 + (int)in_r2) < 0x710700) {
    puVar1 = &0x11bc4;
  }
  else {
    puVar1 = &0x11bb0;
  }
  iVar3 = J_XeCryptMemDiff(param_1,ZEXT48(puVar1) + in_r2,param_2);
  if (iVar3 == 0) {
    FUN_00003830(0x100000,0);
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00007668)

undefined8 FUN_000075b8(QWORD param_1,QWORD param_2,int param_3)

{
  int in_r2;
  QWORD uVar1;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  param_2 = param_2 & 0xffffffff;
  if (((param_2 == (param_2 + 0xf & 0xfffffffffffffff0)) && (param_2 - 0x80 < 0x7ffff80)) &&
     (0x4000 < 0x8000000 - param_2)) {
    CopyBy64(param_3,param_2 + param_1,0x800);
    uVar1 = FUN_00003760(param_3);
    if ((uVar1 & 0xffffffff) != 0) {
      if (((&0x16615)[in_r2] == '\0') && ((*(byte *)(param_3 + 0x1a) & 4) != 0)) {
        WORD_00000006 = 0xd83e;
                    // WARNING: Read-only address (ram,0x00000006) is written
      }
      return 1;
                    // WARNING: Read-only address (ram,0x00000006) is written
    }
  }
                    // WARNING: Read-only address (ram,0x00000006) is written
  return 0;
}



// WARNING: Removing unreachable block (ram,0x00007700)
// WARNING: Removing unreachable block (ram,0x00007738)
// WARNING: Removing unreachable block (ram,0x00007748)
// WARNING: Removing unreachable block (ram,0x00007758)
// WARNING: Removing unreachable block (ram,0x00007768)
// WARNING: Removing unreachable block (ram,0x00007774)
// WARNING: Removing unreachable block (ram,0x00007778)
// WARNING: Removing unreachable block (ram,0x00007780)
// WARNING: Removing unreachable block (ram,0x00007790)
// WARNING: Removing unreachable block (ram,0x0000779c)
// WARNING: Removing unreachable block (ram,0x000077bc)
// WARNING: Removing unreachable block (ram,0x000077cc)
// WARNING: Removing unreachable block (ram,0x000077d8)
// WARNING: Removing unreachable block (ram,0x000077e4)
// WARNING: Removing unreachable block (ram,0x000077f0)
// WARNING: Removing unreachable block (ram,0x000077f8)
// WARNING: Removing unreachable block (ram,0x00007804)
// WARNING: Removing unreachable block (ram,0x00007808)
// WARNING: Removing unreachable block (ram,0x00007824)
// WARNING: Removing unreachable block (ram,0x0000781c)
// WARNING: Removing unreachable block (ram,0x00007830)
// WARNING: Removing unreachable block (ram,0x00007834)
// WARNING: Removing unreachable block (ram,0x00007840)
// WARNING: Removing unreachable block (ram,0x0000784c)
// WARNING: Removing unreachable block (ram,0x00007868)
// WARNING: Removing unreachable block (ram,0x00007870)
// WARNING: Removing unreachable block (ram,0x00007858)
// WARNING: Removing unreachable block (ram,0x0000788c)
// WARNING: Removing unreachable block (ram,0x00007890)
// WARNING: Removing unreachable block (ram,0x000078b0)
// WARNING: Removing unreachable block (ram,0x000078cc)
// WARNING: Removing unreachable block (ram,0x00007910)
// WARNING: Removing unreachable block (ram,0x000078e8)
// WARNING: Removing unreachable block (ram,0x0000792c)

undefined8 HvxKeysGetStatus(void)

{
  QWORD in_r2;
  undefined8 uVar1;
  qword back_chain;
  qword local_40;
  dword local_34;
  qword local_30;
  
  uVar1 = __Save_R12_29_thru_31();
  HvpAquireSpinLock(ZEXT48(&0x16a98) + in_r2);
  uVar1 = HvpRelocatePhysicalToProtected(uVar1,0x10000,0x3a);
  FUN_00006e68();
  HvpZeroCacheLines(uVar1,0x200);
  FUN_000034b8(uVar1,0x10000,0x3a);
  FUN_0000b130(0);
  HvpReleaseSpinLock(ZEXT48(&0x16a98) + in_r2);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00007a70)

undefined8 HvxKeysSaveKeyVault(undefined8 param_1,int param_2)

{
  uint uVar1;
  QWORD in_r2;
  undefined8 uVar2;
  QWORD uVar3;
  QWORD lVar4;
  qword back_chain;
  word local_120;
  dword local_20;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if (param_2 == 0x100) {
    uVar2 = HvpPhysicalToReal(param_1,0x100);
    memcpy(&local_120,uVar2,0x100);
    lVar4 = ZEXT48(&0x16640) + in_r2;
    uVar3 = FUN_000038d8(lVar4,&local_120,ZEXT48(&0x11208) + in_r2);
    if (((uVar3 & 0xffffffff) == 0) &&
       ((*(int *)(&0x109c8 + (int)in_r2) != 0x20 ||
        (uVar3 = FUN_000038d8(lVar4,&local_120,ZEXT48(&0x109c8) + in_r2),
        (uVar3 & 0xffffffff) == 0)))) {
      FUN_00000204((QWORD)uVar1);
      uVar2 = 0xffffffffc8000005;
    }
    else {
      FUN_00003830(4,0);
      FUN_00007310();
      FUN_0000b138();
      FUN_00000204((QWORD)uVar1);
      uVar2 = 0;
    }
  }
  else {
    FUN_00000204((QWORD)uVar1);
    uVar2 = 0xffffffffc8000004;
  }
  return uVar2;
}



// WARNING: Removing unreachable block (ram,0x00007b4c)
// WARNING: Removing unreachable block (ram,0x00007c80)
// WARNING: Removing unreachable block (ram,0x00007c88)
// WARNING: Removing unreachable block (ram,0x00007c94)
// WARNING: Removing unreachable block (ram,0x00007b64)
// WARNING: Removing unreachable block (ram,0x00007b78)
// WARNING: Removing unreachable block (ram,0x00007c74)
// WARNING: Removing unreachable block (ram,0x00007cb0)
// WARNING: Removing unreachable block (ram,0x00007b80)
// WARNING: Removing unreachable block (ram,0x00007b8c)
// WARNING: Removing unreachable block (ram,0x00007b9c)
// WARNING: Removing unreachable block (ram,0x00007ba8)
// WARNING: Removing unreachable block (ram,0x00007b6c)
// WARNING: Removing unreachable block (ram,0x00007bb8)
// WARNING: Removing unreachable block (ram,0x00007bc8)
// WARNING: Removing unreachable block (ram,0x00007bd4)
// WARNING: Removing unreachable block (ram,0x00007be4)
// WARNING: Removing unreachable block (ram,0x00007bfc)
// WARNING: Removing unreachable block (ram,0x00007c14)
// WARNING: Removing unreachable block (ram,0x00007c30)
// WARNING: Removing unreachable block (ram,0x00007c40)
// WARNING: Removing unreachable block (ram,0x00007c60)
// WARNING: Removing unreachable block (ram,0x00007c6c)
// WARNING: Removing unreachable block (ram,0x00007cb8)
// WARNING: Removing unreachable block (ram,0x00007c24)
// WARNING: Removing unreachable block (ram,0x00007da4)

undefined8 HvxKeysGetDigest(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  QWORD in_r2;
  QWORD uVar1;
  undefined8 uVar2;
  qword back_chain;
  
  uVar1 = __Save_R12_26_thru_31();
  if (((uVar1 & 0xffffffff) < 0x39) || ((uVar1 & 0xffffffff) == 0x44)) {
    uVar2 = 0xffffffffc8000002;
  }
  else {
    if ((uVar1 & 0xffffffff) == 0x46) {
      uVar2 = FUN_00003c50(param_2,param_3);
    }
    else {
      if ((uVar1 & 0xffffffff) == 0x47) {
        uVar2 = FUN_00003980(ZEXT48(&0x16600) + in_r2,param_2,param_3);
      }
      else {
        if ((uVar1 & 0xffffffff) == 0x4d) {
          uVar2 = FUN_00003a00(param_2,param_3);
        }
        else {
          if ((uVar1 - 0xe0 & 0xffffffff) < 8) {
            uVar2 = FUN_00003b10(((uVar1 - 0xe0) * 0x10 & 0xffffffff0) +
                                 *(QWORD *)(&0x16630 + (int)in_r2),param_2,param_3);
          }
          else {
            if ((uVar1 & 0xffffffff) == 0xf0) {
              memset(*(undefined8 *)(&0x16630 + (int)in_r2),0,0x80);
              uVar2 = 0;
            }
            else {
              if ((uVar1 - 0x1000 & 0xffffffff) < 0x1000) {
                uVar2 = FUN_0000b148(uVar1 - 0x1000,param_2,param_3);
              }
              else {
                uVar2 = 0xffffffffc8000001;
              }
            }
          }
        }
      }
    }
  }
  return uVar2;
}



// WARNING: Removing unreachable block (ram,0x00007e88)

undefined8 HvxKeysSetFactoryResponse(QWORD param_1)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  uint uVar3;
  qword back_chain;
  qword local_8;
  
  if ((param_1 & 0xffffffff) < 0x39) {
    uVar1 = *(uint *)(&0x10ec0 + (int)((param_1 & 0xffffffff) << 2) + in_r2);
    if (((uVar1 & 0x10000) != 0) && ((uVar1 & 0x100000) != 0)) {
      if ((uVar1 & 0x20000000) == 0) {
        uVar3 = uVar1 & 0x10000000;
      }
      else {
        uVar3 = 0;
      }
      if (uVar3 != 0) {
        J_XeCryptRandom((QWORD)*(ushort *)(&0x10e48 + (int)((param_1 & 0xffffffff) << 1) + in_r2) + *(QWORD *)(&0x163c0 + in_r2) + 0x18,(QWORD)(uVar1 & 0xffff));
        FUN_000073c0(1);
        return 0;
      }
    }
    uVar2 = 0xffffffffc8000002;
  }
  else {
    uVar2 = 0xffffffffc8000001;
  }
  return uVar2;
}



// WARNING: Removing unreachable block (ram,0x00007ee4)
// WARNING: Removing unreachable block (ram,0x00007eec)
// WARNING: Removing unreachable block (ram,0x00007ef4)
// WARNING: Removing unreachable block (ram,0x00007efc)
// WARNING: Removing unreachable block (ram,0x00007f04)

undefined8 HvxKeysRsaPrvCrypt(undefined8 param_1,undefined8 param_2,undefined8 param_3) {
  uint uVar1;
  bool bVar2;
  uint uVar3;
  undefined *puVar4;
  QWORD uVar5;
  QWORD in_r2;
  QWORD uVar6;
  QWORD lVar7;
  uint *puVar9;
  undefined8 uVar8;
  int iVar10;
  uint uVar11;
  QWORD uVar12;
  QWORD uVar13;
  QWORD lVar14;
  ushort *puVar15;
  uint uVar16;
  qword back_chain;
  word local_2a0;
  word local_280;
  word local_270;
  word local_250;
  dword local_50;
  
  uVar5 = ZEXT48(register0x0000000c);
  uVar6 = __Save_R12_24_thru_31();
  iVar10 = (int)in_r2;
  uVar1 = *(uint *)(iVar10 + 0x10000);
  if ((uVar6 & 0xffffffff) < 0x39) {
    uVar16 = *(uint *)(&0x10ec0 + (int)((uVar6 & 0xffffffff) << 2) + iVar10);
    lVar14 = (QWORD)*(ushort *)(&0x10e48 + (int)((uVar6 & 0xffffffff) << 1) + iVar10) +
             *(QWORD *)(&0x163c0 + iVar10) + 0x18;
    goto LAB_00008130;
  }
  if ((uVar6 & 0xffffffff) == 0x39) {
    lVar14 = ZEXT48(&0x108b8) + in_r2;
LAB_00007ff0:
    uVar16 = 0x1010110;
  }
  else {
    if ((uVar6 & 0xffffffff) == 0x3c) {
      lVar14 = ZEXT48(&0x11318) + in_r2;
      goto LAB_00007ff0;
    }
    if ((uVar6 & 0xffffffff) == 0x3d) {
      lVar14 = ZEXT48(&0x110f8) + in_r2;
      goto LAB_00007ff0;
    }
    if ((uVar6 & 0xffffffff) == 0x3a) {
      uVar16 = 0x1010110;
      lVar14 = ZEXT48(&0x10ad8) + in_r2;
    }
    else {
      if ((uVar6 & 0xffffffff) != 0x3b) {
        if ((uVar6 & 0xffffffff) == 0x3e) {
          lVar14 = ZEXT48(&0x11758) + in_r2;
        }
        else {
          if ((uVar6 & 0xffffffff) != 0x3f) {
            if ((uVar6 & 0xffffffff) == 0x40) {
              lVar14 = ZEXT48(&0x11028) + in_r2;
              uVar16 = 0x10100d0;
            }
            else {
              if ((uVar6 & 0xffffffff) == 0x41) {
                uVar16 = 0x1010110;
                lVar14 = ZEXT48(&0x10d18) + in_r2;
              }
              else {
                if ((uVar6 & 0xffffffff) == 0x42) {
                  FUN_0000b0e0(uVar5 - 0x280);
                  lVar14 = uVar5 - 0x280;
                  uVar16 = 0x1010010;
                }
                else {
                  if ((uVar6 & 0xffffffff) == 0x44) {
                    FUN_00003620(*(undefined8 *)(&0x163c0 + iVar10),uVar5 - 0x2a0,0x14);
                    uVar16 = 0x2010000;
                    lVar14 = uVar5 - 0x2a0;
                  }
                  else {
                    if ((uVar6 & 0xffffffff) != 0x45) {
                      if ((uVar6 & 0xffffffff) == 0x48) {
                        lVar14 = FUN_0000b450(*(undefined8 *)(&0x165f0 + iVar10));
                        lVar7 = FUN_0000b450(*(undefined8 *)(&0x165f8 + iVar10));
                        if (((lVar7 + lVar14 & 0xffffffffU) != 0x40) &&
                           ((lVar7 + lVar14 & 0xffffffffU) != 0x80)) {
                          FUN_00000204((QWORD)uVar1);
                          return 0xffffffffc800000e;
                        }
                        lVar14 = ZEXT48(&0x163b0) + in_r2;
                        uVar16 = 0x1140010;
                      }
                      else {
                        if ((uVar6 & 0xffffffff) != 0x49) {
                          if ((uVar6 & 0xffffffff) != 0x4d) {
                            FUN_00000204((QWORD)uVar1);
                            return 0xffffffffc8000001;
                          }
                          lVar14 = ZEXT48(&0x16640) + in_r2;
                          goto LAB_00008128;
                        }
                        lVar14 = ZEXT48(&0x16654) + in_r2;
                        uVar16 = 0x1010004;
                      }
                      goto LAB_00008130;
                    }
                    FUN_00007500(uVar5 - 0x2a0,0x14);
                    lVar14 = uVar5 - 0x2a0;
LAB_00008128:
                    uVar16 = 0x1010000;
                  }
                  uVar16 = uVar16 | 0x14;
                }
              }
            }
            goto LAB_00008130;
          }
          lVar14 = ZEXT48(&0x11428) + in_r2;
        }
        goto LAB_00007ff0;
      }
      uVar16 = 0x1010110;
      lVar14 = ZEXT48(&0x10be8) + in_r2;
    }
  }
LAB_00008130:
  uVar3 = uVar16 & 0xffff;
  uVar13 = (QWORD)uVar3;
  if ((uVar16 & 0x2000000) == 0) {
    uVar11 = uVar16 & 0x1000000;
  }
  else {
    uVar11 = 0;
  }
  if (uVar11 == 0) goto LAB_00008150;
  puVar9 = (uint *)HvpPhysicalToReal(param_3,4);
  uVar12 = (QWORD)*puVar9;
  uVar8 = HvpPhysicalToReal(param_2,uVar12);
  if ((uVar16 & 0x40000) == 0) {
    if ((uVar16 & 0x10000) != 0) {
      if (uVar12 != uVar13) {
        FUN_00000204((QWORD)uVar1);
        return 0xffffffffc8000004;
      }
      goto LAB_00008318;
    }
    if (uVar3 < 2) {
      uVar13 = 0;
      goto LAB_00008318;
    }
    puVar15 = (ushort *)lVar14;
    uVar13 = uVar13 - 2;
    lVar14 = lVar14 + 2;
    if ((QWORD)*puVar15 < (uVar13 & 0xffffffff)) {
      uVar13 = (QWORD)*puVar15;
    }
  }
  else {
    if ((uVar6 & 0xffffffff) == 0x1c) {
      puVar4 = &0x11648;
LAB_000081d4:
      bVar2 = false;
    }
    else {
      if ((uVar6 & 0xffffffff) != 0x48) {
        puVar4 = &0x11208;
        goto LAB_000081d4;
      }
      puVar4 = &0x11868;
      bVar2 = true;
    }
    uVar11 = *(uint *)(ZEXT48(puVar4) + in_r2);
    uVar6 = (QWORD)(uVar11 << 3);
    if (0x1c0 < (uVar6 - 0x40 & 0xffffffff)) {
LAB_00008150:
      FUN_00000204((QWORD)uVar1);
      return 0xffffffffc8000002;
    }
    if (bVar2) {
      J_XeCryptRandom(uVar5 - 0x270,0x14);
      iVar10 = j_HvSetupMemEncryptionKey(lVar14,uVar13,uVar5 - 0x250,0x200,0,uVar5 - 0x270);
      if (iVar10 == 0) goto LAB_00008280;
      FUN_0000b498(uVar5 - 0x250,0x200);
      uVar13 = 0x40;
    }
    else {
      if ((((uVar16 & 0x100000) == 0) || ((uVar16 & 0x10000) == 0)) || (0x14 < uVar3))
      goto LAB_00008150;
      memcpy(uVar5 - 0x2a0,lVar14,uVar13);
      j_XeCryptBnDwLePkcs1Format(uVar5 - 0x2a0,0,uVar5 - 0x250,uVar6);
      uVar13 = (QWORD)(uVar11 & 0x1fffffff);
    }
    j_XeCryptBnQw_SwapDwQwLeBe(uVar5 - 0x250,uVar5 - 0x250,uVar13);
    iVar10 = j_XeCryptBnQwNeRsaPubCrypt(uVar5 - 0x250,uVar5 - 0x250,ZEXT48(puVar4) + in_r2);
    if (iVar10 == 0) {
LAB_00008280:
      FUN_00000204((QWORD)uVar1);
      return 0xffffffffc8000006;
    }
    j_XeCryptBnQw_SwapDwQwLeBe(uVar5 - 0x250,uVar5 - 0x250,(QWORD)(uVar11 & 0x1fffffff));
    lVar14 = uVar5 - 0x250;
    uVar13 = uVar6;
  }
  if (uVar12 < (uVar13 & 0xffffffff)) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc8000003;
  }
LAB_00008318:
  memcpy(uVar8,lVar14,uVar13);
  *puVar9 = (uint)uVar13;
  FUN_00000204((QWORD)uVar1);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_00008388(qword *param_1)

{
  QWORD lVar1;
  uint uVar2;
  int in_r2;
  int iVar3;
  int iVar4;
  QWORD lVar5;
  QWORD uVar6;
  undefined8 uVar7;
  qword back_chain;
  qword local_30;
  qword local_28;
  qword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  iVar3 = HvpGetSocMMIORegs(0x20000);
  iVar4 = 0;
  uVar6 = 0x200;
  do {
    lVar5 = (QWORD)iVar4;
    lVar1 = uVar6 << 3;
    uVar6 = uVar6 + 0x40;
    iVar4 = iVar4 + 1;
    *(undefined8 *)((int)&local_30 + (int)(lVar5 << 3)) = *(undefined8 *)((int)lVar1 + iVar3);
  } while ((uVar6 & 0xffffffff) < 0x300);
  if (param_1 != (qword *)0x0) {
    *param_1 = local_30;
    param_1[1] = local_28;
    param_1[2] = local_20;
    param_1[3] = local_18;
  }
  iVar3 = FUN_0000b450(local_20 | local_30);
  iVar4 = FUN_0000b450(local_18 | local_28);
  uVar2 = iVar4 + iVar3 & 0xff;
  (&0x16614)[in_r2] = (char)uVar2;
  if (uVar2 < 0x40) {
    uVar7 = countLeadingZeros(uVar2);
    iVar3 = ((uint)uVar7 >> 5 & 1 ^ 1) + 1;
  }
  else {
    iVar3 = 0;
  }
  *(int *)(&0x16654 + in_r2) = iVar3;
  return;
}



void FUN_00008478(void)

{
  int in_r2;
  
  (&0x16392)[in_r2] = 0x80;
  (&0x16391)[in_r2] = 0xff;
  (&0x16393)[in_r2] = 0xff;
  (&0x16390)[in_r2] = 0xff;
  return;
}



void FUN_000084a8(undefined8 param_1,int param_2)

{
  if (param_2 != 0) {
    do {
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  instructionSynchronize();
  return;
}


// sub_84E0
void HvpSaveThread(void)
{
  byte bVar1;
  int iVar2;
  int in_r2;
  QWORD uVar3;
  undefined uVar6;
  int iVar4;
  int iVar5;
  int iVar7;
  undefined8 in_DEC;
  undefined4 uVar8;
  undefined8 in_spr088;
  uint uVar9;
  QWORD in_spr131;
  undefined8 in_spr136;
  undefined4 uVar10;
  qword back_chain;
  
  uVar3 = __Save_R12_28_thru_31();
  iVar2 = (int)in_spr131;
  if (*(char *)(iVar2 + 0x81) != '\0') {
    uVar3 = _v_MACHINE_CHECK_0();
  }
  uVar6 = (undefined)uVar3;
  if (2 < (uVar3 & 0xffffffff)) {
    uVar6 = _v_MACHINE_CHECK_0();
  }
  *(undefined *)(iVar2 + 0x82) = uVar6;
  sync(0);
  *(undefined *)(iVar2 + 0x81) = 1;
  sync(0);
  iVar4 = HvpGetSocMMIORegs(0x61000);
  iVar5 = HvpGetSocMMIORegs(0x50000);
  uVar10 = (undefined4)in_spr136;
  uVar9 = (uint)in_spr088;
  uVar8 = (undefined4)in_DEC;
  bVar1 = *(byte *)(iVar2 + 0x80);
  if (bVar1 == 0) {
    iVar7 = 5;
    in_spr131 = in_spr131 + 0xa081;
    do {
      do {
      } while (*(char *)in_spr131 != '\x01');
      iVar7 = iVar7 + -1;
      in_spr131 = in_spr131 + -0x2000;
    } while (iVar7 != 0);
    *(QWORD *)(iVar4 + 0x1a0) = *(QWORD *)(iVar4 + 0x1a0) & 0xfffffffffffffeff;
    eieioOp();
    instructionSynchronize();
    *(undefined8 *)(&0x16360 + in_r2) = *(undefined8 *)(iVar5 + 0x6000);
    *(undefined8 *)(&0x16368 + in_r2) = *(undefined8 *)(iVar5 + 0x6010);
    *(undefined8 *)(&0x16370 + in_r2) = *(undefined8 *)(iVar5 + 0x6020);
    *(undefined8 *)(&0x16378 + in_r2) = *(undefined8 *)(iVar5 + 0x6030);
    *(undefined8 *)(&0x16380 + in_r2) = *(undefined8 *)(iVar5 + 0x6040);
    *(undefined8 *)(iVar5 + 0x6000) = 0;
    eieioOp();
    *(undefined8 *)(iVar5 + 0x6010) = 0;
    eieioOp();
    *(undefined8 *)(iVar5 + 0x6020) = 0;
    eieioOp();
    *(undefined8 *)(iVar5 + 0x6030) = 0;
    eieioOp();
    *(undefined8 *)(iVar5 + 0x6040) = 0;
    eieioOp();
    instructionSynchronize();
    *(undefined8 *)(&0x16388 + in_r2) = *(undefined8 *)(iVar4 + 0x1c8);
    *(undefined8 *)(iVar4 + 0x1c8) = 0;
    eieioOp();
    instructionSynchronize();
    iVar4 = 5;
    do {
      iVar7 = iVar4 * 0x2000 + iVar2;
      if (*(char *)(iVar7 + 0x82) != *(char *)(iVar2 + 0x82)) {
        _v_MACHINE_CHECK_0();
        goto LAB_000086f4;
      }
      *(undefined *)(iVar7 + 0x81) = 2;
      sync(0);
      do {
      } while (*(char *)(iVar7 + 0x81) != '\x03');
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    FUN_000004cc();
    iVar4 = 0x200;
    do {
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    instructionSynchronize();
    iVar4 = 0x180;
    do {
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    instructionSynchronize();
  }
  else {
LAB_000086f4:
    do {
      uVar10 = (undefined4)in_spr136;
      uVar9 = (uint)in_spr088;
      uVar8 = (undefined4)in_DEC;
    } while (*(char *)(iVar2 + 0x81) != '\x02');
  }
  *(undefined8 *)((uint)bVar1 * 0x1000 + iVar5 + 8) = 0x7c;
  eieioOp();
  instructionSynchronize();
  *(undefined4 *)(iVar2 + 0x88) = uVar8;
  if ((*(byte *)(iVar2 + 0x80) & 1) == 0) {
    do {
    } while ((uVar9 & 0x400000) != 0);
    *(undefined4 *)(iVar2 + 0x8c) = uVar10;
  }
  sync(0);
  sync(0);
  instructionSynchronize();
  *(undefined *)(iVar2 + 0x81) = 3;
  sync(0);
  return;
}

void HvpSaveThread(BYTE Reason)
{
	PTHREAD_STATE pThreadState = (PTHREAD_STATE)HSPRG1;
	if(pThreadState->STATE != 0
		|| Reason > 2)
		MACHINE_CHECK();

	pThreadState->REASON = Reason;

	// notify thread 0 that this thread is ready to continue
	pThreadState->STATE = 1;

	// thread 0 handles most of the saving
	if(pThreadState->PID == 0)
	{
		// wait until all threads are ready
		PCPU_STATE pCPU = (PCPU_STATE)pThreadState;
		for(int i = 0;i < 3;i++)
		{
			int CoreNum = 2 - i;

			// virtual first
			while(pCPU->Core[CoreNum].vThread.STATE != 1)
				continue;

			// now hardware
			while(pCPU->Core[CoreNum].hThread.STATE != 1)
				continue;
		}

		_REG_611A0 = _REG_611A0 & 0xFEFF; // ei_is

		PQWORD pqwIrqlState = (PQWORD)0x2000161E0;
		pqwIrqlState[0] = _REG_56000;
		pqwIrqlState[1] = _REG_56010;
		pqwIrqlState[2] = _REG_56020;
		pqwIrqlState[3] = _REG_56030;
		pqwIrqlState[4] = _REG_56040;

		_REG_56000 = 0; // ei
		_REG_56010 = 0; // ei
		_REG_56020 = 0; // ei
		_REG_56030 = 0; // ei
		_REG_56040 = 0; // ei_is

		pqwIrqlState[5] = _REG_611C8;
		_REG_611C8 = 0; // ei_is

		for(int i = 0;i < 3;i++)
		{
			int CoreNum = 2 - i;

			// first virtual threads
			// make sure all threads are being paused for the same reason
			if(pCPU->Core[CoreNum].vThread.REASON != pThreadState->REASON)
				MACHINE_CHECK();

			// notify thread to continue with save
			pCPU->Core[CoreNum].vThread.STATE = 2;

			// wait until thread finished save
			while(pCPU->Core[CoreNum].vThread.STATE != 3)
				continue;

			// hardware threads now
			// make sure all threads are being paused for the same reason
			if(pCPU->Core[CoreNum].hThread.REASON != pThreadState->REASON)
				MACHINE_CHECK();

			// notify thread to continue with save
			pCPU->Core[CoreNum].hThread.STATE = 2; // s

			// wait until thread finished save
			while(pCPU->Core[CoreNum].hThread.STATE != 3)
				continue;
		}

		// flush out the cache without cache flush instructions? might be for the security engine?
		PBYTE pbCurPage = HvpGetCurrentPage();
		QWORD inc = 0;
		for(int i = 0;i < 0x200;i++)
			inc += pbCurPage[i * 0x80];
		// is

		// same thing as above but with the thread states
		pbCurPage = HSPRG1;
		inc = 0;
		for(int i = 0;i < 0x180;i++)
			inc += pbCurPage[i * 0x80];
		// is
	}
	else
	{
		// wait until thread 0 has saved the IRQL stuff
		while(pThreadState->STATE != 2)
			continue;
	}

	// set this thread's irql register to 0x7C
	QWORD IRQLRegs = __REG_50000 + (pThreadState->PID << 12);
	write64(IRQLRegs + 8, 0x7C); // ei_is

	// save this thread's DEC register
	pThreadState->DEC_SAVE = mfspr(SPR_DEC);
	mtspr(SPR_DEC, 0x7FFFFFFF);

	// only cores save the HDEC (cores are even, virtual hw threads are odd)
	if(pThreadState->PID & 1 == 0)
	{
		// wait until this core's virtual thread is asleep ?
		while(mfspr(SPR_CTRL) & 0x400000)
			continue;

		// save the HDEC
		pThreadState->HDEC_SAVE = mfspr(SPR_HDEC);
		mtspr(SPR_HDEC, 0x7FFFFFFF);
	}

	// update this thread's flags in the thread control register
	DWORD TSCR = mfspr(SPR_TSCR); // s
	TSCR &= 0xFF8FFFFF;
	TSCR |= ((~pThreadState->PID) & 1) << 20;
	mtspr(SPR_TSCR, TSCR); // s_is

	// notify thread 0 that this thread has completed it's save
	pThreadState->STATE = 3; // s

	return;
}



// sub_87A8
void HvpRestoreThread(void)
{
  byte bVar1;
  int iVar2;
  int in_r2;
  int iVar3;
  int iVar4;
  int iVar5;
  QWORD lVar6;
  char *pcVar7;
  QWORD in_spr131;
  qword back_chain;
  
  __Save_R12_29_thru_31();
  lVar6 = in_spr131 + 0x81;
  pcVar7 = (char *)lVar6;
  if (*pcVar7 != '\x03') {
    _v_MACHINE_CHECK_0();
  }
  *pcVar7 = '\x04';
  sync(0);
  iVar3 = HvpGetSocMMIORegs(0x61000);
  iVar4 = HvpGetSocMMIORegs(0x50000);
  iVar5 = (int)in_spr131;
  bVar1 = *(byte *)(iVar5 + 0x80);
  iVar2 = (uint)bVar1 * 0x1000 + iVar4;
  if ((bVar1 & 1) == 0) {
    if (bVar1 == 0) {
      *(undefined8 *)(iVar4 + 0x6000) = *(undefined8 *)(&0x16360 + in_r2);
      eieioOp();
      *(undefined8 *)(iVar4 + 0x6010) = *(undefined8 *)(&0x16368 + in_r2);
      eieioOp();
      *(undefined8 *)(iVar4 + 0x6020) = *(undefined8 *)(&0x16370 + in_r2);
      eieioOp();
      *(undefined8 *)(iVar4 + 0x6030) = *(undefined8 *)(&0x16378 + in_r2);
      eieioOp();
      *(undefined8 *)(iVar4 + 0x6040) = *(undefined8 *)(&0x16380 + in_r2);
      eieioOp();
      instructionSynchronize();
      *(undefined8 *)(iVar3 + 0x1c8) = *(undefined8 *)(&0x16388 + in_r2);
      eieioOp();
      instructionSynchronize();
    }
    do {
    } while (*(char *)(iVar5 + 0x2081) != '\x05');
  }
  *(undefined8 *)(iVar2 + 8) = 0;
  eieioOp();
  instructionSynchronize();
  if (*(char *)(iVar5 + 0x80) == '\0') {
    *(undefined8 *)(iVar4 + 0x2008) = 0;
    eieioOp();
    instructionSynchronize();
    *(undefined8 *)(iVar2 + 0x10) = 0x40078;
    eieioOp();
    do {
    } while (*(char *)(iVar5 + 0x4081) != '\x05');
    *(undefined8 *)(iVar4 + 0x4008) = 0;
    eieioOp();
    instructionSynchronize();
    *(undefined8 *)(iVar2 + 0x10) = 0x100078;
    eieioOp();
    do {
    } while (*(char *)(iVar5 + 0x8081) != '\x05');
    *(QWORD *)(iVar3 + 0x1a0) = *(QWORD *)(iVar3 + 0x1a0) | 0x100;
    eieioOp();
    instructionSynchronize();
    iVar5 = 6;
    do {
      iVar5 = iVar5 + -1;
      *(undefined *)lVar6 = 0;
      lVar6 = lVar6 + 0x2000;
    } while (iVar5 != 0);
    sync(0);
  }
  else {
    *pcVar7 = '\x05';
    sync(0);
    do {
    } while (*pcVar7 != '\0');
  }
  return;
}


// sub_87A8
void HvpRestoreThread()
{
	PTHREAD_STATE pThreadState = (PTHREAD_STATE)HSPRG1;

	// make sure the thread had saved
	if(pThreadState->STATE != 3)
		MACHINE_CHECK();

	// update state
	pThreadState->STATE = 4;

	// check if this is a hardware thread
	if(pThreadState->PID & 1 == 0)
	{
		// if this is core 0/thread 0 restore the irql stuff
		if(pThreadState->PID == 0)
		{
			PQWORD pqwIrqlState = (PQWORD)0x2000161E0;
			_REG_56000 = pqwIrqlState[0]; // ei
			_REG_56010 = pqwIrqlState[1]; // ei
			_REG_56020 = pqwIrqlState[2]; // ei
			_REG_56030 = pqwIrqlState[3]; // ei
			_REG_56040 = pqwIrqlState[4]; // ei_is

			_REG_611C8 = pqwIrqlState[5]; // ei_is
		}

		// restore this core's HDEC register
		mtspr(SPR_HDEC, pThreadState->HDEC_SAVE);

		// wake up this core's virtual thread
		QWORD CTRL = mfspr(SPR_CTRL);
		CTRL |= 0xC00000;
		mtspr(SPR_CTRL, CTRL);

		// wait until the virtual thread wakes up
		PPPE_STATE pCore = (PPPE_STATE)pThreadState;
		while(pCore->vThread.STATE != 5)
			continue;
	}

	// restore this thread's DEC register
	mtspr(SPR_DEC, pThreadState->DEC_SAVE);

	// set this thread's irql register to 0
	QWORD IRQLRegs = __REG_50000 + (pThreadState->PID << 12);
	write64(IRQLRegs + 8, 0); // ei_is

	// if this is core 0/thread 0 then finish restores
	if(pThreadState->PID == 0)
	{
		// wake up core 1
		_REG_52008 = 0; // ei_is
		_REG_50010 = 0x40078; // ei

		// wait until core 1 is ready
		PCPU_STATE pCPU = (PCPU_STATE)pThreadState;
		while(pCPU->Core1.hThread.STATE != 5)
			continue;

		// wake up core 2
		_REG_54008 = 0; // ei_is
		_REG_50010 = 0x100078; // ei

		// wait until core 2 is ready
		while(pCPU->Core2.hThread.STATE != 5)
			continue;

		// unknown register
		_REG_611A0 |= 0x100; // ei_is

		// done restoring, notify all threads
		pCPU->Core0.hThread.STATE = 0;
		pCPU->Core0.vThread.STATE = 0;
		pCPU->Core1.hThread.STATE = 0;
		pCPU->Core1.vThread.STATE = 0;
		pCPU->Core2.hThread.STATE = 0;
		pCPU->Core2.vThread.STATE = 0;
		// s
	}
	else
	{
		// notify that this thread is awake
		pThreadState->STATE = 5; // s

		// wait until restore is done
		while(pThreadState->STATE != 0)
			continue;
	}

	// continue where thread left off
	return;
}


//FUN_000089e0
QWORD HvpMakeVID(QWORD param_1,QWORD param_2)

{
  int in_r2;
  
  if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
    if (param_1 < 0x15) {
      param_1 = param_1 + 0x3e;
    }
    param_2 = param_1 + param_2;
    if (param_2 < 0x53) {
      if (param_2 < 0x15) {
        param_2 = 0x15;
      }
      if (param_2 < 0x3e) {
        return param_2;
      }
    }
    else {
      param_2 = 0x52;
    }
    param_2 = param_2 + -0x3e;
  }
  else {
    param_2 = param_1 + param_2;
    if (param_2 < 0x40) {
      if (param_2 < 1) {
        param_2 = 1;
      }
    }
    else {
      param_2 = 0x3f;
    }
  }
  return param_2;
}



QWORD FUN_00008a60(QWORD param_1)

{
  int in_r2;
  QWORD uVar1;
  
  uVar1 = *(QWORD *)(&0x16aa0 + in_r2);
  if (uVar1 < 0x710500) {
    if (uVar1 < 0x710700) {
      if (uVar1 < 0x710900) {
        return param_1;
      }
      goto LAB_00008b08;
    }
  }
  else {
    if (uVar1 < 0x710700) {
      uVar1 = param_1;
      if (param_1 < 0x15) {
        uVar1 = param_1 + 0x3e;
      }
      if (0x24 < uVar1) {
        return param_1;
      }
      return 0x25;
    }
  }
  if (uVar1 < 0x710900) {
    if (uVar1 < 0x710700) {
      uVar1 = param_1;
      if (param_1 < 0x15) {
        uVar1 = param_1 + 0x3e;
      }
      if (0x18 < uVar1) {
        return param_1;
      }
    }
    else {
      if (0x18 < param_1) {
        return param_1;
      }
    }
    return 0x19;
  }
LAB_00008b08:
  if (uVar1 < 0x710700) {
    uVar1 = param_1;
    if (param_1 < 0x15) {
      uVar1 = param_1 + 0x3e;
    }
    if (0x1f < uVar1) {
      return param_1;
    }
  }
  else {
    if (0x1f < param_1) {
      return param_1;
    }
  }
  return 0x20;
}



undefined8 HvxQuiesceProcessor(void)
{
  int in_spr131;
  qword back_chain;
  qword local_8;
  
  if (*(char *)(in_spr131 + 0x80) == '\0') {
    _v_MACHINE_CHECK_0();
  }
  HvpSaveThread();
  HvpSleepThread();
  HvpRestoreThread();
  return 0;
}

QWORD HvxQuiesceProcessor(BYTE Reason)
{
	PTHREAD_STATE pThreadState = (PTHREAD_STATE)HSPRG1;

	// we cannot put thread 0 to sleep, how would we wake up?
	if(pThreadState->PID == 0)
		MACHINE_CHECK();

	HvpSaveThread(Reason);
	HvpSleepThread();
	HvpRestoreThread();

	return 0;
}



// sub_8B80
void HvpSetVRMSpeed(int param_1,int param_2,uint param_3)
{
  QWORD uVar1;
  
  uVar1 = *(QWORD *)(param_1 + 0x188);
  *(undefined8 *)(param_2 + 0x6020) = 0x400;
  eieioOp();
  instructionSynchronize();
  do {
  } while ((*(QWORD *)(param_2 + 0x6020) & 0x2000) != 0);
  *(QWORD *)(param_1 + 0x188) =
       (QWORD)((param_3 & 0x3f) << 8) | 0xff004000 | uVar1 & 0xffffffffffff40f7;
  eieioOp();
  do {
  } while ((*(QWORD *)(param_2 + 0x6020) & 0x2000) == 0);
  *(QWORD *)(param_1 + 0x188) = *(QWORD *)(param_1 + 0x188) | 0x8000;
  eieioOp();
  instructionSynchronize();
  *(undefined8 *)(param_2 + 0x6020) = 0;
  eieioOp();
  instructionSynchronize();
  return;
}

// sub_8B80
void HvpSetVRMSpeed(QWORD add1, QWORD add2, QWORD val)
{
	// NOTE: Ignoring these because the function is always sent the same addresses
	QWORD IRQReg = add2 + 0x6020; // _REG_56020
	QWORD VRMReg = add1 + 0x188; // _REG_61188

	QWORD vrm_config = _REG_61188;
	_REG_56020 = 0x400;

	while(_REG_56020 & 0x2000);

	val = ROTL32(val, 8) & 0xF8003FFF
	val |= 0xFF004000;
	vrm_config &= 0xFFFF40F7;
	vrm_config |= val;
	_REG_61188 = vrm_config;

	while(!(_REG_56020 & 0x2000));

	_REG_61188 = _REG_61188 | 0x8000;

	_REG_56020 = 0;

	return;
}


//FUN_00008c40
QWORD HvpGetCurrentVSpeed(int param_1)
{
  int in_r2;
  QWORD lVar1;
  QWORD uVar2;
  
  if (0x7104ff < *(QWORD *)(&0x16aa0 + in_r2)) {
    lVar1 = countLeadingZeros(*(QWORD *)(param_1 + 0x30) & 0x7fffffffffffffff);
    if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710900) {
      uVar2 = 9 - lVar1;
    }
    else {
      uVar2 = 0xd - lVar1;
    }
    return uVar2 & 0xffffffff;
  }
  return 0;
}

DWORD HvpGetCurrentVSpeed(QWORD reg)
{
	// NOTE: Ignoring this because the function is always sent the same addresses
	QWORD CPUReg = reg + 0x30; // _REG_61030

	if(HvpPVRStore < PVR_500)
		return 0;

	QWORD qwVal = _REG_61030;
	qwVal &= 0x7FFFFFFFFFFFFFFF;

	//cntlzd
	BYTE lz = 0;
	for(int i = 0;i < 64;i++)
	{
		if(qwVal & 0x8000000000000000)
			break;
		qwVal <<= 1;
		lz++;
	}

	if(HvpPVRStore >= PVR_900)
		qwVal = 0xD-lz;
	else
		qwVal = 9-lz;
	return (DWORD)(qwVal & 0xFFFFFFFF);
}


//FUN_00008c90
QWORD HvpGetVSpeed(int param_1,int param_2)

{
  int in_r2;
  int iVar2;
  undefined8 uVar1;
  QWORD uVar3;
  QWORD uVar4;
  qword back_chain;
  qword local_8;
  
  uVar3 = *(QWORD *)(&0x16aa0 + in_r2);
  if (uVar3 < 0x710500) {
    if (uVar3 < 0x710900) {
      return 0;
    }
  }
  else {
    if (uVar3 < 0x710900) {
      if (param_2 == 0) {
        uVar4 = (QWORD)(byte)(&0x16390)[in_r2];
      }
      else {
        if (param_2 == 1) {
          uVar4 = (QWORD)(byte)(&0x16393)[in_r2];
        }
        else {
          uVar4 = (QWORD)(byte)(&0x16391)[in_r2];
        }
      }
      if (uVar4 != 0xff) {
        return uVar4;
      }
      uVar4 = *(QWORD *)(param_1 + 0x188);
      if (uVar3 < 0x710700) {
        if (param_2 == 2) {
          iVar2 = 0x38;
        }
        else {
          uVar3 = uVar4 >> 0x30 & 0x3f;
          iVar2 = (int)uVar3;
          if (param_2 == 1) {
            iVar2 = HvpMakeVID(uVar3,uVar4 >> 0x27 & 0xe);
          }
        }
        return (QWORD)(byte)(&0x11c10)[iVar2 + in_r2];
      }
      return (QWORD)(byte)(&0x11c50)[((uint)(uVar4 >> 0x30) & 0x3f) + in_r2];
    }
  }
  uVar1 = FUN_00008c40();
  return uVar1;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 Syscall_HvxEnableTimeBase(undefined4 param_1)

{
  int iVar1;
  undefined8 uVar2;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  iVar1 = HvpGetSocMMIORegs(0x61000);
  uVar2 = countLeadingZeros(param_1);
  *(QWORD *)(iVar1 + 0x1a0) =
       (QWORD)(((uint)uVar2 >> 5 & 1) << 8) ^ 0x100 |
       *(QWORD *)(iVar1 + 0x1a0) & 0xfffffffffffffeff;
  eieioOp();
  instructionSynchronize();
  return 0;
}


// r3/arg1 = 0x30
// r4/arg2 = 1 ; r26
// r5/arg3 = 5 ; r23
// sub_8E00
// FUN_00008e00
void HvpUpdateVRM(undefined8 param_1,QWORD param_2,QWORD param_3)
{
  int in_r2;
  undefined8 uVar1;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  QWORD *puVar8;
  int iVar9;
  int iVar10;
  QWORD uVar2;
  QWORD uVar3;
  QWORD uVar11;
  QWORD uVar12;
  uint *puVar13;
  QWORD uVar14;
  qword back_chain;
  
  uVar1 = __Save_R12_16_thru_31();
  iVar4 = HvpGetSocMMIORegs(0x60000);
  iVar5 = HvpGetSocMMIORegs(0x61000);
  iVar6 = HvpGetSocMMIORegs(0x50000);
  iVar7 = HvpGetSocMMIORegs(0x30000);
  puVar8 = (QWORD *)HvpGetSocMMIORegs(0x48000);
  iVar9 = HvpGetHostBridgeRegs(0x1020000);
  iVar10 = HvpGetHostBridgeRegs(0x1000000);
  uVar2 = FUN_00008a60(uVar1);
  uVar14 = *(QWORD *)(iVar5 + 0x188);
  if ((0x7106ff < *(QWORD *)(&0x16aa0 + in_r2)) && ((uVar14 & 0x80) == 0)) {
    uVar14 = uVar14 | 0x80;
    *(QWORD *)(iVar5 + 0x188) = uVar14;
    eieioOp();
    instructionSynchronize();
  }
  uVar3 = FUN_00008c40(iVar5);
  if (((param_2 == (uVar14 & 7)) && (uVar2 == (uVar14 >> 8 & 0x3f))) && (param_3 == uVar3)) {
    return;
  }
  *(QWORD *)(iVar4 + 0xb58) = *(QWORD *)(iVar4 + 0xb58) | 0x8000000000000000;
  eieioOp();
  instructionSynchronize();
  *(QWORD *)(iVar5 + 0x50) = *(QWORD *)(iVar5 + 0x50) & 0xfffffffdffffffff;
  eieioOp();
  instructionSynchronize();
  *(QWORD *)(iVar5 + 0x60) = *(QWORD *)(iVar5 + 0x60) | 0x200000000;
  eieioOp();
  instructionSynchronize();
  puVar13 = (uint *)(iVar9 + 4);
  *puVar13 = ((uint)*(byte *)puVar13 | 1) << 0x18 | (uint)*(byte *)(iVar9 + 5) << 0x10 |
             ((uint)*(byte *)(iVar9 + 6) << 0x10) >> 8 | (uint)*(byte *)(iVar9 + 7);
  eieioOp();
  instructionSynchronize();
  Syscall_HvxEnableTimeBase(1);
  Sleep(10000);
  Syscall_HvxEnableTimeBase(0);
  if (param_2 != 1) {
    *(undefined8 *)(iVar7 + 0x20) = 0x2000000000000000;
    eieioOp();
    instructionSynchronize();
    if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
      *puVar8 = *puVar8 & 0xf1ffffffffffffff | 0x100000000000000;
      eieioOp();
    }
    else {
      *(undefined8 *)(iVar7 + 0x7000) = 0xc0f04c000000000;
      eieioOp();
      instructionSynchronize();
      *(undefined4 *)(iVar10 + 0x7000) = 0x3150d;
      eieioOp();
    }
    instructionSynchronize();
  }
  if ((uVar3 < param_3) && (*(QWORD *)(&0x16aa0 + in_r2) - 0x710500U < 0x400)) {
    *(QWORD *)(iVar5 + 0x30) = param_3 << 0x3c;
    eieioOp();
  }
  uVar12 = uVar14 >> 8 & 0x3f;
  if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
    uVar11 = uVar2;
    if (uVar2 < 0x15) {
      uVar11 = uVar2 + 0x3e;
    }
    if (uVar12 < 0x15) {
      uVar12 = uVar12 + 0x3e;
    }
    if (uVar11 < uVar12) {
LAB_000090dc:
      HvpSetVRMSpeed(iVar5,iVar6,uVar2);
      uVar14 = *(QWORD *)(iVar5 + 0x188);
    }
  }
  else {
    if (uVar2 < uVar12) goto LAB_000090dc;
  }
  if ((uVar14 & 7) != param_2) {
    *(undefined8 *)(iVar6 + 0x6020) = 0x1047c;
    eieioOp();
    instructionSynchronize();
    do {
    } while ((*(QWORD *)(iVar6 + 0x6020) & 0x2000) != 0);
    *(undefined8 *)(iVar6 + 8) = 0x78;
    eieioOp();
    instructionSynchronize();
    *(QWORD *)(iVar5 + 0x188) =
         *(QWORD *)(iVar5 + 0x188) & 0xffffffffffff3ff8 | param_2 & 7 | 0xff0008;
    eieioOp();
    HvpSleepThread();
    uVar14 = *(QWORD *)(iVar5 + 0x188) | 0x8000;
    *(QWORD *)(iVar5 + 0x188) = uVar14;
    eieioOp();
    instructionSynchronize();
    *(undefined8 *)(iVar6 + 0x60) = *(undefined8 *)(iVar6 + 0x50);
    eieioOp();
    *(undefined8 *)(iVar6 + 8) = 0x7c;
    eieioOp();
    instructionSynchronize();
    *(undefined8 *)(iVar6 + 0x6020) = 0;
    eieioOp();
    instructionSynchronize();
  }
  uVar12 = uVar14 >> 8 & 0x3f;
  if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
    if (uVar12 < 0x15) {
      uVar12 = uVar12 + 0x3e;
    }
    uVar11 = uVar2;
    if (uVar2 < 0x15) {
      uVar11 = uVar2 + 0x3e;
    }
    if (uVar11 <= uVar12) goto LAB_00009248;
  }
  else {
    if (uVar2 <= uVar12) goto LAB_00009248;
  }
  HvpSetVRMSpeed(iVar5,iVar6,uVar2);
  uVar14 = *(QWORD *)(iVar5 + 0x188);
LAB_00009248:
  if ((param_3 < uVar3) && (*(QWORD *)(&0x16aa0 + in_r2) - 0x710500U < 0x400)) {
    *(QWORD *)(iVar5 + 0x30) = param_3 << 0x3c;
    eieioOp();
  }
  if ((uVar14 & 7) == 1) {
    *(undefined8 *)(iVar7 + 0x10) = 0xdfffffffffffffff;
    eieioOp();
    instructionSynchronize();
    if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
      *puVar8 = *puVar8 & 0xf2ffffffffffffff | 0x200000000000000;
      eieioOp();
    }
    else {
      *(undefined8 *)(iVar7 + 0x7000) = 0x2523040000000000;
      eieioOp();
      instructionSynchronize();
      *(undefined4 *)(iVar10 + 0x7000) = 0x3150d;
      eieioOp();
    }
    instructionSynchronize();
  }
  *(QWORD *)(iVar4 + 0xb58) = *(QWORD *)(iVar4 + 0xb58) & 0x7fffffffffffffff;
  eieioOp();
  instructionSynchronize();
  *puVar13 = ((uint)*(byte *)puVar13 & 0xfffffffe) << 0x18 | (uint)*(byte *)(iVar9 + 5) << 0x10 |
             ((uint)*(byte *)(iVar9 + 6) << 0x10) >> 8 | (uint)*(byte *)(iVar9 + 7);
  eieioOp();
  instructionSynchronize();
  return;
}



// WARNING: Could not reconcile some variable overlaps
QWORD HvxBlowFuses(void)
{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  undefined uVar4;
  int in_r2;
  int iVar5;
  QWORD uVar6;
  int iVar7;
  undefined uVar8;
  undefined8 uVar9;
  QWORD uVar10;
  undefined8 uVar11;
  QWORD uVar12;
  uint uVar13;
  int iVar14;
  QWORD uVar15;
  int in_spr131;
  uint param_1;
  byte bStack00000014;
  qword back_chain;
  qword local_50;
  
  uVar6 = __Save_R12_25_thru_31();
  if (*(char *)(in_spr131 + 0x80) != '\0') {
    _v_MACHINE_CHECK_0();
  }
  HvpSaveThread(0);
  param_1 = (uint)(uVar6 >> 0x20);
  if ((uVar6 & 0x200000000) != 0) {
    (&0x16390)[in_r2] = (byte)(param_1 >> 4) & 0xf;
    (&0x16393)[in_r2] = (byte)(uVar6 >> 0x28) & 0xf;
    (&0x16391)[in_r2] = (byte)(param_1 >> 0xc) & 0xf;
  }
  if (((uVar6 & 0x400000000) != 0) &&
     (bStack00000014 = (byte)(uVar6 >> 0x18), (QWORD)bStack00000014 - 0x79 < 0xf)) {
    (&0x16392)[in_r2] = bStack00000014;
  }
  iVar5 = in_r2;
  iVar7 = HvpGetSocMMIORegs(0x61000);
  uVar10 = *(QWORD *)(iVar7 + 0x188);
  uVar12 = uVar10 >> 0x38 & 0x3f;
  uVar15 = uVar10 >> 0x30 & 0x3f;
  if ((uVar12 == 0) || (uVar12 == 0x3b)) {
    uVar15 = 0x30;
  }
  uVar12 = (QWORD)(param_1 & 1);
  if (((uVar6 & 0x100000000) != 0) ||
     (uVar6 = uVar15, 0x58110011 < *(uint *)(&0x16ab0 + iVar5))) {
    uVar6 = HvpMakeVID(uVar15,(QWORD)(byte)(&0x16392)[in_r2] - 0x80);
  }
  if ((uVar12 & 0xffffffff) == 0) {
    iVar14 = 2;
    if (0x7106ff < *(QWORD *)(&0x16aa0 + iVar5)) {
      iVar14 = 1;
    }
    uVar6 = HvpMakeVID(uVar6,(uVar10 >> 0x28 & 7) * (QWORD)iVar14);
    if ((uVar12 & 0xffffffff) == 0) {
      uVar9 = 1;
      uVar11 = 4;
      goto LAB_000094bc;
    }
  }
  uVar9 = 0;
  uVar11 = 1;
LAB_000094bc:
  uVar9 = FUN_00008c90(iVar7,uVar9);
  HvpUpdateVRM(uVar6,uVar11,uVar9);
  HvpRestoreThread();
  uVar6 = *(QWORD *)(iVar7 + 0x188);
  uVar13 = local_50._0_4_ | 1;
  if ((uVar6 & 7) != 1) {
    uVar13 = local_50._0_4_ & 0xfffffffe;
  }
  bVar1 = (&0x16391)[in_r2];
  bVar2 = (&0x16393)[in_r2];
  bVar3 = (&0x16390)[in_r2];
  uVar4 = (&0x16392)[in_r2];
  uVar8 = FUN_00008c40(iVar7);
  return CONCAT71(CONCAT61(CONCAT51(CONCAT41((((((uint)bVar1 & 0xf) << 4 | (uint)bVar2 & 0xffffff0f)
                                               << 4 | (uint)bVar3 & 0xf) << 3 |
                                             (uint)(uVar6 >> 0x28) & 7) << 1 | uVar13 & 0xffff0001,
                                             uVar4),(char)uVar15),(char)(uVar6 >> 8)),uVar8) &
         0xffffffffffff3fff;
}


// if FuseBitPos != -1, SleepTime is ignored
// sub_9558
// FUN_00009558
undefined8 HvpBurnFuse(undefined8 param_1,QWORD param_2)

{
  int in_r2;
  QWORD uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  qword back_chain;
  
  uVar1 = __Save_R12_24_thru_31();
  iVar2 = HvpGetSocMMIORegs(0x61000);
  iVar3 = HvpGetSocMMIORegs(0x20000);
  iVar4 = 3;
  while( true ) {
    if (0x7106ff < *(QWORD *)(&0x16aa0 + in_r2)) {
      *(QWORD *)(iVar2 + 0x188) = *(QWORD *)(iVar2 + 0x188) & 0xffffffffffffff7f;
      eieioOp();
      instructionSynchronize();
    }
    do {
    } while ((*(QWORD *)(iVar3 + 0x2000) & 0x8000000000000000) != 0);
    *(QWORD *)(iVar3 + 0x2018) = *(QWORD *)(iVar3 + 0x2018) | 0x8000000000000000;
    eieioOp();
    if ((int)uVar1 == -1) {
      if ((param_2 & 0xffffffff) == 0) {
        param_2 = 1;
      }
      if (0xfff < (param_2 & 0xffffffff)) {
        param_2 = 0xfff;
      }
      Syscall_HvxEnableTimeBase(1);
      Sleep(param_2 * 1000);
      Syscall_HvxEnableTimeBase(0);
    }
    else {
      Syscall_HvxEnableTimeBase(1);
      Sleep(1000);
      Syscall_HvxEnableTimeBase(0);
      *(undefined8 *)((int)(uVar1 << 3) + iVar3) = 1;
      eieioOp();
    }
    do {
    } while ((*(QWORD *)(iVar3 + 0x2000) & 0x8000000000000000) != 0);
    *(QWORD *)(iVar3 + 0x2018) = *(QWORD *)(iVar3 + 0x2018) & 0x7fffffffffffffff;
    eieioOp();
    Syscall_HvxEnableTimeBase(1);
    Sleep(2000);
    Syscall_HvxEnableTimeBase(0);
    do {
    } while ((*(QWORD *)(iVar3 + 0x2000) & 0x8000000000000000) != 0);
    if (0x7106ff < *(QWORD *)(&0x16aa0 + in_r2)) {
      *(QWORD *)(iVar2 + 0x188) = *(QWORD *)(iVar2 + 0x188) | 0x80;
      eieioOp();
      instructionSynchronize();
    }
    if ((int)uVar1 == -1) break;
    *(undefined8 *)(iVar3 + 0x2010) = 0x8000000000000000;
    eieioOp();
    do {
    } while ((*(QWORD *)(iVar3 + 0x2000) & 0x8000000000000000) != 0);
    if ((0x8000000000000000U >> (uVar1 & 0x3f) &
        *(QWORD *)((int)((uVar1 & 0xffffffff) << 3) + iVar3)) != 0) {
      return 1;
    }
    iVar4 = iVar4 + -1;
    if (iVar4 < 1) {
      return 0;
    }
  }
  return 1;
}

int HvpBurnFuse(DWORD FuseBitPos, DWORD SleepTime) // sub_9558
{
	QWORD Mask = 0x8000000000000000;
	PFUSE_DEVICE pFuseDev = (PFUSE_DEVICE)__REG_20000;

	for(int i = 0;i < 3;i++)
	{
		if(HvpPVRStore >= PVR_700)
			_REG_61188 = _REG_61188 & -0x81; // ei_is

		// check if device is ready
		while(pFuseDev->SenseState)
			continue;

		// write to device
		pFuseDev->BlowEnable = pFuseDev->BlowEnable | Mask; // ei

		// enter fuse to burn (or not if r3 = -1)
		if(FuseBitPos != -1)
		{
			HvxEnableTimeBase(1);
			HvpDelay(0x3E8);
			HvxEnableTimeBase(0);
			pFuseDev->SoftFuseChain[FuseBitPos] = 1;
		}
		else
		{
			HvxEnableTimeBase(1);
			if(SleepTime > 0xFFF)
				HvpDelay(0xFFF*0x3E8);
			else
				HvpDelay(SleepTime*0x3E8);
			HvxEnableTimeBase(0);
		}

		// check if device is ready
		while(pFuseDev->SenseState)
			continue;

		// write to device
		pFuseDev->BlowEnable = pFuseDev->BlowEnable & 0x7FFFFFFFFFFFFFFF; // ei

		HvxEnableTimeBase(1);
		HvpDelay(0x7D0);
		HvxEnableTimeBase(0);

		// check if device is ready
		while(pFuseDev->SenseState)
			continue;

		if(HvpPVRStore >= PVR_700)
			_REG_61188 = _REG_61188 | 0x80; // ei_is

		// -1 seems like a diagnostic setting
		if(FuseBitPos = -1)
			return 1;

		// write to device at 0x10
		pFuseDev->Precharge = Mask; // ei

		// check if device is ready
		while(pFuseDev->SenseState)
			continue;

		// check if our fuse burned
		QWORD FuseStatus = pFuseDev->SoftFuseChain[FuseBitPos];
		if(FuseStatus & (Mask >> (FuseBitPos & 0x3F)))
			return 1; // success
	}
	return 0;
}


// sub_9738
// WARNING: Removing unreachable block (ram,0x00009844)
undefined8 HvpBurnFuseline01(void)
{
  int in_r2;
  undefined8 uVar1;
  int iVar3;
  QWORD uVar2;
  uint uVar4;
  undefined8 *puVar5;
  QWORD uVar6;
  uint uVar7;
  uint uVar8;
  QWORD lVar9;
  QWORD lVar10;
  qword back_chain;
  word local_b0;
  qword local_a8;
  
  __Save_R12_24_thru_31();
  if ((*(QWORD *)(&0x16aa0 + in_r2) < 0x710900) || (*(int *)(&0x16654 + in_r2) == 0))
  {
    iVar3 = HvpGetSocMMIORegs(0x20000);
    puVar5 = (undefined8 *)&local_b0;
    lVar10 = 0xc;
    do {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
      lVar10 = lVar10 + -1;
    } while (lVar10 != 0);
    uVar6 = 0;
    puVar5 = (undefined8 *)&local_b0;
    do {
      lVar10 = uVar6 << 3;
      uVar6 = uVar6 + 0x40;
      *puVar5 = *(undefined8 *)((int)lVar10 + iVar3);
      puVar5 = puVar5 + 1;
    } while ((uVar6 & 0xffffffff) < 0x300);
    uVar4 = 0;
    uVar6 = local_a8;
    do {
      if (((uVar6 & 0xff) != 0) &&
         ((((uVar6 & 0xf0) != 0 && ((uVar6 & 0xf) != 0)) || ((uVar6 & 0xf) == 0)))) {
        return 2;
      }
      uVar4 = uVar4 + 1;
      uVar6 = uVar6 >> 8;
    } while (uVar4 < 8);
    lVar10 = 0x7f;
    uVar4 = 0;
    do {
      uVar6 = local_a8 & 0xf;
      uVar7 = 0;
      uVar8 = 0;
      do {
        lVar9 = lVar10;
        if ((((uVar6 & 1) == 0) && (uVar2 = HvpBurnFuse(lVar9,0), (uVar2 & 0xffffffff) == 0)) &&
           (uVar7 = uVar7 + 1, 1 < uVar7)) {
          return 3;
        }
        uVar8 = uVar8 + 1;
        uVar6 = uVar6 >> 1;
        lVar10 = lVar9 + -1;
      } while (uVar8 < 4);
      lVar10 = lVar9 + -5;
      uVar4 = uVar4 + 1;
      local_a8 = local_a8 >> 8;
    } while (uVar4 < 8);
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

int HvpBurnFuseline01()
{
	if(HvpPVRStore > PVR_900 && HvpBurnFuseLock != 0)
		return 1;

	QWORD fuses[12] = { 0 };
	for(int i = 0;i < 12;i++)
		fuses[i] = getFuseline(i);

	QWORD fuse = fuses[1];
	PBYTE fusebytes = ((PBYTE)&fuse);
	DWORD bConsoleInfo = *(BYTE*)0x74;
	for(int i = 0;i < 8;i++)
	{
		BYTE curByte = fusebytes[8 - i];
		if(curByte) // devkit/retail line check?
		{
			if((curByte & 0xF0) && (curByte & 0xF))
				return 2;

			BYTE curBit = 0;
			if(curByte & 0xF)
				curBit = 1;
			else 
				curBit = 0;

			if((~bConsoleInfo) & 1 != curBit)
				return 2;
		}

		bConsoleInfo = ROTL32(bConsoleInfo, 1) & 0x7F;
	}

	bConsoleInfo = *(BYTE*)0x74;
	QWORD fuseBitPos = 0x7F;
	fuse = fuses[1];
	for(int i = 0;i < 8;i++)
	{
		BYTE curByte = fusebytes[8 - i];
		if(bConsoleInfo & 1)
		{
			curByte = (curByte >> 4) & 0xF;
			fuseBitPos -= 4;
		}
		else 
			curByte &= 0xF;

		QWORD BurnFail = 0;
		for(int j = 0;j < 4;j++)
		{
			if(curByte & 1)
			{
				if(!HvpBurnFuse(fuseBitPos, 0))
				{
					BurnFail++;
					if(BurnFail > 1)
						return 3;
				}
			}
			fuseBitPos--;
			curByte >>= 1;
		}

		if(!bConsoleInfo & 1)
			fuseBitPos -= 4;

		bConsoleInfo = ROTL32(bConsoleInfo, 1) & 0x7F;
	}
	return 0;
}

// WARNING: Removing unreachable block (ram,0x000099a4)
// WARNING: Removing unreachable block (ram,0x000099c8)
// WARNING: Removing unreachable block (ram,0x000099d4)
// WARNING: Removing unreachable block (ram,0x000099e8)
// WARNING: Removing unreachable block (ram,0x00009a10)
// WARNING: Removing unreachable block (ram,0x000099f4)

// sub_98D8
undefined8 HvpBurnFuseline02_Seq(void)
{
  int in_r2;
  undefined8 uVar1;
  int iVar2;
  undefined8 *puVar4;
  QWORD uVar3;
  QWORD lVar5;
  qword back_chain;
  word local_90;
  qword local_80;
  
  __Save_R12_28_thru_31();
  if ((*(QWORD *)(&0x16aa0 + in_r2) < 0x710900) || (*(int *)(&0x16654 + in_r2) == 0))
  {
    iVar2 = HvpGetSocMMIORegs(0x20000);
    puVar4 = (undefined8 *)&local_90;
    lVar5 = 0xc;
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
      lVar5 = lVar5 + -1;
    } while (lVar5 != 0);
    uVar3 = 0;
    puVar4 = (undefined8 *)&local_90;
    do {
      lVar5 = uVar3 << 3;
      uVar3 = uVar3 + 0x40;
      *puVar4 = *(undefined8 *)((int)lVar5 + iVar2);
      puVar4 = puVar4 + 1;
    } while ((uVar3 & 0xffffffff) < 0x300);
    iVar2 = 0x10;
    do {
      if ((local_80 & 0xf) != 0) break;
      iVar2 = iVar2 + -1;
      local_80 = local_80 >> 4;
    } while (iVar2 != 0);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 5;
    }
  }
  else {
    uVar1 = 4;
  }
  return uVar1;
}


// sub_98D8
int HvpBurnFuseline02_Seq()
{
	if(HvpPVRStore >= PVR_900 && HvpBurnFuseLock != 0)
		return 4;

	QWORD pqwFuses[12] = { 0 };
	for(int i = 0;i < 12;i++)
		pqwFuses[i] = getFuseline(i);

	QWORD qwFuse = pqwFuses[2];
	BYTE FuseBitPos = 16;
	for(int i = 0;i < 16;i++)
	{
		if(qwFuse & 0xF)
			break;

		FuseBitPos--;
		qwFuse >>= 4;
	}

	BYTE ConsoleSequence = read8(0x75);
	if(FuseBitPos > ConsoleSequence)
		return 5;
	if(ConsoleSequence > 16)
		return 5;
	if(!ConsoleSequence)
		return 0;

	FuseBitPos = 0x7F + (ConsoleSequence << 2);
	DWORD LShift = ((16 - ConsoleSequence) << 2) & 0xFFFFFFFF;
	BYTE BurnFail = 0;
	qwFuse = pqwFuses[2] >> LShift;
	for(int i = 0;i < 4;i++)
	{
		if(qwFuse & 1 == 0)
		{
			if(!HvpBurnFuse(FuseBitPos, 0))
			{
				BurnFail++;
				if(BurnFail > 1)
					return 6;
			}
		}
		FuseBitPos--;
		qwFuse >>= 1;
	}
	return 0;
}


undefined8 FUN_00009a28(void)

{
  int in_r2;
  int iVar2;
  QWORD lVar1;
  undefined8 *puVar3;
  QWORD uVar4;
  QWORD uVar5;
  uint uVar6;
  QWORD uVar7;
  QWORD lVar8;
  qword back_chain;
  dword local_b0;
  qword local_a8;
  qword local_a0;
  qword local_98;
  word local_90;
  qword local_78;
  qword local_70;
  qword local_68;
  qword local_60;
  
  __Save_R12_28_thru_31();
  if ((0x7108ff < *(QWORD *)(&0x16aa0 + in_r2)) && (*(int *)(&0x16654 + in_r2) != 0))
  {
    return 7;
  }
  iVar2 = HvpGetSocMMIORegs(0x20000);
  puVar3 = (undefined8 *)&local_90;
  lVar8 = 0xc;
  do {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
    lVar8 = lVar8 + -1;
  } while (lVar8 != 0);
  uVar4 = 0;
  puVar3 = (undefined8 *)&local_90;
  do {
    lVar8 = uVar4 << 3;
    uVar4 = uVar4 + 0x40;
    *puVar3 = *(undefined8 *)((int)lVar8 + iVar2);
    puVar3 = puVar3 + 1;
  } while ((uVar4 & 0xffffffff) < 0x300);
  iVar2 = FUN_0000b500(&local_a0);
  if (-1 < iVar2) {
    lVar8 = FUN_0000b450(local_70 | local_78);
    lVar1 = FUN_0000b450((local_60 | local_68) & 0xffffffffff030000);
    if ((lVar1 + lVar8 & 0xffffffffU) == 0x35) {
      return 0;
    }
  }
  lVar8 = FUN_0000b450();
  lVar1 = FUN_0000b450((local_60 | local_68) & 0xffffffffff030000);
  uVar7 = lVar1 + lVar8;
  uVar4 = uVar7 & 0xffffffff;
  if (0x35 < uVar4) {
    return 8;
  }
  do {
    if (0x34 < uVar4) {
      FUN_0000b508(&local_a0);
      uVar6 = 0;
      uVar4 = 0;
      do {
        uVar7 = 0;
        do {
          uVar5 = (QWORD)((uint)uVar7 & 7);
          if ((((*(byte *)((int)&local_a8 + ((uint)(uVar7 >> 3) & 0x1fffffff)) >> uVar5 & 1) != 0)
              && (uVar5 = HvpBurnFuse((((uint)uVar7 & 0x38) - uVar5) + uVar4 + 199,0),
                 (uVar5 & 0xffffffff) == 0)) && (uVar6 = uVar6 + 1, 3 < uVar6)) {
            return 9;
          }
          uVar7 = uVar7 + 1;
        } while ((uVar7 & 0xffffffff) < 0x40);
        uVar4 = uVar4 + 0x40;
        if (0xff < (uVar4 & 0xffffffff)) {
          return 0;
        }
      } while( true );
    }
    J_XeCryptRandom(&local_b0,4);
    uVar4 = 0x6a - uVar7;
    uVar5 = 0;
    trapWord(6,uVar4,0);
    uVar4 = (QWORD)local_b0 -
            (QWORD)(int)((QWORD)local_b0 / (uVar4 & 0xffffffff)) * (QWORD)(int)uVar4;
    local_b0 = (dword)uVar4;
    do {
      if ((*(byte *)((int)&local_a0 + ((uint)(uVar5 >> 3) & 0x1fffffff)) >>
           (QWORD)((uint)uVar5 & 7) & 1) == 0) {
        if ((uVar4 & 0xffffffff) == 0) goto LAB_00009bb4;
        uVar4 = uVar4 - 1;
        local_b0 = (dword)uVar4;
      }
      uVar5 = uVar5 + 1;
    } while ((uVar5 & 0xffffffff) < 0x6a);
    if ((uVar4 & 0xffffffff) != 0) {
      return 8;
    }
LAB_00009bb4:
    if ((uVar5 & 0xffffffff) == 0x6a) {
      return 8;
    }
    uVar6 = (uint)(uVar5 >> 3) & 0x1fffffff;
    uVar7 = uVar7 + 1;
    uVar4 = uVar7 & 0xffffffff;
    *(byte *)(uVar6 + (int)&local_a0) =
         (byte)(1 << (QWORD)((uint)uVar5 & 7)) ^ *(byte *)(uVar6 + (int)&local_a0);
  } while( true );
}


// sub_9CC8
QWORD HvpBurnFuseline00(void)

{
  int in_r2;
  QWORD uVar1;
  int iVar3;
  QWORD uVar2;
  qword *pqVar4;
  QWORD lVar5;
  qword back_chain;
  qword local_90;
  
  __Save_R12_28_thru_31();
  if ((*(QWORD *)(&0x16aa0 + in_r2) < 0x710900) || (*(int *)(&0x16654 + in_r2) == 0))
  {
    iVar3 = HvpGetSocMMIORegs(0x20000);
    pqVar4 = &local_90;
    lVar5 = 0xc;
    do {
      *pqVar4 = 0;
      pqVar4 = pqVar4 + 1;
      lVar5 = lVar5 + -1;
    } while (lVar5 != 0);
    uVar1 = 0;
    pqVar4 = &local_90;
    do {
      lVar5 = uVar1 << 3;
      uVar1 = uVar1 + 0x40;
      *pqVar4 = *(qword *)((int)lVar5 + iVar3);
      pqVar4 = pqVar4 + 1;
    } while ((uVar1 & 0xffffffff) < 0x300);
    uVar1 = 0;
    lVar5 = 0x3f;
    iVar3 = 0x38;
    do {
      if (((local_90 & 1) == 0) && (uVar2 = HvpBurnFuse(lVar5,0), (uVar2 & 0xffffffff) == 0)) {
        uVar1 = uVar1 + 1;
      }
      iVar3 = iVar3 + -1;
      lVar5 = lVar5 + -1;
      local_90 = local_90 >> 1;
    } while (iVar3 != 0);
    uVar1 = (QWORD)(-(uint)(0xc < uVar1) & 0xc);
  }
  else {
    uVar1 = 10;
  }
  return uVar1;
}



// sub_9DB0
undefined8 HvpBurnFuseline07_Seq(void)
{
  undefined8 in_r2;
  undefined8 uVar1;
  QWORD uVar2;
  int iVar3;
  int iVar4;
  QWORD lVar5;
  qword back_chain;
  
  __Save_R12_29_thru_31();
  iVar4 = (int)in_r2;
  if ((*(QWORD *)(&0x16aa0 + iVar4) < 0x710900) || (*(int *)(&0x16654 + iVar4) == 0))
  {
    if ((byte)(&0x16620)[iVar4] < (byte)(&0x165e4)[iVar4]) {
      iVar3 = 0;
      lVar5 = (QWORD)(byte)(&0x165e4)[iVar4] * 4 + 0x1bf;
      iVar4 = 4;
      do {
        uVar2 = HvpBurnFuse(lVar5,0);
        if ((uVar2 & 0xffffffff) == 0) {
          iVar3 = iVar3 + 1;
        }
        iVar4 = iVar4 + -1;
        lVar5 = lVar5 + -1;
      } while (iVar4 != 0);
      if (iVar3 == 4) {
        return 0x15;
      }
      WORD_00000006 = 0xd81e;
                    // WARNING: Read-only address (ram,0x00000006) is written
      *(undefined2 *)((int)*(undefined8 *)(&0x162d0 + (int)in_r2) + 0x600) = 0xd81e;
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 0x13;
  }
                    // WARNING: Read-only address (ram,0x00000006) is written
  return uVar1;
}



// WARNING: Restarted to delay deadcode elimination for space: stack

QWORD FUN_00009e78(void)

{
  int iVar1;
  QWORD in_r2;
  QWORD uVar2;
  int iVar4;
  QWORD lVar3;
  qword *pqVar5;
  undefined *puVar6;
  QWORD uVar7;
  uint uVar8;
  QWORD lVar9;
  qword back_chain;
  qword local_80;
  qword local_70;
  qword local_68;
  qword local_60;
  qword local_58;
  
  uVar2 = __Save_R12_24_thru_31();
  if (*(QWORD *)(&0x16aa0 + (int)in_r2) < 0x710900) {
    return 0;
  }
  iVar4 = HvpGetSocMMIORegs(0x20000);
  *(QWORD *)(iVar4 + 0x2028) =
       *(QWORD *)(iVar4 + 0x2028) & 0x3fffffffffffffff | 0x4000000000000000;
  FUN_00008388(&local_70);
  iVar1 = (int)in_r2;
  if ((byte)(&0x16614)[iVar1] < 0x41) {
    if (((&0x16614)[iVar1] != 0) && ((uVar2 & 0x8000000) == 0)) {
      lVar3 = 0x17;
      goto LAB_0000a050;
    }
    FUN_00003e80(uVar2);
    pqVar5 = &local_70;
    lVar9 = 0x10;
    lVar3 = ZEXT48(&0x165f0) + in_r2;
    do {
      puVar6 = (undefined *)lVar3;
      lVar3 = lVar3 + 1;
      *(undefined *)pqVar5 = *puVar6;
      pqVar5 = (qword *)((int)pqVar5 + 1);
      lVar9 = lVar9 + -1;
    } while (lVar9 != 0);
    uVar2 = 0;
    do {
      uVar8 = 0;
      uVar7 = 0;
      do {
        if ((*(byte *)((int)&local_80 + (int)(uVar7 >> 3)) >> (QWORD)(uVar8 & 7) & 1) != 0) {
          HvpBurnFuse(((QWORD)(uVar8 & 0x38) - (QWORD)(uVar8 & 7)) + uVar2 + 0x207,0);
        }
        uVar8 = uVar8 + 1;
        uVar7 = uVar7 + 1;
      } while (uVar8 < 0x40);
      uVar2 = uVar2 + 0x40;
    } while ((uVar2 & 0xffffffff) < 0x100);
    FUN_00008388(&local_70);
    if ((*(QWORD *)(ZEXT48(&0x165f0) + in_r2) != 0) ||
       (*(QWORD *)(&0x165f8 + (int)in_r2) != 0)) {
      uVar2 = 0x200;
      do {
        uVar7 = 0;
        do {
          HvpBurnFuse(uVar2 + uVar7,0);
          uVar7 = uVar7 + 1;
        } while ((uVar7 & 0xffffffff) < 0x40);
        uVar2 = uVar2 + 0x40;
      } while ((uVar2 & 0xffffffff) < 0x300);
      FUN_00008388(&local_70);
      lVar3 = (QWORD)(-(uint)(0x40 < (byte)(&0x16614)[iVar1]) & 0xffffffe8) + 0x18;
      goto LAB_0000a050;
    }
  }
  lVar3 = 0;
LAB_0000a050:
  *(QWORD *)(iVar4 + 0x2028) = *(QWORD *)(iVar4 + 0x2028) & 0x3fffffffffffffff;
  return lVar3;
}


// sub_A068
QWORD HvpBurnFuseline01_ALL(void)
{
  int iVar1;
  undefined8 *puVar2;
  QWORD uVar3;
  QWORD lVar4;
  QWORD lVar5;
  qword back_chain;
  word local_90;
  qword local_88;
  
  __Save_R12_28_thru_31();
  iVar1 = HvpGetSocMMIORegs(0x20000);
  puVar2 = (undefined8 *)&local_90;
  lVar5 = 0xc;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
    lVar5 = lVar5 + -1;
  } while (lVar5 != 0);
  uVar3 = 0;
  puVar2 = (undefined8 *)&local_90;
  do {
    lVar5 = uVar3 << 3;
    uVar3 = uVar3 + 0x40;
    *puVar2 = *(undefined8 *)((int)lVar5 + iVar1);
    puVar2 = puVar2 + 1;
  } while ((uVar3 & 0xffffffff) < 0x300);
  lVar5 = 0;
  lVar4 = 0x7f;
  iVar1 = 0x40;
  do {
    if (((local_88 & 1) == 0) && (uVar3 = HvpBurnFuse(lVar4,0), (uVar3 & 0xffffffff) == 0)) {
      lVar5 = lVar5 + 1;
    }
    iVar1 = iVar1 + -1;
    lVar4 = lVar4 + -1;
    local_88 = local_88 >> 1;
  } while (iVar1 != 0);
  return (QWORD)(-(uint)(lVar5 != 0) & 3);
}

// sub_A068
int HvpBurnFuseline01_ALL()
{
	QWORD pqwFuses[12] = { 0 };
	for(int i = 0;i < 12;i++)
		pqwFuses[i] = getFuseline(i);

	QWORD qwFuse = pqwFuses[1];
	BYTE BurnFail = 0;
	BYTE FuseBitPos = 0x7F;
	for(int i = 0;i < 64;i++)
	{
		if(qwFuse & 1 != 0)
		{
			if(!HvpBurnFuse(FuseBitPos, 0))
				BurnFail++;
		}

		FuseBitPos--;
		qwFuse >>= 1;
	}

	if(BurnFail > 0)
		return -1;
	else
		return 0;
}

// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x0000a408)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_0000a120(void)

{
  byte bVar1;
  int in_r2;
  int iVar3;
  QWORD lVar2;
  QWORD uVar4;
  qword *pqVar5;
  int iVar6;
  undefined uVar8;
  uint uVar7;
  QWORD lVar9;
  qword back_chain;
  qword local_90;
  qword local_88;
  qword local_80;
  qword local_78;
  qword local_70;
  qword local_68;
  qword local_60;
  qword local_58;
  qword local_50;
  qword local_18;
  qword local_10;
  qword local_8;
  
  iVar3 = HvpGetSocMMIORegs(0x20000);
  pqVar5 = &local_80;
  lVar9 = 0xc;
  do {
    *pqVar5 = 0;
    pqVar5 = pqVar5 + 1;
    lVar9 = lVar9 + -1;
  } while (lVar9 != 0);
  iVar6 = 0;
  pqVar5 = &local_80;
  do {
    lVar9 = (QWORD)iVar6;
    iVar6 = iVar6 + 0x40;
    *pqVar5 = *(qword *)((int)(lVar9 << 3) + iVar3);
    pqVar5 = pqVar5 + 1;
  } while (iVar6 < 0x300);
  if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710900) {
    (&0x16614)[in_r2] = 0x80;
    *(undefined4 *)(&0x16654 + in_r2) = 0;
  }
  else {
    *(QWORD *)(iVar3 + 0x2028) =
         *(QWORD *)(iVar3 + 0x2028) & 0x3fffffffffffffff | 0x4000000000000000;
    FUN_00008388(0);
    *(QWORD *)(iVar3 + 0x2028) = *(QWORD *)(iVar3 + 0x2028) & 0x3fffffffffffffff;
  }
  iVar3 = FUN_0000b500(&local_90);
  if (-1 < iVar3) {
    lVar9 = FUN_0000b450(local_60 | local_68);
    lVar2 = FUN_0000b450((local_50 | local_58) & 0xffffffffff030000);
    if ((lVar2 + lVar9 & 0xffffffffU) == 0x35) {
                    // WARNING: Read-only address (ram,0x00000020) is written
      _0x00020 = local_90;
                    // WARNING: Read-only address (ram,0x00000028) is written
      _0x00028 = local_50 | local_58;
    }
  }
  uVar4 = 0;
  lVar9 = 0;
  do {
    if ((local_78 & 0xff) == 0) {
      uVar4 = 0xff;
      break;
    }
    uVar7 = (uint)((local_78 & 0xf0) != 0) << lVar9;
    lVar9 = lVar9 + 1;
    uVar4 = uVar7 | uVar4;
    local_78 = local_78 >> 8;
  } while ((int)lVar9 < 8);
  if (uVar4 == 2) {
    *(ushort *)(&0x16a94 + in_r2) = *(ushort *)(&0x16a94 + in_r2) | 1;
  }
  lVar9 = 0x10;
  do {
    uVar8 = (undefined)lVar9;
    if ((local_70 & 0xf) != 0) break;
    lVar9 = lVar9 + -1;
    uVar8 = (undefined)lVar9;
    local_70 = local_70 >> 4;
  } while (0 < (int)lVar9);
  (&0x163a0)[in_r2] = uVar8;
  iVar3 = 5;
  (&0x16615)[in_r2] = (char)uVar4;
  if ((local_80 & 0x300000000000000) != 0) {
    iVar3 = 1;
  }
  iVar6 = iVar3 + -1;
  uVar7 = 0;
  (&0x16620)[in_r2] = 0;
  (&0x16658)[in_r2] = (char)(iVar3 << 4);
  if (-1 < iVar6) {
    iVar3 = iVar3 + 6;
    do {
      uVar4 = *(QWORD *)((int)&local_80 + (int)((QWORD)iVar3 << 3));
      if (uVar4 != 0) {
        iVar3 = 0x10;
        goto LAB_0000a364;
      }
      iVar6 = iVar6 + -1;
      iVar3 = iVar3 + -1;
    } while (-1 < iVar6);
  }
  goto LAB_0000a390;
  while( true ) {
    iVar3 = iVar3 + -1;
    uVar4 = uVar4 >> 4;
    if (iVar3 < 1) break;
LAB_0000a364:
    if ((uVar4 & 0xf) != 0) break;
  }
  uVar7 = iVar6 * 0x10 + iVar3 & 0xff;
  (&0x16620)[in_r2] = (char)uVar7;
LAB_0000a390:
  iVar3 = in_r2;
  if ((local_80 & 0xffffffffffffff) != 0) {
    FUN_00003830(1,0);
    uVar7 = (uint)(byte)(&0x16620)[in_r2];
  }
  DWORD_00000014 = uVar7 | 0xc81cb400;
                    // WARNING: Read-only address (ram,0x00000014) is written
  bVar1 = (&0x16615)[in_r2];
  uVar4 = (QWORD)bVar1;
  if ((((bVar1 != 1) && (bVar1 != 3)) && (bVar1 != 4)) && ((bVar1 == 0 || (bVar1 == 2)))) {
    _v_MACHINE_CHECK_0();
  }
  if (((*(ushort *)(&0x16a9c + iVar3) & 4) != 0) &&
     ((((uVar4 & 0xffffffff) == 1 || ((uVar4 & 0xffffffff) == 2)) || ((uVar4 & 0xffffffff) == 3))))
  {
    _v_MACHINE_CHECK_0();
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_0000a458(undefined8 param_1)

{
  int iVar2;
  QWORD uVar1;
  QWORD uVar3;
  undefined8 *puVar4;
  int iVar5;
  QWORD lVar6;
  qword back_chain;
  word local_70;
  qword local_68;
  qword local_60;
  qword local_10;
  qword local_8;
  
  iVar2 = HvpGetSocMMIORegs(0x20000);
  puVar4 = (undefined8 *)&local_70;
  lVar6 = 0xc;
  do {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  iVar5 = 0;
  puVar4 = (undefined8 *)&local_70;
  do {
    lVar6 = (QWORD)iVar5;
    iVar5 = iVar5 + 0x40;
    *puVar4 = *(undefined8 *)((int)(lVar6 << 3) + iVar2);
    puVar4 = puVar4 + 1;
  } while (iVar5 < 0x300);
  uVar1 = 0;
  iVar2 = 0x10;
  do {
    uVar3 = local_68 & 0xf000000000000000;
    iVar2 = iVar2 + -1;
    local_68 = local_68 << 4;
    uVar1 = (QWORD)(((uint)uVar1 & 0x7fff) << 1 | (uint)(uVar3 != 0));
  } while (iVar2 != 0);
  uVar3 = 0;
  iVar2 = 0x10;
  do {
    iVar2 = iVar2 + -1;
    uVar3 = (QWORD)(((uint)uVar3 & 0x7fff) << 1) |
            (QWORD)((local_60 & 0xf000000000000000) != 0);
    local_60 = local_60 << 4;
  } while (iVar2 != 0);
  FUN_000004e8(uVar1,uVar3,param_1);
  return;
}



// WARNING: Removing unreachable block (ram,0x0000a780)

QWORD HvxLockL2(void)

{
  dword dVar1;
  int in_r2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar2;
  undefined8 uVar6;
  QWORD lVar7;
  QWORD uVar8;
  QWORD uVar9;
  int in_spr131;
  qword back_chain;
  
  uVar3 = __Save_R12_25_thru_31();
  if (*(char *)(in_spr131 + 0x80) != '\0') {
    uVar3 = _v_MACHINE_CHECK_0();
  }
  dVar1 = uVar3 & 0xdfffffff;
  if ((uVar3 & 0x40000000) != 0) {
    dVar1 = 0;
  }
  if ((dVar1 & 0x10000000) != 0) {
    dVar1 = dVar1 & 0xefffffff;
  }
  iVar4 = HvpGetSocMMIORegs(0x61000);
  iVar5 = HvpGetSocMMIORegs(0x20000);
  HvpSaveThread(1);
  uVar8 = *(QWORD *)(iVar4 + 0x188);
  if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
    uVar6 = 0x38;
  }
  else {
    uVar6 = HvpMakeVID(uVar8 >> 0x30 & 0x3f,
                         (uVar8 >> 0x28 & 7) + (QWORD)(byte)(&0x16392)[in_r2] + -0x80);
  }
  uVar2 = FUN_00008c90(iVar4,2);
  HvpUpdateVRM(uVar6,4,uVar2);
  if (*(QWORD *)(&0x16aa0 + in_r2) < 0x710700) {
    uVar9 = 0x69ff800;
    lVar7 = 0xc2a2619;
  }
  else {
    uVar9 = 0x38910000;
    lVar7 = 0x80e190d;
  }
  *(QWORD *)(iVar5 + 0x2008) = lVar7 << 0x20 | uVar9;
  eieioOp();
  instructionSynchronize();
  uVar9 = 0;
  if ((dVar1 & 0x80) == 0) {
    if ((((((dVar1 & 1) == 0) || (uVar9 = HvpBurnFuseline01(), (uVar9 & 0xffffffff) == 0)) &&
         (((dVar1 & 2) == 0 || (uVar9 = HvpBurnFuseline02_Seq(), (uVar9 & 0xffffffff) == 0)))) &&
        (((dVar1 & 4) == 0 || (uVar9 = FUN_00009a28((QWORD)dVar1), (uVar9 & 0xffffffff) == 0))))
       && (((dVar1 & 8) == 0 || (uVar9 = HvpBurnFuseline00(), (uVar9 & 0xffffffff) == 0)))) {
      if ((dVar1 & 0x10) == 0) {
        if ((dVar1 & 0x20) == 0) {
          if ((((dVar1 & 0x40) == 0) || (uVar9 = HvpBurnFuseline07_Seq(), (uVar9 & 0xffffffff) == 0)) &&
             ((dVar1 & 0x100000) != 0)) {
            uVar9 = FUN_00009e78((QWORD)dVar1);
          }
        }
        else {
          uVar9 = 0x10;
        }
      }
      else {
        uVar9 = 0xd;
      }
    }
  }
  else {
    HvpBurnFuse(0xffffffffffffffff,(QWORD)(dVar1 >> 8 & 0xfff));
  }
  uVar6 = FUN_00008c90(iVar4,(QWORD)((uVar8 & 7) != 1));
  HvpUpdateVRM(uVar8 >> 8 & 0x3f,uVar8 & 7,uVar6);
  if ((dVar1 & 0x80) == 0) {
    FUN_0000a120();
  }
  HvpRestoreThread();
  return uVar9;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_14_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_15_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_16_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_17_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_18_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_19_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_20_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_21_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_22_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_23_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_24_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_25_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_26_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_27_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_28_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_29_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_30_thru_31(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_31_thru_31(void)

{
  qword back_chain;
  qword local_8;
  
  return;
}



void __Rest_R12_lr_14_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_15_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_16_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_17_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_18_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_19_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_20_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_21_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_22_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_23_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_24_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_25_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_26_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_27_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_28_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_29_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_30_thru_31(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_31_thru_31(void)

{
  qword back_chain;
  qword local_8;
  
  return;
}



undefined * memcpy(undefined *param_1,undefined *param_2,uint param_3)

{
  undefined *puVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined8 *puVar6;
  undefined4 *puVar7;
  undefined *puVar8;
  undefined8 *puVar9;
  undefined4 *puVar10;
  QWORD uVar11;
  uint uVar13;
  undefined8 uVar12;
  QWORD uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  int iVar17;
  QWORD lVar18;
  undefined8 *puVar19;
  undefined4 *puVar20;
  undefined *puVar21;
  qword back_chain;
  
  uVar13 = 8 - ((uint)param_1 & 7);
  puVar21 = param_1;
  if (((uint)param_1 & 7) == 0) {
LAB_0000a8c0:
    bVar2 = 0x7f < param_3;
    if (((uint)param_2 & 7) == 4) {
      puVar10 = (undefined4 *)(param_2 + -4);
      if (bVar2) {
        puVar7 = (undefined4 *)(puVar21 + -4);
        uVar13 = 0x80 - ((uint)puVar21 & 0x7f);
        if (((uint)puVar21 & 0x7f) != 0) {
          uVar11 = (QWORD)(uVar13 >> 2);
          param_3 = param_3 - uVar13;
          do {
            puVar10 = puVar10 + 1;
            puVar7 = puVar7 + 1;
            *puVar7 = *puVar10;
            uVar11 = uVar11 - 1;
          } while (uVar11 != 0);
        }
        uVar11 = (QWORD)(param_3 >> 7);
        if (param_3 >> 7 != 0) {
          bVar2 = (param_3 & 0x7f) == 0;
          lVar18 = (QWORD)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
          iVar17 = 4;
          do {
            iVar17 = iVar17 + 0x80;
            lVar18 = lVar18 + -1;
          } while (lVar18 != 0);
          puVar20 = (undefined4 *)((int)puVar10 + (param_3 - iVar17));
          do {
            while( true ) {
              iVar17 = 8;
              do {
                iVar17 = iVar17 + -1;
                uVar3 = puVar10[2];
                uVar4 = puVar10[3];
                puVar7[1] = puVar10[1];
                puVar10 = puVar10 + 4;
                uVar5 = *puVar10;
                puVar7[2] = uVar3;
                puVar7[3] = uVar4;
                puVar7 = puVar7 + 4;
                *puVar7 = uVar5;
              } while (iVar17 != 0);
              if (puVar20 <= puVar10) break;
              uVar11 = uVar11 - 1;
              if (uVar11 == 0) goto LAB_0000aa58;
            }
            if (!bVar2) {
              bVar2 = false;
            }
            uVar11 = uVar11 - 1;
          } while (uVar11 != 0);
        }
      }
      else {
        puVar7 = (undefined4 *)(puVar21 + -4);
      }
LAB_0000aa58:
      uVar13 = param_3 >> 2 & 0x1f;
      uVar14 = (QWORD)uVar13;
      uVar11 = (QWORD)(param_3 & 3);
      if (uVar13 != 0) {
        do {
          puVar10 = puVar10 + 1;
          puVar7 = puVar7 + 1;
          *puVar7 = *puVar10;
          uVar14 = uVar14 - 1;
        } while (uVar14 != 0);
      }
      if ((param_3 & 3) != 0) {
        puVar8 = (undefined *)((int)puVar7 + 3);
        puVar21 = (undefined *)((int)puVar10 + 3);
        do {
          puVar21 = puVar21 + 1;
          puVar8 = puVar8 + 1;
          *puVar8 = *puVar21;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      return param_1;
    }
    if (((uint)param_2 & 7) != 0) {
      param_2 = param_2 + -1;
      if (bVar2) {
        puVar8 = puVar21 + -1;
        iVar17 = 0x80 - ((uint)puVar21 & 0x7f);
        if (((uint)puVar21 & 0x7f) != 0) {
          param_3 = param_3 - iVar17;
          do {
            param_2 = param_2 + 1;
            puVar8 = puVar8 + 1;
            *puVar8 = *param_2;
            iVar17 = iVar17 + -1;
          } while (iVar17 != 0);
        }
        uVar11 = (QWORD)(param_3 >> 7);
        if (param_3 >> 7 != 0) {
          bVar2 = (param_3 & 0x7f) == 0;
          lVar18 = (QWORD)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
          iVar17 = 1;
          do {
            iVar17 = iVar17 + 0x80;
            lVar18 = lVar18 + -1;
          } while (lVar18 != 0);
          puVar21 = param_2 + (param_3 - iVar17);
          do {
            while( true ) {
              iVar17 = 0x20;
              do {
                iVar17 = iVar17 + -1;
                puVar10 = (undefined4 *)(param_2 + 1);
                param_2 = param_2 + 4;
                *(undefined4 *)(puVar8 + 1) = *puVar10;
                puVar8 = puVar8 + 4;
              } while (iVar17 != 0);
              if (puVar21 <= param_2) break;
              uVar11 = uVar11 - 1;
              if (uVar11 == 0) goto LAB_0000ab78;
            }
            if (!bVar2) {
              bVar2 = false;
            }
            uVar11 = uVar11 - 1;
          } while (uVar11 != 0);
        }
      }
      else {
        puVar8 = puVar21 + -1;
      }
LAB_0000ab78:
      uVar11 = (QWORD)(param_3 & 0x7f);
      if ((param_3 & 0x7f) != 0) {
        do {
          param_2 = param_2 + 1;
          puVar8 = puVar8 + 1;
          *puVar8 = *param_2;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      return param_1;
    }
    if (bVar2) {
      puVar6 = (undefined8 *)(puVar21 + -8);
      puVar9 = (undefined8 *)(param_2 + -8);
      uVar13 = 0x80 - ((uint)puVar21 & 0x7f);
      if (((uint)puVar21 & 0x7f) != 0) {
        uVar11 = (QWORD)(uVar13 >> 3);
        param_3 = param_3 - uVar13;
        do {
          puVar9 = puVar9 + 1;
          puVar6 = puVar6 + 1;
          *puVar6 = *puVar9;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      uVar11 = (QWORD)(param_3 >> 7);
      if (param_3 >> 7 != 0) {
        bVar2 = (param_3 & 0x7f) == 0;
        lVar18 = (QWORD)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
        iVar17 = 8;
        do {
          iVar17 = iVar17 + 0x80;
          lVar18 = lVar18 + -1;
        } while (lVar18 != 0);
        puVar19 = (undefined8 *)((int)puVar9 + (param_3 - iVar17));
        do {
          while( true ) {
            uVar15 = puVar9[2];
            uVar16 = puVar9[3];
            puVar6[1] = puVar9[1];
            uVar12 = puVar9[4];
            puVar6[2] = uVar15;
            uVar15 = puVar9[5];
            puVar6[3] = uVar16;
            uVar16 = puVar9[6];
            puVar6[4] = uVar12;
            uVar12 = puVar9[7];
            puVar6[5] = uVar15;
            uVar15 = puVar9[8];
            puVar6[6] = uVar16;
            uVar16 = puVar9[9];
            puVar6[7] = uVar12;
            uVar12 = puVar9[10];
            puVar6[8] = uVar15;
            uVar15 = puVar9[0xb];
            puVar6[9] = uVar16;
            uVar16 = puVar9[0xc];
            puVar6[10] = uVar12;
            uVar12 = puVar9[0xd];
            puVar6[0xb] = uVar15;
            uVar15 = puVar9[0xe];
            puVar6[0xc] = uVar16;
            uVar16 = puVar9[0xf];
            puVar6[0xd] = uVar12;
            puVar9 = puVar9 + 0x10;
            uVar12 = *puVar9;
            puVar6[0xe] = uVar15;
            puVar6[0xf] = uVar16;
            puVar6 = puVar6 + 0x10;
            *puVar6 = uVar12;
            if (puVar19 <= puVar9) break;
            uVar11 = uVar11 - 1;
            if (uVar11 == 0) goto LAB_0000a8e4;
          }
          if (!bVar2) {
            bVar2 = false;
          }
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      goto LAB_0000a8e4;
    }
  }
  else {
    if (uVar13 < param_3) {
      param_3 = param_3 - uVar13;
      puVar8 = param_2 + -1;
      puVar1 = param_1 + -1;
      do {
        puVar21 = puVar1;
        param_2 = puVar8;
        puVar8 = param_2 + 1;
        puVar1 = puVar21 + 1;
        *puVar1 = *puVar8;
        uVar13 = uVar13 - 1;
      } while (uVar13 != 0);
      puVar21 = puVar21 + 2;
      param_2 = param_2 + 2;
      goto LAB_0000a8c0;
    }
  }
  puVar9 = (undefined8 *)(param_2 + -8);
  puVar6 = (undefined8 *)(puVar21 + -8);
LAB_0000a8e4:
  uVar13 = param_3 >> 3 & 0xf;
  uVar14 = (QWORD)uVar13;
  uVar11 = (QWORD)(param_3 & 7);
  if (uVar13 != 0) {
    do {
      puVar9 = puVar9 + 1;
      puVar6 = puVar6 + 1;
      *puVar6 = *puVar9;
      uVar14 = uVar14 - 1;
    } while (uVar14 != 0);
  }
  if ((param_3 & 7) != 0) {
    puVar8 = (undefined *)((int)puVar6 + 7);
    puVar21 = (undefined *)((int)puVar9 + 7);
    do {
      puVar21 = puVar21 + 1;
      puVar8 = puVar8 + 1;
      *puVar8 = *puVar21;
      uVar11 = uVar11 - 1;
    } while (uVar11 != 0);
  }
  return param_1;
}



void _blkmov(undefined4 *param_1,undefined4 *param_2,QWORD param_3)

{
  undefined uVar1;
  undefined4 uVar2;
  uint uVar3;
  QWORD lVar4;
  QWORD uVar5;
  
  lVar4 = param_3 + 1;
  while (lVar4 = lVar4 + -1, lVar4 != 0 && ((uint)param_1 & 3) == 0) {
    param_3 = param_3 - 1;
    uVar1 = *(undefined *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    *(undefined *)param_1 = uVar1;
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  uVar3 = (uint)param_3 >> 2;
  uVar5 = (QWORD)uVar3;
  if (uVar3 != 0) {
    if (((uint)param_2 & 3) == 0) {
      do {
        uVar2 = *param_2;
        param_2 = param_2 + 1;
        *param_1 = uVar2;
        param_1 = param_1 + 1;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
    else {
      do {
        uVar2 = *param_2;
        param_2 = param_2 + 1;
        *param_1 = uVar2;
        param_1 = param_1 + 1;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
  }
  param_3 = param_3 & 3;
  if (param_3 != 0) {
    do {
      uVar1 = *(undefined *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      *(undefined *)param_1 = uVar1;
      param_1 = (undefined4 *)((int)param_1 + 1);
      param_3 = param_3 - 1;
    } while (param_3 != 0);
    return;
  }
  return;
}



void memset(uint *param_1,QWORD param_2,QWORD param_3)

{
  uint uVar1;
  QWORD lVar2;
  QWORD uVar3;
  uint uVar4;
  undefined uVar5;
  uint *puVar6;
  code *UNRECOVERED_JUMPTABLE_00;
  
  lVar2 = param_3 + 1;
  while (lVar2 = lVar2 + -1, lVar2 != 0 && ((uint)param_1 & 3) == 0) {
    param_3 = param_3 - 1;
    *(char *)param_1 = (char)param_2;
    param_1 = (uint *)((int)param_1 + 1);
  }
  uVar4 = ((uint)param_2 & 0xff) << 8;
  uVar1 = (uint)param_3 >> 4;
  uVar3 = (QWORD)uVar1;
  uVar4 = (uVar4 | (uint)param_2 & 0xffff00ff) << 0x10 |
          uVar4 | (uint)(param_2 & 0xffffffff000000ff);
  if (uVar1 != 0) {
    do {
      *param_1 = uVar4;
      param_1[1] = uVar4;
      param_1[2] = uVar4;
      param_1[3] = uVar4;
      param_1 = param_1 + 4;
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
  uVar1 = (uint)param_3 >> 2 & 3;
  puVar6 = param_1;
  if (uVar1 != 0) {
    *param_1 = uVar4;
    puVar6 = param_1 + 1;
    if (uVar1 != 1) {
      *puVar6 = uVar4;
      puVar6 = param_1 + 2;
      if (uVar1 != 2) {
        *puVar6 = uVar4;
        puVar6 = param_1 + 3;
      }
    }
  }
  param_3 = param_3 & 3;
  if (param_3 == 0) {
    return;
  }
  uVar5 = (undefined)(param_2 & 0xffffffff000000ff);
  *(undefined *)puVar6 = uVar5;
                    // WARNING: Could not recover jumptable at 0x0000adac. Too many branches
                    // WARNING: Treating indirect jump as call
  if (param_3 == 1) {
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  *(undefined *)((int)puVar6 + 1) = uVar5;
                    // WARNING: Could not recover jumptable at 0x0000adb4. Too many branches
                    // WARNING: Treating indirect jump as call
  if (param_3 != 2) {
    *(undefined *)((int)puVar6 + 2) = uVar5;
    return;
  }
  (*UNRECOVERED_JUMPTABLE_00)();
  return;
}



undefined4 * FUN_0000adc0(undefined *param_1,undefined *param_2,uint param_3)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined8 *puVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  undefined8 *puVar9;
  undefined4 *puVar10;
  QWORD uVar11;
  uint uVar13;
  undefined8 uVar12;
  QWORD uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  int iVar17;
  QWORD lVar18;
  undefined8 *puVar19;
  undefined4 *puVar20;
  undefined *puVar21;
  
  if (param_1 == param_2) {
    return (undefined4 *)param_1;
  }
  if ((int)param_2 <= (int)param_1) {
    iVar17 = param_3 + 1;
    puVar10 = (undefined4 *)(param_1 + param_3);
    param_2 = param_2 + param_3;
    while (iVar17 = iVar17 + -1, iVar17 != 0 && ((uint)puVar10 & 3) == 0) {
      param_3 = param_3 - 1;
      puVar21 = param_2 + -1;
      param_2 = param_2 + -1;
      *(undefined *)((int)puVar10 + -1) = *puVar21;
      puVar10 = (undefined4 *)((int)puVar10 + -1);
    }
    uVar11 = (QWORD)(param_3 >> 2);
    if (param_3 >> 2 != 0) {
      if (((uint)param_2 & 3) == 0) {
        do {
          puVar8 = (undefined4 *)(param_2 + -4);
          param_2 = param_2 + -4;
          puVar10[-1] = *puVar8;
          puVar10 = puVar10 + -1;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      else {
        do {
          puVar10 = puVar10 + -1;
          puVar8 = (undefined4 *)(param_2 + -4);
          param_2 = param_2 + -4;
          *puVar10 = *puVar8;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
    }
    param_3 = param_3 & 3;
    if (param_3 != 0) {
      do {
        puVar21 = param_2 + -1;
        param_2 = param_2 + -1;
        *(undefined *)((int)puVar10 + -1) = *puVar21;
        puVar10 = (undefined4 *)((int)puVar10 + -1);
        param_3 = param_3 - 1;
      } while (param_3 != 0);
      return puVar10;
    }
    return puVar10;
  }
  uVar13 = 8 - ((uint)param_1 & 7);
  puVar21 = param_1;
  if (((uint)param_1 & 7) == 0) {
LAB_0000a8c0:
    bVar1 = 0x7f < param_3;
    if (((uint)param_2 & 7) == 4) {
      puVar10 = (undefined4 *)(param_2 + -4);
      if (bVar1) {
        puVar8 = (undefined4 *)(puVar21 + -4);
        uVar13 = 0x80 - ((uint)puVar21 & 0x7f);
        if (((uint)puVar21 & 0x7f) != 0) {
          uVar11 = (QWORD)(uVar13 >> 2);
          param_3 = param_3 - uVar13;
          do {
            puVar10 = puVar10 + 1;
            puVar8 = puVar8 + 1;
            *puVar8 = *puVar10;
            uVar11 = uVar11 - 1;
          } while (uVar11 != 0);
        }
        uVar11 = (QWORD)(param_3 >> 7);
        if (param_3 >> 7 != 0) {
          bVar1 = (param_3 & 0x7f) == 0;
          lVar18 = (QWORD)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
          iVar17 = 4;
          do {
            iVar17 = iVar17 + 0x80;
            lVar18 = lVar18 + -1;
          } while (lVar18 != 0);
          puVar20 = (undefined4 *)((int)puVar10 + (param_3 - iVar17));
          do {
            while( true ) {
              iVar17 = 8;
              do {
                iVar17 = iVar17 + -1;
                uVar2 = puVar10[2];
                uVar3 = puVar10[3];
                puVar8[1] = puVar10[1];
                puVar10 = puVar10 + 4;
                uVar4 = *puVar10;
                puVar8[2] = uVar2;
                puVar8[3] = uVar3;
                puVar8 = puVar8 + 4;
                *puVar8 = uVar4;
              } while (iVar17 != 0);
              if (puVar20 <= puVar10) break;
              uVar11 = uVar11 - 1;
              if (uVar11 == 0) goto LAB_0000aa58;
            }
            if (!bVar1) {
              bVar1 = false;
            }
            uVar11 = uVar11 - 1;
          } while (uVar11 != 0);
        }
      }
      else {
        puVar8 = (undefined4 *)(puVar21 + -4);
      }
LAB_0000aa58:
      uVar13 = param_3 >> 2 & 0x1f;
      uVar14 = (QWORD)uVar13;
      uVar11 = (QWORD)(param_3 & 3);
      if (uVar13 != 0) {
        do {
          puVar10 = puVar10 + 1;
          puVar8 = puVar8 + 1;
          *puVar8 = *puVar10;
          uVar14 = uVar14 - 1;
        } while (uVar14 != 0);
      }
      if ((param_3 & 3) != 0) {
        puVar7 = (undefined *)((int)puVar8 + 3);
        puVar21 = (undefined *)((int)puVar10 + 3);
        do {
          puVar21 = puVar21 + 1;
          puVar7 = puVar7 + 1;
          *puVar7 = *puVar21;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      return (undefined4 *)param_1;
    }
    if (((uint)param_2 & 7) != 0) {
      param_2 = param_2 + -1;
      if (bVar1) {
        puVar7 = puVar21 + -1;
        iVar17 = 0x80 - ((uint)puVar21 & 0x7f);
        if (((uint)puVar21 & 0x7f) != 0) {
          param_3 = param_3 - iVar17;
          do {
            param_2 = param_2 + 1;
            puVar7 = puVar7 + 1;
            *puVar7 = *param_2;
            iVar17 = iVar17 + -1;
          } while (iVar17 != 0);
        }
        uVar11 = (QWORD)(param_3 >> 7);
        if (param_3 >> 7 != 0) {
          bVar1 = (param_3 & 0x7f) == 0;
          lVar18 = (QWORD)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
          iVar17 = 1;
          do {
            iVar17 = iVar17 + 0x80;
            lVar18 = lVar18 + -1;
          } while (lVar18 != 0);
          puVar21 = param_2 + (param_3 - iVar17);
          do {
            while( true ) {
              iVar17 = 0x20;
              do {
                iVar17 = iVar17 + -1;
                puVar10 = (undefined4 *)(param_2 + 1);
                param_2 = param_2 + 4;
                *(undefined4 *)(puVar7 + 1) = *puVar10;
                puVar7 = puVar7 + 4;
              } while (iVar17 != 0);
              if (puVar21 <= param_2) break;
              uVar11 = uVar11 - 1;
              if (uVar11 == 0) goto LAB_0000ab78;
            }
            if (!bVar1) {
              bVar1 = false;
            }
            uVar11 = uVar11 - 1;
          } while (uVar11 != 0);
        }
      }
      else {
        puVar7 = puVar21 + -1;
      }
LAB_0000ab78:
      uVar11 = (QWORD)(param_3 & 0x7f);
      if ((param_3 & 0x7f) != 0) {
        do {
          param_2 = param_2 + 1;
          puVar7 = puVar7 + 1;
          *puVar7 = *param_2;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      return (undefined4 *)param_1;
    }
    if (bVar1) {
      puVar6 = (undefined8 *)(puVar21 + -8);
      puVar9 = (undefined8 *)(param_2 + -8);
      uVar13 = 0x80 - ((uint)puVar21 & 0x7f);
      if (((uint)puVar21 & 0x7f) != 0) {
        uVar11 = (QWORD)(uVar13 >> 3);
        param_3 = param_3 - uVar13;
        do {
          puVar9 = puVar9 + 1;
          puVar6 = puVar6 + 1;
          *puVar6 = *puVar9;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      uVar11 = (QWORD)(param_3 >> 7);
      if (param_3 >> 7 != 0) {
        bVar1 = (param_3 & 0x7f) == 0;
        lVar18 = (QWORD)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
        iVar17 = 8;
        do {
          iVar17 = iVar17 + 0x80;
          lVar18 = lVar18 + -1;
        } while (lVar18 != 0);
        puVar19 = (undefined8 *)((int)puVar9 + (param_3 - iVar17));
        do {
          while( true ) {
            uVar15 = puVar9[2];
            uVar16 = puVar9[3];
            puVar6[1] = puVar9[1];
            uVar12 = puVar9[4];
            puVar6[2] = uVar15;
            uVar15 = puVar9[5];
            puVar6[3] = uVar16;
            uVar16 = puVar9[6];
            puVar6[4] = uVar12;
            uVar12 = puVar9[7];
            puVar6[5] = uVar15;
            uVar15 = puVar9[8];
            puVar6[6] = uVar16;
            uVar16 = puVar9[9];
            puVar6[7] = uVar12;
            uVar12 = puVar9[10];
            puVar6[8] = uVar15;
            uVar15 = puVar9[0xb];
            puVar6[9] = uVar16;
            uVar16 = puVar9[0xc];
            puVar6[10] = uVar12;
            uVar12 = puVar9[0xd];
            puVar6[0xb] = uVar15;
            uVar15 = puVar9[0xe];
            puVar6[0xc] = uVar16;
            uVar16 = puVar9[0xf];
            puVar6[0xd] = uVar12;
            puVar9 = puVar9 + 0x10;
            uVar12 = *puVar9;
            puVar6[0xe] = uVar15;
            puVar6[0xf] = uVar16;
            puVar6 = puVar6 + 0x10;
            *puVar6 = uVar12;
            if (puVar19 <= puVar9) break;
            uVar11 = uVar11 - 1;
            if (uVar11 == 0) goto LAB_0000a8e4;
          }
          if (!bVar1) {
            bVar1 = false;
          }
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      goto LAB_0000a8e4;
    }
  }
  else {
    if (uVar13 < param_3) {
      param_3 = param_3 - uVar13;
      puVar7 = param_2 + -1;
      puVar5 = param_1 + -1;
      do {
        puVar21 = puVar5;
        param_2 = puVar7;
        puVar7 = param_2 + 1;
        puVar5 = puVar21 + 1;
        *puVar5 = *puVar7;
        uVar13 = uVar13 - 1;
      } while (uVar13 != 0);
      puVar21 = puVar21 + 2;
      param_2 = param_2 + 2;
      goto LAB_0000a8c0;
    }
  }
  puVar9 = (undefined8 *)(param_2 + -8);
  puVar6 = (undefined8 *)(puVar21 + -8);
LAB_0000a8e4:
  uVar13 = param_3 >> 3 & 0xf;
  uVar14 = (QWORD)uVar13;
  uVar11 = (QWORD)(param_3 & 7);
  if (uVar13 != 0) {
    do {
      puVar9 = puVar9 + 1;
      puVar6 = puVar6 + 1;
      *puVar6 = *puVar9;
      uVar14 = uVar14 - 1;
    } while (uVar14 != 0);
  }
  if ((param_3 & 7) != 0) {
    puVar7 = (undefined *)((int)puVar6 + 7);
    puVar21 = (undefined *)((int)puVar9 + 7);
    do {
      puVar21 = puVar21 + 1;
      puVar7 = puVar7 + 1;
      *puVar7 = *puVar21;
      uVar11 = uVar11 - 1;
    } while (uVar11 != 0);
  }
  return (undefined4 *)param_1;
}



void FUN_0000b0b0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00027ee0();
  return;
}



void FUN_0000b0b8(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00027f08();
  return;
}



void FUN_0000b0c0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00026828();
  return;
}



void FUN_0000b0c8(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029b58();
  return;
}



void FUN_0000b0d0(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x30398)();
  return;
}



void FUN_0000b0e0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002d310();
  return;
}



void FUN_0000b0e8(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029670();
  return;
}



void FUN_0000b0f0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029710();
  return;
}



void FUN_0000b0f8(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029720();
  return;
}



void FUN_0000b100(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002afb8();
  return;
}



void FUN_0000b110(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x309c8)();
  return;
}



void FUN_0000b118(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002dbd8();
  return;
}



void FUN_0000b120(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002db50();
  return;
}



void FUN_0000b128(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002e120();
  return;
}



void FUN_0000b130(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002e2f8();
  return;
}



void FUN_0000b138(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002e4c0();
  return;
}



void FUN_0000b140(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002e800();
  return;
}



void FUN_0000b148(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002e580();
  return;
}



void FUN_0000b150(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x318a8)();
  return;
}



void FUN_0000b158(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x200a8)();
  return;
}



void FUN_0000b160(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x30000)();
  return;
}



void FUN_0000b168(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x30050)();
  return;
}



void j_XeCryptAesCbc(void)
{
                    // WARNING: Treating indirect jump as call
  XeCryptAesCbc();
  return;
}



void j_XeCryptAesEcb(void)
{
                    // WARNING: Treating indirect jump as call
  XeCryptAesEcb();
  return;
}



void j_XeCryptAesKey(void){
                    // WARNING: Treating indirect jump as call
  XeCryptAesKey();
  return;
}



void j_XeCryptAesKeyExpand128(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x23798)();
  return;
}



void j_XeCryptBnDwLePkcs1Format(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnDwLePkcs1Format();
  return;
}



void j_XeCryptBnDwLePkcs1Verify(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnDwLePkcs1Verify();
  return;
}


//b3c0
void j_XeCryptBnQw_SwapDwQwLeBe(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQw_SwapDwQwLeBe();
  return;
}


//0xb3d8
void j_XeCryptBnQwBeSigVerify(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQwBeSigVerify();
  return;
}

//0xb3f8
void j_XeCryptBnQwNeRsaPrvCrypt(void) {
                    // WARNING: Treating indirect jump as call
  XeCryptBnQwNeRsaPrvCrypt();
  return;
}


//0xb400
void j_XeCryptBnQwNeRsaPubCrypt(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQwNeRsaPubCrypt();
  return;
}


//0xb408
void j_XeCryptDes3Cbc(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDes3Cbc();
  return;
}


//b410
void j_XeCryptDes3Ecb(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDes3Ecb();
  return;
}



void FUN_0000b418(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDes3Key();
  return;
}


// 0xb420
void j_XeCryptDesCbc(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDesCbc();
  return;
}


// 0xb428
void j_XeCryptDesEcb(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDesEcb();
  return;
}



void j_XeCryptDesKey(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDesKey();
  return;
}


//0xb438
void j_XeCryptDesParity(void){
                    // WARNING: Treating indirect jump as call
  XeCryptDesParity();
  return;
}



void j_HvSetupMemEncryptionKey(void)

{
                    // WARNING: Treating indirect jump as call
  HvSetupMemEncryptionKey();
  return;
}



void FUN_0000b450(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x226c8)();
  return;
}



void j_XeCryptHmacSha(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptHmacSha();
  return;
}



void j_XeCryptHmacShaFinal(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptHmacShaFinal();
  return;
}



void j_XeCryptHmacShaInit(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptHmacShaInit();
  return;
}



void j_XeCryptHmacShaUpdate(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptHmacShaUpdate();
  return;
}



void J_XeCryptMemDiff(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptMemDiff();
  return;
}


//b498
void FUN_0000b498(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00023b10();
  return;
}



void J_XeCryptRandom(void)
{
                    // WARNING: Treating indirect jump as call
  XeCryptRandom();
  return;
}


//sub_b4a8
void j_XeCryptRc4(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptRc4();
  return;
}



void j_XeCryptRc4Ecb(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptRc4Ecb();
  return;
}



void j_XeCryptRc4Key(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptRc4Key();
  return;
}



void FUN_0000b4c8(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x232f0)();
  return;
}



void j_XeCryptRotSumSha(void) {
                    // WARNING: Treating indirect jump as call
  XeCryptRotSumSha();
  return;
}



void j_XeCryptSha(void) {
                    // WARNING: Treating indirect jump as call
  XeCryptSha();
  return;
}



void j_XeCryptShaFinal(void){
                    // WARNING: Treating indirect jump as call
  XeCryptShaFinal();
  return;
}



void j_XeCryptShaInit(void) {
                    // WARNING: Treating indirect jump as call
  XeCryptShaInit();
  return;
}



void j_XeCryptShaUpdate(void){
                    // WARNING: Treating indirect jump as call
  XeCryptShaUpdate();
  return;
}

void FUN_0000b4f8(void){
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x23450)();
  return;
}



void FUN_0000b500(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x22018)();
  return;
}



void FUN_0000b508(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&0x21f48)();
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_14_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_15_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_16_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_17_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_18_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_19_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_20_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_21_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_22_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_23_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_24_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_25_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_26_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_27_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_28_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_29_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_30_thru_31_(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void __Save_R12_31_thru_31_(void)

{
  qword back_chain;
  dword local_8;
  
  return;
}



void __Rest_R12_lr_14_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_15_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_16_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_17_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_18_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_19_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_20_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_21_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_22_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_23_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_24_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_25_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_26_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_27_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_28_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_29_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_30_thru_31_(void)

{
  qword back_chain;
  
  return;
}



void __Rest_R12_lr_31_thru_31_(void)

{
  qword back_chain;
  dword local_8;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_000103f4(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_000103f8(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_000103fc(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010400(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010404(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010408(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_0001040c(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010410(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010414(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010418(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_0001041c(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010420(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010424(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010428(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_0001042c(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010430(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010434(void)

{
  qword back_chain;
  
  return;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_00010438(void)

{
  qword back_chain;
  dword local_8;
  
  return;
}



void FUN_00010450(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010454(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010458(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_0001045c(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010460(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010464(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010468(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_0001046c(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010470(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010474(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010478(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_0001047c(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010480(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010484(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010488(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_0001048c(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010490(void)

{
  int in_r13;
  qword back_chain;
  uint uStack8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ uStack8),(QWORD)uStack4);
  return;
}



void FUN_00010494(void)

{
  int in_r13;
  qword back_chain;
  dword local_8;
  uint uStack4;
  
  trapWord(0x18,(QWORD)(*(uint *)(in_r13 + 0x2ac) ^ local_8),(QWORD)uStack4);
  return;
}



undefined8 FUN_00020000(uint param_1)

{
  int in_r2;
  undefined8 uVar1;
  qword back_chain;
  qword local_8;
  
  if (param_1 < 0x2801) {
    HvpAquireSpinLock(&0x16978 + in_r2);
    uVar1 = *(undefined8 *)(&0x16a88 + in_r2);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



void FUN_00020040(QWORD param_1) {
  int in_r2;
  
  if (param_1 != *(QWORD *)(&0x16a88 + in_r2)) {
    return;
  }
  sync(1);
  *(undefined4 *)(&0x16978 + in_r2) = 0;
  return;
}


void XeCryptRandom(u8* data, s32 dataSize) {
  QWORD in_r2;
  undefined8 uVar1;
  QWORD lVar2;
  qword back_chain;
  
  uVar1 = __Save_R12_29_thru_31();
  lVar2 = ZEXT48(&0x16a90) + in_r2;
  HvpAquireSpinLock(lVar2);
  XeCryptRc4Ecb(ZEXT48(&0x16980) + in_r2,uVar1,param_2);
  HvpReleaseSpinLock(lVar2);
  return;
}



void XeCryptAesKey(uint *param_1,uint *param_2) {
  int in_r2;
  byte *pbVar1;
  undefined *puVar2;
  QWORD uVar3;
  uint uVar4;
  QWORD uVar5;
  uint uVar6;
  QWORD uVar7;
  uint uVar8;
  QWORD uVar9;
  uint uVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  QWORD lVar15;
  
  puVar2 = &0x13e60 + in_r2;
  uVar4 = *param_2;
  uVar3 = (QWORD)uVar4;
  uVar6 = param_2[1];
  uVar5 = (QWORD)uVar6;
  uVar8 = param_2[2];
  uVar7 = (QWORD)uVar8;
  uVar10 = param_2[3];
  uVar9 = (QWORD)uVar10;
  puVar11 = &0x13f60 + in_r2;
  puVar12 = &0x14360 + in_r2;
  puVar13 = &0x14760 + in_r2;
  puVar14 = &0x14b60 + in_r2;
  pbVar1 = &0x14f70 + in_r2;
  *param_1 = uVar4;
  param_1[1] = uVar6;
  param_1[2] = uVar8;
  param_1[3] = uVar10;
  param_1[0x2c] = uVar4;
  param_1[0x2d] = uVar6;
  param_1[0x2e] = uVar8;
  param_1[0x2f] = uVar10;
  lVar15 = 10;
  while( true ) {
    uVar4 = (uint)uVar9;
    pbVar1 = pbVar1 + -1;
    uVar3 = (QWORD)
            CONCAT13(puVar2[uVar4 >> 0x10 & 0xff],
                     CONCAT12(puVar2[uVar4 >> 8 & 0xff],
                              CONCAT11(puVar2[uVar4 & 0xff],puVar2[uVar4 >> 0x18]))) ^
            (QWORD)*pbVar1 << 0x18 ^ uVar3;
    uVar5 = uVar3 ^ uVar5;
    uVar7 = uVar5 ^ uVar7;
    uVar9 = uVar7 ^ uVar9;
    uVar4 = (uint)uVar3;
    param_1[4] = uVar4;
    uVar6 = (uint)uVar5;
    param_1[5] = uVar6;
    uVar8 = (uint)uVar7;
    param_1[6] = uVar8;
    uVar10 = (uint)uVar9;
    param_1[7] = uVar10;
    lVar15 = lVar15 + -1;
    if (lVar15 == 0) break;
    param_1[0x30] =
         *(uint *)(puVar11 + (uVar4 >> 0x16 & 0x3fc)) ^ *(uint *)(puVar12 + (uVar4 >> 0xe & 0x3fc))
         ^ *(uint *)(puVar13 + (uVar4 >> 6 & 0x3fc)) ^ *(uint *)(puVar14 + (uVar4 & 0xff) * 4);
    param_1[0x31] =
         *(uint *)(puVar11 + (uVar6 >> 0x16 & 0x3fc)) ^ *(uint *)(puVar12 + (uVar6 >> 0xe & 0x3fc))
         ^ *(uint *)(puVar13 + (uVar6 >> 6 & 0x3fc)) ^ *(uint *)(puVar14 + (uVar6 & 0xff) * 4);
    param_1[0x32] =
         *(uint *)(puVar11 + (uVar8 >> 0x16 & 0x3fc)) ^ *(uint *)(puVar12 + (uVar8 >> 0xe & 0x3fc))
         ^ *(uint *)(puVar13 + (uVar8 >> 6 & 0x3fc)) ^ *(uint *)(puVar14 + (uVar8 & 0xff) * 4);
    param_1[0x33] =
         *(uint *)(puVar11 + (uVar10 >> 0x16 & 0x3fc)) ^
         *(uint *)(puVar12 + (uVar10 >> 0xe & 0x3fc)) ^
         *(uint *)(puVar13 + (uVar10 >> 6 & 0x3fc)) ^ *(uint *)(puVar14 + (uVar10 & 0xff) * 4);
    param_1 = param_1 + 4;
  }
  param_1[0x30] = uVar4;
  param_1[0x31] = uVar6;
  param_1[0x32] = uVar8;
  param_1[0x33] = uVar10;
  return;
}



void XeCryptAesEcb(uint *param_1,uint *param_2,uint *param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  int in_r2;
  uint *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  QWORD lVar17;
  
  if (param_4 != 0) {
    puVar10 = &0x11d60 + in_r2;
    puVar9 = &0x12160 + in_r2;
    puVar11 = &0x12560 + in_r2;
    puVar12 = &0x12960 + in_r2;
    uVar13 = *param_1 ^ *param_2;
    uVar14 = param_1[1] ^ param_2[1];
    uVar15 = param_1[2] ^ param_2[2];
    uVar16 = param_1[3] ^ param_2[3];
    lVar17 = 9;
    puVar7 = param_1 + 4;
    do {
      puVar8 = puVar7;
      uVar4 = uVar13 & 0xff;
      uVar1 = uVar13 >> 6;
      uVar5 = uVar14 & 0xff;
      uVar2 = uVar13 >> 0xe;
      uVar3 = uVar14 >> 6;
      uVar6 = uVar15 & 0xff;
      uVar13 = *(uint *)(puVar10 + (uVar13 >> 0x16 & 0x3fc)) ^
               *(uint *)(puVar9 + (uVar14 >> 0xe & 0x3fc)) ^
               *(uint *)(puVar11 + (uVar15 >> 6 & 0x3fc)) ^ *(uint *)(puVar12 + (uVar16 & 0xff) * 4)
               ^ *puVar8;
      uVar14 = *(uint *)(puVar10 + (uVar14 >> 0x16 & 0x3fc)) ^
               *(uint *)(puVar9 + (uVar15 >> 0xe & 0x3fc)) ^
               *(uint *)(puVar11 + (uVar16 >> 6 & 0x3fc)) ^ *(uint *)(puVar12 + uVar4 * 4) ^
               puVar8[1];
      uVar15 = *(uint *)(puVar10 + (uVar15 >> 0x16 & 0x3fc)) ^
               *(uint *)(puVar9 + (uVar16 >> 0xe & 0x3fc)) ^
               *(uint *)(puVar11 + (uVar1 & 0x3fc)) ^ *(uint *)(puVar12 + uVar5 * 4) ^ puVar8[2];
      uVar16 = *(uint *)(puVar10 + (uVar16 >> 0x16 & 0x3fc)) ^ *(uint *)(puVar9 + (uVar2 & 0x3fc)) ^
               *(uint *)(puVar11 + (uVar3 & 0x3fc)) ^ *(uint *)(puVar12 + uVar6 * 4) ^ puVar8[3];
      lVar17 = lVar17 + -1;
      puVar7 = puVar8 + 4;
    } while (lVar17 != 0);
    puVar9 = &0x11d61 + in_r2;
    param_3[3] = puVar8[7] ^
                 CONCAT13(puVar9[uVar16 >> 0x16 & 0x3fc],
                          CONCAT12(puVar9[uVar13 >> 0xe & 0x3fc],
                                   CONCAT11(puVar9[uVar14 >> 6 & 0x3fc],puVar9[(uVar15 & 0xff) * 4])
                                  ));
    param_3[2] = puVar8[6] ^
                 CONCAT13(puVar9[uVar15 >> 0x16 & 0x3fc],
                          CONCAT12(puVar9[uVar16 >> 0xe & 0x3fc],
                                   CONCAT11(puVar9[uVar13 >> 6 & 0x3fc],puVar9[(uVar14 & 0xff) * 4])
                                  ));
    param_3[1] = puVar8[5] ^
                 CONCAT13(puVar9[uVar14 >> 0x16 & 0x3fc],
                          CONCAT12(puVar9[uVar15 >> 0xe & 0x3fc],
                                   CONCAT11(puVar9[uVar16 >> 6 & 0x3fc],puVar9[(uVar13 & 0xff) * 4])
                                  ));
    *param_3 = puVar8[4] ^
               CONCAT13(puVar9[uVar13 >> 0x16 & 0x3fc],
                        CONCAT12(puVar9[uVar14 >> 0xe & 0x3fc],
                                 CONCAT11(puVar9[uVar15 >> 6 & 0x3fc],puVar9[(uVar16 & 0xff) * 4])))
    ;
    return;
  }
  puVar10 = &0x12d60 + in_r2;
  puVar9 = &0x13160 + in_r2;
  puVar11 = &0x13560 + in_r2;
  puVar12 = &0x13960 + in_r2;
  uVar13 = param_1[0x54] ^ *param_2;
  uVar14 = param_1[0x55] ^ param_2[1];
  uVar15 = param_1[0x56] ^ param_2[2];
  uVar16 = param_1[0x57] ^ param_2[3];
  lVar17 = 9;
  puVar7 = param_1 + 0x50;
  do {
    puVar8 = puVar7;
    uVar1 = uVar13 >> 0xe;
    uVar2 = uVar14 >> 0xe;
    uVar3 = uVar13 >> 6;
    uVar4 = uVar15 >> 0xe;
    uVar5 = uVar14 >> 6;
    uVar6 = uVar13 & 0xff;
    uVar13 = *(uint *)(puVar10 + (uVar13 >> 0x16 & 0x3fc)) ^
             *(uint *)(puVar9 + (uVar16 >> 0xe & 0x3fc)) ^
             *(uint *)(puVar11 + (uVar15 >> 6 & 0x3fc)) ^ *(uint *)(puVar12 + (uVar14 & 0xff) * 4) ^
             *puVar8;
    uVar14 = *(uint *)(puVar10 + (uVar14 >> 0x16 & 0x3fc)) ^ *(uint *)(puVar9 + (uVar1 & 0x3fc)) ^
             *(uint *)(puVar11 + (uVar16 >> 6 & 0x3fc)) ^ *(uint *)(puVar12 + (uVar15 & 0xff) * 4) ^
             puVar8[1];
    uVar15 = *(uint *)(puVar10 + (uVar15 >> 0x16 & 0x3fc)) ^ *(uint *)(puVar9 + (uVar2 & 0x3fc)) ^
             *(uint *)(puVar11 + (uVar3 & 0x3fc)) ^ *(uint *)(puVar12 + (uVar16 & 0xff) * 4) ^
             puVar8[2];
    uVar16 = *(uint *)(puVar10 + (uVar16 >> 0x16 & 0x3fc)) ^ *(uint *)(puVar9 + (uVar4 & 0x3fc)) ^
             *(uint *)(puVar11 + (uVar5 & 0x3fc)) ^ *(uint *)(puVar12 + uVar6 * 4) ^ puVar8[3];
    lVar17 = lVar17 + -1;
    puVar7 = puVar8 + -4;
  } while (lVar17 != 0);
  puVar9 = &0x13d60 + in_r2;
  param_3[3] = puVar8[-1] ^
               CONCAT13(puVar9[uVar16 >> 0x18],
                        CONCAT12(puVar9[uVar15 >> 0x10 & 0xff],
                                 CONCAT11(puVar9[uVar14 >> 8 & 0xff],puVar9[uVar13 & 0xff])));
  param_3[2] = puVar8[-2] ^
               CONCAT13(puVar9[uVar15 >> 0x18],
                        CONCAT12(puVar9[uVar14 >> 0x10 & 0xff],
                                 CONCAT11(puVar9[uVar13 >> 8 & 0xff],puVar9[uVar16 & 0xff])));
  param_3[1] = puVar8[-3] ^
               CONCAT13(puVar9[uVar14 >> 0x18],
                        CONCAT12(puVar9[uVar13 >> 0x10 & 0xff],
                                 CONCAT11(puVar9[uVar16 >> 8 & 0xff],puVar9[uVar15 & 0xff])));
  *param_3 = puVar8[-4] ^
             CONCAT13(puVar9[uVar13 >> 0x18],
                      CONCAT12(puVar9[uVar16 >> 0x10 & 0xff],
                               CONCAT11(puVar9[uVar15 >> 8 & 0xff],puVar9[uVar14 & 0xff])));
  return;
}



void XeCryptAesCbc(undefined8 param_1,QWORD param_2,undefined8 param_3,QWORD param_4,
                  QWORD *param_5,int param_6)

{
  QWORD in_r2;
  undefined8 uVar1;
  QWORD uVar2;
  QWORD uVar3;
  uint uVar4;
  qword back_chain;
  qword local_70;
  qword local_68;
  qword local_60;
  qword local_58;
  qword local_50;
  qword local_48;
  
  uVar4 = (uint)param_3;
  uVar1 = __Save_R12_26_thru_31();
  uVar4 = uVar4 >> 4;
  uVar3 = *param_5;
  uVar2 = param_5[1];
  if (param_6 == 0) {
    if (uVar4 != 0) {
      local_70 = uVar3;
      local_68 = uVar2;
      do {
        uVar3 = *(QWORD *)param_2;
        uVar2 = ((QWORD *)param_2)[1];
        XeCryptBnQwBeSigDifference(uVar1,&local_60,&local_50,ZEXT48(&0x12d60) + in_r2);
        uVar4 = uVar4 - 1;
        param_2 = param_2 + 0x10;
        *(QWORD *)param_4 = local_50 ^ local_70;
        ((QWORD *)param_4)[1] = local_48 ^ local_68;
        param_4 = param_4 + 0x10;
        local_70 = uVar3;
        local_68 = uVar2;
      } while (uVar4 != 0);
    }
  }
  else {
    if (uVar4 != 0) {
      do {
        uVar3 = *(QWORD *)param_2 ^ uVar3;
        uVar2 = ((QWORD *)param_2)[1] ^ uVar2;
        FUN_0002402c(uVar1,&local_70,&local_70,ZEXT48(&0x11d60) + in_r2);
        uVar4 = uVar4 - 1;
        param_2 = param_2 + 0x10;
        *(QWORD *)param_4 = uVar3;
        ((QWORD *)param_4)[1] = uVar2;
        param_4 = param_4 + 0x10;
      } while (uVar4 != 0);
    }
  }
  *param_5 = uVar3;
  param_5[1] = uVar2;
  return;
}



void XeCryptAesCtr(undefined8 param_1,QWORD param_2,undefined8 param_3,QWORD param_4,
                  undefined8 param_5)

{
  bool bVar1;
  char cVar2;
  QWORD in_r2;
  undefined8 uVar3;
  int iVar4;
  uint uVar5;
  qword back_chain;
  qword local_50;
  qword local_48;
  
  uVar5 = (uint)param_3;
  uVar3 = __Save_R12_26_thru_31();
  uVar5 = uVar5 >> 4;
  if (uVar5 != 0) {
    do {
      FUN_0002402c(uVar3,param_5,&local_50,ZEXT48(&0x11d60) + in_r2);
      *(QWORD *)param_4 = *(QWORD *)param_2 ^ local_50;
      ((QWORD *)param_4)[1] = ((QWORD *)param_2)[1] ^ local_48;
      iVar4 = 0xf;
      do {
        cVar2 = *(char *)(iVar4 + (int)param_5) + '\x01';
        *(char *)(iVar4 + (int)param_5) = cVar2;
        if (cVar2 != '\0') break;
        bVar1 = iVar4 != 0;
        iVar4 = iVar4 + -1;
      } while (bVar1);
      uVar5 = uVar5 - 1;
      param_2 = param_2 + 0x10;
      param_4 = param_4 + 0x10;
    } while (uVar5 != 0);
  }
  return;
}



void XeCryptAesCbcMac(undefined8 param_1,QWORD param_2,undefined8 param_3,QWORD *param_4)

{
  QWORD in_r2;
  QWORD *puVar1;
  uint uVar2;
  qword back_chain;
  qword local_1b0;
  qword local_1a8;
  qword local_1a0;
  qword local_198;
  word local_190;
  
  uVar2 = (uint)param_3;
  puVar1 = (QWORD *)__Save_R12_27_thru_31();
  local_1b0 = *puVar1;
  uVar2 = uVar2 >> 4;
  local_1a8 = puVar1[1];
  if (uVar2 != 0) {
    do {
      FUN_00023e70(&local_190,param_2,ZEXT48(&0x13e60) + in_r2);
      FUN_0002402c(&local_190,&local_1b0,&local_1a0,ZEXT48(&0x11d60) + in_r2);
      uVar2 = uVar2 - 1;
      param_2 = param_2 + 0x10;
      local_1b0 = local_1a0 ^ local_1b0;
      local_1a8 = local_198 ^ local_1a8;
    } while (uVar2 != 0);
  }
  *param_4 = local_1b0;
  param_4[1] = local_1a8;
  return;
}



void XeCryptBnDwLePkcs1Format
               (undefined8 param_1,QWORD param_2,QWORD param_3,QWORD param_4)

{
  undefined *puVar1;
  QWORD in_r2;
  int iVar2;
  undefined8 uVar3;
  QWORD lVar4;
  int iVar5;
  int iVar6;
  qword back_chain;
  
  iVar2 = __Save_R12_28_thru_31();
  memset(param_3,0xff,param_4 & 0xffffffff);
  if ((param_4 - 0x27 & 0xffffffff) < 0x1da) {
    *(undefined *)((int)param_4 + -1 + (int)param_3) = 0;
    *(undefined *)((int)param_4 + -2 + (int)param_3) = 1;
    lVar4 = param_3;
    iVar5 = 0x13;
    do {
      iVar6 = iVar5 + -1;
      *(undefined *)lVar4 = *(undefined *)(iVar5 + iVar2);
      lVar4 = lVar4 + 1;
      iVar5 = iVar6;
    } while (-1 < iVar6);
    if ((param_2 & 0xffffffff) == 0) {
      uVar3 = 0x10;
      puVar1 = &0x14f70;
    }
    else {
      if ((param_2 & 0xffffffff) != 1) {
        *(undefined *)(param_3 + 0x14) = 0;
        return;
      }
      uVar3 = 0xe;
      puVar1 = &0x14f80;
    }
    memcpy(param_3 + 0x14,ZEXT48(puVar1) + in_r2,uVar3);
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 XeCryptBnDwLePkcs1Verify(undefined8 param_1,int param_2,QWORD param_3)

{
  uint uVar1;
  int in_r2;
  int iVar2;
  QWORD lVar3;
  undefined8 uVar4;
  qword back_chain;
  word local_220;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)(in_r2 + 0x10000);
  if ((param_3 - 0x27U & 0xffffffff) < 0x1da) {
    if (*(byte *)(param_2 + 0x16) == 0) {
      lVar3 = 0;
    }
    else {
      uVar4 = countLeadingZeros((uint)*(byte *)(param_2 + 0x16) - 0x1a);
      lVar3 = ((QWORD)((uint)uVar4 >> 5 & 1) ^ 1) + 1;
    }
    XeCryptBnDwLePkcs1Format(param_1,lVar3,&local_220,param_3);
    iVar2 = XeCryptMemDiff(param_2,&local_220,param_3);
    if (iVar2 == 0) {
      FUN_00000204((QWORD)uVar1);
      return 1;
    }
  }
  FUN_00000204((QWORD)uVar1);
  return 0;
}



void XeCryptBnDw_Copy(undefined4 *param_1,undefined4 *param_2,QWORD param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)((int)param_2 - (int)param_1);
  if ((int)param_3 == 0) {
    return;
  }
  if (param_1 == param_2) {
    return;
  }
  do {
    *(undefined4 *)((int)param_1 + (int)puVar1) = *param_1;
    param_1 = param_1 + 1;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  return;
}



void XeCryptBnDw_SwapLeBe(uint *param_1,int param_2,QWORD param_3)

{
  uint uVar1;
  
  param_2 = param_2 - (int)param_1;
  if ((int)param_3 == 0) {
    return;
  }
  do {
    uVar1 = *param_1;
    *(uint *)((int)param_1 + param_2) =
         uVar1 << 0x18 | (uVar1 & 0xff00) << 8 | uVar1 >> 8 & 0xff00 | uVar1 >> 0x18;
    param_1 = param_1 + 1;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  return;
}



void XeCryptBnQwBeSigFormat(undefined8 param_1,undefined8 param_2,undefined8 param_3){
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  qword back_chain;
  word local_130;
  dword local_2c;
  
  puVar3 = (undefined8 *)__Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  memset(puVar3,0,0xe0);
  *(byte *)(puVar3 + 0x1c) = 1;
  memcpy((byte *)((int)puVar3 + 0xe1),param_3,10);
  *(byte *)((int)puVar3 + 0xff) = 0xbc;
  XeCryptShaInit(&local_130);
  XeCryptShaUpdate(&local_130,puVar3,8);
  XeCryptShaUpdate(&local_130,param_2,0x14);
  XeCryptShaUpdate(&local_130,param_3,10);
  XeCryptShaFinal(&local_130,(byte *)((int)puVar3 + 0xeb),0x14);
  XeCryptRc4Key(&local_130,(byte *)((int)puVar3 + 0xeb),0x14);
  XeCryptRc4Ecb(&local_130,puVar3,0xeb);
  puVar4 = puVar3 + 0x1f;
  *(byte *)puVar3 = *(byte *)puVar3 & 0x7f;
  if (puVar3 < puVar4) {
    do {
      uVar2 = *puVar3;
      *puVar3 = *puVar4;
      puVar3 = puVar3 + 1;
      *puVar4 = uVar2;
      puVar4 = puVar4 + -1;
    } while (puVar3 < puVar4);
  }
  FUN_00000204((QWORD)uVar1);
  return;
}



QWORD XeCryptBnQwBeSigVerify(void)

{
  undefined4 uVar2;
  QWORD uVar1;
  int *in_r6;
  undefined8 uVar3;
  qword back_chain;
  word local_210;
  word local_110;
  qword local_8;
  
  if ((*in_r6 == 0x20) &&
     (((undefined *)in_r6[1] == (undefined *)0x3 || ((undefined *)in_r6[1] == &0x10001)))) {
    XeCryptBnQwNeDigLen();
    uVar2 = XeCryptMemDiff(&local_110,&local_210,0x100);
    uVar3 = countLeadingZeros(uVar2);
    uVar1 = (QWORD)((uint)uVar3 >> 5 & 1);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



void FUN_000206f0(undefined8 param_1,QWORD param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint *puVar6;
  QWORD uVar4;
  QWORD lVar5;
  int iVar7;
  QWORD lVar8;
  undefined8 uVar9;
  QWORD uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  QWORD uVar14;
  QWORD uVar15;
  qword back_chain;
  
  puVar6 = (uint *)__Save_R12_23_thru_31();
  uVar4 = 0;
  uVar1 = *puVar6;
  uVar15 = (QWORD)uVar1;
  uVar12 = *(undefined8 *)(puVar6 + 4);
  uVar11 = *(undefined8 *)(puVar6 + 6);
  uVar13 = *(undefined8 *)(puVar6 + 2);
  uVar14 = (uVar15 - 2) * 8 + param_2;
  if (param_2 <= uVar14) {
    do {
      uVar10 = *(QWORD *)((uVar1 + 1) * 8 + (int)uVar14);
      if (uVar10 < uVar4) {
        lVar8 = uVar4 - uVar10;
        uVar9 = uVar12;
      }
      else {
        lVar8 = uVar10 - uVar4;
        uVar9 = uVar11;
      }
      uVar4 = FUN_00024c88(uVar14,lVar8,uVar9,uVar15);
      uVar14 = uVar14 - 8;
    } while (param_2 <= uVar14);
  }
  iVar2 = uVar1 * 8;
  lVar8 = param_2 + 8;
  iVar3 = (int)param_2;
  uVar14 = *(QWORD *)(iVar2 + iVar3);
  *(QWORD *)(iVar2 + iVar3) = uVar14 - uVar4;
  if (uVar14 < uVar4) {
    do {
      lVar5 = XeCryptBnQwNeAcc(lVar8,lVar8,uVar13,uVar15);
    } while (lVar5 == 0);
  }
  else {
    iVar7 = FUN_00024d08(lVar8,uVar13,uVar15);
    if (-1 < iVar7) {
      FUN_00024b38(lVar8,lVar8,uVar13,uVar15);
    }
  }
  iVar7 = (uVar1 - 1) * 8;
  uVar11 = FUN_00024788(*(undefined8 *)(iVar2 + iVar3),*(undefined8 *)(iVar7 + iVar3),
                        *(undefined8 *)(iVar7 + (int)uVar13),0);
  lVar8 = FUN_00024c88(param_2,uVar11,uVar13,uVar15);
  lVar8 = *(QWORD *)(iVar2 + iVar3) - lVar8;
  *(QWORD *)(iVar2 + iVar3) = lVar8;
  while (lVar8 != 0) {
    lVar8 = XeCryptBnQwNeAcc(param_2,param_2,uVar13,uVar15);
    lVar8 = lVar8 + *(QWORD *)(iVar2 + iVar3);
    *(QWORD *)(iVar2 + iVar3) = lVar8;
  }
  XeCryptBnQw_Copy(param_2,param_3,uVar15);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00020860(uint *param_1,undefined8 param_2,undefined8 param_3)

{
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  FUN_000246b0(*(undefined8 *)(param_1 + 8),param_3,(QWORD)*param_1);
  FUN_000206f0(param_1,*(undefined8 *)(param_1 + 8),param_2);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_000208b8(uint *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  FUN_00024600(*(undefined8 *)(param_1 + 8),param_3,param_4,(QWORD)*param_1);
  FUN_000206f0(param_1,*(undefined8 *)(param_1 + 8),param_2);
  return;
}



undefined8
XeCryptBnQwNeModExp(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                   QWORD param_5)

{
  int iVar1;
  bool bVar2;
  undefined8 *puVar5;
  QWORD lVar3;
  QWORD lVar4;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar11;
  QWORD uVar10;
  uint uVar12;
  undefined8 uVar13;
  QWORD uVar14;
  uint uVar15;
  QWORD uVar16;
  int iVar17;
  QWORD lVar18;
  QWORD uVar19;
  QWORD lVar20;
  QWORD uVar21;
  int iVar22;
  int iVar23;
  qword back_chain;
  dword local_c0;
  qword local_b8;
  qword local_b0;
  qword local_a8;
  qword local_a0;
  
  puVar5 = (undefined8 *)__Save_R12_14_thru_31();
  uVar13 = 0;
  lVar3 = XeCryptBnQwNeMul(param_4,param_5);
  iVar23 = (int)lVar3;
  if ((iVar23 != 0) &&
     (iVar7 = (int)((QWORD)(iVar23 + -1) << 3), *(QWORD *)(iVar7 + (int)param_4) != 0)) {
    iVar22 = iVar23 * 0x10;
    iVar1 = iVar23 * 8;
    lVar4 = FUN_000245b0(param_3,param_5);
    iVar6 = (int)lVar4;
    if (iVar6 == 0) {
      *puVar5 = 1;
      XeCryptBnQw_Zero(puVar5 + 1,param_5 + -1);
      return 1;
    }
    if (iVar6 < 0x12) {
      uVar15 = 1;
    }
    else {
      if (iVar6 < 0x21) {
        uVar15 = 2;
      }
      else {
        if (iVar6 < 0x41) {
          uVar15 = 4;
        }
        else {
          if (iVar6 < 0x81) {
            uVar15 = 8;
          }
          else {
            uVar15 = 0x10;
            if (0x100 < iVar6) {
              uVar15 = 0x20;
            }
          }
        }
      }
    }
    iVar6 = FUN_00020000((uVar15 + 4) * iVar1 + iVar22 + 8);
    if (iVar6 != 0) {
      iVar8 = iVar1 + iVar6;
      iVar9 = iVar1 + iVar8;
      iVar11 = iVar1 + iVar1 + iVar9;
      iVar17 = iVar22 + 8 + iVar11;
      if ((uVar15 * iVar1 - iVar6) + iVar17 == (uVar15 + 4) * iVar1 + iVar22 + 8) {
        XeCryptBnQw_Copy(param_4,iVar8,lVar3);
        while ((*(QWORD *)(iVar7 + iVar8) & 0x8000000000000000) == 0) {
          XeCryptBnQwNeAcc(iVar8,iVar1 + iVar6,iVar1 + iVar6,lVar3);
        }
        XeCryptBnQw_Zero(iVar11,lVar3 + 1);
        *(undefined8 *)((int)((QWORD)(int)(lVar3 + 1) << 3) + iVar11) = 1;
        iVar7 = XeCryptBnQwNeAdd(iVar11,param_4,iVar9,lVar3 + 2,lVar3);
        if (iVar7 != 0) {
          FUN_00024b38(iVar1 + iVar9,param_4,iVar9,lVar3);
          XeCryptBnQw_Copy(param_2,iVar17,lVar3);
          if ((1 < uVar15) && (FUN_00020860(&local_c0,iVar6,param_2), 1 < uVar15)) {
            lVar18 = 0;
            iVar7 = uVar15 - 1;
            lVar20 = lVar3;
            do {
              FUN_000208b8(&local_c0,(int)lVar20 * 8 + iVar17,(int)lVar18 * 8 + iVar17,iVar6);
              iVar7 = iVar7 + -1;
              lVar20 = lVar20 + lVar3;
              lVar18 = lVar18 + lVar3;
            } while (iVar7 != 0);
          }
          uVar10 = lVar4 - 1;
          uVar21 = 0;
          bVar2 = true;
          uVar16 = 1 << (uVar10 & 0x3f);
          if (-1 < (int)uVar10) {
            uVar14 = SEXT48((int)uVar10);
            uVar19 = uVar10;
            do {
              uVar21 = (QWORD)(uint)((int)uVar21 << 1);
              if ((*(QWORD *)(((uint)(uVar14 >> 3) & 0xfffffff8) + (int)param_3) & uVar16) != 0)
              {
                uVar21 = uVar21 + 1;
              }
              uVar16 = uVar16 << 0x3f | uVar16 >> 1;
              if (((int)uVar19 == 0) || ((int)uVar15 <= (int)uVar21)) {
                lVar4 = uVar10 - uVar19;
                iVar7 = 0;
                while ((iVar22 = (int)uVar21, iVar22 != 0 &&
                       (iVar22 == ((iVar22 >> 1) + (uint)(iVar22 < 0 && (uVar21 & 1) != 0)) * 2))) {
                  lVar4 = lVar4 + -1;
                  uVar21 = (QWORD)(uint)(iVar22 >> 1) +
                           (QWORD)(iVar22 < 0 && (uVar21 & 1) != 0);
                  iVar7 = iVar7 + 1;
                }
                if (bVar2) {
                  uVar12 = (iVar22 + -1) * iVar23;
                  XeCryptBnQw_Copy((((int)uVar12 >> 1) +
                                   (uint)((int)uVar12 < 0 && (uVar12 & 1) != 0)) * 8 + iVar17,iVar6,
                                   lVar3);
                  bVar2 = false;
                }
                else {
                  while ((int)lVar4 != 0) {
                    lVar4 = lVar4 + -1;
                    FUN_00020860(&local_c0,iVar6,iVar6);
                  }
                  if (iVar22 != 0) {
                    uVar12 = (iVar22 + -1) * iVar23;
                    FUN_000208b8(&local_c0,iVar6,iVar6,
                                 (((int)uVar12 >> 1) + (uint)((int)uVar12 < 0 && (uVar12 & 1) != 0))
                                 * 8 + iVar17);
                  }
                }
                while (iVar7 != 0) {
                  iVar7 = iVar7 + -1;
                  FUN_00020860(&local_c0,iVar6,iVar6);
                }
                uVar21 = 0;
                uVar10 = uVar19;
              }
              uVar19 = uVar19 - 1;
              uVar14 = uVar14 - 1;
            } while (-1 < (int)uVar19);
          }
          iVar7 = XeCryptBnQwNeAdd(iVar6,param_4,puVar5,lVar3,lVar3);
          if (iVar7 != 0) {
            XeCryptBnQw_Zero(puVar5 + iVar23,param_5 - lVar3);
            uVar13 = 1;
          }
        }
      }
      FUN_00020040(iVar6);
      return uVar13;
    }
  }
  return 0;
}



undefined8
XeCryptBnQwNeModExpRoot
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5,undefined8 param_6,undefined8 param_7,QWORD param_8)

{
  QWORD uVar1;
  undefined8 uVar2;
  int iVar4;
  QWORD lVar3;
  undefined8 uVar5;
  QWORD uVar6;
  qword back_chain;
  word local_460;
  word local_360;
  word local_260;
  
  uVar1 = ZEXT48(register0x0000000c);
  uVar2 = __Save_R12_22_thru_31();
  uVar5 = 0;
  if ((param_8 & 0xffffffff) < 0x21) {
    uVar6 = (QWORD)(uint)((int)param_8 << 1);
    iVar4 = XeCryptBnQwNeAdd(param_2,param_3,uVar1 - 0x460,uVar6,param_8);
    if ((((iVar4 != 0) &&
         (iVar4 = XeCryptBnQwNeModExp(uVar1 - 0x360,uVar1 - 0x460,param_5,param_3,param_8),
         iVar4 != 0)) &&
        (iVar4 = XeCryptBnQwNeAdd(param_2,param_4,uVar1 - 0x460,uVar6,param_8), iVar4 != 0)) &&
       (iVar4 = XeCryptBnQwNeModExp(uVar1 - 0x260,uVar1 - 0x460,param_6,param_4,param_8), iVar4 != 0
       )) {
      lVar3 = FUN_00024b38(uVar1 - 0x460,uVar1 - 0x360,uVar1 - 0x260,param_8);
      if (lVar3 != 0) {
        do {
          lVar3 = XeCryptBnQwNeAcc(uVar1 - 0x460,uVar1 - 0x460,param_3,param_8);
        } while (lVar3 == 0);
      }
      FUN_00024600(uVar2,uVar1 - 0x460,param_7,param_8);
      iVar4 = XeCryptBnQwNeAdd(uVar2,param_3,uVar1 - 0x460,uVar6,param_8);
      if (iVar4 != 0) {
        FUN_00024600(uVar2,uVar1 - 0x460,param_4,param_8);
        XeCryptBnQw_Zero((param_8 & 0xffffffff) * 8 + (uVar1 - 0x260),param_8);
        XeCryptBnQwNeAcc(uVar2,uVar2,uVar1 - 0x260,uVar6);
        uVar5 = 1;
      }
    }
  }
  XeCryptBnQw_Zero(uVar1 - 0x360,0x20);
  XeCryptBnQw_Zero(uVar1 - 0x260,0x40);
  XeCryptBnQw_Zero(uVar1 - 0x460,0x20);
  return uVar5;
}



QWORD XeCryptBnQwNeModInv(QWORD param_1)

{
  QWORD lVar1;
  uint uVar2;
  QWORD uVar3;
  QWORD lVar4;
  
  uVar3 = param_1 * 3 ^ 2;
  uVar2 = 5;
  lVar4 = 1 - uVar3 * param_1;
  do {
    lVar1 = lVar4 + 1;
    uVar2 = uVar2 << 1;
    lVar4 = lVar4 * lVar4;
    uVar3 = lVar1 * uVar3;
  } while (uVar2 < 0x20);
  return (lVar4 + 1) * uVar3;
}



// WARNING: Variable defined which should be unmapped: local_50
// WARNING: Variable defined which should be unmapped: local_48
// WARNING: Variable defined which should be unmapped: local_40
// WARNING: Variable defined which should be unmapped: local_38
// WARNING: Variable defined which should be unmapped: local_30
// WARNING: Variable defined which should be unmapped: local_28
// WARNING: Variable defined which should be unmapped: local_20
// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void XeCryptBnQwNeModMul(QWORD *param_1,QWORD *param_2,QWORD *param_3,QWORD param_4,
                        QWORD *param_5,int param_6)

{
  bool bVar1;
  QWORD *puVar2;
  QWORD *puVar3;
  QWORD uVar4;
  QWORD uVar5;
  undefined8 *puVar7;
  QWORD uVar6;
  QWORD uVar8;
  QWORD uVar9;
  QWORD uVar10;
  int iVar11;
  QWORD lVar12;
  int iVar13;
  int iVar14;
  dword back_chain;
  word local_260;
  word local_258;
  QWORD local_150;
  qword local_50;
  qword local_48;
  qword local_40;
  qword local_38;
  qword local_30;
  qword local_28;
  qword local_20;
  qword local_18;
  qword local_10;
  
  lVar12 = 0xb;
  puVar7 = (undefined8 *)&local_260;
  do {
    *puVar7 = 0;
    puVar7[1] = 0;
    puVar7[2] = 0;
    puVar7[3] = 0;
    puVar7[4] = 0;
    puVar7[5] = 0;
    puVar7 = puVar7 + 6;
    lVar12 = lVar12 + -1;
  } while (lVar12 != 0);
  lVar12 = *param_1;
  iVar13 = param_6;
  do {
    uVar4 = *param_2;
    param_2 = param_2 + 1;
    uVar5 = param_4 * lVar12 * uVar4 + param_4 * (_local_258 - local_150);
    uVar6 = 0;
    uVar8 = 0;
    iVar11 = 0;
    puVar3 = (QWORD *)&local_258;
    iVar14 = param_6;
    do {
      puVar2 = puVar3;
      uVar9 = SUB168(ZEXT816(uVar4) * ZEXT816(*(QWORD *)((int)param_1 + iVar11)) >> 0x40,0);
      uVar10 = uVar4 * *(QWORD *)((int)param_1 + iVar11) + *puVar2;
      if (uVar10 < *puVar2) {
        uVar9 = uVar9 + 1;
      }
      uVar10 = uVar10 + uVar6;
      bVar1 = uVar10 < uVar6;
      uVar6 = uVar9;
      if (bVar1) {
        uVar6 = uVar9 + 1;
      }
      puVar2[-1] = uVar10;
      uVar9 = SUB168(ZEXT816(uVar5) * ZEXT816(*(QWORD *)((int)param_5 + iVar11)) >> 0x40,0);
      uVar10 = uVar5 * *(QWORD *)((int)param_5 + iVar11) + puVar2[0x21];
      if (uVar10 < puVar2[0x21]) {
        uVar9 = uVar9 + 1;
      }
      uVar10 = uVar10 + uVar8;
      bVar1 = uVar10 < uVar8;
      uVar8 = uVar9;
      if (bVar1) {
        uVar8 = uVar9 + 1;
      }
      puVar2[0x20] = uVar10;
      iVar11 = iVar11 + 8;
      iVar14 = iVar14 + -1;
      puVar3 = puVar2 + 1;
    } while (iVar14 != 0);
    *puVar2 = uVar6;
    puVar2[0x21] = uVar8;
    iVar13 = iVar13 + -1;
  } while (iVar13 != 0);
  uVar8 = 0;
  uVar6 = 0;
  puVar3 = (QWORD *)(&local_260 + param_6 * 4);
  iVar13 = param_6;
  do {
    if (*puVar3 < puVar3[0x21]) {
      puVar3 = (QWORD *)&local_258;
      do {
        uVar4 = *puVar3;
        uVar5 = puVar3[0x21];
        puVar3 = puVar3 + 1;
        uVar9 = *param_5;
        param_5 = param_5 + 1;
        uVar10 = uVar4 + uVar9 + uVar8;
        uVar6 = (uVar10 - uVar5) - uVar6;
        *param_3 = uVar6;
        param_3 = param_3 + 1;
        uVar8 = ((uVar4 ^ uVar10 | uVar9 ^ uVar10) ^ uVar10) >> 0x3f;
        uVar6 = ((uVar5 ^ uVar10 | uVar6 ^ uVar10) ^ uVar10) >> 0x3f;
        param_6 = param_6 + -1;
      } while (param_6 != 0);
      return;
    }
    if (puVar3[0x21] < *puVar3) break;
    puVar3 = puVar3 + -1;
    iVar13 = iVar13 + -1;
  } while (iVar13 != 0);
  puVar3 = (QWORD *)&local_258;
  do {
    uVar6 = *puVar3;
    uVar4 = puVar3[0x21];
    puVar3 = puVar3 + 1;
    uVar8 = (uVar6 - uVar4) - uVar8;
    *param_3 = uVar8;
    param_3 = param_3 + 1;
    uVar8 = (uVar6 ^ (uVar8 ^ uVar6 | uVar4 ^ uVar6)) >> 0x3f;
    param_6 = param_6 + -1;
  } while (param_6 != 0);
  return;
}



undefined8 XeCryptBnQwNeRsaPubCrypt(undefined8 param_1,undefined8 param_2,QWORD param_3)

{
  undefined8 uVar1;
  int iVar2;
  QWORD uVar3;
  qword back_chain;
  qword local_230;
  
  uVar1 = __Save_R12_27_thru_31();
  uVar3 = (QWORD)*(uint *)param_3;
  if (((uVar3 - 1 & 0xffffffff) < 0x40) &&
     (iVar2 = FUN_00024d08(uVar1,param_3 + 0x10,uVar3), iVar2 < 0)) {
    XeCryptBnQw_Zero(&local_230,uVar3);
    uVar1 = XeCryptBnQwNeModExp(param_2,uVar1,&local_230,param_3 + 0x10,uVar3);
    return uVar1;
  }
  return 0;
}



undefined8 XeCryptBnQwNeRsaPrvCrypt(undefined8 param_1,undefined8 param_2,QWORD param_3)

{
  QWORD uVar1;
  undefined8 uVar2;
  int iVar3;
  QWORD lVar4;
  QWORD lVar5;
  QWORD lVar6;
  QWORD lVar7;
  QWORD uVar8;
  undefined8 uVar9;
  QWORD uVar10;
  
  uVar1 = ZEXT48(register0x0000000c);
  uVar8 = (QWORD)(*(uint *)param_3 >> 1);
  lVar7 = uVar8 * 8;
  param_3 = ((QWORD)(*(uint *)param_3 & 0xfffffffe) + 2) * 8 + param_3;
  lVar4 = lVar7 + param_3;
  lVar5 = lVar7 + lVar4;
  lVar6 = lVar7 + lVar5;
  lVar7 = lVar7 + lVar6;
  uVar2 = __Save_R12_22_thru_31(param_2,param_1,param_3,lVar4,lVar5,lVar6,lVar7);
  uVar9 = 0;
  if ((uVar8 & 0xffffffff) < 0x21) {
    uVar10 = (QWORD)(uint)((int)uVar8 << 1);
    iVar3 = XeCryptBnQwNeAdd(param_1,param_3,uVar1 - 0x460,uVar10,uVar8);
    if ((((iVar3 != 0) &&
         (iVar3 = XeCryptBnQwNeModExp(uVar1 - 0x360,uVar1 - 0x460,lVar5,param_3,uVar8), iVar3 != 0))
        && (iVar3 = XeCryptBnQwNeAdd(param_1,lVar4,uVar1 - 0x460,uVar10,uVar8), iVar3 != 0)) &&
       (iVar3 = XeCryptBnQwNeModExp(uVar1 - 0x260,uVar1 - 0x460,lVar6,lVar4,uVar8), iVar3 != 0)) {
      lVar5 = FUN_00024b38(uVar1 - 0x460,uVar1 - 0x360,uVar1 - 0x260,uVar8);
      if (lVar5 != 0) {
        do {
          lVar5 = XeCryptBnQwNeAcc(uVar1 - 0x460,uVar1 - 0x460,param_3,uVar8);
        } while (lVar5 == 0);
      }
      FUN_00024600(uVar2,uVar1 - 0x460,lVar7,uVar8);
      iVar3 = XeCryptBnQwNeAdd(uVar2,param_3,uVar1 - 0x460,uVar10,uVar8);
      if (iVar3 != 0) {
        FUN_00024600(uVar2,uVar1 - 0x460,lVar4,uVar8);
        XeCryptBnQw_Zero((uVar8 & 0xffffffff) * 8 + (uVar1 - 0x260),uVar8);
        XeCryptBnQwNeAcc(uVar2,uVar2,uVar1 - 0x260,uVar10);
        uVar9 = 1;
      }
    }
  }
  XeCryptBnQw_Zero(uVar1 - 0x360,0x20);
  XeCryptBnQw_Zero(uVar1 - 0x260,0x40);
  XeCryptBnQw_Zero(uVar1 - 0x460,0x20);
  return uVar9;
}



void XeCryptBnQw_Zero(undefined8 *param_1,QWORD param_2)

{
  if ((int)param_2 == 0) {
    return;
  }
  do {
    *param_1 = 0;
    param_1 = param_1 + 1;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return;
}



void XeCryptBnQw_Copy(undefined8 *param_1,undefined8 *param_2,QWORD param_3)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)((int)param_2 - (int)param_1);
  if ((int)param_3 == 0) {
    return;
  }
  if (param_1 == param_2) {
    return;
  }
  do {
    *(undefined8 *)((int)param_1 + (int)puVar1) = *param_1;
    param_1 = param_1 + 1;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  return;
}



void XeCryptBnQw_SwapDwQwLeBe(undefined8 *param_1,int param_2,QWORD param_3)

{
  undefined8 uVar1;
  uint uVar2;
  
  param_2 = param_2 - (int)param_1;
  if ((int)param_3 == 0) {
    return;
  }
  do {
    uVar1 = *param_1;
    uVar2 = (uint)uVar1;
    *(uint *)((int)param_1 + param_2) =
         uVar2 << 0x18 | (uVar2 & 0xff00) << 8 | uVar2 >> 8 & 0xff00 | uVar2 >> 0x18;
    uVar2 = (uint)((QWORD)uVar1 >> 0x20);
    *(uint *)((int)param_1 + param_2 + 4) =
         uVar2 << 0x18 | (uVar2 & 0xff00) << 8 | uVar2 >> 8 & 0xff00 | uVar2 >> 0x18;
    param_1 = param_1 + 1;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  return;
}



void XeCryptDesEcb(undefined8 param_1,byte *param_2,uint *param_3,int param_4)

{
  undefined *puVar1;
  uint uVar2;
  int in_r2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  QWORD uVar6;
  uint uVar8;
  QWORD lVar7;
  int iVar9;
  QWORD uVar10;
  uint uVar11;
  QWORD uVar12;
  QWORD uVar13;
  uint *puVar14;
  
  puVar3 = (uint *)__Save_R12_16_thru_31();
  iVar4 = 8;
  uVar13 = (QWORD)param_2[7] << 0x18 | (QWORD)param_2[6] << 0x10 |
           (QWORD)param_2[5] << 8 | (QWORD)param_2[4];
  uVar12 = (QWORD)
           (((uint)param_2[3] << 0x18 | (uint)param_2[2] << 0x10 | (uint)param_2[1] << 8 |
            (uint)*param_2) << 4 | ((uint)param_2[3] << 0x18) >> 0x1c);
  uVar10 = (uVar13 ^ uVar12) & 0xfffffffff0f0f0f0;
  uVar8 = (uint)uVar13 ^ (uint)uVar10;
  uVar12 = uVar12 ^ uVar10;
  uVar8 = uVar8 << 0x14 | uVar8 >> 0xc;
  uVar5 = ((uint)uVar12 ^ uVar8) & 0xfff0000f;
  uVar8 = uVar5 ^ uVar8;
  uVar12 = uVar5 ^ uVar12;
  uVar13 = (QWORD)(uVar8 << 0xe | uVar8 >> 0x12);
  uVar10 = (uVar13 ^ uVar12) & 0x33333333;
  uVar8 = (uint)uVar12 ^ (uint)uVar10;
  uVar13 = uVar13 ^ uVar10;
  uVar8 = uVar8 << 0x16 | uVar8 >> 10;
  uVar5 = (uVar8 ^ (uint)uVar13) & 0x3fc03fc;
  uVar8 = uVar5 ^ uVar8;
  uVar13 = uVar5 ^ uVar13;
  uVar12 = (QWORD)(uVar8 << 9 | uVar8 >> 0x17);
  uVar10 = (uVar13 ^ uVar12) & 0xffffffffaaaaaaaa;
  uVar8 = (uint)uVar13 ^ (uint)uVar10;
  uVar12 = uVar12 ^ uVar10;
  uVar10 = (QWORD)(uVar8 << 1 | uVar8 >> 0x1f);
  puVar1 = &0x14f90 + in_r2;
  if (param_4 == 0) {
    iVar9 = 0x1c;
    puVar14 = puVar3 + 0x1e;
    do {
      uVar6 = *puVar14 ^ uVar12;
      uVar5 = *(uint *)((int)((QWORD)(iVar9 + 3) << 2) + (int)puVar3) ^ (uint)uVar12;
      uVar8 = uVar5 >> 4;
      uVar13 = (QWORD)(uVar5 << 0x1c | uVar8);
      uVar10 = (*(uint *)(&0x15590 + ((uint)(uVar6 >> 0x18) & 0xfc) + in_r2) ^
                *(uint *)(&0x15390 + ((uint)(uVar6 >> 0x10) & 0xfc) + in_r2) ^
                *(uint *)(&0x15190 + ((uint)(uVar6 >> 8) & 0xfc) + in_r2) ^
                *(uint *)(&0x15690 + ((uint)(uVar13 >> 0x18) & 0xfc) + in_r2) ^
                *(uint *)(&0x15490 + ((uint)(uVar13 >> 0x10) & 0xfc) + in_r2) ^
                *(uint *)(&0x15290 + ((uint)(uVar13 >> 8) & 0xfc) + in_r2) ^
                *(uint *)(puVar1 + ((uint)uVar6 & 0xfc)) ^
               *(uint *)(&0x15090 + (uVar8 & 0xfc) + in_r2)) ^ uVar10;
      uVar6 = *(uint *)((int)((QWORD)iVar9 << 2) + (int)puVar3) ^ uVar10;
      uVar5 = (uint)uVar10;
      uVar11 = *(uint *)((int)((QWORD)(iVar9 + 1) << 2) + (int)puVar3) ^ uVar5;
      uVar8 = uVar11 >> 4;
      uVar13 = (QWORD)(uVar11 << 0x1c | uVar8);
      iVar4 = iVar4 + -1;
      puVar14 = puVar14 + -4;
      iVar9 = iVar9 + -4;
      uVar12 = (*(uint *)(&0x15590 + ((uint)(uVar6 >> 0x18) & 0xfc) + in_r2) ^
                *(uint *)(&0x15390 + ((uint)(uVar6 >> 0x10) & 0xfc) + in_r2) ^
                *(uint *)(&0x15190 + ((uint)(uVar6 >> 8) & 0xfc) + in_r2) ^
                *(uint *)(&0x15690 + ((uint)(uVar13 >> 0x18) & 0xfc) + in_r2) ^
                *(uint *)(&0x15490 + ((uint)(uVar13 >> 0x10) & 0xfc) + in_r2) ^
                *(uint *)(&0x15290 + ((uint)(uVar13 >> 8) & 0xfc) + in_r2) ^
                *(uint *)(puVar1 + ((uint)uVar6 & 0xfc)) ^
               *(uint *)(&0x15090 + (uVar8 & 0xfc) + in_r2)) ^ uVar12;
      uVar8 = (uint)uVar12;
    } while (iVar4 != 0);
  }
  else {
    lVar7 = 2;
    puVar14 = puVar3;
    do {
      uVar6 = *puVar14 ^ uVar12;
      uVar5 = puVar3[(int)lVar7 + -1] ^ (uint)uVar12;
      uVar8 = uVar5 >> 4;
      uVar13 = (QWORD)(uVar5 << 0x1c | uVar8);
      uVar10 = (*(uint *)(&0x15590 + ((uint)(uVar6 >> 0x18) & 0xfc) + in_r2) ^
                *(uint *)(&0x15390 + ((uint)(uVar6 >> 0x10) & 0xfc) + in_r2) ^
                *(uint *)(&0x15190 + ((uint)(uVar6 >> 8) & 0xfc) + in_r2) ^
                *(uint *)(&0x15690 + ((uint)(uVar13 >> 0x18) & 0xfc) + in_r2) ^
                *(uint *)(&0x15490 + ((uint)(uVar13 >> 0x10) & 0xfc) + in_r2) ^
                *(uint *)(&0x15290 + ((uint)(uVar13 >> 8) & 0xfc) + in_r2) ^
                *(uint *)(puVar1 + ((uint)uVar6 & 0xfc)) ^
               *(uint *)(&0x15090 + (uVar8 & 0xfc) + in_r2)) ^ uVar10;
      uVar6 = *(uint *)((int)(lVar7 << 2) + (int)puVar3) ^ uVar10;
      uVar5 = (uint)uVar10;
      uVar8 = (puVar3[(int)lVar7 + 1] ^ uVar5) >> 4;
      uVar13 = (QWORD)((puVar3[(int)lVar7 + 1] ^ uVar5) << 0x1c | uVar8);
      iVar4 = iVar4 + -1;
      puVar14 = puVar14 + 4;
      lVar7 = lVar7 + 4;
      uVar12 = (*(uint *)(&0x15590 + ((uint)(uVar6 >> 0x18) & 0xfc) + in_r2) ^
                *(uint *)(&0x15390 + ((uint)(uVar6 >> 0x10) & 0xfc) + in_r2) ^
                *(uint *)(&0x15190 + ((uint)(uVar6 >> 8) & 0xfc) + in_r2) ^
                *(uint *)(&0x15690 + ((uint)(uVar13 >> 0x18) & 0xfc) + in_r2) ^
                *(uint *)(&0x15490 + ((uint)(uVar13 >> 0x10) & 0xfc) + in_r2) ^
                *(uint *)(&0x15290 + ((uint)(uVar13 >> 8) & 0xfc) + in_r2) ^
                *(uint *)(puVar1 + ((uint)uVar6 & 0xfc)) ^
               *(uint *)(&0x15090 + (uVar8 & 0xfc) + in_r2)) ^ uVar12;
      uVar8 = (uint)uVar12;
    } while (iVar4 != 0);
  }
  uVar8 = uVar8 << 0x1f | uVar8 >> 1;
  uVar11 = (uVar5 ^ uVar8) & 0xaaaaaaaa;
  uVar5 = uVar11 ^ uVar5;
  uVar11 = uVar11 ^ uVar8;
  uVar8 = uVar5 << 0x17 | uVar5 >> 9;
  uVar5 = (uVar8 ^ uVar11) & 0x3fc03fc;
  uVar8 = uVar8 ^ uVar5;
  uVar11 = uVar11 ^ uVar5;
  uVar8 = uVar8 << 10 | uVar8 >> 0x16;
  uVar2 = (uVar11 ^ uVar8) & 0x33333333;
  uVar11 = uVar2 ^ uVar11;
  uVar2 = uVar2 ^ uVar8;
  uVar8 = uVar11 << 0x12 | uVar11 >> 0xe;
  uVar5 = (uVar2 ^ uVar8) & 0xfff0000f;
  uVar8 = uVar8 ^ uVar5;
  uVar2 = uVar2 ^ uVar5;
  uVar5 = uVar8 << 0xc | uVar8 >> 0x14;
  uVar8 = (uVar5 ^ uVar2) & 0xf0f0f0f0;
  uVar5 = uVar8 ^ uVar5;
  uVar8 = (uVar8 ^ uVar2) >> 4;
  *param_3 = uVar8 << 0x18 | (uVar8 & 0xff00) << 8 | (uVar8 & 0xff0000) >> 8 |
             (uVar2 << 0x1c | uVar8) >> 0x18;
  param_3[1] = uVar5 << 0x18 | (uVar5 & 0xff00) << 8 | uVar5 >> 8 & 0xff00 | uVar5 >> 0x18;
  return;
}



void XeCryptDesCbc(undefined8 param_1,QWORD param_2,undefined8 param_3,QWORD param_4,
                  QWORD *param_5,int param_6)

{
  undefined8 uVar1;
  QWORD uVar2;
  QWORD uVar3;
  uint uVar4;
  qword back_chain;
  qword local_50;
  qword local_48;
  
  uVar4 = (uint)param_3;
  uVar1 = __Save_R12_26_thru_31();
  uVar4 = uVar4 >> 3;
  uVar3 = *param_5;
  if (param_6 == 0) {
    while (uVar4 != 0) {
      uVar2 = *(QWORD *)param_2;
      uVar1 = XeCryptDesEcb(uVar1,&local_50,&local_48,0);
      uVar4 = uVar4 - 1;
      param_2 = param_2 + 8;
      *(QWORD *)param_4 = local_48 ^ uVar3;
      param_4 = param_4 + 8;
      uVar3 = uVar2;
    }
  }
  else {
    while (uVar4 != 0) {
      uVar3 = *(QWORD *)param_2 ^ uVar3;
      uVar1 = XeCryptDesEcb(uVar1,&local_50,&local_50,1);
      uVar4 = uVar4 - 1;
      param_2 = param_2 + 8;
      *(QWORD *)param_4 = uVar3;
      param_4 = param_4 + 8;
    }
  }
  *param_5 = uVar3;
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void XeCryptDes3Ecb(QWORD param_1,undefined8 param_2,undefined8 param_3,int param_4)

{
  qword back_chain;
  qword local_10;
  qword local_8;
  
  if (param_4 == 0) {
    XeCryptDesEcb(param_1 + 0x100,param_2,param_3,0);
    XeCryptDesEcb(param_1 + 0x80,param_3);
  }
  else {
    XeCryptDesEcb();
    XeCryptDesEcb(param_1 + 0x80,param_3);
    param_1 = param_1 + 0x100;
  }
  XeCryptDesEcb(param_1,param_3);
  return;
}



void XeCryptDes3Cbc(undefined8 param_1,QWORD param_2,undefined8 param_3,QWORD param_4,
                   QWORD *param_5,int param_6)

{
  QWORD lVar1;
  QWORD uVar2;
  QWORD uVar3;
  uint uVar4;
  qword back_chain;
  qword local_60;
  qword local_58;
  
  uVar4 = (uint)param_3;
  lVar1 = __Save_R12_23_thru_31();
  uVar4 = uVar4 >> 3;
  uVar2 = *param_5;
  if (param_6 == 0) {
    if (uVar4 != 0) {
      uVar3 = uVar2;
      do {
        uVar2 = *(QWORD *)param_2;
        XeCryptDesEcb(lVar1 + 0x100,&local_58,&local_60,0);
        XeCryptDesEcb(lVar1 + 0x80,&local_60,&local_60,1);
        XeCryptDesEcb(lVar1,&local_60,&local_60,0);
        uVar4 = uVar4 - 1;
        param_2 = param_2 + 8;
        *(QWORD *)param_4 = local_60 ^ uVar3;
        param_4 = param_4 + 8;
        uVar3 = uVar2;
      } while (uVar4 != 0);
    }
  }
  else {
    if (uVar4 != 0) {
      do {
        uVar2 = *(QWORD *)param_2 ^ uVar2;
        XeCryptDesEcb(lVar1,&local_60,&local_60,1);
        XeCryptDesEcb(lVar1 + 0x80,&local_60,&local_60,0);
        XeCryptDesEcb(lVar1 + 0x100,&local_60,&local_60,1);
        uVar4 = uVar4 - 1;
        param_2 = param_2 + 8;
        *(QWORD *)param_4 = uVar2;
        param_4 = param_4 + 8;
      } while (uVar4 != 0);
    }
  }
  *param_5 = uVar2;
  return;
}



void XeCryptDesKey(undefined8 param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  QWORD in_r2;
  QWORD lVar4;
  int iVar5;
  uint *puVar6;
  QWORD uVar7;
  uint uVar8;
  QWORD uVar9;
  uint uVar10;
  uint uVar11;
  uint *puVar12;
  QWORD uVar13;
  uint uVar14;
  
  puVar6 = (uint *)__Save_R12_17_thru_31();
  lVar4 = ZEXT48(&0x15f90) + in_r2;
  uVar13 = (QWORD)param_2[3] << 0x18 | (QWORD)param_2[2] << 0x10 |
           (QWORD)param_2[1] << 8 | (QWORD)*param_2;
  uVar9 = (QWORD)param_2[7] << 0x18 | (QWORD)param_2[6] << 0x10 | (QWORD)param_2[5] << 8
          | (QWORD)param_2[4];
  iVar5 = 0x10;
  uVar7 = (uVar9 >> 4 ^ uVar13) & 0xf0f0f0f;
  uVar13 = uVar7 ^ uVar13;
  uVar9 = (uint)((int)uVar7 << 4) ^ uVar9;
  uVar14 = (uint)uVar13;
  uVar7 = (uVar14 << 0x12 ^ uVar13) & 0xffffffffcccc0000;
  uVar13 = ((uint)((int)uVar9 << 0x12) ^ uVar9) & 0xffffffffcccc0000;
  uVar14 = (uint)(uVar7 >> 0x12) ^ (uint)uVar7 ^ uVar14;
  uVar9 = uVar13 >> 0x12 ^ uVar13 ^ uVar9;
  uVar8 = ((uint)(uVar9 >> 1) ^ uVar14) & 0x55555555;
  uVar14 = uVar8 ^ uVar14;
  uVar10 = uVar8 << 1 ^ (uint)uVar9;
  uVar8 = (uVar14 >> 8 ^ uVar10) & 0xff00ff;
  uVar10 = uVar8 ^ uVar10;
  uVar14 = uVar8 << 8 ^ uVar14;
  uVar8 = (uVar10 >> 1 ^ uVar14) & 0x55555555;
  uVar14 = uVar8 ^ uVar14;
  uVar10 = uVar8 << 1 ^ uVar10;
  uVar8 = uVar14 & 0xfffffff;
  uVar10 = (uVar10 >> 0xc & 0xff0 | uVar14 & 0xf0000000) >> 4 | (uVar10 & 0xff) << 0x10 |
           uVar10 & 0xff00;
  iVar3 = (int)in_r2;
  do {
    if (*(char *)lVar4 == '\0') {
      uVar14 = uVar8 << 0x1b;
      uVar1 = uVar8 >> 1;
      uVar11 = uVar10 << 0x1b;
      uVar2 = uVar10 >> 1;
    }
    else {
      uVar14 = uVar8 << 0x1a;
      uVar1 = uVar8 >> 2;
      uVar11 = uVar10 << 0x1a;
      uVar2 = uVar10 >> 2;
    }
    uVar8 = uVar14 & 0xfffffff | uVar1;
    uVar10 = uVar11 & 0xfffffff | uVar2;
    iVar5 = iVar5 + -1;
    lVar4 = lVar4 + 1;
    uVar14 = *(uint *)(&0x15a90 +
                      ((((uVar14 & 0xfffffff | uVar1 & 0xe000000) >> 1 | uVar1 & 0xc00000) >> 1 |
                       uVar1 & 0x100000) >> 0x12) + iVar3) |
             *(uint *)(&0x15890 + (((uVar1 & 0x1e00) >> 1 | uVar1 & 0xc0) >> 4) + iVar3) |
             *(uint *)(&0x15990 + (((uVar1 & 0xc0000) >> 1 | uVar1 & 0x1e000) >> 0xb) + iVar3)
             | *(uint *)(&0x15790 + (uVar1 & 0x3f) * 4 + iVar3);
    uVar11 = *(uint *)(&0x15e90 +
                      (((uVar11 & 0xfffffff | uVar2 & 0xc000000) >> 1 | uVar2 & 0x1e00000) >> 0x13)
                      + iVar3) |
             *(uint *)(&0x15c90 + (((uVar2 & 0x3c00) >> 1 | uVar2 & 0x180) >> 5) + iVar3) |
             *(uint *)(&0x15d90 + ((uVar2 & 0x1f8000) >> 0xd) + iVar3) |
             *(uint *)(&0x15b90 + (uVar2 & 0x3f) * 4 + iVar3);
    puVar12 = puVar6 + 1;
    *puVar6 = (uVar11 << 0x10 | uVar14 & 0xffff) << 2 | (uVar11 << 0x10) >> 0x1e;
    puVar6 = puVar6 + 2;
    *puVar12 = (uVar14 >> 0x10 | uVar11 & 0xffff0000) << 6 | uVar11 >> 0x1a;
  } while (iVar5 != 0);
  return;
}



void XeCryptDes3Key(undefined8 param_1,QWORD param_2)

{
  QWORD lVar1;
  int iVar2;
  qword back_chain;
  
  lVar1 = __Save_R12_29_thru_31();
  iVar2 = 3;
  do {
    XeCryptDesKey(lVar1,param_2);
    iVar2 = iVar2 + -1;
    lVar1 = lVar1 + 0x80;
    param_2 = param_2 + 8;
  } while (iVar2 != 0);
  return;
}



void XeCryptDesParity(byte *param_1,int param_2,byte *param_3)
{
  int in_r2;
  byte bVar1;
  int iVar2;
  
  if (param_2 == 0) {
    return;
  }
  do {
    bVar1 = *param_1;
    param_1 = param_1 + 1;
    iVar2 = (uint)(byte)(&0x15fa0 + in_r2)[bVar1 >> 4] +
            (uint)(byte)(&0x15fa0 + in_r2)[(uint)bVar1 & 0xf];
    if (iVar2 == (iVar2 >> 1) * 2) {
      bVar1 = bVar1 ^ 1;
    }
    param_2 = param_2 + -1;
    *param_3 = bVar1;
    param_3 = param_3 + 1;
  } while (param_2 != 0);
  return;
}

void XeCryptShaInit(undefined4 *param_1)
{
  *param_1 = 0;
  param_1[1] = 0x67452301;
  param_1[2] = 0xefcdab89;
  param_1[3] = 0x98badcfe;
  param_1[4] = 0x10325476;
  param_1[5] = 0xc3d2e1f0;
  return;
}

void XeCryptShaTransform(undefined8 param_1,undefined8 param_2)
{
  uint uVar1;
  int *piVar2;
  uint *puVar4;
  QWORD lVar3;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint *puVar10;
  int iVar11;
  int *piVar12;
  int *piVar13;
  int iVar14;
  int *piVar15;
  int *piVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  qword back_chain;
  word local_190;
  word local_188;
  word local_150;
  
  puVar4 = (uint *)__Save_R12_23_thru_31();
  uVar17 = *puVar4;
  uVar18 = puVar4[1];
  uVar19 = puVar4[2];
  uVar20 = puVar4[3];
  uVar21 = puVar4[4];
  XeCryptBnDw_Copy(param_2,&local_190,0x10);
  iVar14 = 2;
  puVar10 = (uint *)&local_150;
  iVar11 = 0x40;
  do {
    iVar7 = iVar14 + 0xb;
    iVar6 = iVar14 + 6;
    iVar5 = iVar14 + -2;
    lVar3 = (QWORD)iVar14;
    iVar11 = iVar11 + -1;
    iVar14 = iVar14 + 1;
    uVar8 = *(uint *)((int)&local_190 + (int)((QWORD)iVar7 << 2)) ^
            *(uint *)((int)&local_190 + (int)((QWORD)iVar6 << 2)) ^
            *(uint *)((int)&local_190 + (int)((QWORD)iVar5 << 2)) ^
            *(uint *)((int)&local_190 + (int)(lVar3 << 2));
    *puVar10 = uVar8 << 1 | uVar8 >> 0x1f;
    puVar10 = puVar10 + 1;
  } while (iVar11 != 0);
  piVar12 = (int *)&local_188;
  iVar11 = 4;
  piVar16 = (int *)&local_190;
  do {
    piVar15 = piVar16;
    piVar16 = piVar12 + 1;
    uVar8 = uVar18 << 0x1e | uVar18 >> 2;
    iVar14 = *piVar12;
    piVar2 = piVar12 + 2;
    iVar11 = iVar11 + -1;
    uVar18 = ((uVar20 ^ uVar19) & uVar18 ^ uVar20) + (uVar17 << 5 | uVar17 >> 0x1b) + uVar21 +
             *piVar15 + 0x5a827999;
    uVar1 = uVar17 << 0x1e | uVar17 >> 2;
    uVar21 = uVar18 * 0x40000000 | uVar18 >> 2;
    uVar17 = ((uVar19 ^ uVar8) & uVar17 ^ uVar19) + piVar12[-1] + (uVar18 * 0x20 | uVar18 >> 0x1b) +
             uVar20 + 0x5a827999;
    uVar20 = uVar17 * 0x40000000 | uVar17 >> 2;
    piVar12 = piVar12 + 5;
    uVar9 = ((uVar8 ^ uVar1) & uVar18 ^ uVar8) + (uVar17 * 0x20 | uVar17 >> 0x1b) + uVar19 + iVar14
            + 0x5a827999;
    uVar19 = uVar9 * 0x40000000 | uVar9 >> 2;
    uVar18 = ((uVar21 ^ uVar1) & uVar17 ^ uVar1) + *piVar16 + (uVar9 * 0x20 | uVar9 >> 0x1b) + uVar8
             + 0x5a827999;
    uVar17 = ((uVar21 ^ uVar20) & uVar9 ^ uVar21) + *piVar2 + (uVar18 * 0x20 | uVar18 >> 0x1b) +
             uVar1 + 0x5a827999;
    piVar16 = piVar15 + 5;
  } while (iVar11 != 0);
  piVar12 = piVar15 + 7;
  iVar11 = 4;
  do {
    piVar13 = piVar16;
    piVar16 = piVar12 + -1;
    iVar14 = *piVar12;
    uVar8 = uVar18 << 0x1e | uVar18 >> 2;
    piVar2 = piVar12 + 1;
    piVar15 = piVar12 + 2;
    iVar11 = iVar11 + -1;
    uVar18 = (uVar20 ^ uVar19 ^ uVar18) + (uVar17 << 5 | uVar17 >> 0x1b) + uVar21 + *piVar13 +
             0x6ed9eba1;
    uVar1 = uVar17 << 0x1e | uVar17 >> 2;
    uVar21 = uVar18 * 0x40000000 | uVar18 >> 2;
    piVar12 = piVar12 + 5;
    uVar17 = (uVar19 ^ uVar8 ^ uVar17) + *piVar16 + (uVar18 * 0x20 | uVar18 >> 0x1b) + uVar20 +
             0x6ed9eba1;
    uVar20 = uVar17 * 0x40000000 | uVar17 >> 2;
    uVar9 = (uVar18 ^ uVar8 ^ uVar1) + iVar14 + (uVar17 * 0x20 | uVar17 >> 0x1b) + uVar19 +
            0x6ed9eba1;
    uVar19 = uVar9 * 0x40000000 | uVar9 >> 2;
    uVar18 = (uVar21 ^ uVar17 ^ uVar1) + *piVar2 + (uVar9 * 0x20 | uVar9 >> 0x1b) + uVar8 +
             0x6ed9eba1;
    uVar17 = (uVar21 ^ uVar20 ^ uVar9) + *piVar15 + (uVar18 * 0x20 | uVar18 >> 0x1b) + uVar1 +
             0x6ed9eba1;
    piVar16 = piVar13 + 5;
  } while (iVar11 != 0);
  piVar12 = piVar13 + 7;
  iVar11 = 4;
  do {
    piVar13 = piVar16;
    piVar2 = piVar12 + 1;
    iVar14 = *piVar12;
    piVar15 = piVar12 + 2;
    uVar8 = uVar18 << 0x1e | uVar18 >> 2;
    iVar11 = iVar11 + -1;
    iVar5 = ((uVar19 | uVar18) & uVar20 | uVar19 & uVar18) + (uVar17 << 5 | uVar17 >> 0x1b) + uVar21
            + *piVar13;
    uVar18 = iVar5 + 0x8f1bbcdc;
    uVar1 = uVar17 << 0x1e | uVar17 >> 2;
    uVar21 = iVar5 * 0x40000000 | uVar18 >> 2;
    iVar5 = ((uVar8 | uVar17) & uVar19 | uVar8 & uVar17) + piVar12[-1] +
            (uVar18 * 0x20 | uVar18 >> 0x1b) + uVar20;
    piVar16 = piVar13 + 5;
    uVar17 = iVar5 + 0x8f1bbcdc;
    piVar12 = piVar12 + 5;
    uVar20 = iVar5 * 0x40000000 | uVar17 >> 2;
    iVar14 = ((uVar18 | uVar1) & uVar8 | uVar18 & uVar1) + (uVar17 * 0x20 | uVar17 >> 0x1b) + uVar19
             + iVar14;
    uVar9 = iVar14 + 0x8f1bbcdc;
    uVar19 = iVar14 * 0x40000000 | uVar9 >> 2;
    uVar18 = ((uVar21 | uVar17) & uVar1 | uVar21 & uVar17) + *piVar2 +
             (uVar9 * 0x20 | uVar9 >> 0x1b) + uVar8 + 0x8f1bbcdc;
    uVar17 = ((uVar20 | uVar9) & uVar21 | uVar20 & uVar9) + *piVar15 +
             (uVar18 * 0x20 | uVar18 >> 0x1b) + uVar1 + 0x8f1bbcdc;
  } while (iVar11 != 0);
  piVar13 = piVar13 + 7;
  iVar11 = 4;
  do {
    iVar14 = *piVar16;
    piVar12 = piVar13 + -1;
    iVar5 = *piVar13;
    uVar8 = uVar18 << 0x1e | uVar18 >> 2;
    piVar2 = piVar13 + 1;
    piVar15 = piVar13 + 2;
    iVar11 = iVar11 + -1;
    piVar16 = piVar16 + 5;
    uVar18 = (uVar20 ^ uVar19 ^ uVar18) + (uVar17 << 5 | uVar17 >> 0x1b) + uVar21 + iVar14 +
             0xca62c1d6;
    uVar1 = uVar17 << 0x1e | uVar17 >> 2;
    uVar21 = uVar18 * 0x40000000 | uVar18 >> 2;
    piVar13 = piVar13 + 5;
    uVar17 = (uVar19 ^ uVar8 ^ uVar17) + *piVar12 + (uVar18 * 0x20 | uVar18 >> 0x1b) + uVar20 +
             0xca62c1d6;
    uVar20 = uVar17 * 0x40000000 | uVar17 >> 2;
    uVar9 = (uVar18 ^ uVar8 ^ uVar1) + iVar5 + (uVar17 * 0x20 | uVar17 >> 0x1b) + uVar19 +
            0xca62c1d6;
    uVar19 = uVar9 * 0x40000000 | uVar9 >> 2;
    uVar18 = (uVar21 ^ uVar17 ^ uVar1) + *piVar2 + (uVar9 * 0x20 | uVar9 >> 0x1b) + uVar8 +
             0xca62c1d6;
    uVar17 = (uVar21 ^ uVar20 ^ uVar9) + *piVar15 + (uVar18 * 0x20 | uVar18 >> 0x1b) + uVar1 +
             0xca62c1d6;
  } while (iVar11 != 0);
  *puVar4 = *puVar4 + uVar17;
  puVar4[1] = puVar4[1] + uVar18;
  puVar4[2] = puVar4[2] + uVar19;
  puVar4[3] = uVar20 + puVar4[3];
  puVar4[4] = puVar4[4] + uVar21;
  return;
}


void XeCryptShaUpdate(undefined8 param_1,QWORD param_2,QWORD param_3) {
  uint uVar1;
  QWORD lVar2;
  uint uVar3;
  QWORD uVar4;
  qword back_chain;
  
  lVar2 = __Save_R12_25_thru_31();
  uVar3 = *(uint *)lVar2;
  uVar1 = uVar3 & 0x3f;
  uVar4 = (QWORD)uVar1;
  *(uint *)lVar2 = uVar3 + (int)param_3;
  if ((uVar1 != 0) && (0x3f < (uVar4 + param_3 & 0xffffffff))) {
    memcpy((QWORD)uVar1 + lVar2 + 0x18);
    param_2 = (0x40 - uVar4 & 0xffffffff) + param_2;
    param_3 = (uVar4 + param_3) - 0x40;
    XeCryptShaTransform(lVar2 + 4,lVar2 + 0x18);
    uVar4 = 0;
  }
  if ((param_2 & 3) == 0) {
    if (0x3f < (param_3 & 0xffffffff)) {
      uVar3 = (uint)param_3 >> 6;
      do {
        XeCryptShaTransform(lVar2 + 4,param_2);
        uVar3 = uVar3 - 1;
        param_2 = param_2 + 0x40;
        param_3 = param_3 - 0x40;
      } while (uVar3 != 0);
    }
  }
  else {
    if (0x3f < (param_3 & 0xffffffff)) {
      uVar3 = (uint)param_3 >> 6;
      do {
        memcpy(lVar2 + 0x18,param_2,0x40);
        XeCryptShaTransform(lVar2 + 4,lVar2 + 0x18);
        uVar3 = uVar3 - 1;
        param_2 = param_2 + 0x40;
        param_3 = param_3 - 0x40;
      } while (uVar3 != 0);
    }
  }
  if ((param_3 & 0xffffffff) != 0) {
    memcpy(uVar4 + lVar2 + 0x18,param_2,param_3 & 0xffffffff);
  }
  return;
}

void XeCryptShaFinal(undefined8 param_1,undefined8 param_2,QWORD param_3) {
  uint uVar1;
  uint *puVar2;
  QWORD uVar3;
  uint *puVar4;
  qword back_chain;
  dword local_50;
  
  puVar2 = (uint *)__Save_R12_25_thru_31();
  puVar4 = puVar2 + 6;
  uVar1 = *puVar2 & 0x3f;
  memset((undefined *)(uVar1 + (int)puVar4),0,0x40 - uVar1);
  *(undefined *)(uVar1 + (int)puVar4) = 0x80;
  if (0x40 - uVar1 < 9) {
    XeCryptShaTransform(puVar2 + 1,puVar4);
    memset(puVar4,0,uVar1 + 1);
  }
  memcpy(puVar2 + 0x15,&local_50,4);
  XeCryptShaTransform(puVar2 + 1,puVar4);
  if ((param_3 & 0xffffffff) != 0) {
    uVar3 = param_3 & 0xffffffff;
    if (0x13 < (param_3 & 0xffffffff)) {
      uVar3 = 0x14;
    }
    memcpy(param_2,puVar2 + 1,uVar3);
  }
  return;
}



void XeCryptSha(undefined8 param_1,QWORD param_2,undefined8 param_3,QWORD param_4, undefined8 param_5,QWORD param_6,undefined8 param_7,undefined8 param_8)
{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  qword back_chain;
  dword local_a0;
  dword local_9c;
  dword local_98;
  dword local_94;
  dword local_90;
  dword local_8c;
  dword local_48;
  
  uVar2 = __Save_R12_26_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  if ((param_2 & 0xffffffff) != 0) {
    XeCryptShaUpdate(&local_a0,uVar2,param_2);
  }
  if ((param_4 & 0xffffffff) != 0) {
    XeCryptShaUpdate(&local_a0,param_3,param_4);
  }
  if ((param_6 & 0xffffffff) != 0) {
    XeCryptShaUpdate(&local_a0,param_5,param_6);
  }
  XeCryptShaFinal(&local_a0,param_7,param_8);
  FUN_00000204((QWORD)uVar1);
  return;
}



void XeCryptHmacShaInit(undefined8 param_1,undefined8 param_2,QWORD param_3)
{
  uint uVar1;
  int in_r2;
  undefined4 *puVar2;
  QWORD *puVar3;
  QWORD *puVar4;
  int iVar5;
  int iVar6;
  qword back_chain;
  word local_c0;
  word local_80;
  dword local_40;
  
  puVar2 = (undefined4 *)__Save_R12_27_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  puVar2[1] = 0x67452301;
  puVar2[2] = 0xefcdab89;
  *puVar2 = 0;
  puVar2[3] = 0x98badcfe;
  puVar2[4] = 0x10325476;
  puVar2[5] = 0xc3d2e1f0;
  puVar2[0x16] = 0;
  puVar2[0x17] = 0x67452301;
  puVar2[0x18] = 0xefcdab89;
  puVar2[0x19] = 0x98badcfe;
  puVar2[0x1a] = 0x10325476;
  puVar2[0x1b] = 0xc3d2e1f0;
  if (0x40 < (param_3 & 0xffffffff)) {
    param_3 = 0x40;
  }
  memset(&local_c0,0,0x40);
  memset(&local_80,0,0x40);
  memcpy(&local_c0,param_2,param_3 & 0xffffffff);
  memcpy(&local_80,param_2,param_3 & 0xffffffff);
  iVar6 = 0;
  iVar5 = 8;
  do {
    puVar4 = (QWORD *)((int)&local_c0 + iVar6);
    puVar3 = (QWORD *)((int)&local_80 + iVar6);
    iVar5 = iVar5 + -1;
    iVar6 = iVar6 + 8;
    *puVar4 = *puVar4 ^ 0x3636363636363636;
    *puVar3 = *puVar3 ^ 0x5c5c5c5c5c5c5c5c;
  } while (iVar5 != 0);
  XeCryptShaUpdate(puVar2,&local_c0,0x40);
  XeCryptShaUpdate(puVar2 + 0x16,&local_80,0x40);
  FUN_00000204((QWORD)uVar1);
  return;
}

void XeCryptHmacShaUpdate(undefined8 param_1,QWORD param_2,QWORD param_3)
{
  uint uVar1;
  QWORD lVar2;
  uint uVar3;
  QWORD uVar4;
  
  lVar2 = __Save_R12_25_thru_31();
  uVar3 = *(uint *)lVar2;
  uVar1 = uVar3 & 0x3f;
  uVar4 = (QWORD)uVar1;
  *(uint *)lVar2 = uVar3 + (int)param_3;
  if ((uVar1 != 0) && (0x3f < (uVar4 + param_3 & 0xffffffff))) {
    memcpy((QWORD)uVar1 + lVar2 + 0x18);
    param_2 = (0x40 - uVar4 & 0xffffffff) + param_2;
    param_3 = (uVar4 + param_3) - 0x40;
    XeCryptShaTransform(lVar2 + 4,lVar2 + 0x18);
    uVar4 = 0;
  }
  if ((param_2 & 3) == 0) {
    if (0x3f < (param_3 & 0xffffffff)) {
      uVar3 = (uint)param_3 >> 6;
      do {
        XeCryptShaTransform(lVar2 + 4,param_2);
        uVar3 = uVar3 - 1;
        param_2 = param_2 + 0x40;
        param_3 = param_3 - 0x40;
      } while (uVar3 != 0);
    }
  }
  else {
    if (0x3f < (param_3 & 0xffffffff)) {
      uVar3 = (uint)param_3 >> 6;
      do {
        memcpy(lVar2 + 0x18,param_2,0x40);
        XeCryptShaTransform(lVar2 + 4,lVar2 + 0x18);
        uVar3 = uVar3 - 1;
        param_2 = param_2 + 0x40;
        param_3 = param_3 - 0x40;
      } while (uVar3 != 0);
    }
  }
  if ((param_3 & 0xffffffff) != 0) {
    memcpy(uVar4 + lVar2 + 0x18,param_2,param_3 & 0xffffffff);
  }
  return;
}



void XeCryptHmacShaFinal(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  QWORD lVar1;
  qword back_chain;
  
  lVar1 = __Save_R12_28_thru_31();
  XeCryptShaFinal(lVar1,0,0);
  XeCryptShaUpdate(lVar1 + 0x58,lVar1 + 4,0x14);
  XeCryptShaFinal(lVar1 + 0x58,param_2,param_3);
  return;
}



void XeCryptHmacSha(undefined8 param_1,undefined8 param_2,undefined8 param_3,QWORD param_4,
                   undefined8 param_5,QWORD param_6,undefined8 param_7,QWORD param_8)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  undefined8 param_1_00;
  uint param_2_00;
  qword back_chain;
  word local_f0;
  dword local_40;
  
  uVar2 = __Save_R12_26_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  XeCryptHmacShaInit(&local_f0,uVar2,param_2);
  if ((param_4 & 0xffffffff) != 0) {
    XeCryptShaUpdate(&local_f0,param_3,param_4);
  }
  if ((param_6 & 0xffffffff) != 0) {
    XeCryptShaUpdate(&local_f0,param_5,param_6);
  }
  if ((param_8 & 0xffffffff) != 0) {
    XeCryptShaUpdate(&local_f0,param_7,param_8);
  }
  XeCryptHmacShaFinal(&local_f0,param_1_00,(QWORD)param_2_00);
  FUN_00000204((QWORD)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void XeCryptRc4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  uint uVar1;
  int in_r2;
  qword back_chain;
  word local_120;
  dword local_1c;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)(in_r2 + 0x10000);
  XeCryptRc4Key(&local_120,param_1,param_2);
  XeCryptRc4Ecb(&local_120,param_3,param_4);
  FUN_00000204((QWORD)uVar1);
  return;
}



void XeCryptRc4Key(QWORD *param_1,int param_2,int param_3)

{
  byte bVar1;
  QWORD *plVar2;
  QWORD lVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  QWORD lVar7;
  
  lVar3 = 0x1020304050607;
  lVar7 = 8;
  do {
    plVar2 = param_1;
    *plVar2 = lVar3;
    plVar2[1] = lVar3 + 0x808080808080808;
    plVar2[2] = lVar3 + 0x1010101010101010;
    plVar2[3] = lVar3 + 0x1818181818181818;
    lVar3 = lVar3 + 0x2020202020202020;
    lVar7 = lVar7 + -1;
    param_1 = plVar2 + 4;
  } while (lVar7 != 0);
  iVar4 = 0;
  *(undefined2 *)(plVar2 + 4) = 0;
  plVar2 = plVar2 + -0x1c;
  uVar5 = 0;
  iVar6 = 0;
  lVar3 = 0x100;
  do {
    bVar1 = *(byte *)((int)plVar2 + iVar4);
    uVar5 = uVar5 + bVar1 + (uint)*(byte *)(param_2 + iVar6) & 0xff;
    iVar6 = iVar6 + 1;
    *(undefined *)((int)plVar2 + iVar4) = *(undefined *)((int)plVar2 + uVar5);
    iVar4 = iVar4 + 1;
    *(byte *)((int)plVar2 + uVar5) = bVar1;
    if (iVar6 == param_3) {
      iVar6 = 0;
    }
    lVar3 = lVar3 + -1;
  } while (lVar3 != 0);
  return;
}



void XeCryptRc4Ecb(int param_1,byte *param_2,QWORD param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  QWORD uVar5;
  QWORD uVar6;
  
  if ((int)param_3 == 0) {
    return;
  }
  uVar5 = (QWORD)*(byte *)(param_1 + 0x100);
  uVar6 = (QWORD)*(byte *)(param_1 + 0x101);
  do {
    uVar3 = (int)uVar5 + 1U & 0xff;
    uVar5 = (QWORD)uVar3;
    bVar1 = *(byte *)(param_1 + uVar3);
    uVar4 = (int)uVar6 + (uint)bVar1 & 0xff;
    uVar6 = (QWORD)uVar4;
    bVar2 = *(byte *)(param_1 + uVar4);
    *(byte *)(param_1 + uVar3) = bVar2;
    *(byte *)(param_1 + uVar4) = bVar1;
    *param_2 = *(byte *)(param_1 + ((uint)bVar1 + (uint)bVar2 & 0xff)) ^ *param_2;
    param_2 = param_2 + 1;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  *(undefined *)(param_1 + 0x100) = (char)uVar3;
  *(undefined *)(param_1 + 0x101) = (char)uVar4;
  return;
}



void XeCryptRotSum(QWORD *param_1,QWORD *param_2,int param_3)

{
  QWORD lVar1;
  QWORD lVar2;
  QWORD uVar3;
  QWORD uVar4;
  QWORD uVar5;
  
  lVar2 = *param_1;
  uVar3 = param_1[1];
  lVar1 = param_1[2];
  uVar4 = param_1[3];
  while (param_3 != 0) {
    uVar5 = *param_2;
    uVar3 = uVar5 + uVar3;
    uVar4 = uVar4 - uVar5;
    lVar2 = (QWORD)(uVar3 < uVar5) + lVar2;
    uVar3 = uVar3 * 0x20000000 | uVar3 >> 0x23;
    param_3 = param_3 + -1;
    lVar1 = lVar1 - (QWORD)(uVar5 < uVar4);
    uVar4 = uVar4 * 0x80000000 | uVar4 >> 0x21;
    param_2 = param_2 + 1;
  }
  *param_1 = lVar2;
  param_1[1] = uVar3;
  param_1[2] = lVar1;
  param_1[3] = uVar4;
  return;
}



void XeCryptRotSumSha(undefined8 param_1,QWORD param_2,undefined8 param_3,QWORD param_4, undefined8 param_5,undefined8 param_6) {
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  qword back_chain;
  qword local_c0;
  qword local_b8;
  qword local_b0;
  qword local_a8;
  word local_a0;
  dword local_48;
  
  uVar2 = __Save_R12_26_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  XeCryptRotSum(&local_c0,uVar2,param_2 >> 3 & 0x1fffffff);
  XeCryptRotSum(&local_c0,param_3,param_4 >> 3 & 0x1fffffff);
  XeCryptShaInit(&local_a0);
  XeCryptShaUpdate(&local_a0,&local_c0,0x20);
  XeCryptShaUpdate(&local_a0,&local_c0,0x20);
  XeCryptShaUpdate(&local_a0,uVar2,param_2);
  XeCryptShaUpdate(&local_a0,param_3,param_4);
  XeCryptShaUpdate(&local_a0,&local_c0,0x20);
  XeCryptShaUpdate(&local_a0,&local_c0,0x20);
  XeCryptShaFinal(&local_a0,param_5,param_6);
  FUN_00000204((QWORD)uVar1);
  return;
}



QWORD XeCryptMemDiff(byte *param_1,byte *param_2,QWORD param_3)

{
  byte bVar1;
  byte bVar2;
  QWORD uVar3;
  
  uVar3 = 0;
  if ((int)param_3 != 0) {
    bVar1 = *param_2;
    bVar2 = *param_1;
    while( true ) {
      uVar3 = uVar3 | bVar1 ^ bVar2;
      param_3 = param_3 + -1;
      if (param_3 == 0) break;
      param_2 = param_2 + 1;
      bVar1 = *param_2;
      param_1 = param_1 + 1;
      bVar2 = *param_1;
    }
  }
  return uVar3;
}



void FUN_00023538(undefined8 param_1,QWORD param_2,QWORD *param_3,undefined8 param_4,
                 undefined8 param_5)

{
  byte bVar1;
  QWORD in_r2;
  undefined8 uVar2;
  QWORD *plVar3;
  qword back_chain;
  word local_1a0;
  
  uVar2 = __Save_R12_26_thru_31();
  memcpy(param_5,uVar2,0x10);
  if ((param_2 & 0xffffffff) != 0) {
    do {
      plVar3 = (QWORD *)param_4;
      bVar1 = *(byte *)(plVar3 + 1);
      *plVar3 = *plVar3 << 1;
      plVar3[1] = plVar3[1] << 1;
      *(byte *)((int)plVar3 + 7) = bVar1 >> 7 | *(byte *)((int)plVar3 + 7);
      *(byte *)((int)plVar3 + 0xf) = *(byte *)param_3 >> 7 | *(byte *)((int)plVar3 + 0xf);
      bVar1 = *(byte *)(param_3 + 1);
      *param_3 = *param_3 << 1;
      param_3[1] = param_3[1] << 1;
      *(byte *)((int)param_3 + 7) = bVar1 >> 7 | *(byte *)((int)param_3 + 7);
      FUN_00023e70(&local_1a0,param_5,ZEXT48(&0x13e60) + in_r2);
      FUN_0002402c(&local_1a0,param_4,param_5,ZEXT48(&0x11d60) + in_r2);
      param_2 = param_2 - 1;
    } while ((param_2 & 0xffffffff) != 0);
  }
  return;
}



void FUN_00023620(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  qword back_chain;
  word local_50;
  word local_40;
  dword local_30;
  
  uVar2 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  memcpy(&local_40);
  memcpy(&local_50,param_3,0x10);
  FUN_00023538(uVar2,0x80,&local_40,&local_50,param_4);
  FUN_00000204((QWORD)uVar1);
  return;
}



QWORD FUN_00023698(QWORD param_1,uint param_2,uint param_3)

{
  return (QWORD)
         (((uint)(param_1 >> 0x11) & 0x80 | (uint)(param_1 >> 0x19) & 0x7f) +
          ((uint)(param_1 >> 0x25) & 7 | (uint)(param_1 >> 0x1d) & 0xf8) +
          ((uint)(param_1 >> 0x16) & 3 | (uint)(param_1 >> 0xe) & 0xfc) +
          ((uint)(param_1 >> 0xb) & 0x1f | (uint)(param_1 >> 3) & 0xe0) +
          ((uint)(param_1 >> 7) & 1 | (uint)(param_1 << 1) & 0xfe) & 0xff ^ param_2 & 0xff ^
         param_3 & 0xff) ^ 0x3a;
}



QWORD FUN_00023718(QWORD param_1,undefined8 param_2,undefined8 param_3) {
  return (QWORD)
         (((uint)(param_1 >> 0x27) & 1 | (uint)(param_1 >> 0x1f) & 0xfe) +
          ((uint)(param_1 >> 0x1b) & 0x1f | (uint)(param_1 >> 0x13) & 0xe0) +
          ((uint)(param_1 >> 10) & 0x3f | (uint)(param_1 >> 2) & 0xc0) +
          ((uint)(param_1 >> 0x14) & 0xf | (uint)(param_1 >> 0xc) & 0xf0) + ((uint)param_1 & 0xff) &
          0xff ^ (uint)((QWORD)param_2 >> 8) & 0xff ^ (uint)((QWORD)param_3 >> 8) & 0xff) ^
         0x72;
}


//23830
void HvSetupShaSaltedHash(undefined8 param_1,undefined8 param_2,QWORD param_3,QWORD param_4) {
  uint uVar1;
  byte *pbVar2;
  int in_r2;
  undefined8 uVar3;
  QWORD uVar4;
  uint uVar6;
  QWORD lVar5;
  qword back_chain;
  dword local_c0;
  word local_b0;
  word local_50;
  dword local_3c;
  
  uVar3 = __Save_R12_27_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  while ((param_4 & 0xffffffff) != 0) {
    XeCryptShaInit(&local_b0);
    XeCryptShaUpdate(&local_b0,uVar3,param_2);
    XeCryptShaUpdate(&local_b0,&local_c0,4);
    XeCryptShaFinal(&local_b0,&local_50,0x14);
    uVar6 = 0x14;
    if ((param_4 & 0xffffffff) < 0x15) {
      uVar6 = (uint)param_4;
    }
    if (uVar6 != 0) {
      uVar4 = (QWORD)uVar6;
      lVar5 = param_3;
      do {
        pbVar2 = (byte *)lVar5;
        uVar4 = uVar4 - 1;
        *pbVar2 = pbVar2[(int)((int)&local_50 - (int)param_3)] ^ *pbVar2;
        lVar5 = lVar5 + 1;
      } while ((uVar4 & 0xffffffff) != 0);
    }
    param_4 = param_4 - (QWORD)uVar6;
    param_3 = (QWORD)uVar6 + param_3;
  }
  FUN_00000204((QWORD)uVar1);
  return;
}

VOID HvSetupShaSaltedHash(PBYTE Buffer1, DWORD Size1, PBYTE Buffer2, DWORD Size2) {
	DWORD i = 0;
	for (DWORD s = 0; s < Size2; s += 0x14)
	{
		DWORD subsize = (s + 0x14 > Size2) ? Size2 - s : 0x14;
		BYTE tmp[0x14];
		BYTE tmpint[] = { 0, 0, 0, i };
		XeShaContext sha;
		XeCryptShaInit(&sha);
		XeCryptShaUpdate(&sha, Buffer1, Size1);
		XeCryptShaUpdate(&sha, tmpint, 4);
		XeCryptShaFinal(&sha, tmp, 0x14);
		for (DWORD l = 0; l < subsize; l++)
			Buffer2[s + l] ^= tmp[l];
		i++;
	}
}

undefined8 HvSetupMemEncryptionKey (undefined8 param_1,QWORD param_2,QWORD param_3,QWORD param_4,QWORD param_5, undefined8 param_6){
  QWORD uVar1;
  QWORD in_r2;
  undefined8 uVar2;
  QWORD lVar3;
  qword back_chain;
  
  uVar2 = __Save_R12_24_thru_31();
  if (((param_4 & 0xffffffff) < 0x2a) || ((param_4 - 0x2a & 0xffffffff) < (param_2 & 0xffffffff))) {
    uVar2 = 0;
  }
  else {
    if (param_5 == 0) {
      param_5 = ZEXT48(&0x15fb0) + in_r2;
    }
	
	
    *(undefined *)param_3 = 0;
	
    memcpy(param_3 + 1,param_6,0x14);
    lVar3 = param_3 + 0x15;
    memcpy(lVar3,param_5,0x14);
    uVar1 = (param_4 - param_2) - 0x2a & 0xffffffff;
    memset(param_3 + 0x29,0,uVar1);
	
	
    *(undefined *)((int)(param_4 - param_2) + -0x16 + (int)lVar3) = 1;
    memcpy(uVar1 + lVar3 + 0x15,uVar2,param_2 & 0xffffffff);
	
	
    HvSetupShaSaltedHash(param_6,0x14,lVar3, param_4 - 0x15);
    HvSetupShaSaltedHash(lVar3, param_4 - 0x15, param_3 + 1,0x14);
    uVar2 = 1;
  }
  return uVar2;
}

//23918
void HvSetupMemEncryptionKey(PBYTE Key, PBYTE clientSession, PBYTE buffer) {
	BYTE HvData[0x14]		= { 0xDA, 0x39, 0xA3, 0xEE, 0x5E, 0x6B, 0x4B, 0x0D, 0x32, 0x55, 0xBF, 0xEF, 0x95, 0x60, 0x18, 0x90, 0xAF, 0xD8, 0x07, 0x09 };
	BYTE signature[0x80]	= { 0x00 };

	signature[0] = 0;
	memcpy((signature + 1),		clientSession, 0x14);
	memcpy((signature + 0x15),	HvData, 0x14);
	memset((signature + 0x29),	0,		0x26);

	signature[0x4F] = 1;
	memcpy((signature + 0x50), Key, 0x30);
	HvSetupShaSaltedHash(clientSession, 0x14, (signature + 0x15), 0x6B);
	HvSetupShaSaltedHash((signature + 0x15), 0x6B, clientSession, 0x14);
	memcpy(buffer, signature, 0x80);
}

undefined8 FUN_00023a10(undefined8 param_1,QWORD param_2,QWORD *param_3,char **param_4,QWORD param_5) {
  QWORD in_r2;
  QWORD lVar1;
  int iVar2;
  QWORD uVar3;
  QWORD uVar4;
  QWORD lVar5;
  qword back_chain;
  
  lVar1 = __Save_R12_24_thru_31();
  if ((0x29 < (param_2 & 0xffffffff)) && (*(char *)lVar1 == '\0')) {
    if (param_5 == 0) {
      param_5 = ZEXT48(&0x15fb0) + in_r2;
    }
    lVar5 = lVar1 + 0x15;
    HvSetupShaSaltedHash(lVar5,param_2 - 0x15,lVar1 + 1,0x14);
    HvSetupShaSaltedHash(lVar1 + 1,0x14,lVar5,param_2 - 0x15);
    iVar2 = XeCryptMemDiff(lVar5,param_5,0x14);
    if (iVar2 == 0) {
      uVar4 = lVar1 + 0x29;
      uVar3 = (param_2 & 0xffffffff) + lVar1;
      while ((uVar4 < uVar3 && (*(char *)uVar4 == '\0'))) {
        uVar4 = uVar4 + 1;
      }
      if ((uVar4 != uVar3) && (*(char *)uVar4 == '\x01')) {
        *param_3 = uVar4 + 1;
        *param_4 = (char *)lVar1 + ((int)param_2 - (int)(uVar4 + 1));
        return 1;
      }
    }
  }
  return 0;
}



void FUN_00023b10(undefined *param_1,uint param_2) {
  undefined uVar1;
  int iVar2;
  undefined *puVar3;
  uint uVar4;
  
  uVar4 = 0;
  puVar3 = param_1;
  if (param_2 >> 1 != 0) {
    do {
      iVar2 = param_2 - uVar4;
      uVar1 = *puVar3;
      uVar4 = uVar4 + 1;
      iVar2 = iVar2 + -1;
      *puVar3 = param_1[iVar2];
      param_1[iVar2] = uVar1;
      puVar3 = puVar3 + 1;
    } while (uVar4 < param_2 >> 1);
    return;
  }
  return;
}

undefined8 FUN_00023b58(undefined8 param_1,QWORD param_2,undefined8 param_3,QWORD param_4, undefined8 param_5){
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  QWORD uVar5;
  int in_r2;
  QWORD lVar6;
  undefined8 uVar7;
  byte bVar8;
  int iVar9;
  uint *puVar10;
  QWORD lVar11;
  int iVar13;
  QWORD uVar12;
  QWORD uVar14;
  qword back_chain;
  word local_1e0;
  word local_80;
  word local_70;
  word local_60;
  byte local_51;
  word local_50;
  byte local_41;
  dword local_40;
  
  uVar5 = ZEXT48(register0x0000000c);
  lVar6 = __Save_R12_27_thru_31();
  uVar2 = *(uint *)(in_r2 + 0x10000);
  if ((param_4 & 0xffffffff) == 0x10) {
    XeCryptAesKey(uVar5 - 0x1e0,param_3);
    memset(uVar5 - 0x60,0,0x10);
    XeCryptAesEcb(uVar5 - 0x1e0,uVar5 - 0x60,uVar5 - 0x50,1);
    bVar8 = 0;
    iVar9 = 0x10;
    lVar11 = uVar5 - 0x40;
    do {
      lVar11 = lVar11 + -1;
      iVar9 = iVar9 + -1;
      bVar1 = *(byte *)lVar11;
      if (bVar8 == 0) {
        bVar8 = bVar1 << 1;
      }
      else {
        bVar8 = (byte)(((QWORD)bVar1 & 0x7fffffff8000007f) << 1) | 1;
      }
      *(byte *)lVar11 = bVar8;
      bVar8 = bVar1 & 0x80;
    } while (iVar9 != 0);
    memcpy(uVar5 - 0x60,uVar5 - 0x50,0x10);
    bVar8 = 0;
    iVar9 = 0x10;
    lVar11 = uVar5 - 0x50;
    do {
      lVar11 = lVar11 + -1;
      iVar9 = iVar9 + -1;
      bVar1 = *(byte *)lVar11;
      if (bVar8 == 0) {
        bVar8 = bVar1 << 1;
      }
      else {
        bVar8 = (byte)(((QWORD)bVar1 & 0x7fffffff8000007f) << 1) | 1;
      }
      *(byte *)lVar11 = bVar8;
      bVar8 = bVar1 & 0x80;
    } while (iVar9 != 0);
    memset(uVar5 - 0x80,0,0x10);
    uVar14 = param_2 & 0xffffffff;
    if (0x10 < uVar14) {
      lVar11 = lVar6 - (uVar5 - 0x80);
      uVar14 = (QWORD)((int)param_2 - 0x11U >> 4) + 1;
      lVar6 = uVar14 * 0x10 + lVar6;
      do {
        iVar13 = 0;
        iVar9 = 4;
        do {
          iVar9 = iVar9 + -1;
          *(uint *)((int)&local_70 + iVar13) =
               *(uint *)((int)lVar11 + (int)(uint *)((int)&local_80 + iVar13)) ^
               *(uint *)((int)&local_80 + iVar13);
          iVar13 = iVar13 + 4;
        } while (iVar9 != 0);
        XeCryptAesEcb(uVar5 - 0x1e0,uVar5 - 0x70,uVar5 - 0x80,1);
        uVar14 = uVar14 - 1;
        param_2 = param_2 - 0x10;
        lVar11 = lVar11 + 0x10;
      } while ((uVar14 & 0xffffffff) != 0);
      uVar14 = param_2 & 0xffffffff;
    }
    if (uVar14 == 0x10) {
      iVar13 = 0;
      iVar9 = 4;
      do {
        iVar9 = iVar9 + -1;
        *(uint *)((int)&local_70 + iVar13) =
             *(uint *)((int)&local_50 + iVar13) ^
             *(uint *)((int)(uint *)((int)&local_80 + iVar13) + ((int)lVar6 - (int)&local_80)) ^
             *(uint *)((int)&local_80 + iVar13);
        iVar13 = iVar13 + 4;
      } while (iVar9 != 0);
    }
    else {
      if ((param_2 & 0xffffffff) != 0) {
        memcpy(uVar5 - 0x70,lVar6,param_2 & 0xffffffff);
      }
      uVar14 = param_2 + 1;
      *(undefined *)((int)&local_70 + (int)param_2) = 0x80;
      if ((uVar14 & 0xffffffff) < 0x10) {
        uVar12 = 0x10 - uVar14;
        lVar6 = (uVar14 & 0xffffffff) + (uVar5 - 0x70);
        uVar14 = uVar12 & 0xffffffff;
        while (uVar14 != 0) {
          *(undefined *)lVar6 = 0;
          lVar6 = lVar6 + 1;
          uVar12 = uVar12 - 1;
          uVar14 = uVar12;
        }
      }
      iVar13 = 0;
      iVar9 = 4;
      do {
        iVar9 = iVar9 + -1;
        puVar10 = (uint *)((int)&local_70 + iVar13);
        puVar3 = (uint *)((int)&local_80 + iVar13);
        puVar4 = (uint *)((int)&local_60 + iVar13);
        iVar13 = iVar13 + 4;
        *puVar10 = *puVar3 ^ *puVar4 ^ *puVar10;
      } while (iVar9 != 0);
    }
    XeCryptAesEcb(uVar5 - 0x1e0,uVar5 - 0x70,uVar5 - 0x80,1);
    memcpy(param_5,uVar5 - 0x80,0x10);
    FUN_00000204((QWORD)uVar2);
    uVar7 = 1;
  }
  else {
    FUN_00000204((QWORD)uVar2);
    uVar7 = 0;
  }
  return uVar7;
}



undefined8 XeCryptAesKeyTable(void) {
  uint *puVar1;
  uint *puVar2;
  QWORD uVar3;
  int in_r9;
  uint *puVar4;
  int in_r10;
  undefined *puVar5;
  int iVar6;
  QWORD in_r11;
  int iVar7;
  undefined8 unaff_r27;
  uint param_1;
  
  puVar5 = (undefined *)(in_r10 + in_r9);
  uVar3 = in_r11 & 0xffffffff;
  while (uVar3 != 0) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    in_r11 = in_r11 - 1;
    uVar3 = in_r11;
  }
  iVar7 = 0;
  iVar6 = 4;
  do {
    iVar6 = iVar6 + -1;
    puVar4 = (uint *)(&stack0x000001c0 + iVar7);
    puVar1 = (uint *)(&stack0x000001b0 + iVar7);
    puVar2 = (uint *)(&stack0x000001d0 + iVar7);
    iVar7 = iVar7 + 4;
    *puVar4 = *puVar1 ^ *puVar2 ^ *puVar4;
  } while (iVar6 != 0);
  XeCryptAesEcb(&stack0x00000050,&stack0x000001c0,&stack0x000001b0,1);
  memcpy(unaff_r27,&stack0x000001b0,0x10);
  FUN_00000204((QWORD)param_1);
  return 1;
}

// WARNING: Variable defined which should be unmapped: local_30
// WARNING: Variable defined which should be unmapped: local_28
// WARNING: Variable defined which should be unmapped: local_20
// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Variable defined which should be unmapped: local_8

void FUN_00023e70(uint *param_1,uint *param_2,int param_3){
  byte *pbVar1;
  QWORD uVar2;
  uint uVar3;
  QWORD uVar4;
  uint uVar5;
  QWORD uVar6;
  uint uVar7;
  QWORD uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  QWORD lVar14;
  dword back_chain;
  qword local_30;
  qword local_28;
  qword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar3 = *param_2;
  uVar2 = (QWORD)uVar3;
  uVar5 = param_2[1];
  uVar4 = (QWORD)uVar5;
  uVar7 = param_2[2];
  uVar6 = (QWORD)uVar7;
  uVar9 = param_2[3];
  uVar8 = (QWORD)uVar9;
  iVar10 = param_3 + 0x100;
  iVar11 = param_3 + 0x500;
  iVar12 = param_3 + 0x900;
  iVar13 = param_3 + 0xd00;
  pbVar1 = (byte *)(param_3 + 0x1110);
  *param_1 = uVar3;
  param_1[1] = uVar5;
  param_1[2] = uVar7;
  param_1[3] = uVar9;
  param_1[0x2c] = uVar3;
  param_1[0x2d] = uVar5;
  param_1[0x2e] = uVar7;
  param_1[0x2f] = uVar9;
  lVar14 = 10;
  while( true ) {
    uVar3 = (uint)uVar8;
    pbVar1 = pbVar1 + -1;
    uVar2 = (QWORD)
            CONCAT13(*(undefined *)(param_3 + (uVar3 >> 0x10 & 0xff)),
                     CONCAT12(*(undefined *)(param_3 + (uVar3 >> 8 & 0xff)),
                              CONCAT11(*(undefined *)(param_3 + (uVar3 & 0xff)),
                                       *(undefined *)(param_3 + (uVar3 >> 0x18))))) ^
            (QWORD)*pbVar1 << 0x18 ^ uVar2;
    uVar4 = uVar2 ^ uVar4;
    uVar6 = uVar4 ^ uVar6;
    uVar8 = uVar6 ^ uVar8;
    uVar3 = (uint)uVar2;
    param_1[4] = uVar3;
    uVar5 = (uint)uVar4;
    param_1[5] = uVar5;
    uVar7 = (uint)uVar6;
    param_1[6] = uVar7;
    uVar9 = (uint)uVar8;
    param_1[7] = uVar9;
    lVar14 = lVar14 + -1;
    if (lVar14 == 0) break;
    param_1[0x30] =
         *(uint *)(iVar10 + (uVar3 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar11 + (uVar3 >> 0xe & 0x3fc)) ^
         *(uint *)(iVar12 + (uVar3 >> 6 & 0x3fc)) ^ *(uint *)(iVar13 + (uVar3 & 0xff) * 4);
    param_1[0x31] =
         *(uint *)(iVar10 + (uVar5 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar11 + (uVar5 >> 0xe & 0x3fc)) ^
         *(uint *)(iVar12 + (uVar5 >> 6 & 0x3fc)) ^ *(uint *)(iVar13 + (uVar5 & 0xff) * 4);
    param_1[0x32] =
         *(uint *)(iVar10 + (uVar7 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar11 + (uVar7 >> 0xe & 0x3fc)) ^
         *(uint *)(iVar12 + (uVar7 >> 6 & 0x3fc)) ^ *(uint *)(iVar13 + (uVar7 & 0xff) * 4);
    param_1[0x33] =
         *(uint *)(iVar10 + (uVar9 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar11 + (uVar9 >> 0xe & 0x3fc)) ^
         *(uint *)(iVar12 + (uVar9 >> 6 & 0x3fc)) ^ *(uint *)(iVar13 + (uVar9 & 0xff) * 4);
    param_1 = param_1 + 4;
  }
  param_1[0x30] = uVar3;
  param_1[0x31] = uVar5;
  param_1[0x32] = uVar7;
  param_1[0x33] = uVar9;
  return;
}

void XeCryptAesEncrypt(uint *param_1,byte *param_2,int param_3,QWORD param_4,QWORD param_5, QWORD param_6,QWORD param_7) {
  uint uVar1;
  uint uVar2;
  int in_r11;
  int in_r12;
  int unaff_r14;
  int unaff_r15;
  uint unaff_r16;
  uint unaff_r18;
  uint unaff_r19;
  QWORD in_CTR;
  
  while( true ) {
    param_1[0x2d] = unaff_r16 ^ unaff_r18 ^ unaff_r19;
    uVar1 = (uint)param_6;
    param_1[0x2e] =
         *(uint *)(in_r11 + (uVar1 >> 0x16 & 0x3fc)) ^ *(uint *)(in_r12 + (uVar1 >> 0xe & 0x3fc)) ^
         *(uint *)(unaff_r14 + (uVar1 >> 6 & 0x3fc)) ^ *(uint *)(unaff_r15 + (uVar1 & 0xff) * 4);
    uVar1 = (uint)param_7;
    param_1[0x2f] =
         *(uint *)(in_r11 + (uVar1 >> 0x16 & 0x3fc)) ^ *(uint *)(in_r12 + (uVar1 >> 0xe & 0x3fc)) ^
         *(uint *)(unaff_r14 + (uVar1 >> 6 & 0x3fc)) ^ *(uint *)(unaff_r15 + (uVar1 & 0xff) * 4);
    param_2 = param_2 + -1;
    param_4 = (QWORD)
              CONCAT13(*(undefined *)(param_3 + (uVar1 >> 0x10 & 0xff)),
                       CONCAT12(*(undefined *)(param_3 + (uVar1 >> 8 & 0xff)),
                                CONCAT11(*(undefined *)(param_3 + (uVar1 & 0xff)),
                                         *(undefined *)(param_3 + (uVar1 >> 0x18))))) ^
              (QWORD)*param_2 << 0x18 ^ param_4;
    param_5 = param_4 ^ param_5;
    param_6 = param_5 ^ param_6;
    param_7 = param_6 ^ param_7;
    uVar1 = (uint)param_4;
    param_1[4] = uVar1;
    uVar2 = (uint)param_5;
    param_1[5] = uVar2;
    param_1[6] = (uint)param_6;
    param_1[7] = (uint)param_7;
    in_CTR = in_CTR + -1;
    if (in_CTR == 0) break;
    param_1[0x30] =
         *(uint *)(in_r11 + (uVar1 >> 0x16 & 0x3fc)) ^ *(uint *)(in_r12 + (uVar1 >> 0xe & 0x3fc)) ^
         *(uint *)(unaff_r14 + (uVar1 >> 6 & 0x3fc)) ^ *(uint *)(unaff_r15 + (uVar1 & 0xff) * 4);
    unaff_r18 = *(uint *)(unaff_r14 + (uVar2 >> 6 & 0x3fc));
    unaff_r19 = *(uint *)(unaff_r15 + (uVar2 & 0xff) * 4);
    unaff_r16 = *(uint *)(in_r11 + (uVar2 >> 0x16 & 0x3fc)) ^
                *(uint *)(in_r12 + (uVar2 >> 0xe & 0x3fc));
    param_1 = param_1 + 4;
  }
  param_1[0x30] = uVar1;
  param_1[0x31] = uVar2;
  param_1[0x32] = (uint)param_6;
  param_1[0x33] = (uint)param_7;
  return;
}

void FUN_0002402c(uint *param_1,uint *param_2,uint *param_3,int param_4) {
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  QWORD lVar16;
  dword back_chain;
  qword local_40;
  qword local_38;
  qword local_30;
  qword local_28;
  qword local_20;
  qword local_18;
  qword local_10;
  
  iVar9 = param_4 + 0x400;
  iVar10 = param_4 + 0x800;
  iVar11 = param_4 + 0xc00;
  uVar12 = *param_1 ^ *param_2;
  uVar13 = param_1[1] ^ param_2[1];
  uVar14 = param_1[2] ^ param_2[2];
  uVar15 = param_1[3] ^ param_2[3];
  lVar16 = 9;
  puVar7 = param_1 + 4;
  do {
    puVar8 = puVar7;
    uVar4 = uVar12 & 0xff;
    uVar1 = uVar12 >> 6;
    uVar5 = uVar13 & 0xff;
    uVar2 = uVar12 >> 0xe;
    uVar3 = uVar13 >> 6;
    uVar6 = uVar14 & 0xff;
    uVar12 = *(uint *)(param_4 + (uVar12 >> 0x16 & 0x3fc)) ^
             *(uint *)(iVar9 + (uVar13 >> 0xe & 0x3fc)) ^
             *(uint *)(iVar10 + (uVar14 >> 6 & 0x3fc)) ^ *(uint *)(iVar11 + (uVar15 & 0xff) * 4) ^
             *puVar8;
    uVar13 = *(uint *)(param_4 + (uVar13 >> 0x16 & 0x3fc)) ^
             *(uint *)(iVar9 + (uVar14 >> 0xe & 0x3fc)) ^
             *(uint *)(iVar10 + (uVar15 >> 6 & 0x3fc)) ^ *(uint *)(iVar11 + uVar4 * 4) ^ puVar8[1];
    uVar14 = *(uint *)(param_4 + (uVar14 >> 0x16 & 0x3fc)) ^
             *(uint *)(iVar9 + (uVar15 >> 0xe & 0x3fc)) ^
             *(uint *)(iVar10 + (uVar1 & 0x3fc)) ^ *(uint *)(iVar11 + uVar5 * 4) ^ puVar8[2];
    uVar15 = *(uint *)(param_4 + (uVar15 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar9 + (uVar2 & 0x3fc)) ^
             *(uint *)(iVar10 + (uVar3 & 0x3fc)) ^ *(uint *)(iVar11 + uVar6 * 4) ^ puVar8[3];
    lVar16 = lVar16 + -1;
    puVar7 = puVar8 + 4;
  } while (lVar16 != 0);
  param_4 = param_4 + 1;
  param_3[3] = puVar8[7] ^
               CONCAT13(*(undefined *)(param_4 + (uVar15 >> 0x16 & 0x3fc)),
                        CONCAT12(*(undefined *)(param_4 + (uVar12 >> 0xe & 0x3fc)),
                                 CONCAT11(*(undefined *)(param_4 + (uVar13 >> 6 & 0x3fc)),
                                          *(undefined *)(param_4 + (uVar14 & 0xff) * 4))));
  param_3[2] = puVar8[6] ^
               CONCAT13(*(undefined *)(param_4 + (uVar14 >> 0x16 & 0x3fc)),
                        CONCAT12(*(undefined *)(param_4 + (uVar15 >> 0xe & 0x3fc)),
                                 CONCAT11(*(undefined *)(param_4 + (uVar12 >> 6 & 0x3fc)),
                                          *(undefined *)(param_4 + (uVar13 & 0xff) * 4))));
  param_3[1] = puVar8[5] ^
               CONCAT13(*(undefined *)(param_4 + (uVar13 >> 0x16 & 0x3fc)),
                        CONCAT12(*(undefined *)(param_4 + (uVar14 >> 0xe & 0x3fc)),
                                 CONCAT11(*(undefined *)(param_4 + (uVar15 >> 6 & 0x3fc)),
                                          *(undefined *)(param_4 + (uVar12 & 0xff) * 4))));
  *param_3 = puVar8[4] ^
             CONCAT13(*(undefined *)(param_4 + (uVar12 >> 0x16 & 0x3fc)),
                      CONCAT12(*(undefined *)(param_4 + (uVar13 >> 0xe & 0x3fc)),
                               CONCAT11(*(undefined *)(param_4 + (uVar14 >> 6 & 0x3fc)),
                                        *(undefined *)(param_4 + (uVar15 & 0xff) * 4))));
  return;
}



void XeCryptAesDecrypt(uint *param_1,undefined8 param_2,uint *param_3) {
  uint in_r9;
  int in_r10;
  uint in_r12;
  uint unaff_r14;
  uint unaff_r15;
  uint unaff_r16;
  uint unaff_r17;
  int unaff_r20;
  
  param_3[2] = in_r9 ^ (unaff_r20 << 0x18 | unaff_r17 & 0xffffff);
  param_3[1] = param_1[1] ^
               CONCAT13(*(undefined *)(in_r10 + (unaff_r14 >> 0x16 & 0x3fc)),
                        CONCAT12(*(undefined *)(in_r10 + (unaff_r15 >> 0xe & 0x3fc)),
                                 CONCAT11(*(undefined *)(in_r10 + (unaff_r16 >> 6 & 0x3fc)),
                                          *(undefined *)(in_r10 + (in_r12 & 0xff) * 4))));
  *param_3 = *param_1 ^
             CONCAT13(*(undefined *)(in_r10 + (in_r12 >> 0x16 & 0x3fc)),
                      CONCAT12(*(undefined *)(in_r10 + (unaff_r14 >> 0xe & 0x3fc)),
                               CONCAT11(*(undefined *)(in_r10 + (unaff_r15 >> 6 & 0x3fc)),
                                        *(undefined *)(in_r10 + (unaff_r16 & 0xff) * 4))));
  return;
}

void XeCryptBnQwBeSigDifference(int param_1,uint *param_2,uint *param_3,int param_4) {
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  QWORD lVar16;
  dword back_chain;
  qword local_40;
  qword local_38;
  qword local_30;
  qword local_28;
  qword local_20;
  qword local_18;
  qword local_10;
  
  iVar9 = param_4 + 0x400;
  iVar10 = param_4 + 0x800;
  iVar11 = param_4 + 0xc00;
  uVar12 = *(uint *)(param_1 + 0x150) ^ *param_2;
  uVar13 = *(uint *)(param_1 + 0x154) ^ param_2[1];
  uVar14 = *(uint *)(param_1 + 0x158) ^ param_2[2];
  uVar15 = *(uint *)(param_1 + 0x15c) ^ param_2[3];
  lVar16 = 9;
  puVar7 = (uint *)(param_1 + 0x140);
  do {
    puVar8 = puVar7;
    uVar1 = uVar12 >> 0xe;
    uVar2 = uVar13 >> 0xe;
    uVar3 = uVar12 >> 6;
    uVar4 = uVar14 >> 0xe;
    uVar5 = uVar13 >> 6;
    uVar6 = uVar12 & 0xff;
    uVar12 = *(uint *)(param_4 + (uVar12 >> 0x16 & 0x3fc)) ^
             *(uint *)(iVar9 + (uVar15 >> 0xe & 0x3fc)) ^
             *(uint *)(iVar10 + (uVar14 >> 6 & 0x3fc)) ^ *(uint *)(iVar11 + (uVar13 & 0xff) * 4) ^
             *puVar8;
    uVar13 = *(uint *)(param_4 + (uVar13 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar9 + (uVar1 & 0x3fc)) ^
             *(uint *)(iVar10 + (uVar15 >> 6 & 0x3fc)) ^ *(uint *)(iVar11 + (uVar14 & 0xff) * 4) ^
             puVar8[1];
    uVar14 = *(uint *)(param_4 + (uVar14 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar9 + (uVar2 & 0x3fc)) ^
             *(uint *)(iVar10 + (uVar3 & 0x3fc)) ^ *(uint *)(iVar11 + (uVar15 & 0xff) * 4) ^
             puVar8[2];
    uVar15 = *(uint *)(param_4 + (uVar15 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar9 + (uVar4 & 0x3fc)) ^
             *(uint *)(iVar10 + (uVar5 & 0x3fc)) ^ *(uint *)(iVar11 + uVar6 * 4) ^ puVar8[3];
    lVar16 = lVar16 + -1;
    puVar7 = puVar8 + -4;
  } while (lVar16 != 0);
  param_4 = param_4 + 0x1000;
  param_3[3] = puVar8[-1] ^
               CONCAT13(*(undefined *)(param_4 + (uVar15 >> 0x18)),
                        CONCAT12(*(undefined *)(param_4 + (uVar14 >> 0x10 & 0xff)),
                                 CONCAT11(*(undefined *)(param_4 + (uVar13 >> 8 & 0xff)),
                                          *(undefined *)(param_4 + (uVar12 & 0xff)))));
  param_3[2] = puVar8[-2] ^
               CONCAT13(*(undefined *)(param_4 + (uVar14 >> 0x18)),
                        CONCAT12(*(undefined *)(param_4 + (uVar13 >> 0x10 & 0xff)),
                                 CONCAT11(*(undefined *)(param_4 + (uVar12 >> 8 & 0xff)),
                                          *(undefined *)(param_4 + (uVar15 & 0xff)))));
  param_3[1] = puVar8[-3] ^
               CONCAT13(*(undefined *)(param_4 + (uVar13 >> 0x18)),
                        CONCAT12(*(undefined *)(param_4 + (uVar12 >> 0x10 & 0xff)),
                                 CONCAT11(*(undefined *)(param_4 + (uVar15 >> 8 & 0xff)),
                                          *(undefined *)(param_4 + (uVar14 & 0xff)))));
  *param_3 = puVar8[-4] ^
             CONCAT13(*(undefined *)(param_4 + (uVar12 >> 0x18)),
                      CONCAT12(*(undefined *)(param_4 + (uVar15 >> 0x10 & 0xff)),
                               CONCAT11(*(undefined *)(param_4 + (uVar14 >> 8 & 0xff)),
                                        *(undefined *)(param_4 + (uVar13 & 0xff)))));
  return;
}



void XeCryptBnQwNeDigLen(undefined8 param_1,undefined8 param_2,undefined8 param_3,QWORD param_4, undefined8 param_5,undefined8 param_6) {
  uint uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  QWORD lVar4;
  qword back_chain;
  
  uVar2 = __Save_R12_24_thru_31();
  lVar4 = param_4 + 0x10;
  uVar1 = *(uint *)((int)param_4 + 4);
  uVar3 = XeCryptBnQwNeModInv(*(undefined8 *)lVar4);
  XeCryptBnQw_Copy(uVar2,param_5,0x20);
  XeCryptBnQw_Copy(param_5,param_6,0x20);
  while (uVar1 = uVar1 >> 1, uVar1 != 0) {
    XeCryptBnQwNeModMul(param_6,param_6,param_6,uVar3,lVar4,0x20);
  }
  XeCryptBnQwNeModMul(param_6,param_5,param_5,uVar3,lVar4,0x20);
  XeCryptBnQw_Copy(param_5,param_5,0x20);
  XeCryptBnQwBeSigFormat(param_6,param_2,param_3);
  return;
}

int XeCryptBnQwNeMul(int param_1,int param_2) {
  QWORD *plVar1;
  
  plVar1 = (QWORD *)(param_2 * 8 + param_1);
  while ((param_2 != 0 && (plVar1 = plVar1 + -1, *plVar1 == 0))) {
    param_2 = param_2 + -1;
  }
  return param_2;
}


QWORD FUN_000245b0(QWORD param_1,QWORD param_2) {
  QWORD lVar1;
  
  param_1 = (param_2 & 0xffffffff) * 8 + param_1;
  if ((param_2 & 0xffffffff) != 0) {
    do {
      param_1 = param_1 + -8;
      if (*(QWORD *)param_1 != 0) break;
      param_2 = param_2 - 1;
    } while ((param_2 & 0xffffffff) != 0);
    if ((param_2 & 0xffffffff) != 0) {
      lVar1 = countLeadingZeros(*(QWORD *)param_1);
      param_2 = (QWORD)(uint)((int)param_2 << 6) - lVar1;
    }
  }
  return param_2;
}


void FUN_00024600(undefined8 param_1,int param_2,QWORD param_3,QWORD param_4) {
  int iVar1;
  int iVar3;
  undefined8 uVar2;
  QWORD lVar4;
  QWORD uVar5;
  QWORD uVar6;
  int iVar7;
  qword back_chain;
  
  iVar3 = __Save_R12_25_thru_31();
  XeCryptBnQw_Zero(iVar3,(QWORD)(uint)((int)param_4 << 1));
  lVar4 = (param_4 & 0xffffffff) * 8 + param_3;
  uVar5 = param_4;
  if ((param_4 & 0xffffffff) != 0) {
    do {
      lVar4 = lVar4 + -8;
      if (*(QWORD *)lVar4 != 0) break;
      uVar5 = uVar5 - 1;
    } while ((uVar5 & 0xffffffff) != 0);
    if (((uVar5 & 0xffffffff) != 0) && (uVar6 = 0, (param_4 & 0xffffffff) != 0)) {
      iVar7 = iVar3;
      do {
        uVar2 = FUN_00024b90(iVar7,*(undefined8 *)((param_2 - iVar3) + iVar7),param_3,uVar5);
        iVar1 = (int)uVar6;
        uVar6 = uVar6 + 1;
        iVar7 = iVar7 + 8;
        *(undefined8 *)(((int)uVar5 + iVar1) * 8 + iVar3) = uVar2;
      } while ((uVar6 & 0xffffffff) < (param_4 & 0xffffffff));
    }
  }
  return;
}

void FUN_000246b0(undefined8 param_1,QWORD param_2,QWORD param_3) {
  undefined8 uVar1;
  undefined8 uVar2;
  QWORD lVar3;
  QWORD uVar4;
  int iVar5;
  QWORD uVar6;
  qword back_chain;
  
  uVar1 = __Save_R12_25_thru_31();
  XeCryptBnQw_Zero(uVar1._4_4_,(QWORD)(uint)((int)param_3 << 1));
  lVar3 = (param_3 & 0xffffffff) * 8 + param_2;
  if ((param_3 & 0xffffffff) != 0) {
    do {
      lVar3 = lVar3 + -8;
      if (*(QWORD *)lVar3 != 0) break;
      param_3 = param_3 - 1;
    } while ((param_3 & 0xffffffff) != 0);
    if ((param_3 & 0xffffffff) != 0) {
      uVar6 = param_3 - 1;
      iVar5 = uVar1._4_4_ + 8;
      if ((uVar6 & 0xffffffff) != 0) {
        uVar4 = uVar6 * 8 & 0x7fffffff8;
        lVar3 = param_2;
        do {
          uVar2 = FUN_00024b90(iVar5,*(undefined8 *)lVar3,lVar3 + 8,uVar6);
          uVar6 = uVar6 - 1;
          *(undefined8 *)((int)uVar4 + iVar5) = uVar2;
          uVar4 = uVar4 - 8;
          iVar5 = iVar5 + 0x10;
          lVar3 = lVar3 + 8;
        } while ((uVar6 & 0xffffffff) != 0);
      }
      XeCryptBnQwNeAcc(uVar1._4_4_,uVar1,uVar1,(QWORD)(uint)((int)param_3 << 1));
      XeCryptBnQwNeCompare(uVar1._4_4_,param_2,param_3);
    }
  }
  return;
}

QWORD FUN_00024788(QWORD param_1,QWORD param_2,QWORD param_3,QWORD param_4) {
  bool bVar1;
  QWORD uVar2;
  QWORD uVar3;
  QWORD uVar4;
  
  if ((param_4 == 0) || ((param_3 & 0x8000000000000000) != 0)) {
    if (param_1 < param_3) {
      uVar2 = 0;
      uVar3 = 0x8000000000000000;
      do {
        uVar4 = param_2 >> 0x3f;
        param_2 = param_2 << 1;
        uVar4 = uVar4 | param_1 << 1;
        if (((QWORD)param_1 < 0) || (param_3 <= uVar4)) {
          uVar4 = uVar4 - param_3;
          uVar2 = uVar3 | uVar2;
        }
        uVar3 = uVar3 >> 1;
        param_1 = uVar4;
      } while (uVar3 != 0);
      return uVar2;
    }
  }
  else {
    if ((param_1 <= param_3) && ((param_1 != param_3 || (param_2 < param_4)))) {
      uVar2 = 0;
      uVar3 = 0x8000000000000000;
      do {
        uVar4 = param_2 >> 0x3f;
        param_2 = param_2 * 2;
        param_1 = uVar4 | param_1 << 1;
        if ((param_3 < param_1) || ((param_1 == param_3 && (param_4 <= param_2)))) {
          bVar1 = param_2 < param_4;
          param_2 = param_2 - param_4;
          param_1 = (param_1 - bVar1) - param_3;
          uVar2 = uVar3 | uVar2;
        }
        uVar3 = uVar3 >> 1;
      } while (uVar3 != 0);
      return uVar2;
    }
  }
  return 0xffffffffffffffff;
}



QWORD XeCryptBnQwNeMod(QWORD param_1,QWORD param_2,QWORD param_3,QWORD param_4, undefined8 param_5,undefined8 param_6,QWORD param_7) {
  bool bVar1;
  QWORD uVar2;
  QWORD in_r11;
  
  while( true ) {
    if ((param_3 < in_r11) || ((in_r11 == param_3 && (param_4 <= param_2)))) {
      bVar1 = param_2 < param_4;
      param_2 = param_2 - param_4;
      in_r11 = (in_r11 - bVar1) - param_3;
      param_1 = param_7 | param_1;
    }
    param_7 = param_7 >> 1;
    if (param_7 == 0) break;
    uVar2 = param_2 >> 0x3f;
    param_2 = param_2 << 1;
    in_r11 = uVar2 | in_r11 << 1;
  }
  return param_1;
}

undefined8 XeCryptBnQwNeAdd(undefined8 param_1,QWORD param_2,QWORD param_3,QWORD param_4, QWORD param_5) {
  QWORD lVar1;
  QWORD lVar2;
  int iVar3;
  undefined8 uVar4;
  QWORD lVar5;
  QWORD lVar6;
  QWORD lVar7;
  word *pwVar8;
  QWORD uVar9;
  qword back_chain;
  word local_8a0;
  word local_690;
  word local_480;
  
  lVar1 = __Save_R12_20_thru_31();
  if (((param_4 & 0xffffffff) < 0x82) && ((param_5 & 0xffffffff) < 0x42)) {
    lVar5 = (param_5 & 0xffffffff) * 8 + param_2;
    uVar9 = param_5;
    while (((uVar9 & 0xffffffff) != 0 && (lVar5 = lVar5 + -8, *(QWORD *)lVar5 == 0))) {
      uVar9 = uVar9 - 1;
    }
    if ((uVar9 & 0xffffffff) != 0) {
      lVar5 = (param_4 & 0xffffffff) * 8 + lVar1;
      while (((param_4 & 0xffffffff) != 0 && (lVar5 = lVar5 + -8, *(QWORD *)lVar5 == 0))) {
        param_4 = param_4 - 1;
      }
      if ((param_4 & 0xffffffff) < (uVar9 & 0xffffffff)) {
        XeCryptBnQw_Copy(lVar1,param_3,param_4);
        lVar5 = (param_4 & 0xffffffff) << 3;
        uVar9 = param_4;
      }
      else {
        XeCryptBnQw_Copy(param_2,&local_690,uVar9);
        lVar5 = (uVar9 & 0xffffffff) << 3;
        *(undefined8 *)((int)&local_690 + (int)lVar5) = 0;
        XeCryptBnQw_Copy(lVar1,&local_480,param_4);
        lVar1 = param_4 - uVar9;
        *(undefined8 *)((int)&local_480 + (int)(param_4 << 3)) = 0;
        if (-1 < (int)lVar1) {
          lVar7 = uVar9 + 1;
          lVar6 = uVar9 + lVar1;
          do {
            if ((uVar9 & 0xffffffff) < 2) {
              uVar4 = 0;
            }
            else {
              uVar4 = *(undefined8 *)(((int)uVar9 + -2) * 8 + (int)param_2);
            }
            lVar2 = FUN_00024788(*(undefined8 *)((int)&local_480 + (int)(lVar6 << 3)),
                                 *(undefined8 *)(&local_480 + ((int)lVar6 + -1) * 4),
                                 *(undefined8 *)(((int)uVar9 + -1) * 8 + (int)param_2),uVar4);
            if (lVar2 == 0) {
              lVar2 = 1;
            }
            XeCryptBnQw_Zero(&local_8a0,uVar9);
            uVar4 = FUN_00024b90(&local_8a0,lVar2,param_2,uVar9);
            pwVar8 = &local_480 + (int)lVar1 * 4;
            *(undefined8 *)((int)&local_8a0 + (int)lVar5) = uVar4;
            while (iVar3 = FUN_00024d08(&local_8a0,pwVar8,lVar7), iVar3 == 1) {
              FUN_00024b38(&local_8a0,&local_8a0,&local_690,lVar7);
            }
            FUN_00024b38(pwVar8,&local_480 + (int)lVar1 * 4,&local_8a0,lVar7);
            iVar3 = FUN_00024d08(pwVar8,&local_690,lVar7);
            if (-1 < iVar3) {
              lVar1 = lVar1 + 1;
              lVar6 = lVar6 + 1;
            }
            lVar1 = lVar1 + -1;
            lVar6 = lVar6 + -1;
          } while (-1 < (int)lVar1);
        }
        XeCryptBnQw_Copy(&local_480,param_3,uVar9);
      }
      XeCryptBnQw_Zero(lVar5 + param_3,param_5 - uVar9);
      return 1;
    }
  }
  return 0;
}

QWORD XeCryptBnQwNeAcc(QWORD* param_1, int param_2, int param_3, QWORD param_4) {
  QWORD uVar1;
  QWORD uVar2;
  QWORD uVar3;
  QWORD uVar4;
  
  uVar1 = 0;
  param_2 = param_2 - (int)param_1;
  param_3 = param_3 - (int)param_1;
  if ((int)param_4 != 0) {
    do {
      uVar4 = *(QWORD *)((int)param_1 + param_3);
      uVar2 = *(QWORD *)((int)param_1 + param_2) + uVar1;
      uVar3 = uVar2 + uVar4;
      *param_1 = uVar3;
      param_1 = param_1 + 1;
      uVar1 = (QWORD)
              (byte)(uVar3 < uVar4 != uVar2 < uVar1 | (uVar2 < uVar1 && uVar3 < uVar4) << 1);
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return uVar1;
}

QWORD FUN_00024b38(QWORD *param_1,int param_2,int param_3,QWORD param_4) {
  QWORD uVar1;
  QWORD uVar2;
  QWORD uVar3;
  QWORD uVar4;
  
  uVar1 = 0;
  param_2 = param_2 - (int)param_1;
  param_3 = param_3 - (int)param_1;
  if ((int)param_4 != 0) {
    do {
      uVar2 = *(QWORD *)((int)param_1 + param_2);
      uVar4 = *(QWORD *)((int)param_1 + param_3);
      uVar3 = uVar2 - uVar1;
      *param_1 = uVar3 - uVar4;
      param_1 = param_1 + 1;
      uVar1 = (QWORD)
              (byte)(uVar3 < uVar4 != uVar2 < uVar1 | (uVar2 < uVar1 && uVar3 < uVar4) << 1);
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return uVar1;
}



QWORD FUN_00024b90(QWORD *param_1,QWORD param_2,int param_3,QWORD param_4)

{
  QWORD uVar1;
  QWORD uVar2;
  QWORD uVar3;
  QWORD uVar4;
  QWORD uVar5;
  
  uVar5 = 0;
  if (1 < param_2) {
    param_3 = param_3 - (int)param_1;
    if ((int)param_4 != 0) {
      do {
        uVar3 = *(QWORD *)((int)param_1 + param_3);
        uVar4 = param_2 * uVar3;
        uVar1 = *param_1 + uVar5;
        uVar2 = uVar1 + uVar4;
        *param_1 = uVar2;
        param_1 = param_1 + 1;
        uVar5 = SUB168(ZEXT816(param_2) * ZEXT816(uVar3) >> 0x40,0) +
                (QWORD)
                (byte)(uVar2 < uVar4 != uVar1 < uVar5 | (uVar1 < uVar5 && uVar2 < uVar4) << 1);
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
    return uVar5;
  }
  if (param_2 == 1) {
    uVar5 = 0;
    param_3 = param_3 - (int)param_1;
    if ((int)param_4 != 0) {
      do {
        uVar3 = *(QWORD *)((int)param_1 + param_3);
        uVar1 = *param_1 + uVar5;
        uVar2 = uVar1 + uVar3;
        *param_1 = uVar2;
        param_1 = param_1 + 1;
        uVar5 = (QWORD)
                (byte)(uVar2 < uVar3 != uVar1 < uVar5 | (uVar1 < uVar5 && uVar2 < uVar3) << 1);
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
    return uVar5;
  }
  return 0;
}



void XeCryptBnQwNeCompare(QWORD *param_1,QWORD *param_2,QWORD param_3)

{
  QWORD uVar1;
  QWORD uVar2;
  QWORD uVar3;
  QWORD uVar4;
  QWORD uVar5;
  
  uVar5 = 0;
  if ((param_3 & 0xffffffff) != 0) {
    do {
      uVar3 = *param_2;
      uVar4 = uVar3 * uVar3;
      uVar1 = *param_1 + uVar5;
      uVar2 = uVar1 + uVar4;
      *param_1 = uVar2;
      param_2 = param_2 + 1;
      uVar1 = SUB168(ZEXT816(uVar3) * ZEXT816(uVar3) >> 0x40,0) +
              (QWORD)
              (byte)(uVar2 < uVar4 != uVar1 < uVar5 | (uVar1 < uVar5 && uVar2 < uVar4) << 1);
      uVar5 = param_1[1] + uVar1;
      param_1[1] = uVar5;
      param_1 = param_1 + 2;
      uVar5 = (QWORD)(uVar5 < uVar1);
      param_3 = param_3 - 1;
    } while (param_3 != 0);
    return;
  }
  return;
}



QWORD FUN_00024c88(QWORD *param_1,QWORD param_2,int param_3,QWORD param_4)

{
  QWORD uVar1;
  QWORD uVar2;
  QWORD uVar3;
  QWORD uVar4;
  QWORD uVar5;
  
  uVar5 = 0;
  if (1 < param_2) {
    param_3 = param_3 - (int)param_1;
    if ((int)param_4 != 0) {
      do {
        uVar3 = *(QWORD *)((int)param_1 + param_3);
        uVar1 = *param_1;
        uVar4 = param_2 * uVar3;
        uVar2 = uVar1 - uVar5;
        *param_1 = uVar2 - uVar4;
        param_1 = param_1 + 1;
        uVar5 = SUB168(ZEXT816(param_2) * ZEXT816(uVar3) >> 0x40,0) +
                (QWORD)
                (byte)(uVar2 < uVar4 != uVar1 < uVar5 | (uVar1 < uVar5 && uVar2 < uVar4) << 1);
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
    return uVar5;
  }
  if (param_2 == 1) {
    uVar5 = 0;
    param_3 = param_3 - (int)param_1;
    if ((int)param_4 != 0) {
      do {
        uVar1 = *param_1;
        uVar3 = *(QWORD *)((int)param_1 + param_3);
        uVar2 = uVar1 - uVar5;
        *param_1 = uVar2 - uVar3;
        param_1 = param_1 + 1;
        uVar5 = (QWORD)
                (byte)(uVar2 < uVar3 != uVar1 < uVar5 | (uVar1 < uVar5 && uVar2 < uVar3) << 1);
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
    return uVar5;
  }
  return 0;
}



undefined8 FUN_00024d08(int param_1,int param_2,int param_3)

{
  QWORD *puVar1;
  QWORD *puVar2;
  
  puVar1 = (QWORD *)(param_3 * 8 + param_1);
  puVar2 = (QWORD *)(param_3 * 8 + param_2);
  while( true ) {
    if (param_3 == 0) {
      return 0;
    }
    puVar1 = puVar1 + -1;
    puVar2 = puVar2 + -1;
    if (*puVar1 != *puVar2) break;
    param_3 = param_3 + -1;
  }
  if (*puVar2 < *puVar1) {
    return 1;
  }
  return 0xffffffffffffffff;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00024d58(undefined8 param_1)

{
  QWORD in_r2;
  int iVar1;
  QWORD lVar2;
  undefined8 uVar3;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  lVar2 = ZEXT48(&0x16e50) + in_r2;
  HvpAquireSpinLock(lVar2);
  if ((&0x1000c)[(int)in_r2] != '\0') {
    iVar1 = XeCryptMemDiff(param_1,ZEXT48(&0x10010) + in_r2,0x10);
    uVar3 = 1;
    if (iVar1 == 0) goto LAB_00024db4;
  }
  uVar3 = 0;
LAB_00024db4:
  HvpReleaseSpinLock(lVar2);
  return uVar3;
}



QWORD FUN_00024dd8(undefined8 param_1,int param_2)

{
  QWORD in_r2;
  undefined *puVar1;
  undefined *puVar2;
  QWORD lVar3;
  QWORD uVar4;
  QWORD lVar5;
  qword back_chain;
  
  puVar1 = (undefined *)__Save_R12_29_thru_31();
  uVar4 = 0;
  if (param_2 == 0x10) {
    lVar3 = ZEXT48(&0x16e50) + in_r2;
    HvpAquireSpinLock(lVar3);
    uVar4 = (QWORD)(byte)(&0x1000c)[(int)in_r2];
    if ((&0x1000c)[(int)in_r2] != 0) {
      in_r2 = ZEXT48(&0x10010) + in_r2;
      lVar5 = 0x10;
      do {
        puVar2 = (undefined *)in_r2;
        in_r2 = in_r2 + 1;
        *puVar1 = *puVar2;
        puVar1 = puVar1 + 1;
        lVar5 = lVar5 + -1;
      } while (lVar5 != 0);
    }
    HvpReleaseSpinLock(lVar3);
  }
  return uVar4;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00024e50(byte *param_1)
{
  uint uVar1;
  QWORD in_r2;
  word *pwVar2;
  byte *pbVar3;
  undefined *puVar5;
  QWORD lVar4;
  QWORD lVar6;
  QWORD lVar7;
  qword back_chain;
  word local_190;
  word local_30;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  memset(param_1,0,0x32);
  param_1[1] = 0x30;
  *param_1 = *param_1 & 0xc0 | 0x3b;
  XeCryptAesKey(&local_190,*(QWORD *)(&0x163c0 + (int)in_r2) + 0x100);
  pwVar2 = &local_30;
  lVar6 = ZEXT48(&0x10030) + in_r2;
  lVar7 = 0x10;
  lVar4 = lVar6;
  do {
    puVar5 = (undefined *)lVar4;
    lVar4 = lVar4 + 1;
    *(undefined *)pwVar2 = *puVar5;
    pwVar2 = (word *)((int)pwVar2 + 1);
    lVar7 = lVar7 + -1;
  } while (lVar7 != 0);
  XeCryptAesCbc(&local_190,ZEXT48(&0x10020) + in_r2,0x10,param_1 + 2,&local_30,1);
  XeCryptAesCbc(&local_190,ZEXT48(&0x16b90) + in_r2,0x10,param_1 + 0x12,&local_30,1);
  param_1 = param_1 + 0x22;
  lVar4 = 0x10;
  do {
    pbVar3 = (byte *)lVar6;
    lVar6 = lVar6 + 1;
    *param_1 = *pbVar3;
    param_1 = param_1 + 1;
    lVar4 = lVar4 + -1;
  } while (lVar4 != 0);
  FUN_00000204((QWORD)uVar1);
  return;
}



void FUN_00024f60(void)

{
  uint uVar1;
  QWORD in_r2;
  byte *pbVar2;
  word *pwVar3;
  byte *pbVar4;
  undefined *puVar6;
  QWORD lVar5;
  byte *pbVar7;
  QWORD lVar8;
  QWORD lVar9;
  qword back_chain;
  word local_1d0;
  word local_70;
  word local_60;
  word local_50;
  word local_40;
  dword local_30;
  
  pbVar2 = (byte *)__Save_R12_29_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  memset(pbVar2,0,0x42);
  lVar8 = ZEXT48(&0x10030) + in_r2;
  *pbVar2 = *pbVar2 & 0xc0 | 0x28;
  pbVar2[1] = 0x40;
  FUN_00023620(*(QWORD *)(&0x163c0 + (int)in_r2) + 0x100,lVar8,&local_70,&local_60);
  XeCryptAesKey(&local_1d0,&local_60);
  pwVar3 = &local_50;
  lVar9 = 0x10;
  lVar5 = lVar8;
  do {
    puVar6 = (undefined *)lVar5;
    lVar5 = lVar5 + 1;
    *(undefined *)pwVar3 = *puVar6;
    pwVar3 = (word *)((int)pwVar3 + 1);
    lVar9 = lVar9 + -1;
  } while (lVar9 != 0);
  XeCryptAesCbc(&local_1d0,ZEXT48(&0x10020) + in_r2,0x10,pbVar2 + 2,&local_50,1);
  XeCryptAesCbc(&local_1d0,ZEXT48(&0x16b90) + in_r2,0x10,pbVar2 + 0x12,&local_50,1);
  pbVar7 = pbVar2 + 0x22;
  lVar5 = 0x10;
  do {
    pbVar4 = (byte *)lVar8;
    lVar8 = lVar8 + 1;
    *pbVar7 = *pbVar4;
    pbVar7 = pbVar7 + 1;
    lVar5 = lVar5 + -1;
  } while (lVar5 != 0);
  XeCryptAesCbcMac(ZEXT48(&0x10578) + in_r2,pbVar2 + 2,0x20,&local_40);
  FUN_00023620(&local_60,&local_40,&local_70,pbVar2 + 0x32);
  FUN_00000204((QWORD)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_000250b8(undefined8 param_1)

{
  int in_r2;
  QWORD lVar1;
  undefined *puVar2;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  puVar2 = &0x16e50 + in_r2;
  HvpAquireSpinLock(puVar2);
  lVar1 = HvpPhysicalToReal(param_1,0x4a);
  if ((*(ushort *)((int)*(undefined8 *)(&0x162d0 + in_r2) + 0x604) & 0x200) == 0x200) {
    FUN_00024f60();
  }
  else {
    FUN_00024e50(lVar1 + 8);
  }
  HvpReleaseSpinLock(puVar2);
  return 0;
}



void FUN_00025138(int param_1,int param_2)

{
  int in_r2;
  qword back_chain;
  qword local_8;
  
  if (param_1 != 0) {
    (&0x1000c)[in_r2] = 0;
    (&0x16e10)[in_r2] = 0;
  }
  if (param_2 != 0) {
    *(undefined4 *)(&0x10010 + in_r2) = 0;
    *(undefined4 *)(&0x10014 + in_r2) = 0;
    *(undefined4 *)(&0x10018 + in_r2) = 0;
    *(undefined4 *)(&0x1001c + in_r2) = 0;
  }
  memset(&0x16ba0 + in_r2,0,0x270);
  *(undefined4 *)(&0x16e14 + in_r2) = 1;
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_000251b8(undefined8 param_1)

{
  int in_r2;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  HvpAquireSpinLock(&0x16e50 + in_r2);
  FUN_00025138(param_1,0);
  HvpReleaseSpinLock(&0x16e50 + in_r2);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00025210(void)

{
  undefined uVar1;
  int iVar2;
  int iVar3;
  int in_r2;
  QWORD uVar4;
  qword back_chain;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar4 = (QWORD)(byte)(&0x16bc3)[in_r2] - (QWORD)((byte)(&0x16cf1)[in_r2] >> 3);
  XeCryptRandom(&local_20,4);
  trapWord(6,uVar4,0);
  iVar2 = local_20 - (int)((QWORD)local_20 / (uVar4 & 0xffffffff)) * (int)uVar4;
  iVar3 = (int)uVar4 + -1;
  uVar1 = (&0x16cf8 + in_r2)[iVar2];
  (&0x16cf8 + in_r2)[iVar2] = (&0x16cf8 + in_r2)[iVar3];
  (&0x16cf8 + in_r2)[iVar3] = uVar1;
  return;
}



undefined8 FUN_00025298(void){
  undefined uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  QWORD in_r2;
  int iVar5;
  QWORD lVar6;
  undefined *puVar7;
  QWORD uVar8;
  undefined8 uVar9;
  QWORD lVar10;
  qword back_chain;
  dword local_b0;
  word local_a0;
  word local_40;
  dword local_2c;
  
  iVar5 = __Save_R12_28_thru_31();
  iVar4 = (int)in_r2;
  uVar2 = *(uint *)(iVar4 + 0x10000);
  uVar9 = 0;
  memcpy(ZEXT48(&0x16cf0) + in_r2,iVar5,0x34);
  XeCryptShaInit(&local_a0);
  XeCryptShaUpdate(&local_a0,ZEXT48(&0x16cf0) + in_r2,0x24);
  *(uint *)(&0x16cf4 + iVar4) =
       (uint)(byte)(&0x16cf7)[iVar4] << 0x18 | (uint)(byte)(&0x16cf6)[iVar4] << 0x10 |
       (uint)(byte)(&0x16cf5)[iVar4] << 8 | (uint)(byte)(&0x16cf4)[iVar4];
  *(uint *)(&0x16d00 + iVar4) =
       (uint)(byte)(&0x16d03)[iVar4] << 0x18 | (uint)(byte)(&0x16d02)[iVar4] << 0x10 |
       (uint)(byte)(&0x16d01)[iVar4] << 8 | (uint)(byte)(&0x16d00)[iVar4];
  uVar8 = (QWORD)(byte)(&0x16d07)[iVar4] << 0x18 |
          (QWORD)(byte)(&0x16d06)[iVar4] << 0x10 |
          (QWORD)(byte)(&0x16d05)[iVar4] << 8 | (QWORD)(byte)(&0x16d04)[iVar4];
  *(int *)(&0x16d04 + iVar4) = (int)uVar8;
  uVar8 = (uVar8 - (*(uint *)(&0x16cfc + iVar4) >> 0xf)) - 0xc;
  *(uint *)(&0x16d08 + iVar4) =
       (uint)(byte)(&0x16d0b)[iVar4] << 0x18 | (uint)(byte)(&0x16d0a)[iVar4] << 0x10 |
       (uint)(byte)(&0x16d09)[iVar4] << 8 | (uint)(byte)(&0x16d08)[iVar4];
  *(uint *)(&0x16d0c + iVar4) =
       (uint)(byte)(&0x16d0f)[iVar4] << 0x18 | (uint)(byte)(&0x16d0e)[iVar4] << 0x10 |
       (uint)(byte)(&0x16d0d)[iVar4] << 8 | (uint)(byte)(&0x16d0c)[iVar4];
  *(uint *)(&0x16d10 + iVar4) =
       (uint)(byte)(&0x16d13)[iVar4] << 0x18 | (uint)(byte)(&0x16d12)[iVar4] << 0x10 |
       (uint)(byte)(&0x16d11)[iVar4] << 8 | (uint)(byte)(&0x16d10)[iVar4];
  XeCryptRandom(&local_b0,4);
  trapWord(6,uVar8,0);
  uVar8 = (QWORD)local_b0 -
          (QWORD)(int)((QWORD)local_b0 / (uVar8 & 0xffffffff)) * (QWORD)(int)uVar8;
  uVar3 = (uint)uVar8;
  *(uint *)(&0x16dfc + iVar4) = uVar3;
  if (((uVar3 + 0xb ^ uVar3) & 0xfffff800) != 0) {
    uVar8 = uVar8 - (uVar3 + 0xc & 0x7ff);
    *(int *)(&0x16dfc + iVar4) = (int)uVar8;
  }
  if ((uVar8 & 0xffffffff) < (QWORD)*(uint *)(&0x16d04 + iVar4)) {
    uVar3 = (uint)uVar8 >> 0xb;
    *(uint *)(&0x16df4 + iVar4) = uVar3;
    if (uVar3 < *(uint *)(&0x16d0c + iVar4)) {
      lVar6 = ZEXT48(&0x16d24) + in_r2;
      puVar7 = (undefined *)(uVar3 * 0x10 + iVar5 + 0x24);
      lVar10 = 0x10;
      do {
        uVar1 = *puVar7;
        puVar7 = puVar7 + 1;
        *(undefined *)lVar6 = uVar1;
        lVar6 = lVar6 + 1;
        lVar10 = lVar10 + -1;
      } while (lVar10 != 0);
      XeCryptShaUpdate(&local_a0,iVar5 + 0x24,
                       (QWORD)(uint)(*(int *)(&0x16df4 + iVar4) << 4));
      XeCryptShaUpdate(&local_a0,ZEXT48(&0x16d24) + in_r2,0x10);
      uVar3 = *(int *)(&0x16df4 + iVar4) * 0x10;
      if ((int)(uVar3 + 0x34) < 0x8000) {
        XeCryptShaUpdate(&local_a0,(*(int *)(&0x16df4 + iVar4) + 1) * 0x10 + iVar5 + 0x24,
                         0x7fcc - (QWORD)uVar3);
      }
      XeCryptShaFinal(&local_a0,&local_40,0x14);
      iVar5 = XeCryptMemDiff(ZEXT48(&0x16cc2) + in_r2,&local_40,0x14);
      if (iVar5 == 0) {
        *(undefined4 *)(&0x16ce8 + iVar4) = 1;
        *(uint *)(&0x16e00 + iVar4) =
             ((*(uint *)(&0x16dfc + iVar4) >> 0xb) + *(int *)(&0x16d00 + iVar4)) * 0x10 +
             *(int *)(&0x16cd8 + iVar4);
        goto LAB_00025494;
      }
    }
  }
  uVar9 = 0xffffffffc8000085;
LAB_00025494:
  FUN_00000204((QWORD)uVar2);
  return uVar9;
}



// WARNING: Variable defined which should be unmapped: back_chain

void FUN_000254a8(void)

{
  uint uVar1;
  uint uVar2;
  int in_r2;
  uint uVar3;
  int iVar4;
  qword back_chain;
  
  iVar4 = *(int *)(&0x16e08 + in_r2);
  if (iVar4 != 0xc) {
    uVar1 = *(uint *)(&0x16d04 + in_r2);
    uVar3 = *(uint *)(&0x16dfc + in_r2);
    do {
      trapDoubleWordImmediate(6,(QWORD)uVar1,0);
      uVar2 = ((int)((QWORD)uVar3 * (QWORD)*(uint *)(&0x16cf4 + in_r2)) -
              (int)(((QWORD)uVar3 * (QWORD)*(uint *)(&0x16cf4 + in_r2)) /
                   (QWORD)uVar1) * uVar1) * 0x10;
      *(uint *)(&0x16e04 + in_r2) = uVar2;
      if (uVar2 < *(uint *)(&0x16cd8 + in_r2)) {
        return;
      }
      if (*(int *)(&0x16d10 + in_r2) + *(int *)(&0x16d08 + in_r2) +
          *(uint *)(&0x16cd8 + in_r2) <= uVar2) {
        return;
      }
      iVar4 = iVar4 + 1;
      uVar3 = uVar3 + 1;
      *(int *)(&0x16e08 + in_r2) = iVar4;
      *(uint *)(&0x16dfc + in_r2) = uVar3;
    } while (iVar4 != 0xc);
  }
  return;
}



undefined8 FUN_00025530(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  QWORD in_r2;
  QWORD lVar4;
  int iVar6;
  undefined8 uVar5;
  qword back_chain;
  word local_40;
  dword local_30;
  
  lVar4 = __Save_R12_29_thru_31();
  iVar2 = (int)in_r2;
  uVar3 = *(uint *)(&0x16dfc + iVar2) & 0x7ff;
  uVar1 = *(uint *)(iVar2 + 0x10000);
  memcpy(ZEXT48(&0x16d34) + in_r2,(QWORD)uVar3 * 0x10 + lVar4,0xc0);
  XeCryptSha(lVar4,(QWORD)(uVar3 << 4),ZEXT48(&0x16d34) + in_r2,0xc0,
             (QWORD)((uVar3 + 0xc) * 0x10) + lVar4,(QWORD)((0x7f4 - uVar3) * 0x10),&local_40
             ,0x10);
  iVar6 = XeCryptMemDiff(&local_40,ZEXT48(&0x16d24) + in_r2,0x10);
  if (iVar6 == 0) {
    *(undefined4 *)(&0x16ce8 + iVar2) = 2;
    *(undefined4 *)(&0x16e08 + iVar2) = 0;
    *(undefined4 *)(&0x16e0c + iVar2) = 0;
    FUN_000254a8();
    FUN_00000204((QWORD)uVar1);
    uVar5 = 0;
  }
  else {
    FUN_00000204((QWORD)uVar1);
    uVar5 = 0xffffffffc8000085;
  }
  return uVar5;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00025600(undefined8 param_1,undefined4 *param_2)

{
  uint uVar1;
  int iVar2;
  QWORD in_r2;
  int iVar3;
  undefined8 uVar4;
  qword back_chain;
  word local_30;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  XeCryptSha(param_1,0x8000,0,0,0,0,&local_30,0x10);
  iVar2 = (int)in_r2;
  iVar3 = XeCryptMemDiff(&local_30,
                         (QWORD)*(uint *)(&0x16e08 + iVar2) * 0x10 +
                         ZEXT48(&0x16d34) + in_r2,0x10);
  if (iVar3 == 0) {
    iVar3 = *(int *)(&0x16e0c + iVar2) + 1;
  }
  else {
    iVar3 = 0;
  }
  *(int *)(&0x16e0c + iVar2) = iVar3;
  *(int *)(&0x16e08 + iVar2) = *(int *)(&0x16e08 + iVar2) + 1;
  *(int *)(&0x16dfc + iVar2) = *(int *)(&0x16dfc + iVar2) + 1;
  FUN_000254a8();
  if (*(int *)(&0x16e0c + iVar2) == 4) {
    uVar4 = 0;
  }
  else {
    if (*(int *)(&0x16e08 + iVar2) != 0xc) {
      FUN_00000204((QWORD)uVar1);
      return 0;
    }
    uVar4 = 0xffffffffc8000085;
  }
  *param_2 = 1;
  FUN_00000204((QWORD)uVar1);
  return uVar4;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00025708(undefined param_1)

{
  int in_r2;
  undefined *puVar1;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  puVar1 = &0x16e50 + in_r2;
  HvpAquireSpinLock(puVar1);
  (&0x16e11)[in_r2] = param_1;
  HvpReleaseSpinLock(puVar1);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x0002583c)
// WARNING: Removing unreachable block (ram,0x00025868)
// WARNING: Removing unreachable block (ram,0x0002587c)

undefined8 FUN_00025760(undefined8 param_1,int param_2)

{
  QWORD in_r2;
  int iVar2;
  undefined8 uVar1;
  QWORD lVar3;
  undefined *puVar4;
  undefined *puVar5;
  QWORD lVar6;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (param_2 == 1) {
    if ((&0x16e10)[(int)in_r2] == '\x01') {
      iVar2 = HvpPhysicalToReal(param_1,0x804);
      puVar5 = (undefined *)(iVar2 + 0x10c);
      lVar3 = ZEXT48(&0x16cc2) + in_r2;
      *(undefined4 *)(iVar2 + 0x104) = *(undefined4 *)(&0x16cd8 + (int)in_r2);
      *(undefined *)(iVar2 + 0x14) = (&0x16cec)[(int)in_r2];
      lVar6 = 0x14;
      do {
        puVar4 = (undefined *)lVar3;
        lVar3 = lVar3 + 1;
        *puVar5 = *puVar4;
        puVar5 = puVar5 + 1;
        lVar6 = lVar6 + -1;
      } while (lVar6 != 0);
      puVar5 = (undefined *)(iVar2 + 8);
      lVar3 = ZEXT48(&0x16cdc) + in_r2;
      lVar6 = 0xc;
      do {
        puVar4 = (undefined *)lVar3;
        lVar3 = lVar3 + 1;
        *puVar5 = *puVar4;
        puVar5 = puVar5 + 1;
        lVar6 = lVar6 + -1;
      } while (lVar6 != 0);
      uVar1 = 0;
    }
    else {
      uVar1 = 0xffffffffc8000080;
    }
  }
  else {
    if (param_2 == 0) {
      uVar1 = 0xffffffffc8000096;
    }
    else {
      uVar1 = 0xffffffffc800008a;
    }
  }
  return uVar1;
}



undefined8 FUN_000258a8(undefined8 param_1,undefined4 param_2)

{
  QWORD in_r2;
  int iVar1;
  undefined4 uVar2;
  qword back_chain;
  
  uVar2 = __Save_R12_29_thru_31();
  iVar1 = (int)in_r2;
  HvpAquireSpinLock(ZEXT48(&0x16e50) + in_r2);
  *(undefined4 *)(&0x16e20 + iVar1) = uVar2;
  *(undefined4 *)(&0x16e24 + iVar1) = param_2;
  HvpReleaseSpinLock(ZEXT48(&0x16e50) + in_r2);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_000258f0(undefined8 param_1)

{
  undefined4 uVar1;
  QWORD in_r2;
  QWORD lVar2;
  undefined4 *puVar3;
  QWORD lVar4;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  puVar3 = (undefined4 *)HvpPhysicalToReal(param_1,0x28);
  lVar2 = ZEXT48(&0x16e50) + in_r2;
  HvpAquireSpinLock(lVar2);
  in_r2 = ZEXT48(&0x16e28) + in_r2;
  lVar4 = 10;
  do {
    uVar1 = *puVar3;
    puVar3 = puVar3 + 1;
    *(undefined4 *)in_r2 = uVar1;
    in_r2 = in_r2 + 4;
    lVar4 = lVar4 + -1;
  } while (lVar4 != 0);
  HvpReleaseSpinLock(lVar2);
  return 0;
}



// WARNING: Removing unreachable block (ram,0x00025a08)
// WARNING: Removing unreachable block (ram,0x00025a10)

undefined8 FUN_00025970(void)

{
  dword dVar1;
  QWORD in_r2;
  dword *pdVar2;
  QWORD lVar3;
  QWORD lVar4;
  qword back_chain;
  dword local_50;
  dword local_4c;
  dword local_48;
  
  __Save_R12_29_thru_31();
  lVar3 = ZEXT48(&0x16e50) + in_r2;
  HvpAquireSpinLock(lVar3);
  pdVar2 = &local_50;
  in_r2 = ZEXT48(&0x16e28) + in_r2;
  lVar4 = 10;
  do {
    dVar1 = *pdVar2;
    pdVar2 = pdVar2 + 1;
    *(dword *)in_r2 = dVar1;
    in_r2 = in_r2 + 4;
    lVar4 = lVar4 + -1;
  } while (lVar4 != 0);
  FUN_00025138(1,1);
  HvpReleaseSpinLock(lVar3);
  return 0;
}



undefined8 FUN_00025a18(int param_1,undefined4 param_2)

{
  int iVar1;
  QWORD in_r2;
  qword back_chain;
  qword local_8;
  
  iVar1 = (int)in_r2;
  if (param_1 == 0) {
    *(undefined4 *)(&0x16e14 + iVar1) = param_2;
  }
  else {
    (&0x1000c)[iVar1] = 0;
    (&0x16e10)[iVar1] = 0;
    memset(ZEXT48(&0x16ba0) + in_r2,0,0x270);
    *(undefined4 *)(&0x16e14 + (int)in_r2) = 1;
  }
  HvpReleaseSpinLock(ZEXT48(&0x16e50) + in_r2);
  return 0;
}



undefined8 FUN_00025a90(undefined8 param_1,QWORD param_2,QWORD param_3)

{
  QWORD in_r2;
  QWORD uVar1;
  undefined *puVar2;
  undefined *puVar3;
  QWORD lVar4;
  undefined8 uVar5;
  QWORD lVar6;
  qword back_chain;
  
  uVar1 = __Save_R12_29_thru_31();
  if (((uVar1 & 0xfff) == 0) && ((param_2 & 0xffffffff) == 0x10)) {
    lVar4 = ZEXT48(&0x16e50) + in_r2;
    HvpAquireSpinLock(lVar4);
    if (((param_3 & 0xffffffff) == 0) ||
       (((&0x1000c)[(int)in_r2] != '\0' && ((&0x16e10)[(int)in_r2] != '\0')))) {
      puVar2 = (undefined *)HvpPhysicalToReal(uVar1,0x10);
      in_r2 = ZEXT48(&0x10010) + in_r2;
      lVar6 = 0x10;
      do {
        puVar3 = (undefined *)in_r2;
        in_r2 = in_r2 + 1;
        *puVar2 = *puVar3;
        puVar2 = puVar2 + 1;
        lVar6 = lVar6 + -1;
      } while (lVar6 != 0);
      uVar5 = 0;
    }
    else {
      uVar5 = 0xffffffffc8000088;
    }
    HvpReleaseSpinLock(lVar4);
  }
  else {
    uVar5 = 0xffffffffc8000087;
  }
  return uVar5;
}



void FUN_00025b50(undefined8 param_1,QWORD param_2,undefined8 param_3)

{
  uint uVar1;
  QWORD in_r2;
  QWORD lVar2;
  word *pwVar3;
  undefined *puVar5;
  QWORD lVar4;
  QWORD lVar6;
  qword back_chain;
  word local_1a0;
  word local_40;
  dword local_30;
  
  lVar2 = __Save_R12_28_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  XeCryptAesKey(&local_1a0,ZEXT48(&0x10020) + in_r2);
  pwVar3 = &local_40;
  in_r2 = ZEXT48(&0x10030) + in_r2;
  lVar6 = 0x10;
  lVar4 = in_r2;
  do {
    puVar5 = (undefined *)lVar4;
    lVar4 = lVar4 + 1;
    *(undefined *)pwVar3 = *puVar5;
    pwVar3 = (word *)((int)pwVar3 + 1);
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  XeCryptAesCbc(&local_1a0,param_2 + 0x10,0x20,param_2 + 0x10,&local_40,param_3);
  pwVar3 = &local_40;
  lVar4 = 0x10;
  do {
    puVar5 = (undefined *)in_r2;
    in_r2 = in_r2 + 1;
    *(undefined *)pwVar3 = *puVar5;
    pwVar3 = (word *)((int)pwVar3 + 1);
    lVar4 = lVar4 + -1;
  } while (lVar4 != 0);
  XeCryptAesCbc(&local_1a0,lVar2 + 2,0x30,lVar2 + 2,&local_40,param_3);
  FUN_00000204((QWORD)uVar1);
  return;
}



QWORD FUN_00025c20(undefined8 param_1,QWORD param_2)

{
  byte bVar1;
  int in_r2;
  QWORD lVar2;
  QWORD uVar3;
  int iVar4;
  byte *pbVar5;
  QWORD lVar6;
  QWORD lVar7;
  qword back_chain;
  
  lVar2 = __Save_R12_28_thru_31();
  lVar7 = lVar2 + 2;
  uVar3 = FUN_00003570(lVar7,0x10);
  if ((uVar3 & 0xffffffff) == 0) {
    uVar3 = FUN_00003570(param_2 + 0x10,0x10);
    if ((uVar3 & 0xffffffff) == 0) {
      FUN_00025b50(lVar2,param_2,0);
      pbVar5 = (byte *)param_2;
      bVar1 = *pbVar5;
      if ((bVar1 < 6) && (pbVar5[1] < 0x10)) {
        lVar6 = *(QWORD *)(&0x162d0 + in_r2);
        iVar4 = (int)(lVar6 + 0x8a0);
        *(byte *)((uint)bVar1 + iVar4) = pbVar5[1];
        *(undefined4 *)(((uint)bVar1 + 2) * 4 + iVar4) = *(undefined4 *)(pbVar5 + 0xc);
        memcpy(((QWORD)bVar1 + 1) * 0x20 + lVar6 + 0x8a0,lVar7,0x20);
        iVar4 = XeCryptMemDiff(lVar7,param_2 + 0x10,0x10);
        if ((iVar4 == 0) && (uVar3 = FUN_00003570(lVar2 + 0x12,0x10), (uVar3 & 0xffffffff) == 0)) {
          return uVar3;
        }
      }
    }
  }
  return 0xffffffffc8000087;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00025d08(int param_1,byte *param_2)

{
  byte bVar1;
  int iVar2;
  int in_r2;
  undefined8 uVar3;
  byte *pbVar4;
  QWORD lVar5;
  byte *pbVar6;
  undefined *puVar7;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  bVar1 = *param_2;
  if ((bVar1 < 6) && (param_2[1] < 0x10)) {
    lVar5 = *(QWORD *)(&0x162d0 + in_r2);
    iVar2 = (int)(lVar5 + 0x8a0);
    *(undefined *)((uint)bVar1 + iVar2) = 0xff;
    *(undefined4 *)(((uint)bVar1 + 2) * 4 + iVar2) = 0x103;
    memset(((QWORD)bVar1 + 1) * 0x20 + lVar5 + 0x8a0,0,0x20);
    pbVar6 = param_2 + 0x10;
    pbVar4 = (byte *)(param_1 + 2);
    lVar5 = 0x10;
    do {
      bVar1 = *pbVar4;
      pbVar4 = pbVar4 + 1;
      *pbVar6 = bVar1;
      pbVar6 = pbVar6 + 1;
      lVar5 = lVar5 + -1;
    } while (lVar5 != 0);
    puVar7 = (undefined *)(param_1 + 0x12);
    lVar5 = 0x10;
    do {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
      lVar5 = lVar5 + -1;
    } while (lVar5 != 0);
    FUN_00025b50(param_1,param_2,1);
    uVar3 = 0;
  }
  else {
    uVar3 = 0xffffffffc8000087;
  }
  return uVar3;
}



undefined8 FUN_00025df8(int param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  undefined uVar3;
  
  if (0xf < *(byte *)(param_2 + 1)) {
    return 0xffffffffc8000087;
  }
  bVar1 = *(byte *)((uint)*(byte *)(param_2 + 1) + param_1 + 2);
  uVar2 = (uint)(bVar1 >> 1) & 7;
  uVar3 = (undefined)uVar2;
  *(byte *)(param_1 + 0x2e) = bVar1 & 1;
  if ((bVar1 >> 1 & 7) != 0) {
    uVar3 = (undefined)(1 << (QWORD)uVar2);
  }
  *(undefined *)(param_1 + 0x2f) = uVar3;
  *(byte *)(param_1 + 0x30) = bVar1 >> 4;
  return 0;
}



undefined8 FUN_00025e60(byte *param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  QWORD uVar3;
  uint uVar4;
  QWORD uVar5;
  
  if (((*param_1 & 0x3f) != 0x24) && ((*param_1 & 0x3f) != 0x23)) {
    *(undefined *)(param_2 + 1) = 0;
    return 0;
  }
  bVar1 = param_1[0x2e];
  if ((bVar1 == 0) || (bVar1 == 1)) {
    bVar2 = param_1[0x2f];
    uVar3 = (QWORD)bVar2;
    uVar4 = 0;
    uVar5 = uVar3;
    if (bVar2 < 0x11) {
      while ((uVar5 != 0 && ((uVar5 & 1) == 0))) {
        uVar4 = uVar4 + 1 & 0xff;
        uVar5 = uVar5 >> 1;
      }
      if ((uVar5 & 0xfffffffe) == 0) {
        if (bVar2 == 0) {
          uVar3 = 1;
        }
        if ((param_1[0x30] < uVar3) && (*(byte *)(param_2 + 1) < 0x10)) {
          param_1[(uint)*(byte *)(param_2 + 1) + 2] =
               (byte)(((uint)param_1[0x30] << 3 | uVar4 & 7) << 1) | bVar1 & 1;
          return 0;
        }
      }
    }
  }
  return 0xffffffffc8000087;
}



void FUN_00025f40(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  int iVar2;
  qword back_chain;
  dword local_30;
  
  iVar1 = __Save_R12_29_thru_31();
  iVar2 = *(int *)(iVar1 + 2);
  if (iVar2 == -1) {
    XeCryptRandom(&local_30,4);
  }
  *(byte *)((int)param_2 + 1) = (byte)iVar2 & 0xf;
  XeCryptRandom((int *)(iVar1 + 2),0x10);
  iVar2 = FUN_00025e60(iVar1,param_2);
  if (iVar2 == 0) {
    FUN_00025d08(iVar1);
  }
  return;
}



undefined8 FUN_00025fb0(QWORD param_1,int param_2)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  QWORD lVar3;
  undefined *puVar4;
  QWORD lVar5;
  char *pcVar6;
  QWORD lVar7;
  qword back_chain;
  qword local_8;
  
  pcVar6 = (char *)*(QWORD *)(&0x162e0 + in_r2);
  if ((*pcVar6 == '\0') ||
     ((byte)(*(byte *)param_1 & 0x3f) !=
      (byte)((-((*(uint *)(pcVar6 + 0x110) & 1) != 0) & 5U) + 0x24))) {
    uVar2 = 0xffffffffc8000089;
  }
  else {
    lVar5 = param_1 + 2;
    uVar1 = *(uint *)lVar5;
    if ((QWORD)uVar1 < (QWORD)(*(uint *)(pcVar6 + 0x118) >> 5)) {
      lVar3 = (QWORD)uVar1 * 0x20 +
              (QWORD)*(uint *)(pcVar6 + 0x11c) + *(QWORD *)(&0x162e0 + in_r2);
      lVar7 = 0x10;
      do {
        puVar4 = (undefined *)lVar3;
        lVar3 = lVar3 + 1;
        *(undefined *)lVar5 = *puVar4;
        lVar5 = lVar5 + 1;
        lVar7 = lVar7 + -1;
      } while (lVar7 != 0);
      *(byte *)(param_2 + 1) = (byte)uVar1 & 0xf;
      uVar2 = FUN_00025df8(param_1);
      if ((int)uVar2 == 0) {
        uVar2 = FUN_00025d08(param_1);
      }
    }
    else {
      uVar2 = 0xffffffffc8000087;
    }
  }
  return uVar2;
}



undefined8 FUN_00026098(undefined8 param_1,QWORD param_2)

{
  uint uVar1;
  uint uVar2;
  int in_r2;
  byte *pbVar4;
  undefined8 uVar3;
  byte *pbVar5;
  char cVar7;
  undefined *puVar6;
  QWORD lVar8;
  byte *pbVar9;
  byte bVar10;
  QWORD lVar11;
  QWORD lVar12;
  char *pcVar13;
  QWORD lVar14;
  qword back_chain;
  dword local_40;
  
  pbVar4 = (byte *)__Save_R12_27_thru_31();
  lVar12 = *(QWORD *)(&0x162e0 + in_r2);
  pcVar13 = (char *)lVar12;
  if (*pcVar13 == '\0') {
    uVar3 = 0xffffffffc8000089;
  }
  else {
    uVar1 = *(uint *)(pcVar13 + 0x11c);
    uVar2 = *(uint *)(pcVar13 + 0x118) >> 5;
    XeCryptRandom(&local_40,4);
    trapWord(6,(QWORD)uVar2,0);
    lVar11 = (QWORD)local_40 - (QWORD)(int)(local_40 / uVar2) * (QWORD)(int)uVar2;
    memset(pbVar4,0,0x32);
    lVar14 = 0xc;
    lVar8 = param_2;
    do {
      *(undefined4 *)lVar8 = 0;
      lVar8 = lVar8 + 4;
      lVar14 = lVar14 + -1;
    } while (lVar14 != 0);
    if ((*(uint *)(pcVar13 + 0x110) & 1) == 0) {
      bVar10 = 0x24;
      cVar7 = '2';
    }
    else {
      bVar10 = 0x29;
      cVar7 = '\"';
    }
    lVar8 = (lVar11 * 0x20 & 0x1fffffffe0U) + (QWORD)uVar1 + lVar12;
    pbVar9 = pbVar4 + 2;
    pbVar4[1] = cVar7 - 2;
    *pbVar4 = bVar10 | *pbVar4 & 0xc0;
    lVar14 = 0x10;
    lVar12 = lVar8;
    do {
      pbVar5 = (byte *)lVar12;
      lVar12 = lVar12 + 1;
      *pbVar9 = *pbVar5;
      pbVar9 = pbVar9 + 1;
      lVar14 = lVar14 + -1;
    } while (lVar14 != 0);
    lVar8 = lVar8 + 0x10;
    lVar12 = param_2 + 0x20;
    lVar14 = 0x10;
    do {
      puVar6 = (undefined *)lVar8;
      lVar8 = lVar8 + 1;
      *(undefined *)lVar12 = *puVar6;
      lVar12 = lVar12 + 1;
      lVar14 = lVar14 + -1;
    } while (lVar14 != 0);
    if (bVar10 == 0x24) {
      *(byte *)((int)param_2 + 1) = (byte)lVar11 & 0xf;
      uVar3 = FUN_00025df8(pbVar4,param_2);
      if ((int)uVar3 != 0) {
        return uVar3;
      }
    }
    uVar3 = FUN_00025d08(pbVar4,param_2);
  }
  return uVar3;
}



undefined8 FUN_000261f8(undefined8 param_1,QWORD param_2)

{
  QWORD lVar1;
  undefined8 uVar2;
  int iVar3;
  qword back_chain;
  
  lVar1 = __Save_R12_29_thru_31();
  uVar2 = FUN_00025c20();
  if ((int)uVar2 == 0) {
    iVar3 = XeCryptMemDiff(lVar1 + 2,param_2 + 0x10,0x10);
    if ((iVar3 == 0) && (iVar3 = XeCryptMemDiff(lVar1 + 0x12,param_2 + 0x20,0x10), iVar3 == 0)) {
      return 0;
    }
    uVar2 = 0xffffffffc800008a;
  }
  FUN_00003830(0,0x800);
  return uVar2;
}



// WARNING: Removing unreachable block (ram,0x000262c0)
// WARNING: Removing unreachable block (ram,0x000262fc)
// WARNING: Removing unreachable block (ram,0x00026310)
// WARNING: Removing unreachable block (ram,0x00026328)
// WARNING: Removing unreachable block (ram,0x00026330)
// WARNING: Removing unreachable block (ram,0x00026340)
// WARNING: Removing unreachable block (ram,0x00026348)
// WARNING: Removing unreachable block (ram,0x00026358)
// WARNING: Removing unreachable block (ram,0x00026360)
// WARNING: Removing unreachable block (ram,0x00026370)
// WARNING: Removing unreachable block (ram,0x00026378)
// WARNING: Removing unreachable block (ram,0x0002638c)
// WARNING: Removing unreachable block (ram,0x00026318)
// WARNING: Removing unreachable block (ram,0x00026384)
// WARNING: Removing unreachable block (ram,0x00026394)
// WARNING: Removing unreachable block (ram,0x0002639c)
// WARNING: Removing unreachable block (ram,0x000263ac)
// WARNING: Removing unreachable block (ram,0x000263b8)
// WARNING: Removing unreachable block (ram,0x000263cc)
// WARNING: Removing unreachable block (ram,0x000263d8)
// WARNING: Removing unreachable block (ram,0x000263f8)
// WARNING: Removing unreachable block (ram,0x0002640c)

undefined8 FUN_00026278(void)

{
  int in_r2;
  qword back_chain;
  word local_90;
  word local_60;
  dword local_2c;
  
  __Save_R12_29_thru_31();
  FUN_00000204((QWORD)*(uint *)(in_r2 + 0x10000));
  return 0xffffffffc8000089;
}



// WARNING: Removing unreachable block (ram,0x0002644c)
// WARNING: Removing unreachable block (ram,0x0002645c)

undefined8 FUN_00026420(void)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  QWORD in_r2;
  undefined8 uVar4;
  QWORD uVar5;
  int iVar6;
  word *pwVar7;
  undefined *puVar9;
  QWORD lVar8;
  QWORD lVar10;
  QWORD lVar11;
  QWORD lVar12;
  QWORD lVar13;
  QWORD lVar14;
  qword back_chain;
  qword local_1e0;
  dword local_1d4;
  word local_1d0;
  word local_70;
  word local_50;
  dword local_40;
  
  uVar4 = __Save_R12_27_thru_31();
  iVar3 = (int)in_r2;
  uVar1 = *(uint *)(iVar3 + 0x10000);
  memcpy(*(undefined8 *)(&0x162e0 + iVar3),uVar4,0x4000);
  lVar13 = *(QWORD *)(&0x162e0 + iVar3);
  puVar2 = (undefined *)lVar13;
  if ((*(uint *)(puVar2 + 0x110) & 0x80000000) == 0) {
    puVar9 = &0x11318;
  }
  else {
    puVar9 = &0x10ad8;
  }
  lVar11 = lVar13 + 0x100;
  XeCryptHmacSha(0x20,0x10,lVar11,0x40,0,0,0,0);
  uVar5 = FUN_000038d8(&local_70,lVar13,ZEXT48(puVar9) + in_r2);
  if ((uVar5 & 0xffffffff) != 0) {
    lVar10 = 0x4000 - (QWORD)*(uint *)(puVar2 + 0x11c);
    lVar12 = (QWORD)*(uint *)(puVar2 + 0x11c) + lVar13;
    XeCryptAesKey(&local_1d0,0x20);
    pwVar7 = &local_50;
    lVar14 = 0x10;
    lVar8 = lVar11;
    do {
      puVar9 = (undefined *)lVar8;
      lVar8 = lVar8 + 1;
      *(undefined *)pwVar7 = *puVar9;
      pwVar7 = (word *)((int)pwVar7 + 1);
      lVar14 = lVar14 + -1;
    } while (lVar14 != 0);
    XeCryptAesCbc(&local_1d0,lVar12,lVar10,lVar12,&local_50,0);
    XeCryptSha(lVar12,lVar10,0,0,0,0,&local_70,0x14);
    iVar6 = XeCryptMemDiff(&local_70,lVar13 + 300,0x14);
    if (iVar6 == 0) {
      memset(lVar13,0,0x100);
      uVar4 = 0;
      *(undefined4 *)lVar11 = 0;
      *(undefined4 *)(puVar2 + 0x104) = 0;
      *(undefined4 *)(puVar2 + 0x108) = 0;
      *(undefined4 *)(puVar2 + 0x10c) = 0;
      *(undefined4 *)(lVar13 + 300) = 0;
      *(undefined4 *)(puVar2 + 0x130) = 0;
      *(undefined4 *)(puVar2 + 0x134) = 0;
      *(undefined4 *)(puVar2 + 0x138) = 0;
      *(undefined4 *)(puVar2 + 0x13c) = 0;
      *puVar2 = 1;
      goto LAB_00026520;
    }
  }
  uVar4 = 0xffffffffc800008a;
  memset(*(undefined8 *)(&0x162e0 + iVar3),0,0x4000);
  FUN_00003830(8,0);
LAB_00026520:
  FUN_00003830(0x1000000,0);
  FUN_00000204((QWORD)uVar1);
  return uVar4;
}



// WARNING: Removing unreachable block (ram,0x0002666c)
// WARNING: Removing unreachable block (ram,0x0002667c)
// WARNING: Removing unreachable block (ram,0x00026688)
// WARNING: Removing unreachable block (ram,0x00026690)
// WARNING: Removing unreachable block (ram,0x0002669c)
// WARNING: Removing unreachable block (ram,0x000266a8)
// WARNING: Removing unreachable block (ram,0x00026788)
// WARNING: Removing unreachable block (ram,0x000266b0)
// WARNING: Removing unreachable block (ram,0x00026718)
// WARNING: Removing unreachable block (ram,0x0002672c)

undefined8 FUN_00026620(void)

{
  int in_r2;
  qword back_chain;
  qword local_1b0;
  dword local_1a4;
  word local_1a0;
  word local_40;
  dword local_30;
  
  __Save_R12_28_thru_31();
  FUN_00000204((QWORD)*(uint *)(in_r2 + 0x10000));
  return 0xffffffffc8000089;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_000267b8(int param_1,QWORD param_2,int param_3)

{
  undefined8 uVar1;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  if (((param_2 & 0xfff) == 0) && (param_3 == 0x4000)) {
    HvpPhysicalToReal(param_2,0x4000);
    if (param_1 == 0) {
      uVar1 = FUN_00026420();
      return uVar1;
    }
    if (param_1 == 1) {
      uVar1 = FUN_00026620();
      return uVar1;
    }
  }
  return 0xffffffffc8000087;
}



void FUN_00026828(void)
{
  QWORD in_r2;
  int iVar1;
  qword back_chain;
  qword local_8;
  
  XeCryptRandom(ZEXT48(&0x10020) + in_r2,0x10);
  XeCryptRandom(ZEXT48(&0x10030) + in_r2,0x10);
  iVar1 = (int)in_r2;
  XeCryptRandom(ZEXT48(&0x16b90) + in_r2,0x10);
  FUN_00003830(0,0x800);
  *(undefined4 *)(&0x16e20 + iVar1) = 0;
  *(undefined4 *)(&0x16e28 + iVar1) = 0;
  FUN_00025138(1,1);
  return;
}



undefined8 FUN_000268a0(undefined8 param_1,int param_2)

{
  uint uVar1;
  QWORD in_r2;
  int iVar2;
  undefined8 uVar3;
  int iVar5;
  QWORD uVar4;
  word *pwVar6;
  QWORD lVar7;
  undefined *puVar8;
  undefined4 uVar9;
  QWORD lVar10;
  byte bVar11;
  QWORD lVar12;
  qword back_chain;
  word local_1c0;
  word local_60;
  word local_50;
  word local_40;
  dword local_30;
  
  uVar3 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if (param_2 < 0) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc8000080;
  }
  bVar11 = 0x28;
  if ((*(ushort *)((int)*(undefined8 *)(&0x162d0 + (int)in_r2) + 0x604) & 0x200) != 0x200) {
    bVar11 = 0x3b;
  }
  iVar5 = HvpPhysicalToReal(uVar3,0x4a);
  lVar10 = ZEXT48(&0x16e50) + in_r2;
  HvpAquireSpinLock(lVar10);
  iVar2 = (int)in_r2;
  if (((*(byte *)(iVar5 + 8) & 0x3f) == bVar11) && (*(char *)(iVar5 + 9) == '0')) {
    XeCryptAesKey(&local_1c0,ZEXT48(&0x10020) + in_r2);
    pwVar6 = &local_60;
    lVar7 = ZEXT48(&0x10030) + in_r2;
    lVar12 = 0x10;
    do {
      puVar8 = (undefined *)lVar7;
      lVar7 = lVar7 + 1;
      *(undefined *)pwVar6 = *puVar8;
      pwVar6 = (word *)((int)pwVar6 + 1);
      lVar12 = lVar12 + -1;
    } while (lVar12 != 0);
    XeCryptAesCbc(&local_1c0,iVar5 + 10,0x20,&local_50,&local_60,0);
    uVar4 = FUN_00003570(&local_50,0x10);
    iVar2 = (int)in_r2;
    if (((uVar4 & 0xffffffff) != 0) &&
       (iVar5 = XeCryptMemDiff(&local_40,ZEXT48(&0x16b90) + in_r2,0x10), iVar5 == 0)) {
      FUN_00003830(0x800,0);
      uVar9 = 7;
      uVar3 = 0;
      goto LAB_000269e0;
    }
    uVar9 = 6;
  }
  else {
    uVar9 = 5;
  }
  uVar3 = 0xffffffffc8000080;
LAB_000269e0:
  *(undefined4 *)(&0x16e20 + iVar2) = uVar9;
  *(undefined4 *)(&0x16e24 + iVar2) = 0;
  HvpReleaseSpinLock(lVar10);
  FUN_00000204((QWORD)uVar1);
  return uVar3;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00026a10(undefined8 param_1)

{
  undefined uVar1;
  uint uVar2;
  QWORD in_r2;
  int iVar4;
  undefined8 uVar3;
  word *pwVar5;
  undefined *puVar6;
  QWORD lVar7;
  qword back_chain;
  word local_190;
  word local_30;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  iVar4 = FUN_00025970(1);
  if (iVar4 == 0) {
    FUN_00000204((QWORD)uVar2);
    uVar3 = 0xffffffffc8000086;
  }
  else {
    iVar4 = HvpPhysicalToReal(param_1,0x2a);
    XeCryptAesKey(&local_190,ZEXT48(&0x10020) + in_r2);
    puVar6 = (undefined *)(iVar4 + 0x1a);
    pwVar5 = &local_30;
    lVar7 = 0x10;
    do {
      uVar1 = *puVar6;
      puVar6 = puVar6 + 1;
      *(undefined *)pwVar5 = uVar1;
      pwVar5 = (word *)((int)pwVar5 + 1);
      lVar7 = lVar7 + -1;
    } while (lVar7 != 0);
    lVar7 = in_r2;
    memcpy(ZEXT48(&0x16ba0) + in_r2,iVar4 + 8,0x22);
    XeCryptAesCbc(&local_190,iVar4 + 10,0x10,ZEXT48(&0x16ba2) + in_r2,&local_30,0);
    *(undefined4 *)(&0x16e14 + (int)lVar7) = 2;
    HvpReleaseSpinLock(ZEXT48(&0x16e50) + lVar7);
    FUN_00000204((QWORD)uVar2);
    uVar3 = 0;
  }
  return uVar3;
}



undefined8 FUN_00026b10(undefined8 param_1,undefined8 param_2)

{
  undefined uVar1;
  char cVar2;
  uint uVar3;
  dword dVar4;
  QWORD in_r2;
  undefined8 uVar5;
  int iVar6;
  undefined4 *puVar7;
  QWORD uVar8;
  uint uVar9;
  word *pwVar10;
  QWORD lVar11;
  undefined *puVar13;
  QWORD uVar12;
  uint uVar14;
  uint uVar15;
  dword *pdVar16;
  QWORD uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  byte bVar21;
  undefined4 uVar22;
  undefined8 uVar23;
  QWORD lVar24;
  QWORD lVar25;
  qword back_chain;
  dword local_9f0;
  dword local_9ec;
  word local_9c0;
  word local_860;
  word local_85c;
  word local_858;
  byte local_84c;
  word local_84b;
  byte local_841;
  dword local_75c;
  word local_754;
  word local_55c;
  word local_558;
  word local_3fc;
  word local_37d;
  word local_50;
  word local_40;
  dword local_2c;
  
  uVar5 = __Save_R12_28_thru_31();
  uVar23 = 0;
  uVar3 = *(uint *)((int)in_r2 + 0x10000);
  uVar22 = 0;
  iVar6 = FUN_00025970(2);
  if (iVar6 == 0) {
    FUN_00000204((QWORD)uVar3);
    return 0xffffffffc8000086;
  }
  uVar5 = HvpPhysicalToReal(uVar5,0x804);
  memcpy(&local_860,uVar5,0x804);
  XeCryptAesKey(&local_9c0,ZEXT48(&0x10020) + in_r2);
  pwVar10 = &local_50;
  lVar11 = ZEXT48(&0x16bb2) + in_r2;
  lVar24 = 0x10;
  do {
    puVar13 = (undefined *)lVar11;
    lVar11 = lVar11 + 1;
    *(undefined *)pwVar10 = *puVar13;
    pwVar10 = (word *)((int)pwVar10 + 1);
    lVar24 = lVar24 + -1;
  } while (lVar24 != 0);
  lVar11 = in_r2;
  XeCryptAesCbc(&local_9c0,&local_84b,0x650,&local_84b,&local_50,0);
  XeCryptRotSumSha(&local_85c,0x4cb,0,0,&local_40,0x14);
  iVar6 = XeCryptBnQwBeSigVerify
                    (&local_37d,&local_40,ZEXT48(&0x10560) + lVar11,
                     ZEXT48(&0x108b8) + lVar11);
  if (iVar6 == 0) {
    lVar11 = ZEXT48(&0x16e28) + lVar11;
    pdVar16 = &local_9f0;
    lVar24 = 10;
    do {
      dVar4 = *pdVar16;
      pdVar16 = pdVar16 + 1;
      *(dword *)lVar11 = dVar4;
      lVar11 = lVar11 + 4;
      lVar24 = lVar24 + -1;
    } while (lVar24 != 0);
    uVar23 = 0xffffffffc8000082;
    goto LAB_00027274;
  }
  pwVar10 = &local_754;
  lVar24 = ZEXT48(&0x16cc2) + in_r2;
  lVar25 = 0x14;
  do {
    uVar1 = *(undefined *)pwVar10;
    pwVar10 = (word *)((int)pwVar10 + 1);
    *(undefined *)lVar24 = uVar1;
    lVar24 = lVar24 + 1;
    lVar25 = lVar25 + -1;
  } while (lVar25 != 0);
  pwVar10 = &local_858;
  lVar24 = ZEXT48(&0x16cdc) + in_r2;
  lVar25 = 0xc;
  do {
    uVar1 = *(undefined *)pwVar10;
    pwVar10 = (word *)((int)pwVar10 + 1);
    *(undefined *)lVar24 = uVar1;
    lVar24 = lVar24 + 1;
    lVar25 = lVar25 + -1;
  } while (lVar25 != 0);
  iVar6 = (int)in_r2;
  *(dword *)(&0x16cd8 + iVar6) = local_75c;
  *(undefined4 *)(&0x16ce8 + iVar6) = 0;
  (&0x16cec)[iVar6] = local_84c;
  memcpy(ZEXT48(&0x16bc2) + in_r2,&local_55c,0x100);
  XeCryptAesKey(&local_9c0,ZEXT48(&0x11008) + lVar11);
  XeCryptAesCbc(&local_9c0,&local_558,0xfc,ZEXT48(&0x16bc6) + in_r2,&local_50,0);
  bVar21 = (&0x16bc3)[iVar6];
  uVar8 = (QWORD)bVar21;
  uVar9 = (uint)bVar21;
  if ((((&0x16bc2)[iVar6] == '\x02') && (bVar21 != 0)) && (bVar21 < 0x16)) {
    uVar17 = 0;
    uVar20 = 0;
    uVar19 = 0;
    uVar20._3_1_ = (&0x16cf2)[iVar6] | 0xf8;
    uVar14 = 0;
    uVar12 = 0;
    (&0x16cf2)[iVar6] = (byte)uVar20;
    (&0x16cf3)[iVar6] = 0;
    uVar18 = (uint)(byte)(&0x16cf5)[iVar6] & 3;
    (&0x16cf5)[iVar6] = (char)uVar18;
    (&0x16cf4)[iVar6] = 0;
    if (bVar21 != 0) {
      do {
        cVar2 = (&0x16bc6)[uVar19 * 0xc + iVar6];
        uVar9 = (uint)uVar17;
        if (cVar2 != '\x01') {
          if ((cVar2 != '\x14') && (cVar2 != '\x15')) {
            if ((cVar2 == '$') || (cVar2 == '%')) {
              uVar9 = (uint)uVar12;
              if (0xdf < (uVar9 & 0xe0)) {
                lVar11 = ZEXT48(&0x16e28) + lVar11;
                pdVar16 = &local_9f0;
                lVar24 = 10;
                do {
                  dVar4 = *pdVar16;
                  pdVar16 = pdVar16 + 1;
                  *(dword *)lVar11 = dVar4;
                  lVar11 = lVar11 + 4;
                  lVar24 = lVar24 + -1;
                } while (lVar24 != 0);
                goto LAB_0002726c;
              }
              uVar9 = uVar9 & 0x1f | (uVar9 & 0xe0) + 0x20 & 0xff;
              uVar12 = (QWORD)uVar9;
              (&0x16cf4)[iVar6] = (char)uVar9;
            }
            else {
              if (cVar2 == -0x20) {
                (&0x16cf2)[iVar6] = (byte)(uVar19 << 3) | (byte)uVar20 & 7;
                *(undefined4 *)(&0x16bca + uVar19 * 0xc + iVar6) = 0;
                uVar12 = (QWORD)(byte)(&0x16cf4)[iVar6];
                uVar17 = (QWORD)(byte)(&0x16cf3)[iVar6];
                uVar20._3_1_ = (&0x16cf2)[iVar6];
                uVar8 = (QWORD)(byte)(&0x16bc3)[iVar6];
              }
            }
            goto LAB_00026e20;
          }
          if ((uVar9 & 7) < 7) {
            uVar9 = uVar9 & 0xf8 | uVar9 + 1 & 0xffffff07;
            goto LAB_00026e18;
          }
          lVar11 = ZEXT48(&0x16e28) + lVar11;
          pdVar16 = &local_9f0;
          lVar24 = 10;
          do {
            dVar4 = *pdVar16;
            pdVar16 = pdVar16 + 1;
            *(dword *)lVar11 = dVar4;
            lVar11 = lVar11 + 4;
            lVar24 = lVar24 + -1;
          } while (lVar24 != 0);
          goto LAB_0002726c;
        }
        if (0xf7 < (uVar9 & 0xf8)) {
          lVar11 = ZEXT48(&0x16e28) + lVar11;
          pdVar16 = &local_9f0;
          lVar24 = 10;
          do {
            dVar4 = *pdVar16;
            pdVar16 = pdVar16 + 1;
            *(dword *)lVar11 = dVar4;
            lVar11 = lVar11 + 4;
            lVar24 = lVar24 + -1;
          } while (lVar24 != 0);
          goto LAB_0002726c;
        }
        uVar9 = uVar9 & 7 | (uVar9 & 0xf8) + 8;
LAB_00026e18:
        uVar17 = (QWORD)(uVar9 & 0xff);
        (&0x16cf3)[iVar6] = (char)(uVar9 & 0xff);
LAB_00026e20:
        uVar20 = (uint)uVar17;
        uVar14 = (uint)uVar12;
        uVar9 = (uint)uVar8;
        uVar19 = uVar19 + 1 & 0xff;
      } while (uVar19 < uVar9);
      uVar18 = (uint)(byte)(&0x16cf5)[iVar6];
    }
    if (((byte)uVar20 & 0xf8) == 0xf8) {
      lVar11 = ZEXT48(&0x16e28) + lVar11;
      pdVar16 = &local_9f0;
      lVar24 = 10;
      do {
        dVar4 = *pdVar16;
        pdVar16 = pdVar16 + 1;
        *(dword *)lVar11 = dVar4;
        lVar11 = lVar11 + 4;
        lVar24 = lVar24 + -1;
      } while (lVar24 != 0);
    }
    else {
      cVar2 = (&0x16e11)[(int)lVar11];
      (&0x16cf0)[iVar6] = (&0x16cf0)[iVar6] & 0x7f;
      (&0x16cf1)[iVar6] = (&0x16cf1)[iVar6] & 7;
      (&0x16cf6)[iVar6] = (&0x16cf6)[iVar6] & 0xc0;
      if (cVar2 != '\0') {
        if ((uVar14 >> 5) + (uVar20 & 7) < 4) {
          lVar11 = ZEXT48(&0x16e28) + lVar11;
          pdVar16 = &local_9f0;
          lVar24 = 10;
          do {
            dVar4 = *pdVar16;
            pdVar16 = pdVar16 + 1;
            *(dword *)lVar11 = dVar4;
            lVar11 = lVar11 + 4;
            lVar24 = lVar24 + -1;
          } while (lVar24 != 0);
          goto LAB_0002726c;
        }
        uVar18 = (uVar20 & 7) << 5 | uVar14 >> 3 & 0x1c;
        (&0x16cf5)[iVar6] = (char)uVar18;
        (&0x16cf6)[iVar6] = 0;
        (&0x16cf4)[iVar6] = (byte)(uVar20 >> 3) | (byte)uVar14 & 0xe0;
        (&0x16cf7)[iVar6] =
             (&0x16cf7)[iVar6] & 0xf |
             ((byte)(uVar18 >> 1) & 0x70) + ((byte)(uVar18 << 2) & 0x70);
LAB_000271a8:
        uVar8 = 0;
        if (uVar9 != 0) {
          do {
            uVar12 = (QWORD)((int)uVar8 + 1U & 0xff);
            (&0x16cf8)[(int)uVar8 + iVar6] = (char)uVar8;
            uVar8 = uVar12;
          } while (uVar12 < (byte)(&0x16bc3)[iVar6]);
        }
        lVar11 = ZEXT48(&0x10010) + lVar11;
        pwVar10 = &local_3fc;
        lVar24 = 0x10;
        do {
          uVar1 = *(undefined *)pwVar10;
          pwVar10 = (word *)((int)pwVar10 + 1);
          *(undefined *)lVar11 = uVar1;
          lVar11 = lVar11 + 1;
          lVar24 = lVar24 + -1;
        } while (lVar24 != 0);
        if (local_841 == 6) {
          uVar22 = 6;
        }
        puVar7 = (undefined4 *)HvpPhysicalToReal(param_2,4);
        *puVar7 = uVar22;
        goto LAB_00027274;
      }
      uVar19 = uVar14 >> 5;
      uVar15 = uVar20 & 7;
      if (uVar19 + uVar15 == 4) {
        uVar18 = uVar20 << 5 | uVar14 >> 3 & 0x1c | uVar18 & 3;
      }
      else {
        if (1 < uVar19) {
          uVar19 = 2;
        }
        if ((int)(4 - uVar19) <= (int)uVar15) {
          uVar15 = 4 - uVar19;
        }
        uVar18 = uVar15 << 5 | uVar19 << 2 | uVar18 & 3;
      }
      uVar18 = uVar18 & 0xff;
      bVar21 = (byte)uVar18;
      (&0x16cf5)[iVar6] = bVar21;
      if ((uVar18 >> 2 & 7) + (uVar18 >> 5) == 4) {
        uVar20 = uVar20 >> 3;
        if (2 < uVar20) {
          uVar20 = 3;
        }
        uVar20._3_1_ = (byte)uVar20 | (byte)uVar14 & 0xe0;
        (&0x16cf4)[iVar6] = (byte)uVar20;
        if (uVar20 != 0) {
          uVar20 = uVar18 >> 2 & 7;
          if (uVar20 == 2) {
            bVar21 = bVar21 & 0xfc | 1;
LAB_00027188:
            (&0x16cf5)[iVar6] = bVar21;
          }
          else {
            if ((uVar20 == 3) || (uVar20 == 4)) {
              bVar21 = bVar21 & 0xfc | 2;
              goto LAB_00027188;
            }
          }
          (&0x16cf7)[iVar6] = (&0x16cf7)[iVar6] & 0xf | 0x10;
          (&0x16cf6)[iVar6] = ((byte)uVar20 - 1) * '@';
          goto LAB_000271a8;
        }
        lVar11 = ZEXT48(&0x16e28) + lVar11;
        pdVar16 = &local_9f0;
        lVar24 = 10;
        do {
          dVar4 = *pdVar16;
          pdVar16 = pdVar16 + 1;
          *(dword *)lVar11 = dVar4;
          lVar11 = lVar11 + 4;
          lVar24 = lVar24 + -1;
        } while (lVar24 != 0);
      }
      else {
        lVar11 = ZEXT48(&0x16e28) + lVar11;
        pdVar16 = &local_9f0;
        lVar24 = 10;
        do {
          dVar4 = *pdVar16;
          pdVar16 = pdVar16 + 1;
          *(dword *)lVar11 = dVar4;
          lVar11 = lVar11 + 4;
          lVar24 = lVar24 + -1;
        } while (lVar24 != 0);
      }
    }
  }
  else {
    lVar11 = ZEXT48(&0x16e28) + lVar11;
    pdVar16 = &local_9f0;
    lVar24 = 10;
    do {
      dVar4 = *pdVar16;
      pdVar16 = pdVar16 + 1;
      *(dword *)lVar11 = dVar4;
      lVar11 = lVar11 + 4;
      lVar24 = lVar24 + -1;
    } while (lVar24 != 0);
  }
LAB_0002726c:
  uVar23 = 0xffffffffc8000083;
LAB_00027274:
  FUN_00025a18(uVar23,3);
  FUN_00000204((QWORD)uVar3);
  return uVar23;
}



undefined8 FUN_00027298(undefined8 param_1,QWORD param_2,undefined8 param_3,QWORD param_4)

{
  byte bVar1;
  uint uVar2;
  dword dVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  QWORD in_r2;
  undefined8 uVar10;
  int iVar11;
  byte *pbVar12;
  int *piVar13;
  short sVar14;
  word *pwVar15;
  short sVar16;
  byte *pbVar19;
  undefined *puVar20;
  QWORD lVar17;
  QWORD lVar18;
  undefined uVar22;
  dword *pdVar21;
  int iVar23;
  int iVar24;
  undefined8 uVar25;
  QWORD lVar26;
  qword back_chain;
  dword local_230;
  dword local_22c;
  dword local_228;
  dword local_224;
  word local_220;
  word local_1fe;
  dword local_1f4;
  word local_1d0;
  word local_70;
  dword local_60;
  
  uVar10 = __Save_R12_22_thru_31();
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  uVar25 = 0;
  iVar24 = 0;
  iVar11 = FUN_00025970(4);
  if (iVar11 == 0) {
    FUN_00000204((QWORD)uVar2);
    return 0xffffffffc8000086;
  }
  iVar11 = (int)in_r2;
  uVar8 = (uint)((byte)(&0x16cf0)[iVar11] >> 2) & 0x1f;
  lVar18 = in_r2;
  pbVar12 = (byte *)HvpPhysicalToReal(uVar10,0x22);
  iVar23 = (int)param_2;
  if (((*pbVar12 & 0x3f) != 0x3e) || (pbVar12[1] != 0x20)) {
    lVar17 = ZEXT48(&0x16e28) + lVar18;
    pdVar21 = &local_230;
    lVar26 = 10;
    do {
      dVar3 = *pdVar21;
      pdVar21 = pdVar21 + 1;
      *(dword *)lVar17 = dVar3;
      lVar17 = lVar17 + 4;
      lVar26 = lVar26 + -1;
    } while (lVar26 != 0);
    uVar25 = 0xffffffffc8000080;
    goto LAB_000276b4;
  }
  if (((&0x16cf0)[iVar11] & 0x80) != 0) {
    iVar24 = 1;
    if ((iVar23 < 0) || (((&0x16cf6)[iVar11] & 0xf) < (byte)(&0x16cf7)[iVar11] >> 4)) {
      uVar22 = 0;
      uVar25 = 0xffffffffc8000084;
    }
    else {
      uVar22 = 1;
    }
    (&0x16e10)[(int)lVar18] = uVar22;
    goto LAB_000276b4;
  }
  if (iVar23 < 0) {
    if ((param_2 & 0xffffffff) != 0xc000009c) {
      uVar25 = 0xffffffffc8000084;
      goto LAB_000276b4;
    }
  }
  else {
    if ((param_2 & 0xffffffff) != 0xc000009c) {
      iVar4 = (uint)((byte)(&0x16cf2)[iVar11] >> 3) * 0xc;
      iVar24 = 0;
      iVar5 = (int)((QWORD)uVar8 * 0xc);
      *(uint *)(&0x16bca + iVar11 + iVar4) =
           (uint)(byte)(&0x16bc7)[iVar5 + iVar11] << 0x18 |
           *(uint *)(&0x16bca + iVar11 + iVar4) >> 8;
      XeCryptAesKey(&local_1d0,ZEXT48(&0x10020) + lVar18);
      pbVar19 = pbVar12 + 0x12;
      pwVar15 = &local_70;
      lVar17 = 0x10;
      do {
        bVar1 = *pbVar19;
        pbVar19 = pbVar19 + 1;
        *(byte *)pwVar15 = bVar1;
        pwVar15 = (word *)((int)pwVar15 + 1);
        lVar17 = lVar17 + -1;
      } while (lVar17 != 0);
      XeCryptAesCbc(&local_1d0,pbVar12 + 2,0x10,&local_1fe,&local_70,0);
      lVar17 = (QWORD)uVar8 * 0xc + ZEXT48(&0x16bc6) + in_r2;
      bVar1 = *(byte *)lVar17;
      if ((bVar1 & 0x20) == 0) {
        if (*(dword *)(&0x16bce + iVar5 + iVar11) != local_1f4) {
          pdVar21 = &local_224;
          lVar26 = 0xc;
          do {
            puVar20 = (undefined *)lVar17;
            lVar17 = lVar17 + 1;
            *(undefined *)pdVar21 = *puVar20;
            pdVar21 = (dword *)((int)pdVar21 + 1);
            lVar26 = lVar26 + -1;
          } while (lVar26 != 0);
          pdVar21 = &local_230;
          lVar17 = ZEXT48(&0x16e28) + lVar18;
          lVar26 = 10;
          do {
            dVar3 = *pdVar21;
            pdVar21 = pdVar21 + 1;
            *(dword *)lVar17 = dVar3;
            lVar17 = lVar17 + 4;
            lVar26 = lVar26 + -1;
          } while (lVar26 != 0);
          goto LAB_00027640;
        }
      }
      else {
        uVar9 = (local_1f4 >> 0x10 & 0xff) << 8;
        sVar14 = (short)*(uint *)(&0x16bce + iVar5 + iVar11);
        sVar16 = sVar14 - (ushort)(byte)(&0x16bc8)[iVar5 + iVar11];
        sVar14 = sVar14 + (ushort)(byte)(&0x16bc8)[iVar5 + iVar11];
        uVar7 = uVar9 | local_1f4 >> 0x18;
        if (sVar16 < 0) {
          if (uVar7 < 0xb5) {
            sVar16 = 0;
          }
          else {
            sVar16 = sVar16 + 0x168;
            sVar14 = 0x168;
          }
        }
        if (((((*(uint *)(&0x16bce + iVar5 + iVar11) ^
               (local_1f4 << 0x18 | (local_1f4 >> 8 & 0xff) << 0x10 | uVar9 | local_1f4 >> 0x18)) &
              0xffff0000) != 0) || ((int)uVar7 < (int)sVar16)) || ((int)sVar14 < (int)uVar7)) {
          pdVar21 = &local_224;
          lVar26 = 0xc;
          do {
            puVar20 = (undefined *)lVar17;
            lVar17 = lVar17 + 1;
            *(undefined *)pdVar21 = *puVar20;
            pdVar21 = (dword *)((int)pdVar21 + 1);
            lVar26 = lVar26 + -1;
          } while (lVar26 != 0);
          pdVar21 = &local_230;
          lVar17 = ZEXT48(&0x16e28) + lVar18;
          lVar26 = 10;
          do {
            dVar3 = *pdVar21;
            pdVar21 = pdVar21 + 1;
            *(dword *)lVar17 = dVar3;
            lVar17 = lVar17 + 4;
            lVar26 = lVar26 + -1;
          } while (lVar26 != 0);
LAB_00027640:
          uVar25 = 0xffffffffc8000084;
        }
      }
      if ((bVar1 != 1) && (2499999 < param_4)) {
        (&0x16cf6)[iVar11] = (&0x16cf6)[iVar11] & 0xf0 | (&0x16cf6)[iVar11] + 1 & 0xf
        ;
      }
      goto LAB_000276b4;
    }
  }
  bVar1 = (&0x16cf6)[iVar11];
  uVar25 = 0xffffffffc8000084;
  if ((&0x16bc6 + iVar11)[uVar8 * 0xc] == '\x01') {
    if ((bVar1 & 0xc0) != 0) {
      uVar25 = 0;
      (&0x16cf6)[iVar11] = ((bVar1 >> 6) - 1) * '@' | bVar1 & 0x3f;
    }
  }
  else {
    bVar6 = (bVar1 & 0xf0) + 0x10 & 0x30;
    (&0x16cf6)[iVar11] = bVar6 | bVar1 & 0xcf;
    if (bVar6 < 0x21) {
      if (((&0x16bc6 + iVar11)[uVar8 * 0xc] & 0x20) == 0) {
        uVar25 = 0;
      }
      else {
        bVar1 = (&0x16cf5)[iVar11];
        if ((bVar1 & 3) != 0) {
          uVar25 = 0;
          (&0x16cf5)[iVar11] = bVar1 & 0xfc | bVar1 - 1 & 3;
        }
      }
    }
  }
LAB_000276b4:
  if ((iVar23 < 0) && ((int)uVar25 != 0)) {
    lVar17 = (QWORD)uVar8 * 0xc + ZEXT48(&0x16bc6) + in_r2;
    pwVar15 = &local_220;
    lVar26 = 0xc;
    do {
      puVar20 = (undefined *)lVar17;
      lVar17 = lVar17 + 1;
      *(undefined *)pwVar15 = *puVar20;
      pwVar15 = (word *)((int)pwVar15 + 1);
      lVar26 = lVar26 + -1;
    } while (lVar26 != 0);
    pdVar21 = &local_230;
    lVar18 = ZEXT48(&0x16e28) + lVar18;
    lVar17 = 10;
    do {
      dVar3 = *pdVar21;
      pdVar21 = pdVar21 + 1;
      *(dword *)lVar18 = dVar3;
      lVar18 = lVar18 + 4;
      lVar17 = lVar17 + -1;
    } while (lVar17 != 0);
  }
  piVar13 = (int *)HvpPhysicalToReal(param_3,4);
  *piVar13 = iVar24;
  FUN_00025a18(uVar25,(QWORD)(-(uint)(iVar24 != 0) & 2) + 3);
  FUN_00000204((QWORD)uVar2);
  return uVar25;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00027778(void)

{
  char cVar1;
  uint uVar2;
  int in_r2;
  undefined8 uVar3;
  uint uVar4;
  byte bVar5;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  if (((((&0x16cf4)[in_r2] & 0x1f) == 0) && (((&0x16cf5)[in_r2] & 0xe0) == 0)) &&
     (((&0x16cf5)[in_r2] & 0x1c) == 0)) {
    uVar3 = 0;
    (&0x16cf0)[in_r2] =
         (byte)(&0x16cf2)[in_r2] >> 1 & 0xfc | (&0x16cf0)[in_r2] & 0x83 | 0x80;
    (&0x16cf1)[in_r2] = (&0x16bc3)[in_r2] << 3 | (&0x16cf1)[in_r2] & 7;
  }
  else {
    if (((byte)(&0x16cf1)[in_r2] >> 3 != (&0x16bc3)[in_r2]) &&
       ((byte)(&0x16cf1)[in_r2] >> 3 < (byte)(&0x16bc3)[in_r2])) {
      do {
        uVar4 = FUN_00025210();
        uVar2 = ((uint)(byte)(&0x16cf1)[in_r2] & 0xfffffff8) + 8 & 0xff;
        (&0x16cf0)[in_r2] = (byte)((uVar4 & 0x1f) << 2) | (&0x16cf0)[in_r2] & 0x83;
        (&0x16cf1)[in_r2] = (&0x16cf1)[in_r2] & 7 | (byte)uVar2;
        cVar1 = (&0x16bc6)[(uVar4 & 0x1f) * 0xc + in_r2];
        if ((cVar1 == '\x01') && (bVar5 = (&0x16cf4)[in_r2], (bVar5 & 0x1f) != 0)) {
          (&0x16cf4)[in_r2] = bVar5 & 0xe0 | bVar5 - 1 & 0x1f;
          return 0;
        }
        bVar5 = (&0x16cf5)[in_r2];
        if (((cVar1 == '\x14') && ((bVar5 & 0xe0) != 0)) ||
           ((cVar1 == '\x15' && ((bVar5 & 0xe0) != 0)))) {
          bVar5 = ((bVar5 >> 5) - 1) * ' ' | bVar5 & 0x1f;
LAB_00027908:
          (&0x16cf5)[in_r2] = bVar5;
          return 0;
        }
        if (((cVar1 == '$') && ((bVar5 & 0x1c) != 0)) || ((cVar1 == '%' && ((bVar5 & 0x1c) != 0))))
        {
          bVar5 = ((bVar5 >> 2) - 1) * '\x04' & 0x1c | bVar5 & 0xe3;
          goto LAB_00027908;
        }
      } while ((QWORD)(uVar2 >> 3) < (QWORD)(byte)(&0x16bc3)[in_r2]);
    }
    uVar3 = 0xffffffffc8000084;
  }
  return uVar3;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00027928(undefined8 param_1)

{
  dword dVar1;
  int iVar2;
  QWORD in_r2;
  int iVar3;
  undefined4 *puVar4;
  dword *pdVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  QWORD lVar8;
  qword back_chain;
  dword local_40;
  dword local_3c;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar7 = 0;
  iVar3 = FUN_00025970(5);
  if (iVar3 == 0) {
    return 0xffffffffc8000086;
  }
  puVar4 = (undefined4 *)HvpPhysicalToReal(param_1,4);
  iVar3 = (int)in_r2;
  if ((&0x16e10)[iVar3] == '\0') {
    in_r2 = ZEXT48(&0x16e28) + in_r2;
    pdVar5 = &local_40;
    lVar8 = 10;
    do {
      dVar1 = *pdVar5;
      pdVar5 = pdVar5 + 1;
      *(dword *)in_r2 = dVar1;
      in_r2 = in_r2 + 4;
      lVar8 = lVar8 + -1;
    } while (lVar8 != 0);
    uVar7 = 0xffffffffc8000084;
  }
  else {
    iVar2 = *(int *)(&0x16ce8 + iVar3);
    if (iVar2 == 0) {
      uVar6 = *(undefined4 *)(&0x16cd8 + iVar3);
    }
    else {
      if (iVar2 == 1) {
        uVar6 = *(undefined4 *)(&0x16e00 + iVar3);
      }
      else {
        if (iVar2 != 2) {
          pdVar5 = &local_40;
          in_r2 = ZEXT48(&0x16e28) + in_r2;
          lVar8 = 10;
          do {
            dVar1 = *pdVar5;
            pdVar5 = pdVar5 + 1;
            *(dword *)in_r2 = dVar1;
            in_r2 = in_r2 + 4;
            lVar8 = lVar8 + -1;
          } while (lVar8 != 0);
          uVar7 = 0xffffffffc8000085;
          *(undefined4 *)(&0x16ce8 + iVar3) = 0;
          goto LAB_00027a44;
        }
        uVar6 = *(undefined4 *)(&0x16e04 + iVar3);
      }
    }
    *puVar4 = uVar6;
  }
LAB_00027a44:
  FUN_00025a18(uVar7,6);
  return uVar7;
}



// WARNING: Removing unreachable block (ram,0x00027c78)
// WARNING: Removing unreachable block (ram,0x00027ca4)

undefined8 FUN_00027a70(undefined8 param_1,int param_2,undefined8 param_3)

{
  int iVar1;
  dword dVar2;
  QWORD in_r2;
  int iVar3;
  undefined8 uVar4;
  int iVar5;
  undefined4 *puVar6;
  dword *pdVar7;
  QWORD lVar8;
  qword back_chain;
  dword local_70;
  dword local_60;
  dword local_5c;
  dword local_58;
  dword local_54;
  dword local_50;
  dword local_4c;
  dword local_48;
  dword local_44;
  dword local_40;
  dword local_3c;
  
  uVar4 = __Save_R12_26_thru_31();
  iVar5 = FUN_00025970(6);
  if (iVar5 == 0) {
    return 0xffffffffc8000086;
  }
  uVar4 = HvpPhysicalToReal(uVar4,0x8000);
  iVar3 = (int)in_r2;
  iVar5 = iVar3;
  if (param_2 < 0) {
    pdVar7 = &local_60;
    in_r2 = ZEXT48(&0x16e28) + in_r2;
    lVar8 = 10;
    do {
      dVar2 = *pdVar7;
      pdVar7 = pdVar7 + 1;
      *(dword *)in_r2 = dVar2;
      in_r2 = in_r2 + 4;
      lVar8 = lVar8 + -1;
    } while (lVar8 != 0);
    uVar4 = 0xffffffffc8000085;
  }
  else {
    iVar1 = *(int *)(&0x16ce8 + iVar3);
    if (iVar1 == 0) {
      uVar4 = FUN_00025298();
    }
    else {
      if (iVar1 == 1) {
        uVar4 = FUN_00025530();
      }
      else {
        if (iVar1 == 2) {
          uVar4 = FUN_00025600(uVar4,&local_70);
        }
        else {
          uVar4 = 0xffffffffc8000085;
          *(undefined4 *)(&0x16ce8 + iVar3) = 0;
        }
      }
    }
    if ((int)uVar4 == 0) goto LAB_00027cb8;
    pdVar7 = &local_60;
    in_r2 = ZEXT48(&0x16e28) + in_r2;
    lVar8 = 10;
    do {
      dVar2 = *pdVar7;
      pdVar7 = pdVar7 + 1;
      *(dword *)in_r2 = dVar2;
      in_r2 = in_r2 + 4;
      lVar8 = lVar8 + -1;
    } while (lVar8 != 0);
  }
  if ((int)uVar4 != 0) {
    *(undefined4 *)(&0x16ce8 + iVar3) = 0;
    (&0x1000c)[iVar5] = 0;
  }
LAB_00027cb8:
  puVar6 = (undefined4 *)HvpPhysicalToReal(param_3,4);
  *puVar6 = 0;
  FUN_00025a18(uVar4,5);
  return uVar4;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00027cf0(undefined8 param_1)

{
  uint uVar1;
  dword dVar2;
  QWORD in_r2;
  int iVar5;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined4 *puVar6;
  QWORD lVar7;
  undefined *puVar8;
  word *pwVar9;
  dword *pdVar10;
  QWORD lVar11;
  qword back_chain;
  word local_1f0;
  undefined uStack494;
  byte local_1ed;
  byte local_1eb;
  byte local_1ea;
  byte local_1e9;
  dword local_1e8;
  word local_1de;
  dword local_1c0;
  dword local_1bc;
  word local_190;
  word local_30;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  iVar5 = FUN_00025970(3);
  if (iVar5 == 0) {
    FUN_00000204((QWORD)uVar1);
    uVar3 = 0xffffffffc8000086;
  }
  else {
    uVar3 = FUN_00027778();
    if ((int)uVar3 == 0) {
      puVar6 = (undefined4 *)&local_1f0;
      lVar7 = 8;
      do {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
        lVar7 = lVar7 + -1;
      } while (lVar7 != 0);
      *(undefined2 *)puVar6 = 0;
      pwVar9 = &local_1de;
      lVar7 = ZEXT48(&0x16bb2) + in_r2;
      lVar11 = 0x10;
      do {
        puVar8 = (undefined *)lVar7;
        lVar7 = lVar7 + 1;
        *(undefined *)pwVar9 = *puVar8;
        pwVar9 = (word *)((int)pwVar9 + 1);
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
      pwVar9 = &local_30;
      lVar7 = ZEXT48(&0x16bb2) + in_r2;
      lVar11 = 0x10;
      do {
        puVar8 = (undefined *)lVar7;
        lVar7 = lVar7 + 1;
        *(undefined *)pwVar9 = *puVar8;
        pwVar9 = (word *)((int)pwVar9 + 1);
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
      XeCryptAesKey(&local_190,ZEXT48(&0x10020) + in_r2);
      XeCryptAesCbc(&local_190,&uStack494,0x10,&uStack494,&local_30,1);
      uVar4 = HvpPhysicalToReal(param_1,0x22);
      memcpy(uVar4,&local_1f0,0x22);
    }
    else {
      lVar7 = ZEXT48(&0x16e28) + in_r2;
      pdVar10 = &local_1c0;
      lVar11 = 10;
      do {
        dVar2 = *pdVar10;
        pdVar10 = pdVar10 + 1;
        *(dword *)lVar7 = dVar2;
        lVar7 = lVar7 + 4;
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
    }
    FUN_00025a18(uVar3,4);
    FUN_00000204((QWORD)uVar1);
  }
  return uVar3;
}



void FUN_00027ee0(void)

{
  int in_r2;
  undefined8 uVar1;
  qword back_chain;
  qword local_8;
  
  uVar1 = FUN_000002c8();
  *(undefined8 *)(&0x16b80 + in_r2) = uVar1;
  return;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Could not reconcile some variable overlaps

void FUN_00027f08(void)

{
  int iVar1;
  int in_r2;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined *puVar4;
  qword back_chain;
  qword local_20;
  qword local_10;
  qword local_8;
  
  uVar2 = 0xffff;
  if (*(QWORD *)(&0x16af8 + in_r2) != 0) {
    uVar2 = *(undefined2 *)((int)*(QWORD *)(&0x16af8 + in_r2) + 0x156);
  }
  uVar3 = 0xffff;
  if (*(QWORD *)(&0x16ae8 + in_r2) != 0) {
    uVar3 = *(undefined2 *)((int)*(QWORD *)(&0x16ae8 + in_r2) + 0x156);
  }
  iVar1 = (int)*(undefined8 *)(&0x16628 + in_r2);
  if (*(char *)(iVar1 + 0x18) == '\0') {
    local_20._4_2_ = 0xffff;
    local_20._6_2_ = 0xffff;
  }
  else {
    local_20._4_2_ = *(undefined2 *)(iVar1 + 0x1c);
    local_20._6_2_ = *(undefined2 *)(iVar1 + 0x1e);
  }
  puVar4 = &0x162c4 + in_r2;
  HvpAquireSpinLock(puVar4);
  *(undefined8 *)((int)*(undefined8 *)(&0x162d0 + in_r2) + 0x648) =
       CONCAT62(CONCAT42(CONCAT22(uVar2,uVar3),local_20._4_2_),local_20._6_2_);
  HvpReleaseSpinLock(puVar4);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00027fc8(int param_1)

{
  int in_r2;
  QWORD lVar1;
  QWORD lVar2;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if ((param_1 != 0) && (lVar2 = *(QWORD *)(&0x16ae8 + in_r2), lVar2 != 0)) {
    if (*(uint *)(&0x16af0 + in_r2) != 0) {
      lVar1 = (QWORD)param_1 + lVar2;
      if (param_1 < 1) {
        memcpy(lVar1);
      }
      else {
        FUN_0000adc0(lVar1,lVar2,(QWORD)*(uint *)(&0x16af0 + in_r2));
      }
      *(QWORD *)(&0x16ae8 + in_r2) =
           (QWORD)param_1 + *(QWORD *)(&0x16ae8 + in_r2);
    }
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00028048(int *param_1,undefined *param_2)

{
  undefined uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int in_r2;
  QWORD uVar5;
  QWORD lVar6;
  word *pwVar7;
  undefined *puVar8;
  int *piVar9;
  QWORD lVar10;
  QWORD lVar11;
  qword back_chain;
  qword local_50;
  dword local_44;
  word local_40;
  word local_3b;
  word local_30;
  dword local_1c;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar2 = *(uint *)(in_r2 + 0x10000);
  iVar3 = *param_1;
  lVar6 = *(QWORD *)(&0x163c0 + in_r2);
  uVar4 = ~(uint)*(ushort *)((int)param_1 + 6) >> 0xf & 1;
  if (iVar3 == 0x44414550) {
    puVar8 = &0x00054;
    piVar9 = (int *)(&0x108b8 + in_r2);
    lVar10 = 0x10;
    do {
      uVar1 = *puVar8;
      puVar8 = puVar8 + 1;
      *param_2 = uVar1;
      param_2 = param_2 + 1;
      lVar10 = lVar10 + -1;
    } while (lVar10 != 0);
  }
  else {
    if (iVar3 == 0x4441454c) {
      if (uVar4 == 0) {
        puVar8 = &0x10be8;
      }
      else {
        puVar8 = &0x110f8;
      }
      piVar9 = (int *)(puVar8 + in_r2);
      lVar10 = lVar6 + 0xf0;
      lVar11 = 0x10;
      do {
        puVar8 = (undefined *)lVar10;
        lVar10 = lVar10 + 1;
        *param_2 = *puVar8;
        param_2 = param_2 + 1;
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
    }
    else {
      if (iVar3 != 0x4441454d) goto LAB_00028250;
      if (uVar4 == 0) {
        puVar8 = &0x10ad8;
      }
      else {
        puVar8 = &0x11318;
      }
      piVar9 = (int *)(puVar8 + in_r2);
      lVar10 = 0x10;
      do {
        *param_2 = 0;
        param_2 = param_2 + 1;
        lVar10 = lVar10 + -1;
      } while (lVar10 != 0);
    }
  }
  if ((*piVar9 == 0x20) || (*piVar9 == 0x40)) {
    if ((*(ushort *)((int)param_1 + 6) & 2) != 0) {
      lVar10 = lVar6 + 0x9ca;
      pwVar7 = &local_40;
      lVar11 = 5;
      do {
        puVar8 = (undefined *)lVar10;
        lVar10 = lVar10 + 1;
        *(undefined *)pwVar7 = *puVar8;
        pwVar7 = (word *)((int)pwVar7 + 1);
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
      lVar6 = lVar6 + 0x9cf;
      pwVar7 = &local_3b;
      lVar10 = 0xb;
      do {
        puVar8 = (undefined *)lVar6;
        lVar6 = lVar6 + 1;
        *(undefined *)pwVar7 = *puVar8;
        pwVar7 = (word *)((int)pwVar7 + 1);
        lVar10 = lVar10 + -1;
      } while (lVar10 != 0);
    }
    XeCryptHmacSha(&local_40,0x10,param_1,0x20,0,0,0,0);
    uVar5 = FUN_000038d8(&local_30,param_1 + 8,piVar9);
    if ((uVar5 & 0xffffffff) == 0) {
      FUN_00000204((QWORD)uVar2);
      return 0xffffffffc8000093;
    }
    FUN_00000204((QWORD)uVar2);
    return 0;
  }
LAB_00028250:
  FUN_00000204((QWORD)uVar2);
  return 0xffffffffc8000092;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00028278(QWORD param_1,undefined8 param_2)

{
  uint uVar1;
  int in_r2;
  int iVar3;
  undefined8 uVar2;
  qword back_chain;
  qword local_40;
  dword local_34;
  word local_30;
  dword local_20;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)(in_r2 + 0x10000);
  XeCryptHmacSha(param_2,0x10,param_1 + 0x120,0x10,param_1 + 0x130,0x10,0,0);
  iVar3 = XeCryptMemDiff(&local_30,param_1 + 0x140,0x10);
  if (iVar3 == 0) {
    FUN_00000204((QWORD)uVar1);
    uVar2 = 0;
  }
  else {
    FUN_00000204((QWORD)uVar1);
    uVar2 = 0xffffffffc8000091;
  }
  return uVar2;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00028318(int param_1)

{
  uint uVar1;
  int in_r2;
  int iVar3;
  undefined8 uVar2;
  qword back_chain;
  word local_30;
  dword local_1c;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)(in_r2 + 0x10000);
  XeCryptSha(param_1 + 0x150,(QWORD)*(ushort *)(param_1 + 4) - 0x150,0,0,0,0,&local_30,0x14);
  iVar3 = XeCryptMemDiff(&local_30,param_1 + 0xc,0x14);
  if (iVar3 == 0) {
    FUN_00000204((QWORD)uVar1);
    uVar2 = 0;
  }
  else {
    FUN_00000204((QWORD)uVar1);
    uVar2 = 0xffffffffc8000091;
  }
  return uVar2;
}



undefined8 FUN_000283b0(undefined8 param_1,undefined8 param_2,QWORD param_3)

{
  ushort uVar1;
  uint uVar2;
  int in_r2;
  QWORD lVar3;
  undefined8 uVar4;
  qword back_chain;
  word local_1c0;
  word local_60;
  dword local_50;
  
  lVar3 = __Save_R12_25_thru_31();
  uVar2 = *(uint *)(in_r2 + 0x10000);
  if ((*(ushort *)(lVar3._4_4_ + 0x120) & 1) != 0) {
    param_2 = 0x20;
  }
  uVar1 = *(ushort *)(lVar3._4_4_ + 4);
  if (((param_3 & 0xffffffff) != 0) &&
     ((uVar4 = FUN_00028278(lVar3._4_4_,param_2), (int)uVar4 != 0 ||
      (uVar4 = FUN_00028318(lVar3._4_4_), (int)uVar4 != 0)))) {
    FUN_00000204((QWORD)uVar2);
    return uVar4;
  }
  XeCryptAesKey(&local_1c0,param_2);
  XeCryptAesCbc(&local_1c0,lVar3._4_4_ + 0x130,0x10,lVar3 + 0x130,&local_60,param_3);
  XeCryptAesCbc(&local_1c0,lVar3._4_4_ + 0x140,0x10,lVar3 + 0x140,&local_60,param_3);
  XeCryptAesCbc(&local_1c0,lVar3._4_4_ + 0x150,(QWORD)uVar1 - 0x150,lVar3 + 0x150,&local_60,
                param_3);
  if ((param_3 & 0xffffffff) == 0) {
    uVar4 = FUN_00028278(lVar3._4_4_,param_2);
    if ((int)uVar4 != 0) {
      FUN_00000204((QWORD)uVar2);
      return uVar4;
    }
    uVar4 = FUN_00028318(lVar3._4_4_);
    if ((int)uVar4 != 0) {
      FUN_00000204((QWORD)uVar2);
      return uVar4;
    }
  }
  FUN_00000204((QWORD)uVar2);
  return 0;
}



undefined8 FUN_00028518(undefined8 param_1,QWORD param_2)

{
  uint uVar1;
  int in_r2;
  int iVar3;
  undefined8 uVar2;
  qword back_chain;
  word local_40;
  dword local_30;
  
  iVar3 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  if (0x14f < (param_2 & 0xffffffff)) {
    uVar2 = FUN_00028048(iVar3,&local_40);
    if ((int)uVar2 != 0) {
      FUN_00000204((QWORD)uVar1);
      return uVar2;
    }
    if (*(short *)(iVar3 + 8) != 1) {
      FUN_00000204((QWORD)uVar1);
      return 0xffffffffc8000094;
    }
    if ((QWORD)*(ushort *)(iVar3 + 4) <= (param_2 & 0xffffffff)) {
      uVar2 = FUN_000283b0(iVar3,&local_40,0);
      FUN_00000204((QWORD)uVar1);
      return uVar2;
    }
  }
  FUN_00000204((QWORD)uVar1);
  return 0xffffffffc8000091;
}



undefined8 FUN_000285d0(int param_1,QWORD param_2)

{
  int in_r2;
  undefined8 uVar1;
  qword back_chain;
  qword local_8;
  
  if ((*(QWORD *)(param_1 + 0x130) == param_2) &&
     (*(char *)(param_1 + 0x13f) == (&0x16620)[in_r2])) {
    FUN_00003830(0x200000,0);
    uVar1 = 0;
  }
  else {
    uVar1 = 0xffffffffc8000091;
  }
  return uVar1;
}



void FUN_00028648(undefined8 param_1,undefined8 param_2)

{
  int in_r2;
  int iVar2;
  QWORD uVar1;
  ushort *puVar3;
  undefined8 *puVar4;
  qword back_chain;
  qword local_40;
  dword local_34;
  
  iVar2 = __Save_R12_28_thru_31();
  puVar3 = (ushort *)(iVar2 + 0x120);
  puVar4 = (undefined8 *)(iVar2 + 0x130);
  XeCryptRandom(puVar3,0x10);
  *puVar3 = *puVar3 | 1;
  XeCryptRandom(puVar4,0x10);
  *puVar4 = param_2;
  *(undefined *)(iVar2 + 0x13f) = (&0x16620)[in_r2];
  uVar1 = func_0x00002b70();
  if ((uVar1 & 0xffffffff) != 0) {
    *(char *)(iVar2 + 0x13f) = *(char *)(iVar2 + 0x13f) + '\x01';
  }
  XeCryptHmacSha(0x20,0x10,puVar3,0x10,puVar4,0x10,0,0);
  return;
}



undefined8 FUN_000286f0(int *param_1,int param_2)

{
  int in_r2;
  
  if ((*(QWORD *)(&0x16700 + in_r2) != 0) && (param_2 != 0)) {
    do {
      if (*param_1 == *(int *)((int)*(QWORD *)(&0x16700 + in_r2) + 0xc)) {
        return 1;
      }
      param_2 = param_2 + -1;
      param_1 = param_1 + 1;
    } while (param_2 != 0);
  }
  return 0;
}



QWORD FUN_00028738(void)

{
  ushort uVar1;
  ushort *puVar2;
  QWORD in_r2;
  QWORD lVar3;
  QWORD uVar4;
  QWORD lVar5;
  int iVar6;
  QWORD lVar7;
  QWORD uVar8;
  qword back_chain;
  
  lVar3 = __Save_R12_26_thru_31();
  uVar1 = *(ushort *)((int)lVar3 + 2);
  uVar8 = (QWORD)uVar1;
  lVar3 = lVar3 + 0x10;
  lVar7 = 0;
  if (uVar1 != 0) {
    do {
      puVar2 = (ushort *)lVar3;
      if ((puVar2[2] & 2) == 0) {
        lVar5 = lVar7;
        if ((lVar7 == 0) && (lVar5 = ZEXT48(&0x10010) + in_r2, (puVar2[2] & 1) != 0)) {
          lVar5 = *(QWORD *)(&0x166f0 + (int)in_r2);
        }
        if ((lVar5 != 0) && (iVar6 = XeCryptMemDiff(lVar5,lVar3 + 0x10,0x10), iVar6 == 0)) {
          return lVar3;
        }
      }
      else {
        uVar4 = FUN_000286f0(lVar3 + 0x20,(QWORD)puVar2[1]);
        if ((uVar4 & 0xffffffff) != 0) {
          lVar7 = ZEXT48(&0x10588) + in_r2;
        }
      }
      uVar8 = uVar8 - 1;
      lVar3 = (QWORD)*puVar2 + lVar3;
    } while ((uVar8 & 0xffffffff) != 0);
  }
  return 0;
}



// WARNING: Removing unreachable block (ram,0x0002884c)
// WARNING: Removing unreachable block (ram,0x00028870)
// WARNING: Removing unreachable block (ram,0x00028878)
// WARNING: Removing unreachable block (ram,0x00028890)
// WARNING: Removing unreachable block (ram,0x000288a4)
// WARNING: Removing unreachable block (ram,0x000288b8)
// WARNING: Removing unreachable block (ram,0x000288c8)
// WARNING: Removing unreachable block (ram,0x000288dc)
// WARNING: Removing unreachable block (ram,0x000288f0)
// WARNING: Removing unreachable block (ram,0x00028900)
// WARNING: Removing unreachable block (ram,0x00028914)
// WARNING: Removing unreachable block (ram,0x00028928)
// WARNING: Removing unreachable block (ram,0x0002893c)
// WARNING: Removing unreachable block (ram,0x00028864)

undefined8 FUN_00028808(void)

{
  qword back_chain;
  
  __Save_R12_23_thru_31();
  return 0xffffffffc8000096;
}



undefined8 FUN_000289a0(undefined8 param_1,QWORD param_2,undefined8 param_3)

{
  uint uVar1;
  int in_r2;
  QWORD lVar2;
  undefined8 uVar3;
  qword back_chain;
  
  lVar2 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)(&0x16ae4 + in_r2);
  if ((((*(QWORD *)(&0x16af8 + in_r2) == 0) || (*(QWORD *)(&0x16ae8 + in_r2) == 0))
      || (uVar1 == 0)) || (*(uint *)(&0x16af0 + in_r2) == 0)) {
    uVar3 = 0xffffffffc8000096;
  }
  else {
    if ((param_2 & 0xffffffff) <
        ((QWORD)*(uint *)(&0x16af0 + in_r2) + (QWORD)uVar1 & 0xffffffff)) {
      uVar3 = 0xffffffffc8000003;
    }
    else {
      memcpy(lVar2,*(QWORD *)(&0x16af8 + in_r2));
      FUN_00028648(lVar2,param_3);
      FUN_00028648((QWORD)uVar1 + lVar2,param_3);
      uVar3 = FUN_000283b0(lVar2,0,1);
      if ((int)uVar3 == 0) {
        uVar3 = FUN_000283b0((QWORD)uVar1 + lVar2,0,1);
      }
    }
  }
  return uVar3;
}



undefined8 FUN_00028a78(void)

{
  ushort uVar1;
  uint uVar2;
  ushort uVar3;
  int in_r2;
  int iVar4;
  int iVar6;
  undefined8 uVar5;
  QWORD uVar7;
  QWORD lVar8;
  QWORD uVar9;
  QWORD uVar10;
  qword back_chain;
  
  iVar6 = __Save_R12_27_thru_31();
  uVar5 = FUN_00028518();
  if ((int)uVar5 == 0) {
    if ((*(ushort *)(iVar6 + 0x120) & 1) == 0) {
      uVar1 = *(ushort *)(iVar6 + 4);
      uVar10 = (QWORD)uVar1;
      uVar3 = ~*(ushort *)(iVar6 + 6) & 1;
      uVar2 = *(uint *)(&0x16ae4 + in_r2);
      if (uVar3 != 0) {
        uVar2 = *(uint *)(&0x16af0 + in_r2);
      }
      if ((0x10000 - (QWORD)uVar2 & 0xffffffff) < uVar10) {
        uVar5 = 0xffffffffc8000003;
      }
      else {
        if (uVar3 == 0) {
          lVar8 = *(QWORD *)(&0x16ae8 + in_r2);
        }
        else {
          lVar8 = *(QWORD *)(&0x16af8 + in_r2);
        }
        if (lVar8 == 0) {
          uVar7 = 0;
          uVar9 = 0xffffffffffffffff;
        }
        else {
          uVar7 = (QWORD)*(ushort *)((int)lVar8 + 4);
          uVar9 = (QWORD)*(ushort *)((int)lVar8 + 0x156);
        }
        if ((uVar9 & 0xffffffff) < (QWORD)*(ushort *)(iVar6 + 0x156)) {
          if (uVar3 == 0) {
            *(uint *)(&0x16af0 + in_r2) = (uint)uVar1;
            lVar8 = (QWORD)*(uint *)(&0x16ae4 + in_r2) +
                    *(QWORD *)(&0x16b80 + in_r2);
            *(QWORD *)(&0x16ae8 + in_r2) = lVar8;
          }
          else {
            iVar4 = in_r2;
            FUN_00027fc8(uVar10 - uVar7);
            *(uint *)(&0x16ae4 + in_r2) = (uint)uVar1;
            lVar8 = *(QWORD *)(&0x16b80 + iVar4);
            *(QWORD *)(&0x16af8 + in_r2) = lVar8;
          }
          memcpy(lVar8,iVar6,uVar10);
          memset(lVar8 + 0x120,0,0x30);
          uVar5 = 0;
        }
        else {
          uVar5 = 0xffffffffc8000095;
        }
      }
    }
    else {
      uVar5 = 0xffffffffc8000091;
    }
  }
  return uVar5;
}



undefined8 FUN_00028bc8(QWORD param_1)

{
  int iVar1;
  int in_r2;
  undefined8 uVar2;
  ushort uStack00000014;
  undefined2 uStack00000016;
  
  iVar1 = (int)*(undefined8 *)(&0x16628 + in_r2);
  if (*(char *)(iVar1 + 0x18) == '\0') {
    return 0xffffffffc8000096;
  }
  uStack00000014 = (ushort)(param_1 >> 0x10);
  if (*(ushort *)(iVar1 + 0x1c) < uStack00000014) {
    *(ushort *)(iVar1 + 0x1c) = uStack00000014;
    uVar2 = 0xffffffffc800009c;
  }
  else {
    uVar2 = 0;
  }
  uStack00000016 = (undefined2)param_1;
  if ((param_1 & 0xffff) <= (QWORD)*(ushort *)(iVar1 + 0x1e)) {
    return uVar2;
  }
  *(undefined2 *)(iVar1 + 0x1e) = uStack00000016;
  return 0xffffffffc800009c;
}



undefined8 FUN_00028c40(void)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  QWORD uVar9;
  QWORD in_r2;
  QWORD lVar10;
  QWORD uVar11;
  undefined8 uVar12;
  QWORD uVar13;
  uint uVar14;
  uint uVar15;
  QWORD uVar16;
  QWORD uVar17;
  QWORD lVar18;
  QWORD lVar19;
  qword back_chain;
  dword local_250;
  word local_240;
  
  uVar9 = ZEXT48(register0x0000000c);
  __Save_R12_26_thru_31();
  iVar8 = (int)in_r2;
  lVar18 = *(QWORD *)(&0x16af8 + iVar8);
  uVar3 = *(ushort *)((int)*(undefined8 *)(&0x16628 + iVar8) + 0x1c);
  if ((lVar18 == 0) || (*(QWORD *)(&0x16ae8 + iVar8) == 0)) {
    return 0xffffffffc8000097;
  }
  uVar4 = *(ushort *)((int)*(QWORD *)(&0x16ae8 + iVar8) + 0x156);
  if ((((uVar4 != 0) && (*(ushort *)((int)*(undefined8 *)(&0x16628 + iVar8) + 0x1e) < uVar4))
      || (lVar10 = FUN_00028738(), lVar10 == 0)) &&
     (((uVar4 = *(ushort *)((int)lVar18 + 0x156), 0x400 < uVar4 && (uVar3 < uVar4)) ||
      (lVar10 = FUN_00028738(), lVar10 == 0)))) {
    return 0xffffffffc8000098;
  }
  lVar18 = ZEXT48(&0x16b00) + in_r2;
  lVar19 = 0x10;
  do {
    *(undefined8 *)lVar18 = 0;
    lVar18 = lVar18 + 8;
    lVar19 = lVar19 + -1;
  } while (lVar19 != 0);
  iVar5 = (int)lVar10;
  uVar16 = (QWORD)*(byte *)(iVar5 + 0xb);
  uVar17 = (QWORD)*(ushort *)(iVar5 + 2);
  bVar1 = *(byte *)(iVar5 + 0xc);
  bVar2 = *(byte *)(iVar5 + 0xd);
  if (((9 < (uVar16 - 3 & 0xffffffff)) || (uVar16 < bVar1)) ||
     ((uVar16 < bVar2 || (uVar17 < uVar16)))) {
    return 0xffffffffc8000099;
  }
  iVar6 = (int)in_r2;
  (&0x16b01)[iVar6] = *(byte *)(iVar5 + 0xb);
  (&0x16b04)[iVar6] = bVar1;
  (&0x16b05)[iVar6] = bVar2;
  if (0xb3 < ((QWORD)*(byte *)(iVar5 + 0xe) - 1 & 0xffffffff)) {
    return 0xffffffffc8000099;
  }
  (&0x16b06)[iVar6] = *(byte *)(iVar5 + 0xe);
  bVar1 = *(byte *)(iVar5 + 0xf);
  if (0x17 < ((QWORD)bVar1 - 1 & 0xffffffff)) {
    return 0xffffffffc8000099;
  }
  if (uVar17 < uVar16) {
    uVar16 = uVar17;
  }
  if ((*(char *)((int)*(undefined8 *)(&0x16628 + iVar8) + 0x18) == '\0') ||
     (*(QWORD *)((int)*(undefined8 *)(&0x16628 + iVar8) + 0x28) != 0)) {
    uVar17 = uVar16;
  }
  if (uVar17 < (uint)((int)uVar16 << 2)) {
    uVar11 = 0;
  }
  else {
    uVar11 = HvpGetTimebase();
    uVar13 = (QWORD)bVar1 * 180000000000;
    trapDoubleWordImmediate(6,uVar13,0);
    uVar14 = (uint)(uVar11 / uVar13);
    if (3 < uVar14) {
      uVar14 = 3;
    }
    XeCryptRandom(uVar9 - 0x250,4);
    uVar7 = local_250 & 0xff;
    if (uVar7 < 0x99) {
      uVar15 = 0;
    }
    else {
      if (uVar7 < 0xd9) {
        uVar15 = 1;
      }
      else {
        if (uVar7 < 0xf3) {
          uVar15 = 2;
        }
        else {
          uVar15 = 3;
          if (0xff < uVar7) {
            uVar15 = 4;
          }
        }
      }
      if (uVar14 < uVar15) {
        uVar15 = uVar14;
      }
    }
    uVar14 = (int)uVar17 + 3U >> 2;
    uVar11 = (QWORD)(int)uVar14 * (QWORD)(int)uVar15;
    uVar13 = uVar11 + uVar14;
    if ((uVar13 & 0xffffffff) <= uVar17) goto LAB_00028e48;
  }
  uVar13 = uVar17;
LAB_00028e48:
  uVar13 = uVar13 - uVar11;
  if (0x40 < (uVar13 & 0xffffffff)) {
    XeCryptRandom(uVar9 - 0x250,4);
    uVar17 = uVar13 & 0xffffffff;
    uVar13 = 0x40;
    uVar17 = uVar17 - 0x3f;
    trapDoubleWordImmediate(6,uVar17,0);
    uVar11 = (local_250 - (int)(local_250 / uVar17) * (int)uVar17) + uVar11;
  }
  memcpy(uVar9 - 0x240,(uVar11 & 0xffffffff) * 8 + lVar10 + 0x20,(QWORD)(uint)((int)uVar13 << 3)
        );
  uVar17 = 0;
  if ((uVar13 - 1 & 0xffffffff) != 0) {
    lVar18 = uVar9 - 0x240;
    do {
      XeCryptRandom(uVar9 - 0x250,4);
      uVar11 = uVar13 - uVar17;
      trapWord(6,uVar11,0);
      iVar8 = (local_250 - (int)((QWORD)local_250 / (uVar11 & 0xffffffff)) * (int)uVar11) +
              (int)uVar17;
      uVar17 = uVar17 + 1;
      uVar12 = *(undefined8 *)(&local_240 + iVar8 * 4);
      *(undefined8 *)(&local_240 + iVar8 * 4) = *(undefined8 *)lVar18;
      *(undefined8 *)lVar18 = uVar12;
      lVar18 = lVar18 + 8;
    } while ((uVar17 & 0xffffffff) < (uVar13 - 1 & 0xffffffff));
  }
  XeCryptRandom(uVar9 - 0x250,4);
  uVar17 = (uVar13 - uVar16) + 1;
  trapWord(6,uVar17,0);
  memcpy(ZEXT48(&0x16b20) + in_r2,
         (((QWORD)local_250 -
          (QWORD)(int)((QWORD)local_250 / (uVar17 & 0xffffffff)) * (QWORD)(int)uVar17) * 8
         & 0x7fffffff8) + (uVar9 - 0x240),(QWORD)(uint)((int)uVar16 << 3));
  XeCryptRandom(uVar9 - 0x250,4);
  trapWord(6,uVar16,0);
  (&0x16b07)[iVar6] = (char)local_250 - (char)(local_250 / uVar16) * (char)uVar16;
  return 0;
}



undefined8 FUN_00028f98(undefined8 param_1,QWORD param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  QWORD in_r2;
  undefined8 uVar4;
  QWORD uVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  word *pwVar8;
  undefined8 uVar9;
  QWORD lVar10;
  QWORD lVar11;
  QWORD lVar12;
  qword back_chain;
  dword local_1e0;
  word local_1d0;
  word local_70;
  word local_6e;
  dword local_6c;
  dword local_68;
  word local_62;
  word local_5e;
  word local_40;
  dword local_30;
  
  uVar4 = __Save_R12_29_thru_31();
  iVar3 = (int)in_r2;
  uVar2 = *(uint *)(iVar3 + 0x10000);
  if ((param_2 & 0xffffffff) == 0x22) {
    bVar1 = (&0x16b00)[iVar3];
    if (bVar1 < (byte)(&0x16b01)[iVar3]) {
      puVar6 = (undefined4 *)&local_70;
      lVar11 = 8;
      do {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
      *(undefined2 *)puVar6 = 0;
      pwVar8 = &local_5e;
      lVar10 = ZEXT48(&0x10030) + in_r2;
      uVar5 = *(QWORD *)(&0x16b20 + iVar3 + (uint)bVar1 * 8);
      uVar9 = *(undefined8 *)(&0x16b20 + iVar3 + (uint)bVar1 * 8);
      lVar12 = 0x10;
      lVar11 = lVar10;
      do {
        puVar7 = (undefined *)lVar11;
        lVar11 = lVar11 + 1;
        *(undefined *)pwVar8 = *puVar7;
        pwVar8 = (word *)((int)pwVar8 + 1);
        lVar12 = lVar12 + -1;
      } while (lVar12 != 0);
      if (bVar1 == (&0x16b07)[iVar3]) {
        uVar5 = ((QWORD)((uint)((QWORD)uVar9 >> 0x10) & 0xffffff) - (uVar5 >> 0x28) &
                0xffffffff) / 3;
        XeCryptRandom(&local_1e0,4);
        trapWord(6,uVar5,0);
        XeCryptRandom(&local_1e0,4);
        trapWord(6,uVar5,0);
      }
      pwVar8 = &local_40;
      lVar11 = 0x10;
      do {
        puVar7 = (undefined *)lVar10;
        lVar10 = lVar10 + 1;
        *(undefined *)pwVar8 = *puVar7;
        pwVar8 = (word *)((int)pwVar8 + 1);
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
      XeCryptAesKey(&local_1d0,ZEXT48(&0x10020) + in_r2);
      XeCryptAesCbc(&local_1d0,&local_6e,0x10,&local_6e,&local_40,1);
      memcpy(uVar4,&local_70,0x22);
      FUN_00000204((QWORD)uVar2);
      uVar4 = 0;
    }
    else {
      FUN_00000204((QWORD)uVar2);
      uVar4 = 0xffffffffc800009a;
    }
  }
  else {
    FUN_00000204((QWORD)uVar2);
    uVar4 = 0xffffffffc8000090;
  }
  return uVar4;
}



// WARNING: Could not reconcile some variable overlaps

undefined8 FUN_000291a0(undefined8 param_1,QWORD param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  QWORD in_r2;
  undefined8 uVar5;
  word *pwVar6;
  undefined8 uVar7;
  QWORD lVar8;
  undefined *puVar10;
  QWORD uVar9;
  byte *pbVar11;
  QWORD lVar12;
  qword back_chain;
  word local_1d0;
  word local_70;
  word local_6e;
  word local_62;
  word local_40;
  dword local_30;
  
  uVar5 = __Save_R12_28_thru_31();
  iVar4 = (int)in_r2;
  uVar3 = *(uint *)(iVar4 + 0x10000);
  pbVar11 = &0x16b00 + iVar4;
  if (((param_2 & 0xffffffff) == 0x22) && (bVar1 = *pbVar11, bVar1 < (byte)(&0x16b01)[iVar4]))
  {
    bVar2 = (&0x16b06)[iVar4];
    uVar7 = *(undefined8 *)(&0x16b20 + (uint)bVar1 * 8 + iVar4);
    if (-1 < param_3) {
      memcpy(&local_70,uVar5,0x22);
      if (((local_70._0_1_ & 0x3f) == 0x39) && ((char)local_70 == ' ')) {
        pwVar6 = &local_40;
        lVar8 = ZEXT48(&0x10030) + in_r2;
        lVar12 = 0x10;
        do {
          puVar10 = (undefined *)lVar8;
          lVar8 = lVar8 + 1;
          *(undefined *)pwVar6 = *puVar10;
          pwVar6 = (word *)((int)pwVar6 + 1);
          lVar12 = lVar12 + -1;
        } while (lVar12 != 0);
        XeCryptAesKey(&local_1d0,ZEXT48(&0x10020) + in_r2);
        XeCryptAesCbc(&local_1d0,&local_6e,0x10,&local_6e,&local_40,0);
        if ((local_6e._0_1_ == '\x11') && (local_62 < 0x168)) {
          if (bVar1 == (&0x16b07)[iVar4]) {
            (&0x16b07)[iVar4] = 0xff;
            goto LAB_00029300;
          }
          uVar9 = ((QWORD)local_62 - (QWORD)((uint)uVar7 & 0xffff)) + (QWORD)bVar2 +
                  0x168;
          if ((QWORD)bVar2 << 1 < (uVar9 + ((uVar9 & 0xffffffff) / 0x168) * -0x168 & 0xffffffff)
             ) {
            (&0x16b03)[iVar4] = (&0x16b03)[iVar4] + '\x01';
          }
          else {
            (&0x16b02)[iVar4] = (&0x16b02)[iVar4] + '\x01';
          }
        }
      }
    }
  }
  *pbVar11 = *pbVar11 + 1;
LAB_00029300:
  FUN_00000204((QWORD)uVar3);
  return 0;
}



undefined8 FUN_00029318(void)

{
  int in_r2;
  undefined8 uVar1;
  undefined8 *puVar2;
  QWORD lVar3;
  
  puVar2 = (undefined8 *)(&0x16b00 + in_r2);
  if (*(char *)puVar2 == (&0x16b01)[in_r2]) {
    if ((byte)(&0x16b05)[in_r2] <= (byte)(&0x16b03)[in_r2]) {
      uVar1 = 0xffffffffc800009e;
      goto LAB_00029370;
    }
    if ((byte)(&0x16b04)[in_r2] <= (byte)(&0x16b02)[in_r2]) {
      uVar1 = 0xffffffffc800009f;
      goto LAB_00029370;
    }
  }
  uVar1 = 0xffffffffc800009d;
LAB_00029370:
  lVar3 = 0x10;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
    lVar3 = lVar3 + -1;
  } while (lVar3 != 0);
  return uVar1;
}



QWORD FUN_00029390(undefined8 param_1,undefined8 param_2)

{
  QWORD in_r2;
  undefined8 uVar1;
  QWORD uVar2;
  qword back_chain;
  
  uVar1 = __Save_R12_29_thru_31();
  HvpAquireSpinLock(ZEXT48(&0x16ae0) + in_r2);
  uVar2 = func_0x00000790(param_2,uVar1);
  FUN_00027f08();
  HvpReleaseSpinLock(ZEXT48(&0x16ae0) + in_r2);
  return uVar2 & 0xffffffff;
}



QWORD FUN_000293e0(undefined8 param_1,QWORD param_2,undefined8 param_3,undefined8 param_4,
                      QWORD param_5,QWORD param_6)

{
  QWORD in_r2;
  QWORD uVar1;
  undefined8 uVar2;
  QWORD lVar3;
  qword back_chain;
  
  uVar1 = __Save_R12_24_thru_31();
  lVar3 = ZEXT48(&0x16a98) + in_r2;
  if ((param_5 & 0xffffffff) == 0) {
    uVar2 = HvpPhysicalToReal(uVar1,param_2);
  }
  else {
    if (((((uVar1 & 0x7f) != 0) || ((param_2 & 0x7f) != 0)) || ((param_2 & 0xffffffff) == 0)) ||
       ((0x10000 < (param_2 & 0xffffffff) ||
        (((((uint)uVar1 + (uint)param_2) - 1 ^ (uint)uVar1) & 0xffff0000) != 0)))) {
      return 0xffffffffc8000090;
    }
    HvpAquireSpinLock(lVar3);
    uVar2 = HvpRelocatePhysicalToProtected(uVar1,param_2,0x3a);
  }
  HvpAquireSpinLock(ZEXT48(&0x16ae0) + in_r2);
  uVar1 = func_0x000007a0(uVar2,param_2,param_3,param_4);
  FUN_00027f08();
  HvpReleaseSpinLock(ZEXT48(&0x16ae0) + in_r2);
  if (((param_6 & 0xffffffff) != 0) || ((int)uVar1 != 0)) {
    if ((param_5 & 0xffffffff) == 0) {
      memset(uVar2,0,param_2);
    }
    else {
      HvpZeroCacheLines(uVar2,(QWORD)((uint)param_2 >> 7));
    }
  }
  if ((param_5 & 0xffffffff) != 0) {
    FUN_000034b8(uVar2,param_2,0x3a);
    HvpReleaseSpinLock(lVar3);
  }
  return uVar1 & 0xffffffff;
}



QWORD FUN_00029528(int param_1,QWORD param_2,QWORD param_3,undefined8 param_4)

{
  QWORD in_r2;
  QWORD uVar1;
  undefined8 uVar2;
  QWORD lVar3;
  QWORD uVar4;
  QWORD uVar5;
  QWORD lVar6;
  
  if (param_1 == 0) {
    uVar5 = 1;
    uVar4 = 1;
    lVar3 = ZEXT48(FUN_00028808) + in_r2;
  }
  else {
    if (param_1 == 1) {
      uVar5 = 0;
      uVar4 = 1;
      lVar3 = ZEXT48(FUN_000289a0) + in_r2;
    }
    else {
      if (param_1 != 2) {
        if (param_1 == 3) {
          lVar3 = ZEXT48(FUN_00028bc8) + in_r2;
        }
        else {
          if (param_1 != 4) {
            if (param_1 == 5) {
              uVar5 = 0;
              uVar4 = 0;
              lVar3 = ZEXT48(FUN_00028f98) + in_r2;
              param_4 = 0;
            }
            else {
              if (param_1 != 6) {
                if (param_1 != 7) {
                  return 0xffffffffc8000090;
                }
                param_2 = 0;
                lVar3 = ZEXT48(FUN_00029318) + in_r2;
                goto FUN_00029390;
              }
              uVar5 = 0;
              uVar4 = 0;
              lVar3 = ZEXT48(FUN_000291a0) + in_r2;
            }
            goto FUN_000293e0;
          }
          param_2 = 0;
          lVar3 = ZEXT48(FUN_00028c40) + in_r2;
        }
FUN_00029390:
        uVar2 = __Save_R12_29_thru_31(lVar3,param_2,param_4);
        HvpAquireSpinLock(ZEXT48(&0x16ae0) + in_r2);
        uVar4 = func_0x00000790(param_2,uVar2);
        FUN_00027f08();
        HvpReleaseSpinLock(ZEXT48(&0x16ae0) + in_r2);
        return uVar4 & 0xffffffff;
      }
      uVar5 = 1;
      uVar4 = 1;
      lVar3 = ZEXT48(FUN_00028a78) + in_r2;
      param_4 = 0;
    }
  }
FUN_000293e0:
  param_3 = param_3 & 0xffffffff;
  uVar1 = __Save_R12_24_thru_31(param_2 & 0xffffffff,param_3,param_4,lVar3);
  lVar6 = ZEXT48(&0x16a98) + in_r2;
  if ((uVar4 & 0xffffffff) == 0) {
    uVar2 = HvpPhysicalToReal(uVar1,param_3);
  }
  else {
    if (((((uVar1 & 0x7f) != 0) || ((param_3 & 0x7f) != 0)) || ((param_3 & 0xffffffff) == 0)) ||
       ((ZEXT48(&0x10001) <= (param_3 & 0xffffffff) ||
        (((((uint)uVar1 + (uint)param_3) - 1 ^ (uint)uVar1) & 0xffff0000) != 0)))) {
      return 0xffffffffc8000090;
    }
    HvpAquireSpinLock(lVar6);
    uVar2 = HvpRelocatePhysicalToProtected(uVar1,param_3,0x3a);
  }
  HvpAquireSpinLock(ZEXT48(&0x16ae0) + in_r2);
  uVar1 = func_0x000007a0(uVar2,param_3,param_4,lVar3);
  FUN_00027f08();
  HvpReleaseSpinLock(ZEXT48(&0x16ae0) + in_r2);
  if (((uVar5 & 0xffffffff) != 0) || ((int)uVar1 != 0)) {
    if ((uVar4 & 0xffffffff) == 0) {
      memset(uVar2,0,param_3);
    }
    else {
      HvpZeroCacheLines(uVar2,(QWORD)((uint)param_3 >> 7));
    }
  }
  if ((uVar4 & 0xffffffff) != 0) {
    FUN_000034b8(uVar2,param_3,0x3a);
    HvpReleaseSpinLock(lVar6);
  }
  return uVar1 & 0xffffffff;
}



QWORD FUN_00029648(QWORD param_1,QWORD param_2,QWORD param_3)

{
  int in_r2;
  
  return *(QWORD *)(&0x16ac0 + in_r2) ^ param_1 ^ param_2 ^ param_3;
}



QWORD thunk_FUN_00023698(QWORD param_1,uint param_2,uint param_3)

{
  return (QWORD)
         (((uint)(param_1 >> 0x11) & 0x80 | (uint)(param_1 >> 0x19) & 0x7f) +
          ((uint)(param_1 >> 0x25) & 7 | (uint)(param_1 >> 0x1d) & 0xf8) +
          ((uint)(param_1 >> 0x16) & 3 | (uint)(param_1 >> 0xe) & 0xfc) +
          ((uint)(param_1 >> 0xb) & 0x1f | (uint)(param_1 >> 3) & 0xe0) +
          ((uint)(param_1 >> 7) & 1 | (uint)(param_1 << 1) & 0xfe) & 0xff ^ param_2 & 0xff ^
         param_3 & 0xff) ^ 0x3a;
}



QWORD thunk_FUN_00023718(QWORD param_1,undefined8 param_2,undefined8 param_3)

{
  return (QWORD)
         (((uint)(param_1 >> 0x27) & 1 | (uint)(param_1 >> 0x1f) & 0xfe) +
          ((uint)(param_1 >> 0x1b) & 0x1f | (uint)(param_1 >> 0x13) & 0xe0) +
          ((uint)(param_1 >> 10) & 0x3f | (uint)(param_1 >> 2) & 0xc0) +
          ((uint)(param_1 >> 0x14) & 0xf | (uint)(param_1 >> 0xc) & 0xf0) + ((uint)param_1 & 0xff) &
          0xff ^ (uint)((QWORD)param_2 >> 8) & 0xff ^ (uint)((QWORD)param_3 >> 8) & 0xff) ^
         0x72;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_00029670(void)

{
  uint uVar1;
  QWORD in_r2;
  qword back_chain;
  qword local_1b0;
  dword local_1a4;
  qword local_1a0;
  word local_190;
  word local_30;
  dword local_20;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  XeCryptHmacSha(&local_1a0,8,0,0,0,0,0,0);
  XeCryptAesKey(&local_190,&local_30);
  XeCryptAesEcb(&local_190,ZEXT48(&0x10598) + in_r2, ZEXT48(&0x16ac0) + in_r2,0);
  FUN_00000204((QWORD)uVar1);
  return;
}



void FUN_00029710(void)

{
  QWORD in_r2;
  undefined8 uVar1;
  undefined8 uVar2;
  QWORD lVar3;
  
  uVar2 = 0x10;
  uVar1 = __Save_R12_29_thru_31(ZEXT48(&0x16710) + in_r2,0x10);
  lVar3 = ZEXT48(&0x16a90) + in_r2;
  HvpAquireSpinLock(lVar3);
  XeCryptRc4Ecb(ZEXT48(&0x16980) + in_r2,uVar1,uVar2);
  HvpReleaseSpinLock(lVar3);
  return;
}



void FUN_00029720(void)

{
  int in_r2;
  QWORD lVar1;
  undefined8 uVar2;
  qword back_chain;
  qword local_8;
  
  lVar1 = FUN_00000270();
  *(QWORD *)(&0x16970 + in_r2) = ZEXT48(&0x0e800) + lVar1;
  uVar2 = FUN_000002a8();
  *(undefined8 *)(&0x166f8 + in_r2) = uVar2;
  return;
}



void FUN_00029760(undefined8 param_1,undefined8 param_2,QWORD param_3)

{
  uint extraout_var;
  uint uVar1;
  QWORD uVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  qword back_chain;
  
  uVar4 = (uint)param_2;
  uVar2 = __Save_R12_29_thru_31();
  if ((param_3 & 0xffffffff) != 0) {
    uVar4 = uVar4 & 0xf;
    iVar3 = FUN_000005a8();
    pbVar5 = (byte *)((extraout_var & 0x7fffffff) + iVar3);
    if ((uVar2 & 1) != 0) {
      param_3 = param_3 - 1;
      *pbVar5 = (byte)(uVar4 << 4) | *pbVar5 & 0xf;
      pbVar5 = pbVar5 + 1;
    }
    if (1 < (param_3 & 0xffffffff)) {
      memset(pbVar5,(QWORD)(uVar4 << 4 | uVar4),param_3 >> 1 & 0x7fffffff);
    }
    if ((param_3 & 1) != 0) {
      uVar1 = (uint)(param_3 >> 1) & 0x7fffffff;
      pbVar5[uVar1] = (byte)uVar4 | pbVar5[uVar1] & 0xf0;
    }
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

QWORD FUN_000297f0(QWORD param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  iVar3 = FUN_000005a8();
  bVar1 = *(byte *)(((uint)(param_1 >> 1) & 0x7fffffff) + iVar3);
  uVar2 = (uint)(bVar1 >> 4);
  if ((param_1 & 1) == 0) {
    uVar2 = (uint)bVar1 & 0xf;
  }
  return (QWORD)uVar2;
}



undefined8 FUN_00029838(undefined8 param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar5;
  uint *puVar6;
  QWORD uVar3;
  undefined8 uVar4;
  qword back_chain;
  
  uVar5 = __Save_R12_28_thru_31();
  *param_2 = 0;
  puVar6 = (uint *)FUN_0000057c();
  if ((puVar6 == (uint *)0x0) || (*puVar6 == 0)) {
LAB_00029898:
    uVar4 = 0;
  }
  else {
    *param_2 = *puVar6;
    if ((uVar5 & 0xf0000000) == 0x90000000) {
      uVar3 = FUN_000297f0((QWORD)(uVar5 >> 0xc & 0xffff));
      if ((uVar3 & 0xffffffff) == 0) {
        *param_2 = 0;
        goto LAB_00029898;
      }
      uVar5 = *param_2;
      *param_2 = (uint)uVar3 & 0xf | uVar5 & 0xfffffff0;
      uVar1 = *puVar6;
      uVar2 = (uint)uVar3 & 7;
      *param_2 = uVar2 | uVar5 & 0xfffffff0 | uVar1 & 8;
      if (((uVar5 & 0x40000000) != 0) && ((uVar3 & 8) == 0)) {
        *param_2 = uVar2 | uVar5 & 0xffff0 | uVar1 & 8;
      }
    }
    uVar4 = 1;
  }
  return uVar4;
}



QWORD FUN_000298e8(int param_1)

{
  int iVar1;
  int in_r2;
  uint uVar2;
  QWORD lVar3;
  QWORD lVar4;
  QWORD lVar5;
  
  uVar2 = 0;
  lVar3 = *(QWORD *)(&0x166f8 + in_r2);
  lVar5 = 0;
  lVar4 = lVar3 + 0x18;
  do {
    if (*(uint *)((int)lVar3 + 0x14) <= uVar2) break;
    if (*(int *)lVar4 == param_1) {
      lVar5 = lVar4;
    }
    uVar2 = uVar2 + 1;
    lVar4 = lVar4 + 8;
  } while (lVar5 == 0);
  if (lVar5 == 0) {
    return 0;
  }
  iVar1 = (int)lVar5;
  if (*(char *)(iVar1 + 3) == '\0') {
    return (QWORD)*(uint *)(iVar1 + 4);
  }
  if (*(char *)(iVar1 + 3) == '\x01') {
    return lVar5 + 4;
  }
  return (QWORD)*(uint *)(iVar1 + 4) + lVar3;
}



undefined8
FUN_00029968(undefined8 param_1,QWORD param_2,QWORD param_3,QWORD param_4,
            QWORD param_5)

{
  uint uVar1;
  QWORD uVar2;
  QWORD uVar3;
  QWORD uVar4;
  QWORD uVar5;
  QWORD uVar6;
  qword back_chain;
  dword local_40;
  
  uVar2 = __Save_R12_27_thru_31();
  if (param_3 != 0) {
    uVar1 = *(uint *)((int)param_3 + 0x10);
    if ((param_2 & 0xffffffff) < (QWORD)uVar1) {
      return 0;
    }
    if ((QWORD)(*(int *)((int)param_3 + 0x14) + uVar1) < (param_2 + param_4 & 0xffffffff)) {
      return 0;
    }
  }
  while( true ) {
    if ((param_4 & 0xffffffff) == 0) {
      return 1;
    }
    uVar3 = FUN_00029838(param_2,&local_40);
    if (((uVar3 & 0xffffffff) == 0) ||
       (((param_5 & 0xffffffff) != 0 && (((local_40 & 1) == 0 || ((local_40 & 0x40000000) == 0))))))
    break;
    uVar3 = ((int)param_2 + 0x1000U & 0xfffff000) - param_2;
    uVar4 = ((QWORD)local_40 & 0xffffffc0) << 10 | 0x8000000000000000 | param_2 & 0xffff;
    if ((param_4 & 0xffffffff) < (uVar3 & 0xffffffff)) {
      uVar3 = param_4;
    }
    uVar5 = uVar4;
    uVar6 = uVar2;
    if ((param_5 & 0xffffffff) != 0) {
      uVar5 = uVar2;
      uVar6 = uVar4;
    }
    memcpy(uVar5,uVar6,uVar3);
    param_4 = param_4 - uVar3;
    param_2 = uVar3 + param_2;
    uVar2 = (uVar3 & 0xffffffff) + uVar2;
  }
  return 0;
}



undefined8 FUN_00029a68(undefined8 param_1,QWORD param_2)

{
  uint uVar1;
  undefined *puVar2;
  QWORD in_r2;
  int iVar3;
  undefined8 uVar4;
  QWORD lVar5;
  qword back_chain;
  word local_140;
  word local_40;
  dword local_2c;
  
  iVar3 = __Save_R12_28_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  uVar4 = countLeadingZeros(*(uint *)(iVar3 + 0x104) & 6);
  if ((*(uint *)(iVar3 + 0x104) & 0x80000000) == 0) {
    puVar2 = &0x10548;
  }
  else {
    puVar2 = &0x10554;
  }
  lVar5 = ZEXT48(puVar2) + in_r2;
  XeCryptRotSumSha((uint *)(iVar3 + 0x100),(QWORD)*(uint *)(iVar3 + 0x100) - 0x100,0,0,&local_40
                   ,0x14);
  memcpy(&local_140,iVar3,0x100);
  iVar3 = XeCryptBnQwBeSigVerify(&local_140,&local_40,lVar5,ZEXT48(&0x108b8) + in_r2);
  if (iVar3 == 0) {
    uVar4 = 0xffffffffc0000221;
  }
  else {
    if (param_2 != 0) {
      in_r2 = ZEXT48(&0x10cf8) + in_r2;
      if (((uint)uVar4 >> 5 & 1) == 1) {
        in_r2 = 0x54;
      }
      XeCryptAesKey(param_2,in_r2);
    }
    uVar4 = 0;
  }
  FUN_00000204((QWORD)uVar1);
  return uVar4;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00029b58(undefined8 param_1,undefined8 param_2)

{
  QWORD in_r2;
  QWORD uVar1;
  qword back_chain;
  word local_1b0;
  word local_180;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = FUN_00029968(&local_1b0,param_1,param_2,0x2c,1);
  if ((uVar1 & 0xffffffff) != 0) {
    XeCryptAesKey(&local_180,ZEXT48(&0x16710) + in_r2);
    XeCryptAesEcb(&local_180,&local_1b0,&local_1b0,1);
    FUN_00029968(&local_1b0,param_1,param_2,0x2c,0);
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

QWORD FUN_00029be8(undefined8 param_1)

{
  int in_r2;
  QWORD uVar1;
  uint uVar2;
  qword back_chain;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  HvpAquireSpinLock(&0x16920 + in_r2);
  uVar1 = FUN_00029838(param_1,&local_20);
  uVar2 = 0;
  if ((uVar1 & 0xffffffff) != 0) {
    uVar2 = local_20;
  }
  HvpReleaseSpinLock(&0x16920 + in_r2);
  return (QWORD)(uVar2 & 0x400fffff);
}



undefined8 thunk_FUN_00002bb8(void)

{
  return 0;
}



QWORD FUN_00029c68(int param_1,QWORD param_2)

{
  ushort uVar1;
  int iVar2;
  qword back_chain;
  word local_10;
  qword local_8;
  
  iVar2 = (int)(param_2 << 1);
  uVar1 = *(ushort *)(iVar2 + param_1);
  if ((uVar1 & 0x400) == 0) {
    *(short *)(iVar2 + param_1) = uVar1 + 1;
  }
  else {
    XeCryptRandom(&local_10,2);
    uVar1 = local_10;
  }
  return (QWORD)((uint)uVar1 & 0x3ff);
}



undefined8 FUN_00029cc0(undefined8 param_1,QWORD param_2,QWORD param_3)

{
  QWORD *puVar1;
  QWORD in_r2;
  QWORD uVar2;
  undefined8 uVar3;
  uint *puVar4;
  int iVar5;
  qword back_chain;
  
  uVar2 = __Save_R12_26_thru_31();
  iVar5 = (int)in_r2;
  if ((uVar2 & 0xffffffff) < 2) {
    HvpAquireSpinLock(ZEXT48(&0x16920) + in_r2);
    uVar3 = 0;
    puVar1 = (QWORD *)(&0x16680 + (int)uVar2 * 0x38 + iVar5);
    if ((((*(char *)((int)puVar1 + 0x34) == '\x01') && ((param_2 & 0xffff) == 0)) &&
        ((param_3 & 0xffff) == 0)) &&
       (((param_3 & 0xffffffff) < 0x20000000 && (uVar2 = FUN_0000057c(param_2), uVar2 != 0)))) {
      puVar4 = (uint *)uVar2;
      if (((((*puVar4 & 8) == 0) && ((*puVar1 <= uVar2 && (uVar2 <= puVar1[1])))) &&
          ((*puVar4 & 0xfffc0) == 0)) &&
         (iVar5 = FUN_000005c0(),
         (*(ushort *)(((uint)(param_3 >> 0xf) & 0x1fffe) + iVar5) & 0x800) == 0)) {
        uVar3 = 1;
        uVar2 = (QWORD)((uint)param_3 >> 10 & 0xfffc0) | (QWORD)*puVar4 & 0xfffffffffff0003f
        ;
        *puVar4 = (uint)uVar2;
        *(ushort *)(((uint)(uVar2 >> 5) & 0x7ffe) + iVar5) =
             *(ushort *)(((uint)(uVar2 >> 5) & 0x7ffe) + iVar5) | 0x800;
      }
    }
    HvpReleaseSpinLock(ZEXT48(&0x16920) + in_r2);
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00029de8(uint param_1)

{
  uint uVar1;
  QWORD *puVar2;
  int in_r2;
  undefined8 uVar3;
  QWORD uVar4;
  undefined uVar5;
  undefined *puVar6;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (param_1 < 2) {
    puVar6 = &0x16920 + in_r2;
    HvpAquireSpinLock(puVar6);
    uVar3 = 0;
    puVar2 = (QWORD *)(&0x16680 + param_1 * 0x38 + in_r2);
    if (*(char *)((int)puVar2 + 0x34) == '\x01') {
      uVar4 = *puVar2;
      while (uVar4 <= puVar2[1]) {
        uVar1 = *(uint *)uVar4;
        if ((uVar1 & 0xfffc0) == 0) {
          uVar5 = 0xf;
          goto LAB_00029e80;
        }
        *(uint *)uVar4 = uVar1 & 0xfffffff0 | 0xe;
        uVar4 = uVar4 + 4;
      }
      uVar5 = 2;
      uVar3 = 1;
LAB_00029e80:
      *(undefined *)((int)puVar2 + 0x34) = uVar5;
    }
    HvpReleaseSpinLock(puVar6);
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



undefined8 FUN_00029eb0(void)

{
  uint uVar1;
  QWORD in_r2;
  QWORD uVar2;
  uint *puVar3;
  undefined8 uVar4;
  qword back_chain;
  dword local_30;
  
  uVar2 = __Save_R12_29_thru_31();
  uVar4 = 0;
  HvpAquireSpinLock(ZEXT48(&0x16920) + in_r2);
  if (((((uVar2 & 0xffff) == 0) && ((uVar2 & 0xffffffff) != 0x80000000)) &&
      (puVar3 = (uint *)FUN_0000057c(uVar2), puVar3 != (uint *)0x0)) && ((*puVar3 & 0x10) != 0)) {
    do {
      uVar1 = *puVar3;
      *puVar3 = uVar1 & 0xfffffff0 | 7;
      puVar3 = puVar3 + 1;
    } while ((uVar1 >> 5 & 1) == 0);
    uVar4 = 1;
  }
  HvpReleaseSpinLock(ZEXT48(&0x16920) + in_r2);
  return uVar4;
}



undefined8 FUN_00029f58(void)

{
  uint uVar1;
  QWORD in_r2;
  QWORD uVar2;
  int iVar3;
  undefined8 uVar4;
  QWORD lVar5;
  QWORD uVar6;
  undefined8 uVar7;
  uint *puVar8;
  qword back_chain;
  
  uVar2 = __Save_R12_25_thru_31();
  uVar7 = 0;
  iVar3 = FUN_000005c0();
  lVar5 = ZEXT48(&0x16920) + in_r2;
  HvpAquireSpinLock(lVar5);
  HvpSetRMCI(0);
  if ((((uVar2 & 0xffff) == 0) && ((uVar2 & 0xffffffff) != 0x80000000)) &&
     (puVar8 = (uint *)FUN_0000057c(uVar2), puVar8 != (uint *)0x0)) {
    uVar6 = (QWORD)((uint)uVar2 >> 0xc & 0xffff);
    uVar4 = countLeadingZeros(-0x70000000 - ((uint)uVar2 & 0xf0000000));
    if ((*puVar8 != 0) && ((*puVar8 & 0x10) != 0)) {
      do {
        if ((*puVar8 & 0xc0000000) != 0) {
          HvpInvalidateCachelines(((QWORD)*puVar8 & 0xffffffc0) << 10,0x10000);
        }
        if (((uint)uVar4 >> 5 & 1) != 0) {
          FUN_00029760(uVar6,0,0x10);
          uVar6 = uVar6 + 0x10;
        }
        if ((*puVar8 & 0xfffc0) != 0) {
          uVar1 = *puVar8 >> 5 & 0x7ffe;
          *(ushort *)(uVar1 + iVar3) = *(ushort *)(uVar1 + iVar3) & 0xf7ff;
        }
        uVar1 = *puVar8;
        *puVar8 = 0;
        puVar8 = puVar8 + 1;
      } while ((uVar1 >> 5 & 1) == 0);
      iVar3 = 0xc;
      in_r2 = ZEXT48(&0x16940) + in_r2;
      do {
        if ((QWORD)*(uint *)in_r2 == (uVar2 & 0xffffffff)) {
          *(uint *)in_r2 = 0;
        }
        iVar3 = iVar3 + -1;
        in_r2 = in_r2 + 4;
      } while (iVar3 != 0);
      uVar7 = 1;
    }
  }
  HvpSetRMCI(1);
  HvpReleaseSpinLock(lVar5);
  return uVar7;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_0002a0b0(uint param_1)

{
  int in_r2;
  undefined *puVar1;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (param_1 < 2) {
    puVar1 = &0x16920 + in_r2;
    HvpAquireSpinLock(puVar1);
    (&0x166b4)[param_1 * 0x38 + in_r2] = 0;
    HvpReleaseSpinLock(puVar1);
  }
  return 0;
}



undefined8 FUN_0002a120(undefined8 param_1,QWORD param_2,undefined8 param_3,undefined8 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined *puVar5;
  QWORD *plVar6;
  QWORD in_r2;
  QWORD uVar7;
  int iVar8;
  uint uVar9;
  QWORD lVar10;
  QWORD uVar11;
  undefined4 *puVar12;
  QWORD lVar13;
  undefined8 uVar14;
  QWORD lVar15;
  QWORD unaff_r28;
  QWORD uVar16;
  QWORD uVar17;
  uint *puVar18;
  int iVar19;
  uint param_1_01;
  QWORD param_1_00;
  undefined8 param_2_00;
  undefined8 param_3_00;
  qword back_chain;
  word local_90;
  dword local_7c;
  
  uVar7 = __Save_R12_19_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  param_1_00 = param_2;
  param_2_00 = param_3;
  param_3_00 = param_4;
  if (1 < (uVar7 & 0xffffffff)) {
    FUN_00000204((QWORD)uVar1);
    return 0;
  }
  lVar13 = ZEXT48(&0x16920) + in_r2;
  HvpAquireSpinLock(lVar13);
  uVar14 = 0;
  HvpSetRMCI(0);
  lVar15 = (uVar7 & 0xffffffff) * 0x38 + ZEXT48(&0x16680) + in_r2;
  plVar6 = (QWORD *)lVar15;
  if (*(char *)((int)plVar6 + 0x34) == '\x02') {
    if ((((param_1_00 & 0x200000000) != 0) || ((param_1_00 & 0x100000000) != 0)) &&
       ((param_1_00 & 0x400000000) == 0)) {
      if (((param_1_00 & 0x200000000) == 0) || (iVar19 = 0, (param_1_00 & 0x800000000) != 0)) {
        iVar19 = 1;
      }
      if ((*(byte *)((int)plVar6 + 0x35) & 1) == 0) {
        uVar7 = (QWORD)(param_1_01 & 3) | 0xc;
        lVar10 = 0x10;
      }
      else {
        lVar10 = 0xc;
        uVar7 = (QWORD)(uint)(iVar19 << 3) | (QWORD)(param_1_01 & 3) | 4;
      }
      uVar2 = *(uint *)(plVar6 + 3);
      puVar5 = (undefined *)((param_1_01 >> 4) << lVar10);
      uVar16 = unaff_r28 & 0xffffffff00000000 | ZEXT48(puVar5);
      if ((((QWORD)uVar2 < (QWORD)*(uint *)((int)plVar6 + 0x14)) &&
          (puVar5 != (undefined *)0x0)) &&
         ((puVar5 < &0x10001 &&
          (((ZEXT48(puVar5) <=
             ((QWORD)*(uint *)((int)plVar6 + 0x14) - (QWORD)uVar2 & 0xffffffff) &&
            ((((uint)(puVar5 + uVar2 + -1) ^ uVar2) & 0xffff0000) == 0)) &&
           (uVar17 = ((QWORD)(uVar2 >> 0xe) & 0x3fffffffffffc) + *plVar6,
           uVar17 <= (QWORD)plVar6[1])))))) {
        puVar18 = (uint *)uVar17;
        uVar3 = *puVar18;
        if (((uVar3 & 8) != 0) && ((uVar3 & 0xfffc0) != 0)) {
          uVar11 = (QWORD)((uVar3 & 0xfffc0) << 10 | uVar2 & 0xf000);
          uVar17 = uVar11 | 0x8000000000000000;
          if (iVar19 != 0) {
            uVar17 = HvpRelocatePhysicalToProtected(uVar11,uVar16,0x3d);
          }
          XeCryptSha(uVar17,uVar16,&stack0x00000020,0x18,0,0,&local_90,0x14);
          lVar15 = lVar15 + 0x20;
          iVar8 = XeCryptMemDiff(&local_90,lVar15,0x14);
          if (iVar8 == 0) {
            if (iVar19 != 0) {
              uVar3 = *puVar18;
              if ((uVar3 & 0xc0000000) == 0) {
                uVar14 = FUN_000005c0();
                uVar9 = FUN_00029c68(uVar14,(QWORD)(*puVar18 >> 6 & 0x3fff));
                *puVar18 = (uVar9 & 0x3ff) << 0x14 | uVar3 & 0xc00fffff | 0xc0000000;
              }
              HvpRelocateCacheLines
                        (uVar17,((QWORD)*puVar18 & 0x3fffffffffffc0) << 10 | 0x8000000000000000
                                | (QWORD)(uVar2 & 0xf000),(QWORD)((uint)puVar5 >> 7));
            }
            if ((*(byte *)((int)plVar6 + 0x35) & 1) == 0) {
              *puVar18 = (uint)uVar7 | *puVar18 & 0xfffffff0;
            }
            else {
              FUN_00029760((QWORD)*(ushort *)((int)plVar6 + 0x36) + (QWORD)(uVar2 >> 0xc),
                           uVar7,(QWORD)((uint)puVar5 >> 0xc));
            }
            puVar12 = (undefined4 *)((int)&stack0x00000020 + 4);
            *(undefined **)(plVar6 + 3) = puVar5 + uVar2;
            lVar10 = 5;
            do {
              uVar4 = *puVar12;
              puVar12 = puVar12 + 1;
              *(undefined4 *)lVar15 = uVar4;
              lVar15 = lVar15 + 4;
              lVar10 = lVar10 + -1;
            } while (lVar10 != 0);
            uVar14 = 1;
            goto LAB_0002a3ec;
          }
          if (iVar19 != 0) {
            HvpInvalidateCachelines(uVar17,uVar16);
          }
        }
      }
    }
  }
  *(undefined *)((int)plVar6 + 0x34) = 0xf;
LAB_0002a3ec:
  HvpSetRMCI(1);
  HvpReleaseSpinLock(lVar13);
  FUN_00000204((QWORD)uVar1);
  return uVar14;
}



undefined8 FUN_0002a410(void)

{
  QWORD *plVar1;
  QWORD in_r2;
  QWORD uVar2;
  undefined8 uVar3;
  QWORD uVar4;
  QWORD lVar5;
  QWORD lVar6;
  qword back_chain;
  
  uVar2 = __Save_R12_29_thru_31();
  if ((uVar2 & 0xffffffff) < 2) {
    lVar5 = ZEXT48(&0x16920) + in_r2;
    HvpAquireSpinLock(lVar5);
    uVar3 = 0;
    lVar6 = (uVar2 & 0xffffffff) * 0x38 + ZEXT48(&0x16680) + in_r2;
    plVar1 = (QWORD *)lVar6;
    if ((*(char *)((int)plVar1 + 0x34) == '\x02') &&
       (*(uint *)(plVar1 + 3) == *(uint *)((int)plVar1 + 0x14))) {
      if ((*(byte *)((int)plVar1 + 0x35) & 1) != 0) {
        uVar2 = (QWORD)(*(uint *)(plVar1 + 3) >> 0xc) +
                (QWORD)*(ushort *)((int)plVar1 + 0x36);
        uVar4 = (QWORD)(uint)(((int)(plVar1[1] - *plVar1 >> 2) + 1) * 0x10) +
                (QWORD)*(ushort *)((int)plVar1 + 0x36);
        if (uVar2 < (uVar4 & 0xffffffff)) {
          FUN_00029760(uVar2,0,uVar4 - uVar2);
        }
      }
      uVar4 = plVar1[1];
      uVar2 = ((QWORD)*(uint *)(plVar1 + 3) - 1 >> 0xe & 0x3fffc) + *plVar1;
      if (uVar2 < uVar4) {
        do {
          *(undefined4 *)uVar4 = 0;
          uVar4 = uVar4 - 4;
        } while (uVar2 < uVar4);
        *(uint *)uVar4 = *(uint *)uVar4 | 0x20;
      }
      HvpSetRMCI(0);
      FUN_00029b58((QWORD)*(uint *)((int)plVar1 + 0x1c),lVar6);
      HvpSetRMCI(1);
      if ((*(byte *)((int)plVar1 + 0x35) & 2) == 0) {
        *(undefined *)((int)plVar1 + 0x34) = 0;
      }
      else {
        *(undefined4 *)(plVar1 + 3) = 0;
        *(undefined *)((int)plVar1 + 0x34) = 3;
      }
      uVar3 = 1;
    }
    HvpReleaseSpinLock(lVar5);
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



undefined8 FUN_0002a560(undefined8 param_1,QWORD param_2)

{
  uint uVar1;
  undefined4 uVar2;
  QWORD *plVar3;
  QWORD in_r2;
  QWORD uVar4;
  undefined8 uVar5;
  QWORD lVar6;
  QWORD lVar7;
  uint uVar8;
  undefined4 *puVar9;
  QWORD lVar10;
  QWORD lVar11;
  qword back_chain;
  word local_1b0;
  dword local_50;
  word local_4c;
  word local_40;
  dword local_38;
  dword local_34;
  dword local_30;
  
  uVar4 = __Save_R12_28_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if ((uVar4 & 0xffffffff) < 2) {
    lVar10 = ZEXT48(&0x16920) + in_r2;
    HvpAquireSpinLock(lVar10);
    uVar5 = 0;
    lVar11 = (uVar4 & 0xffffffff) * 0x38 + ZEXT48(&0x16680) + in_r2;
    plVar3 = (QWORD *)lVar11;
    if ((*(char *)((int)plVar3 + 0x34) == '\0') && ((param_2 + 0x120 & 0xfff) + 0x20 < 0x1001)) {
      if ((param_2 & 0xffffffff) == 0) {
        lVar6 = *(QWORD *)(&0x16670 + (int)in_r2) + 0x120;
      }
      else {
        lVar6 = HvpPhysicalToReal(param_2 + 0x120,0x20);
      }
      XeCryptAesKey(&local_1b0,ZEXT48(&0x16710) + in_r2);
      XeCryptAesEcb(&local_1b0,lVar6,&local_50,0);
      XeCryptAesEcb(&local_1b0,lVar6 + 0x10,&local_40,0);
      if (local_50 == local_38) {
        *(dword *)(plVar3 + 2) = local_34;
        lVar6 = FUN_0000057c();
        *plVar3 = lVar6;
        if (lVar6 != 0) {
          uVar8 = *(uint *)lVar6;
          if (((uVar8 & 8) != 0) && ((uVar8 & 0x10) != 0)) {
            plVar3[1] = lVar6;
            uVar8 = *(uint *)lVar6;
            while ((uVar8 & 0x20) == 0) {
              lVar7 = plVar3[1];
              plVar3[1] = lVar7 + 4;
              uVar8 = *(uint *)(lVar7 + 4);
            }
            *(undefined *)((int)plVar3 + 0x35) = 0;
            uVar5 = 1;
            *(int *)((int)plVar3 + 0x14) = ((int)(plVar3[1] - lVar6 >> 2) + 1) * 0x10000;
            if ((*(uint *)(plVar3 + 2) & 0xf0000000) == 0x90000000) {
              *(undefined *)((int)plVar3 + 0x35) = 1;
              *(undefined2 *)((int)plVar3 + 0x36) = (short)(*(uint *)(plVar3 + 2) >> 0xc);
            }
            lVar11 = lVar11 + 0x20;
            puVar9 = (undefined4 *)&local_4c;
            lVar6 = 5;
            do {
              uVar2 = *puVar9;
              puVar9 = puVar9 + 1;
              *(undefined4 *)lVar11 = uVar2;
              lVar11 = lVar11 + 4;
              lVar6 = lVar6 + -1;
            } while (lVar6 != 0);
            *(dword *)(plVar3 + 3) = local_50;
            *(undefined *)((int)plVar3 + 0x34) = 3;
          }
        }
      }
    }
    HvpReleaseSpinLock(lVar10);
    FUN_00000204((QWORD)uVar1);
  }
  else {
    FUN_00000204((QWORD)uVar1);
    uVar5 = 0;
  }
  return uVar5;
}



QWORD FUN_0002a740(int param_1,QWORD param_2,QWORD param_3)

{
  int in_r2;
  QWORD uVar1;
  QWORD uVar2;
  QWORD *puVar3;
  
  if ((*(ushort *)(&0x16720 + in_r2) & 1) == 0) {
    return param_3;
  }
  if (param_1 == 0) {
    return param_3;
  }
  uVar2 = 0;
  puVar3 = (QWORD *)(&0x16728 + in_r2);
  if (*(ushort *)(&0x16722 + in_r2) == 0) {
    return param_3;
  }
  while (((uVar1 = *puVar3, (uVar1 & 1) == 0 ||
          ((uVar1 >> 8 & 0xffffffff) != (param_2 & 0xffffffff))) ||
         ((uVar1 >> 0x28 & 0xfff) != (param_3 & 0xffffffff)))) {
    uVar2 = uVar2 + 1;
    puVar3 = puVar3 + 1;
    if ((QWORD)*(ushort *)(&0x16722 + in_r2) <= (uVar2 & 0xffffffff)) {
      return param_3;
    }
  }
  return *puVar3 >> 0x34;
}



undefined8 FUN_0002a7d0(undefined8 param_1,QWORD param_2,QWORD param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  QWORD in_r2;
  QWORD uVar5;
  int iVar8;
  QWORD uVar6;
  QWORD uVar7;
  QWORD lVar9;
  uint uVar11;
  undefined4 *puVar12;
  QWORD uVar10;
  uint *puVar13;
  QWORD lVar14;
  QWORD lVar15;
  QWORD uVar16;
  QWORD lVar17;
  uint uVar18;
  undefined8 uVar19;
  qword back_chain;
  dword local_260;
  dword local_250;
  dword local_24c;
  dword local_248;
  dword local_244;
  dword local_240;
  dword local_23c;
  dword local_238;
  dword local_234;
  dword local_230;
  dword local_22c;
  dword local_228;
  word local_220;
  word local_c0;
  dword local_ac;
  dword local_a8;
  dword local_a4;
  byte local_9f;
  word local_9e;
  word local_90;
  dword local_7c;
  
  uVar5 = __Save_R12_19_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if (1 < (uVar5 & 0xffffffff)) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc000000d;
  }
  lVar14 = ZEXT48(&0x16920) + in_r2;
  HvpAquireSpinLock(lVar14);
  HvpSetRMCI(0);
  lVar15 = (uVar5 & 0xffffffff) * 0x38 + ZEXT48(&0x16680) + in_r2;
  iVar3 = (int)lVar15;
  if (*(char *)(iVar3 + 0x34) == '\x03') {
    if (*(int *)(iVar3 + 0x18) == 0) {
      uVar19 = 0xffffffffc00000cd;
    }
    else {
      *(int *)(iVar3 + 0x18) = *(int *)(iVar3 + 0x18) + -1;
      if (((param_2 & 3) == 0) &&
         (uVar6 = param_2 & 0xffffffff,
         (QWORD)((uint)uVar6 & 0xfffff000) == (uVar6 + 0x23 & 0xfffffffffffff000))) {
        iVar4 = (int)in_r2;
        if ((param_2 & 0xffffffff) < 0x10000) {
          lVar17 = *(QWORD *)(&0x166f8 + iVar4);
          lVar9 = uVar6 + lVar17;
        }
        else {
          lVar9 = HvpPhysicalToReal(param_2,0x24);
          lVar17 = *(QWORD *)(&0x166f8 + iVar4);
        }
        memcpy(&local_c0,lVar9,0x24);
        uVar11 = 0x1000 - ((uint)param_2 & 0xfff);
        if ((0x23 < uVar11) && ((QWORD)local_9e <= (QWORD)uVar11 - 0x24 >> 2)) {
          param_2 = param_2 + 0x24;
          if ((param_2 & 0xffffffff) < 0x10000) {
            lVar17 = (param_2 & 0xffffffff) + lVar17;
          }
          else {
            lVar17 = HvpPhysicalToReal(param_2,(QWORD)local_9e << 2);
          }
          iVar4 = (int)in_r2;
          memcpy(*(undefined8 *)(&0x16970 + iVar4),lVar17,(QWORD)local_9e << 2);
          XeCryptSha(&local_c0,0x24,*(undefined8 *)(&0x16970 + iVar4),(QWORD)local_9e << 2,
                     0,0,&local_90,0x14);
          lVar15 = lVar15 + 0x20;
          iVar8 = XeCryptMemDiff(lVar15,&local_90,0x14);
          if (iVar8 != 0) {
            uVar19 = 0xffffffffc0000221;
            goto LAB_0002accc;
          }
          puVar12 = (undefined4 *)&local_c0;
          lVar9 = 5;
          do {
            uVar2 = *puVar12;
            puVar12 = puVar12 + 1;
            *(undefined4 *)lVar15 = uVar2;
            lVar15 = lVar15 + 4;
            lVar9 = lVar9 + -1;
          } while (lVar9 != 0);
          if ((param_3 & 3) == 0) {
            uVar6 = FUN_00029968(&local_250,param_3,0,0x2c,1);
            if ((uVar6 & 0xffffffff) == 0) {
LAB_0002a9d4:
              uVar19 = 0xffffffffc0000156;
            }
            else {
              XeCryptAesKey(&local_220,ZEXT48(&0x16710) + in_r2);
              XeCryptAesEcb(&local_220,&local_250,&local_250,0);
              if (((local_250 == 0x48000000) && (local_24c == 0x485645)) &&
                 (local_248 == 0x48000000)) {
                if ((local_244 << 0x10 | local_240 & 0xffff) == local_ac) {
                  if ((((local_234 & 0xff00) << 0x10 | local_23c & 0xffffff) < local_a4) ||
                     (local_a8 < (local_234 << 0x18 | local_238 & 0xffffff))) {
                    uVar19 = 0xffffffffc0000059;
                  }
                  else {
                    uVar6 = 0;
                    if (local_9e != 0) {
                      do {
                        uVar11 = *(uint *)((int)(uVar6 << 2) +
                                          (int)*(undefined8 *)(&0x16970 + iVar4));
                        uVar16 = (QWORD)uVar11;
                        if ((((uVar11 & 3) != 0) ||
                            ((QWORD)uVar11 < (QWORD)*(uint *)(iVar3 + 0x10))) ||
                           ((((QWORD)*(uint *)(iVar3 + 0x14) +
                              (QWORD)*(uint *)(iVar3 + 0x10) & 0xffffffff) <= uVar16 ||
                            (uVar7 = FUN_00029838(uVar16,&local_260), (uVar7 & 0xffffffff) == 0))))
                        goto LAB_0002a9d4;
                        puVar13 = (uint *)((uint)(((QWORD)local_260 & 0x3fffffffffffc0) << 10) |
                                          uVar11 & 0xffff);
                        if (*(byte *)((int)puVar13 + 1) != local_9f) goto LAB_0002acb8;
                        uVar7 = FUN_0002a740(uVar5,(QWORD)local_ac,
                                             (QWORD)*(ushort *)((int)puVar13 + 2));
                        if (((uVar7 & 0xffffffff) < (QWORD)local_228) ||
                           (uVar10 = uVar7 - (QWORD)local_228,
                           (QWORD)local_22c <= (uVar10 & 0xffffffff))) {
LAB_0002aca0:
                          uVar19 = 0xffffffffc0000138;
                          goto LAB_0002accc;
                        }
                        lVar15 = (QWORD)(uint)((int)uVar10 << 2) + param_3 + 0x2c;
                        uVar10 = FUN_00029838(lVar15,&local_260);
                        if (((uVar10 & 0xffffffff) == 0) ||
                           (((local_260 & 1) == 0 || ((local_260 & 0x40000000) == 0))))
                        goto LAB_0002a9d4;
                        iVar8 = *(int *)((local_260 & 0x3fffc0) << 10 | (uint)lVar15 & 0xffff);
                        if (iVar8 == 0) goto LAB_0002aca0;
                        uVar18 = local_230 * 0x10000 + iVar8;
                        if ((*puVar13 & 0xff000000) == 0) {
                          *puVar13 = uVar18;
                        }
                        else {
                          if ((*puVar13 & 0xff000000) != 0x1000000) goto LAB_0002acb8;
                          if (((QWORD)*(uint *)(iVar3 + 0x14) +
                               (QWORD)*(uint *)(iVar3 + 0x10) & 0xffffffff) <
                              (QWORD)uVar11 + 8) goto LAB_0002a9d4;
                          *puVar13 = uVar18 + 0x8000 >> 0x10 | 0x3d600000;
                          if ((uVar16 + 4 & 0xffff) == 0) {
                            uVar10 = FUN_00029838(uVar16 + 8,&local_260);
                            if ((uVar10 & 0xffffffff) == 0) goto LAB_0002a9d4;
                            puVar13 = (uint *)((local_260 & 0x3fffc0) << 10 |
                                              (uint)(uVar16 + 4) & 0xffff);
                          }
                          else {
                            puVar13 = puVar13 + 1;
                          }
                          if ((QWORD)*puVar13 !=
                              ((QWORD)local_9f << 0x10 | 0x2000000 | uVar7 & 0xffffffff))
                          goto LAB_0002acb8;
                          *puVar13 = uVar18 & 0xffff | 0x396b0000;
                        }
                        uVar6 = uVar6 + 1;
                      } while ((uVar6 & 0xffffffff) < (QWORD)local_9e);
                    }
                    uVar19 = 0;
                  }
                }
                else {
                  uVar19 = 0xffffffffc0000225;
                }
              }
              else {
LAB_0002acb8:
                uVar19 = 0xffffffffc000007b;
              }
            }
            goto LAB_0002accc;
          }
        }
      }
      uVar19 = 0xffffffffc0000141;
    }
  }
  else {
    uVar19 = 0xffffffffc000000d;
  }
LAB_0002accc:
  HvpSetRMCI(1);
  if ((int)uVar19 != 0) {
    *(undefined *)(iVar3 + 0x34) = 0xf;
  }
  HvpReleaseSpinLock(lVar14);
  FUN_00000204((QWORD)uVar1);
  return uVar19;
}



undefined8 FUN_0002ad00(void)

{
  byte bVar1;
  QWORD *puVar2;
  QWORD in_r2;
  int iVar3;
  QWORD uVar4;
  undefined8 uVar5;
  QWORD lVar6;
  uint uVar7;
  qword back_chain;
  
  uVar4 = __Save_R12_29_thru_31();
  iVar3 = (int)in_r2;
  if ((uVar4 & 0xffffffff) < 2) {
    HvpAquireSpinLock(ZEXT48(&0x16920) + in_r2);
    uVar5 = 0;
    puVar2 = (QWORD *)(&0x16680 + (int)uVar4 * 0x38 + iVar3);
    if (((*(char *)((int)puVar2 + 0x34) == '\x03') || (*(char *)((int)puVar2 + 0x34) == '\x04')) &&
       (*(int *)(puVar2 + 3) == 0)) {
      if ((*(byte *)((int)puVar2 + 0x35) & 1) == 0) {
        while (*puVar2 <= puVar2[1]) {
          uVar7 = *(uint *)*puVar2;
          *(uint *)*puVar2 = (uVar7 & 2) << 1 | uVar7 & 0xfffffffb;
          *puVar2 = *puVar2 + 4;
        }
      }
      else {
        lVar6 = FUN_000005a8();
        lVar6 = (QWORD)(*(ushort *)((int)puVar2 + 0x36) >> 1) + lVar6;
        uVar7 = (*(uint *)((int)puVar2 + 0x14) >> 0xc) + 1 >> 1;
        while (uVar7 != 0) {
          bVar1 = *(byte *)lVar6;
          uVar7 = uVar7 - 1;
          *(byte *)lVar6 = (bVar1 << 1 | 0xbb) & bVar1;
          lVar6 = lVar6 + 1;
        }
      }
      uVar5 = 1;
      *(undefined *)((int)puVar2 + 0x34) = 0;
    }
    HvpReleaseSpinLock(ZEXT48(&0x16920) + in_r2);
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}



undefined8 FUN_0002ae18(undefined8 param_1,QWORD param_2)

{
  uint uVar1;
  uint uVar2;
  QWORD in_r2;
  QWORD uVar3;
  int iVar4;
  uint *puVar5;
  QWORD lVar6;
  undefined8 uVar7;
  int iVar8;
  uint *puVar9;
  qword back_chain;
  
  uVar3 = __Save_R12_24_thru_31();
  lVar6 = ZEXT48(&0x16920) + in_r2;
  HvpAquireSpinLock(lVar6);
  uVar7 = 0;
  iVar4 = FUN_000005c0();
  HvpSetRMCI(0);
  if (((((((uVar3 & 0xffff) == 0) && ((param_2 & 0xffff) == 0)) &&
        ((uVar3 & 0xffffffff) < (param_2 & 0xffffffff))) &&
       ((uVar1 = (uint)uVar3, (((int)param_2 - 1U ^ uVar1) & 0xf0000000) == 0 &&
        (puVar9 = (uint *)FUN_0000057c(uVar3), puVar9 != (uint *)0x0)))) &&
      ((*puVar9 == 0 || ((*puVar9 & 0x10) != 0)))) &&
     ((puVar5 = (uint *)FUN_0000057c(param_2 - 0x10000), puVar5 != (uint *)0x0 &&
      ((*puVar5 == 0 || ((*puVar5 & 0x20) != 0)))))) {
    iVar8 = 0;
    do {
      if ((*puVar9 & 0xc0000000) != 0) {
        HvpInvalidateCachelines(((QWORD)*puVar9 & 0xffffffc0) << 10,0x10000);
      }
      if ((*puVar9 & 0xfffc0) != 0) {
        uVar2 = *puVar9 >> 5 & 0x7ffe;
        *(ushort *)(uVar2 + iVar4) = *(ushort *)(uVar2 + iVar4) & 0xf7ff;
      }
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
      iVar8 = iVar8 + 1;
    } while (puVar9 <= puVar5);
    if ((uVar1 & 0xf0000000) == 0x90000000) {
      FUN_00029760((QWORD)(uVar1 >> 0xc & 0xffff),0,(QWORD)(uint)(iVar8 * 0x10));
    }
    iVar4 = 0xc;
    in_r2 = ZEXT48(&0x16940) + in_r2;
    do {
      uVar1 = *(uint *)in_r2;
      if (((uVar3 & 0xffffffff) <= (QWORD)uVar1) && ((QWORD)uVar1 < (param_2 & 0xffffffff)))
      {
        *(uint *)in_r2 = 0;
      }
      iVar4 = iVar4 + -1;
      in_r2 = in_r2 + 4;
    } while (iVar4 != 0);
    uVar7 = 1;
  }
  HvpSetRMCI(1);
  HvpReleaseSpinLock(lVar6);
  return uVar7;
}



QWORD FUN_0002afb8(QWORD param_1)
{
  int in_r2;
  undefined8 uVar1;
  
  uVar1 = countLeadingZeros(*(undefined4 *)(&0x16940 + (int)(param_1 << 2) + in_r2));
  return (QWORD)((uint)uVar1 >> 5 & 1) ^ 1;
}



// WARNING: Variable defined which should be unmapped: local_10

QWORD FUN_0002afe0(QWORD param_1,QWORD param_2)

{
  uint uVar1;
  uint uVar2;
  QWORD uVar3;
  int iVar5;
  undefined8 uVar4;
  QWORD lVar6;
  uint *puVar7;
  qword back_chain;
  dword local_20;
  qword local_10;
  qword local_8;
  
  if (((((uint)param_1 + (int)param_2) - 1 ^ (uint)param_1) & 0xffff0000) != 0) {
    _v_MACHINE_CHECK_0();
  }
  if (((param_1 - 0x80000000 & 0xffffffff) < 0x20000000) &&
     ((param_2 & 0xffffffff) <= (-param_1 - 0x60000000 & 0xffffffff))) {
    param_2 = ZEXT48(register0x0000000c) - 0x20;
    uVar3 = FUN_00029838(param_1);
    if ((uVar3 & 0xffffffff) == 0) {
      _v_MACHINE_CHECK_0();
    }
    if (((local_20 & 8) != 0) && ((local_20 & 1) == 0)) {
      return ((QWORD)local_20 & 0xffffffc0) << 10 | 0x8000000000000000 | param_1 & 0xffff;
    }
    _v_MACHINE_CHECK_0();
  }
  _v_MACHINE_CHECK_0();
  puVar7 = (uint *)FUN_0000057c();
  if ((puVar7 == (uint *)0x0) || ((*puVar7 & 0x10) == 0)) {
LAB_0002b158:
    uVar4 = 0;
  }
  else {
    iVar5 = FUN_000005c0();
    uVar1 = *puVar7;
    lVar6 = 0;
    do {
      uVar2 = *puVar7;
      if (((((uVar2 & 2) == 0) || ((uVar2 & 4) == 0)) || ((uVar2 & 0xfffc0) == 0)) ||
         (((QWORD)(uVar2 >> 0x1e) != (param_2 & 0xffffffff) ||
          ((*(ushort *)((int)(lVar6 << 1) + (uVar1 >> 5 & 0x7ffe) + iVar5) & 0x800) == 0))))
      goto LAB_0002b158;
      lVar6 = lVar6 + 1;
      puVar7 = puVar7 + 1;
    } while ((uVar2 >> 5 & 1) == 0);
    uVar4 = 1;
  }
  return uVar4;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_0002b0a0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar4;
  undefined8 uVar3;
  QWORD lVar5;
  uint *puVar6;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  puVar6 = (uint *)FUN_0000057c();
  if ((puVar6 == (uint *)0x0) || ((*puVar6 & 0x10) == 0)) {
LAB_0002b158:
    uVar3 = 0;
  }
  else {
    iVar4 = FUN_000005c0();
    uVar1 = *puVar6;
    lVar5 = 0;
    do {
      uVar2 = *puVar6;
      if (((((uVar2 & 2) == 0) || ((uVar2 & 4) == 0)) || ((uVar2 & 0xfffc0) == 0)) ||
         ((uVar2 >> 0x1e != param_2 ||
          ((*(ushort *)((int)(lVar5 << 1) + (uVar1 >> 5 & 0x7ffe) + iVar4) & 0x800) == 0))))
      goto LAB_0002b158;
      lVar5 = lVar5 + 1;
      puVar6 = puVar6 + 1;
    } while ((uVar2 >> 5 & 1) == 0);
    uVar3 = 1;
  }
  return uVar3;
}



undefined8 FUN_0002b178(undefined8 param_1,QWORD param_2,QWORD param_3)

{
  uint uVar1;
  QWORD in_r2;
  QWORD uVar2;
  uint *puVar4;
  QWORD lVar3;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  QWORD uVar8;
  undefined8 uVar9;
  qword back_chain;
  
  uVar2 = __Save_R12_27_thru_31();
  if ((((((uVar2 & 0xffff) == 0) && ((param_2 & 0xffff) == 0)) && ((param_3 & 0xffff) == 0)) &&
      (((param_3 & 0xffffffff) < 0x2000000 && ((uVar2 + 0x74000000 & 0xffffffff) < 0x2000000)))) &&
     ((param_2 - 0x40000 & 0xffffffff) < 0x1ffc0000)) {
    uVar9 = 0;
    HvpAquireSpinLock(ZEXT48(&0x16920) + in_r2);
    puVar4 = (uint *)FUN_0000057c(uVar2);
    if (puVar4 != (uint *)0x0) {
      lVar3 = FUN_000005c0();
      uVar1 = (uint)param_3 >> 0x10;
      uVar8 = (QWORD)uVar1;
      uVar2 = 0;
      lVar3 = lVar3 + (param_2 >> 0xf & 0x1fffe);
      if (uVar1 != 0) {
        do {
          uVar5 = *(uint *)((int)((uVar2 & 0xffffffff) << 2) + (int)puVar4);
          if ((((uVar5 & 8) != 0) || ((uVar5 & 0xfffc0) != 0)) ||
             ((*(ushort *)((int)((uVar2 & 0xffffffff) << 1) + (int)lVar3) & 0x800) != 0))
          goto LAB_0002b2e4;
          uVar2 = uVar2 + 1;
        } while ((uVar2 & 0xffffffff) < uVar8);
      }
      uVar6 = (uint)param_2 >> 10 & 0xfffc0 | 0x16;
      puVar7 = puVar4;
      uVar5 = 0;
      if (uVar1 != 0) {
        do {
          uVar8 = uVar8 - 1;
          *puVar7 = uVar6;
          *(ushort *)lVar3 = *(ushort *)lVar3 | 0x800;
          lVar3 = lVar3 + 2;
          uVar6 = uVar6 & 0xfff0002f | (uVar6 & 0xffffffc0) + 0x40 & 0xfffc0;
          puVar7 = puVar7 + 1;
          uVar5 = uVar1;
        } while ((uVar8 & 0xffffffff) != 0);
      }
      uVar9 = 1;
      puVar4[uVar5 - 1] = puVar4[uVar5 - 1] | 0x20;
    }
LAB_0002b2e4:
    HvpReleaseSpinLock(ZEXT48(&0x16920) + in_r2);
  }
  else {
    uVar9 = 0;
  }
  return uVar9;
}



undefined8 FUN_0002b300(void)

{
  uint uVar1;
  uint uVar2;
  QWORD in_r2;
  QWORD uVar3;
  QWORD uVar4;
  undefined8 uVar5;
  uint uVar6;
  uint *puVar7;
  qword back_chain;
  
  uVar3 = __Save_R12_28_thru_31();
  if (((uVar3 & 0xffff) == 0) && ((uVar3 + 0x74000000 & 0xffffffff) < 0x2000000)) {
    in_r2 = ZEXT48(&0x16920) + in_r2;
    HvpAquireSpinLock(in_r2);
    uVar4 = FUN_0002b0a0(uVar3,0);
    if ((uVar4 & 0xffffffff) != 0) {
      puVar7 = (uint *)FUN_0000057c(uVar3);
      FUN_000005c0();
      HvpSetRMCI(0);
      do {
        uVar1 = *puVar7;
        *puVar7 = uVar1 | 0xc0000000;
        uVar5 = FUN_000005c0();
        uVar6 = FUN_00029c68(uVar5,(QWORD)(*puVar7 >> 6 & 0x3fff));
        uVar2 = *puVar7;
        uVar6 = (uVar6 & 0x3ff) << 0x14;
        *puVar7 = uVar6 | uVar2 & 0xc00fffff;
        HvpRelocateCacheLines
                  ((QWORD)((uVar2 & 0xfffc0) << 10) | 0x8000000000000000,
                   ((QWORD)uVar6 | (QWORD)uVar2 & 0x3fffffc00fffc0) << 10 |
                   0x8000000000000000,0x200);
        *puVar7 = *puVar7 | 8;
        puVar7 = puVar7 + 1;
      } while ((uVar1 >> 5 & 1) == 0);
      HvpSetRMCI(1);
      HvpReleaseSpinLock(in_r2);
      return 1;
    }
    HvpReleaseSpinLock(in_r2);
  }
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_0002b408(QWORD param_1)

{
  uint uVar1;
  int in_r2;
  QWORD uVar2;
  uint *puVar3;
  undefined *puVar4;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (((param_1 & 0xffff) == 0) && ((param_1 + 0x74000000 & 0xffffffff) < 0x2000000)) {
    puVar4 = &0x16920 + in_r2;
    HvpAquireSpinLock(puVar4);
    uVar2 = FUN_0002b0a0(param_1,3);
    if ((uVar2 & 0xffffffff) != 0) {
      puVar3 = (uint *)FUN_0000057c(param_1);
      do {
        uVar1 = *puVar3;
        *puVar3 = uVar1 & 0xfffffff6 | 1;
        puVar3 = puVar3 + 1;
      } while ((uVar1 >> 5 & 1) == 0);
      HvpReleaseSpinLock(puVar4);
      return 1;
    }
    HvpReleaseSpinLock(puVar4);
  }
  return 0;
}



undefined8 FUN_0002b4c8(void)

{
  uint uVar1;
  QWORD in_r2;
  QWORD uVar2;
  QWORD uVar3;
  int iVar4;
  ushort *puVar5;
  uint *puVar6;
  qword back_chain;
  
  uVar2 = __Save_R12_28_thru_31();
  if (((uVar2 & 0xffff) == 0) && ((uVar2 + 0x74000000 & 0xffffffff) < 0x2000000)) {
    in_r2 = ZEXT48(&0x16920) + in_r2;
    HvpAquireSpinLock(in_r2);
    uVar3 = FUN_0002b0a0(uVar2,3);
    if ((uVar3 & 0xffffffff) != 0) {
      puVar6 = (uint *)FUN_0000057c(uVar2);
      iVar4 = FUN_000005c0();
      puVar5 = (ushort *)((*puVar6 >> 5 & 0x7ffe) + iVar4);
      HvpSetRMCI(0);
      do {
        uVar1 = *puVar6;
        HvpInvalidateCachelines(((QWORD)uVar1 & 0x3fffffffffffc0) << 10,0x10000);
        *puVar5 = *puVar5 & 0xf7ff;
        puVar5 = puVar5 + 1;
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
      } while ((uVar1 >> 5 & 1) == 0);
      HvpSetRMCI(1);
      HvpReleaseSpinLock(in_r2);
      return 1;
    }
    HvpReleaseSpinLock(in_r2);
  }
  return 0;
}



undefined8 FUN_0002b5c0(undefined8 param_1,QWORD param_2)

{
  uint uVar1;
  QWORD in_r2;
  QWORD uVar2;
  uint *puVar3;
  int iVar4;
  uint *puVar5;
  qword back_chain;
  
  uVar2 = __Save_R12_28_thru_31();
  if (((((uVar2 & 0xffff) == 0) && ((param_2 & 0xffff) == 0)) &&
      ((uVar2 + 0x74000000 & 0xffffffff) < 0x2000001)) &&
     (((param_2 + 0x74000000 & 0xffffffff) < 0x2000001 &&
      ((uVar2 & 0xffffffff) < (param_2 & 0xffffffff))))) {
    HvpAquireSpinLock(ZEXT48(&0x16920) + in_r2);
    puVar5 = (uint *)FUN_0000057c(uVar2);
    puVar3 = (uint *)FUN_0000057c(param_2);
    if ((puVar5 != (uint *)0x0) && (puVar3 != (uint *)0x0)) {
      iVar4 = FUN_000005c0();
      HvpSetRMCI(0);
      do {
        if ((*puVar5 & 0xc0000000) != 0) {
          HvpInvalidateCachelines(((QWORD)*puVar5 & 0xffffffc0) << 10,0x10000);
        }
        if ((*puVar5 & 0xfffc0) != 0) {
          uVar1 = *puVar5 >> 5 & 0x7ffe;
          *(ushort *)(uVar1 + iVar4) = *(ushort *)(uVar1 + iVar4) & 0xf7ff;
        }
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      } while (puVar5 <= puVar3);
      HvpSetRMCI(1);
    }
    HvpReleaseSpinLock(ZEXT48(&0x16920) + in_r2);
  }
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x0002b754)

undefined8 FUN_0002b6d8(QWORD param_1,int param_2)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  QWORD lVar3;
  QWORD uVar4;
  int iVar5;
  qword back_chain;
  word local_2f0;
  word local_190;
  dword local_8c;
  word local_58;
  word local_48;
  dword local_1c;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)(in_r2 + 0x10000);
  if (((param_1 & 0xfff) == 0) && (param_2 == 0x174)) {
    if ((*(QWORD *)(&0x16618 + in_r2) & 2) != 0) {
      lVar3 = HvpPhysicalToReal(param_1,0x174);
      memcpy(&local_190,lVar3,0x174);
      if (((local_8c & 8) == 0) || (uVar4 = FUN_00024d58(&local_58), (uVar4 & 0xffffffff) != 0)) {
        iVar5 = FUN_00029a68(&local_190,&local_2f0);
        if (iVar5 < 0) {
          FUN_00000204((QWORD)uVar1);
          return 0xffffffffc8000006;
        }
        XeCryptAesEcb(&local_2f0,&local_48,lVar3 + 0x148,0);
        FUN_00000204((QWORD)uVar1);
        return 0;
      }
    }
    FUN_00000204((QWORD)uVar1);
    uVar2 = 0xffffffffc8000002;
  }
  else {
    FUN_00000204((QWORD)uVar1);
    uVar2 = 0xffffffffc8000004;
  }
  return uVar2;
}



undefined8 FUN_0002b818(undefined8 param_1,QWORD param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined8 in_r2;
  int iVar4;
  undefined8 uVar5;
  int iVar7;
  undefined8 uVar6;
  QWORD uVar8;
  uint *puVar9;
  QWORD uVar10;
  uint uVar11;
  QWORD lVar12;
  qword back_chain;
  word local_90;
  word local_50;
  dword local_3c;
  
  uVar5 = __Save_R12_27_thru_31();
  iVar3 = (int)in_r2;
  uVar1 = *(uint *)(iVar3 + 0x10000);
  uVar10 = *(QWORD *)(&0x166f8 + iVar3);
  if ((param_2 & 0xffffffff) < 0x11) {
    uVar5 = HvpPhysicalToReal(uVar5,param_2);
    memcpy(&local_90,uVar5,(QWORD)(uint)((int)param_2 << 2));
    iVar4 = (int)in_r2;
    uVar11 = 0;
    if ((param_2 & 0xffffffff) != 0) {
      puVar9 = (uint *)&local_90;
      do {
        uVar5 = HvpPhysicalToReal((QWORD)*puVar9,0x1000);
        memcpy((uVar11 << 0xc) + uVar10,uVar5,0x1000);
        iVar4 = (int)in_r2;
        uVar11 = uVar11 + 1;
        puVar9 = puVar9 + 1;
      } while ((QWORD)uVar11 < (param_2 & 0xffffffff));
    }
    uVar11 = *(uint *)((int)uVar10 + 8);
    if (ZEXT48(&0x0fe64) < ((QWORD)uVar11 - 0x19c & 0xffffffff)) {
      uVar5 = 0xffffffffc8004002;
    }
    else {
      uVar8 = (QWORD)*(uint *)((int)uVar10 + 0x10);
      if (uVar8 < (QWORD)uVar11 - 0x184) {
        lVar12 = uVar8 + uVar10;
        uVar8 = lVar12 + 8;
        uVar2 = *(uint *)((int)lVar12 + 0x108);
        if (((QWORD)uVar2 - 0x104 & 0xffffffff) < 0x71) {
          if (uVar2 < 0x174) {
            memset(uVar2 + uVar8,0,0x174 - (QWORD)uVar2);
          }
          XeCryptSha(lVar12 + 0x17cU,
                     ((uVar10 & 0xffffffff) - (lVar12 + 0x17cU & 0xffffffff)) + (QWORD)uVar11,
                     uVar10,(uVar8 & 0xffffffff) - (uVar10 & 0xffffffff),0,0,&local_50,0x14);
          iVar7 = XeCryptMemDiff(lVar12 + 0x164,&local_50,0x14);
          if (iVar7 == 0) {
            iVar7 = FUN_00029a68(uVar8,0);
            if (-1 < iVar7) {
              *(QWORD *)(&0x16670 + iVar4) = uVar8;
              uVar5 = FUN_000298e8(0x40006);
              *(undefined8 *)(&0x16700 + iVar4) = uVar5;
              uVar6 = FUN_000298e8(0x4304);
              uVar5 = 0;
              *(undefined8 *)(&0x166f0 + iVar4) = uVar6;
              goto LAB_0002b9f0;
            }
            uVar5 = 0xffffffffc8004005;
          }
          else {
            uVar5 = 0xffffffffc8004004;
          }
          goto LAB_0002b9c4;
        }
      }
      uVar5 = 0xffffffffc8004003;
    }
  }
  else {
    uVar5 = 0xffffffffc8004001;
    iVar4 = iVar3;
  }
LAB_0002b9c4:
  lVar12 = *(QWORD *)(&0x166f8 + iVar3) + 0x10000;
  memset(*(QWORD *)(&0x166f8 + iVar3),0,0x10000);
  *(QWORD *)(&0x16670 + iVar4) = lVar12;
  *(QWORD *)(&0x16700 + iVar4) = lVar12;
  *(QWORD *)(&0x166f0 + iVar4) = lVar12;
LAB_0002b9f0:
  FUN_00000204((QWORD)uVar1);
  return uVar5;
}



undefined8 FUN_0002ba08(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  QWORD in_r2;
  int iVar1;
  int iVar2;
  QWORD lVar3;
  undefined8 uVar4;
  qword back_chain;
  
  iVar2 = __Save_R12_28_thru_31();
  iVar1 = (int)in_r2;
  HvpAquireSpinLock(ZEXT48(&0x16920) + in_r2);
  if (iVar2 == 0) {
    lVar3 = *(QWORD *)(&0x166f8 + iVar1) + 0x10000;
    memset(*(QWORD *)(&0x166f8 + iVar1),0,0x10000);
    *(QWORD *)(&0x16670 + iVar1) = lVar3;
    *(QWORD *)(&0x16700 + iVar1) = lVar3;
    *(QWORD *)(&0x166f0 + iVar1) = lVar3;
    uVar4 = 0;
  }
  else {
    if (iVar2 == 1) {
      uVar4 = FUN_0002b818(param_2,param_3);
    }
    else {
      if (iVar2 == 2) {
        uVar4 = 0;
        *(uint *)((int)*(undefined8 *)(&0x166f8 + iVar1) + 0x10) =
             *(uint *)((int)*(undefined8 *)(&0x166f8 + iVar1) + 0x10) | 0x8e050000;
      }
      else {
        if (iVar2 == 3) {
          if ((*(QWORD *)(&0x16700 + iVar1) == 0) ||
             (iVar1 = (int)*(QWORD *)(&0x16700 + iVar1),
             *(int *)(iVar1 + 8) != *(int *)(iVar1 + 4))) {
            uVar4 = 0xffffffffc8004006;
          }
          else {
            uVar4 = 0;
            *(undefined4 *)(iVar1 + 8) = (int)param_2;
          }
        }
        else {
          uVar4 = 0xffffffffc8004001;
        }
      }
    }
  }
  HvpReleaseSpinLock(ZEXT48(&0x16920) + in_r2);
  return uVar4;
}



QWORD FUN_0002bb10(void)

{
  QWORD uVar1;
  qword back_chain;
  qword local_8;
  
  uVar1 = FUN_00002bb8();
  return uVar1 & 0xffffffff;
}



undefined8 FUN_0002bb38(void)

{
  return 0xffffffffc8004007;
}



QWORD * FUN_0002bb48(QWORD param_1)

{
  int in_r2;
  QWORD uVar1;
  QWORD *puVar2;
  
  uVar1 = 0;
  puVar2 = (QWORD *)(&0x16728 + in_r2);
  if (*(ushort *)(&0x16722 + in_r2) != 0) {
    do {
      if ((*puVar2 >> 2 & 0x3f) == (param_1 & 0xffffffff)) {
        return puVar2;
      }
      uVar1 = uVar1 + 1;
      puVar2 = puVar2 + 1;
    } while ((uVar1 & 0xffffffff) < (QWORD)*(ushort *)(&0x16722 + in_r2));
  }
  return (QWORD *)0;
}



undefined8 FUN_0002bb98(void)

{
  int in_r2;
  QWORD uVar1;
  QWORD *puVar2;
  
  uVar1 = (QWORD)*(ushort *)(&0x16722 + in_r2);
  if (*(ushort *)(&0x16722 + in_r2) != 0) {
    puVar2 = (QWORD *)(&0x16728 + in_r2);
    do {
      uVar1 = uVar1 - 1;
      *puVar2 = *puVar2 & 0xfffffffffffffffe;
      puVar2 = puVar2 + 1;
    } while ((uVar1 & 0xffffffff) != 0);
  }
  *(ushort *)(&0x16720 + in_r2) = *(ushort *)(&0x16720 + in_r2) & 0xfffe;
  return 0;
}



undefined8 FUN_0002bbe8(uint param_1)

{
  undefined8 uVar1;
  QWORD *puVar2;
  qword back_chain;
  qword local_8;
  
  if (param_1 < 0x3f) {
    puVar2 = (QWORD *)FUN_0002bb48();
    if (puVar2 == (QWORD *)0x0) {
      uVar1 = 0xffffffffc8004009;
    }
    else {
      uVar1 = 0;
      *puVar2 = *puVar2 | 1;
    }
  }
  else {
    uVar1 = 0xffffffffc8004001;
  }
  return uVar1;
}



undefined8 FUN_0002bc48(uint param_1)

{
  undefined8 uVar1;
  QWORD *puVar2;
  qword back_chain;
  qword local_8;
  
  if (param_1 < 0x3f) {
    puVar2 = (QWORD *)FUN_0002bb48();
    if (puVar2 == (QWORD *)0x0) {
      uVar1 = 0xffffffffc8004009;
    }
    else {
      uVar1 = 0;
      *puVar2 = *puVar2 & 0xfffffffffffffffe;
    }
  }
  else {
    uVar1 = 0xffffffffc8004001;
  }
  return uVar1;
}



undefined8 FUN_0002bca8(undefined8 param_1,QWORD param_2,QWORD param_3,QWORD param_4)

{
  ushort uVar1;
  int iVar2;
  undefined *puVar3;
  QWORD in_r2;
  undefined8 uVar4;
  QWORD uVar5;
  qword back_chain;
  dword local_1c0;
  dword local_1bc;
  dword local_1b8;
  dword local_1b4;
  dword local_1b0;
  dword local_19c;
  dword local_198;
  word local_190;
  
  uVar4 = __Save_R12_27_thru_31();
  iVar2 = (int)in_r2;
  if ((*(ushort *)(&0x16720 + iVar2) & 2) == 0) {
    if (*(ushort *)(&0x16722 + iVar2) < 0x3f) {
      if ((((param_2 & 0xffffffff) < 0x3f) && ((param_3 & 0xffffffff) < 0x1000)) &&
         ((param_4 & 0xffffffff) < 0x1000)) {
        HvpSetRMCI(0);
        uVar5 = FUN_00029968(&local_1c0,uVar4,0,0x2c,1);
        HvpSetRMCI(1);
        if ((uVar5 & 0xffffffff) != 0) {
          XeCryptAesKey(&local_190,ZEXT48(&0x16710) + in_r2);
          XeCryptAesEcb(&local_190,&local_1c0,&local_1c0,0);
          if (((((local_1c0 == 0x48000000) && (local_1bc == 0x485645)) &&
               ((local_1b8 == 0x48000000 &&
                (((QWORD)local_198 <= (param_3 & 0xffffffff) &&
                 ((param_3 & 0xffffffff) < (QWORD)(local_19c + local_198))))))) &&
              ((QWORD)local_198 <= (param_4 & 0xffffffff))) &&
             ((param_4 & 0xffffffff) < (QWORD)(local_19c + local_198))) {
            uVar1 = *(ushort *)(&0x16722 + iVar2);
            puVar3 = &0x16728 + iVar2;
            *(ushort *)(&0x16722 + iVar2) = uVar1 + 1;
            uVar5 = (param_3 & 0xfff) << 0x28;
            iVar2 = (int)((QWORD)(int)(uint)uVar1 << 3);
            *(QWORD *)(puVar3 + iVar2) =
                 param_4 << 0x34 | *(QWORD *)(puVar3 + iVar2) & 0xffffffffff | uVar5;
            *(QWORD *)(puVar3 + iVar2) =
                 (((QWORD)(int)(local_1b4 << 0x10) & 0xffffffffU |
                  (QWORD)(local_1b0 & 0xffff)) << 6 | param_2 & 0x3f) << 2 |
                 param_4 << 0x34 | uVar5;
            return 0;
          }
        }
      }
      uVar4 = 0xffffffffc8004001;
    }
    else {
      uVar4 = 0xffffffffc8004008;
    }
  }
  else {
    uVar4 = 0xffffffffc8004007;
  }
  return uVar4;
}



undefined8 FUN_0002be60(undefined8 param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  QWORD in_r2;
  int iVar1;
  int iVar3;
  undefined8 uVar2;
  ushort uVar4;
  qword back_chain;
  
  iVar3 = __Save_R12_26_thru_31();
  iVar1 = (int)in_r2;
  HvpAquireSpinLock(ZEXT48(&0x16920) + in_r2);
  if (iVar3 == 0) {
    uVar2 = FUN_0002bb98();
  }
  else {
    if (iVar3 == 1) {
      uVar4 = *(ushort *)(&0x16720 + iVar1) | 2;
    }
    else {
      if (iVar3 != 2) {
        if (iVar3 == 3) {
          uVar2 = 0;
          *(ushort *)(&0x16720 + iVar1) = *(ushort *)(&0x16720 + iVar1) & 0xfffe;
        }
        else {
          if (iVar3 == 4) {
            uVar2 = FUN_0002bbe8((QWORD)param_2);
          }
          else {
            if (iVar3 == 5) {
              uVar2 = FUN_0002bc48((QWORD)param_2);
            }
            else {
              if (iVar3 == 6) {
                uVar2 = FUN_0002bca8((QWORD)param_2,(QWORD)param_3,(QWORD)param_4,
                                     (QWORD)param_5);
              }
              else {
                uVar2 = 0xffffffffc8004001;
              }
            }
          }
        }
        goto LAB_0002bf4c;
      }
      uVar4 = *(ushort *)(&0x16720 + iVar1) | 1;
    }
    uVar2 = 0;
    *(ushort *)(&0x16720 + iVar1) = uVar4;
  }
LAB_0002bf4c:
  HvpReleaseSpinLock(ZEXT48(&0x16920) + in_r2);
  return uVar2;
}



undefined8
FUN_0002bf60(undefined8 param_1,QWORD param_2,QWORD param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6)

{
  int iVar3;
  QWORD uVar1;
  undefined8 uVar2;
  QWORD lVar4;
  qword back_chain;
  dword local_50;
  
  iVar3 = __Save_R12_25_thru_31();
  if (((param_2 & 0xffffffff) < (QWORD)*(uint *)(iVar3 + 0x10)) ||
     (((QWORD)*(uint *)(iVar3 + 0x14) + (QWORD)*(uint *)(iVar3 + 0x10) & 0xffffffff) <
      (param_2 & 0xffffffff) + (param_3 & 0xffffffff))) {
LAB_0002c05c:
    uVar2 = 0;
  }
  else {
    lVar4 = 0x1000;
    if ((*(byte *)(iVar3 + 0x35) & 1) == 0) {
      lVar4 = 0x10000;
    }
    while ((param_3 & 0xffffffff) != 0) {
      uVar1 = FUN_00029838(param_2,&local_50);
      if ((uVar1 & 0xffffffff) == 0) goto LAB_0002c05c;
      uVar1 = (lVar4 + param_2 & ~(lVar4 - 1U)) - param_2;
      if ((param_3 & 0xffffffff) < (uVar1 & 0xffffffff)) {
        uVar1 = param_3;
      }
      iVar3 = func_0x000007b8((QWORD)local_50,param_2,
                              ((QWORD)local_50 & 0x3fffffffffffc0) << 10 | 0x8000000000000000 |
                              param_2 & 0xffff,uVar1,param_5,param_6,param_4);
      if (iVar3 == 0) goto LAB_0002c05c;
      param_3 = param_3 - uVar1;
      param_2 = uVar1 + param_2;
    }
    uVar2 = 1;
  }
  return uVar2;
}



// WARNING: Removing unreachable block (ram,0x0002c0e0)
// WARNING: Removing unreachable block (ram,0x0002c0ec)
// WARNING: Removing unreachable block (ram,0x0002c0f8)

undefined8 FUN_0002c068(undefined8 param_1,uint *param_2)

{
  int *piVar1;
  QWORD in_r2;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  undefined8 uVar6;
  int iVar7;
  uint uVar8;
  qword back_chain;
  dword local_40;
  
  iVar2 = __Save_R12_27_thru_31();
  uVar6 = 0;
  HvpSetRMCI(0);
  iVar7 = 0x1000;
  if ((*(byte *)(iVar2 + 0x35) & 1) == 0) {
    iVar7 = 0x10000;
  }
  uVar4 = *(uint *)(iVar2 + 0x10);
  uVar8 = (*(int *)(iVar2 + 0x14) + uVar4) - 0xc0;
  while (uVar4 <= uVar8) {
    FUN_00029838(uVar8,&local_40);
    uVar4 = *(uint *)(iVar2 + 0x10);
    uVar8 = uVar8 - iVar7;
  }
  if (*(uint *)(iVar2 + 0x10) <= uVar8) {
    piVar1 = (int *)(uVar8 & 0xffff);
    piVar3 = piVar1 + 0x30;
    piVar5 = piVar1;
    if (piVar1 < piVar3) {
      do {
        if (*piVar5 != 0) break;
        piVar5 = piVar5 + 1;
      } while (piVar5 < piVar3);
      if (piVar5 < piVar3) goto LAB_0002c1c0;
    }
    memcpy(piVar1,ZEXT48(FUN_000103f4) + in_r2,0xc0);
    *param_2 = uVar8;
    uVar6 = 1;
    *(undefined *)((int)param_2 + 0xf) = 0x19;
    *(undefined *)((int)param_2 + 7) = 0x17;
    param_2[2] = uVar8 + 0x5c;
    param_2[1] = 0x1717;
    param_2[3] = 0x80001919;
    *(uint *)(iVar2 + 0x1c) = uVar8;
  }
LAB_0002c1c0:
  HvpSetRMCI(1);
  return uVar6;
}



undefined8 FUN_0002c1d8(uint param_1,uint param_2,uint *param_3,int param_4,int param_5)

{
  uint uVar1;
  
  uVar1 = param_2 + param_4;
  if (((((param_1 & 8) == 8) && ((param_1 & 1) == 1)) && ((param_1 & 2) == 0)) &&
     ((param_1 & 0x40000000) == 0x40000000)) {
    if (param_2 < uVar1) {
      do {
        if (*param_3 == 0x4e800020) {
          *param_3 = param_5 - param_2 & 0x3fffffc | 0x48000000;
        }
        param_2 = param_2 + 4;
        param_3 = param_3 + 1;
      } while (param_2 < uVar1);
    }
    return 1;
  }
  return 0;
}



undefined8 FUN_0002c268(uint param_1,uint param_2,uint *param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_2 + param_4;
  if (((((param_1 & 8) == 8) && ((param_1 & 1) == 1)) && ((param_1 & 2) == 0)) &&
     ((param_1 & 0x40000000) == 0x40000000)) {
    uVar2 = param_6 - param_2 & 0x3fffffc | 0x48000000;
    if (param_2 < uVar1) {
      do {
        if (*param_3 == uVar2) {
          *param_3 = param_5 - param_2 & 0x3fffffc | 0x48000000;
        }
        param_2 = param_2 + 4;
        uVar2 = uVar2 - 4;
        param_3 = param_3 + 1;
      } while (param_2 < uVar1);
    }
    return 1;
  }
  return 0;
}



QWORD FUN_0002c300(undefined8 param_1,QWORD param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  QWORD in_r2;
  int iVar4;
  QWORD uVar3;
  QWORD uVar5;
  QWORD uVar6;
  qword back_chain;
  dword local_f0;
  word local_e0;
  dword local_3c;
  
  iVar4 = __Save_R12_26_thru_31();
  uVar5 = 0;
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  do {
    uVar2 = *(uint *)((int)(uVar5 << 2) + param_3);
    uVar6 = (QWORD)uVar2;
    if (uVar2 == 0) break;
    if ((uVar6 <= (param_2 & 0xffffffff)) && ((param_2 & 0xffffffff) < (uVar6 + 0x50 & 0xffffffff)))
    goto LAB_0002c47c;
    uVar5 = uVar5 + 1;
  } while ((uVar5 & 0xffffffff) < 2);
  if ((((((QWORD)*(uint *)(iVar4 + 0x10) <= (param_2 & 0xffffffff)) &&
        ((param_2 & 0xffffffff) <
         ((QWORD)*(uint *)(iVar4 + 0x14) + (QWORD)*(uint *)(iVar4 + 0x10) & 0xffffffff))) &&
       (uVar6 = FUN_00029838(param_2,&local_f0), (uVar6 & 0xffffffff) != 0)) &&
      (((local_f0 & 8) == 8 && ((local_f0 & 1) == 1)))) &&
     (((local_f0 & 2) == 0 &&
      (((local_f0 & 0x40000000) == 0x40000000 &&
       (uVar2 = *(uint *)((local_f0 & 0x3fffc0) << 10 | (uint)param_2 & 0xffff),
       (uVar2 & 0xfc000003) == 0xf8000000)))))) {
    uVar6 = 0;
    do {
      if (uVar2 == *(uint *)((int)(uVar6 << 2) + (int)(ZEXT48(__Save_R12_14_thru_31_) + in_r2)))
      break;
      uVar6 = uVar6 + 1;
    } while ((uVar6 & 0xffffffff) < 0x12);
    if ((uVar6 & 0xffffffff) < 0x12) {
      uVar6 = param_2 - (uint)((int)uVar6 << 2);
      uVar3 = FUN_00029968(&local_e0,uVar6,iVar4,0xa4,1);
      if (((uVar3 & 0xffffffff) != 0) &&
         (iVar4 = XeCryptMemDiff(&local_e0,ZEXT48(__Save_R12_14_thru_31_) + in_r2,0xa4), iVar4 == 0)
         ) {
        if ((uVar5 & 0xffffffff) < 2) {
          *(undefined4 *)((int)(uVar5 << 2) + param_3) = (int)uVar6;
        }
LAB_0002c47c:
        FUN_00000204((QWORD)uVar1);
        return uVar6;
      }
    }
  }
  FUN_00000204((QWORD)uVar1);
  return 0;
}



// WARNING: Could not reconcile some variable overlaps

undefined8 FUN_0002c4a0(undefined8 param_1,QWORD *param_2,undefined8 param_3,QWORD param_4)

{
  uint uVar1;
  QWORD in_r2;
  int iVar4;
  QWORD uVar2;
  undefined8 uVar3;
  uint uVar5;
  QWORD uVar6;
  int *piVar7;
  QWORD uVar8;
  QWORD uVar9;
  uint *puVar10;
  QWORD lVar11;
  QWORD uVar12;
  qword back_chain;
  qword local_60;
  
  iVar4 = __Save_R12_22_thru_31();
  uVar6 = *param_2;
  local_60._4_4_ = (uint)uVar6;
  local_60._0_4_ = (uint)(uVar6 >> 0x20);
  uVar12 = (QWORD)local_60._0_4_;
  uVar8 = (local_60._4_4_ >> 6 & 0xfffffc) + uVar12;
  uVar9 = ((local_60._4_4_ & 0xff) << 2) + uVar12;
  if (((((uVar6 & 0x300000000) != 0) ||
       ((QWORD)local_60._0_4_ < (QWORD)*(uint *)(iVar4 + 0x10))) ||
      (((QWORD)*(uint *)(iVar4 + 0x14) + (QWORD)*(uint *)(iVar4 + 0x10) & 0xffffffff) <
       (uVar8 & 0xffffffff))) ||
     (((uVar9 & 0xffffffff) < uVar12 || ((uVar8 & 0xffffffff) < (uVar9 & 0xffffffff))))) {
    return 0;
  }
  if ((1 < (local_60._4_4_ & 0xff)) &&
     ((local_60._4_4_ >> 0x1e != 0 && (local_60._4_4_ >> 0x1e != 2)))) {
    uVar2 = FUN_00029838(uVar12,&local_60);
    if ((uVar2 & 0xffffffff) == 0) {
      return 0;
    }
    if ((local_60._0_4_ & 8) != 8) {
      return 0;
    }
    if ((local_60._0_4_ & 1) != 1) {
      return 0;
    }
    if ((uVar6 & 0x200000000) != 0) {
      return 0;
    }
    if ((local_60._0_4_ & 0x40000000) != 0x40000000) {
      return 0;
    }
    piVar7 = (int *)((uint)(((QWORD)local_60._0_4_ & 0xffffffc0) << 10) |
                    local_60._0_4_ & 0xffff);
    if (*piVar7 == 0x7d8802a6) {
      uVar12 = uVar12 + 4;
      puVar10 = (uint *)(piVar7 + 1);
      uVar5 = (uint)uVar12;
      if ((uVar12 & 0xfff) == 0) {
        uVar2 = FUN_00029838(uVar12,&local_60);
        if ((uVar2 & 0xffffffff) == 0) {
          return 0;
        }
        if ((local_60._0_4_ & 8) != 8) {
          return 0;
        }
        if ((local_60._0_4_ & 1) != 1) {
          return 0;
        }
        if ((uVar6 & 0x200000000) != 0) {
          return 0;
        }
        if ((local_60._0_4_ & 0x40000000) != 0x40000000) {
          return 0;
        }
        puVar10 = (uint *)((local_60._0_4_ & 0x3fffc0) << 10 | uVar5 & 0xffff);
      }
      uVar1 = *puVar10;
      if (uVar1 == 0x9181fff8) {
        uVar5 = ((int)param_4 - uVar5) + 0x48;
        uVar6 = param_4 + 0xac;
        uVar12 = 0;
        in_r2 = ZEXT48(FUN_0002c1d8) + in_r2;
LAB_0002c658:
        *puVar10 = uVar5 & 0x3fffffc | 0x48000001;
        uVar3 = FUN_0002bf60(iVar4,uVar9,uVar8 - uVar9,in_r2,uVar6 & 0xffffffff,uVar12);
        return uVar3;
      }
      if ((uVar1 & 0xfc000003) == 0x48000001) {
        lVar11 = (-(QWORD)(uVar1 & 0x2000000) | (QWORD)(uVar1 & 0x3fffffc)) + uVar12;
        uVar12 = FUN_0002c300(iVar4,lVar11,param_3);
        if ((uVar12 & 0xffffffff) != 0) {
          lVar11 = lVar11 - uVar12;
          in_r2 = ZEXT48(FUN_0002c268) + in_r2;
          uVar5 = ((int)lVar11 - uVar5) + (int)param_4;
          uVar6 = lVar11 + param_4 + 0x5c;
          uVar12 = lVar11 + uVar12 + 0x50 & 0xffffffff;
          goto LAB_0002c658;
        }
      }
    }
  }
  return 1;
}



undefined8
FUN_0002c700(undefined8 param_1,undefined8 param_2,QWORD param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6)

{
  uint uVar1;
  uint uVar4;
  QWORD uVar2;
  undefined8 uVar3;
  uint uVar5;
  qword back_chain;
  
  uVar5 = (uint)param_4;
  uVar4 = __Save_R12_27_thru_31();
  uVar1 = *(uint *)((int)param_5 + 0x1c);
  if (((((uVar4 & 8) == 8) && ((uVar4 & 1) == 1)) && ((uVar4 & 2) == 2)) &&
     ((uVar4 & 0x40000000) == 0)) {
    uVar5 = uVar5 >> 3;
    while (uVar5 != 0) {
      uVar2 = FUN_0002c4a0(param_5,param_3,param_6,(QWORD)uVar1);
      if ((uVar2 & 0xffffffff) == 0) goto LAB_0002c788;
      uVar5 = uVar5 - 1;
      param_3 = param_3 + 8;
    }
    uVar3 = 1;
  }
  else {
LAB_0002c788:
    uVar3 = 0;
  }
  return uVar3;
}



undefined8 FUN_0002c798(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  QWORD in_r2;
  undefined8 uVar1;
  qword back_chain;
  dword local_30;
  word local_2c;
  
  uVar1 = __Save_R12_29_thru_31();
  HvpSetRMCI(0);
  uVar1 = FUN_0002bf60(uVar1,param_2,param_3,ZEXT48(FUN_0002c700) + in_r2,uVar1,&local_30);
  HvpSetRMCI(1);
  return uVar1;
}



QWORD FUN_0002c800(undefined8 param_1,QWORD param_2)

{
  int iVar1;
  QWORD in_r2;
  QWORD uVar2;
  QWORD uVar3;
  undefined8 uVar4;
  QWORD lVar5;
  QWORD lVar6;
  qword back_chain;
  
  uVar2 = __Save_R12_28_thru_31();
  if ((uVar2 & 0xffffffff) < 2) {
    lVar5 = ZEXT48(&0x16920) + in_r2;
    HvpAquireSpinLock(lVar5);
    uVar3 = 0;
    lVar6 = (uVar2 & 0xffffffff) * 0x38 + ZEXT48(&0x16680) + in_r2;
    iVar1 = (int)lVar6;
    if (((*(char *)(iVar1 + 0x34) == '\x03') && ((param_2 & 7) == 0)) &&
       ((param_2 & 0xfff) + 0x10 < 0x1001)) {
      uVar4 = HvpPhysicalToReal(param_2,0x10);
      uVar3 = FUN_0002c068(lVar6,uVar4);
      if ((uVar3 & 0xffffffff) != 0) {
        *(undefined *)(iVar1 + 0x34) = 4;
      }
    }
    HvpReleaseSpinLock(lVar5);
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



QWORD FUN_0002c8b8(undefined8 param_1,QWORD param_2,QWORD param_3)

{
  int iVar1;
  QWORD in_r2;
  QWORD uVar2;
  QWORD lVar3;
  QWORD uVar4;
  QWORD lVar5;
  qword back_chain;
  
  uVar2 = __Save_R12_27_thru_31();
  if ((uVar2 & 0xffffffff) < 2) {
    lVar3 = ZEXT48(&0x16920) + in_r2;
    HvpAquireSpinLock(lVar3);
    uVar4 = 0;
    lVar5 = (uVar2 & 0xffffffff) * 0x38 + ZEXT48(&0x16680) + in_r2;
    iVar1 = (int)lVar5;
    if ((((*(char *)(iVar1 + 0x34) != '\x04') || ((param_2 & 7) != 0)) || ((param_3 & 7) != 0)) ||
       ((((param_2 & 0xffffffff) < (QWORD)*(uint *)(iVar1 + 0x10) ||
         (((QWORD)*(uint *)(iVar1 + 0x14) + (QWORD)*(uint *)(iVar1 + 0x10) & 0xffffffff) <
          (param_2 & 0xffffffff) + (param_3 & 0xffffffff))) ||
        (uVar4 = FUN_0002c798(lVar5,param_2,param_3), (uVar4 & 0xffffffff) == 0)))) {
      *(undefined *)(iVar1 + 0x34) = 0xf;
    }
    HvpReleaseSpinLock(lVar3);
    return uVar4;
  }
  return 0;
}



// WARNING: Removing unreachable block (ram,0x0002ccb0)
// WARNING: Removing unreachable block (ram,0x0002ccc0)
// WARNING: Removing unreachable block (ram,0x0002ccc8)
// WARNING: Removing unreachable block (ram,0x0002ccd8)
// WARNING: Removing unreachable block (ram,0x0002cce0)
// WARNING: Removing unreachable block (ram,0x0002cd64)
// WARNING: Removing unreachable block (ram,0x0002cd70)

undefined8 FUN_0002c990(undefined8 param_1,QWORD param_2,QWORD param_3,QWORD param_4)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  dword dVar4;
  QWORD *puVar5;
  QWORD in_r2;
  QWORD uVar6;
  QWORD lVar7;
  int iVar8;
  QWORD *puVar9;
  int iVar10;
  dword *pdVar11;
  uint uVar12;
  undefined4 *puVar14;
  QWORD uVar13;
  QWORD lVar15;
  QWORD lVar16;
  uint *puVar17;
  QWORD uVar18;
  undefined8 uVar19;
  QWORD lVar20;
  qword back_chain;
  word local_4b0;
  word local_350;
  word local_1f0;
  dword local_f0;
  dword local_ec;
  dword local_e8;
  word local_e4;
  dword local_d0;
  word local_c0;
  dword local_b8;
  dword local_b4;
  dword local_98;
  dword local_80;
  word local_70;
  dword local_5c;
  
  uVar6 = __Save_R12_23_thru_31();
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  if (1 < (uVar6 & 0xffffffff)) {
    FUN_00000204((QWORD)uVar2);
    return 0xffffffffc000000d;
  }
  lVar15 = ZEXT48(&0x16920) + in_r2;
  HvpAquireSpinLock(lVar15);
  if ((param_2 & 0xffffffff) == 0) {
    lVar7 = *(QWORD *)(&0x16670 + (int)in_r2);
  }
  else {
    lVar7 = HvpPhysicalToReal(param_2,0x174);
  }
  uVar18 = (QWORD)((uint)param_2 & 0xfff);
  if (uVar18 + 0x104 < 0x1001) {
    memcpy(&local_1f0,lVar7,0x104);
    if ((local_f0 < 0x104) || (0x174 < local_f0)) {
      uVar19 = 0xffffffffc000007b;
      goto LAB_0002d0dc;
    }
    if ((uVar18 + (QWORD)local_f0 & 0xffffffff) < 0x1001) {
      memcpy(&local_ec,lVar7 + 0x104,(QWORD)local_f0 - 0x104);
      memset((int)&local_1f0 + local_f0,0,0x174 - local_f0);
      if (((local_ec & 0xc0000000) != 0) &&
         ((iVar8 = FUN_000298e8(0x40006), iVar8 == 0 || (*(int *)(iVar8 + 0xc) != 0x58480880)))) {
        XeCryptSha(&local_1f0,0x100,0,0,0,0,&local_70,0x14);
        uVar18 = FUN_0002d370(&local_70,1);
        if ((uVar18 & 0xffffffff) != 0) {
          uVar19 = 0xffffffffc8003004;
          goto LAB_0002d0dc;
        }
      }
      uVar19 = FUN_00029a68(&local_1f0,&local_350);
      if ((int)uVar19 < 0) goto LAB_0002d0dc;
      if ((param_4 & 0xffffffff) == 0) {
        uVar19 = 0;
        goto LAB_0002d0dc;
      }
      lVar16 = (uVar6 & 0xffffffff) * 0x38 + ZEXT48(&0x16680) + in_r2;
      puVar5 = (QWORD *)lVar16;
      if (*(char *)((int)puVar5 + 0x34) != '\0') {
        uVar19 = 0xffffffffc000012b;
        goto LAB_0002d0dc;
      }
      iVar8 = (int)in_r2;
      iVar10 = (int)*(undefined8 *)(&0x162d0 + iVar8);
      uVar12 = local_ec;
      if (((param_2 & 0xffffffff) != 0) || ((local_ec & 0x4000000) == 0)) goto LAB_0002cbe8;
      puVar9 = (QWORD *)FUN_000298e8(0x4004);
      if (puVar9 == (QWORD *)0x0) {
        uVar19 = 0xffffffffc0000225;
        goto LAB_0002d0dc;
      }
      uVar6 = *(QWORD *)(iVar10 + 0x630) & *puVar9;
      if (puVar9[1] == 0) {
        if (uVar6 != 0) {
LAB_0002cbe8:
          if ((*(uint *)(iVar10 + 0x614) & 0x100) == 0) {
            uVar12 = uVar12 & 0xf7ffffff;
            puVar17 = (uint *)(lVar7 + 0x104);
            *puVar17 = *puVar17 & 0xf7ffffff;
            local_ec = uVar12;
          }
          if (((uVar12 & 0x8000000) != 0) &&
             ((iVar10 = FUN_000298e8(0x40006), iVar10 == 0 ||
              (uVar6 = FUN_0000b168((QWORD)*(uint *)(iVar10 + 0xc),0), uVar12 = local_ec,
              (uVar6 & 0xffffffff) == 0)))) {
            uVar19 = 0xffffffffc8005003;
            goto LAB_0002d0dc;
          }
          if ((((uVar12 & 8) != 0) ||
              (iVar10 = XeCryptMemDiff(ZEXT48(&0x108a8) + in_r2,&local_b8,0x10), iVar10 == 0))
             && (uVar6 = FUN_00024d58(&local_b8), (uVar6 & 0xffffffff) == 0)) {
            uVar19 = 0xffffffffc0050002;
            goto LAB_0002d0dc;
          }
          if (((local_ec & 6) != 0) && ((local_ec & 6) != 6)) {
            uVar19 = 0xffffffffc0000156;
            goto LAB_0002d0dc;
          }
          if ((*(ushort *)(&0x16a94 + (int)in_r2) & 4) == 0) {
            if ((local_ec & 0x10) == 0) {
LAB_0002cd4c:
              uVar1 = *(ushort *)((int)*(undefined8 *)(&0x162d0 + iVar8) + 0x602);
              uVar12 = (uint)uVar1;
              if (uVar1 == 0x102) {
                uVar12 = 0x1ff;
              }
              if (((local_ec & 0x20000000) == 0) &&
                 ((3 < uVar12 >> 8 ||
                  (((uVar12 & 0xff) << (QWORD)((uVar12 >> 8) << 3) & local_80) == 0)))) {
                uVar19 = 0xffffffffc0050001;
                goto LAB_0002d0dc;
              }
              uVar19 = 0;
              uVar6 = 0;
              do {
                if ((*(int *)(&0x16940 + (int)in_r2 + (int)(uVar6 << 2)) != 0) &&
                   ((1 << uVar6 + 8 & local_ec) != 0)) {
                  uVar19 = 0xffffffffc0000105;
                  goto LAB_0002d0dc;
                }
                uVar6 = uVar6 + 1;
              } while ((uVar6 & 0xffffffff) < 0xc);
              *(undefined4 *)((int)puVar5 + 0x14) = (int)param_3;
              *(undefined4 *)(puVar5 + 3) = 0;
              *(undefined *)((int)puVar5 + 0x35) = 0;
              *(dword *)(puVar5 + 2) = local_e8;
              if ((local_ec & 0x10000000) != 0) {
                *(undefined *)((int)puVar5 + 0x35) = 1;
              }
              if (local_d0 == 0) {
                *(byte *)((int)puVar5 + 0x35) = *(byte *)((int)puVar5 + 0x35) | 2;
              }
              *(dword *)((int)puVar5 + 0x1c) = local_98;
              if ((local_e8 & 0xffff) != 0) goto LAB_0002ca18;
              if ((local_e8 & 0xf0000000) == 0x90000000) {
                if ((*(byte *)((int)puVar5 + 0x35) & 1) != 0) {
                  uVar6 = 0xfff;
LAB_0002cebc:
                  if ((((param_3 & 0xffffffff) <= (param_4 & 0xffffffff)) &&
                      ((uVar6 & param_4) == 0)) && ((uVar6 & param_3) == 0)) {
                    uVar6 = 0x10000000 - (QWORD)(local_e8 & 0xfffffff);
                    if (((param_3 & 0xffffffff) <= (uVar6 & 0xffffffff)) &&
                       ((param_4 & 0xffffffff) <= (uVar6 & 0xffffffff))) {
                      lVar16 = lVar16 + 0x20;
                      puVar14 = (undefined4 *)&local_e4;
                      lVar20 = 5;
                      do {
                        uVar3 = *puVar14;
                        puVar14 = puVar14 + 1;
                        *(undefined4 *)lVar16 = uVar3;
                        lVar16 = lVar16 + 4;
                        lVar20 = lVar20 + -1;
                      } while (lVar20 != 0);
                      XeCryptAesKey(&local_4b0,ZEXT48(&0x16710) + in_r2);
                      XeCryptAesEcb(&local_4b0,&local_d0,&local_d0,1);
                      XeCryptAesEcb(&local_4b0,&local_c0,&local_c0,1);
                      lVar16 = lVar7 + 0x120;
                      pdVar11 = &local_d0;
                      lVar20 = 8;
                      do {
                        dVar4 = *pdVar11;
                        pdVar11 = pdVar11 + 1;
                        *(dword *)lVar16 = dVar4;
                        lVar16 = lVar16 + 4;
                        lVar20 = lVar20 + -1;
                      } while (lVar20 != 0);
                      uVar6 = FUN_0000057c((QWORD)local_e8);
                      *puVar5 = uVar6;
                      if (uVar6 != 0) {
                        uVar6 = FUN_0000057c(local_e8 + param_4 + -1);
                        puVar5[1] = uVar6;
                        if (uVar6 != 0) {
                          uVar18 = 6;
                          if ((local_e8 & 0xf0000000) == 0x90000000) {
                            uVar18 = 7;
                            *(undefined2 *)((int)puVar5 + 0x36) = (short)(local_e8 >> 0xc);
                            *(byte *)((int)puVar5 + 0x35) = *(byte *)((int)puVar5 + 0x35) | 1;
                          }
                          uVar12 = (uint)uVar18;
                          uVar13 = *puVar5;
                          if (uVar13 <= uVar6) {
                            do {
                              if (*(uint *)uVar13 != 0) goto LAB_0002d0b8;
                              uVar18 = (QWORD)(uVar13 == puVar5[1]) << 5 |
                                       (QWORD)(uVar13 == *puVar5) << 4 |
                                       uVar18 & 0xffffffffffffffcf;
                              uVar12 = (uint)uVar18;
                              *(uint *)uVar13 = uVar12;
                              uVar13 = uVar13 + 4;
                            } while (uVar13 <= puVar5[1]);
                          }
                          if ((*(byte *)((int)puVar5 + 0x35) & 1) != 0) {
                            FUN_00029760((QWORD)*(ushort *)((int)puVar5 + 0x36),
                                         (QWORD)(uVar12 & 0xfffffffe),param_4 >> 0xc & 0xfffff);
                          }
                          XeCryptAesEcb(&local_350,lVar7 + 0x148,lVar7 + 0x148,0);
                          uVar6 = 0;
                          do {
                            if ((1 << uVar6 + 8 & local_ec) != 0) {
                              *(dword *)(&0x16940 + (int)in_r2 + (int)(uVar6 << 2)) = local_e8;
                            }
                            uVar6 = uVar6 + 1;
                          } while ((uVar6 & 0xffffffff) < 0xc);
                          *(undefined *)((int)puVar5 + 0x34) = 1;
                          goto LAB_0002d0dc;
                        }
                      }
                    }
                    goto LAB_0002ca18;
                  }
                }
              }
              else {
                if ((*(byte *)((int)puVar5 + 0x35) & 1) == 0) {
                  uVar6 = 0xffff;
                  goto LAB_0002cebc;
                }
              }
              uVar19 = 0xffffffffc000000d;
              goto LAB_0002d0dc;
            }
          }
          else {
            if (((local_ec & 0x30) != 0) || ((param_2 & 0xffffffff) != 0)) {
              local_ec = local_ec | 0x20000000;
              goto LAB_0002cd4c;
            }
          }
          uVar19 = 0xffffffffc0052001;
          goto LAB_0002d0dc;
        }
      }
      else {
        if (puVar9[1] == uVar6) goto LAB_0002cbe8;
      }
      uVar19 = 0xffffffffc0000061;
      goto LAB_0002d0dc;
    }
  }
LAB_0002ca18:
  uVar19 = 0xffffffffc0000141;
LAB_0002d0dc:
  HvpReleaseSpinLock(lVar15);
  FUN_00000204((QWORD)uVar2);
  return uVar19;
LAB_0002d0b8:
  while (uVar13 = uVar13 - 4, *puVar5 <= uVar13) {
    *(undefined4 *)uVar13 = 0;
  }
  uVar19 = 0xffffffffc0000018;
  goto LAB_0002d0dc;
}



undefined8 FUN_0002d0f8(undefined8 param_1,QWORD param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  QWORD in_r2;
  undefined8 uVar5;
  QWORD lVar6;
  QWORD lVar7;
  QWORD uVar8;
  QWORD uVar9;
  QWORD lVar10;
  QWORD uVar11;
  qword back_chain;
  dword local_210;
  word local_20c;
  word local_10c;
  dword local_fc;
  word local_f8;
  word local_b0;
  word local_60;
  dword local_4c;
  
  uVar5 = __Save_R12_25_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if ((param_2 & 0xffffffff) != 0x1a8) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc8003000;
  }
  uVar5 = HvpPhysicalToReal(uVar5,0x1a8);
  memcpy(&local_210,uVar5,0x1a8);
  if (local_210 != 0) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc8003001;
  }
  if ((FUN_00003e80 < local_fc) || ((QWORD)local_fc % 0x14 != 0)) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc8003002;
  }
  lVar10 = *(QWORD *)(&0x16328 + (int)in_r2);
  HvpAquireSpinLock(lVar10);
  FUN_00003830(0,0x10000);
  lVar6 = lVar10 + 0x1c;
  uVar9 = 0;
  iVar3 = (int)lVar10;
  *(undefined4 *)(iVar3 + 0x14) = 0;
  *(dword *)(iVar3 + 0x18) = local_fc;
  uVar8 = (QWORD)local_fc;
  lVar7 = lVar6;
  do {
    if ((uVar8 & 0xffffffff) == 0) goto LAB_0002d230;
    iVar4 = (int)(uVar9 << 2);
    uVar2 = *(uint *)((int)&local_b0 + iVar4);
    uVar11 = (QWORD)uVar2;
    if ((uVar2 == 0) || ((uVar8 & 0xffffffff) < uVar11)) goto LAB_0002d2d4;
    uVar5 = HvpPhysicalToReal((QWORD)*(uint *)((int)&local_f8 + iVar4),uVar11);
    memcpy(lVar7,uVar5,uVar11);
    uVar9 = uVar9 + 1;
    uVar8 = uVar8 - uVar11;
    lVar7 = (QWORD)uVar2 + lVar7;
  } while ((uVar9 & 0xffffffff) < 0x12);
  if ((uVar8 & 0xffffffff) == 0) {
LAB_0002d230:
    XeCryptSha(lVar10 + 4,0x10,&local_10c,0x10,lVar6,(QWORD)*(uint *)(iVar3 + 0x18),&local_60,
               0x14);
    uVar8 = FUN_000038d8(&local_60,&local_20c,ZEXT48(&0x110f8) + in_r2);
    if (((uVar8 & 0xffffffff) != 0) ||
       ((*(int *)(&0x10be8 + (int)in_r2) == 0x20 &&
        (uVar8 = FUN_000038d8(&local_60,&local_20c,ZEXT48(&0x10be8) + in_r2),
        (uVar8 & 0xffffffff) != 0)))) {
      FUN_00003830(0x10000,0);
      uVar5 = 0;
      goto LAB_0002d2bc;
    }
    uVar5 = 0xffffffffc8003003;
  }
  else {
LAB_0002d2d4:
    uVar5 = 0xffffffffc8003002;
  }
  *(undefined4 *)(iVar3 + 0x14) = 0;
  *(undefined4 *)(iVar3 + 0x18) = 0;
  memset(lVar6,0,FUN_00003e80);
LAB_0002d2bc:
  HvpReleaseSpinLock(lVar10);
  FUN_00000204((QWORD)uVar1);
  return uVar5;
}



void FUN_0002d310(void)

{
  int in_r2;
  undefined *puVar1;
  QWORD lVar2;
  QWORD lVar3;
  undefined *puVar4;
  QWORD lVar5;
  qword back_chain;
  
  puVar1 = (undefined *)__Save_R12_29_thru_31();
  lVar2 = *(QWORD *)(&0x16328 + in_r2);
  HvpAquireSpinLock(lVar2);
  lVar3 = lVar2 + 4;
  XeCryptRandom(lVar3,0x10);
  lVar5 = 0x10;
  do {
    puVar4 = (undefined *)lVar3;
    lVar3 = lVar3 + 1;
    *puVar1 = *puVar4;
    puVar1 = puVar1 + 1;
    lVar5 = lVar5 + -1;
  } while (lVar5 != 0);
  HvpReleaseSpinLock(lVar2);
  return;
}



// WARNING: Removing unreachable block (ram,0x0002d3ac)
// WARNING: Removing unreachable block (ram,0x0002d3dc)
// WARNING: Removing unreachable block (ram,0x0002d3bc)
// WARNING: Removing unreachable block (ram,0x0002d3e8)
// WARNING: Removing unreachable block (ram,0x0002d3d4)
// WARNING: Removing unreachable block (ram,0x0002d3e4)

undefined8 FUN_0002d370(undefined8 param_1,undefined8 param_2)

{
  int in_r2;
  undefined8 uVar1;
  qword back_chain;
  
  __Save_R12_27_thru_31();
  uVar1 = *(undefined8 *)(&0x16328 + in_r2);
  HvpAquireSpinLock(uVar1);
  HvpReleaseSpinLock(uVar1);
  return param_2;
}



undefined8 FUN_0002d400(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  QWORD in_r2;
  int *piVar3;
  int iVar4;
  QWORD uVar2;
  QWORD lVar5;
  undefined8 uVar6;
  QWORD lVar7;
  qword back_chain;
  word local_40;
  dword local_2c;
  
  piVar3 = (int *)__Save_R12_29_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  XeCryptSha(param_2,param_3,0,0,0,0,&local_40,0x14);
  iVar4 = XeCryptMemDiff(piVar3 + 3,&local_40,0x14);
  if (iVar4 != 0) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc8003005;
  }
  if (*piVar3 == 0x43524c50) {
    lVar5 = ZEXT48(&0x108b8) + in_r2;
LAB_0002d488:
    lVar7 = 0;
LAB_0002d48c:
    uVar2 = FUN_000038d8(&local_40,piVar3 + 8,lVar5);
    if ((uVar2 & 0xffffffff) == 0) goto LAB_0002d4a0;
  }
  else {
    if (*piVar3 == 0x43524c4c) {
      lVar5 = ZEXT48(&0x110f8) + in_r2;
      lVar7 = ZEXT48(&0x10be8) + in_r2;
      if (*(int *)(&0x10be8 + (int)in_r2) != 0x20) goto LAB_0002d488;
      goto LAB_0002d48c;
    }
    lVar7 = 0;
LAB_0002d4a0:
    uVar6 = 0xffffffffc8003003;
    if ((lVar7 == 0) ||
       (uVar2 = FUN_000038d8(&local_40,piVar3 + 8,lVar7), (uVar2 & 0xffffffff) == 0))
    goto LAB_0002d4cc;
  }
  uVar6 = 0;
LAB_0002d4cc:
  FUN_00000204((QWORD)uVar1);
  return uVar6;
}



undefined8 FUN_0002d520(undefined8 param_1,QWORD param_2)

{
  undefined uVar1;
  uint uVar2;
  int in_r2;
  QWORD lVar3;
  undefined8 uVar4;
  word *pwVar5;
  undefined *puVar6;
  QWORD lVar7;
  qword back_chain;
  word local_1b0;
  word local_50;
  word local_40;
  dword local_30;
  
  lVar3 = __Save_R12_29_thru_31();
  uVar2 = *(uint *)(in_r2 + 0x10000);
  XeCryptAesKey(&local_1b0,0x54);
  XeCryptAesEcb(&local_1b0,lVar3._4_4_ + 0x130,&local_40,0);
  XeCryptAesKey(&local_1b0,&local_40);
  puVar6 = (undefined *)(lVar3._4_4_ + 0x120);
  pwVar5 = &local_50;
  lVar7 = 0x10;
  do {
    uVar1 = *puVar6;
    puVar6 = puVar6 + 1;
    *(undefined *)pwVar5 = uVar1;
    pwVar5 = (word *)((int)pwVar5 + 1);
    lVar7 = lVar7 + -1;
  } while (lVar7 != 0);
  XeCryptAesCbc(&local_1b0,lVar3._4_4_ + 0x140,0x10,lVar3 + 0x140,&local_50,0);
  XeCryptAesCbc(&local_1b0,lVar3._4_4_ + 0x150,param_2 + -0x150,lVar3 + 0x150,&local_50,0);
  uVar4 = FUN_0002d400(lVar3._4_4_,lVar3._4_4_ + 0x150,param_2 + -0x150);
  FUN_00000204((QWORD)uVar2);
  return uVar4;
}



void FUN_0002d5f8(undefined8 param_1,QWORD param_2)

{
  undefined uVar1;
  uint uVar2;
  int in_r2;
  QWORD lVar3;
  word *pwVar4;
  undefined *puVar5;
  QWORD lVar6;
  qword back_chain;
  word local_1b0;
  word local_50;
  word local_40;
  dword local_30;
  
  lVar3 = __Save_R12_28_thru_31();
  puVar5 = (undefined *)(lVar3._4_4_ + 0x120);
  uVar2 = *(uint *)(in_r2 + 0x10000);
  XeCryptRandom(puVar5,0x10);
  pwVar4 = &local_40;
  lVar6 = 0x10;
  do {
    uVar1 = *puVar5;
    puVar5 = puVar5 + 1;
    *(undefined *)pwVar4 = uVar1;
    pwVar4 = (word *)((int)pwVar4 + 1);
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  XeCryptRandom(&local_50,0x10);
  XeCryptAesKey(&local_1b0,&local_50);
  XeCryptAesCbc(&local_1b0,lVar3._4_4_ + 0x140,0x10,lVar3 + 0x140,&local_40,1);
  XeCryptAesCbc(&local_1b0,lVar3._4_4_ + 0x150,param_2 + -0x150,lVar3 + 0x150,&local_40,1);
  XeCryptAesKey(&local_1b0,0x20);
  XeCryptAesEcb(&local_1b0,&local_50,lVar3._4_4_ + 0x130,1);
  FUN_00000204((QWORD)uVar2);
  return;
}



undefined8 FUN_0002d6d0(undefined8 param_1,QWORD param_2)

{
  undefined uVar1;
  uint uVar2;
  int in_r2;
  QWORD lVar3;
  undefined8 uVar4;
  word *pwVar5;
  undefined *puVar6;
  QWORD lVar7;
  qword back_chain;
  word local_1b0;
  word local_50;
  word local_40;
  dword local_30;
  
  lVar3 = __Save_R12_29_thru_31();
  uVar2 = *(uint *)(in_r2 + 0x10000);
  XeCryptAesKey(&local_1b0,0x20);
  XeCryptAesEcb(&local_1b0,lVar3._4_4_ + 0x130,&local_40,0);
  puVar6 = (undefined *)(lVar3._4_4_ + 0x120);
  pwVar5 = &local_50;
  lVar7 = 0x10;
  do {
    uVar1 = *puVar6;
    puVar6 = puVar6 + 1;
    *(undefined *)pwVar5 = uVar1;
    pwVar5 = (word *)((int)pwVar5 + 1);
    lVar7 = lVar7 + -1;
  } while (lVar7 != 0);
  XeCryptAesKey(&local_1b0,&local_40);
  XeCryptAesCbc(&local_1b0,lVar3._4_4_ + 0x140,0x10,lVar3 + 0x140,&local_50,0);
  XeCryptAesCbc(&local_1b0,lVar3._4_4_ + 0x150,param_2 + -0x150,lVar3 + 0x150,&local_50,0);
  uVar4 = FUN_0002d400(lVar3._4_4_,lVar3._4_4_ + 0x150,param_2 + -0x150);
  FUN_00000204((QWORD)uVar2);
  return uVar4;
}



void FUN_0002d7a8(undefined8 param_1,QWORD param_2,QWORD param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int in_r2;
  QWORD *plVar3;
  word *pwVar4;
  QWORD lVar5;
  undefined *puVar6;
  QWORD lVar7;
  qword back_chain;
  word local_180;
  word local_17c;
  word local_177;
  word local_60;
  word local_50;
  word local_40;
  dword local_30;
  
  plVar3 = (QWORD *)__Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  memcpy(&local_180);
  pwVar4 = &local_17c;
  lVar5 = *(QWORD *)(&0x163c0 + in_r2) + 0x9ca;
  lVar7 = 5;
  do {
    puVar6 = (undefined *)lVar5;
    lVar5 = lVar5 + 1;
    *(undefined *)pwVar4 = *puVar6;
    pwVar4 = (word *)((int)pwVar4 + 1);
    lVar7 = lVar7 + -1;
  } while (lVar7 != 0);
  memcpy(*plVar3,&local_180,0x150);
  memcpy(*plVar3 + 0x150,param_2 + 0x150,param_3);
  uVar2 = *(undefined4 *)((int)plVar3[1] + 4);
  *(undefined4 *)((int)plVar3 + 0x14) = (int)(param_3 + 0x150);
  *(undefined4 *)(plVar3 + 3) = uVar2;
  memset((param_3 & 0xffffffff) + plVar3[1],0,(QWORD)*(uint *)(plVar3 + 2) - (param_3 + 0x150));
  FUN_00000204((QWORD)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_0002d8a0(void)

{
  uint uVar1;
  int in_r2;
  int iVar2;
  qword back_chain;
  word local_30;
  dword local_1c;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)(in_r2 + 0x10000);
  XeCryptSha(*(QWORD *)(&0x16320 + in_r2) + 0x14,0x3ec,0,0,0,0,&local_30,0x14);
  iVar2 = XeCryptMemDiff(*(undefined8 *)(&0x16320 + in_r2),&local_30,0x14);
  if (iVar2 != 0) {
    _v_MACHINE_CHECK_0();
  }
  FUN_00000204((QWORD)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

QWORD FUN_0002d928(QWORD param_1)

{
  int in_r2;
  QWORD lVar1;
  uint uVar2;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  FUN_0002d8a0();
  if (param_1 != 0) {
    lVar1 = *(QWORD *)(&0x16320 + in_r2) + 0x20;
    uVar2 = 0;
    do {
      if (*(QWORD *)lVar1 == param_1) {
        return lVar1;
      }
      uVar2 = uVar2 + 1;
      lVar1 = lVar1 + 0x10;
    } while (uVar2 < 0x3e);
  }
  return 0;
}



// WARNING: Could not reconcile some variable overlaps

undefined8 FUN_0002d990(void)

{
  uint uVar1;
  uint uVar2;
  QWORD in_r2;
  undefined8 uVar3;
  int iVar5;
  QWORD uVar4;
  int iVar6;
  QWORD lVar7;
  QWORD *plVar8;
  qword back_chain;
  word local_1f0;
  word local_1ee;
  dword local_1ec;
  word local_1e8;
  dword local_1d8;
  word local_148;
  word local_40;
  dword local_2c;
  
  uVar3 = __Save_R12_29_thru_31();
  lVar7 = *(QWORD *)(&0x163c0 + (int)in_r2);
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  memcpy(&local_1f0,uVar3,0x1a8);
  iVar5 = XeCryptMemDiff(&local_1f0,lVar7 + 0x9c8,0x1a8);
  if ((iVar5 == 0) || (((*(uint *)((int)lVar7 + 0x9e0) ^ local_1d8) & 0xffffff) != 0)) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc8003005;
  }
  XeCryptSha(&local_1f0,0xa8,0,0,0,0,&local_40,0x14);
  uVar4 = FUN_000038d8(&local_40,&local_148,ZEXT48(&0x11318) + in_r2);
  iVar5 = (int)in_r2;
  if ((uVar4 & 0xffffffff) == 0) {
    FUN_00000204((QWORD)uVar1);
    return 0xffffffffc8003003;
  }
  lVar7 = ((QWORD)_local_1ee & 0xffffffffff00) << 0x10;
  HvpAquireSpinLock(ZEXT48(&0x162f8) + in_r2);
  iVar6 = FUN_0002d928(lVar7);
  if (iVar6 == 0) {
    iVar6 = (int)*(undefined8 *)(&0x16320 + iVar5);
    uVar2 = *(uint *)(iVar6 + 0x14);
    if (0x3d < uVar2) {
      uVar3 = 0xffffffffc8003004;
      goto LAB_0002dae0;
    }
    plVar8 = (QWORD *)((uVar2 + 2) * 0x10 + iVar6);
    *(int *)(iVar6 + 0x14) = uVar2 + 1;
    *plVar8 = lVar7;
    *(undefined4 *)(plVar8 + 1) = 1;
    *(undefined4 *)((int)plVar8 + 0xc) = 0;
  }
  else {
    if (*(uint *)(iVar6 + 8) < 0xfffffffe) {
      *(int *)(iVar6 + 8) = *(uint *)(iVar6 + 8) + 1;
    }
  }
  uVar3 = 0;
  XeCryptSha(*(QWORD *)(&0x16320 + iVar5) + 0x14,0x3ec,0,0,0,0,
             *(QWORD *)(&0x16320 + iVar5),0x14);
LAB_0002dae0:
  HvpReleaseSpinLock(ZEXT48(&0x162f8) + in_r2);
  FUN_00000204((QWORD)uVar1);
  return uVar3;
}



void FUN_0002db50(void)

{
  uint uVar1;
  int iVar2;
  int in_r2;
  undefined8 uVar3;
  QWORD uVar4;
  undefined8 uVar5;
  QWORD uVar6;
  undefined8 uVar7;
  QWORD uVar8;
  QWORD lVar9;
  QWORD lVar10;
  undefined8 uVar11;
  QWORD lVar12;
  undefined *puVar13;
  QWORD lVar14;
  undefined auStack160 [160];
  
  iVar2 = (int)*(QWORD *)(&0x16320 + in_r2);
  uVar1 = *(uint *)(iVar2 + 0x14);
  lVar9 = ((QWORD)uVar1 + 2) * 0x10 + *(QWORD *)(&0x16320 + in_r2);
  *(int *)(iVar2 + 0x14) = uVar1 + 1;
  lVar12 = *(QWORD *)(&0x163c0 + in_r2) + 0x9ca;
  lVar14 = 5;
  lVar10 = lVar9;
  do {
    puVar13 = (undefined *)lVar12;
    lVar12 = lVar12 + 1;
    *(undefined *)lVar10 = *puVar13;
    lVar10 = lVar10 + 1;
    lVar14 = lVar14 + -1;
  } while (lVar14 != 0);
  uVar5 = 0;
  uVar11 = 0x14;
  uVar8 = 0;
  uVar7 = 0;
  iVar2 = (int)lVar9;
  *(undefined4 *)(iVar2 + 8) = 0xffffffff;
  uVar6 = 0;
  *(undefined4 *)(iVar2 + 0xc) = 0;
  lVar10 = *(QWORD *)(&0x16320 + in_r2);
  uVar4 = 0x3ec;
  uVar3 = __Save_R12_26_thru_31(lVar10 + 0x14);
  uVar1 = *(uint *)(in_r2 + 0x10000);
  if ((uVar4 & 0xffffffff) != 0) {
    XeCryptShaUpdate(auStack160,uVar3,uVar4);
  }
  if ((uVar6 & 0xffffffff) != 0) {
    XeCryptShaUpdate(auStack160,uVar5,uVar6);
  }
  if ((uVar8 & 0xffffffff) != 0) {
    XeCryptShaUpdate(auStack160,uVar7,uVar8);
  }
  XeCryptShaFinal(auStack160,lVar10,uVar11);
  FUN_00000204((QWORD)uVar1);
  return;
}



void FUN_0002dbd8(void)

{
  int in_r2;
  int iVar1;
  QWORD lVar2;
  QWORD lVar3;
  qword back_chain;
  
  __Save_R12_29_thru_31();
  lVar2 = FUN_00000270();
  *(QWORD *)(&0x16328 + in_r2) = lVar2 + 0x8000;
  lVar2 = FUN_00000298();
  *(QWORD *)(&0x16320 + in_r2) = lVar2 + 0x8000;
  iVar1 = in_r2;
  lVar2 = FUN_00000280();
  *(undefined4 *)(&0x16310 + iVar1) = 0x20000;
  *(undefined4 *)(&0x16314 + iVar1) = 0;
  *(undefined4 *)(&0x16318 + iVar1) = 0;
  *(QWORD *)(&0x16300 + iVar1) = lVar2;
  *(QWORD *)(&0x16308 + iVar1) = lVar2 + 0x150;
  lVar2 = thunk_FUN_00000298();
  lVar3 = *(QWORD *)(&0x16320 + in_r2);
  *(undefined4 *)(&0x16350 + iVar1) = 0x8000;
  *(undefined4 *)(&0x16354 + iVar1) = 0;
  *(undefined4 *)(&0x16358 + iVar1) = 0;
  *(QWORD *)(&0x16340 + iVar1) = lVar2;
  *(QWORD *)(&0x16348 + iVar1) = lVar2 + 0x150;
  XeCryptSha(lVar3 + 0x14,0x3ec,0,0,0,0,lVar3,0x14);
  return;
}



undefined8 FUN_0002dc90(undefined8 param_1,QWORD param_2,QWORD param_3)

{
  bool bVar1;
  uint uVar2;
  undefined *puVar3;
  QWORD in_r2;
  int iVar4;
  QWORD uVar5;
  int iVar7;
  undefined8 uVar6;
  QWORD uVar8;
  QWORD uVar9;
  QWORD *plVar10;
  qword back_chain;
  
  uVar5 = __Save_R12_24_thru_31();
  iVar4 = (int)in_r2;
  bVar1 = param_3 == 0;
  uVar9 = (QWORD)((int)param_2 + 0x7fU & 0xffffff80);
  if (bVar1) {
    puVar3 = &0x16340;
    uVar8 = 0x8000;
  }
  else {
    puVar3 = &0x16300;
    uVar8 = 0x20000;
  }
  if (((((uVar5 & 0xffff) != 0) || ((param_2 & 0xf) != 0)) || ((param_2 & 0xffffffff) < 0x150)) ||
     ((uVar8 < (param_2 & 0xffffffff) || (uVar8 < uVar9)))) {
    return 0xffffffffc8003000;
  }
  plVar10 = (QWORD *)(ZEXT48(puVar3) + in_r2);
  if (*plVar10 == 0) {
    return 0xffffffffc8003004;
  }
  HvpSetRMCI(0);
  iVar7 = FUN_00003280(uVar5,uVar9);
  if (bVar1) {
    uVar6 = FUN_0002d520(iVar7,param_2);
  }
  else {
    uVar6 = FUN_0002d6d0();
  }
  if ((int)uVar6 == 0) {
    uVar2 = *(uint *)(iVar7 + 0x150);
    if ((QWORD)uVar2 == (param_2 & 0xffffffff) - 0x150) {
      if (*(uint *)(plVar10 + 3) < *(uint *)(iVar7 + 0x154)) {
        if (!bVar1) {
          if ((*(QWORD *)(iVar7 + 0x140) != param_3) ||
             (*(char *)(iVar7 + 0x14f) != (&0x16620)[iVar4])) {
            uVar6 = 0xffffffffc8003005;
            goto LAB_0002de14;
          }
          FUN_00003830(0x200000,0);
        }
        FUN_0002d7a8(ZEXT48(puVar3) + in_r2,iVar7,(QWORD)uVar2);
      }
      else {
        uVar6 = 0xffffffffc8003006;
      }
    }
    else {
      uVar6 = 0xffffffffc8003002;
    }
  }
LAB_0002de14:
  memset(iVar7,0,param_2);
  if ((int)uVar6 != 0) {
    memset(*plVar10,0,0x150);
    *(undefined4 *)(plVar10 + 3) = 0xffffffff;
  }
  HvpRelocateEncryptedToPhysical(iVar7,uVar9);
  HvpSetRMCI(1);
  return uVar6;
}



undefined8 FUN_0002de70(undefined8 param_1,QWORD param_2,undefined8 param_3)

{
  uint uVar1;
  QWORD in_r2;
  int iVar2;
  QWORD uVar3;
  int iVar5;
  undefined8 uVar4;
  qword back_chain;
  
  uVar3 = __Save_R12_26_thru_31();
  uVar1 = (int)param_2 + 0x7fU & 0xffffff80;
  if (((((uVar3 & 0xffff) != 0) || ((param_2 & 0xf) != 0)) ||
      (ZEXT48(&0x1feb0) < (param_2 - 0x150 & 0xffffffff))) || (0x20000 < uVar1)) {
    return 0xffffffffc8003000;
  }
  if (*(QWORD *)(ZEXT48(&0x16300) + in_r2) == 0) {
    return 0xffffffffc8003004;
  }
  iVar2 = (int)in_r2;
  HvpSetRMCI(0);
  iVar5 = FUN_00003280(uVar3,(QWORD)uVar1);
  uVar4 = FUN_0002d520(iVar5,param_2);
  if ((int)uVar4 == 0) {
    if ((QWORD)*(uint *)(iVar5 + 0x150) == (param_2 & 0xffffffff) - 0x150) {
      if (*(uint *)(&0x16318 + (int)in_r2) < *(uint *)(iVar5 + 0x154)) {
        FUN_0002d7a8(ZEXT48(&0x16300) + in_r2,iVar5);
        *(undefined8 *)(iVar5 + 0x140) = param_3;
        *(undefined *)(iVar5 + 0x14f) = (&0x16620)[iVar2];
        uVar3 = func_0x00002b70();
        if ((uVar3 & 0xffffffff) != 0) {
          *(char *)(iVar5 + 0x14f) = *(char *)(iVar5 + 0x14f) + '\x01';
        }
        FUN_0002d5f8(iVar5,param_2);
        goto LAB_0002df44;
      }
      uVar4 = 0xffffffffc8003006;
    }
    else {
      uVar4 = 0xffffffffc8003002;
    }
  }
  memset(iVar5,0,param_2);
LAB_0002df44:
  HvpRelocateEncryptedToPhysical(iVar5,(QWORD)uVar1);
  HvpSetRMCI(1);
  return uVar4;
}



undefined8 FUN_0002dfe0(undefined8 param_1,QWORD param_2,undefined8 param_3)

{
  uint uVar1;
  uint uVar2;
  int in_r2;
  QWORD uVar3;
  int iVar4;
  QWORD lVar5;
  undefined8 uVar6;
  qword back_chain;
  
  uVar3 = __Save_R12_27_thru_31();
  uVar2 = (int)param_2 + 0x7fU & 0xffffff80;
  if (((((uVar3 & 0xffff) == 0) && ((param_2 & 0xf) == 0)) &&
      ((param_2 - 0x150 & 0xffffffff) <= ZEXT48(&0x1feb0))) && (uVar2 < 0x20001)) {
    HvpSetRMCI(0);
    iVar4 = FUN_00003280(uVar3,(QWORD)uVar2);
    lVar5 = *(QWORD *)(&0x16300 + in_r2);
    if (((lVar5 == 0) || (*(int *)lVar5 == 0)) ||
       (uVar1 = *(uint *)(&0x16314 + in_r2), uVar1 == 0)) {
      uVar6 = 0xffffffffc8003004;
      memset(iVar4,0,param_2);
    }
    else {
      memcpy(iVar4,lVar5,(QWORD)uVar1);
      uVar6 = 0;
      *(undefined4 *)(iVar4 + 4) = 0;
      *(undefined *)(iVar4 + 8) = 0;
      *(undefined *)(iVar4 + 9) = 0;
      *(undefined *)(iVar4 + 10) = 0;
      *(undefined *)(iVar4 + 0xb) = 0;
      *(undefined8 *)(iVar4 + 0x140) = 0;
      *(undefined8 *)(iVar4 + 0x148) = 0;
      *(undefined8 *)(iVar4 + 0x140) = param_3;
      *(undefined *)(iVar4 + 0x14f) = (&0x16620)[in_r2];
      uVar3 = func_0x00002b70();
      if ((uVar3 & 0xffffffff) != 0) {
        *(char *)(iVar4 + 0x14f) = *(char *)(iVar4 + 0x14f) + '\x01';
      }
      FUN_0002d5f8(iVar4,(QWORD)uVar1);
    }
    HvpRelocateEncryptedToPhysical(iVar4,(QWORD)uVar2);
    HvpSetRMCI(1);
  }
  else {
    uVar6 = 0xffffffffc8003000;
  }
  return uVar6;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_0002e120(void)

{
  int iVar1;
  QWORD in_r2;
  int iVar2;
  QWORD lVar3;
  QWORD lVar4;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  lVar3 = FUN_00000298();
  lVar4 = FUN_00000270();
  iVar1 = (int)lVar3;
  iVar2 = (int)in_r2;
  *(QWORD *)(&0x162e8 + iVar2) = lVar3 + 0xa000;
  *(QWORD *)(&0x162e0 + iVar2) = lVar3 + 0xc000;
  *(QWORD *)(&0x162d8 + iVar2) = lVar4 + 0xfe00;
  *(QWORD *)(&0x162d0 + iVar2) = lVar3 + 0x8000;
  memcpy(lVar4 + 0xfe00,ZEXT48(&0x11c90) + in_r2,0x21);
  *(word *)(iVar1 + 0x8600) = 0xd81e;
  *(undefined2 *)(iVar1 + 0x8608) = *(undefined2 *)(&0x16a9c + iVar2);
  *(dword *)(iVar1 + 0x8610) = 0x21281d3;
  *(undefined4 *)(iVar1 + 0x861c) = *(undefined4 *)(&0x16aac + iVar2);
  return;
}



void FUN_0002e1d0(QWORD param_1)

{
  byte bVar1;
  int in_r2;
  
  bVar1 = *(byte *)((int)*(undefined8 *)(&0x163c0 + in_r2) + 0x1a);
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 2) != 0) {
      param_1 = *(QWORD *)(&0x162f0 + in_r2) & param_1;
    }
  }
  else {
    param_1 = 0;
  }
  *(QWORD *)((int)*(undefined8 *)(&0x163c0 + in_r2) + 0x30) = param_1;
  *(QWORD *)((int)*(undefined8 *)(&0x162d0 + in_r2) + 0x630) = param_1;
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_0002e220(void)

{
  ushort uVar1;
  QWORD in_r2;
  int iVar2;
  int iVar3;
  QWORD lVar4;
  ushort uVar5;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  iVar2 = (int)in_r2;
  iVar3 = (int)*(QWORD *)(&0x163c0 + iVar2);
  uVar1 = *(ushort *)(iVar3 + 0x1c);
  if ((*(ushort *)(&0x16a9c + iVar2) & 4) == 0) {
    uVar5 = uVar1;
    if (*(QWORD *)(&0x16aa0 + iVar2) - 0x710700U < 0x200) {
      lVar4 = *(QWORD *)(&0x163c0 + iVar2) + 0xb72;
      uVar5 = uVar1 | 0x40;
      if (*(int *)(iVar3 + 0xc82) != 0x4f534947) {
        _v_MACHINE_CHECK_0();
      }
      iVar2 = (int)in_r2;
      iVar3 = XeCryptMemDiff(lVar4 + 0x120,ZEXT48(&0x11d3c) + in_r2,0x1c);
      if (iVar3 == 0) {
        uVar5 = uVar1 & 0xffdf | 0x40;
      }
    }
  }
  else {
    uVar5 = 0;
  }
  *(ushort *)((int)*(undefined8 *)(&0x162d0 + iVar2) + 0x604) = uVar5;
  return;
}



// WARNING: Removing unreachable block (ram,0x0002e388)

void FUN_0002e2f8(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  QWORD in_r2;
  undefined8 uVar5;
  QWORD uVar6;
  QWORD lVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  QWORD lVar10;
  qword back_chain;
  word local_1d0;
  word local_70;
  word local_60;
  dword local_50;
  
  uVar5 = __Save_R12_25_thru_31();
  iVar4 = (int)in_r2;
  uVar1 = *(uint *)(iVar4 + 0x10000);
  lVar10 = *(QWORD *)(&0x162e8 + iVar4);
  lVar7 = *(QWORD *)(&0x163c0 + iVar4);
  *(undefined8 *)(&0x162f0 + iVar4) = uVar5;
  iVar2 = (int)*(undefined8 *)(&0x162d0 + iVar4);
  *(word *)(iVar2 + 0x600) = 0xd81e;
  *(undefined2 *)(iVar2 + 0x608) = *(undefined2 *)(&0x16a9c + iVar4);
  *(undefined2 *)(iVar2 + 0x60a) = *(undefined2 *)(&0x16a94 + iVar4);
  uVar6 = FUN_000035a0();
  if ((uVar6 & 0xffffffff) == 0) {
    uVar5 = 0;
    uVar9 = 0;
    uVar8 = 0;
  }
  else {
    iVar3 = (int)lVar7;
    uVar5 = *(undefined8 *)(iVar3 + 0x30);
    uVar9 = *(undefined4 *)(iVar3 + 0x24);
    uVar8 = *(undefined4 *)(iVar3 + 0x28);
  }
  FUN_0002e1d0(uVar5);
  FUN_0002e220();
  *(undefined4 *)(iVar2 + 0x618) = uVar9;
  *(undefined4 *)(iVar2 + 0x620) = uVar8;
  memcpy(lVar10,lVar7 + 0x9c8,0x1a8);
  *(undefined4 *)((int)lVar10 + 0x1a8) = 0x73;
  lVar7 = in_r2;
  memcpy(lVar10 + 0x1b0,ZEXT48(&0x108b8) + in_r2,0x110);
  memcpy(lVar10 + 0x2c0,ZEXT48(&0x110f8) + lVar7,0x110);
  memcpy(lVar10 + 0x3d0,ZEXT48(&0x11318) + lVar7,0x110);
  memcpy(lVar10 + 0x4e0,ZEXT48(&0x11428) + lVar7,0x110);
  memcpy(lVar10 + 0x5f0,ZEXT48(&0x11538) + lVar7,0x110);
  memcpy(lVar10 + 0x810,ZEXT48(&0x10be8) + in_r2,0x110);
  XeCryptSha(0x20,0x10,0,0,0,0,lVar10 + 0xa30,0x10);
  FUN_00003620(*(undefined8 *)(&0x163c0 + iVar4),lVar10 + 0xa40,0x10);
  FUN_0000a458(&local_60);
  XeCryptAesKey(&local_1d0,&local_60);
  XeCryptAesEcb(&local_1d0,&local_70,lVar10 + 0xa50,1);
  uVar5 = HvpGetFlashBase();
  CopyBy64(lVar10 + 0xa60,uVar5,0x10);
  FUN_00000204((QWORD)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_0002e4c0(void)

{
  int iVar1;
  int in_r2;
  undefined4 uVar2;
  QWORD lVar3;
  undefined *puVar4;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  puVar4 = &0x162c4 + in_r2;
  lVar3 = *(QWORD *)(&0x16628 + in_r2);
  HvpAquireSpinLock(puVar4);
  if (*(short *)((int)*(undefined8 *)(&0x162d0 + in_r2) + 0x602) == 0x102) {
    uVar2 = 0x107;
  }
  else {
    uVar2 = 0x70000;
  }
  *(undefined4 *)((int)*(undefined8 *)(&0x162d0 + in_r2) + 0x614) = uVar2;
  iVar1 = (int)lVar3;
  *(undefined8 *)((int)*(undefined8 *)(&0x162d0 + in_r2) + 0x638) =
       *(undefined8 *)(iVar1 + 0x28);
  *(undefined8 *)((int)*(undefined8 *)(&0x162d0 + in_r2) + 0x640) =
       *(undefined8 *)(iVar1 + 0x30);
  memcpy(*(QWORD *)(&0x162d0 + in_r2) + 0x700,lVar3 + 0x38,0x80);
  FUN_0002e220();
  HvpReleaseSpinLock(puVar4);
  return;
}



// WARNING: Removing unreachable block (ram,0x0002e6ac)
// WARNING: Removing unreachable block (ram,0x0002e6c0)

undefined8 FUN_0002e580(undefined8 param_1,undefined8 param_2,QWORD param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  QWORD in_r2;
  int iVar4;
  int iVar5;
  QWORD uVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  QWORD lVar10;
  QWORD lVar11;
  qword back_chain;
  word local_f0;
  word local_dc;
  word local_70;
  dword local_50;
  
  uVar6 = __Save_R12_25_thru_31();
  iVar4 = (int)in_r2;
  uVar1 = *(uint *)(iVar4 + 0x10000);
  if ((uVar6 & 0xffffffff) < 0x21) {
    uVar2 = *(uint *)(&0x11cb8 + (int)((uVar6 & 0xffffffff) << 2) + iVar4) >> 0x10;
    if ((param_3 & 0xffffffff) ==
        (QWORD)(*(uint *)(&0x11cb8 + (int)((uVar6 & 0xffffffff) << 2) + iVar4) & 0xffff)) {
      HvpAquireSpinLock(ZEXT48(&0x162c4) + in_r2);
      iVar3 = (int)(uVar6 & 0xffffffff);
      if (*(char *)(iVar3 + (int)*(undefined8 *)(&0x162d8 + iVar4)) == '\0') {
        uVar7 = 0xffffffffc8000002;
      }
      else {
        lVar10 = *(QWORD *)(&0x162d0 + iVar4);
        iVar5 = iVar4;
        puVar8 = (undefined8 *)HvpPhysicalToReal(param_2,param_3);
        if ((uVar6 & 0xffffffff) == 0) {
          uVar7 = FUN_0002d990();
        }
        else {
          if ((uVar6 & 0xffffffff) == 1) {
            memcpy((QWORD)uVar2 + lVar10,puVar8,param_3);
            uVar7 = 0;
          }
          else {
            if ((uVar6 & 0xffffffff) == 3) {
              uVar7 = 0;
              *(undefined2 *)((int)lVar10 + 0x602) =
                   *(undefined2 *)((int)*(undefined8 *)(&0x163c0 + iVar5) + 200);
            }
            else {
              if ((uVar6 & 0xffffffff) == 0x1c) {
                if (*(int *)puVar8 == 0) {
                  uVar7 = 0xffffffffc800000c;
                }
                else {
                  uVar7 = 0;
                  *(int *)(((*(uint *)(&0x162c8 + iVar5) & 0x1f) + 0x1a0) * 4 + (int)lVar10) =
                       *(int *)puVar8;
                  *(int *)(&0x162c8 + iVar5) = *(int *)(&0x162c8 + iVar5) + 1;
                }
              }
              else {
                if ((uVar6 & 0xffffffff) == 0x1e) {
                  puVar9 = (undefined8 *)&local_f0;
                  lVar11 = 0x14;
                  do {
                    uVar7 = *puVar8;
                    puVar8 = puVar8 + 1;
                    *puVar9 = uVar7;
                    puVar9 = puVar9 + 1;
                    lVar11 = lVar11 + -1;
                  } while (lVar11 != 0);
                  FUN_00024dd8(&local_70,0x10);
                  uVar7 = 0;
                  XeCryptSha(&local_dc,0x8c,0,0,0,0,&local_f0,0x14);
                  memcpy((QWORD)uVar2 + lVar10,&local_f0,0xa0);
                }
                else {
                  uVar7 = 0xffffffffc8000001;
                }
              }
            }
          }
        }
      }
      iVar4 = (int)*(undefined8 *)(&0x162d8 + iVar4);
      if ('\0' < *(char *)(iVar3 + iVar4)) {
        *(char *)(iVar3 + iVar4) = *(char *)(iVar3 + iVar4) + -1;
      }
      HvpReleaseSpinLock(ZEXT48(&0x162c4) + in_r2);
      FUN_0002e4c0();
      FUN_00000204((QWORD)uVar1);
    }
    else {
      FUN_00000204((QWORD)uVar1);
      uVar7 = 0xffffffffc8000004;
    }
  }
  else {
    FUN_00000204((QWORD)uVar1);
    uVar7 = 0xffffffffc8000001;
  }
  return uVar7;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_0002e800(QWORD *param_1)

{
  int in_r2;
  int iVar1;
  short sVar2;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  iVar1 = in_r2 + 0x10000;
  FUN_0002e1d0(*(QWORD *)((int)*(undefined8 *)(&0x163c0 + in_r2) + 0x30) & ~*param_1 |
               param_1[1]);
  sVar2 = *(short *)(param_1 + 2);
  if (sVar2 != 0) {
    *(short *)((int)*(undefined8 *)(HvxGetUpdateSequence + iVar1) + 200) = sVar2;
    if (sVar2 == 0x7fff) {
      FUN_00003830(0x1000,0);
      sVar2 = *(short *)((int)param_1 + 0x12);
    }
    *(short *)((int)*(undefined8 *)(&0x162d0 + in_r2) + 0x602) = sVar2;
  }
  return 0;
}



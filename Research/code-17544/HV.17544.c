typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef unsigned long long    qword;
typedef unsigned char    undefined1;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    word;



undefined8 _v_RESET(void)

{
  ushort *puVar1;
  int iVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  uint uVar5;
  uint uVar6;
  ulonglong *puVar7;
  int iVar8;
  ulonglong uVar9;
  longlong in_spr130;
  int in_spr131;
  ulonglong in_spr139;
  ulonglong in_spr399;
  ulonglong in_spr3f1;
  uint in_PIR;
  
  uVar3 = in_spr3f1 & 0xf3ffffbfffffffff | 0xc00004000000000;
  sync(0);
  sync(0);
  instructionSynchronize();
  if (in_spr131 == 0) {
    uVar6 = in_PIR & 7;
    uVar9 = (ulonglong)uVar6;
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
      *(uint *)((int)&DWORD_00010004 + iVar2) =
           ((uint)(in_spr139 >> 0x10) | (uint)((ulonglong)uVar4 >> 0x10)) & 0x3ffffff;
    }
    HvxFlushEntireTb();
    puVar7 = (ulonglong *)((in_PIR & 7) << 0xc | 0x50000);
    puVar7[0xe] = 0x7c;
    eieioOp();
    puVar7[1] = 0x7c;
    eieioOp();
    *puVar7 = (ulonglong)(uint)(1 << uVar9);
    eieioOp();
    sync(0);
    instructionSynchronize();
    returnFromInterrupt();
    return 0;
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
  return 0;
}



void HvpSleepThread(void)

{
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



void HvpAquireSpinLock(undefined8 param_1)

{
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



void FUN_000001e0(undefined4 *param_1)

{
  sync(1);
  *param_1 = 0;
  return;
}



void j_XeCryptMemDiff(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptMemDiff();
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



void HvpReleaseSpinLock(int param_1)

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

undefined8 _v_DATA_STORAGE(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ushort uVar1;
  uint uVar2;
  ulonglong uVar3;
  ushort *puVar4;
  uint uVar5;
  byte bVar6;
  ulonglong *puVar7;
  undefined *puVar9;
  ulonglong uVar8;
  int iVar10;
  uint *puVar11;
  undefined8 in_r13;
  ulonglong uVar12;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  longlong in_LR;
  uint in_DSISR;
  uint in_DAR;
  uint in_SRR0;
  ulonglong in_SRR1;
  uint in_spr130;
  ulonglong in_spr131;
  
  *(ulonglong *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(byte *)(in_spr130 + 0xf) = in_cr0 & 0xf;
  if (!SUB41((in_DSISR << 1) >> 0x1f,0)) goto LAB_0000163c;
  if ((bool)(((byte)((uint)((int)in_SRR1 << 0x10) >> 0x18) & 0x40) >> 6)) {
    uVar2 = *(uint *)(in_spr130 + 0x58) & 2;
    uVar12 = *(ulonglong *)(DWORD_ARRAY_00010330 + uVar2 * 2 + 2) << 0x20;
    uVar3 = (ulonglong)in_DAR;
    if (*(longlong *)(DWORD_ARRAY_00010330 + uVar2 * 2) != 0) {
      uVar5 = (uint)(*(ulonglong *)(DWORD_ARRAY_00010330 + uVar2 * 2 + 2) >>
                    (in_DAR >> 0x1b & 0x1e) + 0x20) & 3;
      uVar2 = (uint)*(longlong *)(DWORD_ARRAY_00010330 + uVar2 * 2);
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
            uVar8 = (ulonglong)uVar2;
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
          uVar8 = (ulonglong)uVar2;
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
    goto FUN_00001018;
  case 8:
  case 10:
  case 0xc:
  case 0xe:
    uVar2 = in_DAR >> 0xe & 0xfffc;
    if (uVar2 == 0xfffc) goto LAB_00001188;
    uVar2 = *(uint *)(uVar2 + 0x1f70000);
joined_r0x00001274:
    if ((uVar2 & 1) != 0) goto LAB_00001188;
FUN_00001018:
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
    bVar6 = *(byte *)(in_DAR >> 0xd & 0xffff | 0x1f50000) >> (ulonglong)(in_DAR >> 10 & 4);
    break;
  case 0x14:
  case 0x16:
    bVar6 = *(byte *)((in_DAR >> 0x11 & 0xfff) + (in_spr130 & 0xffff0000) + 0x11000) >>
            (ulonglong)(in_DAR >> 0xe & 4);
    break;
  case 0x18:
  case 0x1a:
    bVar6 = *(byte *)((int)&DWORD_00010c00 + (in_DAR >> 0x19 & 0xf) + (in_spr130 & 0xffff0000)) >>
            (ulonglong)(in_DAR >> 0x16 & 4);
    break;
  case 0x1c:
  case 0x1e:
    if ((*(uint *)((in_DAR + 0x1000 >> 10 & 0x7fffc) + 0x1f80000) & 3) == 3) goto LAB_00001188;
    goto LAB_0000163c;
  }
  if ((bVar6 & 0xf) != 0) {
LAB_00001188:
    uVar2 = (uint)in_spr131 >> 7 & 0x40;
    uVar12 = (ulonglong)(((uint)in_spr131 & 0x1000) << 1) |
             (ulonglong)uVar2 | in_spr131 & 0xffffffffffffdfbf;
    puVar7 = (ulonglong *)uVar12;
    *puVar7 = uVar12;
    sync(1);
    if (*(longlong *)((uint)puVar7 ^ 0x40) != 0) {
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
  *(ulonglong *)(in_spr130 + 0x28) =
       (ulonglong)
       ((uint)*(byte *)(in_spr130 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | (ulonglong)in_SRR0;
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



// WARNING: Removing unreachable block (ram,0x00003134)
// WARNING: Removing unreachable block (ram,0x00003144)
// WARNING: Removing unreachable block (ram,0x0000315c)

void FUN_00000364(void)

{
  int in_r2;
  
  FUN_0000b150();
  FUN_00001f60();
  FUN_00002bc0();
  FUN_0000a120();
  FUN_00003f88();
  FUN_00001b10();
  FUN_00001c50();
  FUN_00002dd8();
  FUN_00002e90();
  FUN_00002ff0();
  if ((*(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6bc) & 0x8000) == 0) {
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



undefined8 FUN_00000384(undefined param_1,ulonglong param_2,ulonglong param_3)

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



longlong HvpZeroCacheLines(longlong param_1,longlong param_2)

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
  ulonglong *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined8 in_r13;
  ulonglong uVar7;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  longlong in_LR;
  uint in_SRR0;
  ulonglong in_SRR1;
  int in_spr130;
  ulonglong in_spr131;
  
  *(ulonglong *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x40) = param_1;
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x50) = param_3;
  *(undefined *)(in_spr130 + 0xf) = (char)((uint)in_cr0 & 0xf);
  if (SUB41((uint)((int)in_SRR1 << 1) >> 0x1f,0)) {
    if ((bool)(((byte)((uint)((int)in_SRR1 << 0x10) >> 0x18) & 0x40) >> 6)) {
      uVar5 = *(uint *)(in_spr130 + 0x58) & 2;
      if (*(longlong *)(DWORD_ARRAY_00010330 + uVar5 * 2) != 0) {
        uVar4 = (uint)(*(ulonglong *)(DWORD_ARRAY_00010330 + uVar5 * 2 + 2) >>
                      (in_SRR0 >> 0x1b & 0x1e) + 0x20) & 3;
        uVar5 = (uint)*(longlong *)(DWORD_ARRAY_00010330 + uVar5 * 2);
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
           ((*(byte *)(in_SRR0 >> 0xd & 0xffff | 0x1f50000) >> (ulonglong)(in_SRR0 >> 10 & 4) & 0xf)
            != 0)) {
LAB_00001188:
          uVar5 = (uint)in_spr131 >> 7 & 0x40;
          uVar7 = (ulonglong)(((uint)in_spr131 & 0x1000) << 1) |
                  (ulonglong)uVar5 | in_spr131 & 0xffffffffffffdfbf;
          puVar3 = (ulonglong *)uVar7;
          *puVar3 = uVar7;
          sync(1);
          if (*(longlong *)((uint)puVar3 ^ 0x40) != 0) {
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
  *(ulonglong *)(in_spr130 + 0x28) =
       (ulonglong)
       ((uint)*(byte *)(in_spr130 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | (ulonglong)in_SRR0;
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



void FUN_00000484(int param_1,undefined8 *param_2,longlong param_3)

{
  param_1 = param_1 - (int)param_2;
  do {
    *(undefined8 *)(param_1 + (int)param_2) = *param_2;
    param_2 = param_2 + 1;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  return;
}



void FUN_000004a8(ulonglong param_1)

{
  do {
  } while ((param_1 & 0xffffffff) * 0x32 != 0);
  return;
}



ulonglong FUN_000004cc(void)

{
  ulonglong in_LR;
  
  return in_LR & 0xffffffffffff0000;
}



void FUN_000004d8(void)

{
  int in_TBLr;
  
  do {
  } while (in_TBLr == 0);
  return;
}



void FUN_000004e8(int param_1,ulonglong param_2,ulonglong *param_3)

{
  ulonglong uVar1;
  
  uVar1 = ((ulonglong)(uint)(param_1 << 0x10) | param_2 & 0xffffffff0000ffff) << 0x20 |
          (ulonglong)(uint)(param_1 << 0x10) | param_2 & 0xffff;
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
  longlong in_LR;
  ulonglong in_SRR0;
  ulonglong in_SRR1;
  int in_spr130;
  
  *(ulonglong *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((longlong)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(ulonglong *)(in_spr130 + 0x28) =
       (ulonglong)
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



ulonglong FUN_0000057c(uint param_1)

{
  if (1 < (param_1 >> 0x1c) - 8) {
    return 0;
  }
  return (ulonglong)(param_1 >> 0xe & 0x7ffc) | 0x6801f50000;
}



undefined8 FUN_000005a8(void)

{
  return 0x6801f58000;
}



undefined8 FUN_000005c0(void)

{
  return 0x6a01f6c000;
}



int FUN_000005d8(uint param_1)

{
  int in_r2;
  
  return (int)&PTR_BYTE_00010130 + (param_1 & 1) * 0x100 + in_r2;
}



int FUN_000005ec(uint param_1)

{
  int in_r2;
  
  return (int)DWORD_ARRAY_00010330 + (param_1 & 1) * 0x10 + in_r2;
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
  longlong in_LR;
  undefined4 in_DSISR;
  undefined4 in_DAR;
  ulonglong in_SRR0;
  ulonglong in_SRR1;
  int in_spr130;
  
  *(ulonglong *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((longlong)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(ulonglong *)(in_spr130 + 0x28) =
       (ulonglong)
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



undefined8 HvpGetFlashBaseAddress(void)

{
  return 0x80000200c8000000;
}



int HvpBuildSocMMIORegs(int param_1)

{
  return (int)&DWORD_00000000 + param_1;
}



longlong HvpBuildPciConfigRegs(longlong param_1)

{
  return param_1 + -0x7ffffdff30000000;
}



longlong FUN_000006cc(longlong param_1)

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
  longlong in_LR;
  ulonglong in_SRR0;
  ulonglong in_SRR1;
  int in_spr130;
  
  *(ulonglong *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((longlong)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(ulonglong *)(in_spr130 + 0x28) =
       (ulonglong)
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
  longlong in_LR;
  ulonglong in_SRR0;
  ulonglong in_SRR1;
  int in_spr130;
  
  *(ulonglong *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  if ((longlong)in_SRR1 < 0) {
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
  *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  *(ulonglong *)(in_spr130 + 0x28) =
       (ulonglong)
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
  ulonglong in_r0;
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
  longlong in_LR;
  ulonglong in_SRR0;
  ulonglong in_SRR1;
  int in_spr130;
  int in_spr131;
  
  *(ulonglong *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  uVar2 = (uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14
          | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc |
          (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf);
  if (-1 < (longlong)in_SRR1) {
    if ((bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
      *(ulonglong *)(in_spr130 + 0x28) = (ulonglong)uVar2 << 0x20 | in_SRR1 & 0xffffffff;
      *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
      *(undefined8 *)(in_spr130 + 0x30) = in_r13;
      if (in_r0 < 2) {
        uVar2 = *(uint *)(in_spr130 + 0x58);
        uVar4 = (uint)in_r0 & 1;
        *(uint *)(in_spr130 + 0x58) = uVar4 | uVar2 & 0xfffffffe;
        slbInvalidateAll();
        puVar7 = (undefined8 *)(&PTR_BYTE_00010130 + (uVar4 | uVar2 & 2) * 0x20);
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
        puVar7 = (undefined8 *)(&PTR_BYTE_00010130 + (*(uint *)(in_spr130 + 0x58) & 3) * 0x20);
        do {
          uVar5 = *puVar7;
          puVar7 = puVar7 + 1;
          slbMoveToEntry();
        } while (((uint)uVar5 >> 0xc & 0xf) != 0xf);
      }
      returnFromInterrupt();
      return param_1;
    }
    if (0x75 < (in_r0 & 0xffffffff)) {
      *(ulonglong *)(in_spr130 + 0x28) = (ulonglong)uVar2 << 0x20 | in_SRR1 & 0xffffffff;
      *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
      returnFromInterrupt();
      return param_1;
    }
    *(ulonglong *)(in_spr130 + 0x28) = (ulonglong)uVar2;
    *(longlong *)(in_spr130 + 0x20) = in_LR;
    pcVar1 = (code *)(&_SyscallTable)[(uint)in_r0];
    if (pcVar1 < &BYTE_00010000) {
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



void HvxStartupProcessors(void)

{
  int in_PIR;
  
  if (in_PIR != 0) {
    DWORD_ARRAY_0001ff00._240_8_ = 0;
    DWORD_ARRAY_0001ff00._248_8_ = 0;
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
  DWORD_ARRAY_0001ff00._240_8_ = 0x3fffc0003fffc00;
  DWORD_ARRAY_0001ff00._248_8_ = 0x3fffc0003fffc00;
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
  longlong in_LR;
  ulonglong in_SRR0;
  ulonglong in_SRR1;
  int in_spr130;
  
  *(ulonglong *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((longlong)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(ulonglong *)(in_spr130 + 0x28) =
       (ulonglong)
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



ulonglong HvpInvalidateCachelines(ulonglong param_1,int param_2)

{
  ulonglong uVar1;
  longlong lVar2;
  
  if (param_2 == 0) {
    return param_1;
  }
  lVar2 = (ulonglong)
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



ulonglong FUN_00000dc8(ulonglong param_1,int param_2)

{
  ulonglong uVar1;
  longlong lVar2;
  
  if (param_2 == 0) {
    return param_1;
  }
  lVar2 = (ulonglong)
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



void HvpRelocateCacheLines(undefined8 param_1,longlong param_2,longlong param_3)

{
  undefined8 in_r0;
  longlong lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  longlong lVar4;
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
  longlong lVar20;
  
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



void HvpSaveCachelines(longlong param_1,longlong param_2)

{
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



undefined8 _v_VPU_UNAVAILABLE(undefined8 param_1,undefined8 param_2,undefined8 param_3)

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
  longlong in_LR;
  ulonglong in_SRR0;
  ulonglong in_SRR1;
  int in_spr130;
  
  *(ulonglong *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  if ((longlong)in_SRR1 < 0) {
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
  *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  *(ulonglong *)(in_spr130 + 0x28) =
       (ulonglong)
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



longlong FUN_00000fd4(void)

{
  undefined8 in_r0;
  longlong lVar1;
  longlong lVar2;
  
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



undefined8 FUN_00001018(undefined4 param_1)

{
  ushort *puVar1;
  int iVar2;
  int in_r13;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  longlong in_LR;
  undefined4 in_DSISR;
  uint in_SRR0;
  ulonglong in_SRR1;
  undefined8 in_SPRG0;
  
  if (in_SRR0 == 0x80075f90) {
    returnFromInterrupt();
    return *(undefined8 *)(in_r13 + 0x40);
  }
  *(undefined4 *)(in_r13 + 100) = in_DSISR;
  *(undefined4 *)(in_r13 + 0x60) = param_1;
  *(undefined8 *)(in_r13 + 0x30) = in_SPRG0;
  *(ulonglong *)(in_r13 + 0x28) =
       (ulonglong)
       ((uint)*(byte *)(in_r13 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(ulonglong *)(in_r13 + 0x20) = in_LR << 0x20 | (ulonglong)in_SRR0;
  if (!(bool)(((byte)(in_SRR1 >> 0xc) & 0xf) >> 2 & 1)) {
    returnFromInterrupt();
    return *(undefined8 *)(in_r13 + 0x40);
  }
  *(undefined8 *)(in_r13 + 0x50) = *(undefined8 *)(in_r13 + 0x50);
  *(undefined8 *)(in_r13 + 0x40) = *(undefined8 *)(in_r13 + 0x40);
  iVar2 = 0;
  slbInvalidateAll();
  do {
    puVar1 = (ushort *)(iVar2 + 0x8e0);
    iVar2 = iVar2 + 2;
    slbMoveToEntry();
  } while (*puVar1 >> 0xc != 0xf);
  returnFromInterrupt();
  return *(undefined8 *)(in_r13 + 0x40);
}



undefined8 FUN_00001070(uint param_1)

{
  uint uVar1;
  ushort *puVar2;
  ulonglong *puVar3;
  int iVar4;
  uint in_r13;
  ulonglong uVar5;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  longlong in_LR;
  undefined4 in_DSISR;
  uint in_SRR0;
  ulonglong in_SRR1;
  undefined8 in_SPRG0;
  int in_spr130;
  ulonglong in_spr131;
  dword local_res0;
  
  uVar1 = *(uint *)(param_1 >> 0x14 & 0xffc | (in_r13 & 0xffff0000) + 0x10000);
  if (((uVar1 & 1) != 0) && ((*(uint *)((param_1 >> 10 & 0xffc) + (uVar1 & 0x1ffff000)) & 1) != 0))
  {
    uVar1 = (uint)in_spr131 >> 7 & 0x40;
    uVar5 = (ulonglong)(((uint)in_spr131 & 0x1000) << 1) |
            (ulonglong)uVar1 | in_spr131 & 0xffffffffffffdfbf;
    puVar3 = (ulonglong *)uVar5;
    *puVar3 = uVar5;
    sync(1);
    if (*(longlong *)((uint)puVar3 ^ 0x40) != 0) {
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
  *(ulonglong *)(in_r13 + 0x28) =
       (ulonglong)
       ((uint)*(byte *)(in_r13 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(ulonglong *)(in_r13 + 0x20) = in_LR << 0x20 | (ulonglong)in_SRR0;
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



undefined8 FUN_00001248(uint param_1)

{
  ushort *puVar1;
  ulonglong *puVar2;
  uint uVar3;
  int iVar4;
  ulonglong uVar5;
  int in_r13;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  longlong in_LR;
  undefined4 in_DSISR;
  uint in_SRR0;
  ulonglong in_SRR1;
  undefined8 in_SPRG0;
  int in_spr130;
  ulonglong in_spr131;
  
  uVar3 = param_1 >> 0xe & 0xfffc;
  if ((uVar3 == 0xfffc) || ((*(uint *)(uVar3 + 0x1f70000) & 1) != 0)) {
    uVar3 = (uint)in_spr131 >> 7 & 0x40;
    uVar5 = (ulonglong)(((uint)in_spr131 & 0x1000) << 1) |
            (ulonglong)uVar3 | in_spr131 & 0xffffffffffffdfbf;
    puVar2 = (ulonglong *)uVar5;
    *puVar2 = uVar5;
    sync(1);
    if (*(longlong *)((uint)puVar2 ^ 0x40) != 0) {
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
  *(ulonglong *)(in_r13 + 0x28) =
       (ulonglong)
       ((uint)*(byte *)(in_r13 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(ulonglong *)(in_r13 + 0x20) = in_LR << 0x20 | (ulonglong)in_SRR0;
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



undefined8 FUN_000012f0(uint param_1)

{
  ushort *puVar1;
  ulonglong *puVar2;
  uint uVar3;
  int iVar4;
  ulonglong uVar5;
  uint in_r13;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  longlong in_LR;
  undefined4 in_DSISR;
  ulonglong in_SRR0;
  ulonglong in_SRR1;
  undefined8 in_SPRG0;
  int in_spr130;
  ulonglong in_spr131;
  
  if ((*(byte *)((param_1 >> 0x11 & 0xfff) + (in_r13 & 0xffff0000) + 0x11000) >>
       (ulonglong)(param_1 >> 0xe & 4) & 0xf) != 0) {
    uVar3 = (uint)in_spr131 >> 7 & 0x40;
    uVar5 = (ulonglong)(((uint)in_spr131 & 0x1000) << 1) |
            (ulonglong)uVar3 | in_spr131 & 0xffffffffffffdfbf;
    puVar2 = (ulonglong *)uVar5;
    *puVar2 = uVar5;
    sync(1);
    if (*(longlong *)((uint)puVar2 ^ 0x40) != 0) {
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
  *(ulonglong *)(in_r13 + 0x28) =
       (ulonglong)
       ((uint)*(byte *)(in_r13 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(ulonglong *)(in_r13 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
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



undefined8 FUN_00001338(uint param_1)

{
  ushort *puVar1;
  ulonglong *puVar2;
  uint uVar3;
  int iVar4;
  ulonglong uVar5;
  uint in_r13;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  longlong in_LR;
  undefined4 in_DSISR;
  ulonglong in_SRR0;
  ulonglong in_SRR1;
  undefined8 in_SPRG0;
  int in_spr130;
  ulonglong in_spr131;
  
  if ((*(byte *)((int)&DWORD_00010c00 + (param_1 >> 0x19 & 0xf) + (in_r13 & 0xffff0000)) >>
       (ulonglong)(param_1 >> 0x16 & 4) & 0xf) != 0) {
    uVar3 = (uint)in_spr131 >> 7 & 0x40;
    uVar5 = (ulonglong)(((uint)in_spr131 & 0x1000) << 1) |
            (ulonglong)uVar3 | in_spr131 & 0xffffffffffffdfbf;
    puVar2 = (ulonglong *)uVar5;
    *puVar2 = uVar5;
    sync(1);
    if (*(longlong *)((uint)puVar2 ^ 0x40) != 0) {
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
  *(ulonglong *)(in_r13 + 0x28) =
       (ulonglong)
       ((uint)*(byte *)(in_r13 + 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
        (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc
        | (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf)) << 0x20 |
       in_SRR1 & 0xffffffff;
  *(ulonglong *)(in_r13 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
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
  longlong in_LR;
  ulonglong in_SRR0;
  ulonglong in_SRR1;
  int in_spr130;
  
  *(ulonglong *)(in_spr130 + 0x38) = ZEXT48(register0x0000000c);
  *(undefined8 *)(in_spr130 + 0x48) = param_2;
  *(undefined8 *)(in_spr130 + 0x30) = in_r13;
  *(ulonglong *)(in_spr130 + 0x20) = in_LR << 0x20 | in_SRR0 & 0xffffffff;
  if ((longlong)in_SRR1 < 0) {
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    instructionSynchronize();
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  *(ulonglong *)(in_spr130 + 0x28) =
       (ulonglong)
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



ulonglong HvpFlushSingleTb(ulonglong param_1,uint param_2)

{
  ulonglong uVar1;
  
  uVar1 = param_1 & 0xfffffffffffff000;
  param_2 = param_2 >> (ulonglong)((uint)param_1 >> 0x1b & 0x1e);
  if ((param_2 & 3) == 0) {
    TLBInvalidateEntryLocal(uVar1);
  }
  else {
    uVar1 = (ulonglong)((param_2 & 1) << 0xc) | param_1 & 0xffffffffffffe000;
    TLBInvalidateEntryLocal(uVar1,ZEXT48(register0x0000000c),0,0,0);
  }
  eieioOp();
  sync(2);
  return uVar1;
}



void HvxFlushEntireTb(void)

{
  longlong lVar1;
  longlong lVar2;
  
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
  char cVar1;
  uint uVar2;
  longlong in_r2;
  int iVar3;
  longlong lVar4;
  int iVar5;
  dword dVar6;
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
  
  iVar3 = (int)in_r2;
  uVar2 = *(uint *)(iVar3 + 0x10000);
  cVar1 = *(char *)((int)DWORD_ARRAY_00016260 + iVar3 + 0x235);
  if ((cVar1 == '\0') || (cVar1 == '\x02')) {
    dVar6 = 0xffffffff;
  }
  else {
    dVar6 = 0;
    lVar4 = HvpGetFlashBaseAddress();
    FUN_00000484(&local_230,lVar4 + 0x200,0x40);
    iVar3 = (int)in_r2;
    if (((local_230 == 0xdb4b) && (local_228 == 0x120)) && (local_224 == 0x200)) {
      j_XeCryptAesKey(&local_390,0x20);
      j_XeCryptAesCbc(&local_390,&local_110,0xe0,&local_110,&local_220,0);
      j_XeCryptHmacSha(0x20,0x10,&local_230,0x10,&local_110,0xe0,0,0);
      iVar3 = (int)in_r2;
      iVar5 = FUN_0000b3c0(&local_210,&local_30,ZEXT48(&UNK_0001059c) + in_r2,in_r2 + 0x16280);
      if (((iVar5 != 0) && (local_110 == 1)) && (local_10c != 0)) {
        dVar6 = local_100;
      }
    }
  }
  *(dword *)((int)DWORD_ARRAY_00016260 + iVar3 + 0x6cc) = dVar6;
  HvpReleaseSpinLock((ulonglong)uVar2);
  return;
}



// WARNING: Removing unreachable block (ram,0x00001c60)

void FUN_00001c50(void)

{
  byte bVar1;
  int in_r2;
  
  bVar1 = *(byte *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x235);
  if (bVar1 == 0xff) {
    return;
  }
  if (bVar1 < 5) {
    if ((*(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6cc) & 1) != 0) {
      return;
    }
    if (*(byte *)((int)DWORD_ARRAY_00010480 + (uint)bVar1 + in_r2) <=
        *(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xe4)) {
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



void nullsub_1(void)

{
  return;
}



void j_XeCryptMemDiff(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptMemDiff();
  return;
}



undefined8 HvxGetVersions(void)

{
  return 0x760000044880000;
}



void FUN_00001ce0(void)

{
  uint uVar1;
  longlong lVar2;
  int in_r2;
  undefined8 uVar3;
  ulonglong *puVar5;
  int iVar6;
  ulonglong uVar4;
  undefined8 *puVar7;
  ulonglong uVar8;
  uint uVar9;
  ulonglong *puVar10;
  ulonglong in_TBLr;
  word local_150;
  word local_f0;
  word local_50;
  dword local_3c;
  
  uVar3 = __Save_R12_26_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  puVar5 = (ulonglong *)HvpBuildSocMMIORegs(0x26000);
  iVar6 = HvpBuildSocMMIORegs(0x20000);
  uVar8 = 0;
  puVar7 = (undefined8 *)&local_150;
  do {
    lVar2 = uVar8 << 3;
    uVar8 = uVar8 + 0x40;
    *puVar7 = *(undefined8 *)((int)lVar2 + iVar6);
    puVar7 = puVar7 + 1;
  } while ((uVar8 & 0xffffffff) < 0x300);
  uVar8 = 0;
  puVar10 = (ulonglong *)&local_f0;
  iVar6 = 0x14;
  do {
    uVar9 = 0;
    do {
      do {
      } while ((*puVar5 & 0x8000000000000000) != 0);
      uVar8 = puVar5[1] ^ uVar8;
    } while ((((uVar9 < 3) || (uVar4 = j_XeCryptHammingWeight(uVar8), (uVar4 & 0xffffffff) < 0x1a))
             || (0x26 < (uVar4 & 0xffffffff))) && (uVar9 = uVar9 + 1, uVar9 < 100));
    iVar6 = iVar6 + -1;
    uVar4 = (ulonglong)(uint)((int)uVar8 + (int)(uVar8 / 0x1d) * -0x1d) & 0x3f;
    uVar8 = (in_TBLr << uVar4 | in_TBLr >> 0x40 - uVar4) & 1 ^ uVar8;
    *puVar10 = uVar8;
    puVar10 = puVar10 + 1;
  } while (iVar6 != 0);
  j_XeCryptSha(&local_f0,0xa0,&local_150,0x60,0x18,8,&local_50,0x14);
  j_XeCryptRc4Key(uVar3,&local_50,0x14);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



void FUN_00001e08(void)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  longlong in_r2;
  longlong lVar4;
  short *psVar5;
  qword local_a0;
  word local_90;
  dword local_38;
  
  __Save_R12_27_thru_31();
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  j_XeCryptShaInit(&local_90);
  lVar4 = ZEXT48(&DWORD_000105a8) + in_r2;
  while( true ) {
    psVar5 = (short *)lVar4;
    sVar1 = *psVar5;
    if ((sVar1 == 3) && (3 < *(uint *)(psVar5 + 2))) break;
    uVar3 = *(uint *)(psVar5 + 2);
    if (psVar5[1] != 0) {
      uVar3 = *(uint *)(((uint)(ushort)psVar5[1] - 1) * 4 + (int)in_r2 + 0x16938) | uVar3;
    }
    if (sVar1 == 0) {
      HvpBuildSocMMIORegs((ulonglong)uVar3);
    }
    else {
      if (sVar1 == 1) {
        HvpBuildSocMMIORegs((ulonglong)uVar3);
      }
    }
    j_XeCryptShaUpdate(&local_90,&local_a0,8);
    if (sVar1 == 3) {
      j_XeCryptShaFinal(&local_90,(ulonglong)uVar3 * 0x10 + in_r2 + 0x100c0,0x10);
      j_XeCryptShaInit(&local_90);
    }
    lVar4 = lVar4 + 8;
  }
  HvpReleaseSpinLock((ulonglong)uVar2);
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
  ulonglong in_PVR;
  word local_a0;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar3 = *(uint *)(in_r2 + 0x10000);
  uVar5 = HvpGetFlashBaseAddress();
  FUN_00000484(&local_a0,uVar5,0x10);
  *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) = in_PVR & 0xffffffff;
  puVar6 = (undefined *)HvpBuildPciConfigRegs(0x8000);
  if (CONCAT11(puVar6[1],*puVar6) == -0x1415) {
    *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6bc) =
         *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6bc) | 0x8000;
  }
  iVar4 = in_r2;
  puVar6 = (undefined *)HvpBuildPciConfigRegs(&WORD_00010002);
  uVar1 = puVar6[1];
  uVar2 = *puVar6;
  pbVar7 = (byte *)HvpBuildPciConfigRegs(&PTR_PTR_DWORD_ARRAY_00010008);
  *(uint *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x6d0) =
       (uint)CONCAT11(uVar1,uVar2) << 0x10 | (uint)*pbVar7;
  if ((local_a0 & 0xf0) == 0x60) {
    *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6bc) =
         *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6bc) | 2;
  }
  iVar8 = HvpBuildSocMMIORegs(0x1ff00);
  if (*(int *)(iVar8 + 0x20) == 0x42440302) {
    uVar10 = *(uint *)(iVar8 + 0x24);
    uVar9 = uVar10 >> 0x18 & 0xf;
    *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6bc) =
         *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6bc) | 4;
    uVar10 = uVar10 >> 0x1c;
  }
  else {
    uVar10 = 0;
    uVar9 = 1;
  }
  *(int *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x6d8) = uVar10 << 0x14;
  *(int *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x6dc) = uVar9 << 0x14;
  FUN_00001e08();
  HvpReleaseSpinLock((ulonglong)uVar3);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_000020b0(int param_1)

{
  int iVar1;
  longlong in_r2;
  longlong lVar2;
  undefined8 *puVar3;
  qword *pqVar4;
  undefined *puVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  qword local_30;
  qword local_28;
  qword local_18;
  qword local_10;
  qword local_8;
  
  puVar3 = (undefined8 *)HvpBuildSocMMIORegs(0x24000);
  lVar7 = in_r2 + 0x10100;
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
    FUN_0000b488(lVar7,0x30);
  }
  *puVar3 = *(undefined8 *)lVar7;
  eieioOp();
  iVar1 = (int)in_r2;
  puVar3[1] = *(undefined8 *)((int)DWORD_ARRAY_0001000c + iVar1 + 0xfc);
  eieioOp();
  puVar3[0x200] = *(undefined8 *)lVar7;
  eieioOp();
  puVar3[0x201] = *(undefined8 *)((int)DWORD_ARRAY_0001000c + iVar1 + 0xfc);
  eieioOp();
  puVar3[0x208] = *(undefined8 *)((int)DWORD_ARRAY_0001000c + iVar1 + 0x104);
  eieioOp();
  puVar3[0x209] = *(undefined8 *)((int)DWORD_ARRAY_0001000c + iVar1 + 0x10c);
  eieioOp();
  pqVar4 = &local_30;
  in_r2 = in_r2 + 0x10110;
  lVar7 = 0x10;
  do {
    puVar5 = (undefined *)in_r2;
    in_r2 = in_r2 + 1;
    *(undefined *)pqVar4 = *puVar5;
    pqVar4 = (qword *)((int)pqVar4 + 1);
    lVar7 = lVar7 + -1;
  } while (lVar7 != 0);
  FUN_0000b378(&local_30,lVar2 + 0x10488);
  puVar3[8] = local_30;
  eieioOp();
  puVar3[9] = local_28;
  eieioOp();
  puVar3[0x10] = *(undefined8 *)((int)DWORD_ARRAY_0001000c + iVar1 + 0x114);
  eieioOp();
  puVar3[0x11] = *(undefined8 *)((int)DWORD_ARRAY_0001000c + iVar1 + 0x11c);
  eieioOp();
  puVar3[0x210] = *(undefined8 *)((int)DWORD_ARRAY_0001000c + iVar1 + 0x114);
  eieioOp();
  puVar3[0x211] = *(undefined8 *)((int)DWORD_ARRAY_0001000c + iVar1 + 0x11c);
  eieioOp();
  instructionSynchronize();
  instructionSynchronize();
  return;
}



void generate_hypervisor_hash_F0(void) {
  uint uVar1;
  uint uVar2;
  longlong in_r2;
  undefined8 uVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  uint uVar7;
  uint uVar8;
  longlong lVar9;
  undefined8 in_spr131;
  word local_90;
  dword local_38;
  
  __Save_R12_28_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  j_XeCryptShaInit(&local_90);
  uVar8 = 0;
  lVar9 = in_r2 + 0x10710;
  do {
    uVar7 = *(int *)lVar9 + 0x7f;
    uVar6 = (ulonglong)(((int *)lVar9)[1] & 0xffffff80);
    uVar2 = uVar7 & 0xffffff80;
    if (uVar2 < uVar6) {
      uVar6 = uVar6 - uVar2;
      uVar5 = uVar6 >> 7 & 0x1ffffff;
      HvpSaveCachelines((ulonglong)(uVar7 >> 0x10) * 0x200010000 + ((ulonglong)uVar2 & 0xffff));
      if (0x3ffff < uVar2) {
        uVar3 = _v_MACHINE_CHECK_0();
        FUN_000084a8(0,0x200);
        FUN_000084a8(&BYTE_00010000,0x200);
        FUN_000084a8(FUN_00020000,0x200);
        FUN_000084a8(FUN_00030000,0x200);
        FUN_000084a8(in_spr131,0x200);
        uVar4 = FUN_000002d8();
        FUN_000084a8(uVar4,0x200);
        FUN_000084a8(uVar3,0x200);
        FUN_000020b0(uVar5);
        if ((uVar5 & 0xffffffff) == 0) {
          generate_hypervisor_hash_F0();
        }
        else {
          HvpSaveCachelines(0,0x200);
          HvpSaveCachelines(&BYTE_00010000,0x200);
          HvpSaveCachelines(FUN_00020000,0x200);
          HvpSaveCachelines(FUN_00030000,0x200);
          HvpSaveCachelines(in_spr131,0x200);
          uVar4 = FUN_000002d8();
          HvpSaveCachelines(uVar4,0x200);
          HvpSaveCachelines(uVar3,0x200);
        }
        return;
      }
      uVar3 = HvpBuildSocMMIORegs((ulonglong)(uVar2 >> 6) + 0x10000);
      j_XeCryptShaUpdate(&local_90,uVar3,uVar6 >> 6 & 0x3ffffff);
    }
    uVar8 = uVar8 + 1;
    lVar9 = lVar9 + 8;
  } while (uVar8 < 6);
  j_XeCryptShaFinal(&local_90,in_r2 + 0x100f0,0x10);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_000022f8(undefined8 param_1,ulonglong param_2){
  undefined8 uVar1;
  undefined8 in_spr131;
  qword local_18;
  qword local_10;
  qword local_8;
  
  FUN_000084a8(0,0x200);
  FUN_000084a8(&BYTE_00010000,0x200);
  FUN_000084a8(FUN_00020000,0x200);
  FUN_000084a8(FUN_00030000,0x200);
  FUN_000084a8(in_spr131,0x200);
  uVar1 = FUN_000002d8();
  FUN_000084a8(uVar1,0x200);
  FUN_000084a8(param_1,0x200);
  FUN_000020b0(param_2);
  if ((param_2 & 0xffffffff) == 0) {
    generate_hypervisor_hash_F0();
  }
  else {
    HvpSaveCachelines(0,0x200);
    HvpSaveCachelines(&BYTE_00010000,0x200);
    HvpSaveCachelines(FUN_00020000,0x200);
    HvpSaveCachelines(FUN_00030000,0x200);
    HvpSaveCachelines(in_spr131,0x200);
    uVar1 = FUN_000002d8();
    HvpSaveCachelines(uVar1,0x200);
    HvpSaveCachelines(param_1,0x200);
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void ComputeRSAOutput(void) {
  uint uVar1;
  longlong in_r2;
  int iVar2;
  longlong lVar3;
  word local_c0;
  word local_a0;
  dword local_20;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  FUN_0000b488(&local_c0,0x14);
  iVar2 = j_HvSetupMemEncryptionKey(in_r2 + 0x10100,0x30,&local_a0,0x80,0,&local_c0);
  if (iVar2 != 0) {
    FUN_0000b480(&local_a0,0x80);
    j_XeCryptBnQw_SwapDwQwLeBe(&local_a0,&local_a0,0x10);
    lVar3 = in_r2 + 0x10040;
    iVar2 = j_XeCryptBnQwNeRsaPubCrypt(&local_a0,lVar3,ZEXT48(DWORD_ARRAY_00010350) + in_r2);
    if (iVar2 == 0) {
      memset(lVar3,0,0x80);
    }
    else {
      j_XeCryptBnQw_SwapDwQwLeBe(lVar3,lVar3,0x10);
    }
  }
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



undefined8 HvxFlushSingleTb(ulonglong param_1)

{
  qword local_8;
  
  HvpFlushSingleTb(param_1 & 0xffffffff,0xfa2aa00);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 HvxPostOutput(longlong param_1)

{
  int iVar1;
  qword local_10;
  qword local_8;
  
  iVar1 = HvpBuildSocMMIORegs(0x61000);
  *(longlong *)(iVar1 + 0x10) = param_1 << 0x38;
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
  qword local_10;
  qword local_8;
  
  if ((((param_1 & 7) == 0) &&
      ((*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700 ||
       (0xffff < param_1 - 0x40000)))) && ((param_1 == 0x61198 || (param_1 == 0x61190)))) {
    puVar2 = (undefined8 *)HvpBuildSocMMIORegs((ulonglong)param_1);
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
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (((param_1 & 7) == 0) &&
     (((*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700 ||
       (0xffff < param_1 - 0x40000)) && (param_1 == 0x61198)))) {
    puVar1 = (undefined8 *)HvpBuildSocMMIORegs(0x61198);
    *puVar1 = param_2;
    eieioOp();
  }
  return 0;
}



undefined8 HvxTest(void)

{
  return 0;
}



undefined8 HvxFsbInterrupt(void)

{
  int in_r2;
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 in_spr131;
  
  __Save_R12_28_thru_31();
  uVar3 = 0;
  iVar1 = HvpBuildSocMMIORegs(0x30000);
  iVar2 = HvpBuildSocMMIORegs(0x40000);
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
    if ((*(ulonglong *)(iVar2 + 0x3000) & 0x400000000000) != 0) {
      if (*(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6d0) < 0x58110012) {
        uVar3 = FUN_000004cc();
        FUN_000084a8(uVar3,0x200);
        FUN_000084a8(in_spr131,0x40);
        *(undefined8 *)(iVar2 + 0x7120) = 0x40000000000;
        eieioOp();
        do {
        } while ((*(ulonglong *)(iVar2 + 0x7100) >> 0x20 & 0xf) != 0xe);
        uVar3 = 1;
      }
      *(ulonglong *)(iVar2 + 0x3000) =
           *(ulonglong *)(iVar2 + 0x3000) & 0xffff9bffffffffff | 0x180000000000;
      eieioOp();
      *(undefined8 *)(iVar1 + 0x3010) = 0xfffffdffffffffff;
      eieioOp();
    }
    *(ulonglong *)(iVar2 + 0x3010) = ~*(ulonglong *)(iVar2 + 0x3200);
    eieioOp();
    *(undefined8 *)(iVar2 + 0x3200) = 0;
    eieioOp();
  }
  *(ulonglong *)(iVar1 + 0x3010) = ~*(ulonglong *)(iVar1 + 0x3200);
  eieioOp();
  *(undefined8 *)(iVar1 + 0x3200) = 0;
  eieioOp();
  return uVar3;
}



undefined8
HvxLockL2(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
         ulonglong param_5)

{
  longlong in_r2;
  ulonglong uVar1;
  int iVar2;
  int iVar3;
  ulonglong uVar4;
  
  uVar1 = __Save_R12_26_thru_31();
  HvpAquireSpinLock(in_r2 + 0x16928);
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
    iVar2 = HvpBuildSocMMIORegs(0x60000);
    *(ulonglong *)(iVar2 + 0x300) = param_5;
    eieioOp();
    sync(0);
  }
  FUN_000001e0(in_r2 + 0x16928);
  return 0;
}



ulonglong HvpPhysicalToReal(uint param_1,uint param_2)

{
  if ((param_1 - 0x40000 < 0x1ffc0000) && (param_2 <= 0x20000000 - param_1)) {
    return (ulonglong)param_1 | 0x8000000000000000;
  }
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



ulonglong FUN_00002a20(uint param_1,uint param_2)

{
  undefined8 uVar1;
  
  if ((param_1 + 0x80000000 < 0x20000000) && (param_2 <= 0xa0000000 - param_1)) {
                    // WARNING: Treating indirect jump as call
    uVar1 = FUN_0002afd8();
    return uVar1;
  }
  if ((param_1 - 0x40000 < 0x1ffc0000) && (param_2 <= 0x20000000 - param_1)) {
    return (ulonglong)param_1 | 0x8000000000000000;
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
      HvpInvalidateCachelines((ulonglong)param_1);
    }
  }
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00002b88)
// WARNING: Removing unreachable block (ram,0x00002b98)
// WARNING: Removing unreachable block (ram,0x00002bb0)

ulonglong HvxZeroPage(ulonglong param_1)

{
  uint uVar1;
  longlong lVar2;
  qword local_10;
  qword local_8;
  
  lVar2 = 0x40000;
  if (0x3ffff < (param_1 & 0xffffffff)) {
    _v_MACHINE_CHECK_0();
  }
  uVar1 = (int)param_1 << 0xc;
  if ((((ulonglong)uVar1 - lVar2 & 0xffffffff) < 0x1ffc0000) &&
     (0xfff < (0x20000000 - (ulonglong)uVar1 & 0xffffffff))) {
    HvpZeroCacheLines((ulonglong)uVar1 | 0x8000000000000000,0x20);
    return param_1;
  }
  _v_MACHINE_CHECK_0();
  return 0;
}



void FUN_00002bc0(void)

{
  int in_r2;
  ulonglong *puVar1;
  ulonglong *puVar2;
  int iVar3;
  int iVar4;
  ulonglong *puVar5;
  
  __Save_R12_28_thru_31();
  HvxPostOutput(0x59);
  puVar1 = (ulonglong *)HvpBuildSocMMIORegs(0x30000);
  puVar2 = (ulonglong *)HvpBuildSocMMIORegs(0x40000);
  iVar3 = HvpBuildSocMMIORegs(0x24000);
  iVar4 = HvpBuildSocMMIORegs(0x60000);
  puVar5 = (ulonglong *)HvpBuildSocMMIORegs(0x48000);
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
    puVar2[0x600] = puVar2[0x600] & 0xffff9bffffffffff | 0x180000000000;
    eieioOp();
    if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
      puVar2[0x622] = 0xffffbfffffffffff;
      eieioOp();
    }
  }
  puVar1[0x622] = 0xfffffdffffffffff;
  eieioOp();
  *(ulonglong *)(iVar4 + 0x700) = *(ulonglong *)(iVar4 + 0x700) | 0xe0000000000000;
  eieioOp();
  *(ulonglong *)(iVar4 + 0x840) =
       *(ulonglong *)(iVar4 + 0x840) & 0xffffbfffffffffff | 0x3c0000000000;
  eieioOp();
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
    *puVar2 = *puVar2 & 0x1ff03fffffffffff | 0x4009000000000000;
    eieioOp();
    if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
      *puVar5 = *puVar5 & 0xa1ffffffffffffff | 0x100400000000000;
      eieioOp();
    }
  }
  *puVar1 = *puVar1 | 0x4000000000000000;
  eieioOp();
  if (*(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) - 0x710500U < 0x200) {
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
  DWORD_ARRAY_00000018 = *(undefined8 *)(iVar3 + 0x10b8);
                    // WARNING: Read-only address (ram,0x00000018) is written
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_00002dd8(void)

{
  byte bVar1;
  longlong in_r2;
  ushort *puVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  qword local_10;
  qword local_8;
  
  HvxPostOutput(0x5a);
  FUN_00000fd4();
  puVar5 = (uint *)FUN_000002d8();
  puVar2 = (ushort *)FUN_000005c0();
  in_r2 = ZEXT48(&DAT_00010440) + in_r2;
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



void FUN_00002e90(void)

{
  uint uVar1;
  uint uVar2;
  int in_r2;
  undefined8 uVar3;
  byte *pbVar4;
  uint *puVar5;
  ulonglong uVar6;
  word local_130;
  dword local_2c;
  
  __Save_R12_28_thru_31();
  uVar6 = 0;
  uVar1 = *(uint *)(in_r2 + 0x10000);
  HvxPostOutput(0x5b);
  FUN_0000b0e8();
  FUN_00001ce0(&local_130);
  HvpSetRMCI(0);
  puVar5 = (uint *)FUN_0000057c(0xffffffff80040000);
  pbVar4 = (byte *)0x40000;
  while( true ) {
    HvpRelocateCacheLines(pbVar4,((ulonglong)*puVar5 & 0x3fffffffffffc0) << 10 | 0x8000000000000000,0x200);
    uVar2 = *puVar5;
    if ((uVar2 & 0xc0000000) == 0x40000000) {
      uVar6 = ((ulonglong)uVar2 & 0xffffffc0) << 10 | 0x8000000000000000;
    }
    if ((uVar2 & 0x20) != 0) break;
    puVar5 = puVar5 + 1;
    pbVar4 = &BYTE_00010000 + (int)pbVar4;
  }
  HvpSetRMCI(1);
  FUN_000022f8(uVar6,0);
  FUN_000022f8(uVar6,1);
  HvpSetRMCI(0);
  FUN_0000b0c0(0x80060000,0);
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
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



void FUN_00002ff0(void)

{
  qword local_8;
  
  HvxPostOutput(0x5c);
  FUN_0000b0b8();
  FUN_0000b0a8();
  FUN_0000b0c8();
  FUN_0000b0e0();
  FUN_0000b0f0();
  FUN_0000b108();
  FUN_00008478();
  FUN_0000b110();
  FUN_0000b120();
  FUN_0000b158();
  return;
}



void FUN_00003040(void)

{
  int in_r2;
  int iVar1;
  qword local_8;
  
  HvxPostOutput(0x5e);
  FUN_0000b148();
  if ((*(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) - 0x710500U < 0x200) &&
     (0x5831000f < *(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6d0))) {
    iVar1 = HvpBuildSocMMIORegs(0x40000);
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



// WARNING: Removing unreachable block (ram,0x00003134)
// WARNING: Removing unreachable block (ram,0x00003144)
// WARNING: Removing unreachable block (ram,0x0000315c)

void FUN_00003100(void)

{
  int in_r2;
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
  if ((*(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6bc) & 0x8000) == 0) {
    FUN_00003040();
  }
  return;
}



void HvpRelocateEncryptedToPhysical(ulonglong param_1,uint param_2)

{
  uint uVar1;
  undefined8 in_r0;
  longlong lVar2;
  undefined8 *puVar3;
  undefined8 *puVar5;
  ulonglong uVar4;
  ulonglong uVar6;
  longlong lVar7;
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
  ulonglong uVar23;
  
  if (((((param_1 & 0x7f) == 0) && (param_2 != 0)) && ((param_2 & 0x7f) == 0)) &&
     (((param_1 >> 0x28 == 0x800003 &&
       (uVar1 = (uint)param_1 & 0x3fffffff, uVar1 - 0x40000 < 0x1ffc0000)) &&
      (param_2 <= 0x20000000 - uVar1)))) {
    uVar6 = (ulonglong)(param_2 >> 7);
    uVar4 = (ulonglong)uVar1 | 0x8000000000000000;
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



void HvpRelocateProtectedToPhysical(ulonglong param_1,ulonglong param_2,int param_3)

{
  uint uVar1;
  undefined8 in_r0;
  longlong lVar2;
  undefined8 *puVar3;
  undefined8 *puVar5;
  ulonglong uVar4;
  ulonglong uVar6;
  longlong lVar7;
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
  ulonglong uVar23;
  
  if ((((((param_1 & 0x7f) == 0) && ((param_2 & 0xffffffff) != 0)) && ((param_2 & 0x7f) == 0)) &&
      (((param_2 & 0xffffffff) < ZEXT48(&BYTE_00010001) &&
       (((((param_2 & 0xffffffff) + param_1) - 1 ^ param_1) & 0xffffffffffff0000) == 0)))) &&
     ((param_3 - 4U < 0x3c && (param_1 >> 0x20 == ((ulonglong)(uint)(param_3 << 1) | 0x80000100)))))
  {
    uVar1 = (uint)param_1 & 0x3fffffff;
    if ((((ulonglong)uVar1 - 0x40000 & 0xffffffff) < 0x1ffc0000) &&
       ((param_2 & 0xffffffff) <= (0x20000000 - (ulonglong)uVar1 & 0xffffffff))) {
      uVar6 = param_2 >> 7 & 0x1ffffff;
      uVar4 = (ulonglong)uVar1 | 0x8000000000000000;
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



ulonglong FUN_00003570(byte *param_1,int param_2)

{
  byte bVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  
  uVar2 = 0;
  while (param_2 != 0) {
    bVar1 = *param_1;
    param_2 = param_2 + -1;
    param_1 = param_1 + 1;
    uVar2 = bVar1 | uVar2;
  }
  uVar3 = countLeadingZeros((int)uVar2);
  return (ulonglong)((uint)uVar3 >> 5 & 1);
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
  longlong lVar2;
  word local_e0;
  dword local_30;
  
  lVar2 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  j_XeCryptHmacShaInit(&local_e0,0x20,0x10);
  j_XeCryptHmacShaUpdate(&local_e0,lVar2 + 0x1c,0xd4);
  j_XeCryptHmacShaUpdate(&local_e0,lVar2 + 0x100,0x1cf8);
  j_XeCryptHmacShaUpdate(&local_e0,lVar2 + 0x1ef8,0x2108);
  j_XeCryptHmacShaFinal(&local_e0,param_2,param_3);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



void FUN_000036a8(void)

{
  uint uVar1;
  int in_r2;
  longlong lVar2;
  longlong lVar3;
  qword local_60;
  dword local_54;
  word local_50;
  word local_40;
  dword local_30;
  
  lVar2 = __Save_R12_29_thru_31();
  lVar3 = lVar2 + 0x10;
  uVar1 = *(uint *)(in_r2 + 0x10000);
  FUN_0000b488(lVar3,8);
  j_XeCryptHmacSha(0x20,0x10,lVar3,0x3ff0,&local_50,2,0,0);
  j_XeCryptHmacSha(0x20,0x10,lVar2,0x10,0,0,0,0);
  j_XeCryptRc4(&local_40,0x10,lVar3,0x3ff0);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



ulonglong FUN_00003760(void)

{
  uint uVar1;
  int in_r2;
  longlong lVar2;
  undefined4 uVar3;
  undefined8 uVar4;
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
  uVar3 = j_XeCryptMemDiff(lVar2,&local_40,0x10);
  uVar4 = countLeadingZeros(uVar3);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return (ulonglong)((uint)uVar4 >> 5 & 1);
}



void FUN_00003830(undefined8 param_1,uint param_2)

{
  longlong in_r2;
  int iVar1;
  uint uVar2;
  longlong lVar3;
  
  uVar2 = __Save_R12_29_thru_31();
  iVar1 = (int)in_r2;
  HvpAquireSpinLock(in_r2 + 0x164dc);
  PTR_LAB_00000030 = (undefined *)((uVar2 | (uint)(undefined *)0x8000) & ~param_2);
                    // WARNING: Read-only address (ram,0x00000030) is written
  lVar3 = *(longlong *)((int)DWORD_ARRAY_0001613c + iVar1 + 0x14);
  if (lVar3 != 0) {
    *(undefined **)((int)lVar3 + 0x610) = (undefined *)0x8000;
  }
  FUN_000001e0(in_r2 + 0x164dc);
  return;
}



undefined8 FUN_00003890(ulonglong param_1,ulonglong param_2)

{
  if (((param_1 == (param_1 + 0xf & 0xfffffffffffffff0)) && (param_1 - 0x80 < 0x7ffff80)) &&
     ((param_2 & 0xffffffff) < 0x8000000 - param_1)) {
    return 1;
  }
  return 0;
}



undefined8 FUN_000038d8(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  uint uVar2;
  int in_r2;
  undefined8 uVar3;
  int iVar4;
  ulonglong uVar5;
  word local_230;
  dword local_30;
  
  uVar3 = __Save_R12_28_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  uVar2 = *(uint *)param_3 << 3;
  if (uVar2 < 0x201) {
    uVar5 = (ulonglong)(*(uint *)param_3 & 0x1fffffff);
    j_XeCryptBnQw_SwapDwQwLeBe(param_2,&local_230,uVar5);
    iVar4 = j_XeCryptBnQwNeRsaPubCrypt(&local_230,&local_230,param_3);
    if (iVar4 != 0) {
      j_XeCryptBnQw_SwapDwQwLeBe(&local_230,&local_230,uVar5);
      uVar3 = j_XeCryptBnDwLePkcs1Verify(uVar3,&local_230,(ulonglong)uVar2);
      HvpReleaseSpinLock((ulonglong)uVar1);
      return uVar3;
    }
  }
  HvpReleaseSpinLock((ulonglong)uVar1);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00003980(undefined8 param_1,undefined8 param_2,int param_3)

{
  longlong in_r2;
  undefined8 uVar1;
  word local_180;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (param_3 == 0x10) {
    uVar1 = HvpPhysicalToReal(param_2,0x10);
    j_XeCryptAesKey(&local_180,in_r2 + 0x16390);
    j_XeCryptAesEcb(&local_180,uVar1,param_1,0);
    uVar1 = 0;
  }
  else {
    uVar1 = 0xffffffffc8000004;
  }
  return uVar1;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00003a2c)
// WARNING: Removing unreachable block (ram,0x00003a3c)
// WARNING: Removing unreachable block (ram,0x00003a58)
// WARNING: Removing unreachable block (ram,0x00003a94)
// WARNING: Removing unreachable block (ram,0x00003aa8)
// WARNING: Removing unreachable block (ram,0x00003ac0)
// WARNING: Removing unreachable block (ram,0x00003adc)
// WARNING: Removing unreachable block (ram,0x00003a44)

undefined8 FUN_00003a00(void)

{
  int in_r2;
  word local_120;
  dword local_20;
  qword local_10;
  qword local_8;
  
  HvpReleaseSpinLock((ulonglong)*(uint *)(in_r2 + 0x10000));
  return 0xffffffffc8000000;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00003b10(undefined8 param_1,undefined8 param_2,int param_3)

{
  uint uVar1;
  longlong in_r2;
  longlong lVar2;
  undefined8 uVar3;
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
    j_XeCryptHmacShaUpdate(&local_d0,in_r2 + 0x16280,0x110);
    j_XeCryptHmacShaUpdate(&local_d0,in_r2 + 0x16390,0x10);
    j_XeCryptHmacShaUpdate(&local_d0,lVar2 + 0x11a30,10);
    j_XeCryptHmacShaUpdate(&local_d0,0x18,8);
    j_XeCryptHmacShaUpdate(&local_d0,ZEXT48(&PTR_DWORD_ARRAY_00010750) + lVar2,0x590);
    j_XeCryptHmacShaUpdate(&local_d0,0x54,0x10);
    j_XeCryptHmacShaUpdate(&local_d0,lVar2 + 0x10ea0,0x10);
    j_XeCryptHmacShaUpdate
              (&local_d0,*(longlong *)((int)DWORD_ARRAY_0001613c + (int)lVar2 + 0x104) + 0xf0,0x10);
    j_XeCryptHmacShaUpdate(&local_d0,lVar2 + 0x10e90,0x10);
    j_XeCryptHmacShaFinal(&local_d0,param_1,0x10);
    HvpReleaseSpinLock((ulonglong)uVar1);
    uVar3 = 0;
  }
  else {
    HvpReleaseSpinLock((ulonglong)uVar1);
    uVar3 = 0xffffffffc8000004;
  }
  return uVar3;
}



// WARNING: Removing unreachable block (ram,0x00003c90)

undefined8 FUN_00003c50(undefined8 param_1,ulonglong param_2)

{
  undefined uVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  longlong in_r2;
  int iVar5;
  ulonglong uVar6;
  longlong lVar7;
  word *pwVar8;
  undefined *puVar9;
  longlong lVar10;
  uint *puVar12;
  undefined8 uVar11;
  longlong lVar13;
  qword local_1c0;
  dword local_1b4;
  word local_1b0;
  word local_50;
  word local_40;
  dword local_2c;
  
  uVar6 = __Save_R12_29_thru_31();
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  if (((uVar6 & 0xfff) != 0) || ((param_2 & 0xffffffff) != 0x1000)) {
    HvpReleaseSpinLock((ulonglong)uVar2);
    return 0xffffffffc8000004;
  }
  lVar10 = in_r2 + 0x16918;
  HvpAquireSpinLock(lVar10);
  lVar7 = func_0x000033d8(uVar6,0x1000,0x3a);
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
    in_r2 = in_r2 + 0x111b0;
  }
  else {
    in_r2 = in_r2 + 0x10970;
  }
  uVar6 = FUN_000038d8(&local_40,lVar7._4_4_,in_r2);
  if ((uVar6 & 0xffffffff) == 0) {
    uVar11 = 0xffffffffc800000d;
    goto LAB_00003e30;
  }
  if (*(int *)(lVar7._4_4_ + 0x114) == 1) {
    if ((*(uint *)(lVar7._4_4_ + 0x11c) == 0) ||
       (bVar3 = false, *(uint *)(lVar7._4_4_ + 0x11c) < 0x4489)) {
      bVar3 = true;
    }
    if ((*(uint *)(lVar7._4_4_ + 0x120) == 0) ||
       (bVar4 = false, 0x4488 < *(uint *)(lVar7._4_4_ + 0x120))) {
      bVar4 = true;
    }
    if ((!bVar3) || (!bVar4)) {
      uVar11 = 0xffffffffc800000f;
      goto LAB_00003e30;
    }
    if (*(longlong *)(lVar7._4_4_ + 0x128) ==
        *(longlong *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar5 + 0x14) + 0x20)) {
      uVar11 = FUN_0000b138(lVar7._4_4_ + 0x130,(ulonglong)*(uint *)(lVar7._4_4_ + 0x124));
      goto LAB_00003e30;
    }
  }
  uVar11 = 0xffffffffc800000e;
LAB_00003e30:
  HvpZeroCacheLines(lVar7._4_4_,0x20);
  HvpRelocateProtectedToPhysical(lVar7._4_4_,0x1000,0x3a);
  FUN_000001e0(lVar10);
  HvpReleaseSpinLock((ulonglong)uVar2);
  return uVar11;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_00003e80(uint param_1)

{
  undefined uVar1;
  uint uVar2;
  longlong in_r2;
  longlong lVar3;
  longlong lVar4;
  word *pwVar5;
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
      FUN_0000b488(&local_40,0x10);
      j_XeCryptAesKey(&local_1a0,&local_40);
      j_XeCryptAesEcb(&local_1a0,&local_30,&local_1b0,0);
      lVar3 = j_XeCryptHammingWeight(local_1b0);
      lVar4 = j_XeCryptHammingWeight(local_1a8);
    } while ((lVar4 + lVar3 & 0xffffffffU) != 0x40);
  }
  else {
    local_1b0 = 0xffffffffffffffff;
    local_1a8 = 0xffffffffffffffff;
  }
  lVar3 = in_r2 + 0x16230;
  pwVar5 = &local_40;
  lVar4 = 0x10;
  do {
    uVar1 = *(undefined *)pwVar5;
    pwVar5 = (word *)((int)pwVar5 + 1);
    *(undefined *)lVar3 = uVar1;
    lVar3 = lVar3 + 1;
    lVar4 = lVar4 + -1;
  } while (lVar4 != 0);
  *(qword *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x210) = local_1b0;
  *(qword *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x218) = local_1a8;
  HvpReleaseSpinLock((ulonglong)uVar2);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x0000426c)
// WARNING: Removing unreachable block (ram,0x0000427c)
// WARNING: Removing unreachable block (ram,0x00004290)
// WARNING: Removing unreachable block (ram,0x000042a4)
// WARNING: Removing unreachable block (ram,0x000042b8)
// WARNING: Removing unreachable block (ram,0x00004284)

longlong FUN_00003f88(void)

{
  undefined2 uVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  longlong in_r2;
  longlong lVar5;
  int iVar6;
  byte bVar7;
  longlong lVar8;
  byte *pbVar9;
  ulonglong uVar10;
  longlong lVar11;
  undefined2 *puVar12;
  ushort *puVar13;
  longlong lVar14;
  qword local_190;
  dword local_184;
  word local_180;
  qword local_18;
  qword local_10;
  qword local_8;
  
  lVar5 = FUN_00000270();
  lVar8 = ZEXT48(&DWORD_00010b90) + in_r2;
  uVar10 = 0x10;
  bVar7 = 0;
  iVar6 = (int)in_r2;
  *(longlong *)((int)DWORD_ARRAY_0001613c + iVar6 + 0x104) = lVar5;
  *(longlong *)((int)DWORD_ARRAY_0001613c + iVar6 + 0xdc) = lVar5 + 0x4000;
  *(longlong *)((int)DWORD_ARRAY_00016260 + iVar6 + 0x248) = lVar5 + 0xf800;
  *(longlong *)((int)DWORD_ARRAY_00016260 + iVar6 + 0x250) = lVar5 + 0xfd80;
  do {
    pbVar9 = (byte *)lVar8;
    uVar10 = uVar10 - 1;
    lVar8 = lVar8 + 1;
    bVar7 = *pbVar9 | bVar7;
  } while ((uVar10 & 0xffffffff) != 0);
  lVar8 = in_r2;
  if (bVar7 != 0) {
    lVar5 = j_XeCryptHmacSha(0x18,8,ZEXT48(&DWORD_00010b90) + in_r2,0x10,0,0,uVar10,0);
  }
  iVar6 = 0x10;
  bVar7 = 0;
  lVar11 = in_r2 + 0x10cc0;
  do {
    pbVar9 = (byte *)lVar11;
    iVar6 = iVar6 + -1;
    lVar11 = lVar11 + 1;
    bVar7 = *pbVar9 | bVar7;
  } while (iVar6 != 0);
  if (bVar7 != 0) {
    lVar5 = j_XeCryptHmacSha(0x18,8,in_r2 + 0x10cc0,0x10,0,0,0,0);
  }
  iVar6 = 0x10;
  bVar7 = 0;
  lVar11 = in_r2 + 0x10cd0;
  do {
    pbVar9 = (byte *)lVar11;
    iVar6 = iVar6 + -1;
    lVar11 = lVar11 + 1;
    bVar7 = *pbVar9 | bVar7;
  } while (iVar6 != 0);
  if (bVar7 != 0) {
    lVar5 = j_XeCryptHmacSha(0x18,8,in_r2 + 0x10cd0,0x10,0,0,0,0);
  }
  puVar13 = (ushort *)(ZEXT48(DWORD_ARRAY_00016260) + lVar8);
  uVar2 = *puVar13 & 0xfff;
  if (((uVar2 != 0x342) && (uVar2 != 0x362)) && (uVar2 != 0x344)) {
    lVar11 = lVar8;
    memset(ZEXT48(DWORD_ARRAY_00016260) + lVar8,0,0x200);
    iVar6 = HvpBuildSocMMIORegs(0);
    uVar3 = *(uint *)(iVar6 + 0xfc);
    if ((0x5e98 < uVar3) || ((uVar3 & 7) != 0)) {
      _v_MACHINE_CHECK_0();
      return 0xffffffffc8000000;
    }
    lVar5 = lVar8 + 0x16266;
    iVar6 = uVar3 + iVar6;
    puVar12 = (undefined2 *)(iVar6 + 0x158);
    *puVar13 = 0x4e4e;
    iVar4 = (int)lVar8;
    *(undefined2 *)((int)DWORD_ARRAY_00016260 + iVar4 + 2) = 0x4488;
    lVar14 = 5;
    do {
      uVar1 = *puVar12;
      puVar12 = puVar12 + 1;
      *(undefined2 *)lVar5 = uVar1;
      lVar5 = lVar5 + 2;
      lVar14 = lVar14 + -1;
    } while (lVar14 != 0);
    *(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x10) = *(undefined8 *)(iVar6 + 0x148);
    *(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x18) = *(undefined8 *)(iVar6 + 0x150);
    lVar5 = memcpy(lVar8 + 0x16280,iVar6,0x110);
    uVar2 = *(ushort *)((int)DWORD_ARRAY_00016260 + (int)lVar11 + 0x6bc);
    *(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x28) = 0xfd336b67936aa211;
    if ((uVar2 & 2) == 0) {
      *(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x130) =
           *(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x10);
      *(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x138) =
           *(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x18);
    }
    else {
      j_XeCryptAesKey(&local_180,lVar8 + 0x16270);
      lVar5 = j_XeCryptAesEcb(&local_180,lVar11 + 0x11a20,lVar8 + 0x16390,0);
    }
  }
  return lVar5;
}



// WARNING: Removing unreachable block (ram,0x0000426c)
// WARNING: Removing unreachable block (ram,0x0000427c)
// WARNING: Removing unreachable block (ram,0x00004290)
// WARNING: Removing unreachable block (ram,0x000042a4)
// WARNING: Removing unreachable block (ram,0x000042b8)
// WARNING: Removing unreachable block (ram,0x00004284)

undefined8 HvxKeysGetFactoryChallenge(void)

{
  qword local_8;
  
  return 0xffffffffc8000000;
}



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
// WARNING: Removing unreachable block (ram,0x00004314)
// WARNING: Removing unreachable block (ram,0x00004324)
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

undefined8 HvxKeysSaveBootLoader(void)

{
  int in_r2;
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
  HvpReleaseSpinLock((ulonglong)*(uint *)(in_r2 + 0x10000));
                    // WARNING: Read-only address (ram,0x00000010) is written
                    // WARNING: Read-only address (ram,0x00000014) is written
  return 0xffffffffc8000010;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00004fc8)
// WARNING: Removing unreachable block (ram,0x00004fb8)
// WARNING: Removing unreachable block (ram,0x00004fd8)
// WARNING: Removing unreachable block (ram,0x00004fec)
// WARNING: Removing unreachable block (ram,0x00005030)
// WARNING: Removing unreachable block (ram,0x0000503c)
// WARNING: Removing unreachable block (ram,0x00004fe0)

undefined8 HvxKeysSaveKeyVault(void)

{
  qword local_18;
  qword local_10;
  qword local_8;
  
  return 0xffffffffc8000007;
}



ulonglong HvxKeysGetKeyProperties(ulonglong param_1)

{
  int iVar1;
  int in_r2;
  undefined *puVar2;
  
  if ((param_1 & 0xffffffff) < 0x39) {
    puVar2 = &DAT_00010d58 + in_r2;
    iVar1 = (int)(param_1 << 2);
  }
  else {
    if (0xd < (param_1 - 0x100 & 0xffffffff)) {
      return 0;
    }
    iVar1 = ((int)param_1 + -0x100) * 4;
    puVar2 = (undefined *)(in_r2 + 0x10e58);
  }
  return (ulonglong)*(uint *)(puVar2 + iVar1);
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00005110)
// WARNING: Removing unreachable block (ram,0x00005120)
// WARNING: Removing unreachable block (ram,0x0000513c)
// WARNING: Removing unreachable block (ram,0x00005128)

undefined8 HvxKeysGetDigest(void)

{
  int in_r2;
  word local_30;
  dword local_1c;
  qword local_18;
  qword local_10;
  qword local_8;
  
  HvpReleaseSpinLock((ulonglong)*(uint *)(in_r2 + 0x10000));
  return 0xffffffffc8000000;
}



// WARNING: Removing unreachable block (ram,0x000051f4)
// WARNING: Removing unreachable block (ram,0x000051e4)
// WARNING: Removing unreachable block (ram,0x00005204)
// WARNING: Removing unreachable block (ram,0x00005238)
// WARNING: Removing unreachable block (ram,0x0000532c)
// WARNING: Removing unreachable block (ram,0x00005244)
// WARNING: Removing unreachable block (ram,0x0000520c)
// WARNING: Removing unreachable block (ram,0x00005270)
// WARNING: Removing unreachable block (ram,0x000052a0)
// WARNING: Removing unreachable block (ram,0x000052a8)
// WARNING: Removing unreachable block (ram,0x00005284)
// WARNING: Removing unreachable block (ram,0x00005288)
// WARNING: Removing unreachable block (ram,0x000052b0)
// WARNING: Removing unreachable block (ram,0x000052bc)
// WARNING: Removing unreachable block (ram,0x000052c4)
// WARNING: Removing unreachable block (ram,0x00005320)
// WARNING: Removing unreachable block (ram,0x000052d8)
// WARNING: Removing unreachable block (ram,0x00005318)
// WARNING: Removing unreachable block (ram,0x0000530c)
// WARNING: Removing unreachable block (ram,0x00005294)

undefined8 HvxKeysRsaPrvCrypt(void)

{
  __Save_R12_26_thru_31();
  return 0xffffffffc8000000;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00005380)
// WARNING: Removing unreachable block (ram,0x00005370)
// WARNING: Removing unreachable block (ram,0x00005390)
// WARNING: Removing unreachable block (ram,0x00005408)
// WARNING: Removing unreachable block (ram,0x0000544c)
// WARNING: Removing unreachable block (ram,0x00005464)
// WARNING: Removing unreachable block (ram,0x0000546c)
// WARNING: Removing unreachable block (ram,0x00005478)
// WARNING: Removing unreachable block (ram,0x000054f0)
// WARNING: Removing unreachable block (ram,0x00005484)
// WARNING: Removing unreachable block (ram,0x00005454)
// WARNING: Removing unreachable block (ram,0x0000545c)
// WARNING: Removing unreachable block (ram,0x000054a0)
// WARNING: Removing unreachable block (ram,0x00005410)
// WARNING: Removing unreachable block (ram,0x000054a4)
// WARNING: Removing unreachable block (ram,0x000054c0)
// WARNING: Removing unreachable block (ram,0x000054b4)
// WARNING: Removing unreachable block (ram,0x000054c8)
// WARNING: Removing unreachable block (ram,0x000054d4)
// WARNING: Removing unreachable block (ram,0x00005398)
// WARNING: Removing unreachable block (ram,0x000053a0)
// WARNING: Removing unreachable block (ram,0x000053ac)
// WARNING: Removing unreachable block (ram,0x000053c8)
// WARNING: Removing unreachable block (ram,0x000053dc)
// WARNING: Removing unreachable block (ram,0x000054e8)

undefined8 FUN_00005348(void)

{
  word local_170;
  qword local_10;
  qword local_8;
  
  return 0xffffffffc8000000;
}



undefined8
HvxKeysHmacSha(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
              undefined8 param_5,undefined8 param_6,ulonglong param_7)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  undefined8 uVar3;
  qword local_60;
  dword local_54;
  word local_50;
  dword local_40;
  
  uVar2 = __Save_R12_27_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  uVar2 = FUN_00005348(uVar2,0x800000,param_2,param_3,&local_50);
  if ((int)uVar2 == 0) {
    if (0x14 < (param_7 & 0xffffffff)) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8000004;
    }
    uVar3 = HvpPhysicalToReal(param_4,param_5);
    HvpPhysicalToReal(param_6,param_7);
    j_XeCryptHmacSha(&local_50,0x10,uVar3,param_5,0,0,0,0);
  }
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar2;
}



undefined8
HvxKeysAesCbc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             ulonglong param_5,undefined8 param_6,undefined8 param_7,ulonglong param_8)

{
  uint uVar1;
  longlong in_r2;
  ulonglong uVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  longlong lVar5;
  longlong lVar6;
  undefined8 uVar7;
  uint uVar8;
  word local_1d0;
  word local_70;
  dword local_60;
  
  uVar2 = __Save_R12_23_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  uVar3 = FUN_00005348(uVar2 >> 0x20,0x400000,param_2,param_3,&local_70);
  if ((int)uVar3 == 0) {
    if (((int)(uVar2 >> 0x20) == 0x1b) && (uVar4 = FUN_0000b0f8(8), (uVar4 & 0xffffffff) == 0)) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8000002;
    }
    if ((param_5 & 0xf) != 0) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8000004;
    }
    HvpAquireSpinLock(in_r2 + 0x167a0);
    lVar5 = FUN_00002a20(param_4,param_5);
    lVar6 = FUN_00002a20(param_6,param_5);
    FUN_00000384(0,lVar5,lVar6);
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
    FUN_00000384(1,lVar5,lVar6);
    FUN_000001e0(in_r2 + 0x167a0);
  }
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar3;
}



undefined8
HvxKeysDes2Cbc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
              ulonglong param_5,undefined8 param_6,undefined8 param_7,ulonglong param_8)

{
  uint uVar1;
  int in_r2;
  ulonglong uVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  longlong lVar5;
  longlong lVar6;
  undefined8 uVar7;
  uint uVar8;
  word local_1f0;
  qword local_70;
  qword local_60;
  dword local_58;
  
  uVar2 = __Save_R12_24_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  uVar3 = FUN_00005348(uVar2 >> 0x20,0x400000,param_2,param_3,&local_70);
  if ((int)uVar3 == 0) {
    if (((int)(uVar2 >> 0x20) == 0x1b) && (uVar4 = FUN_0000b0f8(8), (uVar4 & 0xffffffff) == 0)) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8000002;
    }
    if ((param_5 & 7) != 0) {
LAB_0000580c:
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8000004;
    }
    lVar5 = HvpPhysicalToReal(param_4,param_5);
    lVar6 = HvpPhysicalToReal(param_6,param_5);
    FUN_0000b420(&local_70,0x18,&local_70);
    j_XeCryptDesCbc(&local_1f0,&local_70);
    if ((param_8 & 0xffffffff) == 0) {
      uVar8 = (uint)param_5 >> 3;
      while (uVar8 != 0) {
        j_XeCryptDes3Key(&local_1f0,lVar5,lVar6,uVar2 & 0xffffffff);
        uVar8 = uVar8 - 1;
        lVar5 = lVar5 + 8;
        lVar6 = lVar6 + 8;
      }
    }
    else {
      if ((param_8 & 0xffffffff) != 8) goto LAB_0000580c;
      uVar7 = HvpPhysicalToReal(param_7,8);
      j_XeCryptDes3Ecb(&local_1f0,lVar5,param_5,lVar6,uVar7,uVar2 & 0xffffffff);
    }
  }
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar3;
}



undefined8
HvxKeysDesCbc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             ulonglong param_5,undefined8 param_6,undefined8 param_7,ulonglong param_8)

{
  uint uVar1;
  int in_r2;
  ulonglong uVar2;
  undefined8 uVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 uVar6;
  uint uVar7;
  word local_e0;
  word local_60;
  dword local_50;
  
  uVar2 = __Save_R12_25_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  uVar3 = FUN_00005348(uVar2 >> 0x20,0x4000000,param_2,param_3,&local_60);
  if ((int)uVar3 == 0) {
    if ((param_5 & 7) != 0) {
LAB_00005950:
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8000004;
    }
    lVar4 = HvpPhysicalToReal(param_4,param_5);
    lVar5 = HvpPhysicalToReal(param_6,param_5);
    FUN_0000b420(&local_60,8,&local_60);
    j_XeCryptDesParity(&local_e0,&local_60);
    if ((param_8 & 0xffffffff) == 0) {
      uVar7 = (uint)param_5 >> 3;
      while (uVar7 != 0) {
        j_XeCryptDesKey(&local_e0,lVar4,lVar5,uVar2 & 0xffffffff);
        uVar7 = uVar7 - 1;
        lVar4 = lVar4 + 8;
        lVar5 = lVar5 + 8;
      }
    }
    else {
      if ((param_8 & 0xffffffff) != 8) goto LAB_00005950;
      uVar6 = HvpPhysicalToReal(param_7,8);
      j_HvxKeysDesEcb(&local_e0,lVar4,param_5,lVar5,uVar6,uVar2 & 0xffffffff);
    }
  }
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar3;
}



// WARNING: Removing unreachable block (ram,0x00005a60)
// WARNING: Removing unreachable block (ram,0x00005a50)
// WARNING: Removing unreachable block (ram,0x00005a70)
// WARNING: Removing unreachable block (ram,0x00005a78)
// WARNING: Removing unreachable block (ram,0x00005b10)
// WARNING: Removing unreachable block (ram,0x00005a80)
// WARNING: Removing unreachable block (ram,0x00005aa4)
// WARNING: Removing unreachable block (ram,0x00005ab8)
// WARNING: Removing unreachable block (ram,0x00005aec)
// WARNING: Removing unreachable block (ram,0x00005b00)

undefined8 HvxKeysObscureKey(void)

{
  int in_r2;
  word local_1a0;
  word local_40;
  dword local_30;
  
  __Save_R12_29_thru_31();
  HvpReleaseSpinLock((ulonglong)*(uint *)(in_r2 + 0x10000));
  return 0xffffffffc8000000;
}



undefined8 HvxKeysGetStatus(void)

{
  return 0x8000;
}



// WARNING: Removing unreachable block (ram,0x00005b7c)
// WARNING: Removing unreachable block (ram,0x00005b8c)
// WARNING: Removing unreachable block (ram,0x00005b6c)
// WARNING: Removing unreachable block (ram,0x00005e38)
// WARNING: Removing unreachable block (ram,0x00005d54)
// WARNING: Removing unreachable block (ram,0x00005d18)
// WARNING: Removing unreachable block (ram,0x00005b9c)
// WARNING: Removing unreachable block (ram,0x00005bbc)
// WARNING: Removing unreachable block (ram,0x00005bc8)
// WARNING: Removing unreachable block (ram,0x00005f38)
// WARNING: Removing unreachable block (ram,0x00005bd4)
// WARNING: Removing unreachable block (ram,0x00005bf0)
// WARNING: Removing unreachable block (ram,0x00005c04)
// WARNING: Removing unreachable block (ram,0x00005c44)
// WARNING: Removing unreachable block (ram,0x00005c58)
// WARNING: Removing unreachable block (ram,0x00005c60)
// WARNING: Removing unreachable block (ram,0x00005efc)
// WARNING: Removing unreachable block (ram,0x00005c68)
// WARNING: Removing unreachable block (ram,0x00005c7c)
// WARNING: Removing unreachable block (ram,0x00005c88)
// WARNING: Removing unreachable block (ram,0x00005c98)
// WARNING: Removing unreachable block (ram,0x00005ca4)
// WARNING: Removing unreachable block (ram,0x00005cc0)
// WARNING: Removing unreachable block (ram,0x00005cd0)
// WARNING: Removing unreachable block (ram,0x00005cdc)
// WARNING: Removing unreachable block (ram,0x00005cf0)
// WARNING: Removing unreachable block (ram,0x00005d00)
// WARNING: Removing unreachable block (ram,0x00005d20)
// WARNING: Removing unreachable block (ram,0x00005d08)
// WARNING: Removing unreachable block (ram,0x00005d2c)
// WARNING: Removing unreachable block (ram,0x00005d60)
// WARNING: Removing unreachable block (ram,0x00005dc8)
// WARNING: Removing unreachable block (ram,0x00005df8)
// WARNING: Removing unreachable block (ram,0x00005e00)
// WARNING: Removing unreachable block (ram,0x00005e24)
// WARNING: Removing unreachable block (ram,0x00005e44)
// WARNING: Removing unreachable block (ram,0x00005e58)
// WARNING: Removing unreachable block (ram,0x00005e60)
// WARNING: Removing unreachable block (ram,0x00005e6c)
// WARNING: Removing unreachable block (ram,0x00005c38)
// WARNING: Removing unreachable block (ram,0x00005f04)
// WARNING: Removing unreachable block (ram,0x00005f10)
// WARNING: Removing unreachable block (ram,0x00005bac)

undefined8 HvxKeysSaveSystemUpdate(void)

{
  int in_r2;
  qword local_3a0;
  dword local_394;
  word local_390;
  word local_280;
  word local_270;
  word local_260;
  dword local_60;
  
  __Save_R12_23_thru_31();
  HvpReleaseSpinLock((ulonglong)*(uint *)(in_r2 + 0x10000));
  return 0xffffffffc8000020;
}



undefined8
HvxKeysExecute(undefined8 param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4,
              undefined8 param_5,undefined8 param_6)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  longlong in_r2;
  ulonglong uVar4;
  ushort *puVar5;
  int iVar6;
  undefined8 *puVar7;
  longlong lVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  ushort *puVar11;
  longlong lVar12;
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
      (0xfee0 < (param_2 - 0x120 & 0xffffffff))) ||
     (((((uint)uVar4 + (uint)param_2) - 1 ^ (uint)uVar4) & 0xffff0000) != 0)) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8000030;
  }
  lVar8 = in_r2 + 0x16460;
  HvpAquireSpinLock(lVar8);
  puVar5 = (ushort *)func_0x000033d8(uVar4,param_2,0x3e);
  if ((*puVar5 & 0xf0f) == 0xd0d) {
    if (((*puVar5 ^ 0x4e4e) & 0xf000) == 0) {
      uVar2 = *(uint *)(puVar5 + 6);
      uVar9 = (ulonglong)(uVar2 + 0xf & 0xfffffff0);
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
          j_XeCryptHmacSha(in_r2 + 0x16390,0x10,puVar5 + 8,0x10,0,0,0,0);
          j_XeCryptRc4Key(&local_2d0,&local_1c0,0x10);
          puVar11 = puVar5 + 0x10;
          j_XeCryptRc4Ecb(&local_2d0,puVar11,uVar9 - 0x20);
          j_XeCryptRotSumSha(puVar5,0x10,puVar5 + 0x90,uVar9 - 0x120,&local_1b0,0x14);
          iVar6 = FUN_0000b3c0(puVar11,&local_1b0,lVar12 + 0x11a3c,in_r2 + 0x16280);
          if (iVar6 != 0) {
            *(undefined8 *)(puVar5 + 8) = 0;
            *(undefined8 *)(puVar5 + 0xc) = 0;
            memset(puVar11,0,0x100);
            if ((ulonglong)uVar2 < (param_2 & 0xffffffff)) {
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
  HvpZeroCacheLines(lVar12,(ulonglong)((uint)param_2 >> 7));
  memcpy(lVar12 + 0x20,&local_190,0x100);
  FUN_000001e0(lVar8);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar10;
}



// WARNING: Removing unreachable block (ram,0x0000625c)
// WARNING: Removing unreachable block (ram,0x0000626c)
// WARNING: Removing unreachable block (ram,0x0000627c)

undefined8 HvxKeysExCreateKeyVault(void)

{
  qword local_8;
  
  return 0xffffffffc8000007;
}



// WARNING: Removing unreachable block (ram,0x000062e0)
// WARNING: Removing unreachable block (ram,0x000062f0)
// WARNING: Removing unreachable block (ram,0x00006300)
// WARNING: Removing unreachable block (ram,0x00006318)
// WARNING: Removing unreachable block (ram,0x0000632c)
// WARNING: Removing unreachable block (ram,0x000063a8)
// WARNING: Removing unreachable block (ram,0x00006368)
// WARNING: Removing unreachable block (ram,0x00006380)
// WARNING: Removing unreachable block (ram,0x00006320)
// WARNING: Removing unreachable block (ram,0x0000630c)

undefined8 HvxKeysExLoadKeyVault(void)

{
  __Save_R12_29_thru_31();
  return 0xffffffffc8000002;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x000063f4)
// WARNING: Removing unreachable block (ram,0x000063e4)
// WARNING: Removing unreachable block (ram,0x00006404)
// WARNING: Removing unreachable block (ram,0x0000641c)
// WARNING: Removing unreachable block (ram,0x00006430)
// WARNING: Removing unreachable block (ram,0x00006424)
// WARNING: Removing unreachable block (ram,0x00006410)

undefined8 HvxKeysExSaveKeyVault(void)

{
  qword local_10;
  qword local_8;
  
  return 0xffffffffc8000007;
}



// WARNING: Removing unreachable block (ram,0x000064d0)
// WARNING: Removing unreachable block (ram,0x000064c0)
// WARNING: Removing unreachable block (ram,0x000064e0)
// WARNING: Removing unreachable block (ram,0x000065cc)
// WARNING: Removing unreachable block (ram,0x000064ec)
// WARNING: Removing unreachable block (ram,0x000064f8)
// WARNING: Removing unreachable block (ram,0x00006508)
// WARNING: Removing unreachable block (ram,0x00006514)
// WARNING: Removing unreachable block (ram,0x0000658c)
// WARNING: Removing unreachable block (ram,0x00006594)
// WARNING: Removing unreachable block (ram,0x000065a0)
// WARNING: Removing unreachable block (ram,0x0000656c)
// WARNING: Removing unreachable block (ram,0x00006580)
// WARNING: Removing unreachable block (ram,0x000065bc)
// WARNING: Removing unreachable block (ram,0x00006574)

undefined8 HvxKeysExSetKey(void)

{
  __Save_R12_28_thru_31();
  return 0xffffffffc8000000;
}



// WARNING: Removing unreachable block (ram,0x0000661c)
// WARNING: Removing unreachable block (ram,0x0000660c)
// WARNING: Removing unreachable block (ram,0x0000662c)
// WARNING: Removing unreachable block (ram,0x00006720)
// WARNING: Removing unreachable block (ram,0x00006638)
// WARNING: Removing unreachable block (ram,0x00006640)
// WARNING: Removing unreachable block (ram,0x00006714)
// WARNING: Removing unreachable block (ram,0x00006648)
// WARNING: Removing unreachable block (ram,0x000066c4)
// WARNING: Removing unreachable block (ram,0x000066e8)
// WARNING: Removing unreachable block (ram,0x000066fc)
// WARNING: Removing unreachable block (ram,0x00006700)
// WARNING: Removing unreachable block (ram,0x00006708)
// WARNING: Removing unreachable block (ram,0x000066cc)
// WARNING: Removing unreachable block (ram,0x000066b0)
// WARNING: Removing unreachable block (ram,0x000066b8)
// WARNING: Removing unreachable block (ram,0x000066d0)

undefined8 HvxKeysExGetKey(void)

{
  __Save_R12_27_thru_31();
  return 0xffffffffc8000000;
}



// WARNING: Removing unreachable block (ram,0x00006750)

undefined8 HvxGetUpdateSequence(void)

{
  return 0;
}



ulonglong FUN_00006760(void)

{
  uint uVar1;
  int in_r2;
  longlong lVar2;
  undefined4 uVar3;
  undefined8 uVar4;
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
  uVar3 = j_XeCryptMemDiff(lVar2,&local_40,0x10);
  uVar4 = countLeadingZeros(uVar3);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return (ulonglong)((uint)uVar4 >> 5 & 1);
}



void FUN_00006828(void)

{
  uint uVar1;
  int in_r2;
  longlong lVar2;
  longlong lVar3;
  qword local_50;
  dword local_44;
  word local_40;
  dword local_30;
  
  lVar2 = __Save_R12_29_thru_31();
  lVar3 = lVar2 + 0x10;
  uVar1 = *(uint *)(in_r2 + 0x10000);
  FUN_0000b488(lVar3,8);
  j_XeCryptHmacSha(0x20,0x10,lVar3,0x3f0,0,0,0,0);
  j_XeCryptHmacSha(0x20,0x10,lVar2,0x10,0,0,0,0);
  j_XeCryptRc4(&local_40,0x10,lVar3,0x3f0);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00006914)

undefined8 HvxSecurityInitialize(void)

{
  qword local_10;
  qword local_8;
  
  return 0xffffffffc8000040;
}



undefined8 HvxSecuritySaveSettings(undefined8 param_1,ulonglong param_2,undefined8 param_3)

{
  int in_r2;
  int iVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  
  uVar2 = __Save_R12_29_thru_31();
  if (*(char *)((int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248) + 0x18) == '\0') {
    uVar3 = 0xffffffffc8000040;
  }
  else {
    if ((param_2 & 0xffffffff) == 0x400) {
      if ((uVar2 & 0xfff) == 0) {
        iVar1 = in_r2;
        HvpSetRMCI(0);
        uVar3 = func_0x00003280(uVar2,0x400);
        *(undefined *)((int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248) + 0x19) =
             *(undefined *)((int)DWORD_ARRAY_00016260 + iVar1 + 0x240);
        uVar2 = func_0x00002b78();
        if ((uVar2 & 0xffffffff) != 0) {
          iVar1 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248);
          *(char *)(iVar1 + 0x19) = *(char *)(iVar1 + 0x19) + '\x01';
        }
        *(undefined8 *)((int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248) + 0x20) =
             param_3;
        memcpy(uVar3,*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248),0x400);
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



// WARNING: Removing unreachable block (ram,0x00006a78)

undefined8 HvxSecurityLoadSettings(undefined8 param_1,ulonglong param_2,longlong param_3)

{
  byte bVar1;
  int iVar2;
  int in_r2;
  int iVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  
  uVar4 = __Save_R12_28_thru_31();
  FUN_00003830(0x20000,0);
  if ((param_2 & 0xffffffff) != 0x400) {
    return 0xffffffffc8000041;
  }
  if ((uVar4 & 0xfff) != 0) {
    return 0xffffffffc8000042;
  }
  HvpSetRMCI(0);
  uVar5 = func_0x00003280(uVar4,0x400);
  iVar3 = in_r2;
  memcpy(*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248),uVar5,0x400);
  uVar6 = *(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248);
  uVar4 = FUN_00006760();
  iVar2 = (int)uVar6;
  if ((uVar4 & 0xffffffff) != 0) {
    bVar1 = *(byte *)((int)DWORD_ARRAY_00016260 + iVar3 + 0x240);
    if (*(byte *)(iVar2 + 0x19) == bVar1) {
      FUN_00003830(0x200000,0);
    }
    else {
      if ((uint)*(byte *)(iVar2 + 0x19) != (uint)bVar1 + 1) goto LAB_00006b68;
    }
    if (*(longlong *)(iVar2 + 0x20) == param_3) {
      uVar6 = 0;
      uVar4 = *(ulonglong *)(iVar2 + 0x28) & 0xfffffffffffffb9c;
      *(ulonglong *)(iVar2 + 0x30) = *(ulonglong *)(iVar2 + 0x30) & 0xfffffffffffffb9c;
      goto LAB_00006b88;
    }
  }
LAB_00006b68:
  uVar6 = 0xffffffffc8000043;
  memset(*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248),0,0x400);
  uVar4 = 0xffffffffffffffff;
  *(undefined8 *)(iVar2 + 0x30) = 0xffffffffffffffff;
LAB_00006b88:
  *(ulonglong *)(iVar2 + 0x28) = uVar4;
  FUN_0000b130();
  HvpRelocateEncryptedToPhysical(uVar5,0x400);
  HvpSetRMCI(1);
  return uVar6;
}



undefined8 HvxSecuritySetDetected(ulonglong param_1)

{
  int iVar1;
  int in_r2;
  undefined8 uVar2;
  qword local_8;
  
  iVar1 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248);
  if (*(char *)(iVar1 + 0x18) == '\0') {
    uVar2 = 0xffffffffc8000040;
  }
  else {
    if ((param_1 & 0xffffffff) < 0x40) {
      if ((*(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6b4) & 1) == 0) {
        *(ulonglong *)(iVar1 + 0x28) = 1 << (param_1 & 0x7f) | *(ulonglong *)(iVar1 + 0x28);
        FUN_0000b130();
      }
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffffffffc8000044;
    }
  }
  return uVar2;
}



undefined8 HvxSecurityGetDetected(void)

{
  int iVar1;
  int in_r2;
  
  if ((*(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6b4) & 1) != 0) {
    return 0;
  }
  iVar1 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248);
  if (*(char *)(iVar1 + 0x18) != '\0') {
    return *(undefined8 *)(iVar1 + 0x28);
  }
  return 0xffffffffffffffff;
}



undefined8 HvxSecuritySetActivated(undefined8 param_1)

{
  int iVar1;
  int in_r2;
  undefined8 uVar2;
  qword local_8;
  
  iVar1 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248);
  if (*(char *)(iVar1 + 0x18) == '\0') {
    uVar2 = 0xffffffffc8000040;
  }
  else {
    if ((*(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6b4) & 1) == 0) {
      *(undefined8 *)(iVar1 + 0x30) = param_1;
      FUN_0000b130();
    }
    uVar2 = 0;
  }
  return uVar2;
}



undefined8 HvxSecurityGetActivated(void)

{
  int iVar1;
  int in_r2;
  
  if ((*(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6b4) & 1) != 0) {
    return 0;
  }
  iVar1 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248);
  if (*(char *)(iVar1 + 0x18) != '\0') {
    return *(undefined8 *)(iVar1 + 0x30);
  }
  return 0xffffffffffffffff;
}



undefined8 HvxSecuritySetStat(uint param_1)

{
  int iVar1;
  int iVar2;
  int in_r2;
  undefined8 uVar3;
  qword local_8;
  
  iVar1 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248);
  if (*(char *)(iVar1 + 0x18) == '\0') {
    uVar3 = 0xffffffffc8000040;
  }
  else {
    if (param_1 < 5) {
      iVar2 = (param_1 + 0xe) * 4;
      *(int *)(iVar2 + iVar1) = *(int *)(iVar2 + iVar1) + 1;
      FUN_0000b130();
      uVar3 = 0;
    }
    else {
      uVar3 = 0xffffffffc8000045;
    }
  }
  return uVar3;
}



undefined8 HvxGetProtectedFlags(void)

{
  int in_r2;
  
  return *(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x238);
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 HvxSetProtectedFlag(ulonglong param_1,int param_2)

{
  int in_r2;
  int iVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if ((param_1 & 0xffffffff) < 3) {
    uVar2 = 1 << (param_1 & 0x7f);
    uVar3 = *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x238);
    if (param_2 == 0) {
      uVar2 = uVar3 & ~uVar2;
    }
    else {
      uVar2 = uVar2 | uVar3;
    }
    *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x238) = uVar2;
  }
  iVar1 = in_r2;
  HvpAquireSpinLock(in_r2 + 0x16144);
  *(undefined8 *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar1 + 0x14) + 0x678) =
       *(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x238);
  FUN_000001e0(in_r2 + 0x16144);
  return 0;
}



// WARNING: Removing unreachable block (ram,0x00007328)
// WARNING: Removing unreachable block (ram,0x00007334)
// WARNING: Removing unreachable block (ram,0x00007344)
// WARNING: Removing unreachable block (ram,0x00007354)
// WARNING: Removing unreachable block (ram,0x00007364)
// WARNING: Removing unreachable block (ram,0x00007370)
// WARNING: Removing unreachable block (ram,0x000072a8)
// WARNING: Removing unreachable block (ram,0x000072b4)
// WARNING: Removing unreachable block (ram,0x00007340)
// WARNING: Removing unreachable block (ram,0x00007384)
// WARNING: Removing unreachable block (ram,0x00007394)
// WARNING: Removing unreachable block (ram,0x000073a0)
// WARNING: Heritage AFTER dead removal. Example location: s0xfffffc50 : 0x00006f64
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_00006e68(void)

{
  undefined uVar1;
  int iVar2;
  longlong in_r2;
  uint uVar3;
  ushort *puVar4;
  int iVar5;
  uint uVar6;
  dword *pdVar7;
  undefined8 uVar8;
  longlong lVar9;
  undefined *puVar10;
  word *pwVar11;
  ulonglong uVar12;
  ushort *puVar13;
  longlong unaff_r19;
  ulonglong unaff_r21;
  word *pwVar14;
  ulonglong uVar15;
  longlong lVar16;
  longlong lVar17;
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
  uVar3 = *(uint *)((int)in_r2 + 0x10000);
  lVar17 = in_r2;
  memcpy(&local_390,in_r2 + 0x16280,0x110);
  pwVar14 = &local_a0;
  lVar9 = in_r2 + 0x16270;
  lVar16 = 0x10;
  do {
    puVar10 = (undefined *)lVar9;
    lVar9 = lVar9 + 1;
    *(undefined *)pwVar14 = *puVar10;
    pwVar14 = (word *)((int)pwVar14 + 1);
    lVar16 = lVar16 + -1;
  } while (lVar16 != 0);
  pwVar14 = &local_e0;
  in_r2 = in_r2 + 0x16266;
  lVar9 = 10;
  do {
    puVar10 = (undefined *)in_r2;
    in_r2 = in_r2 + 1;
    *(undefined *)pwVar14 = *puVar10;
    pwVar14 = (word *)((int)pwVar14 + 1);
    lVar9 = lVar9 + -1;
  } while (lVar9 != 0);
  pwVar14 = (word *)0x0;
  lVar9 = HvpGetFlashBaseAddress();
  FUN_00000484(&local_170,lVar9,0x10);
  uVar12 = (ulonglong)local_168;
  if (((uVar12 != (uVar12 + 0xf & 0xfffffffffffffff0)) ||
      (unaff_r21 = 0x7ffff7f, 0x7ffff7f < uVar12 - 0x80)) ||
     (unaff_r19 = 0x8000000, 0x8000000 - uVar12 < 0x11)) {
    _v_MACHINE_CHECK_0();
  }
  FUN_00000484(&local_3b0,uVar12 + lVar9,2);
  if ((local_3b0 & 0xf0f) != 0x302) {
    _v_MACHINE_CHECK_0();
  }
  uVar6 = local_3a4 + 0xf & 0xfffffff0;
  uVar15 = (ulonglong)uVar6;
  if (((uVar12 != (uVar12 + 0xf & 0xfffffffffffffff0)) || (unaff_r21 < uVar12 - 0x80)) ||
     ((unaff_r19 - uVar12 <= (ulonglong)uVar6 || (0x10000 < local_3a4)))) {
LAB_0000730c:
    _v_MACHINE_CHECK_0();
    uVar6 = 0;
    uVar3 = __Save_R12_29_thru_31(0x208);
    iVar2 = (int)lVar17;
    HvpAquireSpinLock(lVar17 + 0x164dc);
    PTR_LAB_00000030 = (undefined *)((uVar3 | (uint)(undefined *)0x8000) & ~uVar6);
                    // WARNING: Read-only address (ram,0x00000030) is written
    lVar9 = *(longlong *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x14);
    if (lVar9 != 0) {
      *(undefined **)((int)lVar9 + 0x610) = (undefined *)0x8000;
    }
    FUN_000001e0(lVar17 + 0x164dc);
    return;
  }
  FUN_00000484(puVar4,uVar12 + lVar9,(ulonglong)(uVar6 >> 3));
  iVar2 = (int)lVar17;
  if ((*puVar4 & 0xf0) == 0x40) {
    pdVar7 = (dword *)0x0;
    uVar8 = 0;
  }
  else {
    if ((*puVar4 & 0xf0) != 0x60) {
      _v_MACHINE_CHECK_0();
      goto LAB_0000730c;
    }
    uVar8 = 0x10;
    pdVar7 = DWORD_ARRAY_00000020;
    if ((puVar4[3] & 0x8000) == 0) {
      pdVar7 = (dword *)&local_b0;
    }
  }
  j_XeCryptHmacSha(&local_a0,0x10,puVar4 + 8,0x10,pdVar7,uVar8,0,0);
  j_XeCryptRc4Key(&local_280,&local_f0,0x10);
  j_XeCryptRc4Ecb(&local_280,puVar4 + 0x10,uVar15 - 0x20);
  j_XeCryptRotSumSha(puVar4,0x10,puVar4 + 0xa0,uVar15 - 0x140,&local_d0,0x14);
  iVar5 = FUN_0000b3c0(puVar4 + 0x20,&local_d0,&local_e0,&local_390);
  if (iVar5 == 0) {
    _v_MACHINE_CHECK_0();
  }
  if ((puVar4[3] & 0x800) != 0) {
    if ((puVar4[3] & 0x1000) == 0) {
      uVar8 = 0;
    }
    else {
      pwVar14 = &local_3a0;
      uVar8 = 0x10;
    }
    puVar13 = puVar4 + 0x1ce;
    pwVar11 = &local_90;
    lVar17 = 0x14;
    do {
      uVar1 = *(undefined *)puVar13;
      puVar13 = (ushort *)((int)puVar13 + 1);
      *(undefined *)pwVar11 = uVar1;
      pwVar11 = (word *)((int)pwVar11 + 1);
      lVar17 = lVar17 + -1;
    } while (lVar17 != 0);
    uVar12 = uVar15 + uVar12 & 0xffffffff;
    if (((uVar12 != (uVar12 + 0xf & 0xfffffffffffffff0)) || (unaff_r21 < uVar12 - 0x80)) ||
       (unaff_r19 - uVar12 < 0x11)) {
      _v_MACHINE_CHECK_0();
    }
    FUN_00000484(&local_3b0,uVar12 + lVar9,2);
    if ((local_3b0 & 0xf0f) != 0x302) {
      _v_MACHINE_CHECK_0();
    }
    uVar6 = local_3a4 + 0xf & 0xfffffff0;
    if ((((uVar12 == (uVar12 + 0xf & 0xfffffffffffffff0)) && (uVar12 - 0x80 <= unaff_r21)) &&
        ((ulonglong)uVar6 < unaff_r19 - uVar12)) && (local_3a4 < &BYTE_00010001)) {
      FUN_00000484(puVar4,uVar12 + lVar9,(ulonglong)(uVar6 >> 3));
      if ((local_3b0 & 0xf000) == 0x4000) {
        pdVar7 = DWORD_ARRAY_00000020;
      }
      else {
        pdVar7 = (dword *)&local_b0;
      }
      j_XeCryptHmacSha(&local_f0,0x10,puVar4 + 8,0x10,pdVar7,0x10,pwVar14,uVar8);
      j_XeCryptRc4Key(&local_280,&local_f0,0x10);
      j_XeCryptRc4Ecb(&local_280,puVar4 + 0x10,(ulonglong)uVar6 - 0x20);
      j_XeCryptRotSumSha(puVar4,0x10,puVar4 + 0xa0,(ulonglong)uVar6 - 0x140,&local_d0,0x14);
      iVar5 = j_XeCryptMemDiff(&local_90,&local_d0,0x14);
      if (iVar5 == 0) goto LAB_0000727c;
      _v_MACHINE_CHECK_0();
    }
    _v_MACHINE_CHECK_0();
  }
LAB_0000727c:
  if ((*(char *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x235) != '\0') || (0x74b < puVar4[1])) {
                    // WARNING: Read-only address (ram,0x00000030) is written
                    // WARNING: Read-only address (ram,0x00000074) is written
    uVar12 = (ulonglong)*(byte *)((int)puVar4 + 0x3b1);
    if (0x10 < *(byte *)((int)puVar4 + 0x3b1)) {
      _v_MACHINE_CHECK_0();
    }
    if (((uVar12 & 0xffffffff) != 0) &&
       (((ulonglong)(uint)(1 << uVar12 - 1) & (ulonglong)puVar4[0x1d9]) == 0)) {
      _v_MACHINE_CHECK_0();
    }
    DWORD_00000074 = *(dword *)(puVar4 + 0x1d8);
                    // WARNING: Read-only address (ram,0x00000074) is written
  }
  HvpReleaseSpinLock((ulonglong)uVar3);
                    // WARNING: Read-only address (ram,0x00000030) is written
                    // WARNING: Read-only address (ram,0x00000074) is written
  return;
}



// WARNING: Removing unreachable block (ram,0x00007370)
// WARNING: Removing unreachable block (ram,0x00007364)
// WARNING: Removing unreachable block (ram,0x00007328)
// WARNING: Removing unreachable block (ram,0x00007334)
// WARNING: Removing unreachable block (ram,0x00007344)
// WARNING: Removing unreachable block (ram,0x00007354)
// WARNING: Removing unreachable block (ram,0x00007384)
// WARNING: Removing unreachable block (ram,0x00007394)
// WARNING: Removing unreachable block (ram,0x000073a0)
// WARNING: Removing unreachable block (ram,0x00007340)

void FUN_00007310(void)

{
  int iVar1;
  longlong in_r2;
  uint uVar2;
  uint uVar3;
  longlong lVar4;
  
  uVar3 = 0;
  uVar2 = __Save_R12_29_thru_31(0x208);
  iVar1 = (int)in_r2;
  HvpAquireSpinLock(in_r2 + 0x164dc);
  PTR_LAB_00000030 = (undefined *)((uVar2 | (uint)(undefined *)0x8000) & ~uVar3);
                    // WARNING: Read-only address (ram,0x00000030) is written
  lVar4 = *(longlong *)((int)DWORD_ARRAY_0001613c + iVar1 + 0x14);
  if (lVar4 != 0) {
    *(undefined **)((int)lVar4 + 0x610) = (undefined *)0x8000;
  }
  FUN_000001e0(in_r2 + 0x164dc);
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

ulonglong FUN_000073c0(int param_1)

{
  int in_r2;
  undefined8 uVar1;
  undefined8 uVar2;
  byte bVar3;
  longlong lVar4;
  byte *pbVar5;
  uint uVar6;
  ulonglong uVar7;
  qword local_10;
  qword local_8;
  
  uVar7 = 0;
  if (param_1 != 0) {
    do {
      bVar3 = 0;
      if ((*(uint *)(&DAT_00010d58 + (int)((uVar7 & 0xffffffff) << 2) + in_r2) & 0x80000000) == 0) {
        uVar6 = *(uint *)(&DAT_00010d58 + (int)((uVar7 & 0xffffffff) << 2) + in_r2) & 0xffff;
        lVar4 = (ulonglong)
                *(ushort *)((int)DWORD_ARRAY_00010ce0 + (int)((uVar7 & 0xffffffff) << 1) + in_r2) +
                *(longlong *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x104) + 0x18;
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

undefined8 FUN_00007498(longlong param_1)

{
  uint uVar1;
  longlong in_r2;
  undefined8 uVar2;
  word local_30;
  dword local_1c;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  FUN_00003620(param_1,&local_30,0x14);
  uVar2 = FUN_000038d8(&local_30,param_1 + 0x1df8,in_r2 + 0x111b0);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar2;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00007500(undefined8 param_1,undefined8 param_2)

{
  longlong in_r2;
  undefined8 uVar1;
  int iVar2;
  qword local_18;
  qword local_10;
  qword local_8;
  
  FUN_00003830(0,0x100000);
  uVar1 = HvpBuildSocMMIORegs(0);
  j_XeCryptSha(uVar1,0x5c00,0,0,0,0,param_1,param_2);
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x6c0) < 0x710700) {
    in_r2 = in_r2 + 0x11a5c;
  }
  else {
    in_r2 = in_r2 + 0x11a48;
  }
  iVar2 = j_XeCryptMemDiff(param_1,in_r2,param_2);
  if (iVar2 == 0) {
    FUN_00003830(0x100000,0);
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x00007668)

undefined8 FUN_000075b8(longlong param_1,ulonglong param_2,int param_3)

{
  int in_r2;
  ulonglong uVar1;
  qword local_10;
  qword local_8;
  
  param_2 = param_2 & 0xffffffff;
  if (((param_2 == (param_2 + 0xf & 0xfffffffffffffff0)) && (param_2 - 0x80 < 0x7ffff80)) &&
     (0x4000 < 0x8000000 - param_2)) {
    FUN_00000484(param_3,param_2 + param_1,0x800);
    uVar1 = FUN_00003760(param_3);
    if ((uVar1 & 0xffffffff) != 0) {
      if ((*(char *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x235) == '\0') &&
         ((*(byte *)(param_3 + 0x1a) & 4) != 0)) {
                    // WARNING: Read-only address (ram,0x00000006) is written
        WORD_00000006 = 0x20;
      }
      return 1;
                    // WARNING: Read-only address (ram,0x00000006) is written
    }
  }
                    // WARNING: Read-only address (ram,0x00000006) is written
  return 0;
}



// WARNING: Removing unreachable block (ram,0x00007768)

undefined8 HvxKeysInitialize(void)

{
  uint uVar1;
  longlong in_r2;
  int iVar2;
  undefined8 uVar3;
  int iVar5;
  ulonglong uVar4;
  uint uVar6;
  byte bVar7;
  int iVar9;
  longlong lVar8;
  byte *pbVar10;
  short sVar11;
  longlong lVar12;
  qword local_40;
  dword local_34;
  qword local_30;
  
  uVar3 = __Save_R12_29_thru_31();
  lVar12 = in_r2 + 0x16918;
  HvpAquireSpinLock(lVar12);
  uVar3 = func_0x000033d8(uVar3,0x10000,0x3a);
  FUN_00006e68();
  HvpZeroCacheLines(uVar3,0x200);
  HvpRelocateProtectedToPhysical(uVar3,0x10000,0x3a);
  FUN_0000b488(in_r2 + 0x164c0,0x14);
  iVar5 = HvpGetFlashBaseAddress();
  iVar2 = (int)in_r2;
  uVar4 = FUN_000075b8(iVar5,(ulonglong)*(uint *)(iVar5 + 0x6c),
                       *(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x104));
  iVar5 = (int)in_r2;
  if ((uVar4 & 0xffffffff) == 0) {
LAB_00007780:
    memset(*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x104),0,0x4000);
  }
  else {
    if ((*(ushort *)((int)DWORD_ARRAY_00016260 + iVar5 + 0x6b4) & 1) != 0) {
      uVar4 = 0;
    }
    if ((uVar4 & 0xffffffff) == 0) goto LAB_00007780;
    FUN_00003830(0x10,0);
  }
  iVar9 = (int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x104);
  uVar1 = *(uint *)(iVar9 + 0x9e0);
  sVar11 = *(short *)(iVar9 + 200);
  uVar6 = uVar1 & 0xff000000;
  if (sVar11 == 0x7fff) {
LAB_00007830:
    sVar11 = 0;
  }
  else {
    if ((uVar1 & 0x10000000) == 0) {
LAB_000077f8:
      if (sVar11 == 0x102) {
LAB_00007804:
        sVar11 = 0;
      }
    }
    else {
      if (sVar11 != 0x102) goto LAB_00007804;
      if ((uVar1 & 0x10000000) == 0) goto LAB_000077f8;
    }
    if ((*(ushort *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x6bc) & 4) == 0) {
      uVar6 = 0;
    }
    else {
      if ((uVar1 & 0x8000000) == 0) goto LAB_00007830;
    }
  }
  if ((uVar6 & 0x8000000) != 0) {
    *(ushort *)((int)DWORD_ARRAY_00016260 + iVar5 + 0x6b4) =
         *(ushort *)((int)DWORD_ARRAY_00016260 + iVar5 + 0x6b4) | 4;
  }
  if (sVar11 == 0x7fff) {
    FUN_00003830(0x1000,0);
  }
  else {
    if (sVar11 != 0) goto LAB_00007890;
    FUN_00003830(0x400000,0);
    memset(*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x104),0,0x4000);
  }
  iVar9 = (int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x104);
LAB_00007890:
  iVar2 = (int)in_r2;
  iVar5 = 0x10;
  uVar3 = *(undefined8 *)(iVar9 + 0xf0);
  bVar7 = 0;
  lVar8 = ZEXT48(&DWORD_00010ba0) + in_r2;
  do {
    pbVar10 = (byte *)lVar8;
    iVar5 = iVar5 + -1;
    lVar8 = lVar8 + 1;
    bVar7 = *pbVar10 | bVar7;
  } while (iVar5 != 0);
  if (bVar7 == 0) {
    j_XeCryptHmacSha(&local_30,8,&local_30,8,0,0,0,0);
  }
  else {
    j_XeCryptHmacSha(0x18,8,ZEXT48(&DWORD_00010ba0) + in_r2,0x10,0,0,0,0);
  }
  FUN_000073c0(1);
  FUN_00003830(0x42,0);
  memset(*(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x248),0,0x400);
  FUN_0000b118();
  FUN_0000b128(uVar3);
  FUN_000001e0(lVar12);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x000079a4)
// WARNING: Removing unreachable block (ram,0x000079b4)
// WARNING: Removing unreachable block (ram,0x000079d0)
// WARNING: Removing unreachable block (ram,0x00007a0c)
// WARNING: Removing unreachable block (ram,0x00007a20)
// WARNING: Removing unreachable block (ram,0x00007a38)
// WARNING: Removing unreachable block (ram,0x00007a5c)
// WARNING: Removing unreachable block (ram,0x000079bc)

undefined8 HvxKeysSetFactoryResponse(void)

{
  int in_r2;
  word local_120;
  dword local_20;
  qword local_10;
  qword local_8;
  
  HvpReleaseSpinLock((ulonglong)*(uint *)(in_r2 + 0x10000));
  return 0xffffffffc8000000;
}



// WARNING: Removing unreachable block (ram,0x00007ac8)
// WARNING: Removing unreachable block (ram,0x00007b10)
// WARNING: Removing unreachable block (ram,0x00007b18)
// WARNING: Removing unreachable block (ram,0x00007cd4)
// WARNING: Removing unreachable block (ram,0x00007cdc)
// WARNING: Removing unreachable block (ram,0x00007ce8)
// WARNING: Removing unreachable block (ram,0x00007cf0)
// WARNING: Removing unreachable block (ram,0x00007d0c)
// WARNING: Removing unreachable block (ram,0x00007d14)
// WARNING: Removing unreachable block (ram,0x00007d20)
// WARNING: Removing unreachable block (ram,0x00007d2c)
// WARNING: Removing unreachable block (ram,0x00007d54)
// WARNING: Removing unreachable block (ram,0x00007d78)
// WARNING: Removing unreachable block (ram,0x00007d98)
// WARNING: Removing unreachable block (ram,0x00007d84)
// WARNING: Removing unreachable block (ram,0x00007d5c)
// WARNING: Removing unreachable block (ram,0x00007ad0)
// WARNING: Removing unreachable block (ram,0x00007b30)
// WARNING: Removing unreachable block (ram,0x00007b3c)
// WARNING: Removing unreachable block (ram,0x00007cc8)
// WARNING: Removing unreachable block (ram,0x00007ab8)
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
// WARNING: Removing unreachable block (ram,0x00007c24)
// WARNING: Removing unreachable block (ram,0x00007c30)
// WARNING: Removing unreachable block (ram,0x00007c40)
// WARNING: Removing unreachable block (ram,0x00007c60)
// WARNING: Removing unreachable block (ram,0x00007c6c)
// WARNING: Removing unreachable block (ram,0x00007cb8)
// WARNING: Removing unreachable block (ram,0x00007d70)

undefined8 HvxKeysSetKey(void)

{
  __Save_R12_26_thru_31();
  return 0xffffffffc8000000;
}



// WARNING: Removing unreachable block (ram,0x00007dcc)
// WARNING: Removing unreachable block (ram,0x00007ddc)
// WARNING: Removing unreachable block (ram,0x00007df0)
// WARNING: Removing unreachable block (ram,0x00007e24)
// WARNING: Removing unreachable block (ram,0x00007e30)
// WARNING: Removing unreachable block (ram,0x00007e58)
// WARNING: Removing unreachable block (ram,0x00007e3c)
// WARNING: Removing unreachable block (ram,0x00007e44)
// WARNING: Removing unreachable block (ram,0x00007e60)
// WARNING: Removing unreachable block (ram,0x00007e4c)
// WARNING: Removing unreachable block (ram,0x00007de4)

undefined8 HvxKeysGenerateRandomKey(void)

{
  qword local_8;
  
  return 0xffffffffc8000000;
}



// WARNING: Removing unreachable block (ram,0x00007ed4)

undefined8 HvxKeysGetKey(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  ulonglong uVar4;
  longlong in_r2;
  ulonglong uVar5;
  longlong lVar6;
  uint *puVar8;
  undefined8 uVar7;
  int iVar9;
  uint uVar10;
  ulonglong uVar11;
  ulonglong uVar12;
  longlong lVar13;
  ushort *puVar14;
  uint uVar15;
  word local_2a0;
  word local_280;
  word local_270;
  word local_250;
  dword local_50;
  
  uVar4 = ZEXT48(register0x0000000c);
  uVar5 = __Save_R12_24_thru_31();
  iVar9 = (int)in_r2;
  uVar1 = *(uint *)(iVar9 + 0x10000);
  if ((uVar5 & 0xffffffff) == 0x39) {
LAB_00007f58:
    lVar13 = ZEXT48(&PTR_DWORD_ARRAY_00010750) + in_r2;
    goto LAB_00007ff0;
  }
  if ((((uVar5 & 0xffffffff) != 0x48) && ((uVar5 & 0xffffffff) != 0x49)) &&
     ((uVar5 & 0xffffffff) != 0x42)) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8000000;
  }
  if ((uVar5 & 0xffffffff) < 0x39) {
    uVar15 = *(uint *)(&DAT_00010d58 + (int)((uVar5 & 0xffffffff) << 2) + iVar9);
    lVar13 = (ulonglong)
             *(ushort *)((int)DWORD_ARRAY_00010ce0 + (int)((uVar5 & 0xffffffff) << 1) + iVar9) +
             *(longlong *)((int)DWORD_ARRAY_0001613c + iVar9 + 0x104) + 0x18;
    goto LAB_00008130;
  }
  if ((uVar5 & 0xffffffff) == 0x39) goto LAB_00007f58;
  if ((uVar5 & 0xffffffff) == 0x3c) {
    lVar13 = in_r2 + 0x111b0;
LAB_00007ff0:
    uVar15 = 0x1010110;
  }
  else {
    if ((uVar5 & 0xffffffff) == 0x3d) {
      lVar13 = in_r2 + 0x10f90;
      goto LAB_00007ff0;
    }
    if ((uVar5 & 0xffffffff) == 0x3a) {
      uVar15 = 0x1010110;
      lVar13 = in_r2 + 0x10970;
    }
    else {
      if ((uVar5 & 0xffffffff) != 0x3b) {
        if ((uVar5 & 0xffffffff) == 0x3e) {
          lVar13 = in_r2 + 0x115f0;
        }
        else {
          if ((uVar5 & 0xffffffff) != 0x3f) {
            if ((uVar5 & 0xffffffff) == 0x40) {
              lVar13 = in_r2 + 0x10ec0;
              uVar15 = 0x10100d0;
            }
            else {
              if ((uVar5 & 0xffffffff) == 0x41) {
                uVar15 = 0x1010110;
                lVar13 = ZEXT48(&DWORD_00010bb0) + in_r2;
              }
              else {
                if ((uVar5 & 0xffffffff) == 0x42) {
                  FUN_0000b0d8(uVar4 - 0x280);
                  lVar13 = uVar4 - 0x280;
                  uVar15 = 0x1010010;
                }
                else {
                  if ((uVar5 & 0xffffffff) == 0x44) {
                    FUN_00003620(*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar9 + 0x104),
                                 uVar4 - 0x2a0,0x14);
                    uVar15 = 0x2010000;
                    lVar13 = uVar4 - 0x2a0;
                  }
                  else {
                    if ((uVar5 & 0xffffffff) != 0x45) {
                      if ((uVar5 & 0xffffffff) == 0x48) {
                        lVar13 = j_XeCryptHammingWeight
                                           (*(undefined8 *)
                                             ((int)DWORD_ARRAY_00016260 + iVar9 + 0x210));
                        lVar6 = j_XeCryptHammingWeight
                                          (*(undefined8 *)
                                            ((int)DWORD_ARRAY_00016260 + iVar9 + 0x218));
                        if (((lVar6 + lVar13 & 0xffffffffU) != 0x40) &&
                           ((lVar6 + lVar13 & 0xffffffffU) != 0x80)) {
                          HvpReleaseSpinLock((ulonglong)uVar1);
                          return 0xffffffffc800000e;
                        }
                        lVar13 = in_r2 + 0x16230;
                        uVar15 = 0x1140010;
                      }
                      else {
                        if ((uVar5 & 0xffffffff) != 0x49) {
                          if ((uVar5 & 0xffffffff) != 0x4d) {
                            HvpReleaseSpinLock((ulonglong)uVar1);
                            return 0xffffffffc8000001;
                          }
                          lVar13 = in_r2 + 0x164c0;
                          goto LAB_00008128;
                        }
                        lVar13 = in_r2 + 0x164d4;
                        uVar15 = 0x1010004;
                      }
                      goto LAB_00008130;
                    }
                    FUN_00007500(uVar4 - 0x2a0,0x14);
                    lVar13 = uVar4 - 0x2a0;
LAB_00008128:
                    uVar15 = 0x1010000;
                  }
                  uVar15 = uVar15 | 0x14;
                }
              }
            }
            goto LAB_00008130;
          }
          lVar13 = in_r2 + 0x112c0;
        }
        goto LAB_00007ff0;
      }
      uVar15 = 0x1010110;
      lVar13 = in_r2 + 0x10a80;
    }
  }
LAB_00008130:
  uVar3 = uVar15 & 0xffff;
  uVar12 = (ulonglong)uVar3;
  if ((uVar15 & 0x2000000) == 0) {
    uVar10 = uVar15 & 0x1000000;
  }
  else {
    uVar10 = 0;
  }
  if (uVar10 == 0) goto LAB_00008150;
  puVar8 = (uint *)HvpPhysicalToReal(param_3,4);
  uVar11 = (ulonglong)*puVar8;
  uVar7 = HvpPhysicalToReal(param_2,uVar11);
  if ((uVar15 & 0x40000) == 0) {
    if ((uVar15 & 0x10000) != 0) {
      if (uVar11 != uVar12) {
        HvpReleaseSpinLock((ulonglong)uVar1);
        return 0xffffffffc8000004;
      }
      goto LAB_00008318;
    }
    if (uVar3 < 2) {
      uVar12 = 0;
      goto LAB_00008318;
    }
    puVar14 = (ushort *)lVar13;
    uVar12 = uVar12 - 2;
    lVar13 = lVar13 + 2;
    if ((ulonglong)*puVar14 < (uVar12 & 0xffffffff)) {
      uVar12 = (ulonglong)*puVar14;
    }
  }
  else {
    if ((uVar5 & 0xffffffff) == 0x1c) {
      in_r2 = in_r2 + 0x114e0;
LAB_000081d4:
      bVar2 = false;
    }
    else {
      if ((uVar5 & 0xffffffff) != 0x48) {
        in_r2 = in_r2 + 0x110a0;
        goto LAB_000081d4;
      }
      in_r2 = in_r2 + 0x11700;
      bVar2 = true;
    }
    uVar10 = *(uint *)in_r2;
    uVar5 = (ulonglong)(uVar10 << 3);
    if (0x1c0 < (uVar5 - 0x40 & 0xffffffff)) {
LAB_00008150:
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8000002;
    }
    if (bVar2) {
      FUN_0000b488(uVar4 - 0x270,0x14);
      iVar9 = j_HvSetupMemEncryptionKey(lVar13,uVar12,uVar4 - 0x250,0x200,0,uVar4 - 0x270);
      if (iVar9 == 0) goto LAB_00008280;
      FUN_0000b480(uVar4 - 0x250,0x200);
      uVar12 = 0x40;
    }
    else {
      if ((((uVar15 & 0x100000) == 0) || ((uVar15 & 0x10000) == 0)) || (0x14 < uVar3))
      goto LAB_00008150;
      memcpy(uVar4 - 0x2a0,lVar13,uVar12);
      j_XeCryptBnDwLePkcs1Format(uVar4 - 0x2a0,0,uVar4 - 0x250,uVar5);
      uVar12 = (ulonglong)(uVar10 & 0x1fffffff);
    }
    j_XeCryptBnQw_SwapDwQwLeBe(uVar4 - 0x250,uVar4 - 0x250,uVar12);
    iVar9 = j_XeCryptBnQwNeRsaPubCrypt(uVar4 - 0x250,uVar4 - 0x250,in_r2);
    if (iVar9 == 0) {
LAB_00008280:
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8000006;
    }
    j_XeCryptBnQw_SwapDwQwLeBe(uVar4 - 0x250,uVar4 - 0x250,(ulonglong)(uVar10 & 0x1fffffff));
    lVar13 = uVar4 - 0x250;
    uVar12 = uVar5;
  }
  if (uVar11 < (uVar12 & 0xffffffff)) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8000003;
  }
LAB_00008318:
  memcpy(uVar7,lVar13,uVar12);
  *puVar8 = (uint)uVar12;
  HvpReleaseSpinLock((ulonglong)uVar1);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_00008388(qword *param_1)

{
  longlong lVar1;
  uint uVar2;
  int in_r2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  qword local_30;
  qword local_28;
  qword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  iVar3 = HvpBuildSocMMIORegs(0x20000);
  iVar4 = 0;
  uVar6 = 0x200;
  do {
    lVar5 = (longlong)iVar4;
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
  iVar3 = j_XeCryptHammingWeight(local_20 | local_30);
  iVar4 = j_XeCryptHammingWeight(local_18 | local_28);
  uVar2 = iVar4 + iVar3 & 0xff;
  *(undefined *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x234) = (char)uVar2;
  if (uVar2 < 0x40) {
    uVar7 = countLeadingZeros(uVar2);
    iVar3 = ((uint)uVar7 >> 5 & 1 ^ 1) + 1;
  }
  else {
    iVar3 = 0;
  }
  *(int *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x274) = iVar3;
  return;
}



void FUN_00008478(void)

{
  int in_r2;
  
  *(undefined *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd6) = 0x80;
  *(undefined *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd5) = 0xff;
  *(undefined *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd7) = 0xff;
  *(undefined *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd4) = 0xff;
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



void HvpSaveThread(void)

{
  byte bVar1;
  int iVar2;
  int in_r2;
  ulonglong uVar3;
  undefined uVar6;
  int iVar4;
  int iVar5;
  int iVar7;
  undefined8 in_DEC;
  undefined4 uVar8;
  undefined8 in_spr088;
  uint uVar9;
  longlong in_spr131;
  undefined8 in_spr136;
  undefined4 uVar10;
  
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
  iVar4 = HvpBuildSocMMIORegs(0x61000);
  iVar5 = HvpBuildSocMMIORegs(0x50000);
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
    *(ulonglong *)(iVar4 + 0x1a0) = *(ulonglong *)(iVar4 + 0x1a0) & 0xfffffffffffffeff;
    eieioOp();
    instructionSynchronize();
    *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xa4) = *(undefined8 *)(iVar5 + 0x6000);
    *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xac) = *(undefined8 *)(iVar5 + 0x6010);
    *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xb4) = *(undefined8 *)(iVar5 + 0x6020);
    *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xbc) = *(undefined8 *)(iVar5 + 0x6030);
    *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xc4) = *(undefined8 *)(iVar5 + 0x6040);
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
    *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xcc) = *(undefined8 *)(iVar4 + 0x1c8);
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



void HvpRestoreThread(void)

{
  byte bVar1;
  int iVar2;
  int in_r2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  char *pcVar7;
  longlong in_spr131;
  
  __Save_R12_29_thru_31();
  lVar6 = in_spr131 + 0x81;
  pcVar7 = (char *)lVar6;
  if (*pcVar7 != '\x03') {
    _v_MACHINE_CHECK_0();
  }
  *pcVar7 = '\x04';
  sync(0);
  iVar3 = HvpBuildSocMMIORegs(0x61000);
  iVar4 = HvpBuildSocMMIORegs(0x50000);
  iVar5 = (int)in_spr131;
  bVar1 = *(byte *)(iVar5 + 0x80);
  iVar2 = (uint)bVar1 * 0x1000 + iVar4;
  if ((bVar1 & 1) == 0) {
    if (bVar1 == 0) {
      *(undefined8 *)(iVar4 + 0x6000) = *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xa4);
      eieioOp();
      *(undefined8 *)(iVar4 + 0x6010) = *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xac);
      eieioOp();
      *(undefined8 *)(iVar4 + 0x6020) = *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xb4);
      eieioOp();
      *(undefined8 *)(iVar4 + 0x6030) = *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xbc);
      eieioOp();
      *(undefined8 *)(iVar4 + 0x6040) = *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xc4);
      eieioOp();
      instructionSynchronize();
      *(undefined8 *)(iVar3 + 0x1c8) = *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xcc);
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
    *(ulonglong *)(iVar3 + 0x1a0) = *(ulonglong *)(iVar3 + 0x1a0) | 0x100;
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



longlong FUN_000089e0(ulonglong param_1,longlong param_2)

{
  int in_r2;
  
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
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



ulonglong FUN_00008a60(ulonglong param_1)

{
  int in_r2;
  ulonglong uVar1;
  
  uVar1 = *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0);
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
  qword local_8;
  
  if (*(char *)(in_spr131 + 0x80) == '\0') {
    _v_MACHINE_CHECK_0();
  }
  HvpSaveThread();
  HvpSleepThread();
  HvpRestoreThread();
  return 0;
}



void FUN_00008b80(int param_1,int param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = *(ulonglong *)(param_1 + 0x188);
  *(undefined8 *)(param_2 + 0x6020) = 0x400;
  eieioOp();
  instructionSynchronize();
  do {
  } while ((*(ulonglong *)(param_2 + 0x6020) & 0x2000) != 0);
  *(ulonglong *)(param_1 + 0x188) =
       (ulonglong)((param_3 & 0x3f) << 8) | 0xff004000 | uVar1 & 0xffffffffffff40f7;
  eieioOp();
  do {
  } while ((*(ulonglong *)(param_2 + 0x6020) & 0x2000) == 0);
  *(ulonglong *)(param_1 + 0x188) = *(ulonglong *)(param_1 + 0x188) | 0x8000;
  eieioOp();
  instructionSynchronize();
  *(undefined8 *)(param_2 + 0x6020) = 0;
  eieioOp();
  instructionSynchronize();
  return;
}



ulonglong FUN_00008c40(int param_1)

{
  int in_r2;
  ulonglong uVar1;
  longlong lVar2;
  
  uVar1 = *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0);
  if (0x7104ff < uVar1) {
    lVar2 = countLeadingZeros(*(ulonglong *)(param_1 + 0x30) & 0x7fffffffffffffff);
    if (uVar1 < 0x710900) {
      uVar1 = 9 - lVar2;
    }
    else {
      uVar1 = 0xd - lVar2;
    }
    return uVar1 & 0xffffffff;
  }
  return 0;
}



ulonglong FUN_00008c90(int param_1,int param_2)

{
  int in_r2;
  int iVar2;
  undefined8 uVar1;
  ulonglong uVar3;
  ulonglong uVar4;
  qword local_8;
  
  uVar3 = *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0);
  if (uVar3 < 0x710500) {
    if (uVar3 < 0x710900) {
      return 0;
    }
  }
  else {
    if (uVar3 < 0x710900) {
      if (param_2 == 0) {
        uVar4 = (ulonglong)*(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd4);
      }
      else {
        if (param_2 == 1) {
          uVar4 = (ulonglong)*(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd7);
        }
        else {
          uVar4 = (ulonglong)*(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd5);
        }
      }
      if (uVar4 != 0xff) {
        return uVar4;
      }
      uVar4 = *(ulonglong *)(param_1 + 0x188);
      if (uVar3 < 0x710700) {
        if (param_2 == 2) {
          iVar2 = 0x38;
        }
        else {
          uVar3 = uVar4 >> 0x30 & 0x3f;
          iVar2 = (int)uVar3;
          if (param_2 == 1) {
            iVar2 = FUN_000089e0(uVar3,uVar4 >> 0x27 & 0xe);
          }
        }
        return (ulonglong)*(byte *)(iVar2 + in_r2 + 0x11aa8);
      }
      return (ulonglong)*(byte *)(((uint)(uVar4 >> 0x30) & 0x3f) + in_r2 + 0x11ae8);
    }
  }
  uVar1 = FUN_00008c40();
  return uVar1;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 HvxEnableTimebase(undefined4 param_1)

{
  int iVar1;
  undefined8 uVar2;
  qword local_10;
  qword local_8;
  
  iVar1 = HvpBuildSocMMIORegs(0x61000);
  uVar2 = countLeadingZeros(param_1);
  *(ulonglong *)(iVar1 + 0x1a0) =
       (ulonglong)(((uint)uVar2 >> 5 & 1) << 8) ^ 0x100 |
       *(ulonglong *)(iVar1 + 0x1a0) & 0xfffffffffffffeff;
  eieioOp();
  instructionSynchronize();
  return 0;
}



void FUN_00008e00(undefined8 param_1,ulonglong param_2,ulonglong param_3)

{
  int in_r2;
  undefined8 uVar1;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  ulonglong *puVar8;
  int iVar9;
  int iVar10;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar11;
  ulonglong uVar12;
  uint *puVar13;
  ulonglong uVar14;
  
  uVar1 = __Save_R12_16_thru_31();
  iVar4 = HvpBuildSocMMIORegs(0x60000);
  iVar5 = HvpBuildSocMMIORegs(0x61000);
  iVar6 = HvpBuildSocMMIORegs(0x50000);
  iVar7 = HvpBuildSocMMIORegs(0x30000);
  puVar8 = (ulonglong *)HvpBuildSocMMIORegs(0x48000);
  iVar9 = FUN_000006cc(0x1020000);
  iVar10 = FUN_000006cc(0x1000000);
  uVar2 = FUN_00008a60(uVar1);
  uVar14 = *(ulonglong *)(iVar5 + 0x188);
  if ((0x7106ff < *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0)) &&
     ((uVar14 & 0x80) == 0)) {
    uVar14 = uVar14 | 0x80;
    *(ulonglong *)(iVar5 + 0x188) = uVar14;
    eieioOp();
    instructionSynchronize();
  }
  uVar3 = FUN_00008c40(iVar5);
  if (((param_2 == (uVar14 & 7)) && (uVar2 == (uVar14 >> 8 & 0x3f))) && (param_3 == uVar3)) {
    return;
  }
  *(ulonglong *)(iVar4 + 0xb58) = *(ulonglong *)(iVar4 + 0xb58) | 0x8000000000000000;
  eieioOp();
  instructionSynchronize();
  *(ulonglong *)(iVar5 + 0x50) = *(ulonglong *)(iVar5 + 0x50) & 0xfffffffdffffffff;
  eieioOp();
  instructionSynchronize();
  *(ulonglong *)(iVar5 + 0x60) = *(ulonglong *)(iVar5 + 0x60) | 0x200000000;
  eieioOp();
  instructionSynchronize();
  puVar13 = (uint *)(iVar9 + 4);
  *puVar13 = ((uint)*(byte *)puVar13 | 1) << 0x18 | (uint)*(byte *)(iVar9 + 5) << 0x10 |
             ((uint)*(byte *)(iVar9 + 6) << 0x10) >> 8 | (uint)*(byte *)(iVar9 + 7);
  eieioOp();
  instructionSynchronize();
  HvxEnableTimebase(1);
  FUN_000004a8(10000);
  HvxEnableTimebase(0);
  if (param_2 != 1) {
    *(undefined8 *)(iVar7 + 0x20) = 0x2000000000000000;
    eieioOp();
    instructionSynchronize();
    if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
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
  if ((uVar3 < param_3) &&
     (*(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) - 0x710500U < 0x400)) {
    *(longlong *)(iVar5 + 0x30) = param_3 << 0x3c;
    eieioOp();
  }
  uVar12 = uVar14 >> 8 & 0x3f;
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
    uVar11 = uVar2;
    if (uVar2 < 0x15) {
      uVar11 = uVar2 + 0x3e;
    }
    if (uVar12 < 0x15) {
      uVar12 = uVar12 + 0x3e;
    }
    if (uVar11 < uVar12) {
LAB_000090dc:
      FUN_00008b80(iVar5,iVar6,uVar2);
      uVar14 = *(ulonglong *)(iVar5 + 0x188);
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
    } while ((*(ulonglong *)(iVar6 + 0x6020) & 0x2000) != 0);
    *(undefined8 *)(iVar6 + 8) = 0x78;
    eieioOp();
    instructionSynchronize();
    *(ulonglong *)(iVar5 + 0x188) =
         *(ulonglong *)(iVar5 + 0x188) & 0xffffffffffff3ff8 | param_2 & 7 | 0xff0008;
    eieioOp();
    HvpSleepThread();
    uVar14 = *(ulonglong *)(iVar5 + 0x188) | 0x8000;
    *(ulonglong *)(iVar5 + 0x188) = uVar14;
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
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
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
  FUN_00008b80(iVar5,iVar6,uVar2);
  uVar14 = *(ulonglong *)(iVar5 + 0x188);
LAB_00009248:
  if ((param_3 < uVar3) &&
     (*(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) - 0x710500U < 0x400)) {
    *(longlong *)(iVar5 + 0x30) = param_3 << 0x3c;
    eieioOp();
  }
  if ((uVar14 & 7) == 1) {
    *(undefined8 *)(iVar7 + 0x10) = 0xdfffffffffffffff;
    eieioOp();
    instructionSynchronize();
    if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
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
  *(ulonglong *)(iVar4 + 0xb58) = *(ulonglong *)(iVar4 + 0xb58) & 0x7fffffffffffffff;
  eieioOp();
  instructionSynchronize();
  *puVar13 = ((uint)*(byte *)puVar13 & 0xfffffffe) << 0x18 | (uint)*(byte *)(iVar9 + 5) << 0x10 |
             ((uint)*(byte *)(iVar9 + 6) << 0x10) >> 8 | (uint)*(byte *)(iVar9 + 7);
  eieioOp();
  instructionSynchronize();
  return;
}



// WARNING: Could not reconcile some variable overlaps

ulonglong HvxSetPowerMode(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  undefined uVar4;
  int in_r2;
  int iVar5;
  ulonglong uVar6;
  int iVar7;
  undefined uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  undefined8 uVar11;
  ulonglong uVar12;
  uint uVar13;
  int iVar14;
  ulonglong uVar15;
  int in_spr131;
  uint param_1;
  byte bStack00000014;
  qword local_50;
  
  uVar6 = __Save_R12_25_thru_31();
  if (*(char *)(in_spr131 + 0x80) != '\0') {
    _v_MACHINE_CHECK_0();
  }
  HvpSaveThread(0);
  param_1 = (uint)(uVar6 >> 0x20);
  if ((uVar6 & 0x200000000) != 0) {
    *(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd4) = (byte)(param_1 >> 4) & 0xf;
    *(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd7) = (byte)(uVar6 >> 0x28) & 0xf;
    *(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd5) = (byte)(param_1 >> 0xc) & 0xf;
  }
  if (((uVar6 & 0x400000000) != 0) &&
     (bStack00000014 = (byte)(uVar6 >> 0x18), (ulonglong)bStack00000014 - 0x79 < 0xf)) {
    *(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd6) = bStack00000014;
  }
  iVar5 = in_r2;
  iVar7 = HvpBuildSocMMIORegs(0x61000);
  uVar10 = *(ulonglong *)(iVar7 + 0x188);
  uVar12 = uVar10 >> 0x38 & 0x3f;
  uVar15 = uVar10 >> 0x30 & 0x3f;
  if ((uVar12 == 0) || (uVar12 == 0x3b)) {
    uVar15 = 0x30;
  }
  uVar12 = (ulonglong)(param_1 & 1);
  if (((uVar6 & 0x100000000) != 0) ||
     (uVar6 = uVar15, 0x58110011 < *(uint *)((int)DWORD_ARRAY_00016260 + iVar5 + 0x6d0))) {
    uVar6 = FUN_000089e0(uVar15,(ulonglong)*(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd6) -
                                0x80);
  }
  if ((uVar12 & 0xffffffff) == 0) {
    iVar14 = 2;
    if (0x7106ff < *(ulonglong *)((int)DWORD_ARRAY_00016260 + iVar5 + 0x6c0)) {
      iVar14 = 1;
    }
    uVar6 = FUN_000089e0(uVar6,(uVar10 >> 0x28 & 7) * (longlong)iVar14);
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
  FUN_00008e00(uVar6,uVar11,uVar9);
  HvpRestoreThread();
  uVar6 = *(ulonglong *)(iVar7 + 0x188);
  uVar13 = local_50._0_4_ | 1;
  if ((uVar6 & 7) != 1) {
    uVar13 = local_50._0_4_ & 0xfffffffe;
  }
  bVar1 = *(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd5);
  bVar2 = *(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd7);
  bVar3 = *(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd4);
  uVar4 = *(undefined *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd6);
  uVar8 = FUN_00008c40(iVar7);
  return CONCAT71(CONCAT61(CONCAT51(CONCAT41((((((uint)bVar1 & 0xf) << 4 | (uint)bVar2 & 0xffffff0f)
                                               << 4 | (uint)bVar3 & 0xf) << 3 |
                                             (uint)(uVar6 >> 0x28) & 7) << 1 | uVar13 & 0xffff0001,
                                             uVar4),(char)uVar15),(char)(uVar6 >> 8)),uVar8) &
         0xffffffffffff3fff;
}



undefined8 HvpBurnFuse(undefined8 param_1,ulonglong param_2)

{
  int in_r2;
  ulonglong uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = __Save_R12_24_thru_31();
  iVar2 = HvpBuildSocMMIORegs(0x61000);
  iVar3 = HvpBuildSocMMIORegs(0x20000);
  iVar4 = 3;
  while( true ) {
    if (0x7106ff < *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0)) {
      *(ulonglong *)(iVar2 + 0x188) = *(ulonglong *)(iVar2 + 0x188) & 0xffffffffffffff7f;
      eieioOp();
      instructionSynchronize();
    }
    do {
    } while ((*(ulonglong *)(iVar3 + 0x2000) & 0x8000000000000000) != 0);
    *(ulonglong *)(iVar3 + 0x2018) = *(ulonglong *)(iVar3 + 0x2018) | 0x8000000000000000;
    eieioOp();
    if ((int)uVar1 == -1) {
      if ((param_2 & 0xffffffff) == 0) {
        param_2 = 1;
      }
      if (0xfff < (param_2 & 0xffffffff)) {
        param_2 = 0xfff;
      }
      HvxEnableTimebase(1);
      FUN_000004a8(param_2 * 1000);
      HvxEnableTimebase(0);
    }
    else {
      HvxEnableTimebase(1);
      FUN_000004a8(1000);
      HvxEnableTimebase(0);
      *(undefined8 *)((int)(uVar1 << 3) + iVar3) = 1;
      eieioOp();
    }
    do {
    } while ((*(ulonglong *)(iVar3 + 0x2000) & 0x8000000000000000) != 0);
    *(ulonglong *)(iVar3 + 0x2018) = *(ulonglong *)(iVar3 + 0x2018) & 0x7fffffffffffffff;
    eieioOp();
    HvxEnableTimebase(1);
    FUN_000004a8(2000);
    HvxEnableTimebase(0);
    do {
    } while ((*(ulonglong *)(iVar3 + 0x2000) & 0x8000000000000000) != 0);
    if (0x7106ff < *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0)) {
      *(ulonglong *)(iVar2 + 0x188) = *(ulonglong *)(iVar2 + 0x188) | 0x80;
      eieioOp();
      instructionSynchronize();
    }
    if ((int)uVar1 == -1) break;
    *(undefined8 *)(iVar3 + 0x2010) = 0x8000000000000000;
    eieioOp();
    do {
    } while ((*(ulonglong *)(iVar3 + 0x2000) & 0x8000000000000000) != 0);
    if ((0x8000000000000000U >> (uVar1 & 0x3f) &
        *(ulonglong *)((int)((uVar1 & 0xffffffff) << 3) + iVar3)) != 0) {
      return 1;
    }
    iVar4 = iVar4 + -1;
    if (iVar4 < 1) {
      return 0;
    }
  }
  return 1;
}



// WARNING: Removing unreachable block (ram,0x00009844)

undefined8 FUN_00009738(void)

{
  int in_r2;
  undefined8 uVar1;
  int iVar3;
  ulonglong uVar2;
  uint uVar4;
  undefined8 *puVar5;
  ulonglong uVar6;
  uint uVar7;
  uint uVar8;
  longlong lVar9;
  longlong lVar10;
  word local_b0;
  qword local_a8;
  
  __Save_R12_24_thru_31();
  if ((*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710900) ||
     (*(int *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x274) == 0)) {
    iVar3 = HvpBuildSocMMIORegs(0x20000);
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



// WARNING: Removing unreachable block (ram,0x000099a4)
// WARNING: Removing unreachable block (ram,0x000099c8)
// WARNING: Removing unreachable block (ram,0x000099d4)
// WARNING: Removing unreachable block (ram,0x000099e8)
// WARNING: Removing unreachable block (ram,0x00009a10)
// WARNING: Removing unreachable block (ram,0x000099f4)

undefined8 FUN_000098d8(void)

{
  int in_r2;
  undefined8 uVar1;
  int iVar2;
  undefined8 *puVar4;
  ulonglong uVar3;
  longlong lVar5;
  word local_90;
  qword local_80;
  
  __Save_R12_28_thru_31();
  if ((*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710900) ||
     (*(int *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x274) == 0)) {
    iVar2 = HvpBuildSocMMIORegs(0x20000);
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



undefined8 FUN_00009a28(void)

{
  int in_r2;
  int iVar2;
  longlong lVar1;
  undefined8 *puVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  uint uVar6;
  ulonglong uVar7;
  longlong lVar8;
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
  if ((0x7108ff < *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0)) &&
     (*(int *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x274) != 0)) {
    return 7;
  }
  iVar2 = HvpBuildSocMMIORegs(0x20000);
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
  iVar2 = j_XeCryptUidEccDecode(&local_a0);
  if (-1 < iVar2) {
    lVar8 = j_XeCryptHammingWeight(local_70 | local_78);
    lVar1 = j_XeCryptHammingWeight((local_60 | local_68) & 0xffffffffff030000);
    if ((lVar1 + lVar8 & 0xffffffffU) == 0x35) {
      return 0;
    }
  }
  lVar8 = j_XeCryptHammingWeight();
  lVar1 = j_XeCryptHammingWeight((local_60 | local_68) & 0xffffffffff030000);
  uVar7 = lVar1 + lVar8;
  uVar4 = uVar7 & 0xffffffff;
  if (0x35 < uVar4) {
    return 8;
  }
  do {
    if (0x34 < uVar4) {
      j_XeCryptUidEccEncode(&local_a0);
      uVar6 = 0;
      uVar4 = 0;
      do {
        uVar7 = 0;
        do {
          uVar5 = (ulonglong)((uint)uVar7 & 7);
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
    FUN_0000b488(&local_b0,4);
    uVar4 = 0x6a - uVar7;
    uVar5 = 0;
    trapWord(6,uVar4,0);
    uVar4 = (ulonglong)local_b0 -
            (longlong)(int)((ulonglong)local_b0 / (uVar4 & 0xffffffff)) * (longlong)(int)uVar4;
    local_b0 = (dword)uVar4;
    do {
      if ((*(byte *)((int)&local_a0 + ((uint)(uVar5 >> 3) & 0x1fffffff)) >>
           (ulonglong)((uint)uVar5 & 7) & 1) == 0) {
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
         (byte)(1 << (ulonglong)((uint)uVar5 & 7)) ^ *(byte *)(uVar6 + (int)&local_a0);
  } while( true );
}



ulonglong FUN_00009cc8(void)

{
  int in_r2;
  ulonglong uVar1;
  int iVar3;
  ulonglong uVar2;
  qword *pqVar4;
  longlong lVar5;
  qword local_90;
  
  __Save_R12_28_thru_31();
  if ((*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710900) ||
     (*(int *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x274) == 0)) {
    iVar3 = HvpBuildSocMMIORegs(0x20000);
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
    uVar1 = (ulonglong)(-(uint)(0xc < uVar1) & 0xc);
  }
  else {
    uVar1 = 10;
  }
  return uVar1;
}



undefined8 FUN_00009db0(void)

{
  byte bVar1;
  undefined8 in_r2;
  undefined8 uVar2;
  ulonglong uVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  
  __Save_R12_29_thru_31();
  iVar4 = (int)in_r2;
  if ((*(ulonglong *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x6c0) < 0x710900) ||
     (*(int *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x274) == 0)) {
    bVar1 = *(byte *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x204);
    if (*(byte *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x240) < bVar1) {
      iVar4 = 0;
      lVar6 = (ulonglong)bVar1 * 4 + 0x1bf;
      iVar5 = 4;
      do {
        uVar3 = HvpBurnFuse(lVar6,0);
        if ((uVar3 & 0xffffffff) == 0) {
          iVar4 = iVar4 + 1;
        }
        iVar5 = iVar5 + -1;
        lVar6 = lVar6 + -1;
      } while (iVar5 != 0);
      if (iVar4 == 4) {
        return 0x15;
      }
      WORD_00000006 = 0x8000;
                    // WARNING: Read-only address (ram,0x00000006) is written
      *(undefined2 *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + (int)in_r2 + 0x14) + 0x600) =
           0x8000;
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 0x13;
  }
                    // WARNING: Read-only address (ram,0x00000006) is written
  return uVar2;
}



// WARNING: Restarted to delay deadcode elimination for space: stack

longlong FUN_00009e78(void)

{
  byte bVar1;
  int iVar2;
  longlong in_r2;
  ulonglong uVar3;
  int iVar5;
  longlong lVar4;
  qword *pqVar6;
  undefined *puVar7;
  ulonglong uVar8;
  uint uVar9;
  longlong lVar10;
  qword local_80;
  qword local_70;
  qword local_68;
  qword local_60;
  qword local_58;
  
  uVar3 = __Save_R12_24_thru_31();
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x6c0) < 0x710900) {
    return 0;
  }
  iVar5 = HvpBuildSocMMIORegs(0x20000);
  *(ulonglong *)(iVar5 + 0x2028) =
       *(ulonglong *)(iVar5 + 0x2028) & 0x3fffffffffffffff | 0x4000000000000000;
  FUN_00008388(&local_70);
  iVar2 = (int)in_r2;
  bVar1 = *(byte *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x234);
  if (bVar1 < 0x41) {
    if ((bVar1 != 0) && ((uVar3 & 0x8000000) == 0)) {
      lVar4 = 0x17;
      goto LAB_0000a050;
    }
    FUN_00003e80(uVar3);
    pqVar6 = &local_70;
    lVar10 = 0x10;
    lVar4 = in_r2 + 0x16470;
    do {
      puVar7 = (undefined *)lVar4;
      lVar4 = lVar4 + 1;
      *(undefined *)pqVar6 = *puVar7;
      pqVar6 = (qword *)((int)pqVar6 + 1);
      lVar10 = lVar10 + -1;
    } while (lVar10 != 0);
    uVar3 = 0;
    do {
      uVar9 = 0;
      uVar8 = 0;
      do {
        if ((*(byte *)((int)&local_80 + (int)(uVar8 >> 3)) >> (ulonglong)(uVar9 & 7) & 1) != 0) {
          HvpBurnFuse(((ulonglong)(uVar9 & 0x38) - (ulonglong)(uVar9 & 7)) + uVar3 + 0x207,0);
        }
        uVar9 = uVar9 + 1;
        uVar8 = uVar8 + 1;
      } while (uVar9 < 0x40);
      uVar3 = uVar3 + 0x40;
    } while ((uVar3 & 0xffffffff) < 0x100);
    FUN_00008388(&local_70);
    if ((*(longlong *)(in_r2 + 0x16470) != 0) ||
       (*(longlong *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x218) != 0)) {
      uVar3 = 0x200;
      do {
        uVar8 = 0;
        do {
          HvpBurnFuse(uVar3 + uVar8,0);
          uVar8 = uVar8 + 1;
        } while ((uVar8 & 0xffffffff) < 0x40);
        uVar3 = uVar3 + 0x40;
      } while ((uVar3 & 0xffffffff) < 0x300);
      FUN_00008388(&local_70);
      lVar4 = (ulonglong)
              (-(uint)(0x40 < *(byte *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x234)) & 0xffffffe8) +
              0x18;
      goto LAB_0000a050;
    }
  }
  lVar4 = 0;
LAB_0000a050:
  *(ulonglong *)(iVar5 + 0x2028) = *(ulonglong *)(iVar5 + 0x2028) & 0x3fffffffffffffff;
  return lVar4;
}



ulonglong FUN_0000a068(void)

{
  int iVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  word local_90;
  qword local_88;
  
  __Save_R12_28_thru_31();
  iVar1 = HvpBuildSocMMIORegs(0x20000);
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
  return (ulonglong)(-(uint)(lVar5 != 0) & 3);
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x0000a408)
// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_0000a120(void)

{
  byte bVar1;
  int in_r2;
  int iVar3;
  longlong lVar2;
  ulonglong uVar4;
  qword *pqVar5;
  int iVar6;
  undefined uVar8;
  uint uVar7;
  longlong lVar9;
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
  
  iVar3 = HvpBuildSocMMIORegs(0x20000);
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
    lVar9 = (longlong)iVar6;
    iVar6 = iVar6 + 0x40;
    *pqVar5 = *(qword *)((int)(lVar9 << 3) + iVar3);
    pqVar5 = pqVar5 + 1;
  } while (iVar6 < 0x300);
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710900) {
    *(undefined *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x234) = 0x80;
    *(undefined4 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x274) = 0;
  }
  else {
    *(ulonglong *)(iVar3 + 0x2028) =
         *(ulonglong *)(iVar3 + 0x2028) & 0x3fffffffffffffff | 0x4000000000000000;
    FUN_00008388(0);
    *(ulonglong *)(iVar3 + 0x2028) = *(ulonglong *)(iVar3 + 0x2028) & 0x3fffffffffffffff;
  }
  iVar3 = j_XeCryptUidEccDecode(&local_90);
  if (-1 < iVar3) {
    lVar9 = j_XeCryptHammingWeight(local_60 | local_68);
    lVar2 = j_XeCryptHammingWeight((local_50 | local_58) & 0xffffffffff030000);
    if ((lVar2 + lVar9 & 0xffffffffU) == 0x35) {
                    // WARNING: Read-only address (ram,0x00000020) is written
      DWORD_ARRAY_00000020._0_8_ = local_90;
                    // WARNING: Read-only address (ram,0x00000028) is written
      DWORD_ARRAY_00000020._8_8_ = local_50 | local_58;
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
    *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6b4) =
         *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6b4) | 1;
  }
  lVar9 = 0x10;
  do {
    uVar8 = (undefined)lVar9;
    if ((local_70 & 0xf) != 0) break;
    lVar9 = lVar9 + -1;
    uVar8 = (undefined)lVar9;
    local_70 = local_70 >> 4;
  } while (0 < (int)lVar9);
  *(undefined *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xe4) = uVar8;
  iVar3 = 5;
  *(undefined *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x235) = (char)uVar4;
  if ((local_80 & 0x300000000000000) != 0) {
    iVar3 = 1;
  }
  iVar6 = iVar3 + -1;
  uVar7 = 0;
  *(undefined *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x240) = 0;
  *(undefined *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x278) = (char)(iVar3 << 4);
  if (-1 < iVar6) {
    iVar3 = iVar3 + 6;
    do {
      uVar4 = *(ulonglong *)((int)&local_80 + (int)((longlong)iVar3 << 3));
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
  *(undefined *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x240) = (char)uVar7;
LAB_0000a390:
  iVar3 = in_r2;
  if ((local_80 & 0xffffffffffffff) != 0) {
    FUN_00003830(1,0);
    uVar7 = (uint)*(byte *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x240);
  }
  DWORD_00000014 = uVar7 | 0x3000000;
                    // WARNING: Read-only address (ram,0x00000014) is written
  bVar1 = *(byte *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x235);
  uVar4 = (ulonglong)bVar1;
  if ((((bVar1 != 1) && (bVar1 != 3)) && (bVar1 != 4)) && ((bVar1 == 0 || (bVar1 == 2)))) {
    _v_MACHINE_CHECK_0();
  }
  if (((*(ushort *)((int)DWORD_ARRAY_00016260 + iVar3 + 0x6bc) & 4) != 0) &&
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
  ulonglong uVar1;
  ulonglong uVar3;
  undefined8 *puVar4;
  int iVar5;
  longlong lVar6;
  word local_70;
  qword local_68;
  qword local_60;
  qword local_10;
  qword local_8;
  
  iVar2 = HvpBuildSocMMIORegs(0x20000);
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
    lVar6 = (longlong)iVar5;
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
    uVar1 = (ulonglong)(((uint)uVar1 & 0x7fff) << 1 | (uint)(uVar3 != 0));
  } while (iVar2 != 0);
  uVar3 = 0;
  iVar2 = 0x10;
  do {
    iVar2 = iVar2 + -1;
    uVar3 = (ulonglong)(((uint)uVar3 & 0x7fff) << 1) |
            (ulonglong)((local_60 & 0xf000000000000000) != 0);
    local_60 = local_60 << 4;
  } while (iVar2 != 0);
  FUN_000004e8(uVar1,uVar3,param_1);
  return;
}



// WARNING: Removing unreachable block (ram,0x0000a780)

ulonglong HvxBlowFuses(void)

{
  dword dVar1;
  int in_r2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar2;
  undefined8 uVar6;
  longlong lVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  int in_spr131;
  
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
  iVar4 = HvpBuildSocMMIORegs(0x61000);
  iVar5 = HvpBuildSocMMIORegs(0x20000);
  HvpSaveThread(1);
  uVar8 = *(ulonglong *)(iVar4 + 0x188);
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
    uVar6 = 0x38;
  }
  else {
    uVar6 = FUN_000089e0(uVar8 >> 0x30 & 0x3f,
                         (uVar8 >> 0x28 & 7) +
                         (ulonglong)*(byte *)((int)DWORD_ARRAY_0001613c + in_r2 + 0xd6) + -0x80);
  }
  uVar2 = FUN_00008c90(iVar4,2);
  FUN_00008e00(uVar6,4,uVar2);
  if (*(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6c0) < 0x710700) {
    uVar9 = 0x69ff800;
    lVar7 = 0xc2a2619;
  }
  else {
    uVar9 = 0x38910000;
    lVar7 = 0x80e190d;
  }
  *(ulonglong *)(iVar5 + 0x2008) = lVar7 << 0x20 | uVar9;
  eieioOp();
  instructionSynchronize();
  uVar9 = 0;
  if ((dVar1 & 0x80) == 0) {
    if ((((((dVar1 & 1) == 0) || (uVar9 = FUN_00009738(), (uVar9 & 0xffffffff) == 0)) &&
         (((dVar1 & 2) == 0 || (uVar9 = FUN_000098d8(), (uVar9 & 0xffffffff) == 0)))) &&
        (((dVar1 & 4) == 0 || (uVar9 = FUN_00009a28((ulonglong)dVar1), (uVar9 & 0xffffffff) == 0))))
       && (((dVar1 & 8) == 0 || (uVar9 = FUN_00009cc8(), (uVar9 & 0xffffffff) == 0)))) {
      if ((dVar1 & 0x10) == 0) {
        if ((dVar1 & 0x20) == 0) {
          if ((((dVar1 & 0x40) == 0) || (uVar9 = FUN_00009db0(), (uVar9 & 0xffffffff) == 0)) &&
             ((dVar1 & 0x100000) != 0)) {
            uVar9 = FUN_00009e78((ulonglong)dVar1);
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
    HvpBurnFuse(0xffffffffffffffff,(ulonglong)(dVar1 >> 8 & 0xfff));
  }
  uVar6 = FUN_00008c90(iVar4,(ulonglong)((uVar8 & 7) != 1));
  FUN_00008e00(uVar8 >> 8 & 0x3f,uVar8 & 7,uVar6);
  if ((dVar1 & 0x80) == 0) {
    FUN_0000a120();
  }
  HvpRestoreThread();
  return uVar9;
}



// WARNING: Variable defined which should be unmapped: local_98

void __Save_R12_14_thru_31(void)

{
  qword local_98;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_90

void __Save_R12_15_thru_31(void)

{
  qword local_90;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_88

void __Save_R12_16_thru_31(void)

{
  qword local_88;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_80

void __Save_R12_17_thru_31(void)

{
  qword local_80;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_78

void __Save_R12_18_thru_31(void)

{
  qword local_78;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_70

void __Save_R12_19_thru_31(void)

{
  qword local_70;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_68

void __Save_R12_20_thru_31(void)

{
  qword local_68;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_60

void __Save_R12_21_thru_31(void)

{
  qword local_60;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_58

void __Save_R12_22_thru_31(void)

{
  qword local_58;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_50

void __Save_R12_23_thru_31(void)

{
  qword local_50;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_48

void __Save_R12_24_thru_31(void)

{
  qword local_48;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_40

void __Save_R12_25_thru_31(void)

{
  qword local_40;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_38

void __Save_R12_26_thru_31(void)

{
  qword local_38;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_30

void __Save_R12_27_thru_31(void)

{
  qword local_30;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_28

void __Save_R12_28_thru_31(void)

{
  qword local_28;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_20

void __Save_R12_29_thru_31(void)

{
  qword local_20;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_18

void __Save_R12_30_thru_31(void)

{
  qword local_18;
  
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void __Save_R12_31_thru_31(void)

{
  qword local_10;
  qword local_8;
  
  return;
}



void __Rest_R12_lr_14_thru_31(void)

{
  qword local_98;
  
  return;
}



void __Rest_R12_lr_15_thru_31(void)

{
  qword local_90;
  
  return;
}



void __Rest_R12_lr_16_thru_31(void)

{
  qword local_88;
  
  return;
}



void __Rest_R12_lr_17_thru_31(void)

{
  qword local_80;
  
  return;
}



void __Rest_R12_lr_18_thru_31(void)

{
  qword local_78;
  
  return;
}



void __Rest_R12_lr_19_thru_31(void)

{
  qword local_70;
  
  return;
}



void __Rest_R12_lr_20_thru_31(void)

{
  qword local_68;
  
  return;
}



void __Rest_R12_lr_21_thru_31(void)

{
  qword local_60;
  
  return;
}



void __Rest_R12_lr_22_thru_31(void)

{
  qword local_58;
  
  return;
}



void __Rest_R12_lr_23_thru_31(void)

{
  qword local_50;
  
  return;
}



void __Rest_R12_lr_24_thru_31(void)

{
  qword local_48;
  
  return;
}



void __Rest_R12_lr_25_thru_31(void)

{
  qword local_40;
  
  return;
}



void __Rest_R12_lr_26_thru_31(void)

{
  qword local_38;
  
  return;
}



void __Rest_R12_lr_27_thru_31(void)

{
  qword local_30;
  
  return;
}



void __Rest_R12_lr_28_thru_31(void)

{
  qword local_28;
  
  return;
}



void __Rest_R12_lr_29_thru_31(void)

{
  qword local_20;
  
  return;
}



void __Rest_R12_lr_30_thru_31(void)

{
  qword local_18;
  
  return;
}



void __Rest_R12_lr_31_thru_31(void)

{
  qword local_10;
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
  ulonglong uVar11;
  uint uVar13;
  undefined8 uVar12;
  ulonglong uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  int iVar17;
  longlong lVar18;
  undefined8 *puVar19;
  undefined4 *puVar20;
  undefined *puVar21;
  qword local_8;
  
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
          uVar11 = (ulonglong)(uVar13 >> 2);
          param_3 = param_3 - uVar13;
          do {
            puVar10 = puVar10 + 1;
            puVar7 = puVar7 + 1;
            *puVar7 = *puVar10;
            uVar11 = uVar11 - 1;
          } while (uVar11 != 0);
        }
        uVar11 = (ulonglong)(param_3 >> 7);
        if (param_3 >> 7 != 0) {
          bVar2 = (param_3 & 0x7f) == 0;
          lVar18 = (ulonglong)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
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
      uVar14 = (ulonglong)uVar13;
      uVar11 = (ulonglong)(param_3 & 3);
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
        uVar11 = (ulonglong)(param_3 >> 7);
        if (param_3 >> 7 != 0) {
          bVar2 = (param_3 & 0x7f) == 0;
          lVar18 = (ulonglong)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
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
      uVar11 = (ulonglong)(param_3 & 0x7f);
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
        uVar11 = (ulonglong)(uVar13 >> 3);
        param_3 = param_3 - uVar13;
        do {
          puVar9 = puVar9 + 1;
          puVar6 = puVar6 + 1;
          *puVar6 = *puVar9;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      uVar11 = (ulonglong)(param_3 >> 7);
      if (param_3 >> 7 != 0) {
        bVar2 = (param_3 & 0x7f) == 0;
        lVar18 = (ulonglong)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
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
  uVar14 = (ulonglong)uVar13;
  uVar11 = (ulonglong)(param_3 & 7);
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



void FUN_0000ac6c(undefined4 *param_1,undefined4 *param_2,ulonglong param_3)

{
  undefined uVar1;
  undefined4 uVar2;
  uint uVar3;
  longlong lVar4;
  ulonglong uVar5;
  
  lVar4 = param_3 + 1;
  while (lVar4 = lVar4 + -1, lVar4 != 0 && ((uint)param_1 & 3) == 0) {
    param_3 = param_3 - 1;
    uVar1 = *(undefined *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    *(undefined *)param_1 = uVar1;
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  uVar3 = (uint)param_3 >> 2;
  uVar5 = (ulonglong)uVar3;
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



void memset(uint *param_1,ulonglong param_2,ulonglong param_3)

{
  uint uVar1;
  longlong lVar2;
  ulonglong uVar3;
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
  uVar3 = (ulonglong)uVar1;
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
  ulonglong uVar11;
  uint uVar13;
  undefined8 uVar12;
  ulonglong uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  int iVar17;
  longlong lVar18;
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
    uVar11 = (ulonglong)(param_3 >> 2);
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
          uVar11 = (ulonglong)(uVar13 >> 2);
          param_3 = param_3 - uVar13;
          do {
            puVar10 = puVar10 + 1;
            puVar8 = puVar8 + 1;
            *puVar8 = *puVar10;
            uVar11 = uVar11 - 1;
          } while (uVar11 != 0);
        }
        uVar11 = (ulonglong)(param_3 >> 7);
        if (param_3 >> 7 != 0) {
          bVar1 = (param_3 & 0x7f) == 0;
          lVar18 = (ulonglong)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
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
      uVar14 = (ulonglong)uVar13;
      uVar11 = (ulonglong)(param_3 & 3);
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
        uVar11 = (ulonglong)(param_3 >> 7);
        if (param_3 >> 7 != 0) {
          bVar1 = (param_3 & 0x7f) == 0;
          lVar18 = (ulonglong)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
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
      uVar11 = (ulonglong)(param_3 & 0x7f);
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
        uVar11 = (ulonglong)(uVar13 >> 3);
        param_3 = param_3 - uVar13;
        do {
          puVar9 = puVar9 + 1;
          puVar6 = puVar6 + 1;
          *puVar6 = *puVar9;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      uVar11 = (ulonglong)(param_3 >> 7);
      if (param_3 >> 7 != 0) {
        bVar1 = (param_3 & 0x7f) == 0;
        lVar18 = (ulonglong)((param_3 + 0x7f >> 7) - 1 & 7) + 1;
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
  uVar14 = (ulonglong)uVar13;
  uVar11 = (ulonglong)(param_3 & 7);
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



void FUN_0000b0a8(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00027ee0();
  return;
}



void FUN_0000b0b0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00027f08();
  return;
}



void FUN_0000b0b8(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00026828();
  return;
}



void FUN_0000b0c0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029b58();
  return;
}



void FUN_0000b0c8(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00030398();
  return;
}



void FUN_0000b0d0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029760();
  return;
}



void FUN_0000b0d8(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002c8d8)();
  return;
}



void FUN_0000b0e0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029670();
  return;
}



void FUN_0000b0e8(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029710();
  return;
}



void FUN_0000b0f0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029720();
  return;
}



void FUN_0000b0f8(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002afb0)();
  return;
}



void FUN_0000b108(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_000309c8();
  return;
}



void FUN_0000b110(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002d1a0)();
  return;
}



void FUN_0000b118(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002d118)();
  return;
}



void FUN_0000b120(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002d6e8();
  return;
}



void FUN_0000b128(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002d8c0();
  return;
}



void FUN_0000b130(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002da88();
  return;
}



void FUN_0000b138(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002ddc8();
  return;
}



void FUN_0000b140(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002db48)();
  return;
}



void FUN_0000b148(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_000318a8();
  return;
}



void FUN_0000b150(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_000200a8();
  return;
}



void FUN_0000b158(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00030000();
  return;
}



void FUN_0000b160(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00030050();
  return;
}



void j_HvxAbandonImageLoad(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002a0b0();
  return;
}



void j_HvxCompleteImageMapping(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029de8();
  return;
}



void j_HvxCreateImageMapping(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002bf58)();
  return;
}



void FUN_0000b1b0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00026278();
  return;
}



void j_HvxEncryptedSweepAddressRange(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002b5b8)();
  return;
}



void j_HvxExpansionCall(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00030970();
  return;
}



void j_HvxExpansionInstall(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00030710();
  return;
}



void j_HvxFinishImageDataLoad(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002a410();
  return;
}



void j_HvxFinishImageLoad(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002ad00)();
  return;
}



void j_HvxFlushUserModeTb(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00031f28();
  return;
}



void j_HvxGetImagePageTableEntry(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029be8();
  return;
}



void j_HvxHdcpCalculateAKsvSignature(void)

{
                    // WARNING: Treating indirect jump as call
  thunk_FUN_00023698();
  return;
}



void j_HvxHdcpCalculateBKsvSignature(void)

{
                    // WARNING: Treating indirect jump as call
  thunk_FUN_00023718();
  return;
}



void j_HvxImageXexHeader(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002ba00)();
  return;
}



void j_HvxIptvGetAesCtrTransform(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00030ea8();
  return;
}



void j_HvxIptvGetSessionKeyHash(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00031048();
  return;
}



void j_HvxIptvSetBoundaryKey(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_000309f8();
  return;
}



void j_HvxIptvSetSessionKey(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00030b70();
  return;
}



void j_HvxIptvVerifyOmac1Signature(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00030d28();
  return;
}



void j_HvxLoadImageData(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002a120();
  return;
}



void j_HvxMapImagePage(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029cc0();
  return;
}



void j_HvxResolveImports(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002a7d0)();
  return;
}



void j_HvxRevokeLoad(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002d258)();
  return;
}



void j_HvxRevokeSave(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002d438)();
  return;
}



void j_HvxRevokeUpdate(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002d5a8)();
  return;
}



void j_HvxSetImagePageTableEntry(void)

{
                    // WARNING: Treating indirect jump as call
  j_HvxTest();
  return;
}



void j_HvxSetRevocationList(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002c6c0)();
  return;
}



void j_HvxShadowBoot(void)

{
                    // WARNING: Treating indirect jump as call
  j__v_MACHINE_CHECK_0();
  return;
}



void j_HvxStartResolveImports(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_0002a560();
  return;
}



void j_HvxUnmapImage(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029f58();
  return;
}



void j_HvxUnmapImagePages(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00029eb0();
  return;
}



void j_HvxUnmapImageRange(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)&LAB_0002ae10)();
  return;
}



void j_HvxXexActivationGetNonce(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00030170();
  return;
}



void j_HvxXexActivationSetLicense(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_000301c0();
  return;
}



void j_HvxXexActivationVerifyOwnership(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00030360();
  return;
}



void j_XeCryptAesCbc(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptAesCbc();
  return;
}



void j_XeCryptAesCtr(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptAesCtr();
  return;
}



void j_XeCryptAesEcb(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptAesEcb();
  return;
}



void j_XeCryptAesKey(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptAesKey();
  return;
}



void FUN_0000b378(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00023798();
  return;
}



void j_XeCryptBnDw_Copy(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnDw_Copy();
  return;
}



void j_XeCryptBnDw_SwapLeBe(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnDw_SwapLeBe();
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



void j_XeCryptBnQw_Copy(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQw_Copy();
  return;
}



void j_XeCryptBnQw_SwapDwQwLeBe(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQw_SwapDwQwLeBe();
  return;
}



void j_XeCryptBnQw_Zero(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQw_Zero();
  return;
}



void j_XeCryptBnQwBeSigFormat(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQwBeSigFormat();
  return;
}



void FUN_0000b3c0(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQwBeSigVerify();
  return;
}



void FUN_0000b3c8(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQwNeModExp();
  return;
}



void FUN_0000b3d0(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQwNeModInv();
  return;
}



void FUN_0000b3d8(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQwNeModMul();
  return;
}



void j_HvxKeysRsaPrvCrypt(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQwNeRsaPrvCrypt();
  return;
}



void j_XeCryptBnQwNeRsaPubCrypt(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptBnQwNeRsaPubCrypt();
  return;
}



void j_XeCryptDes3Ecb(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDes3Cbc();
  return;
}



void j_XeCryptDes3Key(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDes3Ecb();
  return;
}



void j_XeCryptDesCbc(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDes3Key();
  return;
}



void j_HvxKeysDesEcb(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDesCbc();
  return;
}



void j_XeCryptDesKey(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDesEcb();
  return;
}



void j_XeCryptDesParity(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptDesKey();
  return;
}



void FUN_0000b420(void)

{
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



void FUN_0000b430(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00023a10();
  return;
}



void j_XeCryptHammingWeight(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptHammingWeight();
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



void FUN_0000b460(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00020000();
  return;
}



void j_XeCryptMemDiff(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptMemDiff();
  return;
}



void FUN_0000b470(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00020040();
  return;
}



void FUN_0000b478(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00023b58();
  return;
}



void FUN_0000b480(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00023b10();
  return;
}



void FUN_0000b488(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00020060();
  return;
}



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



void j_XeCryptRotSum(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptRotSum();
  return;
}



void j_XeCryptRotSum4(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_000232f0();
  return;
}



void j_XeCryptRotSumSha(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptRotSumSha();
  return;
}



void j_XeCryptSha(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptSha();
  return;
}



void j_XeCryptShaFinal(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptShaFinal();
  return;
}



void j_XeCryptShaInit(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptShaInit();
  return;
}



void j_XeCryptShaUpdate(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptShaUpdate();
  return;
}



void FUN_0000b4e0(void)

{
                    // WARNING: Treating indirect jump as call
  FUN_00023450();
  return;
}



void j_XeCryptUidEccDecode(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptUidEccDecode();
  return;
}



void j_XeCryptUidEccEncode(void)

{
                    // WARNING: Treating indirect jump as call
  XeCryptUidEccEncode();
  return;
}



undefined8 FUN_00020000(uint param_1)

{
  int in_r2;
  undefined8 uVar1;
  qword local_8;
  
  if (param_1 < 0x2801) {
    HvpAquireSpinLock(in_r2 + 0x167f8);
    uVar1 = *(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6a8);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



void FUN_00020040(longlong param_1)

{
  int in_r2;
  
  if (param_1 != *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6a8)) {
    return;
  }
  sync(1);
  *(undefined4 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x598) = 0;
  return;
}



void FUN_00020060(undefined8 param_1,undefined8 param_2)

{
  longlong in_r2;
  undefined8 uVar1;
  longlong lVar2;
  
  uVar1 = __Save_R12_29_thru_31();
  lVar2 = in_r2 + 0x16910;
  HvpAquireSpinLock(lVar2);
  XeCryptRc4Ecb(in_r2 + 0x16800,uVar1,param_2);
  FUN_000001e0(lVar2);
  return;
}



void FUN_000200a8(void)

{
  longlong in_r2;
  longlong lVar1;
  qword local_8;
  
  lVar1 = FUN_00000270();
  *(longlong *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x6a8) = lVar1 + 0xc000;
  FUN_00001ce0(in_r2 + 0x16800);
  FUN_00020060(in_r2 + 0x10000,4);
  return;
}



void XeCryptAesKey(uint *param_1,uint *param_2)

{
  int in_r2;
  byte *pbVar1;
  int iVar2;
  ulonglong uVar3;
  uint uVar4;
  ulonglong uVar5;
  uint uVar6;
  ulonglong uVar7;
  uint uVar8;
  ulonglong uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  longlong lVar15;
  
  iVar2 = in_r2 + 0x13cf8;
  uVar4 = *param_2;
  uVar3 = (ulonglong)uVar4;
  uVar6 = param_2[1];
  uVar5 = (ulonglong)uVar6;
  uVar8 = param_2[2];
  uVar7 = (ulonglong)uVar8;
  uVar10 = param_2[3];
  uVar9 = (ulonglong)uVar10;
  iVar11 = in_r2 + 0x13df8;
  iVar12 = in_r2 + 0x141f8;
  iVar13 = in_r2 + 0x145f8;
  iVar14 = in_r2 + 0x149f8;
  pbVar1 = (byte *)((int)DWORD_ARRAY_00014a00 + in_r2 + 0x408);
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
    uVar3 = (ulonglong)
            CONCAT13(*(undefined *)(iVar2 + (uVar4 >> 0x10 & 0xff)),
                     CONCAT12(*(undefined *)(iVar2 + (uVar4 >> 8 & 0xff)),
                              CONCAT11(*(undefined *)(iVar2 + (uVar4 & 0xff)),
                                       *(undefined *)(iVar2 + (uVar4 >> 0x18))))) ^
            (ulonglong)*pbVar1 << 0x18 ^ uVar3;
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
         *(uint *)(iVar11 + (uVar4 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar12 + (uVar4 >> 0xe & 0x3fc)) ^
         *(uint *)(iVar13 + (uVar4 >> 6 & 0x3fc)) ^ *(uint *)(iVar14 + (uVar4 & 0xff) * 4);
    param_1[0x31] =
         *(uint *)(iVar11 + (uVar6 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar12 + (uVar6 >> 0xe & 0x3fc)) ^
         *(uint *)(iVar13 + (uVar6 >> 6 & 0x3fc)) ^ *(uint *)(iVar14 + (uVar6 & 0xff) * 4);
    param_1[0x32] =
         *(uint *)(iVar11 + (uVar8 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar12 + (uVar8 >> 0xe & 0x3fc)) ^
         *(uint *)(iVar13 + (uVar8 >> 6 & 0x3fc)) ^ *(uint *)(iVar14 + (uVar8 & 0xff) * 4);
    param_1[0x33] =
         *(uint *)(iVar11 + (uVar10 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar12 + (uVar10 >> 0xe & 0x3fc))
         ^ *(uint *)(iVar13 + (uVar10 >> 6 & 0x3fc)) ^ *(uint *)(iVar14 + (uVar10 & 0xff) * 4);
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
  int iVar9;
  undefined *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  byte *pbVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  longlong lVar19;
  
  if (param_4 != 0) {
    puVar10 = &UNK_00011bf8 + in_r2;
    iVar9 = in_r2 + 0x11ff8;
    iVar11 = in_r2 + 0x123f8;
    iVar12 = in_r2 + 0x127f8;
    uVar15 = *param_1 ^ *param_2;
    uVar16 = param_1[1] ^ param_2[1];
    uVar17 = param_1[2] ^ param_2[2];
    uVar18 = param_1[3] ^ param_2[3];
    lVar19 = 9;
    puVar7 = param_1 + 4;
    do {
      puVar8 = puVar7;
      uVar4 = uVar15 & 0xff;
      uVar1 = uVar15 >> 6;
      uVar5 = uVar16 & 0xff;
      uVar2 = uVar15 >> 0xe;
      uVar3 = uVar16 >> 6;
      uVar6 = uVar17 & 0xff;
      uVar15 = *(uint *)(puVar10 + (uVar15 >> 0x16 & 0x3fc)) ^
               *(uint *)(iVar9 + (uVar16 >> 0xe & 0x3fc)) ^
               *(uint *)(iVar11 + (uVar17 >> 6 & 0x3fc)) ^ *(uint *)(iVar12 + (uVar18 & 0xff) * 4) ^
               *puVar8;
      uVar16 = *(uint *)(puVar10 + (uVar16 >> 0x16 & 0x3fc)) ^
               *(uint *)(iVar9 + (uVar17 >> 0xe & 0x3fc)) ^
               *(uint *)(iVar11 + (uVar18 >> 6 & 0x3fc)) ^ *(uint *)(iVar12 + uVar4 * 4) ^ puVar8[1]
      ;
      uVar17 = *(uint *)(puVar10 + (uVar17 >> 0x16 & 0x3fc)) ^
               *(uint *)(iVar9 + (uVar18 >> 0xe & 0x3fc)) ^
               *(uint *)(iVar11 + (uVar1 & 0x3fc)) ^ *(uint *)(iVar12 + uVar5 * 4) ^ puVar8[2];
      uVar18 = *(uint *)(puVar10 + (uVar18 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar9 + (uVar2 & 0x3fc)) ^
               *(uint *)(iVar11 + (uVar3 & 0x3fc)) ^ *(uint *)(iVar12 + uVar6 * 4) ^ puVar8[3];
      lVar19 = lVar19 + -1;
      puVar7 = puVar8 + 4;
    } while (lVar19 != 0);
    pbVar14 = BYTE_ARRAY_00011bf9 + in_r2;
    param_3[3] = puVar8[7] ^
                 CONCAT13(pbVar14[uVar18 >> 0x16 & 0x3fc],
                          CONCAT12(pbVar14[uVar15 >> 0xe & 0x3fc],
                                   CONCAT11(pbVar14[uVar16 >> 6 & 0x3fc],
                                            pbVar14[(uVar17 & 0xff) * 4])));
    param_3[2] = puVar8[6] ^
                 CONCAT13(pbVar14[uVar17 >> 0x16 & 0x3fc],
                          CONCAT12(pbVar14[uVar18 >> 0xe & 0x3fc],
                                   CONCAT11(pbVar14[uVar15 >> 6 & 0x3fc],
                                            pbVar14[(uVar16 & 0xff) * 4])));
    param_3[1] = puVar8[5] ^
                 CONCAT13(pbVar14[uVar16 >> 0x16 & 0x3fc],
                          CONCAT12(pbVar14[uVar17 >> 0xe & 0x3fc],
                                   CONCAT11(pbVar14[uVar18 >> 6 & 0x3fc],
                                            pbVar14[(uVar15 & 0xff) * 4])));
    *param_3 = puVar8[4] ^
               CONCAT13(pbVar14[uVar15 >> 0x16 & 0x3fc],
                        CONCAT12(pbVar14[uVar16 >> 0xe & 0x3fc],
                                 CONCAT11(pbVar14[uVar17 >> 6 & 0x3fc],pbVar14[(uVar18 & 0xff) * 4])
                                ));
    return;
  }
  iVar11 = in_r2 + 0x12bf8;
  iVar9 = in_r2 + 0x12ff8;
  iVar12 = in_r2 + 0x133f8;
  iVar13 = in_r2 + 0x137f8;
  uVar15 = param_1[0x54] ^ *param_2;
  uVar16 = param_1[0x55] ^ param_2[1];
  uVar17 = param_1[0x56] ^ param_2[2];
  uVar18 = param_1[0x57] ^ param_2[3];
  lVar19 = 9;
  puVar7 = param_1 + 0x50;
  do {
    puVar8 = puVar7;
    uVar1 = uVar15 >> 0xe;
    uVar2 = uVar16 >> 0xe;
    uVar3 = uVar15 >> 6;
    uVar4 = uVar17 >> 0xe;
    uVar5 = uVar16 >> 6;
    uVar6 = uVar15 & 0xff;
    uVar15 = *(uint *)(iVar11 + (uVar15 >> 0x16 & 0x3fc)) ^
             *(uint *)(iVar9 + (uVar18 >> 0xe & 0x3fc)) ^
             *(uint *)(iVar12 + (uVar17 >> 6 & 0x3fc)) ^ *(uint *)(iVar13 + (uVar16 & 0xff) * 4) ^
             *puVar8;
    uVar16 = *(uint *)(iVar11 + (uVar16 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar9 + (uVar1 & 0x3fc)) ^
             *(uint *)(iVar12 + (uVar18 >> 6 & 0x3fc)) ^ *(uint *)(iVar13 + (uVar17 & 0xff) * 4) ^
             puVar8[1];
    uVar17 = *(uint *)(iVar11 + (uVar17 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar9 + (uVar2 & 0x3fc)) ^
             *(uint *)(iVar12 + (uVar3 & 0x3fc)) ^ *(uint *)(iVar13 + (uVar18 & 0xff) * 4) ^
             puVar8[2];
    uVar18 = *(uint *)(iVar11 + (uVar18 >> 0x16 & 0x3fc)) ^ *(uint *)(iVar9 + (uVar4 & 0x3fc)) ^
             *(uint *)(iVar12 + (uVar5 & 0x3fc)) ^ *(uint *)(iVar13 + uVar6 * 4) ^ puVar8[3];
    lVar19 = lVar19 + -1;
    puVar7 = puVar8 + -4;
  } while (lVar19 != 0);
  iVar9 = in_r2 + 0x13bf8;
  param_3[3] = puVar8[-1] ^
               CONCAT13(*(undefined *)(iVar9 + (uVar18 >> 0x18)),
                        CONCAT12(*(undefined *)(iVar9 + (uVar17 >> 0x10 & 0xff)),
                                 CONCAT11(*(undefined *)(iVar9 + (uVar16 >> 8 & 0xff)),
                                          *(undefined *)(iVar9 + (uVar15 & 0xff)))));
  param_3[2] = puVar8[-2] ^
               CONCAT13(*(undefined *)(iVar9 + (uVar17 >> 0x18)),
                        CONCAT12(*(undefined *)(iVar9 + (uVar16 >> 0x10 & 0xff)),
                                 CONCAT11(*(undefined *)(iVar9 + (uVar15 >> 8 & 0xff)),
                                          *(undefined *)(iVar9 + (uVar18 & 0xff)))));
  param_3[1] = puVar8[-3] ^
               CONCAT13(*(undefined *)(iVar9 + (uVar16 >> 0x18)),
                        CONCAT12(*(undefined *)(iVar9 + (uVar15 >> 0x10 & 0xff)),
                                 CONCAT11(*(undefined *)(iVar9 + (uVar18 >> 8 & 0xff)),
                                          *(undefined *)(iVar9 + (uVar17 & 0xff)))));
  *param_3 = puVar8[-4] ^
             CONCAT13(*(undefined *)(iVar9 + (uVar15 >> 0x18)),
                      CONCAT12(*(undefined *)(iVar9 + (uVar18 >> 0x10 & 0xff)),
                               CONCAT11(*(undefined *)(iVar9 + (uVar17 >> 8 & 0xff)),
                                        *(undefined *)(iVar9 + (uVar16 & 0xff)))));
  return;
}



void XeCryptAesCbc(undefined8 param_1,longlong param_2,undefined8 param_3,longlong param_4,
                  ulonglong *param_5,int param_6)

{
  longlong in_r2;
  undefined8 uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  uint uVar4;
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
        uVar3 = *(ulonglong *)param_2;
        uVar2 = ((ulonglong *)param_2)[1];
        FUN_00024274(uVar1,&local_60,&local_50,in_r2 + 0x12bf8);
        uVar4 = uVar4 - 1;
        param_2 = param_2 + 0x10;
        *(ulonglong *)param_4 = local_50 ^ local_70;
        ((ulonglong *)param_4)[1] = local_48 ^ local_68;
        param_4 = param_4 + 0x10;
        local_70 = uVar3;
        local_68 = uVar2;
      } while (uVar4 != 0);
    }
  }
  else {
    if (uVar4 != 0) {
      do {
        uVar3 = *(ulonglong *)param_2 ^ uVar3;
        uVar2 = ((ulonglong *)param_2)[1] ^ uVar2;
        FUN_0002402c(uVar1,&local_70,&local_70,ZEXT48(&UNK_00011bf8) + in_r2);
        uVar4 = uVar4 - 1;
        param_2 = param_2 + 0x10;
        *(ulonglong *)param_4 = uVar3;
        ((ulonglong *)param_4)[1] = uVar2;
        param_4 = param_4 + 0x10;
      } while (uVar4 != 0);
    }
  }
  *param_5 = uVar3;
  param_5[1] = uVar2;
  return;
}



void XeCryptAesCtr(undefined8 param_1,longlong param_2,undefined8 param_3,longlong param_4,
                  undefined8 param_5)

{
  bool bVar1;
  char cVar2;
  longlong in_r2;
  undefined8 uVar3;
  int iVar4;
  uint uVar5;
  qword local_50;
  qword local_48;
  
  uVar5 = (uint)param_3;
  uVar3 = __Save_R12_26_thru_31();
  uVar5 = uVar5 >> 4;
  if (uVar5 != 0) {
    do {
      FUN_0002402c(uVar3,param_5,&local_50,ZEXT48(&UNK_00011bf8) + in_r2);
      *(ulonglong *)param_4 = *(ulonglong *)param_2 ^ local_50;
      ((ulonglong *)param_4)[1] = ((ulonglong *)param_2)[1] ^ local_48;
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



void XeCryptAesCbcMac(undefined8 param_1,longlong param_2,undefined8 param_3,ulonglong *param_4)

{
  longlong in_r2;
  ulonglong *puVar1;
  uint uVar2;
  qword local_1b0;
  qword local_1a8;
  qword local_1a0;
  qword local_198;
  word local_190;
  
  uVar2 = (uint)param_3;
  puVar1 = (ulonglong *)__Save_R12_27_thru_31();
  local_1b0 = *puVar1;
  uVar2 = uVar2 >> 4;
  local_1a8 = puVar1[1];
  if (uVar2 != 0) {
    do {
      XeCryptAesEncrypt(&local_190,param_2,in_r2 + 0x13cf8);
      FUN_0002402c(&local_190,&local_1b0,&local_1a0,ZEXT48(&UNK_00011bf8) + in_r2);
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
               (undefined8 param_1,ulonglong param_2,longlong param_3,ulonglong param_4)

{
  longlong in_r2;
  int iVar1;
  undefined8 uVar2;
  longlong lVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = __Save_R12_28_thru_31();
  memset(param_3,0xff,param_4 & 0xffffffff);
  if ((param_4 - 0x27 & 0xffffffff) < 0x1da) {
    *(undefined *)((int)param_4 + -1 + (int)param_3) = 0;
    *(undefined *)((int)param_4 + -2 + (int)param_3) = 1;
    lVar3 = param_3;
    iVar4 = 0x13;
    do {
      iVar5 = iVar4 + -1;
      *(undefined *)lVar3 = *(undefined *)(iVar4 + iVar1);
      lVar3 = lVar3 + 1;
      iVar4 = iVar5;
    } while (-1 < iVar5);
    if ((param_2 & 0xffffffff) == 0) {
      uVar2 = 0x10;
      in_r2 = in_r2 + 0x14e08;
    }
    else {
      if ((param_2 & 0xffffffff) != 1) {
        *(undefined *)(param_3 + 0x14) = 0;
        return;
      }
      uVar2 = 0xe;
      in_r2 = in_r2 + 0x14e18;
    }
    memcpy(param_3 + 0x14,in_r2,uVar2);
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 XeCryptBnDwLePkcs1Verify(undefined8 param_1,int param_2,longlong param_3)

{
  uint uVar1;
  int in_r2;
  int iVar2;
  longlong lVar3;
  undefined8 uVar4;
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
      lVar3 = ((ulonglong)((uint)uVar4 >> 5 & 1) ^ 1) + 1;
    }
    XeCryptBnDwLePkcs1Format(param_1,lVar3,&local_220,param_3);
    iVar2 = XeCryptMemDiff(param_2,&local_220,param_3);
    if (iVar2 == 0) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 1;
    }
  }
  HvpReleaseSpinLock((ulonglong)uVar1);
  return 0;
}



void XeCryptBnDw_Copy(undefined4 *param_1,undefined4 *param_2,longlong param_3)

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



void XeCryptBnDw_SwapLeBe(uint *param_1,int param_2,longlong param_3)

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



void XeCryptBnQwBeSigFormat(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
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
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



ulonglong XeCryptBnQwBeSigVerify(void)

{
  undefined4 uVar2;
  ulonglong uVar1;
  int *in_r6;
  undefined8 uVar3;
  word local_210;
  word local_110;
  qword local_8;
  
  if ((*in_r6 == 0x20) &&
     (((byte *)in_r6[1] == (byte *)0x3 || ((byte *)in_r6[1] == &BYTE_00010001)))) {
    FUN_000244c0();
    uVar2 = XeCryptMemDiff(&local_110,&local_210,0x100);
    uVar3 = countLeadingZeros(uVar2);
    uVar1 = (ulonglong)((uint)uVar3 >> 5 & 1);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



void FUN_000206f0(undefined8 param_1,ulonglong param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint *puVar6;
  ulonglong uVar4;
  longlong lVar5;
  int iVar7;
  longlong lVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  ulonglong uVar14;
  ulonglong uVar15;
  
  puVar6 = (uint *)__Save_R12_23_thru_31();
  uVar4 = 0;
  uVar1 = *puVar6;
  uVar15 = (ulonglong)uVar1;
  uVar12 = *(undefined8 *)(puVar6 + 4);
  uVar11 = *(undefined8 *)(puVar6 + 6);
  uVar13 = *(undefined8 *)(puVar6 + 2);
  uVar14 = (uVar15 - 2) * 8 + param_2;
  if (param_2 <= uVar14) {
    do {
      uVar10 = *(ulonglong *)((uVar1 + 1) * 8 + (int)uVar14);
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
  uVar14 = *(ulonglong *)(iVar2 + iVar3);
  *(longlong *)(iVar2 + iVar3) = uVar14 - uVar4;
  if (uVar14 < uVar4) {
    do {
      lVar5 = FUN_00024ae0(lVar8,lVar8,uVar13,uVar15);
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
  lVar8 = *(longlong *)(iVar2 + iVar3) - lVar8;
  *(longlong *)(iVar2 + iVar3) = lVar8;
  while (lVar8 != 0) {
    lVar8 = FUN_00024ae0(param_2,param_2,uVar13,uVar15);
    lVar8 = lVar8 + *(longlong *)(iVar2 + iVar3);
    *(longlong *)(iVar2 + iVar3) = lVar8;
  }
  XeCryptBnQw_Copy(param_2,param_3,uVar15);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00020860(uint *param_1,undefined8 param_2,undefined8 param_3)

{
  qword local_18;
  qword local_10;
  qword local_8;
  
  FUN_000246b0(*(undefined8 *)(param_1 + 8),param_3,(ulonglong)*param_1);
  FUN_000206f0(param_1,*(undefined8 *)(param_1 + 8),param_2);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_000208b8(uint *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  qword local_18;
  qword local_10;
  qword local_8;
  
  FUN_00024600(*(undefined8 *)(param_1 + 8),param_3,param_4,(ulonglong)*param_1);
  FUN_000206f0(param_1,*(undefined8 *)(param_1 + 8),param_2);
  return;
}



undefined8
XeCryptBnQwNeModExp(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                   longlong param_5)

{
  int iVar1;
  bool bVar2;
  undefined8 *puVar5;
  longlong lVar3;
  longlong lVar4;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar11;
  ulonglong uVar10;
  uint uVar12;
  undefined8 uVar13;
  ulonglong uVar14;
  uint uVar15;
  ulonglong uVar16;
  int iVar17;
  longlong lVar18;
  ulonglong uVar19;
  longlong lVar20;
  ulonglong uVar21;
  int iVar22;
  int iVar23;
  dword local_c0;
  qword local_b8;
  qword local_b0;
  qword local_a8;
  qword local_a0;
  
  puVar5 = (undefined8 *)__Save_R12_14_thru_31();
  uVar13 = 0;
  lVar3 = FUN_00024578(param_4,param_5);
  iVar23 = (int)lVar3;
  if ((iVar23 != 0) &&
     (iVar7 = (int)((longlong)(iVar23 + -1) << 3), *(longlong *)(iVar7 + (int)param_4) != 0)) {
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
        while ((*(ulonglong *)(iVar7 + iVar8) & 0x8000000000000000) == 0) {
          FUN_00024ae0(iVar8,iVar1 + iVar6,iVar1 + iVar6,lVar3);
        }
        XeCryptBnQw_Zero(iVar11,lVar3 + 1);
        *(undefined8 *)((int)((longlong)(int)(lVar3 + 1) << 3) + iVar11) = 1;
        iVar7 = FUN_00024870(iVar11,param_4,iVar9,lVar3 + 2,lVar3);
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
              uVar21 = (ulonglong)(uint)((int)uVar21 << 1);
              if ((*(ulonglong *)(((uint)(uVar14 >> 3) & 0xfffffff8) + (int)param_3) & uVar16) != 0)
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
                  uVar21 = (ulonglong)(uint)(iVar22 >> 1) +
                           (ulonglong)(iVar22 < 0 && (uVar21 & 1) != 0);
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
          iVar7 = FUN_00024870(iVar6,param_4,puVar5,lVar3,lVar3);
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
          undefined8 param_5,undefined8 param_6,undefined8 param_7,ulonglong param_8)

{
  ulonglong uVar1;
  undefined8 uVar2;
  int iVar4;
  longlong lVar3;
  undefined8 uVar5;
  ulonglong uVar6;
  word local_460;
  word local_360;
  word local_260;
  
  uVar1 = ZEXT48(register0x0000000c);
  uVar2 = __Save_R12_22_thru_31();
  uVar5 = 0;
  if ((param_8 & 0xffffffff) < 0x21) {
    uVar6 = (ulonglong)(uint)((int)param_8 << 1);
    iVar4 = FUN_00024870(param_2,param_3,uVar1 - 0x460,uVar6,param_8);
    if ((((iVar4 != 0) &&
         (iVar4 = XeCryptBnQwNeModExp(uVar1 - 0x360,uVar1 - 0x460,param_5,param_3,param_8),
         iVar4 != 0)) &&
        (iVar4 = FUN_00024870(param_2,param_4,uVar1 - 0x460,uVar6,param_8), iVar4 != 0)) &&
       (iVar4 = XeCryptBnQwNeModExp(uVar1 - 0x260,uVar1 - 0x460,param_6,param_4,param_8), iVar4 != 0
       )) {
      lVar3 = FUN_00024b38(uVar1 - 0x460,uVar1 - 0x360,uVar1 - 0x260,param_8);
      if (lVar3 != 0) {
        do {
          lVar3 = FUN_00024ae0(uVar1 - 0x460,uVar1 - 0x460,param_3,param_8);
        } while (lVar3 == 0);
      }
      FUN_00024600(uVar2,uVar1 - 0x460,param_7,param_8);
      iVar4 = FUN_00024870(uVar2,param_3,uVar1 - 0x460,uVar6,param_8);
      if (iVar4 != 0) {
        FUN_00024600(uVar2,uVar1 - 0x460,param_4,param_8);
        XeCryptBnQw_Zero((param_8 & 0xffffffff) * 8 + (uVar1 - 0x260),param_8);
        FUN_00024ae0(uVar2,uVar2,uVar1 - 0x260,uVar6);
        uVar5 = 1;
      }
    }
  }
  XeCryptBnQw_Zero(uVar1 - 0x360,0x20);
  XeCryptBnQw_Zero(uVar1 - 0x260,0x40);
  XeCryptBnQw_Zero(uVar1 - 0x460,0x20);
  return uVar5;
}



longlong XeCryptBnQwNeModInv(longlong param_1)

{
  longlong lVar1;
  uint uVar2;
  ulonglong uVar3;
  longlong lVar4;
  
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

void XeCryptBnQwNeModMul(longlong *param_1,ulonglong *param_2,ulonglong *param_3,longlong param_4,
                        ulonglong *param_5,int param_6)

{
  bool bVar1;
  ulonglong *puVar2;
  ulonglong *puVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  undefined8 *puVar7;
  ulonglong uVar6;
  ulonglong uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  int iVar11;
  longlong lVar12;
  int iVar13;
  int iVar14;
  word local_260;
  word local_258;
  longlong local_150;
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
    puVar3 = (ulonglong *)&local_258;
    iVar14 = param_6;
    do {
      puVar2 = puVar3;
      uVar9 = SUB168(ZEXT816(uVar4) * ZEXT816(*(ulonglong *)((int)param_1 + iVar11)) >> 0x40,0);
      uVar10 = uVar4 * *(ulonglong *)((int)param_1 + iVar11) + *puVar2;
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
      uVar9 = SUB168(ZEXT816(uVar5) * ZEXT816(*(ulonglong *)((int)param_5 + iVar11)) >> 0x40,0);
      uVar10 = uVar5 * *(ulonglong *)((int)param_5 + iVar11) + puVar2[0x21];
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
  puVar3 = (ulonglong *)(&local_260 + param_6 * 4);
  iVar13 = param_6;
  do {
    if (*puVar3 < puVar3[0x21]) {
      puVar3 = (ulonglong *)&local_258;
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
  puVar3 = (ulonglong *)&local_258;
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



undefined8 XeCryptBnQwNeRsaPubCrypt(undefined8 param_1,undefined8 param_2,longlong param_3)

{
  undefined8 uVar1;
  int iVar2;
  ulonglong uVar3;
  qword local_230;
  
  uVar1 = __Save_R12_27_thru_31();
  uVar3 = (ulonglong)*(uint *)param_3;
  if (((uVar3 - 1 & 0xffffffff) < 0x40) &&
     (iVar2 = FUN_00024d08(uVar1,param_3 + 0x10,uVar3), iVar2 < 0)) {
    XeCryptBnQw_Zero(&local_230,uVar3);
    uVar1 = XeCryptBnQwNeModExp(param_2,uVar1,&local_230,param_3 + 0x10,uVar3);
    return uVar1;
  }
  return 0;
}



undefined8 XeCryptBnQwNeRsaPrvCrypt(undefined8 param_1,undefined8 param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  ulonglong uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  
  uVar1 = ZEXT48(register0x0000000c);
  uVar8 = (ulonglong)(*(uint *)param_3 >> 1);
  lVar7 = uVar8 * 8;
  param_3 = ((ulonglong)(*(uint *)param_3 & 0xfffffffe) + 2) * 8 + param_3;
  lVar4 = lVar7 + param_3;
  lVar5 = lVar7 + lVar4;
  lVar6 = lVar7 + lVar5;
  lVar7 = lVar7 + lVar6;
  uVar2 = __Save_R12_22_thru_31(param_2,param_1,param_3,lVar4,lVar5,lVar6,lVar7);
  uVar9 = 0;
  if ((uVar8 & 0xffffffff) < 0x21) {
    uVar10 = (ulonglong)(uint)((int)uVar8 << 1);
    iVar3 = FUN_00024870(param_1,param_3,uVar1 - 0x460,uVar10,uVar8);
    if ((((iVar3 != 0) &&
         (iVar3 = XeCryptBnQwNeModExp(uVar1 - 0x360,uVar1 - 0x460,lVar5,param_3,uVar8), iVar3 != 0))
        && (iVar3 = FUN_00024870(param_1,lVar4,uVar1 - 0x460,uVar10,uVar8), iVar3 != 0)) &&
       (iVar3 = XeCryptBnQwNeModExp(uVar1 - 0x260,uVar1 - 0x460,lVar6,lVar4,uVar8), iVar3 != 0)) {
      lVar5 = FUN_00024b38(uVar1 - 0x460,uVar1 - 0x360,uVar1 - 0x260,uVar8);
      if (lVar5 != 0) {
        do {
          lVar5 = FUN_00024ae0(uVar1 - 0x460,uVar1 - 0x460,param_3,uVar8);
        } while (lVar5 == 0);
      }
      FUN_00024600(uVar2,uVar1 - 0x460,lVar7,uVar8);
      iVar3 = FUN_00024870(uVar2,param_3,uVar1 - 0x460,uVar10,uVar8);
      if (iVar3 != 0) {
        FUN_00024600(uVar2,uVar1 - 0x460,lVar4,uVar8);
        XeCryptBnQw_Zero((uVar8 & 0xffffffff) * 8 + (uVar1 - 0x260),uVar8);
        FUN_00024ae0(uVar2,uVar2,uVar1 - 0x260,uVar10);
        uVar9 = 1;
      }
    }
  }
  XeCryptBnQw_Zero(uVar1 - 0x360,0x20);
  XeCryptBnQw_Zero(uVar1 - 0x260,0x40);
  XeCryptBnQw_Zero(uVar1 - 0x460,0x20);
  return uVar9;
}



void XeCryptBnQw_Zero(undefined8 *param_1,longlong param_2)

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



void XeCryptBnQw_Copy(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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



void XeCryptBnQw_SwapDwQwLeBe(undefined8 *param_1,int param_2,longlong param_3)

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
    uVar2 = (uint)((ulonglong)uVar1 >> 0x20);
    *(uint *)((int)param_1 + param_2 + 4) =
         uVar2 << 0x18 | (uVar2 & 0xff00) << 8 | uVar2 >> 8 & 0xff00 | uVar2 >> 0x18;
    param_1 = param_1 + 1;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  return;
}



void XeCryptDesEcb(undefined8 param_1,byte *param_2,uint *param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  int in_r2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  ulonglong uVar6;
  uint uVar8;
  longlong lVar7;
  int iVar9;
  ulonglong uVar10;
  uint uVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  uint *puVar14;
  
  puVar3 = (uint *)__Save_R12_16_thru_31();
  iVar4 = 8;
  uVar13 = (ulonglong)param_2[7] << 0x18 | (ulonglong)param_2[6] << 0x10 |
           (ulonglong)param_2[5] << 8 | (ulonglong)param_2[4];
  uVar12 = (ulonglong)
           (((uint)param_2[3] << 0x18 | (uint)param_2[2] << 0x10 | (uint)param_2[1] << 8 |
            (uint)*param_2) << 4 | ((uint)param_2[3] << 0x18) >> 0x1c);
  uVar10 = (uVar13 ^ uVar12) & 0xfffffffff0f0f0f0;
  uVar8 = (uint)uVar13 ^ (uint)uVar10;
  uVar12 = uVar12 ^ uVar10;
  uVar8 = uVar8 << 0x14 | uVar8 >> 0xc;
  uVar5 = ((uint)uVar12 ^ uVar8) & 0xfff0000f;
  uVar8 = uVar5 ^ uVar8;
  uVar12 = uVar5 ^ uVar12;
  uVar13 = (ulonglong)(uVar8 << 0xe | uVar8 >> 0x12);
  uVar10 = (uVar13 ^ uVar12) & 0x33333333;
  uVar8 = (uint)uVar12 ^ (uint)uVar10;
  uVar13 = uVar13 ^ uVar10;
  uVar8 = uVar8 << 0x16 | uVar8 >> 10;
  uVar5 = (uVar8 ^ (uint)uVar13) & 0x3fc03fc;
  uVar8 = uVar5 ^ uVar8;
  uVar13 = uVar5 ^ uVar13;
  uVar12 = (ulonglong)(uVar8 << 9 | uVar8 >> 0x17);
  uVar10 = (uVar13 ^ uVar12) & 0xffffffffaaaaaaaa;
  uVar8 = (uint)uVar13 ^ (uint)uVar10;
  uVar12 = uVar12 ^ uVar10;
  uVar10 = (ulonglong)(uVar8 << 1 | uVar8 >> 0x1f);
  iVar1 = in_r2 + 0x14e28;
  if (param_4 == 0) {
    iVar9 = 0x1c;
    puVar14 = puVar3 + 0x1e;
    do {
      uVar6 = *puVar14 ^ uVar12;
      uVar5 = *(uint *)((int)((longlong)(iVar9 + 3) << 2) + (int)puVar3) ^ (uint)uVar12;
      uVar8 = uVar5 >> 4;
      uVar13 = (ulonglong)(uVar5 << 0x1c | uVar8);
      uVar10 = (*(uint *)(((uint)(uVar6 >> 0x18) & 0xfc) + in_r2 + 0x15428) ^
                *(uint *)(((uint)(uVar6 >> 0x10) & 0xfc) + in_r2 + 0x15228) ^
                *(uint *)(((uint)(uVar6 >> 8) & 0xfc) + in_r2 + 0x15028) ^
                *(uint *)(((uint)(uVar13 >> 0x18) & 0xfc) + in_r2 + 0x15528) ^
                *(uint *)(((uint)(uVar13 >> 0x10) & 0xfc) + in_r2 + 0x15328) ^
                *(uint *)(((uint)(uVar13 >> 8) & 0xfc) + in_r2 + 0x15128) ^
                *(uint *)(((uint)uVar6 & 0xfc) + iVar1) ^
               *(uint *)((uVar8 & 0xfc) + in_r2 + 0x14f28)) ^ uVar10;
      uVar6 = *(uint *)((int)((longlong)iVar9 << 2) + (int)puVar3) ^ uVar10;
      uVar5 = (uint)uVar10;
      uVar11 = *(uint *)((int)((longlong)(iVar9 + 1) << 2) + (int)puVar3) ^ uVar5;
      uVar8 = uVar11 >> 4;
      uVar13 = (ulonglong)(uVar11 << 0x1c | uVar8);
      iVar4 = iVar4 + -1;
      puVar14 = puVar14 + -4;
      iVar9 = iVar9 + -4;
      uVar12 = (*(uint *)(((uint)(uVar6 >> 0x18) & 0xfc) + in_r2 + 0x15428) ^
                *(uint *)(((uint)(uVar6 >> 0x10) & 0xfc) + in_r2 + 0x15228) ^
                *(uint *)(((uint)(uVar6 >> 8) & 0xfc) + in_r2 + 0x15028) ^
                *(uint *)(((uint)(uVar13 >> 0x18) & 0xfc) + in_r2 + 0x15528) ^
                *(uint *)(((uint)(uVar13 >> 0x10) & 0xfc) + in_r2 + 0x15328) ^
                *(uint *)(((uint)(uVar13 >> 8) & 0xfc) + in_r2 + 0x15128) ^
                *(uint *)(((uint)uVar6 & 0xfc) + iVar1) ^
               *(uint *)((uVar8 & 0xfc) + in_r2 + 0x14f28)) ^ uVar12;
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
      uVar13 = (ulonglong)(uVar5 << 0x1c | uVar8);
      uVar10 = (*(uint *)(((uint)(uVar6 >> 0x18) & 0xfc) + in_r2 + 0x15428) ^
                *(uint *)(((uint)(uVar6 >> 0x10) & 0xfc) + in_r2 + 0x15228) ^
                *(uint *)(((uint)(uVar6 >> 8) & 0xfc) + in_r2 + 0x15028) ^
                *(uint *)(((uint)(uVar13 >> 0x18) & 0xfc) + in_r2 + 0x15528) ^
                *(uint *)(((uint)(uVar13 >> 0x10) & 0xfc) + in_r2 + 0x15328) ^
                *(uint *)(((uint)(uVar13 >> 8) & 0xfc) + in_r2 + 0x15128) ^
                *(uint *)(((uint)uVar6 & 0xfc) + iVar1) ^
               *(uint *)((uVar8 & 0xfc) + in_r2 + 0x14f28)) ^ uVar10;
      uVar6 = *(uint *)((int)(lVar7 << 2) + (int)puVar3) ^ uVar10;
      uVar5 = (uint)uVar10;
      uVar8 = (puVar3[(int)lVar7 + 1] ^ uVar5) >> 4;
      uVar13 = (ulonglong)((puVar3[(int)lVar7 + 1] ^ uVar5) << 0x1c | uVar8);
      iVar4 = iVar4 + -1;
      puVar14 = puVar14 + 4;
      lVar7 = lVar7 + 4;
      uVar12 = (*(uint *)(((uint)(uVar6 >> 0x18) & 0xfc) + in_r2 + 0x15428) ^
                *(uint *)(((uint)(uVar6 >> 0x10) & 0xfc) + in_r2 + 0x15228) ^
                *(uint *)(((uint)(uVar6 >> 8) & 0xfc) + in_r2 + 0x15028) ^
                *(uint *)(((uint)(uVar13 >> 0x18) & 0xfc) + in_r2 + 0x15528) ^
                *(uint *)(((uint)(uVar13 >> 0x10) & 0xfc) + in_r2 + 0x15328) ^
                *(uint *)(((uint)(uVar13 >> 8) & 0xfc) + in_r2 + 0x15128) ^
                *(uint *)(((uint)uVar6 & 0xfc) + iVar1) ^
               *(uint *)((uVar8 & 0xfc) + in_r2 + 0x14f28)) ^ uVar12;
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



void XeCryptDesCbc(undefined8 param_1,longlong param_2,undefined8 param_3,longlong param_4,
                  ulonglong *param_5,int param_6)

{
  undefined8 uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  uint uVar4;
  qword local_50;
  qword local_48;
  
  uVar4 = (uint)param_3;
  uVar1 = __Save_R12_26_thru_31();
  uVar4 = uVar4 >> 3;
  uVar3 = *param_5;
  if (param_6 == 0) {
    while (uVar4 != 0) {
      uVar2 = *(ulonglong *)param_2;
      uVar1 = XeCryptDesEcb(uVar1,&local_50,&local_48,0);
      uVar4 = uVar4 - 1;
      param_2 = param_2 + 8;
      *(ulonglong *)param_4 = local_48 ^ uVar3;
      param_4 = param_4 + 8;
      uVar3 = uVar2;
    }
  }
  else {
    while (uVar4 != 0) {
      uVar3 = *(ulonglong *)param_2 ^ uVar3;
      uVar1 = XeCryptDesEcb(uVar1,&local_50,&local_50,1);
      uVar4 = uVar4 - 1;
      param_2 = param_2 + 8;
      *(ulonglong *)param_4 = uVar3;
      param_4 = param_4 + 8;
    }
  }
  *param_5 = uVar3;
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void XeCryptDes3Ecb(longlong param_1,undefined8 param_2,undefined8 param_3,int param_4)

{
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



void XeCryptDes3Cbc(undefined8 param_1,longlong param_2,undefined8 param_3,longlong param_4,
                   ulonglong *param_5,int param_6)

{
  longlong lVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  uint uVar4;
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
        uVar2 = *(ulonglong *)param_2;
        XeCryptDesEcb(lVar1 + 0x100,&local_58,&local_60,0);
        XeCryptDesEcb(lVar1 + 0x80,&local_60,&local_60,1);
        XeCryptDesEcb(lVar1,&local_60,&local_60,0);
        uVar4 = uVar4 - 1;
        param_2 = param_2 + 8;
        *(ulonglong *)param_4 = local_60 ^ uVar3;
        param_4 = param_4 + 8;
        uVar3 = uVar2;
      } while (uVar4 != 0);
    }
  }
  else {
    if (uVar4 != 0) {
      do {
        uVar2 = *(ulonglong *)param_2 ^ uVar2;
        XeCryptDesEcb(lVar1,&local_60,&local_60,1);
        XeCryptDesEcb(lVar1 + 0x80,&local_60,&local_60,0);
        XeCryptDesEcb(lVar1 + 0x100,&local_60,&local_60,1);
        uVar4 = uVar4 - 1;
        param_2 = param_2 + 8;
        *(ulonglong *)param_4 = uVar2;
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
  longlong in_r2;
  longlong lVar4;
  int iVar5;
  uint *puVar6;
  ulonglong uVar7;
  uint uVar8;
  ulonglong uVar9;
  uint uVar10;
  uint uVar11;
  uint *puVar12;
  ulonglong uVar13;
  uint uVar14;
  
  puVar6 = (uint *)__Save_R12_17_thru_31();
  lVar4 = in_r2 + 0x15e28;
  uVar13 = (ulonglong)param_2[3] << 0x18 | (ulonglong)param_2[2] << 0x10 |
           (ulonglong)param_2[1] << 8 | (ulonglong)*param_2;
  uVar9 = (ulonglong)param_2[7] << 0x18 | (ulonglong)param_2[6] << 0x10 | (ulonglong)param_2[5] << 8
          | (ulonglong)param_2[4];
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
    uVar14 = *(uint *)(((((uVar14 & 0xfffffff | uVar1 & 0xe000000) >> 1 | uVar1 & 0xc00000) >> 1 |
                        uVar1 & 0x100000) >> 0x12) + iVar3 + 0x15928) |
             *(uint *)((((uVar1 & 0x1e00) >> 1 | uVar1 & 0xc0) >> 4) + iVar3 + 0x15728) |
             *(uint *)((((uVar1 & 0xc0000) >> 1 | uVar1 & 0x1e000) >> 0xb) + iVar3 + 0x15828) |
             *(uint *)((uVar1 & 0x3f) * 4 + iVar3 + 0x15628);
    uVar11 = *(uint *)((((uVar11 & 0xfffffff | uVar2 & 0xc000000) >> 1 | uVar2 & 0x1e00000) >> 0x13)
                      + iVar3 + 0x15d28) |
             *(uint *)((((uVar2 & 0x3c00) >> 1 | uVar2 & 0x180) >> 5) + iVar3 + 0x15b28) |
             *(uint *)(((uVar2 & 0x1f8000) >> 0xd) + iVar3 + 0x15c28) |
             *(uint *)((uVar2 & 0x3f) * 4 + iVar3 + 0x15a28);
    puVar12 = puVar6 + 1;
    *puVar6 = (uVar11 << 0x10 | uVar14 & 0xffff) << 2 | (uVar11 << 0x10) >> 0x1e;
    puVar6 = puVar6 + 2;
    *puVar12 = (uVar14 >> 0x10 | uVar11 & 0xffff0000) << 6 | uVar11 >> 0x1a;
  } while (iVar5 != 0);
  return;
}



void XeCryptDes3Key(undefined8 param_1,longlong param_2)

{
  longlong lVar1;
  int iVar2;
  
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
    iVar2 = (uint)*(byte *)((uint)(bVar1 >> 4) + in_r2 + 0x15e38) +
            (uint)*(byte *)(((uint)bVar1 & 0xf) + in_r2 + 0x15e38);
    if (iVar2 == (iVar2 >> 1) * 2) {
      bVar1 = bVar1 ^ 1;
    }
    param_2 = param_2 + -1;
    *param_3 = bVar1;
    param_3 = param_3 + 1;
  } while (param_2 != 0);
  return;
}



ulonglong FUN_00021c70(undefined8 param_1,undefined8 param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  undefined8 uVar15;
  
  uVar14 = (uint)param_2;
  uVar13 = __Save_R12_19_thru_31();
  uVar1 = uVar13 & 0xff;
  uVar2 = uVar14 & 0xff;
  uVar3 = uVar1 >> 5 & 1;
  uVar4 = uVar1 >> 4 & 1;
  uVar5 = uVar1 >> 6 & 1;
  uVar6 = uVar2 >> 1 & 1;
  uVar7 = uVar2 >> 2 & 1;
  uVar8 = uVar1 >> 1 & 1;
  uVar9 = uVar2 >> 6 & 1;
  uVar10 = uVar1 >> 2 & 1;
  uVar11 = uVar2 >> 5 & 1;
  uVar1 = uVar1 >> 3 & 1;
  uVar12 = uVar2 >> 4 & 1;
  uVar2 = uVar2 >> 3 & 1;
  uVar13 = uVar13 & 1;
  uVar14 = uVar14 & 1;
  uVar15 = countLeadingZeros(uVar13 & uVar14);
  return (ulonglong)
         ((-(uint)((uVar1 & uVar7 ^ uVar4 & uVar6 ^ uVar3 & uVar14 ^ uVar11 & uVar13 ^
                   uVar8 & uVar12) != (uVar10 & uVar2)) & 0x20 |
          -(uint)((uVar2 & uVar4 ^ uVar7 & uVar3 ^ uVar6 & uVar5 ^ uVar9 & uVar8 ^ uVar11 & uVar10)
                 != (uVar12 & uVar1)) & 3 |
          -(uint)((uVar4 & uVar7 ^ uVar3 & uVar6 ^ uVar5 & uVar14 ^ uVar9 & uVar13 ^ uVar8 & uVar11
                  ^ uVar10 & uVar12) != (uVar1 & uVar2)) & 0x40) ^
          -(uint)((uVar12 & uVar4 ^ uVar2 & uVar3 ^ uVar7 & uVar5 ^ uVar9 & uVar10) !=
                 (uVar11 & uVar1)) & 6 ^
          -(uint)((uVar10 & uVar7 ^ uVar1 & uVar6 ^ uVar4 & uVar14 ^ uVar12 & uVar13) !=
                 (uVar8 & uVar2)) & 0x10 ^
          -(uint)((uVar12 & uVar3 ^ uVar2 & uVar5 ^ uVar9 & uVar1) != (uVar11 & uVar4)) & 0xc ^
          -(uint)((uVar10 & uVar6 ^ uVar1 & uVar14 ^ uVar2 & uVar13) != (uVar8 & uVar7)) & 8 ^
          -(uint)((uVar11 & uVar3 ^ uVar12 & uVar5) != (uVar9 & uVar4)) & 0x18 ^
          -(uint)((uVar8 & uVar6 ^ uVar10 & uVar14) != (uVar7 & uVar13)) & 4 ^
          -(uint)((uVar9 & uVar3) != (uVar11 & uVar5)) & 0x30 ^
          -(uint)((uVar6 & uVar13) != (uVar8 & uVar14)) & 2 ^ -(uint)((uVar9 & uVar5) != 0) & 0x60 ^
         (uint)uVar15 >> 5 & 1 ^ 1);
}



// WARNING: Variable defined which should be unmapped: local_8

void XeCryptUidEccEncode(int param_1)

{
  byte bVar1;
  int iVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  qword local_8;
  
  uVar6 = 0;
  uVar3 = 0;
  uVar7 = 0;
  do {
    uVar5 = (ulonglong)(*(byte *)((int)(uVar7 >> 3) + param_1) >> (uVar7 & 7)) & 1;
    uVar6 = uVar5 ^ uVar6;
    if ((uVar6 & 1) != 0) {
      uVar6 = uVar6 ^ 0x360325;
    }
    uVar7 = uVar7 + 1;
    uVar6 = uVar6 >> 1;
    uVar3 = uVar5 ^ uVar3;
  } while (uVar7 < 0x6a);
  while (uVar7 < 0x7f) {
    iVar2 = (int)(uVar7 >> 3);
    uVar4 = (ulonglong)((uint)uVar7 & 7);
    uVar5 = uVar6 & 1;
    bVar1 = *(byte *)(iVar2 + param_1);
    if (((ulonglong)(bVar1 >> uVar4) & 1) != uVar5) {
      *(byte *)(iVar2 + param_1) = (byte)(1 << uVar4) ^ bVar1;
    }
    uVar7 = uVar7 + 1;
    uVar6 = uVar6 >> 1;
    uVar3 = uVar5 ^ uVar3;
  }
  uVar6 = (ulonglong)((uint)uVar7 & 7);
  iVar2 = (int)(uVar7 >> 3);
  bVar1 = *(byte *)(iVar2 + param_1);
  if (((ulonglong)(bVar1 >> uVar6) & 1) != uVar3) {
    *(byte *)(iVar2 + param_1) = (byte)(1 << uVar6) ^ bVar1;
  }
  return;
}



ulonglong XeCryptUidEccDecode(void)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  uint uVar11;
  undefined8 uVar10;
  ulonglong uVar12;
  ulonglong uVar13;
  uint uVar14;
  
  iVar4 = __Save_R12_14_thru_31();
  uVar5 = 0;
  uVar9 = 0;
  uVar13 = 0;
  uVar12 = 0;
  uVar8 = 0;
  do {
    bVar1 = *(byte *)((int)(uVar8 >> 3) + iVar4);
    uVar7 = (uint)bVar1 & 0x40;
    uVar5 = (((bVar1 >> 2 ^ uVar7) >> 2 ^ (uint)bVar1 & 0x20) >> 2 ^ (uint)bVar1 & 0x10) >> 1 ^
            ((((uint)bVar1 & 2) << 2 ^ (uint)bVar1 & 4) << 2 ^ (uint)bVar1 & 8) << 1 ^
            -(uint)((uVar5 & 0x10) != 0) & 0x60 ^ -(uint)((uVar5 & 0x20) != 0) & 0x43 ^
            -(uint)((uVar5 & 0x40) != 0) & 5 ^ -(uint)((uVar5 & 8) != 0) & 0x30 ^
            -(uint)((uVar5 & 4) != 0) & 0x18 ^ -(uint)((uVar5 & 2) != 0) & 0xc ^
            -(uint)((uVar5 & 1) != 0) & 6 ^ -(uint)((bVar1 & 1) != 0) & 3;
    uVar9 = (ulonglong)
            (-(uint)((uVar9 & 0x40) != 0) & 0x44 ^ -(uint)((uVar9 & 1) != 0) & 0x78 ^
            -(uint)((uVar9 & 2) != 0) & 0x73) ^ -(ulonglong)((uVar9 & 4) != 0) & 0x65 ^
            -(ulonglong)((uVar9 & 8) != 0) & 0x49 ^ (ulonglong)(-(uint)((uVar9 & 0x20) != 0) & 0x22)
            ^ (ulonglong)(-(uint)((uVar9 & 0x10) != 0) & 0x11) ^
            (ulonglong)((bVar1 >> 4 ^ uVar7) >> 3) ^ (ulonglong)(-(uint)((bVar1 & 4) != 0) & 10) ^
            (ulonglong)(-(uint)((bVar1 & 0x10) != 0) & 0xc) ^
            (ulonglong)(-(uint)((bVar1 & 2) != 0) & 0x50) ^
            (ulonglong)(-(uint)((bVar1 & 8) != 0) & 0x60) ^
            (ulonglong)(-(uint)((bVar1 & 1) != 0) & 0xf) ^ (ulonglong)(((uint)bVar1 & 0x20) << 1);
    uVar13 = (ulonglong)(-(uint)((uVar13 & 0x40) != 0) & 0x4e ^ -(uint)((uVar13 & 1) != 0) & 0x74) ^
             -(ulonglong)((uVar13 & 2) != 0) & 0x6b ^ -(ulonglong)((uVar13 & 0x10) != 0) & 0x52 ^
             -(ulonglong)((uVar13 & 4) != 0) & 0x55 ^
             (ulonglong)(-(uint)((uVar13 & 0x20) != 0) & 0x27) ^
             -(ulonglong)((uVar13 & 8) != 0) & 0x29 ^ (ulonglong)((bVar1 >> 6 ^ uVar7) >> 1) ^
             (ulonglong)(-(uint)((bVar1 & 0x20) != 0) & 0x18) ^
             (ulonglong)(-(uint)((bVar1 & 4) != 0) & 0x73) ^
             (ulonglong)(-(uint)((bVar1 & 0x10) != 0) & 10) ^
             (ulonglong)(-(uint)((bVar1 & 2) != 0) & 0x44) ^
             (ulonglong)(-(uint)((bVar1 & 8) != 0) & 0x46) ^
             (ulonglong)(-(uint)((bVar1 & 1) != 0) & 0x33);
    uVar8 = uVar8 + 8;
    uVar12 = ((((((uint)bVar1 & 0x10) >> 1 ^ (uint)bVar1 & 8) >> 1 ^ (uint)bVar1 & 4) >> 1 ^
              (uint)bVar1 & 2) >> 1 ^
             (uint)(byte)(((bVar1 >> 1 ^ bVar1) >> 1 ^ bVar1) >> 5 ^ bVar1) & 1) ^ uVar12;
  } while (uVar8 < 0x80);
  uVar7 = (uint)(bVar1 >> 7);
  uVar11 = uVar7 ^ (uint)uVar13;
  uVar6 = uVar7 ^ (uint)uVar9;
  uVar7 = uVar7 ^ uVar5;
  uVar8 = (ulonglong)uVar7;
  if (((uint)uVar12 | uVar11 | uVar6 | uVar7) == 0) {
    return 0;
  }
  uVar9 = (ulonglong)
          ((((uVar7 & 8) << 1 | uVar7 & 4) << 1 ^ uVar7 & 2) << 1 ^
           -(uint)((uVar7 & 0x40) != 0) & 0x60 ^ -(uint)((uVar7 & 0x20) != 0) & 0x18 ^
           -(uint)((uVar7 & 0x10) != 0) & 6 ^ uVar7 & 1);
  uVar5 = FUN_00021c70(uVar8,uVar9);
  uVar5 = uVar5 & 0xff ^ uVar6;
  uVar13 = (ulonglong)uVar5;
  uVar6 = FUN_00021c70((ulonglong)uVar6,uVar9);
  uVar11 = uVar6 & 0xff ^ uVar11;
  uVar9 = (ulonglong)uVar11;
  if (uVar5 == 0) {
    if (uVar11 == 0) {
      uVar10 = countLeadingZeros(uVar7);
      uVar13 = 1;
      uVar5 = 0;
      uVar8 = (ulonglong)((uint)uVar10 >> 5 & 1) ^ 1;
      goto LAB_000225bc;
    }
LAB_0002259c:
    uVar9 = 0xffffffffffffffff;
  }
  else {
    uVar7 = FUN_00021c70(uVar8,uVar13);
    uVar6 = FUN_00021c70(uVar8,uVar9);
    uVar5 = (((uVar5 & 8) << 1 | uVar5 & 4) << 1 ^ uVar5 & 2) << 1 ^
            -(uint)((uVar5 & 0x40) != 0) & 0x60 ^ -(uint)((uVar5 & 0x20) != 0) & 0x18 ^
            -(uint)((uVar5 & 0x10) != 0) & 6 ^ uVar5 & 1 ^ uVar6 & 0xff;
    uVar10 = countLeadingZeros(uVar5);
    uVar8 = ((ulonglong)((uint)uVar10 >> 5 & 1) ^ 1) + 2;
LAB_000225bc:
    uVar6 = (uint)uVar8;
    if ((uVar8 & 1) != uVar12) {
      if (uVar8 == 3) goto LAB_0002259c;
      uVar6 = uVar6 + 1;
      *(byte *)(iVar4 + 0xf) = *(byte *)(iVar4 + 0xf) ^ 0x80;
    }
    uVar12 = 0x7f;
    do {
      uVar14 = (uint)uVar9;
      uVar11 = (int)uVar13 << 1;
      uVar2 = uVar11 & 0xfe;
      uVar13 = (ulonglong)uVar2;
      if ((uVar11 & 0x80) != 0) {
        uVar13 = (ulonglong)uVar2 ^ 0x83;
      }
      if ((uVar9 & 1) != 0) {
        uVar14 = uVar14 ^ 0x83;
      }
      uVar9 = (ulonglong)(uVar14 >> 1);
      if ((uVar5 & 1) != 0) {
        uVar5 = uVar5 ^ 0x83;
      }
      uVar11 = uVar5 >> 1;
      if ((uVar11 & 1) != 0) {
        uVar11 = uVar11 ^ 0x83;
      }
      uVar5 = uVar11 >> 1;
      uVar12 = uVar12 - 1;
      if (((uVar11 ^ uVar14) >> 1 ^ (uint)uVar13) == (uVar7 & 0xff)) {
        iVar3 = (int)(uVar12 >> 3);
        uVar8 = uVar8 - 1;
        *(byte *)(iVar3 + iVar4) =
             (byte)(1 << (ulonglong)((uint)uVar12 & 7)) ^ *(byte *)(iVar3 + iVar4);
      }
    } while (uVar12 != 0);
    uVar9 = 0xffffffffffffffff;
    if (uVar8 == 0) {
      uVar9 = (ulonglong)uVar6;
    }
  }
  return uVar9;
}



ulonglong XeCryptHammingWeight(ulonglong param_1)

{
  ulonglong uVar1;
  ulonglong uVar2;
  
  uVar2 = 0;
  while (param_1 != 0) {
    uVar1 = param_1 & 1;
    param_1 = param_1 >> 1;
    uVar2 = uVar1 + uVar2;
  }
  return uVar2 & 0xffffffff;
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
  longlong lVar3;
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
    lVar3 = (longlong)iVar14;
    iVar11 = iVar11 + -1;
    iVar14 = iVar14 + 1;
    uVar8 = *(uint *)((int)&local_190 + (int)((longlong)iVar7 << 2)) ^
            *(uint *)((int)&local_190 + (int)((longlong)iVar6 << 2)) ^
            *(uint *)((int)&local_190 + (int)((longlong)iVar5 << 2)) ^
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



void XeCryptShaUpdate(undefined8 param_1,ulonglong param_2,ulonglong param_3)

{
  uint uVar1;
  longlong lVar2;
  uint uVar3;
  ulonglong uVar4;
  
  lVar2 = __Save_R12_25_thru_31();
  uVar3 = *(uint *)lVar2;
  uVar1 = uVar3 & 0x3f;
  uVar4 = (ulonglong)uVar1;
  *(uint *)lVar2 = uVar3 + (int)param_3;
  if ((uVar1 != 0) && (0x3f < (uVar4 + param_3 & 0xffffffff))) {
    memcpy((ulonglong)uVar1 + lVar2 + 0x18);
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



void XeCryptShaFinal(undefined8 param_1,undefined8 param_2,ulonglong param_3)

{
  uint uVar1;
  uint *puVar2;
  ulonglong uVar3;
  uint *puVar4;
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



void XeCryptSha(undefined8 param_1,ulonglong param_2,undefined8 param_3,ulonglong param_4,
               undefined8 param_5,ulonglong param_6,undefined8 param_7,undefined8 param_8)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
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
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



void XeCryptHmacShaInit(undefined8 param_1,undefined8 param_2,ulonglong param_3)

{
  uint uVar1;
  int in_r2;
  undefined4 *puVar2;
  ulonglong *puVar3;
  ulonglong *puVar4;
  int iVar5;
  int iVar6;
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
    puVar4 = (ulonglong *)((int)&local_c0 + iVar6);
    puVar3 = (ulonglong *)((int)&local_80 + iVar6);
    iVar5 = iVar5 + -1;
    iVar6 = iVar6 + 8;
    *puVar4 = *puVar4 ^ 0x3636363636363636;
    *puVar3 = *puVar3 ^ 0x5c5c5c5c5c5c5c5c;
  } while (iVar5 != 0);
  XeCryptShaUpdate(puVar2,&local_c0,0x40);
  XeCryptShaUpdate(puVar2 + 0x16,&local_80,0x40);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



void XeCryptHmacShaUpdate(undefined8 param_1,ulonglong param_2,ulonglong param_3)

{
  uint uVar1;
  longlong lVar2;
  uint uVar3;
  ulonglong uVar4;
  
  lVar2 = __Save_R12_25_thru_31();
  uVar3 = *(uint *)lVar2;
  uVar1 = uVar3 & 0x3f;
  uVar4 = (ulonglong)uVar1;
  *(uint *)lVar2 = uVar3 + (int)param_3;
  if ((uVar1 != 0) && (0x3f < (uVar4 + param_3 & 0xffffffff))) {
    memcpy((ulonglong)uVar1 + lVar2 + 0x18);
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
  longlong lVar1;
  
  lVar1 = __Save_R12_28_thru_31();
  XeCryptShaFinal(lVar1,0,0);
  XeCryptShaUpdate(lVar1 + 0x58,lVar1 + 4,0x14);
  XeCryptShaFinal(lVar1 + 0x58,param_2,param_3);
  return;
}



void XeCryptHmacSha(undefined8 param_1,undefined8 param_2,undefined8 param_3,ulonglong param_4,
                   undefined8 param_5,ulonglong param_6,undefined8 param_7,ulonglong param_8)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  undefined8 param_1_00;
  uint param_2_00;
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
  XeCryptHmacShaFinal(&local_f0,param_1_00,(ulonglong)param_2_00);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void XeCryptRc4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  uint uVar1;
  int in_r2;
  word local_120;
  dword local_1c;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)(in_r2 + 0x10000);
  XeCryptRc4Key(&local_120,param_1,param_2);
  XeCryptRc4Ecb(&local_120,param_3,param_4);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



void XeCryptRc4Key(longlong *param_1,int param_2,int param_3)

{
  byte bVar1;
  longlong *plVar2;
  longlong lVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  longlong lVar7;
  
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



void XeCryptRc4Ecb(int param_1,byte *param_2,longlong param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  
  if ((int)param_3 == 0) {
    return;
  }
  uVar5 = (ulonglong)*(byte *)(param_1 + 0x100);
  uVar6 = (ulonglong)*(byte *)(param_1 + 0x101);
  do {
    uVar3 = (int)uVar5 + 1U & 0xff;
    uVar5 = (ulonglong)uVar3;
    bVar1 = *(byte *)(param_1 + uVar3);
    uVar4 = (int)uVar6 + (uint)bVar1 & 0xff;
    uVar6 = (ulonglong)uVar4;
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



void XeCryptRotSum(longlong *param_1,ulonglong *param_2,int param_3)

{
  longlong lVar1;
  longlong lVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  
  lVar2 = *param_1;
  uVar3 = param_1[1];
  lVar1 = param_1[2];
  uVar4 = param_1[3];
  while (param_3 != 0) {
    uVar5 = *param_2;
    uVar3 = uVar5 + uVar3;
    uVar4 = uVar4 - uVar5;
    lVar2 = (ulonglong)(uVar3 < uVar5) + lVar2;
    uVar3 = uVar3 * 0x20000000 | uVar3 >> 0x23;
    param_3 = param_3 + -1;
    lVar1 = lVar1 - (ulonglong)(uVar5 < uVar4);
    uVar4 = uVar4 * 0x80000000 | uVar4 >> 0x21;
    param_2 = param_2 + 1;
  }
  *param_1 = lVar2;
  param_1[1] = uVar3;
  param_1[2] = lVar1;
  param_1[3] = uVar4;
  return;
}



void FUN_000232f0(ulonglong *param_1,uint *param_2,int param_3)

{
  uint uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  
  uVar3 = *param_1;
  uVar2 = param_1[1];
  while (param_3 != 0) {
    uVar1 = *param_2;
    param_3 = param_3 + -1;
    param_2 = param_2 + 1;
    uVar3 = uVar1 + uVar3;
    uVar2 = uVar2 - uVar1;
    uVar3 = uVar3 * 0x20000000 | uVar3 >> 0x23;
    uVar2 = uVar2 * 0x80000000 | uVar2 >> 0x21;
  }
  *param_1 = uVar3;
  param_1[1] = uVar2;
  return;
}



void XeCryptRotSumSha(undefined8 param_1,ulonglong param_2,undefined8 param_3,ulonglong param_4,
                     undefined8 param_5,undefined8 param_6)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
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
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



void FUN_00023450(byte *param_1,int param_2,int param_3)

{
  ulonglong uVar1;
  ulonglong uVar2;
  
  uVar1 = 0x79004e00750042;
  if (param_3 == 0) {
    while (param_2 != 0) {
      param_2 = param_2 + -1;
      uVar2 = (ulonglong)*param_1 * 0xfb;
      *param_1 = *param_1 ^ (byte)uVar1;
      param_1 = param_1 + 1;
      uVar1 = (ulonglong)(((uint)uVar2 & 0xff00) << 8) + (uVar2 & 0xff) +
              (uVar1 << 0x30 | uVar1 >> 0x10) & 0xffffffff00ff00ff;
    }
    return;
  }
  while (param_2 != 0) {
    uVar2 = (*param_1 ^ uVar1) * 0xfb;
    *param_1 = (byte)(*param_1 ^ uVar1);
    param_2 = param_2 + -1;
    param_1 = param_1 + 1;
    uVar1 = (ulonglong)(((uint)uVar2 & 0xff00) << 8) + (uVar2 & 0xff) +
            (uVar1 << 0x30 | uVar1 >> 0x10) & 0xffffffff00ff00ff;
  }
  return;
}



ulonglong XeCryptMemDiff(byte *param_1,byte *param_2,longlong param_3)

{
  byte bVar1;
  byte bVar2;
  ulonglong uVar3;
  
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



void FUN_00023538(undefined8 param_1,ulonglong param_2,longlong *param_3,undefined8 param_4,
                 undefined8 param_5)

{
  byte bVar1;
  longlong in_r2;
  undefined8 uVar2;
  longlong *plVar3;
  word local_1a0;
  
  uVar2 = __Save_R12_26_thru_31();
  memcpy(param_5,uVar2,0x10);
  if ((param_2 & 0xffffffff) != 0) {
    do {
      plVar3 = (longlong *)param_4;
      bVar1 = *(byte *)(plVar3 + 1);
      *plVar3 = *plVar3 << 1;
      plVar3[1] = plVar3[1] << 1;
      *(byte *)((int)plVar3 + 7) = bVar1 >> 7 | *(byte *)((int)plVar3 + 7);
      *(byte *)((int)plVar3 + 0xf) = *(byte *)param_3 >> 7 | *(byte *)((int)plVar3 + 0xf);
      bVar1 = *(byte *)(param_3 + 1);
      *param_3 = *param_3 << 1;
      param_3[1] = param_3[1] << 1;
      *(byte *)((int)param_3 + 7) = bVar1 >> 7 | *(byte *)((int)param_3 + 7);
      XeCryptAesEncrypt(&local_1a0,param_5,in_r2 + 0x13cf8);
      FUN_0002402c(&local_1a0,param_4,param_5,ZEXT48(&UNK_00011bf8) + in_r2);
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
  word local_50;
  word local_40;
  dword local_30;
  
  uVar2 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  memcpy(&local_40);
  memcpy(&local_50,param_3,0x10);
  FUN_00023538(uVar2,0x80,&local_40,&local_50,param_4);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



ulonglong FUN_00023698(ulonglong param_1,uint param_2,uint param_3)

{
  return (ulonglong)
         (((uint)(param_1 >> 0x11) & 0x80 | (uint)(param_1 >> 0x19) & 0x7f) +
          ((uint)(param_1 >> 0x25) & 7 | (uint)(param_1 >> 0x1d) & 0xf8) +
          ((uint)(param_1 >> 0x16) & 3 | (uint)(param_1 >> 0xe) & 0xfc) +
          ((uint)(param_1 >> 0xb) & 0x1f | (uint)(param_1 >> 3) & 0xe0) +
          ((uint)(param_1 >> 7) & 1 | (uint)(param_1 << 1) & 0xfe) & 0xff ^ param_2 & 0xff ^
         param_3 & 0xff) ^ 0x3a;
}



ulonglong FUN_00023718(ulonglong param_1,undefined8 param_2,undefined8 param_3)

{
  return (ulonglong)
         (((uint)(param_1 >> 0x27) & 1 | (uint)(param_1 >> 0x1f) & 0xfe) +
          ((uint)(param_1 >> 0x1b) & 0x1f | (uint)(param_1 >> 0x13) & 0xe0) +
          ((uint)(param_1 >> 10) & 0x3f | (uint)(param_1 >> 2) & 0xc0) +
          ((uint)(param_1 >> 0x14) & 0xf | (uint)(param_1 >> 0xc) & 0xf0) + ((uint)param_1 & 0xff) &
          0xff ^ (uint)((ulonglong)param_2 >> 8) & 0xff ^ (uint)((ulonglong)param_3 >> 8) & 0xff) ^
         0x72;
}



void FUN_00023798(undefined8 param_1,longlong param_2)

{
  int iVar1;
  uint *puVar2;
  longlong lVar3;
  byte *pbVar4;
  int iVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  
  puVar2 = (uint *)__Save_R12_28_thru_31();
  uVar9 = (ulonglong)*puVar2;
  lVar3 = param_2 + 0x10f;
  uVar8 = (ulonglong)puVar2[1];
  iVar5 = 10;
  uVar7 = (ulonglong)puVar2[2];
  uVar6 = (ulonglong)puVar2[3];
  do {
    pbVar4 = (byte *)lVar3;
    iVar5 = iVar5 + -1;
    lVar3 = lVar3 + -1;
    iVar1 = (int)param_2;
    uVar9 = CONCAT31(CONCAT21(CONCAT11(*(byte *)(((uint)(uVar6 >> 0x10) & 0xff) + iVar1) ^ *pbVar4,
                                       *(undefined *)(((uint)(uVar6 >> 8) & 0xff) + iVar1)),
                              *(undefined *)(((uint)uVar6 & 0xff) + iVar1)),
                     *(undefined *)((int)(uVar6 >> 0x18) + iVar1)) ^ uVar9;
    uVar8 = uVar8 ^ uVar9;
    uVar7 = uVar7 ^ uVar8;
    uVar6 = uVar6 ^ uVar7;
  } while (iVar5 != 0);
  *puVar2 = (uint)uVar9;
  puVar2[1] = (uint)uVar8;
  puVar2[2] = (uint)uVar7;
  puVar2[3] = (uint)uVar6;
  return;
}

//23830
void HvSetupShaSaltedHash(undefined8 param_1,undefined8 param_2,longlong param_3,ulonglong param_4) {
  uint uVar1;
  byte *pbVar2;
  int in_r2;
  undefined8 uVar3;
  ulonglong uVar4;
  uint uVar6;
  longlong lVar5;
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
      uVar4 = (ulonglong)uVar6;
      lVar5 = param_3;
	  
      do {
        pbVar2 = (byte *)lVar5;
        uVar4 = uVar4 - 1;
        *pbVar2 = pbVar2[(int)((int)&local_50 - (int)param_3)] ^ *pbVar2;
        lVar5 = lVar5 + 1;
      } while ((uVar4 & 0xffffffff) != 0);
    }
	
    param_4 = param_4 - (ulonglong)uVar6;
    param_3 = (ulonglong)uVar6 + param_3;
  }
  
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



undefined8 HvSetupMemEncryptionKey(undefined8 param_1,ulonglong param_2,longlong param_3,ulonglong param_4, longlong param_5,undefined8 param_6) {
  ulonglong uVar1;
  longlong in_r2;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = __Save_R12_24_thru_31();
  if (((param_4 & 0xffffffff) < 0x2a) || ((param_4 - 0x2a & 0xffffffff) < (param_2 & 0xffffffff))) {
    uVar2 = 0;
  }
  else {
    if (param_5 == 0) {
      param_5 = in_r2 + 0x15e48;
    }
    *(undefined *)param_3 = 0;
    memcpy(param_3 + 1, param_6, 0x14);
	
    lVar3 = param_3 + 0x15;
    memcpy(lVar3,param_5,0x14);
	
    uVar1 = (param_4 - param_2) - 0x2a & 0xffffffff;
    memset(param_3 + 0x29, 0, uVar1);
	
    *(undefined *)((int)(param_4 - param_2) + -0x16 + (int)lVar3) = 1;
    memcpy(uVar1 + lVar3 + 0x15,uVar2,param_2 & 0xffffffff);
	
    HvSetupShaSaltedHash(param_6, 0x14, lVar3, param_4 - 0x15);
    HvSetupShaSaltedHash(lVar3, param_4 - 0x15, param_3 + 1, 0x14);
    uVar2 = 1;
  }
  return uVar2;
}



undefined8
FUN_00023a10(undefined8 param_1,ulonglong param_2,longlong *param_3,char **param_4,longlong param_5)

{
  longlong in_r2;
  longlong lVar1;
  int iVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  longlong lVar5;
  
  lVar1 = __Save_R12_24_thru_31();
  if ((0x29 < (param_2 & 0xffffffff)) && (*(char *)lVar1 == '\0')) {
    if (param_5 == 0) {
      param_5 = in_r2 + 0x15e48;
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



void FUN_00023b10(undefined *param_1,uint param_2)

{
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



undefined8
FUN_00023b58(undefined8 param_1,ulonglong param_2,undefined8 param_3,ulonglong param_4,
            undefined8 param_5)

{
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  ulonglong uVar5;
  int in_r2;
  longlong lVar6;
  undefined8 uVar7;
  byte bVar8;
  int iVar9;
  uint *puVar10;
  longlong lVar11;
  int iVar13;
  ulonglong uVar12;
  ulonglong uVar14;
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
        bVar8 = (byte)(((ulonglong)bVar1 & 0x7fffffff8000007f) << 1) | 1;
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
        bVar8 = (byte)(((ulonglong)bVar1 & 0x7fffffff8000007f) << 1) | 1;
      }
      *(byte *)lVar11 = bVar8;
      bVar8 = bVar1 & 0x80;
    } while (iVar9 != 0);
    memset(uVar5 - 0x80,0,0x10);
    uVar14 = param_2 & 0xffffffff;
    if (0x10 < uVar14) {
      lVar11 = lVar6 - (uVar5 - 0x80);
      uVar14 = (ulonglong)((int)param_2 - 0x11U >> 4) + 1;
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
    HvpReleaseSpinLock((ulonglong)uVar2);
    uVar7 = 1;
  }
  else {
    HvpReleaseSpinLock((ulonglong)uVar2);
    uVar7 = 0;
  }
  return uVar7;
}



undefined8 XeCryptAesKeyTable(void)

{
  uint *puVar1;
  uint *puVar2;
  ulonglong uVar3;
  int in_r9;
  uint *puVar4;
  int in_r10;
  undefined *puVar5;
  int iVar6;
  ulonglong in_r11;
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
  HvpReleaseSpinLock((ulonglong)param_1);
  return 1;
}



// WARNING: Variable defined which should be unmapped: local_30
// WARNING: Variable defined which should be unmapped: local_28
// WARNING: Variable defined which should be unmapped: local_20
// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Variable defined which should be unmapped: local_8

void XeCryptAesEncrypt(uint *param_1,uint *param_2,int param_3)

{
  byte *pbVar1;
  ulonglong uVar2;
  uint uVar3;
  ulonglong uVar4;
  uint uVar5;
  ulonglong uVar6;
  uint uVar7;
  ulonglong uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  longlong lVar14;
  qword local_30;
  qword local_28;
  qword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar3 = *param_2;
  uVar2 = (ulonglong)uVar3;
  uVar5 = param_2[1];
  uVar4 = (ulonglong)uVar5;
  uVar7 = param_2[2];
  uVar6 = (ulonglong)uVar7;
  uVar9 = param_2[3];
  uVar8 = (ulonglong)uVar9;
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
    uVar2 = (ulonglong)
            CONCAT13(*(undefined *)(param_3 + (uVar3 >> 0x10 & 0xff)),
                     CONCAT12(*(undefined *)(param_3 + (uVar3 >> 8 & 0xff)),
                              CONCAT11(*(undefined *)(param_3 + (uVar3 & 0xff)),
                                       *(undefined *)(param_3 + (uVar3 >> 0x18))))) ^
            (ulonglong)*pbVar1 << 0x18 ^ uVar2;
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



// WARNING: Variable defined which should be unmapped: local_40
// WARNING: Variable defined which should be unmapped: local_38
// WARNING: Variable defined which should be unmapped: local_30
// WARNING: Variable defined which should be unmapped: local_28
// WARNING: Variable defined which should be unmapped: local_20
// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_0002402c(uint *param_1,uint *param_2,uint *param_3,int param_4)

{
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
  longlong lVar16;
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



void XeCryptAesDecrypt(uint *param_1,undefined8 param_2,uint *param_3)

{
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



// WARNING: Variable defined which should be unmapped: local_40
// WARNING: Variable defined which should be unmapped: local_38
// WARNING: Variable defined which should be unmapped: local_30
// WARNING: Variable defined which should be unmapped: local_28
// WARNING: Variable defined which should be unmapped: local_20
// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00024274(int param_1,uint *param_2,uint *param_3,int param_4)

{
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
  longlong lVar16;
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



void XeCryptBnQwBeSigDifference(uint *param_1,undefined8 param_2,uint *param_3)

{
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
               CONCAT13(*(undefined *)(in_r10 + (unaff_r14 >> 0x18)),
                        CONCAT12(*(undefined *)(in_r10 + (in_r12 >> 0x10 & 0xff)),
                                 CONCAT11(*(undefined *)(in_r10 + (unaff_r16 >> 8 & 0xff)),
                                          *(undefined *)(in_r10 + (unaff_r15 & 0xff)))));
  *param_3 = *param_1 ^
             CONCAT13(*(undefined *)(in_r10 + (in_r12 >> 0x18)),
                      CONCAT12(*(undefined *)(in_r10 + (unaff_r16 >> 0x10 & 0xff)),
                               CONCAT11(*(undefined *)(in_r10 + (unaff_r15 >> 8 & 0xff)),
                                        *(undefined *)(in_r10 + (unaff_r14 & 0xff)))));
  return;
}



void FUN_000244c0(undefined8 param_1,undefined8 param_2,undefined8 param_3,longlong param_4,
                 undefined8 param_5,undefined8 param_6)

{
  uint uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  longlong lVar4;
  
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



void XeCryptBnQwNeDigLen(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4
                        ,undefined8 param_5,undefined8 param_6)

{
  uint uVar1;
  undefined8 uVar2;
  uint unaff_r27;
  undefined8 *unaff_r28;
  undefined8 unaff_r29;
  
  uVar2 = XeCryptBnQwNeModInv(*unaff_r28);
  XeCryptBnQw_Copy(unaff_r29,param_5,0x20);
  XeCryptBnQw_Copy(param_5,param_6,0x20);
  uVar1 = unaff_r27 >> 1;
  while (uVar1 != 0) {
    XeCryptBnQwNeModMul(param_6,param_6,param_6,uVar2,unaff_r28,0x20);
    uVar1 = uVar1 >> 1;
  }
  XeCryptBnQwNeModMul(param_6,param_5,param_5,uVar2,unaff_r28,0x20);
  XeCryptBnQw_Copy(param_5,param_5,0x20);
  XeCryptBnQwBeSigFormat(param_6,param_2,param_3);
  return;
}



int FUN_00024578(int param_1,int param_2)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(param_2 * 8 + param_1);
  while ((param_2 != 0 && (plVar1 = plVar1 + -1, *plVar1 == 0))) {
    param_2 = param_2 + -1;
  }
  return param_2;
}



ulonglong FUN_000245b0(longlong param_1,ulonglong param_2)

{
  longlong lVar1;
  
  param_1 = (param_2 & 0xffffffff) * 8 + param_1;
  if ((param_2 & 0xffffffff) != 0) {
    do {
      param_1 = param_1 + -8;
      if (*(longlong *)param_1 != 0) break;
      param_2 = param_2 - 1;
    } while ((param_2 & 0xffffffff) != 0);
    if ((param_2 & 0xffffffff) != 0) {
      lVar1 = countLeadingZeros(*(longlong *)param_1);
      param_2 = (ulonglong)(uint)((int)param_2 << 6) - lVar1;
    }
  }
  return param_2;
}



void FUN_00024600(undefined8 param_1,int param_2,longlong param_3,ulonglong param_4)

{
  int iVar1;
  int iVar3;
  undefined8 uVar2;
  longlong lVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  int iVar7;
  
  iVar3 = __Save_R12_25_thru_31();
  XeCryptBnQw_Zero(iVar3,(ulonglong)(uint)((int)param_4 << 1));
  lVar4 = (param_4 & 0xffffffff) * 8 + param_3;
  uVar5 = param_4;
  if ((param_4 & 0xffffffff) != 0) {
    do {
      lVar4 = lVar4 + -8;
      if (*(longlong *)lVar4 != 0) break;
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



void FUN_000246b0(undefined8 param_1,longlong param_2,ulonglong param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  longlong lVar3;
  ulonglong uVar4;
  int iVar5;
  ulonglong uVar6;
  
  uVar1 = __Save_R12_25_thru_31();
  XeCryptBnQw_Zero(uVar1._4_4_,(ulonglong)(uint)((int)param_3 << 1));
  lVar3 = (param_3 & 0xffffffff) * 8 + param_2;
  if ((param_3 & 0xffffffff) != 0) {
    do {
      lVar3 = lVar3 + -8;
      if (*(longlong *)lVar3 != 0) break;
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
      FUN_00024ae0(uVar1._4_4_,uVar1,uVar1,(ulonglong)(uint)((int)param_3 << 1));
      FUN_00024c0c(uVar1._4_4_,param_2,param_3);
    }
  }
  return;
}



ulonglong FUN_00024788(ulonglong param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4)

{
  bool bVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  
  if ((param_4 == 0) || ((param_3 & 0x8000000000000000) != 0)) {
    if (param_1 < param_3) {
      uVar2 = 0;
      uVar3 = 0x8000000000000000;
      do {
        uVar4 = param_2 >> 0x3f;
        param_2 = param_2 << 1;
        uVar4 = uVar4 | param_1 << 1;
        if (((longlong)param_1 < 0) || (param_3 <= uVar4)) {
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



ulonglong XeCryptBnQwNeMod(ulonglong param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4,
                          undefined8 param_5,undefined8 param_6,ulonglong param_7)

{
  bool bVar1;
  ulonglong uVar2;
  ulonglong in_r11;
  
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



undefined8
FUN_00024870(undefined8 param_1,longlong param_2,longlong param_3,ulonglong param_4,
            ulonglong param_5)

{
  longlong lVar1;
  longlong lVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  word *pwVar8;
  ulonglong uVar9;
  word local_8a0;
  word local_690;
  word local_480;
  
  lVar1 = __Save_R12_20_thru_31();
  if (((param_4 & 0xffffffff) < 0x82) && ((param_5 & 0xffffffff) < 0x42)) {
    lVar5 = (param_5 & 0xffffffff) * 8 + param_2;
    uVar9 = param_5;
    while (((uVar9 & 0xffffffff) != 0 && (lVar5 = lVar5 + -8, *(longlong *)lVar5 == 0))) {
      uVar9 = uVar9 - 1;
    }
    if ((uVar9 & 0xffffffff) != 0) {
      lVar5 = (param_4 & 0xffffffff) * 8 + lVar1;
      while (((param_4 & 0xffffffff) != 0 && (lVar5 = lVar5 + -8, *(longlong *)lVar5 == 0))) {
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



undefined8 XeCryptBnQwNeAdd(void)

{
  undefined *unaff_100001d5;
  longlong lVar1;
  undefined8 uVar2;
  int iVar3;
  undefined8 in_r6;
  int unaff_r20;
  longlong unaff_r21;
  undefined8 unaff_r22;
  int unaff_r23;
  int unaff_r24;
  int unaff_r25;
  int unaff_r26;
  int unaff_r27;
  undefined8 unaff_r28;
  int unaff_r29;
  undefined *unaff_r30;
  ulonglong unaff_r31;
  
  do {
    FUN_00024b38(&stack0x00000050,&stack0x00000050,&stack0x00000260,in_r6);
    while (iVar3 = FUN_00024d08(&stack0x00000050,unaff_r30,unaff_r28), in_r6 = unaff_r28, iVar3 != 1
          ) {
      FUN_00024b38(unaff_r30,unaff_100001d5,&stack0x00000050,unaff_r28);
      iVar3 = FUN_00024d08(unaff_r30,&stack0x00000260,unaff_r28);
      if (-1 < iVar3) {
        unaff_r29 = unaff_r29 + 1;
        unaff_r25 = unaff_r25 + 1;
      }
      unaff_r29 = unaff_r29 + -1;
      if (unaff_r29 < 0) {
        XeCryptBnQw_Copy(&stack0x00000470,unaff_r20,unaff_r31);
        XeCryptBnQw_Zero(unaff_r26 + unaff_r20,unaff_r21 - unaff_r31);
        return 1;
      }
      uVar2 = unaff_r22;
      if (1 < (unaff_r31 & 0xffffffff)) {
        uVar2 = *(undefined8 *)(((int)unaff_r31 + -2) * 8 + unaff_r27);
      }
      lVar1 = FUN_00024788(*(undefined8 *)(&stack0x00000470 + (unaff_r25 + -1) * 8),
                           *(undefined8 *)(&stack0x00000470 + (unaff_r25 + -2) * 8),
                           *(undefined8 *)(unaff_r23 + unaff_r27),uVar2);
      if (lVar1 == 0) {
        lVar1 = 1;
      }
      XeCryptBnQw_Zero(&stack0x00000050,unaff_r31);
      uVar2 = FUN_00024b90(&stack0x00000050,lVar1,unaff_r27,unaff_r31);
      unaff_100001d5 = &stack0x00000470 + unaff_r29 * 8;
      unaff_r30 = &stack0x00000470 + unaff_r29 * 8;
      *(undefined8 *)(unaff_r26 + unaff_r24) = uVar2;
      unaff_r25 = unaff_r25 + -1;
    }
  } while( true );
}



ulonglong FUN_00024ae0(ulonglong *param_1,int param_2,int param_3,longlong param_4)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  
  uVar1 = 0;
  param_2 = param_2 - (int)param_1;
  param_3 = param_3 - (int)param_1;
  if ((int)param_4 != 0) {
    do {
      uVar4 = *(ulonglong *)((int)param_1 + param_3);
      uVar2 = *(longlong *)((int)param_1 + param_2) + uVar1;
      uVar3 = uVar2 + uVar4;
      *param_1 = uVar3;
      param_1 = param_1 + 1;
      uVar1 = (ulonglong)
              (byte)(uVar3 < uVar4 != uVar2 < uVar1 | (uVar2 < uVar1 && uVar3 < uVar4) << 1);
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return uVar1;
}



ulonglong XeCryptBnQwNeAcc(ulonglong *param_1,int param_2,int param_3,longlong param_4,
                          ulonglong param_5)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  byte in_cr0;
  
  if (!(bool)(in_cr0 >> 1 & 1)) {
    do {
      uVar3 = *(ulonglong *)((int)param_1 + param_3);
      uVar1 = *(longlong *)((int)param_1 + param_2) + param_5;
      uVar2 = uVar1 + uVar3;
      *param_1 = uVar2;
      param_1 = param_1 + 1;
      param_5 = (ulonglong)
                (byte)(uVar2 < uVar3 != uVar1 < param_5 | (uVar1 < param_5 && uVar2 < uVar3) << 1);
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return param_5;
}



ulonglong FUN_00024b38(longlong *param_1,int param_2,int param_3,longlong param_4)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  
  uVar1 = 0;
  param_2 = param_2 - (int)param_1;
  param_3 = param_3 - (int)param_1;
  if ((int)param_4 != 0) {
    do {
      uVar2 = *(ulonglong *)((int)param_1 + param_2);
      uVar4 = *(ulonglong *)((int)param_1 + param_3);
      uVar3 = uVar2 - uVar1;
      *param_1 = uVar3 - uVar4;
      param_1 = param_1 + 1;
      uVar1 = (ulonglong)
              (byte)(uVar3 < uVar4 != uVar2 < uVar1 | (uVar2 < uVar1 && uVar3 < uVar4) << 1);
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return uVar1;
}



ulonglong FUN_00024b90(ulonglong *param_1,ulonglong param_2,int param_3,longlong param_4)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  
  uVar5 = 0;
  if (1 < param_2) {
    param_3 = param_3 - (int)param_1;
    if ((int)param_4 != 0) {
      do {
        uVar3 = *(ulonglong *)((int)param_1 + param_3);
        uVar4 = param_2 * uVar3;
        uVar1 = *param_1 + uVar5;
        uVar2 = uVar1 + uVar4;
        *param_1 = uVar2;
        param_1 = param_1 + 1;
        uVar5 = SUB168(ZEXT816(param_2) * ZEXT816(uVar3) >> 0x40,0) +
                (ulonglong)
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
        uVar3 = *(ulonglong *)((int)param_1 + param_3);
        uVar1 = *param_1 + uVar5;
        uVar2 = uVar1 + uVar3;
        *param_1 = uVar2;
        param_1 = param_1 + 1;
        uVar5 = (ulonglong)
                (byte)(uVar2 < uVar3 != uVar1 < uVar5 | (uVar1 < uVar5 && uVar2 < uVar3) << 1);
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
    return uVar5;
  }
  return 0;
}



void FUN_00024c0c(ulonglong *param_1,ulonglong *param_2,ulonglong param_3)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  
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
              (ulonglong)
              (byte)(uVar2 < uVar4 != uVar1 < uVar5 | (uVar1 < uVar5 && uVar2 < uVar4) << 1);
      uVar5 = param_1[1] + uVar1;
      param_1[1] = uVar5;
      param_1 = param_1 + 2;
      uVar5 = (ulonglong)(uVar5 < uVar1);
      param_3 = param_3 - 1;
    } while (param_3 != 0);
    return;
  }
  return;
}



void XeCryptBnQwNeCompare(ulonglong *param_1,ulonglong *param_2,ulonglong param_3)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  ulonglong in_r12;
  ulonglong uVar6;
  longlong in_CTR;
  
  while( true ) {
    param_1[1] = param_3;
    puVar1 = param_1 + 2;
    uVar6 = (ulonglong)(param_3 < in_r12);
    in_CTR = in_CTR + -1;
    if (in_CTR == 0) break;
    uVar4 = *param_2;
    uVar5 = uVar4 * uVar4;
    uVar2 = *puVar1 + uVar6;
    uVar3 = uVar2 + uVar5;
    *puVar1 = uVar3;
    param_2 = param_2 + 1;
    in_r12 = SUB168(ZEXT816(uVar4) * ZEXT816(uVar4) >> 0x40,0) +
             (ulonglong)
             (byte)(uVar3 < uVar5 != uVar2 < uVar6 | (uVar2 < uVar6 && uVar3 < uVar5) << 1);
    param_3 = param_1[3] + in_r12;
    param_1 = puVar1;
  }
  return;
}



ulonglong FUN_00024c88(ulonglong *param_1,ulonglong param_2,int param_3,longlong param_4)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  
  uVar5 = 0;
  if (1 < param_2) {
    param_3 = param_3 - (int)param_1;
    if ((int)param_4 != 0) {
      do {
        uVar3 = *(ulonglong *)((int)param_1 + param_3);
        uVar1 = *param_1;
        uVar4 = param_2 * uVar3;
        uVar2 = uVar1 - uVar5;
        *param_1 = uVar2 - uVar4;
        param_1 = param_1 + 1;
        uVar5 = SUB168(ZEXT816(param_2) * ZEXT816(uVar3) >> 0x40,0) +
                (ulonglong)
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
        uVar3 = *(ulonglong *)((int)param_1 + param_3);
        uVar2 = uVar1 - uVar5;
        *param_1 = uVar2 - uVar3;
        param_1 = param_1 + 1;
        uVar5 = (ulonglong)
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
  ulonglong *puVar1;
  ulonglong *puVar2;
  
  puVar1 = (ulonglong *)(param_3 * 8 + param_1);
  puVar2 = (ulonglong *)(param_3 * 8 + param_2);
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
  longlong in_r2;
  int iVar1;
  longlong lVar2;
  undefined8 uVar3;
  qword local_18;
  qword local_10;
  qword local_8;
  
  lVar2 = in_r2 + 0x16cd0;
  HvpAquireSpinLock(lVar2);
  if (*(char *)((int)DWORD_ARRAY_0001000c + (int)in_r2) != '\0') {
    iVar1 = XeCryptMemDiff(param_1,in_r2 + 0x10010,0x10);
    uVar3 = 1;
    if (iVar1 == 0) goto LAB_00024db4;
  }
  uVar3 = 0;
LAB_00024db4:
  FUN_000001e0(lVar2);
  return uVar3;
}



ulonglong FUN_00024dd8(undefined8 param_1,int param_2)

{
  byte bVar1;
  longlong in_r2;
  undefined *puVar2;
  undefined *puVar3;
  longlong lVar4;
  ulonglong uVar5;
  longlong lVar6;
  
  puVar2 = (undefined *)__Save_R12_29_thru_31();
  uVar5 = 0;
  if (param_2 == 0x10) {
    lVar4 = in_r2 + 0x16cd0;
    HvpAquireSpinLock(lVar4);
    bVar1 = *(byte *)((int)DWORD_ARRAY_0001000c + (int)in_r2);
    uVar5 = (ulonglong)bVar1;
    if (bVar1 != 0) {
      in_r2 = in_r2 + 0x10010;
      lVar6 = 0x10;
      do {
        puVar3 = (undefined *)in_r2;
        in_r2 = in_r2 + 1;
        *puVar2 = *puVar3;
        puVar2 = puVar2 + 1;
        lVar6 = lVar6 + -1;
      } while (lVar6 != 0);
    }
    FUN_000001e0(lVar4);
  }
  return uVar5;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00024e50(byte *param_1)

{
  uint uVar1;
  longlong in_r2;
  word *pwVar2;
  byte *pbVar3;
  undefined *puVar5;
  longlong lVar4;
  longlong lVar6;
  longlong lVar7;
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
  XeCryptAesKey(&local_190,*(longlong *)((int)DWORD_ARRAY_0001613c + (int)in_r2 + 0x104) + 0x100);
  pwVar2 = &local_30;
  lVar6 = in_r2 + 0x10030;
  lVar7 = 0x10;
  lVar4 = lVar6;
  do {
    puVar5 = (undefined *)lVar4;
    lVar4 = lVar4 + 1;
    *(undefined *)pwVar2 = *puVar5;
    pwVar2 = (word *)((int)pwVar2 + 1);
    lVar7 = lVar7 + -1;
  } while (lVar7 != 0);
  XeCryptAesCbc(&local_190,in_r2 + 0x10020,0x10,param_1 + 2,&local_30,1);
  XeCryptAesCbc(&local_190,in_r2 + 0x16a10,0x10,param_1 + 0x12,&local_30,1);
  param_1 = param_1 + 0x22;
  lVar4 = 0x10;
  do {
    pbVar3 = (byte *)lVar6;
    lVar6 = lVar6 + 1;
    *param_1 = *pbVar3;
    param_1 = param_1 + 1;
    lVar4 = lVar4 + -1;
  } while (lVar4 != 0);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



void FUN_00024f60(void)

{
  uint uVar1;
  longlong in_r2;
  byte *pbVar2;
  word *pwVar3;
  byte *pbVar4;
  undefined *puVar6;
  longlong lVar5;
  byte *pbVar7;
  longlong lVar8;
  longlong lVar9;
  word local_1d0;
  word local_70;
  word local_60;
  word local_50;
  word local_40;
  dword local_30;
  
  pbVar2 = (byte *)__Save_R12_29_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  memset(pbVar2,0,0x42);
  lVar8 = in_r2 + 0x10030;
  *pbVar2 = *pbVar2 & 0xc0 | 0x28;
  pbVar2[1] = 0x40;
  FUN_00023620(*(longlong *)((int)DWORD_ARRAY_0001613c + (int)in_r2 + 0x104) + 0x100,lVar8,&local_70
               ,&local_60);
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
  XeCryptAesCbc(&local_1d0,in_r2 + 0x10020,0x10,pbVar2 + 2,&local_50,1);
  XeCryptAesCbc(&local_1d0,in_r2 + 0x16a10,0x10,pbVar2 + 0x12,&local_50,1);
  pbVar7 = pbVar2 + 0x22;
  lVar5 = 0x10;
  do {
    pbVar4 = (byte *)lVar8;
    lVar8 = lVar8 + 1;
    *pbVar7 = *pbVar4;
    pbVar7 = pbVar7 + 1;
    lVar5 = lVar5 + -1;
  } while (lVar5 != 0);
  XeCryptAesCbcMac(ZEXT48(DWORD_ARRAY_00010410) + in_r2,pbVar2 + 2,0x20,&local_40);
  FUN_00023620(&local_60,&local_40,&local_70,pbVar2 + 0x32);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_000250b8(undefined8 param_1)

{
  int in_r2;
  longlong lVar1;
  int iVar2;
  qword local_18;
  qword local_10;
  qword local_8;
  
  iVar2 = in_r2 + 0x16cd0;
  HvpAquireSpinLock(iVar2);
  lVar1 = HvpPhysicalToReal(param_1,0x4a);
  if ((*(ushort *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14) + 0x604) & 0x200)
      == 0x200) {
    FUN_00024f60();
  }
  else {
    FUN_00024e50(lVar1 + 8);
  }
  FUN_000001e0(iVar2);
  return 0;
}



void FUN_00025138(int param_1,int param_2)

{
  int in_r2;
  qword local_8;
  
  if (param_1 != 0) {
    *(undefined *)((int)DWORD_ARRAY_0001000c + in_r2) = 0;
    *(undefined *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x270) = 0;
  }
  if (param_2 != 0) {
    *(undefined4 *)((int)DWORD_ARRAY_0001000c + in_r2 + 4) = 0;
    *(undefined4 *)((int)DWORD_ARRAY_0001000c + in_r2 + 8) = 0;
    *(undefined4 *)((int)DWORD_ARRAY_0001000c + in_r2 + 0xc) = 0;
    *(undefined4 *)((int)DWORD_ARRAY_0001000c + in_r2 + 0x10) = 0;
  }
  memset((int)DWORD_ARRAY_00016a20 + in_r2,0,0x270);
  *(undefined4 *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x274) = 1;
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_000251b8(undefined8 param_1)

{
  longlong in_r2;
  qword local_18;
  qword local_10;
  qword local_8;
  
  HvpAquireSpinLock(in_r2 + 0x16cd0);
  FUN_00025138(param_1,0);
  FUN_000001e0(in_r2 + 0x16cd0);
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
  ulonglong uVar4;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar4 = (ulonglong)*(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x23) -
          (ulonglong)(*(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x151) >> 3);
  FUN_00020060(&local_20,4);
  trapWord(6,uVar4,0);
  iVar2 = local_20 - (int)((ulonglong)local_20 / (uVar4 & 0xffffffff)) * (int)uVar4;
  iVar3 = (int)uVar4 + -1;
  uVar1 = *(undefined *)(iVar2 + in_r2 + 0x16b78);
  *(undefined *)(iVar2 + in_r2 + 0x16b78) = *(undefined *)(iVar3 + in_r2 + 0x16b78);
  *(undefined *)(iVar3 + in_r2 + 0x16b78) = uVar1;
  return;
}



undefined8 FUN_00025298(void)

{
  undefined uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  longlong in_r2;
  int iVar6;
  longlong lVar7;
  undefined *puVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  longlong lVar11;
  dword local_b0;
  word local_a0;
  word local_40;
  dword local_2c;
  
  iVar6 = __Save_R12_28_thru_31();
  iVar5 = (int)in_r2;
  uVar2 = *(uint *)(iVar5 + 0x10000);
  uVar10 = 0;
  memcpy(in_r2 + 0x16b70,iVar6,0x34);
  XeCryptShaInit(&local_a0);
  XeCryptShaUpdate(&local_a0,in_r2 + 0x16b70,0x24);
  *(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x154) =
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x157) << 0x18 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x156) << 0x10 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x155) << 8 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x154);
  *(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x160) =
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x163) << 0x18 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x162) << 0x10 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x161) << 8 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x160);
  uVar9 = (ulonglong)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x167) << 0x18 |
          (ulonglong)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x166) << 0x10 |
          (ulonglong)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x165) << 8 |
          (ulonglong)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x164);
  *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x164) = (int)uVar9;
  uVar9 = (uVar9 - (*(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x15c) >> 0xf)) - 0xc;
  *(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x168) =
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x16b) << 0x18 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x16a) << 0x10 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x169) << 8 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x168);
  *(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x16c) =
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x16f) << 0x18 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x16e) << 0x10 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x16d) << 8 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x16c);
  *(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x170) =
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x173) << 0x18 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x172) << 0x10 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x171) << 8 |
       (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x170);
  FUN_00020060(&local_b0,4);
  trapWord(6,uVar9,0);
  uVar9 = (ulonglong)local_b0 -
          (longlong)(int)((ulonglong)local_b0 / (uVar9 & 0xffffffff)) * (longlong)(int)uVar9;
  uVar4 = (uint)uVar9;
  *(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x25c) = uVar4;
  if (((uVar4 + 0xb ^ uVar4) & 0xfffff800) != 0) {
    uVar9 = uVar9 - (uVar4 + 0xc & 0x7ff);
    *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x25c) = (int)uVar9;
  }
  if ((uVar9 & 0xffffffff) < (ulonglong)*(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x164)) {
    uVar4 = (uint)uVar9 >> 0xb;
    *(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x254) = uVar4;
    if (uVar4 < *(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x16c)) {
      lVar7 = in_r2 + 0x16ba4;
      puVar8 = (undefined *)(uVar4 * 0x10 + iVar6 + 0x24);
      lVar11 = 0x10;
      do {
        uVar1 = *puVar8;
        puVar8 = puVar8 + 1;
        *(undefined *)lVar7 = uVar1;
        lVar7 = lVar7 + 1;
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
      XeCryptShaUpdate(&local_a0,iVar6 + 0x24,
                       (ulonglong)(uint)(*(int *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x254) << 4));
      XeCryptShaUpdate(&local_a0,in_r2 + 0x16ba4,0x10);
      iVar3 = *(int *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x254);
      uVar4 = iVar3 * 0x10;
      if ((int)(uVar4 + 0x34) < 0x8000) {
        XeCryptShaUpdate(&local_a0,(iVar3 + 1) * 0x10 + iVar6 + 0x24,0x7fcc - (ulonglong)uVar4);
      }
      XeCryptShaFinal(&local_a0,&local_40,0x14);
      iVar6 = XeCryptMemDiff(in_r2 + 0x16b42,&local_40,0x14);
      if (iVar6 == 0) {
        *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x148) = 1;
        *(int *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x260) =
             ((*(uint *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x25c) >> 0xb) +
             *(int *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x160)) * 0x10 +
             *(int *)((int)DWORD_ARRAY_00016a20 + iVar5 + 0x138);
        goto LAB_00025494;
      }
    }
  }
  uVar10 = 0xffffffffc8000085;
LAB_00025494:
  HvpReleaseSpinLock((ulonglong)uVar2);
  return uVar10;
}



// WARNING: Variable defined which should be unmapped: local_8

void FUN_000254a8(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int in_r2;
  uint uVar4;
  ulonglong uVar5;
  int iVar6;
  qword local_8;
  
  iVar6 = *(int *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x268);
  if (iVar6 != 0xc) {
    uVar1 = *(uint *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x164);
    uVar2 = *(uint *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x138);
    uVar4 = *(uint *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x25c);
    do {
      trapDoubleWordImmediate(6,(ulonglong)uVar1,0);
      uVar5 = (ulonglong)uVar4 * (ulonglong)*(uint *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x154);
      uVar3 = ((int)uVar5 - (int)(uVar5 / (ulonglong)uVar1) * uVar1) * 0x10;
      *(uint *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x264) = uVar3;
      if (uVar3 < uVar2) {
        return;
      }
      if (*(int *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x170) +
          *(int *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x168) + uVar2 <= uVar3) {
        return;
      }
      iVar6 = iVar6 + 1;
      uVar4 = uVar4 + 1;
      *(int *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x268) = iVar6;
      *(uint *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x25c) = uVar4;
    } while (iVar6 != 0xc);
  }
  return;
}



undefined8 FUN_00025530(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  longlong in_r2;
  longlong lVar4;
  int iVar6;
  undefined8 uVar5;
  word local_40;
  dword local_30;
  
  lVar4 = __Save_R12_29_thru_31();
  iVar2 = (int)in_r2;
  uVar3 = *(uint *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x25c) & 0x7ff;
  uVar1 = *(uint *)(iVar2 + 0x10000);
  memcpy(in_r2 + 0x16bb4,(ulonglong)uVar3 * 0x10 + lVar4,0xc0);
  XeCryptSha(lVar4,(ulonglong)(uVar3 << 4),in_r2 + 0x16bb4,0xc0,
             (ulonglong)((uVar3 + 0xc) * 0x10) + lVar4,(ulonglong)((0x7f4 - uVar3) * 0x10),&local_40
             ,0x10);
  iVar6 = XeCryptMemDiff(&local_40,in_r2 + 0x16ba4,0x10);
  if (iVar6 == 0) {
    *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x148) = 2;
    *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x268) = 0;
    *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x26c) = 0;
    FUN_000254a8();
    HvpReleaseSpinLock((ulonglong)uVar1);
    uVar5 = 0;
  }
  else {
    HvpReleaseSpinLock((ulonglong)uVar1);
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
  longlong in_r2;
  int iVar3;
  undefined8 uVar4;
  word local_30;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  XeCryptSha(param_1,0x8000,0,0,0,0,&local_30,0x10);
  iVar2 = (int)in_r2;
  iVar3 = XeCryptMemDiff(&local_30,
                         (ulonglong)*(uint *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x268) * 0x10 +
                         in_r2 + 0x16bb4,0x10);
  if (iVar3 == 0) {
    iVar3 = *(int *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x26c) + 1;
  }
  else {
    iVar3 = 0;
  }
  *(int *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x26c) = iVar3;
  *(int *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x268) =
       *(int *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x268) + 1;
  *(int *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x25c) =
       *(int *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x25c) + 1;
  FUN_000254a8();
  if (*(int *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x26c) == 4) {
    uVar4 = 0;
  }
  else {
    if (*(int *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x268) != 0xc) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0;
    }
    uVar4 = 0xffffffffc8000085;
  }
  *param_2 = 1;
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar4;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00025708(undefined param_1)

{
  int in_r2;
  int iVar1;
  qword local_18;
  qword local_10;
  qword local_8;
  
  iVar1 = in_r2 + 0x16cd0;
  HvpAquireSpinLock(iVar1);
  *(undefined *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x271) = param_1;
  FUN_000001e0(iVar1);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x0002583c)
// WARNING: Removing unreachable block (ram,0x00025868)
// WARNING: Removing unreachable block (ram,0x0002587c)

undefined8 FUN_00025760(undefined8 param_1,int param_2)

{
  longlong in_r2;
  int iVar2;
  undefined8 uVar1;
  longlong lVar3;
  undefined *puVar4;
  undefined *puVar5;
  longlong lVar6;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (param_2 == 1) {
    if (*(char *)((int)DWORD_ARRAY_00016a20 + (int)in_r2 + 0x270) == '\x01') {
      iVar2 = HvpPhysicalToReal(param_1,0x804);
      puVar5 = (undefined *)(iVar2 + 0x10c);
      lVar3 = in_r2 + 0x16b42;
      *(undefined4 *)(iVar2 + 0x104) =
           *(undefined4 *)((int)DWORD_ARRAY_00016a20 + (int)in_r2 + 0x138);
      *(undefined *)(iVar2 + 0x14) = *(undefined *)((int)DWORD_ARRAY_00016a20 + (int)in_r2 + 0x14c);
      lVar6 = 0x14;
      do {
        puVar4 = (undefined *)lVar3;
        lVar3 = lVar3 + 1;
        *puVar5 = *puVar4;
        puVar5 = puVar5 + 1;
        lVar6 = lVar6 + -1;
      } while (lVar6 != 0);
      puVar5 = (undefined *)(iVar2 + 8);
      lVar3 = in_r2 + 0x16b5c;
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
  longlong in_r2;
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = __Save_R12_29_thru_31();
  iVar1 = (int)in_r2;
  HvpAquireSpinLock(in_r2 + 0x16cd0);
  *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar1 + 0x280) = uVar2;
  *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar1 + 0x284) = param_2;
  FUN_000001e0(in_r2 + 0x16cd0);
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_000258f0(undefined8 param_1)

{
  undefined4 uVar1;
  longlong in_r2;
  longlong lVar2;
  undefined4 *puVar3;
  longlong lVar4;
  qword local_18;
  qword local_10;
  qword local_8;
  
  puVar3 = (undefined4 *)HvpPhysicalToReal(param_1,0x28);
  lVar2 = in_r2 + 0x16cd0;
  HvpAquireSpinLock(lVar2);
  in_r2 = in_r2 + 0x16ca8;
  lVar4 = 10;
  do {
    uVar1 = *puVar3;
    puVar3 = puVar3 + 1;
    *(undefined4 *)in_r2 = uVar1;
    in_r2 = in_r2 + 4;
    lVar4 = lVar4 + -1;
  } while (lVar4 != 0);
  FUN_000001e0(lVar2);
  return 0;
}



// WARNING: Removing unreachable block (ram,0x00025a08)
// WARNING: Removing unreachable block (ram,0x00025a10)

undefined8 FUN_00025970(void)

{
  dword dVar1;
  longlong in_r2;
  dword *pdVar2;
  longlong lVar3;
  longlong lVar4;
  dword local_50;
  dword local_4c;
  dword local_48;
  
  __Save_R12_29_thru_31();
  lVar3 = in_r2 + 0x16cd0;
  HvpAquireSpinLock(lVar3);
  pdVar2 = &local_50;
  in_r2 = in_r2 + 0x16ca8;
  lVar4 = 10;
  do {
    dVar1 = *pdVar2;
    pdVar2 = pdVar2 + 1;
    *(dword *)in_r2 = dVar1;
    in_r2 = in_r2 + 4;
    lVar4 = lVar4 + -1;
  } while (lVar4 != 0);
  FUN_00025138(1,1);
  FUN_000001e0(lVar3);
  return 0;
}



undefined8 FUN_00025a18(int param_1,undefined4 param_2)

{
  int iVar1;
  longlong in_r2;
  qword local_8;
  
  iVar1 = (int)in_r2;
  if (param_1 == 0) {
    *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar1 + 0x274) = param_2;
  }
  else {
    *(undefined *)((int)DWORD_ARRAY_0001000c + iVar1) = 0;
    *(undefined *)((int)DWORD_ARRAY_00016a20 + iVar1 + 0x270) = 0;
    memset(ZEXT48(DWORD_ARRAY_00016a20) + in_r2,0,0x270);
    *(undefined4 *)((int)DWORD_ARRAY_00016a20 + (int)in_r2 + 0x274) = 1;
  }
  FUN_000001e0(in_r2 + 0x16cd0);
  return 0;
}



undefined8 FUN_00025a90(undefined8 param_1,ulonglong param_2,ulonglong param_3)

{
  longlong in_r2;
  ulonglong uVar1;
  undefined *puVar2;
  undefined *puVar3;
  longlong lVar4;
  undefined8 uVar5;
  longlong lVar6;
  
  uVar1 = __Save_R12_29_thru_31();
  if (((uVar1 & 0xfff) == 0) && ((param_2 & 0xffffffff) == 0x10)) {
    lVar4 = in_r2 + 0x16cd0;
    HvpAquireSpinLock(lVar4);
    if (((param_3 & 0xffffffff) == 0) ||
       ((*(char *)((int)DWORD_ARRAY_0001000c + (int)in_r2) != '\0' &&
        (*(char *)((int)DWORD_ARRAY_00016a20 + (int)in_r2 + 0x270) != '\0')))) {
      puVar2 = (undefined *)HvpPhysicalToReal(uVar1,0x10);
      in_r2 = in_r2 + 0x10010;
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
    FUN_000001e0(lVar4);
  }
  else {
    uVar5 = 0xffffffffc8000087;
  }
  return uVar5;
}



void FUN_00025b50(undefined8 param_1,longlong param_2,undefined8 param_3)

{
  uint uVar1;
  longlong in_r2;
  longlong lVar2;
  word *pwVar3;
  undefined *puVar5;
  longlong lVar4;
  longlong lVar6;
  word local_1a0;
  word local_40;
  dword local_30;
  
  lVar2 = __Save_R12_28_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  XeCryptAesKey(&local_1a0,in_r2 + 0x10020);
  pwVar3 = &local_40;
  in_r2 = in_r2 + 0x10030;
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
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



ulonglong FUN_00025c20(undefined8 param_1,longlong param_2)

{
  byte bVar1;
  int in_r2;
  longlong lVar2;
  ulonglong uVar3;
  int iVar4;
  byte *pbVar5;
  longlong lVar6;
  longlong lVar7;
  
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
        lVar6 = *(longlong *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14) + 0x8a0;
        iVar4 = (int)lVar6;
        *(byte *)((uint)bVar1 + iVar4) = pbVar5[1];
        *(undefined4 *)(((uint)bVar1 + 2) * 4 + iVar4) = *(undefined4 *)(pbVar5 + 0xc);
        memcpy(((ulonglong)bVar1 + 1) * 0x20 + lVar6,lVar7,0x20);
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
  longlong lVar5;
  byte *pbVar6;
  undefined *puVar7;
  qword local_18;
  qword local_10;
  qword local_8;
  
  bVar1 = *param_2;
  if ((bVar1 < 6) && (param_2[1] < 0x10)) {
    lVar5 = *(longlong *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14) + 0x8a0;
    iVar2 = (int)lVar5;
    *(undefined *)((uint)bVar1 + iVar2) = 0xff;
    *(undefined4 *)(((uint)bVar1 + 2) * 4 + iVar2) = 0x103;
    memset(((ulonglong)bVar1 + 1) * 0x20 + lVar5,0,0x20);
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
    uVar3 = (undefined)(1 << (ulonglong)uVar2);
  }
  *(undefined *)(param_1 + 0x2f) = uVar3;
  *(byte *)(param_1 + 0x30) = bVar1 >> 4;
  return 0;
}



undefined8 FUN_00025e60(byte *param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  ulonglong uVar3;
  uint uVar4;
  ulonglong uVar5;
  
  if (((*param_1 & 0x3f) != 0x24) && ((*param_1 & 0x3f) != 0x23)) {
    *(undefined *)(param_2 + 1) = 0;
    return 0;
  }
  bVar1 = param_1[0x2e];
  if ((bVar1 == 0) || (bVar1 == 1)) {
    bVar2 = param_1[0x2f];
    uVar3 = (ulonglong)bVar2;
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
  dword local_30;
  
  iVar1 = __Save_R12_29_thru_31();
  iVar2 = *(int *)(iVar1 + 2);
  if (iVar2 == -1) {
    FUN_00020060(&local_30,4);
  }
  *(byte *)((int)param_2 + 1) = (byte)iVar2 & 0xf;
  FUN_00020060((int *)(iVar1 + 2),0x10);
  iVar2 = FUN_00025e60(iVar1,param_2);
  if (iVar2 == 0) {
    FUN_00025d08(iVar1);
  }
  return;
}



undefined8 FUN_00025fb0(longlong param_1,int param_2)

{
  uint uVar1;
  int in_r2;
  undefined8 uVar2;
  undefined *puVar3;
  longlong lVar4;
  longlong lVar5;
  char *pcVar6;
  longlong lVar7;
  qword local_8;
  
  lVar5 = *(longlong *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x24);
  pcVar6 = (char *)lVar5;
  if ((*pcVar6 == '\0') ||
     ((byte)(*(byte *)param_1 & 0x3f) !=
      (byte)((-((*(uint *)(pcVar6 + 0x110) & 1) != 0) & 5U) + 0x24))) {
    uVar2 = 0xffffffffc8000089;
  }
  else {
    lVar4 = param_1 + 2;
    uVar1 = *(uint *)lVar4;
    if ((ulonglong)uVar1 < (ulonglong)(*(uint *)(pcVar6 + 0x118) >> 5)) {
      lVar5 = (ulonglong)uVar1 * 0x20 + (ulonglong)*(uint *)(pcVar6 + 0x11c) + lVar5;
      lVar7 = 0x10;
      do {
        puVar3 = (undefined *)lVar5;
        lVar5 = lVar5 + 1;
        *(undefined *)lVar4 = *puVar3;
        lVar4 = lVar4 + 1;
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



undefined8 FUN_00026098(undefined8 param_1,longlong param_2)

{
  uint uVar1;
  uint uVar2;
  int in_r2;
  byte *pbVar4;
  undefined8 uVar3;
  byte *pbVar5;
  char cVar7;
  undefined *puVar6;
  longlong lVar8;
  byte *pbVar9;
  byte bVar10;
  longlong lVar11;
  longlong lVar12;
  char *pcVar13;
  longlong lVar14;
  dword local_40;
  
  pbVar4 = (byte *)__Save_R12_27_thru_31();
  lVar12 = *(longlong *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x24);
  pcVar13 = (char *)lVar12;
  if (*pcVar13 == '\0') {
    uVar3 = 0xffffffffc8000089;
  }
  else {
    uVar1 = *(uint *)(pcVar13 + 0x11c);
    uVar2 = *(uint *)(pcVar13 + 0x118) >> 5;
    FUN_00020060(&local_40,4);
    trapWord(6,(ulonglong)uVar2,0);
    lVar11 = (ulonglong)local_40 - (longlong)(int)(local_40 / uVar2) * (longlong)(int)uVar2;
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
    lVar8 = (lVar11 * 0x20 & 0x1fffffffe0U) + (ulonglong)uVar1 + lVar12;
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



undefined8 FUN_000261f8(undefined8 param_1,longlong param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  int iVar3;
  
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
  word local_90;
  word local_60;
  dword local_2c;
  
  __Save_R12_29_thru_31();
  HvpReleaseSpinLock((ulonglong)*(uint *)(in_r2 + 0x10000));
  return 0xffffffffc8000089;
}



// WARNING: Removing unreachable block (ram,0x0002644c)
// WARNING: Removing unreachable block (ram,0x0002645c)

undefined8 FUN_00026420(void)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  longlong in_r2;
  undefined8 uVar4;
  ulonglong uVar5;
  int iVar6;
  word *pwVar7;
  undefined *puVar9;
  longlong lVar8;
  longlong lVar10;
  longlong lVar11;
  longlong lVar12;
  longlong lVar13;
  longlong lVar14;
  qword local_1e0;
  dword local_1d4;
  word local_1d0;
  word local_70;
  word local_50;
  dword local_40;
  
  uVar4 = __Save_R12_27_thru_31();
  iVar3 = (int)in_r2;
  uVar1 = *(uint *)(iVar3 + 0x10000);
  memcpy(*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar3 + 0x24),uVar4,0x4000);
  lVar13 = *(longlong *)((int)DWORD_ARRAY_0001613c + iVar3 + 0x24);
  puVar2 = (undefined *)lVar13;
  if ((*(uint *)(puVar2 + 0x110) & 0x80000000) == 0) {
    in_r2 = in_r2 + 0x111b0;
  }
  else {
    in_r2 = in_r2 + 0x10970;
  }
  lVar11 = lVar13 + 0x100;
  XeCryptHmacSha(0x20,0x10,lVar11,0x40,0,0,0,0);
  uVar5 = FUN_000038d8(&local_70,lVar13,in_r2);
  if ((uVar5 & 0xffffffff) != 0) {
    lVar10 = 0x4000 - (ulonglong)*(uint *)(puVar2 + 0x11c);
    lVar12 = (ulonglong)*(uint *)(puVar2 + 0x11c) + lVar13;
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
  memset(*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar3 + 0x24),0,0x4000);
  FUN_00003830(8,0);
LAB_00026520:
  FUN_00003830(0x1000000,0);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar4;
}



// WARNING: Removing unreachable block (ram,0x0002665c)
// WARNING: Removing unreachable block (ram,0x0002664c)
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
  qword local_1b0;
  dword local_1a4;
  word local_1a0;
  word local_40;
  dword local_30;
  
  __Save_R12_28_thru_31();
  HvpReleaseSpinLock((ulonglong)*(uint *)(in_r2 + 0x10000));
  return 0xffffffffc8000089;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_000267b8(int param_1,ulonglong param_2,int param_3)

{
  undefined8 uVar1;
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
  longlong in_r2;
  int iVar1;
  qword local_8;
  
  FUN_00020060(in_r2 + 0x10020,0x10);
  FUN_00020060(in_r2 + 0x10030,0x10);
  iVar1 = (int)in_r2;
  FUN_00020060(in_r2 + 0x16a10,0x10);
  FUN_00003830(0,0x800);
  *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar1 + 0x280) = 0;
  *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar1 + 0x288) = 0;
  FUN_00025138(1,1);
  return;
}



undefined8 FUN_000268a0(undefined8 param_1,int param_2)

{
  uint uVar1;
  longlong in_r2;
  int iVar2;
  undefined8 uVar3;
  int iVar5;
  ulonglong uVar4;
  word *pwVar6;
  longlong lVar7;
  undefined *puVar8;
  undefined4 uVar9;
  longlong lVar10;
  byte bVar11;
  longlong lVar12;
  word local_1c0;
  word local_60;
  word local_50;
  word local_40;
  dword local_30;
  
  uVar3 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if (param_2 < 0) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8000080;
  }
  bVar11 = 0x28;
  if ((*(ushort *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + (int)in_r2 + 0x14) + 0x604) &
      0x200) != 0x200) {
    bVar11 = 0x3b;
  }
  iVar5 = HvpPhysicalToReal(uVar3,0x4a);
  lVar10 = in_r2 + 0x16cd0;
  HvpAquireSpinLock(lVar10);
  iVar2 = (int)in_r2;
  if (((*(byte *)(iVar5 + 8) & 0x3f) == bVar11) && (*(char *)(iVar5 + 9) == '0')) {
    XeCryptAesKey(&local_1c0,in_r2 + 0x10020);
    pwVar6 = &local_60;
    lVar7 = in_r2 + 0x10030;
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
       (iVar5 = XeCryptMemDiff(&local_40,in_r2 + 0x16a10,0x10), iVar5 == 0)) {
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
  *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x280) = uVar9;
  *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x284) = 0;
  FUN_000001e0(lVar10);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar3;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00026a10(undefined8 param_1)

{
  undefined uVar1;
  uint uVar2;
  longlong in_r2;
  int iVar4;
  undefined8 uVar3;
  word *pwVar5;
  undefined *puVar6;
  longlong lVar7;
  word local_190;
  word local_30;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  iVar4 = FUN_00025970(1);
  if (iVar4 == 0) {
    HvpReleaseSpinLock((ulonglong)uVar2);
    uVar3 = 0xffffffffc8000086;
  }
  else {
    iVar4 = HvpPhysicalToReal(param_1,0x2a);
    XeCryptAesKey(&local_190,in_r2 + 0x10020);
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
    memcpy(ZEXT48(DWORD_ARRAY_00016a20) + in_r2,iVar4 + 8,0x22);
    XeCryptAesCbc(&local_190,iVar4 + 10,0x10,in_r2 + 0x16a22,&local_30,0);
    *(undefined4 *)((int)DWORD_ARRAY_00016a20 + (int)lVar7 + 0x274) = 2;
    FUN_000001e0(lVar7 + 0x16cd0);
    HvpReleaseSpinLock((ulonglong)uVar2);
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
  longlong in_r2;
  undefined8 uVar5;
  int iVar6;
  undefined4 *puVar7;
  ulonglong uVar8;
  uint uVar9;
  longlong lVar10;
  undefined *puVar12;
  ulonglong uVar11;
  uint uVar13;
  uint uVar14;
  dword *pdVar15;
  ulonglong uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  byte bVar21;
  word *pwVar20;
  undefined4 uVar22;
  undefined8 uVar23;
  longlong lVar24;
  longlong lVar25;
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
    HvpReleaseSpinLock((ulonglong)uVar3);
    return 0xffffffffc8000086;
  }
  uVar5 = HvpPhysicalToReal(uVar5,0x804);
  memcpy(&local_860,uVar5,0x804);
  XeCryptAesKey(&local_9c0,in_r2 + 0x10020);
  pwVar20 = &local_50;
  lVar10 = in_r2 + 0x16a32;
  lVar24 = 0x10;
  do {
    puVar12 = (undefined *)lVar10;
    lVar10 = lVar10 + 1;
    *(undefined *)pwVar20 = *puVar12;
    pwVar20 = (word *)((int)pwVar20 + 1);
    lVar24 = lVar24 + -1;
  } while (lVar24 != 0);
  lVar10 = in_r2;
  XeCryptAesCbc(&local_9c0,&local_84b,0x650,&local_84b,&local_50,0);
  XeCryptRotSumSha(&local_85c,0x4cb,0,0,&local_40,0x14);
  iVar6 = XeCryptBnQwBeSigVerify
                    (&local_37d,&local_40,lVar10 + 0x103f8,
                     ZEXT48(&PTR_DWORD_ARRAY_00010750) + lVar10);
  if (iVar6 == 0) {
    lVar10 = lVar10 + 0x16ca8;
    pdVar15 = &local_9f0;
    lVar24 = 10;
    do {
      dVar4 = *pdVar15;
      pdVar15 = pdVar15 + 1;
      *(dword *)lVar10 = dVar4;
      lVar10 = lVar10 + 4;
      lVar24 = lVar24 + -1;
    } while (lVar24 != 0);
    uVar23 = 0xffffffffc8000082;
    goto LAB_00027274;
  }
  pwVar20 = &local_754;
  lVar24 = in_r2 + 0x16b42;
  lVar25 = 0x14;
  do {
    uVar1 = *(undefined *)pwVar20;
    pwVar20 = (word *)((int)pwVar20 + 1);
    *(undefined *)lVar24 = uVar1;
    lVar24 = lVar24 + 1;
    lVar25 = lVar25 + -1;
  } while (lVar25 != 0);
  pwVar20 = &local_858;
  lVar24 = in_r2 + 0x16b5c;
  lVar25 = 0xc;
  do {
    uVar1 = *(undefined *)pwVar20;
    pwVar20 = (word *)((int)pwVar20 + 1);
    *(undefined *)lVar24 = uVar1;
    lVar24 = lVar24 + 1;
    lVar25 = lVar25 + -1;
  } while (lVar25 != 0);
  iVar6 = (int)in_r2;
  *(dword *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x138) = local_75c;
  *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x148) = 0;
  *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x14c) = local_84c;
  memcpy(in_r2 + 0x16a42,&local_55c,0x100);
  XeCryptAesKey(&local_9c0,lVar10 + 0x10ea0);
  XeCryptAesCbc(&local_9c0,&local_558,0xfc,in_r2 + 0x16a46,&local_50,0);
  bVar21 = *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x23);
  uVar8 = (ulonglong)bVar21;
  uVar9 = (uint)bVar21;
  if (((*(char *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x22) == '\x02') && (bVar21 != 0)) &&
     (bVar21 < 0x16)) {
    uVar16 = 0;
    uVar19 = 0;
    uVar18 = 0;
    uVar19._3_1_ = *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x152) | 0xf8;
    uVar13 = 0;
    uVar11 = 0;
    *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x152) = (byte)uVar19;
    *(undefined *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x153) = 0;
    uVar17 = (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x155) & 3;
    *(undefined *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x155) = (char)uVar17;
    *(undefined *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x154) = 0;
    if (bVar21 != 0) {
      do {
        cVar2 = *(char *)(uVar18 * 0xc + iVar6 + 0x16a46);
        uVar9 = (uint)uVar16;
        if (cVar2 != '\x01') {
          if ((cVar2 != '\x14') && (cVar2 != '\x15')) {
            if ((cVar2 == '$') || (cVar2 == '%')) {
              uVar9 = (uint)uVar11;
              if (0xdf < (uVar9 & 0xe0)) {
                lVar10 = lVar10 + 0x16ca8;
                pdVar15 = &local_9f0;
                lVar24 = 10;
                do {
                  dVar4 = *pdVar15;
                  pdVar15 = pdVar15 + 1;
                  *(dword *)lVar10 = dVar4;
                  lVar10 = lVar10 + 4;
                  lVar24 = lVar24 + -1;
                } while (lVar24 != 0);
                goto LAB_0002726c;
              }
              uVar9 = uVar9 & 0x1f | (uVar9 & 0xe0) + 0x20 & 0xff;
              uVar11 = (ulonglong)uVar9;
              *(undefined *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x154) = (char)uVar9;
            }
            else {
              if (cVar2 == -0x20) {
                *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x152) =
                     (byte)(uVar18 << 3) | (byte)uVar19 & 7;
                *(undefined4 *)(uVar18 * 0xc + iVar6 + 0x16a4a) = 0;
                uVar11 = (ulonglong)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x154);
                uVar16 = (ulonglong)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x153);
                uVar19._3_1_ = *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x152);
                uVar8 = (ulonglong)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x23);
              }
            }
            goto LAB_00026e20;
          }
          if ((uVar9 & 7) < 7) {
            uVar9 = uVar9 & 0xf8 | uVar9 + 1 & 0xffffff07;
            goto LAB_00026e18;
          }
          lVar10 = lVar10 + 0x16ca8;
          pdVar15 = &local_9f0;
          lVar24 = 10;
          do {
            dVar4 = *pdVar15;
            pdVar15 = pdVar15 + 1;
            *(dword *)lVar10 = dVar4;
            lVar10 = lVar10 + 4;
            lVar24 = lVar24 + -1;
          } while (lVar24 != 0);
          goto LAB_0002726c;
        }
        if (0xf7 < (uVar9 & 0xf8)) {
          lVar10 = lVar10 + 0x16ca8;
          pdVar15 = &local_9f0;
          lVar24 = 10;
          do {
            dVar4 = *pdVar15;
            pdVar15 = pdVar15 + 1;
            *(dword *)lVar10 = dVar4;
            lVar10 = lVar10 + 4;
            lVar24 = lVar24 + -1;
          } while (lVar24 != 0);
          goto LAB_0002726c;
        }
        uVar9 = uVar9 & 7 | (uVar9 & 0xf8) + 8;
LAB_00026e18:
        uVar16 = (ulonglong)(uVar9 & 0xff);
        *(undefined *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x153) = (char)(uVar9 & 0xff);
LAB_00026e20:
        uVar19 = (uint)uVar16;
        uVar13 = (uint)uVar11;
        uVar9 = (uint)uVar8;
        uVar18 = uVar18 + 1 & 0xff;
      } while (uVar18 < uVar9);
      uVar17 = (uint)*(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x155);
    }
    if (((byte)uVar19 & 0xf8) == 0xf8) {
      lVar10 = lVar10 + 0x16ca8;
      pdVar15 = &local_9f0;
      lVar24 = 10;
      do {
        dVar4 = *pdVar15;
        pdVar15 = pdVar15 + 1;
        *(dword *)lVar10 = dVar4;
        lVar10 = lVar10 + 4;
        lVar24 = lVar24 + -1;
      } while (lVar24 != 0);
    }
    else {
      cVar2 = *(char *)((int)DWORD_ARRAY_00016a20 + (int)lVar10 + 0x271);
      *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x150) =
           *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x150) & 0x7f;
      *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x151) =
           *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x151) & 7;
      *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x156) =
           *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x156) & 0xc0;
      if (cVar2 != '\0') {
        if ((uVar13 >> 5) + (uVar19 & 7) < 4) {
          lVar10 = lVar10 + 0x16ca8;
          pdVar15 = &local_9f0;
          lVar24 = 10;
          do {
            dVar4 = *pdVar15;
            pdVar15 = pdVar15 + 1;
            *(dword *)lVar10 = dVar4;
            lVar10 = lVar10 + 4;
            lVar24 = lVar24 + -1;
          } while (lVar24 != 0);
          goto LAB_0002726c;
        }
        uVar17 = (uVar19 & 7) << 5 | uVar13 >> 3 & 0x1c;
        *(undefined *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x155) = (char)uVar17;
        *(undefined *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x156) = 0;
        *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x154) =
             (byte)(uVar19 >> 3) | (byte)uVar13 & 0xe0;
        *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x157) =
             *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x157) & 0xf |
             ((byte)(uVar17 >> 1) & 0x70) + ((byte)(uVar17 << 2) & 0x70);
LAB_000271a8:
        uVar8 = 0;
        if (uVar9 != 0) {
          do {
            uVar11 = (ulonglong)((int)uVar8 + 1U & 0xff);
            *(undefined *)((int)uVar8 + iVar6 + 0x16b78) = (char)uVar8;
            uVar8 = uVar11;
          } while (uVar11 < *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x23));
        }
        lVar10 = lVar10 + 0x10010;
        pwVar20 = &local_3fc;
        lVar24 = 0x10;
        do {
          uVar1 = *(undefined *)pwVar20;
          pwVar20 = (word *)((int)pwVar20 + 1);
          *(undefined *)lVar10 = uVar1;
          lVar10 = lVar10 + 1;
          lVar24 = lVar24 + -1;
        } while (lVar24 != 0);
        if (local_841 == 6) {
          uVar22 = 6;
        }
        puVar7 = (undefined4 *)HvpPhysicalToReal(param_2,4);
        *puVar7 = uVar22;
        goto LAB_00027274;
      }
      uVar18 = uVar13 >> 5;
      uVar14 = uVar19 & 7;
      if (uVar18 + uVar14 == 4) {
        uVar17 = uVar19 << 5 | uVar13 >> 3 & 0x1c | uVar17 & 3;
      }
      else {
        if (1 < uVar18) {
          uVar18 = 2;
        }
        if ((int)(4 - uVar18) <= (int)uVar14) {
          uVar14 = 4 - uVar18;
        }
        uVar17 = uVar14 << 5 | uVar18 << 2 | uVar17 & 3;
      }
      uVar17 = uVar17 & 0xff;
      bVar21 = (byte)uVar17;
      *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x155) = bVar21;
      if ((uVar17 >> 2 & 7) + (uVar17 >> 5) == 4) {
        uVar19 = uVar19 >> 3;
        if (2 < uVar19) {
          uVar19 = 3;
        }
        uVar19._3_1_ = (byte)uVar19 | (byte)uVar13 & 0xe0;
        *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x154) = (byte)uVar19;
        if (uVar19 != 0) {
          uVar19 = uVar17 >> 2 & 7;
          if (uVar19 == 2) {
            bVar21 = bVar21 & 0xfc | 1;
LAB_00027188:
            *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x155) = bVar21;
          }
          else {
            if ((uVar19 == 3) || (uVar19 == 4)) {
              bVar21 = bVar21 & 0xfc | 2;
              goto LAB_00027188;
            }
          }
          *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x157) =
               *(byte *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x157) & 0xf | 0x10;
          *(char *)((int)DWORD_ARRAY_00016a20 + iVar6 + 0x156) = ((byte)uVar19 - 1) * '@';
          goto LAB_000271a8;
        }
        lVar10 = lVar10 + 0x16ca8;
        pdVar15 = &local_9f0;
        lVar24 = 10;
        do {
          dVar4 = *pdVar15;
          pdVar15 = pdVar15 + 1;
          *(dword *)lVar10 = dVar4;
          lVar10 = lVar10 + 4;
          lVar24 = lVar24 + -1;
        } while (lVar24 != 0);
      }
      else {
        lVar10 = lVar10 + 0x16ca8;
        pdVar15 = &local_9f0;
        lVar24 = 10;
        do {
          dVar4 = *pdVar15;
          pdVar15 = pdVar15 + 1;
          *(dword *)lVar10 = dVar4;
          lVar10 = lVar10 + 4;
          lVar24 = lVar24 + -1;
        } while (lVar24 != 0);
      }
    }
  }
  else {
    lVar10 = lVar10 + 0x16ca8;
    pdVar15 = &local_9f0;
    lVar24 = 10;
    do {
      dVar4 = *pdVar15;
      pdVar15 = pdVar15 + 1;
      *(dword *)lVar10 = dVar4;
      lVar10 = lVar10 + 4;
      lVar24 = lVar24 + -1;
    } while (lVar24 != 0);
  }
LAB_0002726c:
  uVar23 = 0xffffffffc8000083;
LAB_00027274:
  FUN_00025a18(uVar23,3);
  HvpReleaseSpinLock((ulonglong)uVar3);
  return uVar23;
}



undefined8 FUN_00027298(undefined8 param_1,ulonglong param_2,undefined8 param_3,ulonglong param_4)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  dword dVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  longlong in_r2;
  undefined8 uVar11;
  int iVar12;
  byte *pbVar13;
  int *piVar14;
  short sVar15;
  short sVar17;
  word *pwVar16;
  byte *pbVar20;
  undefined *puVar21;
  longlong lVar18;
  longlong lVar19;
  undefined uVar23;
  dword *pdVar22;
  int iVar24;
  int iVar25;
  undefined8 uVar26;
  longlong lVar27;
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
  
  uVar11 = __Save_R12_22_thru_31();
  uVar3 = *(uint *)((int)in_r2 + 0x10000);
  uVar26 = 0;
  iVar25 = 0;
  iVar12 = FUN_00025970(4);
  if (iVar12 == 0) {
    HvpReleaseSpinLock((ulonglong)uVar3);
    return 0xffffffffc8000086;
  }
  iVar12 = (int)in_r2;
  uVar9 = (uint)(*(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x150) >> 2) & 0x1f;
  lVar19 = in_r2;
  pbVar13 = (byte *)HvpPhysicalToReal(uVar11,0x22);
  iVar24 = (int)param_2;
  if (((*pbVar13 & 0x3f) != 0x3e) || (pbVar13[1] != 0x20)) {
    lVar18 = lVar19 + 0x16ca8;
    pdVar22 = &local_230;
    lVar27 = 10;
    do {
      dVar4 = *pdVar22;
      pdVar22 = pdVar22 + 1;
      *(dword *)lVar18 = dVar4;
      lVar18 = lVar18 + 4;
      lVar27 = lVar27 + -1;
    } while (lVar27 != 0);
    uVar26 = 0xffffffffc8000080;
    goto LAB_000276b4;
  }
  if ((*(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x150) & 0x80) != 0) {
    iVar25 = 1;
    if ((iVar24 < 0) ||
       ((*(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x156) & 0xf) <
        *(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x157) >> 4)) {
      uVar23 = 0;
      uVar26 = 0xffffffffc8000084;
    }
    else {
      uVar23 = 1;
    }
    *(undefined *)((int)DWORD_ARRAY_00016a20 + (int)lVar19 + 0x270) = uVar23;
    goto LAB_000276b4;
  }
  if (iVar24 < 0) {
    if ((param_2 & 0xffffffff) != 0xc000009c) {
      uVar26 = 0xffffffffc8000084;
      goto LAB_000276b4;
    }
  }
  else {
    if ((param_2 & 0xffffffff) != 0xc000009c) {
      iVar6 = (uint)(*(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x152) >> 3) * 0xc;
      iVar25 = 0;
      iVar7 = (int)((ulonglong)uVar9 * 0xc);
      *(uint *)(iVar6 + iVar12 + 0x16a4a) =
           (uint)*(byte *)(iVar7 + iVar12 + 0x16a47) << 0x18 |
           *(uint *)(iVar6 + iVar12 + 0x16a4a) >> 8;
      XeCryptAesKey(&local_1d0,lVar19 + 0x10020);
      pbVar20 = pbVar13 + 0x12;
      pwVar16 = &local_70;
      lVar18 = 0x10;
      do {
        bVar1 = *pbVar20;
        pbVar20 = pbVar20 + 1;
        *(byte *)pwVar16 = bVar1;
        pwVar16 = (word *)((int)pwVar16 + 1);
        lVar18 = lVar18 + -1;
      } while (lVar18 != 0);
      XeCryptAesCbc(&local_1d0,pbVar13 + 2,0x10,&local_1fe,&local_70,0);
      lVar18 = (ulonglong)uVar9 * 0xc + in_r2 + 0x16a46;
      bVar1 = *(byte *)lVar18;
      if ((bVar1 & 0x20) == 0) {
        if (*(dword *)(iVar7 + iVar12 + 0x16a4e) != local_1f4) {
          pdVar22 = &local_224;
          lVar27 = 0xc;
          do {
            puVar21 = (undefined *)lVar18;
            lVar18 = lVar18 + 1;
            *(undefined *)pdVar22 = *puVar21;
            pdVar22 = (dword *)((int)pdVar22 + 1);
            lVar27 = lVar27 + -1;
          } while (lVar27 != 0);
          pdVar22 = &local_230;
          lVar18 = lVar19 + 0x16ca8;
          lVar27 = 10;
          do {
            dVar4 = *pdVar22;
            pdVar22 = pdVar22 + 1;
            *(dword *)lVar18 = dVar4;
            lVar18 = lVar18 + 4;
            lVar27 = lVar27 + -1;
          } while (lVar27 != 0);
          goto LAB_00027640;
        }
      }
      else {
        bVar2 = *(byte *)(iVar7 + iVar12 + 0x16a48);
        uVar5 = *(uint *)(iVar7 + iVar12 + 0x16a4e);
        uVar10 = (local_1f4 >> 0x10 & 0xff) << 8;
        sVar15 = (short)uVar5;
        sVar17 = sVar15 - (ushort)bVar2;
        sVar15 = sVar15 + (ushort)bVar2;
        uVar8 = uVar10 | local_1f4 >> 0x18;
        if (sVar17 < 0) {
          if (uVar8 < 0xb5) {
            sVar17 = 0;
          }
          else {
            sVar17 = sVar17 + 0x168;
            sVar15 = 0x168;
          }
        }
        if (((((uVar5 ^ (local_1f4 << 0x18 | (local_1f4 >> 8 & 0xff) << 0x10 | uVar10 |
                        local_1f4 >> 0x18)) & 0xffff0000) != 0) || ((int)uVar8 < (int)sVar17)) ||
           ((int)sVar15 < (int)uVar8)) {
          pdVar22 = &local_224;
          lVar27 = 0xc;
          do {
            puVar21 = (undefined *)lVar18;
            lVar18 = lVar18 + 1;
            *(undefined *)pdVar22 = *puVar21;
            pdVar22 = (dword *)((int)pdVar22 + 1);
            lVar27 = lVar27 + -1;
          } while (lVar27 != 0);
          pdVar22 = &local_230;
          lVar18 = lVar19 + 0x16ca8;
          lVar27 = 10;
          do {
            dVar4 = *pdVar22;
            pdVar22 = pdVar22 + 1;
            *(dword *)lVar18 = dVar4;
            lVar18 = lVar18 + 4;
            lVar27 = lVar27 + -1;
          } while (lVar27 != 0);
LAB_00027640:
          uVar26 = 0xffffffffc8000084;
        }
      }
      if ((bVar1 != 1) && (2499999 < param_4)) {
        bVar1 = *(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x156);
        *(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x156) = bVar1 & 0xf0 | bVar1 + 1 & 0xf;
      }
      goto LAB_000276b4;
    }
  }
  bVar1 = *(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x156);
  uVar26 = 0xffffffffc8000084;
  if (*(char *)(uVar9 * 0xc + iVar12 + 0x16a46) == '\x01') {
    if ((bVar1 & 0xc0) != 0) {
      uVar26 = 0;
      *(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x156) =
           ((bVar1 >> 6) - 1) * '@' | bVar1 & 0x3f;
    }
  }
  else {
    bVar2 = (bVar1 & 0xf0) + 0x10 & 0x30;
    *(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x156) = bVar2 | bVar1 & 0xcf;
    if (bVar2 < 0x21) {
      if ((*(byte *)(uVar9 * 0xc + iVar12 + 0x16a46) & 0x20) == 0) {
        uVar26 = 0;
      }
      else {
        bVar1 = *(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x155);
        if ((bVar1 & 3) != 0) {
          uVar26 = 0;
          *(byte *)((int)DWORD_ARRAY_00016a20 + iVar12 + 0x155) = bVar1 & 0xfc | bVar1 - 1 & 3;
        }
      }
    }
  }
LAB_000276b4:
  if ((iVar24 < 0) && ((int)uVar26 != 0)) {
    lVar18 = (ulonglong)uVar9 * 0xc + in_r2 + 0x16a46;
    pwVar16 = &local_220;
    lVar27 = 0xc;
    do {
      puVar21 = (undefined *)lVar18;
      lVar18 = lVar18 + 1;
      *(undefined *)pwVar16 = *puVar21;
      pwVar16 = (word *)((int)pwVar16 + 1);
      lVar27 = lVar27 + -1;
    } while (lVar27 != 0);
    pdVar22 = &local_230;
    lVar19 = lVar19 + 0x16ca8;
    lVar18 = 10;
    do {
      dVar4 = *pdVar22;
      pdVar22 = pdVar22 + 1;
      *(dword *)lVar19 = dVar4;
      lVar19 = lVar19 + 4;
      lVar18 = lVar18 + -1;
    } while (lVar18 != 0);
  }
  piVar14 = (int *)HvpPhysicalToReal(param_3,4);
  *piVar14 = iVar25;
  FUN_00025a18(uVar26,(ulonglong)(-(uint)(iVar25 != 0) & 2) + 3);
  HvpReleaseSpinLock((ulonglong)uVar3);
  return uVar26;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00027778(void)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  int in_r2;
  undefined8 uVar4;
  uint uVar5;
  byte bVar6;
  qword local_10;
  qword local_8;
  
  if ((((*(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x154) & 0x1f) == 0) &&
      (bVar6 = *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x155), (bVar6 & 0xe0) == 0)) &&
     ((bVar6 & 0x1c) == 0)) {
    uVar4 = 0;
    *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x150) =
         *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x152) >> 1 & 0xfc |
         *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x150) & 0x83 | 0x80;
    *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x151) =
         *(char *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x23) << 3 |
         *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x151) & 7;
  }
  else {
    bVar6 = *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x23);
    bVar2 = *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x151) >> 3;
    if ((bVar2 != bVar6) && (bVar2 < bVar6)) {
      do {
        uVar5 = FUN_00025210();
        bVar6 = *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x151);
        uVar3 = ((uint)bVar6 & 0xfffffff8) + 8 & 0xff;
        *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x150) =
             (byte)((uVar5 & 0x1f) << 2) |
             *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x150) & 0x83;
        *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x151) = bVar6 & 7 | (byte)uVar3;
        cVar1 = *(char *)((uVar5 & 0x1f) * 0xc + in_r2 + 0x16a46);
        if ((cVar1 == '\x01') &&
           (bVar6 = *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x154), (bVar6 & 0x1f) != 0)) {
          *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x154) = bVar6 & 0xe0 | bVar6 - 1 & 0x1f;
          return 0;
        }
        bVar6 = *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x155);
        if (((cVar1 == '\x14') && ((bVar6 & 0xe0) != 0)) ||
           ((cVar1 == '\x15' && ((bVar6 & 0xe0) != 0)))) {
          bVar6 = ((bVar6 >> 5) - 1) * ' ' | bVar6 & 0x1f;
LAB_00027908:
          *(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x155) = bVar6;
          return 0;
        }
        if (((cVar1 == '$') && ((bVar6 & 0x1c) != 0)) || ((cVar1 == '%' && ((bVar6 & 0x1c) != 0))))
        {
          bVar6 = ((bVar6 >> 2) - 1) * '\x04' & 0x1c | bVar6 & 0xe3;
          goto LAB_00027908;
        }
      } while ((ulonglong)(uVar3 >> 3) <
               (ulonglong)*(byte *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x23));
    }
    uVar4 = 0xffffffffc8000084;
  }
  return uVar4;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00027928(undefined8 param_1)

{
  dword dVar1;
  int iVar2;
  longlong in_r2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  dword *pdVar6;
  undefined8 uVar7;
  longlong lVar8;
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
  if (*(char *)((int)DWORD_ARRAY_00016a20 + iVar3 + 0x270) == '\0') {
    in_r2 = in_r2 + 0x16ca8;
    pdVar6 = &local_40;
    lVar8 = 10;
    do {
      dVar1 = *pdVar6;
      pdVar6 = pdVar6 + 1;
      *(dword *)in_r2 = dVar1;
      in_r2 = in_r2 + 4;
      lVar8 = lVar8 + -1;
    } while (lVar8 != 0);
    uVar7 = 0xffffffffc8000084;
  }
  else {
    iVar2 = *(int *)((int)DWORD_ARRAY_00016a20 + iVar3 + 0x148);
    if (iVar2 == 0) {
      uVar5 = *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar3 + 0x138);
    }
    else {
      if (iVar2 == 1) {
        uVar5 = *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar3 + 0x260);
      }
      else {
        if (iVar2 != 2) {
          pdVar6 = &local_40;
          in_r2 = in_r2 + 0x16ca8;
          lVar8 = 10;
          do {
            dVar1 = *pdVar6;
            pdVar6 = pdVar6 + 1;
            *(dword *)in_r2 = dVar1;
            in_r2 = in_r2 + 4;
            lVar8 = lVar8 + -1;
          } while (lVar8 != 0);
          uVar7 = 0xffffffffc8000085;
          *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar3 + 0x148) = 0;
          goto LAB_00027a44;
        }
        uVar5 = *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar3 + 0x264);
      }
    }
    *puVar4 = uVar5;
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
  longlong in_r2;
  int iVar3;
  undefined8 uVar4;
  int iVar5;
  undefined4 *puVar6;
  dword *pdVar7;
  longlong lVar8;
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
    in_r2 = in_r2 + 0x16ca8;
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
    iVar1 = *(int *)((int)DWORD_ARRAY_00016a20 + iVar3 + 0x148);
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
          *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar3 + 0x148) = 0;
        }
      }
    }
    if ((int)uVar4 == 0) goto LAB_00027cb8;
    pdVar7 = &local_60;
    in_r2 = in_r2 + 0x16ca8;
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
    *(undefined4 *)((int)DWORD_ARRAY_00016a20 + iVar3 + 0x148) = 0;
    *(undefined *)((int)DWORD_ARRAY_0001000c + iVar5) = 0;
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
  longlong in_r2;
  int iVar5;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined4 *puVar6;
  longlong lVar7;
  undefined *puVar8;
  word *pwVar9;
  dword *pdVar10;
  longlong lVar11;
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
    HvpReleaseSpinLock((ulonglong)uVar1);
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
      lVar7 = in_r2 + 0x16a32;
      lVar11 = 0x10;
      do {
        puVar8 = (undefined *)lVar7;
        lVar7 = lVar7 + 1;
        *(undefined *)pwVar9 = *puVar8;
        pwVar9 = (word *)((int)pwVar9 + 1);
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
      pwVar9 = &local_30;
      lVar7 = in_r2 + 0x16a32;
      lVar11 = 0x10;
      do {
        puVar8 = (undefined *)lVar7;
        lVar7 = lVar7 + 1;
        *(undefined *)pwVar9 = *puVar8;
        pwVar9 = (word *)((int)pwVar9 + 1);
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
      XeCryptAesKey(&local_190,in_r2 + 0x10020);
      XeCryptAesCbc(&local_190,&uStack494,0x10,&uStack494,&local_30,1);
      uVar4 = HvpPhysicalToReal(param_1,0x22);
      memcpy(uVar4,&local_1f0,0x22);
    }
    else {
      lVar7 = in_r2 + 0x16ca8;
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
    HvpReleaseSpinLock((ulonglong)uVar1);
  }
  return uVar3;
}



void FUN_00027ee0(void)

{
  int in_r2;
  undefined8 uVar1;
  qword local_8;
  
  uVar1 = FUN_000002c8();
  *(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x7a0) = uVar1;
  return;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Could not reconcile some variable overlaps

void FUN_00027f08(void)

{
  int in_r2;
  undefined2 uVar1;
  undefined2 uVar2;
  longlong lVar3;
  int iVar4;
  qword local_20;
  qword local_10;
  qword local_8;
  
  lVar3 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x718);
  uVar1 = 0xffff;
  if (lVar3 != 0) {
    uVar1 = *(undefined2 *)((int)lVar3 + 0x156);
  }
  uVar2 = 0xffff;
  lVar3 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x708);
  if (lVar3 != 0) {
    uVar2 = *(undefined2 *)((int)lVar3 + 0x156);
  }
  iVar4 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248);
  if (*(char *)(iVar4 + 0x18) == '\0') {
    local_20._4_2_ = 0xffff;
    local_20._6_2_ = 0xffff;
  }
  else {
    local_20._4_2_ = *(undefined2 *)(iVar4 + 0x1c);
    local_20._6_2_ = *(undefined2 *)(iVar4 + 0x1e);
  }
  iVar4 = in_r2 + 0x16144;
  HvpAquireSpinLock(iVar4);
  *(undefined8 *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14) + 0x648) =
       CONCAT62(CONCAT42(CONCAT22(uVar1,uVar2),local_20._4_2_),local_20._6_2_);
  FUN_000001e0(iVar4);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00027fc8(int param_1)

{
  uint uVar1;
  int in_r2;
  longlong lVar2;
  longlong lVar3;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if ((param_1 != 0) &&
     (lVar3 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x708), lVar3 != 0)) {
    uVar1 = *(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x710);
    if (uVar1 != 0) {
      lVar2 = (longlong)param_1 + lVar3;
      if (param_1 < 1) {
        memcpy(lVar2);
      }
      else {
        FUN_0000adc0(lVar2,lVar3,(ulonglong)uVar1);
      }
      *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x708) =
           (longlong)param_1 + *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x708);
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
  ulonglong uVar5;
  longlong lVar6;
  dword *pdVar7;
  word *pwVar8;
  undefined *puVar9;
  int *piVar10;
  longlong lVar11;
  longlong lVar12;
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
  lVar6 = *(longlong *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x104);
  uVar4 = ~(uint)*(ushort *)((int)param_1 + 6) >> 0xf & 1;
  if (iVar3 == 0x44414550) {
    pdVar7 = &DWORD_00000054;
    piVar10 = (int *)((int)&PTR_DWORD_ARRAY_00010750 + in_r2);
    lVar11 = 0x10;
    do {
      uVar1 = *(undefined *)pdVar7;
      pdVar7 = (dword *)((int)pdVar7 + 1);
      *param_2 = uVar1;
      param_2 = param_2 + 1;
      lVar11 = lVar11 + -1;
    } while (lVar11 != 0);
  }
  else {
    if (iVar3 == 0x4441454c) {
      if (uVar4 == 0) {
        piVar10 = (int *)((int)DWORD_ARRAY_00010760 + in_r2 + 800);
      }
      else {
        piVar10 = (int *)((int)DWORD_ARRAY_00010ed4 + in_r2 + 0xbc);
      }
      lVar11 = lVar6 + 0xf0;
      lVar12 = 0x10;
      do {
        puVar9 = (undefined *)lVar11;
        lVar11 = lVar11 + 1;
        *param_2 = *puVar9;
        param_2 = param_2 + 1;
        lVar12 = lVar12 + -1;
      } while (lVar12 != 0);
    }
    else {
      if (iVar3 != 0x4441454d) goto LAB_00028250;
      if (uVar4 == 0) {
        piVar10 = (int *)((int)DWORD_ARRAY_00010760 + in_r2 + 0x210);
      }
      else {
        piVar10 = (int *)((int)DWORD_ARRAY_000110b4 + in_r2 + 0xfc);
      }
      lVar11 = 0x10;
      do {
        *param_2 = 0;
        param_2 = param_2 + 1;
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
    }
  }
  if ((*piVar10 == 0x20) || (*piVar10 == 0x40)) {
    if ((*(ushort *)((int)param_1 + 6) & 2) != 0) {
      lVar11 = lVar6 + 0x9ca;
      pwVar8 = &local_40;
      lVar12 = 5;
      do {
        puVar9 = (undefined *)lVar11;
        lVar11 = lVar11 + 1;
        *(undefined *)pwVar8 = *puVar9;
        pwVar8 = (word *)((int)pwVar8 + 1);
        lVar12 = lVar12 + -1;
      } while (lVar12 != 0);
      lVar6 = lVar6 + 0x9cf;
      pwVar8 = &local_3b;
      lVar11 = 0xb;
      do {
        puVar9 = (undefined *)lVar6;
        lVar6 = lVar6 + 1;
        *(undefined *)pwVar8 = *puVar9;
        pwVar8 = (word *)((int)pwVar8 + 1);
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
    }
    XeCryptHmacSha(&local_40,0x10,param_1,0x20,0,0,0,0);
    uVar5 = FUN_000038d8(&local_30,param_1 + 8,piVar10);
    if ((uVar5 & 0xffffffff) == 0) {
      HvpReleaseSpinLock((ulonglong)uVar2);
      return 0xffffffffc8000093;
    }
    HvpReleaseSpinLock((ulonglong)uVar2);
    return 0;
  }
LAB_00028250:
  HvpReleaseSpinLock((ulonglong)uVar2);
  return 0xffffffffc8000092;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00028278(longlong param_1,undefined8 param_2)

{
  uint uVar1;
  int in_r2;
  int iVar3;
  undefined8 uVar2;
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
    HvpReleaseSpinLock((ulonglong)uVar1);
    uVar2 = 0;
  }
  else {
    HvpReleaseSpinLock((ulonglong)uVar1);
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
  word local_30;
  dword local_1c;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = *(uint *)(in_r2 + 0x10000);
  XeCryptSha(param_1 + 0x150,(ulonglong)*(ushort *)(param_1 + 4) - 0x150,0,0,0,0,&local_30,0x14);
  iVar3 = XeCryptMemDiff(&local_30,param_1 + 0xc,0x14);
  if (iVar3 == 0) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    uVar2 = 0;
  }
  else {
    HvpReleaseSpinLock((ulonglong)uVar1);
    uVar2 = 0xffffffffc8000091;
  }
  return uVar2;
}



undefined8 FUN_000283b0(undefined8 param_1,undefined8 param_2,ulonglong param_3)

{
  ushort uVar1;
  uint uVar2;
  int in_r2;
  longlong lVar3;
  undefined8 uVar4;
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
    HvpReleaseSpinLock((ulonglong)uVar2);
    return uVar4;
  }
  XeCryptAesKey(&local_1c0,param_2);
  XeCryptAesCbc(&local_1c0,lVar3._4_4_ + 0x130,0x10,lVar3 + 0x130,&local_60,param_3);
  XeCryptAesCbc(&local_1c0,lVar3._4_4_ + 0x140,0x10,lVar3 + 0x140,&local_60,param_3);
  XeCryptAesCbc(&local_1c0,lVar3._4_4_ + 0x150,(ulonglong)uVar1 - 0x150,lVar3 + 0x150,&local_60,
                param_3);
  if ((param_3 & 0xffffffff) == 0) {
    uVar4 = FUN_00028278(lVar3._4_4_,param_2);
    if ((int)uVar4 != 0) {
      HvpReleaseSpinLock((ulonglong)uVar2);
      return uVar4;
    }
    uVar4 = FUN_00028318(lVar3._4_4_);
    if ((int)uVar4 != 0) {
      HvpReleaseSpinLock((ulonglong)uVar2);
      return uVar4;
    }
  }
  HvpReleaseSpinLock((ulonglong)uVar2);
  return 0;
}



undefined8 FUN_00028518(undefined8 param_1,ulonglong param_2)

{
  uint uVar1;
  int in_r2;
  int iVar3;
  undefined8 uVar2;
  word local_40;
  dword local_30;
  
  iVar3 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  if (0x14f < (param_2 & 0xffffffff)) {
    uVar2 = FUN_00028048(iVar3,&local_40);
    if ((int)uVar2 != 0) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return uVar2;
    }
    if (*(short *)(iVar3 + 8) != 1) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8000094;
    }
    if ((ulonglong)*(ushort *)(iVar3 + 4) <= (param_2 & 0xffffffff)) {
      uVar2 = FUN_000283b0(iVar3,&local_40,0);
      HvpReleaseSpinLock((ulonglong)uVar1);
      return uVar2;
    }
  }
  HvpReleaseSpinLock((ulonglong)uVar1);
  return 0xffffffffc8000091;
}



undefined8 FUN_000285d0(int param_1,longlong param_2)

{
  int in_r2;
  undefined8 uVar1;
  ulonglong uVar2;
  qword local_8;
  
  if (*(longlong *)(param_1 + 0x130) == param_2) {
    uVar2 = (ulonglong)*(byte *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x240);
    if ((ulonglong)*(byte *)(param_1 + 0x13f) == uVar2) {
      FUN_00003830(0x200000,0);
    }
    else {
      if ((ulonglong)*(byte *)(param_1 + 0x13f) != uVar2 + 1) goto LAB_00028630;
    }
    uVar1 = 0;
  }
  else {
LAB_00028630:
    uVar1 = 0xffffffffc8000091;
  }
  return uVar1;
}



void FUN_00028648(undefined8 param_1,undefined8 param_2)

{
  int in_r2;
  int iVar2;
  ulonglong uVar1;
  ushort *puVar3;
  undefined8 *puVar4;
  qword local_40;
  dword local_34;
  
  iVar2 = __Save_R12_28_thru_31();
  puVar3 = (ushort *)(iVar2 + 0x120);
  puVar4 = (undefined8 *)(iVar2 + 0x130);
  FUN_00020060(puVar3,0x10);
  *puVar3 = *puVar3 | 1;
  FUN_00020060(puVar4,0x10);
  *puVar4 = param_2;
  *(undefined *)(iVar2 + 0x13f) = *(undefined *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x240);
  uVar1 = func_0x00002b78();
  if ((uVar1 & 0xffffffff) != 0) {
    *(char *)(iVar2 + 0x13f) = *(char *)(iVar2 + 0x13f) + '\x01';
  }
  XeCryptHmacSha(0x20,0x10,puVar3,0x10,puVar4,0x10,0,0);
  return;
}



undefined8 FUN_000286f0(int *param_1,int param_2)

{
  int in_r2;
  longlong lVar1;
  
  lVar1 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 800);
  if ((lVar1 != 0) && (param_2 != 0)) {
    do {
      if (*param_1 == *(int *)((int)lVar1 + 0xc)) {
        return 1;
      }
      param_2 = param_2 + -1;
      param_1 = param_1 + 1;
    } while (param_2 != 0);
  }
  return 0;
}



longlong FUN_00028738(void)

{
  ushort uVar1;
  ushort *puVar2;
  longlong in_r2;
  longlong lVar3;
  ulonglong uVar4;
  longlong lVar5;
  int iVar6;
  longlong lVar7;
  ulonglong uVar8;
  
  lVar3 = __Save_R12_26_thru_31();
  uVar1 = *(ushort *)((int)lVar3 + 2);
  uVar8 = (ulonglong)uVar1;
  lVar3 = lVar3 + 0x10;
  lVar7 = 0;
  if (uVar1 != 0) {
    do {
      puVar2 = (ushort *)lVar3;
      if ((puVar2[2] & 2) == 0) {
        lVar5 = lVar7;
        if ((lVar7 == 0) && (lVar5 = in_r2 + 0x10010, (puVar2[2] & 1) != 0)) {
          lVar5 = *(longlong *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x310);
        }
        if ((lVar5 != 0) && (iVar6 = XeCryptMemDiff(lVar5,lVar3 + 0x10,0x10), iVar6 == 0)) {
          return lVar3;
        }
      }
      else {
        uVar4 = FUN_000286f0(lVar3 + 0x20,(ulonglong)puVar2[1]);
        if ((uVar4 & 0xffffffff) != 0) {
          lVar7 = in_r2 + 0x10420;
        }
      }
      uVar8 = uVar8 - 1;
      lVar3 = (ulonglong)*puVar2 + lVar3;
    } while ((uVar8 & 0xffffffff) != 0);
  }
  return 0;
}



// WARNING: Removing unreachable block (ram,0x00028840)

undefined8 FUN_00028808(undefined8 param_1,ulonglong param_2,undefined8 param_3)

{
  ushort uVar1;
  ushort uVar2;
  int in_r2;
  longlong lVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  longlong lVar6;
  ulonglong uVar7;
  
  lVar3 = __Save_R12_23_thru_31();
  FUN_00003830(0x2000000,0);
  if (((param_2 & 0xffffffff) < ZEXT48(&BYTE_00010001)) && (0x14f < (param_2 & 0xffffffff))) {
    uVar1 = *(ushort *)((int)lVar3 + 4);
    uVar7 = (ulonglong)uVar1;
    if (uVar7 + 0x150 <= (param_2 & 0xffffffff)) {
      lVar6 = uVar7 + lVar3;
      uVar2 = *(ushort *)((int)lVar6 + 4);
      uVar5 = (ulonglong)uVar2 + uVar7;
      if (uVar5 <= (param_2 & 0xffffffff)) {
        uVar4 = FUN_00028518(lVar3,uVar7);
        if ((int)uVar4 != 0) {
          return uVar4;
        }
        if (((*(ushort *)((int)lVar3 + 6) & 1) == 0) && ((*(ushort *)(lVar3 + 0x120) & 1) != 0)) {
          uVar4 = FUN_00028518(lVar6,(ulonglong)uVar2);
          if ((int)uVar4 != 0) {
            return uVar4;
          }
          if (((*(ushort *)((int)lVar6 + 6) & 1) != 0) && ((*(ushort *)(lVar6 + 0x120) & 1) != 0)) {
            uVar4 = FUN_000285d0(lVar3,param_3);
            if ((int)uVar4 != 0) {
              return uVar4;
            }
            uVar4 = FUN_000285d0(lVar6,param_3);
            if ((int)uVar4 != 0) {
              return uVar4;
            }
            memset(lVar3 + 0x120,0,0x30);
            memset(lVar6 + 0x120,0,0x30);
            lVar6 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x7a0);
            *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x718) = lVar6;
            *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x708) = uVar7 + lVar6;
            *(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x704) = (uint)uVar1;
            *(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x710) = (uint)uVar2;
            memcpy(lVar6,lVar3,uVar5);
            return 0;
          }
        }
      }
    }
  }
  return 0xffffffffc8000091;
}



undefined8 FUN_000289a0(undefined8 param_1,ulonglong param_2,undefined8 param_3)

{
  uint uVar1;
  uint uVar2;
  int in_r2;
  longlong lVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  lVar3 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x704);
  lVar5 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x718);
  uVar2 = *(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x710);
  if ((((lVar5 == 0) || (*(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x708) == 0)) ||
      (uVar1 == 0)) || (uVar2 == 0)) {
    uVar4 = 0xffffffffc8000096;
  }
  else {
    if ((param_2 & 0xffffffff) < ((ulonglong)uVar2 + (ulonglong)uVar1 & 0xffffffff)) {
      uVar4 = 0xffffffffc8000003;
    }
    else {
      memcpy(lVar3,lVar5);
      FUN_00028648(lVar3,param_3);
      FUN_00028648((ulonglong)uVar1 + lVar3,param_3);
      uVar4 = FUN_000283b0(lVar3,0,1);
      if ((int)uVar4 == 0) {
        uVar4 = FUN_000283b0((ulonglong)uVar1 + lVar3,0,1);
      }
    }
  }
  return uVar4;
}



undefined8 FUN_00028a78(void)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  ushort uVar4;
  int in_r2;
  int iVar5;
  int iVar7;
  undefined8 uVar6;
  ulonglong uVar8;
  longlong lVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  
  iVar7 = __Save_R12_27_thru_31();
  uVar6 = FUN_00028518();
  if ((int)uVar6 == 0) {
    if ((*(ushort *)(iVar7 + 0x120) & 1) == 0) {
      uVar1 = *(ushort *)(iVar7 + 4);
      uVar11 = (ulonglong)uVar1;
      uVar4 = ~*(ushort *)(iVar7 + 6) & 1;
      uVar2 = *(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x704);
      uVar3 = uVar2;
      if (uVar4 != 0) {
        uVar3 = *(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x710);
      }
      if ((0x10000 - (ulonglong)uVar3 & 0xffffffff) < uVar11) {
        uVar6 = 0xffffffffc8000003;
      }
      else {
        if (uVar4 == 0) {
          lVar9 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x708);
        }
        else {
          lVar9 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x718);
        }
        if (lVar9 == 0) {
          uVar8 = 0;
          uVar10 = 0xffffffffffffffff;
        }
        else {
          uVar8 = (ulonglong)*(ushort *)((int)lVar9 + 4);
          uVar10 = (ulonglong)*(ushort *)((int)lVar9 + 0x156);
        }
        if ((uVar10 & 0xffffffff) < (ulonglong)*(ushort *)(iVar7 + 0x156)) {
          if (uVar4 == 0) {
            *(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x710) = (uint)uVar1;
            lVar9 = (ulonglong)uVar2 + *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x7a0);
            *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x708) = lVar9;
          }
          else {
            iVar5 = in_r2;
            FUN_00027fc8(uVar11 - uVar8);
            *(uint *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x704) = (uint)uVar1;
            lVar9 = *(longlong *)((int)DWORD_ARRAY_00016260 + iVar5 + 0x7a0);
            *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x718) = lVar9;
          }
          memcpy(lVar9,iVar7,uVar11);
          memset(lVar9 + 0x120,0,0x30);
          uVar6 = 0;
        }
        else {
          uVar6 = 0xffffffffc8000095;
        }
      }
    }
    else {
      uVar6 = 0xffffffffc8000091;
    }
  }
  return uVar6;
}



undefined8 FUN_00028bc8(ulonglong param_1)

{
  int iVar1;
  int in_r2;
  undefined8 uVar2;
  ushort uStack00000014;
  undefined2 uStack00000016;
  
  iVar1 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248);
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
  if ((param_1 & 0xffff) <= (ulonglong)*(ushort *)(iVar1 + 0x1e)) {
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
  ulonglong uVar9;
  longlong in_r2;
  ulonglong uVar10;
  undefined8 uVar11;
  longlong lVar12;
  ulonglong uVar13;
  uint uVar14;
  uint uVar15;
  ulonglong uVar16;
  ulonglong uVar17;
  longlong lVar18;
  longlong lVar19;
  dword local_250;
  word local_240;
  
  uVar9 = ZEXT48(register0x0000000c);
  __Save_R12_26_thru_31();
  iVar8 = (int)in_r2;
  lVar18 = *(longlong *)((int)DWORD_ARRAY_00016260 + iVar8 + 0x718);
  lVar12 = *(longlong *)((int)DWORD_ARRAY_00016260 + iVar8 + 0x708);
  iVar5 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar8 + 0x248);
  uVar3 = *(ushort *)(iVar5 + 0x1c);
  if ((lVar18 == 0) || (lVar12 == 0)) {
    return 0xffffffffc8000097;
  }
  uVar4 = *(ushort *)((int)lVar12 + 0x156);
  if ((((uVar4 != 0) && (*(ushort *)(iVar5 + 0x1e) < uVar4)) ||
      (lVar12 = FUN_00028738(), lVar12 == 0)) &&
     (((uVar4 = *(ushort *)((int)lVar18 + 0x156), 0x400 < uVar4 && (uVar3 < uVar4)) ||
      (lVar12 = FUN_00028738(), lVar12 == 0)))) {
    return 0xffffffffc8000098;
  }
  lVar18 = in_r2 + 0x16980;
  lVar19 = 0x10;
  do {
    *(undefined8 *)lVar18 = 0;
    lVar18 = lVar18 + 8;
    lVar19 = lVar19 + -1;
  } while (lVar19 != 0);
  iVar5 = (int)lVar12;
  uVar16 = (ulonglong)*(byte *)(iVar5 + 0xb);
  uVar17 = (ulonglong)*(ushort *)(iVar5 + 2);
  bVar1 = *(byte *)(iVar5 + 0xc);
  bVar2 = *(byte *)(iVar5 + 0xd);
  if (((9 < (uVar16 - 3 & 0xffffffff)) || (uVar16 < bVar1)) ||
     ((uVar16 < bVar2 || (uVar17 < uVar16)))) {
    return 0xffffffffc8000099;
  }
  iVar6 = (int)in_r2;
  *(byte *)((int)DWORD_ARRAY_00016260 + iVar6 + 0x721) = *(byte *)(iVar5 + 0xb);
  *(byte *)((int)DWORD_ARRAY_00016260 + iVar6 + 0x724) = bVar1;
  *(byte *)((int)DWORD_ARRAY_00016260 + iVar6 + 0x725) = bVar2;
  if (0xb3 < ((ulonglong)*(byte *)(iVar5 + 0xe) - 1 & 0xffffffff)) {
    return 0xffffffffc8000099;
  }
  *(byte *)((int)DWORD_ARRAY_00016260 + iVar6 + 0x726) = *(byte *)(iVar5 + 0xe);
  bVar1 = *(byte *)(iVar5 + 0xf);
  if (0x17 < ((ulonglong)bVar1 - 1 & 0xffffffff)) {
    return 0xffffffffc8000099;
  }
  if (uVar17 < uVar16) {
    uVar16 = uVar17;
  }
  iVar8 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar8 + 0x248);
  if ((*(char *)(iVar8 + 0x18) == '\0') || (*(longlong *)(iVar8 + 0x28) != 0)) {
    uVar17 = uVar16;
  }
  if (uVar17 < (uint)((int)uVar16 << 2)) {
    uVar10 = 0;
  }
  else {
    uVar10 = FUN_000004d8();
    uVar13 = (ulonglong)bVar1 * 180000000000;
    trapDoubleWordImmediate(6,uVar13,0);
    uVar14 = (uint)(uVar10 / uVar13);
    if (3 < uVar14) {
      uVar14 = 3;
    }
    FUN_00020060(uVar9 - 0x250,4);
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
    uVar10 = (longlong)(int)uVar14 * (longlong)(int)uVar15;
    uVar13 = uVar10 + uVar14;
    if ((uVar13 & 0xffffffff) <= uVar17) goto LAB_00028e48;
  }
  uVar13 = uVar17;
LAB_00028e48:
  uVar13 = uVar13 - uVar10;
  if (0x40 < (uVar13 & 0xffffffff)) {
    FUN_00020060(uVar9 - 0x250,4);
    uVar17 = uVar13 & 0xffffffff;
    uVar13 = 0x40;
    uVar17 = uVar17 - 0x3f;
    trapDoubleWordImmediate(6,uVar17,0);
    uVar10 = (local_250 - (int)(local_250 / uVar17) * (int)uVar17) + uVar10;
  }
  memcpy(uVar9 - 0x240,(uVar10 & 0xffffffff) * 8 + lVar12 + 0x20,(ulonglong)(uint)((int)uVar13 << 3)
        );
  uVar17 = 0;
  if ((uVar13 - 1 & 0xffffffff) != 0) {
    lVar12 = uVar9 - 0x240;
    do {
      FUN_00020060(uVar9 - 0x250,4);
      uVar10 = uVar13 - uVar17;
      trapWord(6,uVar10,0);
      iVar8 = (local_250 - (int)((ulonglong)local_250 / (uVar10 & 0xffffffff)) * (int)uVar10) +
              (int)uVar17;
      uVar17 = uVar17 + 1;
      uVar11 = *(undefined8 *)(&local_240 + iVar8 * 4);
      *(undefined8 *)(&local_240 + iVar8 * 4) = *(undefined8 *)lVar12;
      *(undefined8 *)lVar12 = uVar11;
      lVar12 = lVar12 + 8;
    } while ((uVar17 & 0xffffffff) < (uVar13 - 1 & 0xffffffff));
  }
  FUN_00020060(uVar9 - 0x250,4);
  uVar17 = (uVar13 - uVar16) + 1;
  trapWord(6,uVar17,0);
  memcpy(in_r2 + 0x169a0,
         (((ulonglong)local_250 -
          (longlong)(int)((ulonglong)local_250 / (uVar17 & 0xffffffff)) * (longlong)(int)uVar17) * 8
         & 0x7fffffff8) + (uVar9 - 0x240),(ulonglong)(uint)((int)uVar16 << 3));
  FUN_00020060(uVar9 - 0x250,4);
  trapWord(6,uVar16,0);
  *(char *)((int)DWORD_ARRAY_00016260 + iVar6 + 0x727) =
       (char)local_250 - (char)(local_250 / uVar16) * (char)uVar16;
  return 0;
}



undefined8 FUN_00028f98(undefined8 param_1,ulonglong param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  longlong in_r2;
  undefined8 uVar4;
  ulonglong uVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  word *pwVar8;
  undefined8 uVar9;
  longlong lVar10;
  longlong lVar11;
  longlong lVar12;
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
    bVar1 = *(byte *)((int)DWORD_ARRAY_00016260 + iVar3 + 0x720);
    if (bVar1 < *(byte *)((int)DWORD_ARRAY_00016260 + iVar3 + 0x721)) {
      puVar6 = (undefined4 *)&local_70;
      lVar11 = 8;
      do {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
      *(undefined2 *)puVar6 = 0;
      pwVar8 = &local_5e;
      lVar10 = in_r2 + 0x10030;
      uVar5 = *(ulonglong *)((uint)bVar1 * 8 + iVar3 + 0x169a0);
      uVar9 = *(undefined8 *)((uint)bVar1 * 8 + iVar3 + 0x169a0);
      lVar12 = 0x10;
      lVar11 = lVar10;
      do {
        puVar7 = (undefined *)lVar11;
        lVar11 = lVar11 + 1;
        *(undefined *)pwVar8 = *puVar7;
        pwVar8 = (word *)((int)pwVar8 + 1);
        lVar12 = lVar12 + -1;
      } while (lVar12 != 0);
      if (bVar1 == *(byte *)((int)DWORD_ARRAY_00016260 + iVar3 + 0x727)) {
        uVar5 = ((ulonglong)((uint)((ulonglong)uVar9 >> 0x10) & 0xffffff) - (uVar5 >> 0x28) &
                0xffffffff) / 3;
        FUN_00020060(&local_1e0,4);
        trapWord(6,uVar5,0);
        FUN_00020060(&local_1e0,4);
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
      XeCryptAesKey(&local_1d0,in_r2 + 0x10020);
      XeCryptAesCbc(&local_1d0,&local_6e,0x10,&local_6e,&local_40,1);
      memcpy(uVar4,&local_70,0x22);
      HvpReleaseSpinLock((ulonglong)uVar2);
      uVar4 = 0;
    }
    else {
      HvpReleaseSpinLock((ulonglong)uVar2);
      uVar4 = 0xffffffffc800009a;
    }
  }
  else {
    HvpReleaseSpinLock((ulonglong)uVar2);
    uVar4 = 0xffffffffc8000090;
  }
  return uVar4;
}



// WARNING: Could not reconcile some variable overlaps

undefined8 FUN_000291a0(undefined8 param_1,ulonglong param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  longlong in_r2;
  undefined8 uVar5;
  word *pwVar6;
  undefined8 uVar7;
  longlong lVar8;
  undefined *puVar10;
  ulonglong uVar9;
  byte *pbVar11;
  longlong lVar12;
  word local_1d0;
  word local_70;
  word local_6e;
  word local_62;
  word local_40;
  dword local_30;
  
  uVar5 = __Save_R12_28_thru_31();
  iVar4 = (int)in_r2;
  uVar3 = *(uint *)(iVar4 + 0x10000);
  pbVar11 = (byte *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x720);
  if (((param_2 & 0xffffffff) == 0x22) &&
     (bVar1 = *pbVar11, bVar1 < *(byte *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x721))) {
    bVar2 = *(byte *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x726);
    uVar7 = *(undefined8 *)((uint)bVar1 * 8 + iVar4 + 0x169a0);
    if (-1 < param_3) {
      memcpy(&local_70,uVar5,0x22);
      if (((local_70._0_1_ & 0x3f) == 0x39) && ((char)local_70 == ' ')) {
        pwVar6 = &local_40;
        lVar8 = in_r2 + 0x10030;
        lVar12 = 0x10;
        do {
          puVar10 = (undefined *)lVar8;
          lVar8 = lVar8 + 1;
          *(undefined *)pwVar6 = *puVar10;
          pwVar6 = (word *)((int)pwVar6 + 1);
          lVar12 = lVar12 + -1;
        } while (lVar12 != 0);
        XeCryptAesKey(&local_1d0,in_r2 + 0x10020);
        XeCryptAesCbc(&local_1d0,&local_6e,0x10,&local_6e,&local_40,0);
        if ((local_6e._0_1_ == '\x11') && (local_62 < 0x168)) {
          if (bVar1 == *(byte *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x727)) {
            *(undefined *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x727) = 0xff;
            goto LAB_00029300;
          }
          uVar9 = ((ulonglong)local_62 - (ulonglong)((uint)uVar7 & 0xffff)) + (ulonglong)bVar2 +
                  0x168;
          if ((ulonglong)bVar2 << 1 < (uVar9 + ((uVar9 & 0xffffffff) / 0x168) * -0x168 & 0xffffffff)
             ) {
            *(char *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x723) =
                 *(char *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x723) + '\x01';
          }
          else {
            *(char *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x722) =
                 *(char *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x722) + '\x01';
          }
        }
      }
    }
  }
  *pbVar11 = *pbVar11 + 1;
LAB_00029300:
  HvpReleaseSpinLock((ulonglong)uVar3);
  return 0;
}



undefined8 FUN_00029318(void)

{
  int in_r2;
  undefined8 uVar1;
  undefined8 *puVar2;
  longlong lVar3;
  
  puVar2 = (undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x720);
  if (*(char *)puVar2 == *(char *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x721)) {
    if (*(byte *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x725) <=
        *(byte *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x723)) {
      uVar1 = 0xffffffffc800009e;
      goto LAB_00029370;
    }
    if (*(byte *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x724) <=
        *(byte *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x722)) {
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



ulonglong FUN_00029528(int param_1,ulonglong param_2,ulonglong param_3,undefined8 param_4)

{
  longlong in_r2;
  ulonglong uVar1;
  undefined8 uVar2;
  longlong lVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  longlong lVar6;
  
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
                goto LAB_00029390;
              }
              uVar5 = 0;
              uVar4 = 0;
              lVar3 = ZEXT48(FUN_000291a0) + in_r2;
            }
            goto LAB_000293e0;
          }
          param_2 = 0;
          lVar3 = ZEXT48(FUN_00028c40) + in_r2;
        }
LAB_00029390:
        uVar2 = __Save_R12_29_thru_31(lVar3,param_2,param_4);
        HvpAquireSpinLock(in_r2 + 0x16960);
        uVar4 = func_0x00000790(param_2,uVar2);
        FUN_00027f08();
        FUN_000001e0(in_r2 + 0x16960);
        return uVar4 & 0xffffffff;
      }
      uVar5 = 1;
      uVar4 = 1;
      lVar3 = ZEXT48(FUN_00028a78) + in_r2;
      param_4 = 0;
    }
  }
LAB_000293e0:
  param_3 = param_3 & 0xffffffff;
  uVar1 = __Save_R12_24_thru_31(param_2 & 0xffffffff,param_3,param_4,lVar3);
  lVar6 = in_r2 + 0x16918;
  if ((uVar4 & 0xffffffff) == 0) {
    uVar2 = HvpPhysicalToReal(uVar1,param_3);
  }
  else {
    if (((((uVar1 & 0x7f) != 0) || ((param_3 & 0x7f) != 0)) || ((param_3 & 0xffffffff) == 0)) ||
       ((ZEXT48(&BYTE_00010001) <= (param_3 & 0xffffffff) ||
        (((((uint)uVar1 + (uint)param_3) - 1 ^ (uint)uVar1) & 0xffff0000) != 0)))) {
      return 0xffffffffc8000090;
    }
    HvpAquireSpinLock(lVar6);
    uVar2 = func_0x000033d8(uVar1,param_3,0x3a);
  }
  HvpAquireSpinLock(in_r2 + 0x16960);
  uVar1 = func_0x000007a0(uVar2,param_3,param_4,lVar3);
  FUN_00027f08();
  FUN_000001e0(in_r2 + 0x16960);
  if (((uVar5 & 0xffffffff) != 0) || ((int)uVar1 != 0)) {
    if ((uVar4 & 0xffffffff) == 0) {
      memset(uVar2,0,param_3);
    }
    else {
      HvpZeroCacheLines(uVar2,(ulonglong)((uint)param_3 >> 7));
    }
  }
  if ((uVar4 & 0xffffffff) != 0) {
    HvpRelocateProtectedToPhysical(uVar2,param_3,0x3a);
    FUN_000001e0(lVar6);
  }
  return uVar1 & 0xffffffff;
}



ulonglong FUN_00029648(ulonglong param_1,ulonglong param_2,ulonglong param_3)

{
  int in_r2;
  
  return *(ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6e0) ^ param_1 ^ param_2 ^ param_3;
}



ulonglong thunk_FUN_00023698(ulonglong param_1,uint param_2,uint param_3)

{
  return (ulonglong)
         (((uint)(param_1 >> 0x11) & 0x80 | (uint)(param_1 >> 0x19) & 0x7f) +
          ((uint)(param_1 >> 0x25) & 7 | (uint)(param_1 >> 0x1d) & 0xf8) +
          ((uint)(param_1 >> 0x16) & 3 | (uint)(param_1 >> 0xe) & 0xfc) +
          ((uint)(param_1 >> 0xb) & 0x1f | (uint)(param_1 >> 3) & 0xe0) +
          ((uint)(param_1 >> 7) & 1 | (uint)(param_1 << 1) & 0xfe) & 0xff ^ param_2 & 0xff ^
         param_3 & 0xff) ^ 0x3a;
}



ulonglong thunk_FUN_00023718(ulonglong param_1,undefined8 param_2,undefined8 param_3)

{
  return (ulonglong)
         (((uint)(param_1 >> 0x27) & 1 | (uint)(param_1 >> 0x1f) & 0xfe) +
          ((uint)(param_1 >> 0x1b) & 0x1f | (uint)(param_1 >> 0x13) & 0xe0) +
          ((uint)(param_1 >> 10) & 0x3f | (uint)(param_1 >> 2) & 0xc0) +
          ((uint)(param_1 >> 0x14) & 0xf | (uint)(param_1 >> 0xc) & 0xf0) + ((uint)param_1 & 0xff) &
          0xff ^ (uint)((ulonglong)param_2 >> 8) & 0xff ^ (uint)((ulonglong)param_3 >> 8) & 0xff) ^
         0x72;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_00029670(void)

{
  uint uVar1;
  longlong in_r2;
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
  XeCryptAesEcb(&local_190,in_r2 + 0x10430,in_r2 + 0x16940,0);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



void FUN_00029710(void)

{
  longlong in_r2;
  undefined8 uVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0x10;
  uVar1 = __Save_R12_29_thru_31(in_r2 + 0x16590,0x10);
  lVar3 = in_r2 + 0x16910;
  HvpAquireSpinLock(lVar3);
  XeCryptRc4Ecb(in_r2 + 0x16800,uVar1,uVar2);
  FUN_000001e0(lVar3);
  return;
}



void FUN_00029720(void)

{
  int in_r2;
  longlong lVar1;
  undefined8 uVar2;
  qword local_8;
  
  lVar1 = FUN_00000270();
  *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x590) = lVar1 + 0xe800;
  uVar2 = FUN_000002a8();
  *(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x318) = uVar2;
  return;
}



void FUN_00029760(undefined8 param_1,undefined8 param_2,ulonglong param_3)

{
  uint extraout_var;
  uint uVar1;
  ulonglong uVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  
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
      memset(pbVar5,(ulonglong)(uVar4 << 4 | uVar4),param_3 >> 1 & 0x7fffffff);
    }
    if ((param_3 & 1) != 0) {
      uVar1 = (uint)(param_3 >> 1) & 0x7fffffff;
      pbVar5[uVar1] = (byte)uVar4 | pbVar5[uVar1] & 0xf0;
    }
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

ulonglong FUN_000297f0(ulonglong param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  qword local_10;
  qword local_8;
  
  iVar3 = FUN_000005a8();
  bVar1 = *(byte *)(((uint)(param_1 >> 1) & 0x7fffffff) + iVar3);
  uVar2 = (uint)(bVar1 >> 4);
  if ((param_1 & 1) == 0) {
    uVar2 = (uint)bVar1 & 0xf;
  }
  return (ulonglong)uVar2;
}



undefined8 FUN_00029838(undefined8 param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar5;
  uint *puVar6;
  ulonglong uVar3;
  undefined8 uVar4;
  
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
      uVar3 = FUN_000297f0((ulonglong)(uVar5 >> 0xc & 0xffff));
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



ulonglong FUN_000298e8(int param_1)

{
  int iVar1;
  int in_r2;
  uint uVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  uVar2 = 0;
  lVar3 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x318);
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
    return (ulonglong)*(uint *)(iVar1 + 4);
  }
  if (*(char *)(iVar1 + 3) == '\x01') {
    return lVar5 + 4;
  }
  return (ulonglong)*(uint *)(iVar1 + 4) + lVar3;
}



undefined8
FUN_00029968(undefined8 param_1,ulonglong param_2,longlong param_3,ulonglong param_4,
            ulonglong param_5)

{
  uint uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  dword local_40;
  
  uVar2 = __Save_R12_27_thru_31();
  if (param_3 != 0) {
    uVar1 = *(uint *)((int)param_3 + 0x10);
    if ((param_2 & 0xffffffff) < (ulonglong)uVar1) {
      return 0;
    }
    if ((ulonglong)(*(int *)((int)param_3 + 0x14) + uVar1) < (param_2 + param_4 & 0xffffffff)) {
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
    uVar4 = ((ulonglong)local_40 & 0xffffffc0) << 10 | 0x8000000000000000 | param_2 & 0xffff;
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



undefined8 FUN_00029a68(undefined8 param_1,longlong param_2)

{
  uint uVar1;
  longlong in_r2;
  int iVar2;
  undefined8 uVar3;
  longlong lVar4;
  word local_140;
  word local_40;
  dword local_2c;
  
  iVar2 = __Save_R12_28_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  uVar3 = countLeadingZeros(*(uint *)(iVar2 + 0x104) & 6);
  if ((*(uint *)(iVar2 + 0x104) & 0x80000000) == 0) {
    lVar4 = in_r2 + 0x103e0;
  }
  else {
    lVar4 = in_r2 + 0x103ec;
  }
  XeCryptRotSumSha((uint *)(iVar2 + 0x100),(ulonglong)*(uint *)(iVar2 + 0x100) - 0x100,0,0,&local_40
                   ,0x14);
  memcpy(&local_140,iVar2,0x100);
  iVar2 = XeCryptBnQwBeSigVerify
                    (&local_140,&local_40,lVar4,ZEXT48(&PTR_DWORD_ARRAY_00010750) + in_r2);
  if (iVar2 == 0) {
    uVar3 = 0xffffffffc0000221;
  }
  else {
    if (param_2 != 0) {
      in_r2 = ZEXT48(&DWORD_00010b90) + in_r2;
      if (((uint)uVar3 >> 5 & 1) == 1) {
        in_r2 = 0x54;
      }
      XeCryptAesKey(param_2,in_r2);
    }
    uVar3 = 0;
  }
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar3;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_00029b58(undefined8 param_1,undefined8 param_2)

{
  longlong in_r2;
  ulonglong uVar1;
  word local_1b0;
  word local_180;
  qword local_18;
  qword local_10;
  qword local_8;
  
  uVar1 = FUN_00029968(&local_1b0,param_1,param_2,0x2c,1);
  if ((uVar1 & 0xffffffff) != 0) {
    XeCryptAesKey(&local_180,in_r2 + 0x16590);
    XeCryptAesEcb(&local_180,&local_1b0,&local_1b0,1);
    FUN_00029968(&local_1b0,param_1,param_2,0x2c,0);
  }
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

ulonglong FUN_00029be8(undefined8 param_1)

{
  longlong in_r2;
  ulonglong uVar1;
  uint uVar2;
  dword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  HvpAquireSpinLock(in_r2 + 0x167a0);
  uVar1 = FUN_00029838(param_1,&local_20);
  uVar2 = 0;
  if ((uVar1 & 0xffffffff) != 0) {
    uVar2 = local_20;
  }
  FUN_000001e0(in_r2 + 0x167a0);
  return (ulonglong)(uVar2 & 0x400fffff);
}



undefined8 j_HvxTest(void)

{
  return 0;
}



ulonglong FUN_00029c68(int param_1,longlong param_2)

{
  ushort uVar1;
  int iVar2;
  word local_10;
  qword local_8;
  
  iVar2 = (int)(param_2 << 1);
  uVar1 = *(ushort *)(iVar2 + param_1);
  if ((uVar1 & 0x400) == 0) {
    *(short *)(iVar2 + param_1) = uVar1 + 1;
  }
  else {
    FUN_00020060(&local_10,2);
    uVar1 = local_10;
  }
  return (ulonglong)((uint)uVar1 & 0x3ff);
}



undefined8 FUN_00029cc0(undefined8 param_1,ulonglong param_2,ulonglong param_3)

{
  ulonglong *puVar1;
  longlong in_r2;
  ulonglong uVar2;
  undefined8 uVar3;
  uint *puVar4;
  int iVar5;
  
  uVar2 = __Save_R12_26_thru_31();
  iVar5 = (int)in_r2;
  if ((uVar2 & 0xffffffff) < 2) {
    HvpAquireSpinLock(in_r2 + 0x167a0);
    uVar3 = 0;
    puVar1 = (ulonglong *)((int)uVar2 * 0x38 + iVar5 + 0x16500);
    if ((((*(char *)((int)puVar1 + 0x34) == '\x01') && ((param_2 & 0xffff) == 0)) &&
        ((param_3 & 0xffff) == 0)) &&
       (((param_3 & 0xffffffff) < 0x20000000 && (uVar2 = FUN_0000057c(param_2), uVar2 != 0)))) {
      puVar4 = (uint *)uVar2;
      if (((((*puVar4 & 8) == 0) && ((*puVar1 <= uVar2 && (uVar2 <= puVar1[1])))) &&
          ((*puVar4 & 0xfffc0) == 0)) &&
         (iVar5 = FUN_000005c0(),
         (*(ushort *)(((uint)(param_3 >> 0xf) & 0x1fffe) + iVar5) & 0x800) == 0)) {
        uVar3 = 1;
        uVar2 = (ulonglong)((uint)param_3 >> 10 & 0xfffc0) | (ulonglong)*puVar4 & 0xfffffffffff0003f
        ;
        *puVar4 = (uint)uVar2;
        *(ushort *)(((uint)(uVar2 >> 5) & 0x7ffe) + iVar5) =
             *(ushort *)(((uint)(uVar2 >> 5) & 0x7ffe) + iVar5) | 0x800;
      }
    }
    FUN_000001e0(in_r2 + 0x167a0);
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
  ulonglong *puVar2;
  int in_r2;
  undefined8 uVar3;
  ulonglong uVar4;
  undefined uVar5;
  int iVar6;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (param_1 < 2) {
    iVar6 = in_r2 + 0x167a0;
    HvpAquireSpinLock(iVar6);
    uVar3 = 0;
    puVar2 = (ulonglong *)(param_1 * 0x38 + in_r2 + 0x16500);
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
    FUN_000001e0(iVar6);
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



undefined8 FUN_00029eb0(void)

{
  uint uVar1;
  longlong in_r2;
  ulonglong uVar2;
  uint *puVar3;
  undefined8 uVar4;
  dword local_30;
  
  uVar2 = __Save_R12_29_thru_31();
  uVar4 = 0;
  HvpAquireSpinLock(in_r2 + 0x167a0);
  if (((((uVar2 & 0xffff) == 0) && ((uVar2 & 0xffffffff) != 0x80000000)) &&
      (puVar3 = (uint *)FUN_0000057c(uVar2), puVar3 != (uint *)0x0)) && ((*puVar3 & 0x10) != 0)) {
    do {
      uVar1 = *puVar3;
      *puVar3 = uVar1 & 0xfffffff0 | 7;
      puVar3 = puVar3 + 1;
    } while ((uVar1 >> 5 & 1) == 0);
    uVar4 = 1;
  }
  FUN_000001e0(in_r2 + 0x167a0);
  return uVar4;
}



undefined8 FUN_00029f58(void)

{
  uint uVar1;
  longlong in_r2;
  ulonglong uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  uint *puVar8;
  
  uVar2 = __Save_R12_25_thru_31();
  uVar7 = 0;
  iVar3 = FUN_000005c0();
  lVar5 = in_r2 + 0x167a0;
  HvpAquireSpinLock(lVar5);
  HvpSetRMCI(0);
  if ((((uVar2 & 0xffff) == 0) && ((uVar2 & 0xffffffff) != 0x80000000)) &&
     (puVar8 = (uint *)FUN_0000057c(uVar2), puVar8 != (uint *)0x0)) {
    uVar6 = (ulonglong)((uint)uVar2 >> 0xc & 0xffff);
    uVar4 = countLeadingZeros(-0x70000000 - ((uint)uVar2 & 0xf0000000));
    if ((*puVar8 != 0) && ((*puVar8 & 0x10) != 0)) {
      do {
        if ((*puVar8 & 0xc0000000) != 0) {
          HvpInvalidateCachelines(((ulonglong)*puVar8 & 0xffffffc0) << 10,0x10000);
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
      in_r2 = in_r2 + 0x167c0;
      do {
        if ((ulonglong)*(uint *)in_r2 == (uVar2 & 0xffffffff)) {
          *(uint *)in_r2 = 0;
        }
        iVar3 = iVar3 + -1;
        in_r2 = in_r2 + 4;
      } while (iVar3 != 0);
      uVar7 = 1;
    }
  }
  HvpSetRMCI(1);
  FUN_000001e0(lVar5);
  return uVar7;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_0002a0b0(uint param_1)

{
  int in_r2;
  int iVar1;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (param_1 < 2) {
    iVar1 = in_r2 + 0x167a0;
    HvpAquireSpinLock(iVar1);
    *(undefined *)(param_1 * 0x38 + in_r2 + 0x16534) = 0;
    FUN_000001e0(iVar1);
  }
  return 0;
}



undefined8 FUN_0002a120(undefined8 param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  byte *pbVar5;
  longlong *plVar6;
  longlong in_r2;
  ulonglong uVar7;
  int iVar8;
  uint uVar9;
  longlong lVar10;
  ulonglong uVar11;
  undefined4 *puVar12;
  longlong lVar13;
  undefined8 uVar14;
  longlong lVar15;
  ulonglong unaff_r28;
  ulonglong uVar16;
  ulonglong uVar17;
  uint *puVar18;
  int iVar19;
  uint param_1_01;
  ulonglong param_1_00;
  undefined8 param_2_00;
  undefined8 param_3_00;
  word local_90;
  dword local_7c;
  
  uVar7 = __Save_R12_19_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  param_1_00 = param_2;
  param_2_00 = param_3;
  param_3_00 = param_4;
  if (1 < (uVar7 & 0xffffffff)) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0;
  }
  lVar13 = in_r2 + 0x167a0;
  HvpAquireSpinLock(lVar13);
  uVar14 = 0;
  HvpSetRMCI(0);
  lVar15 = (uVar7 & 0xffffffff) * 0x38 + in_r2 + 0x16500;
  plVar6 = (longlong *)lVar15;
  if (*(char *)((int)plVar6 + 0x34) == '\x02') {
    if ((((param_1_00 & 0x200000000) != 0) || ((param_1_00 & 0x100000000) != 0)) &&
       ((param_1_00 & 0x400000000) == 0)) {
      if (((param_1_00 & 0x200000000) == 0) || (iVar19 = 0, (param_1_00 & 0x800000000) != 0)) {
        iVar19 = 1;
      }
      if ((*(byte *)((int)plVar6 + 0x35) & 1) == 0) {
        uVar7 = (ulonglong)(param_1_01 & 3) | 0xc;
        lVar10 = 0x10;
      }
      else {
        lVar10 = 0xc;
        uVar7 = (ulonglong)(uint)(iVar19 << 3) | (ulonglong)(param_1_01 & 3) | 4;
      }
      uVar2 = *(uint *)(plVar6 + 3);
      pbVar5 = (byte *)((param_1_01 >> 4) << lVar10);
      uVar16 = unaff_r28 & 0xffffffff00000000 | ZEXT48(pbVar5);
      if ((((ulonglong)uVar2 < (ulonglong)*(uint *)((int)plVar6 + 0x14)) && (pbVar5 != (byte *)0x0))
         && ((pbVar5 < &BYTE_00010001 &&
             (((ZEXT48(pbVar5) <=
                ((ulonglong)*(uint *)((int)plVar6 + 0x14) - (ulonglong)uVar2 & 0xffffffff) &&
               ((((uint)(pbVar5 + uVar2 + -1) ^ uVar2) & 0xffff0000) == 0)) &&
              (uVar17 = ((ulonglong)(uVar2 >> 0xe) & 0x3fffffffffffc) + *plVar6,
              uVar17 <= (ulonglong)plVar6[1])))))) {
        puVar18 = (uint *)uVar17;
        uVar3 = *puVar18;
        if (((uVar3 & 8) != 0) && ((uVar3 & 0xfffc0) != 0)) {
          uVar11 = (ulonglong)((uVar3 & 0xfffc0) << 10 | uVar2 & 0xf000);
          uVar17 = uVar11 | 0x8000000000000000;
          if (iVar19 != 0) {
            uVar17 = func_0x000033d8(uVar11,uVar16,0x3d);
          }
          XeCryptSha(uVar17,uVar16,&stack0x00000020,0x18,0,0,&local_90,0x14);
          lVar15 = lVar15 + 0x20;
          iVar8 = XeCryptMemDiff(&local_90,lVar15,0x14);
          if (iVar8 == 0) {
            if (iVar19 != 0) {
              uVar3 = *puVar18;
              if ((uVar3 & 0xc0000000) == 0) {
                uVar14 = FUN_000005c0();
                uVar9 = FUN_00029c68(uVar14,(ulonglong)(*puVar18 >> 6 & 0x3fff));
                *puVar18 = (uVar9 & 0x3ff) << 0x14 | uVar3 & 0xc00fffff | 0xc0000000;
              }
              HvpRelocateCacheLines
                        (uVar17,((ulonglong)*puVar18 & 0x3fffffffffffc0) << 10 | 0x8000000000000000
                                | (ulonglong)(uVar2 & 0xf000),(ulonglong)((uint)pbVar5 >> 7));
            }
            if ((*(byte *)((int)plVar6 + 0x35) & 1) == 0) {
              *puVar18 = (uint)uVar7 | *puVar18 & 0xfffffff0;
            }
            else {
              FUN_00029760((ulonglong)*(ushort *)((int)plVar6 + 0x36) + (ulonglong)(uVar2 >> 0xc),
                           uVar7,(ulonglong)((uint)pbVar5 >> 0xc));
            }
            puVar12 = (undefined4 *)((int)&stack0x00000020 + 4);
            *(byte **)(plVar6 + 3) = pbVar5 + uVar2;
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
  FUN_000001e0(lVar13);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar14;
}



undefined8 FUN_0002a410(void)

{
  longlong *plVar1;
  longlong in_r2;
  ulonglong uVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  longlong lVar5;
  longlong lVar6;
  
  uVar2 = __Save_R12_29_thru_31();
  if ((uVar2 & 0xffffffff) < 2) {
    lVar5 = in_r2 + 0x167a0;
    HvpAquireSpinLock(lVar5);
    uVar3 = 0;
    lVar6 = (uVar2 & 0xffffffff) * 0x38 + in_r2 + 0x16500;
    plVar1 = (longlong *)lVar6;
    if ((*(char *)((int)plVar1 + 0x34) == '\x02') &&
       (*(uint *)(plVar1 + 3) == *(uint *)((int)plVar1 + 0x14))) {
      if ((*(byte *)((int)plVar1 + 0x35) & 1) != 0) {
        uVar2 = (ulonglong)(*(uint *)(plVar1 + 3) >> 0xc) +
                (ulonglong)*(ushort *)((int)plVar1 + 0x36);
        uVar4 = (ulonglong)(uint)(((int)(plVar1[1] - *plVar1 >> 2) + 1) * 0x10) +
                (ulonglong)*(ushort *)((int)plVar1 + 0x36);
        if (uVar2 < (uVar4 & 0xffffffff)) {
          FUN_00029760(uVar2,0,uVar4 - uVar2);
        }
      }
      uVar4 = plVar1[1];
      uVar2 = ((ulonglong)*(uint *)(plVar1 + 3) - 1 >> 0xe & 0x3fffc) + *plVar1;
      if (uVar2 < uVar4) {
        do {
          *(undefined4 *)uVar4 = 0;
          uVar4 = uVar4 - 4;
        } while (uVar2 < uVar4);
        *(uint *)uVar4 = *(uint *)uVar4 | 0x20;
      }
      HvpSetRMCI(0);
      FUN_00029b58((ulonglong)*(uint *)((int)plVar1 + 0x1c),lVar6);
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
    FUN_000001e0(lVar5);
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



undefined8 FUN_0002a560(undefined8 param_1,ulonglong param_2)

{
  uint uVar1;
  undefined4 uVar2;
  longlong *plVar3;
  longlong in_r2;
  ulonglong uVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong lVar7;
  uint uVar8;
  undefined4 *puVar9;
  longlong lVar10;
  longlong lVar11;
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
    lVar10 = in_r2 + 0x167a0;
    HvpAquireSpinLock(lVar10);
    uVar5 = 0;
    lVar11 = (uVar4 & 0xffffffff) * 0x38 + in_r2 + 0x16500;
    plVar3 = (longlong *)lVar11;
    if ((*(char *)((int)plVar3 + 0x34) == '\0') && ((param_2 + 0x120 & 0xfff) + 0x20 < 0x1001)) {
      if ((param_2 & 0xffffffff) == 0) {
        lVar6 = *(longlong *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x290) + 0x120;
      }
      else {
        lVar6 = HvpPhysicalToReal(param_2 + 0x120,0x20);
      }
      XeCryptAesKey(&local_1b0,in_r2 + 0x16590);
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
    FUN_000001e0(lVar10);
    HvpReleaseSpinLock((ulonglong)uVar1);
  }
  else {
    HvpReleaseSpinLock((ulonglong)uVar1);
    uVar5 = 0;
  }
  return uVar5;
}



ulonglong FUN_0002a740(int param_1,ulonglong param_2,ulonglong param_3)

{
  ushort uVar1;
  int in_r2;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong *puVar4;
  
  if ((*(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x340) & 1) == 0) {
    return param_3;
  }
  if (param_1 == 0) {
    return param_3;
  }
  uVar1 = *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x342);
  uVar3 = 0;
  puVar4 = (ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x348);
  if (uVar1 == 0) {
    return param_3;
  }
  while (((uVar2 = *puVar4, (uVar2 & 1) == 0 ||
          ((uVar2 >> 8 & 0xffffffff) != (param_2 & 0xffffffff))) ||
         ((uVar2 >> 0x28 & 0xfff) != (param_3 & 0xffffffff)))) {
    uVar3 = uVar3 + 1;
    puVar4 = puVar4 + 1;
    if ((ulonglong)uVar1 <= (uVar3 & 0xffffffff)) {
      return param_3;
    }
  }
  return *puVar4 >> 0x34;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Variable defined which should be unmapped: local_88

ulonglong FUN_0002afd8(ulonglong param_1,ulonglong param_2)

{
  uint uVar1;
  uint uVar2;
  ulonglong uVar3;
  int iVar5;
  undefined8 uVar4;
  longlong lVar6;
  uint *puVar7;
  qword local_e0;
  qword local_88;
  qword local_80;
  qword local_78;
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
      return ((ulonglong)local_20 & 0xffffffc0) << 10 | 0x8000000000000000 | param_1 & 0xffff;
    }
    _v_MACHINE_CHECK_0();
  }
  _v_MACHINE_CHECK_0();
  puVar7 = (uint *)FUN_0000057c();
  if ((puVar7 == (uint *)0x0) || ((*puVar7 & 0x10) == 0)) {
LAB_0002b150:
    uVar4 = 0;
  }
  else {
    iVar5 = FUN_000005c0();
    uVar1 = *puVar7;
    lVar6 = 0;
    do {
      uVar2 = *puVar7;
      if (((((uVar2 & 2) == 0) || ((uVar2 & 4) == 0)) || ((uVar2 & 0xfffc0) == 0)) ||
         (((ulonglong)(uVar2 >> 0x1e) != (param_2 & 0xffffffff) ||
          ((*(ushort *)((int)(lVar6 << 1) + (uVar1 >> 5 & 0x7ffe) + iVar5) & 0x800) == 0))))
      goto LAB_0002b150;
      lVar6 = lVar6 + 1;
      puVar7 = puVar7 + 1;
    } while ((uVar2 >> 5 & 1) == 0);
    uVar4 = 1;
  }
  return uVar4;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_0002b400(ulonglong param_1)

{
  uint uVar1;
  longlong in_r2;
  ulonglong uVar2;
  uint *puVar3;
  longlong lVar4;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if (((param_1 & 0xffff) == 0) && ((param_1 + 0x74000000 & 0xffffffff) < 0x2000000)) {
    lVar4 = in_r2 + 0x167a0;
    HvpAquireSpinLock(lVar4);
    uVar2 = func_0x0002b098(param_1,3);
    if ((uVar2 & 0xffffffff) != 0) {
      puVar3 = (uint *)FUN_0000057c(param_1);
      do {
        uVar1 = *puVar3;
        *puVar3 = uVar1 & 0xfffffff6 | 1;
        puVar3 = puVar3 + 1;
      } while ((uVar1 >> 5 & 1) == 0);
      FUN_000001e0(lVar4);
      return 1;
    }
    FUN_000001e0(lVar4);
  }
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10
// WARNING: Removing unreachable block (ram,0x0002b73c)
// WARNING: Removing unreachable block (ram,0x0002b74c)
// WARNING: Removing unreachable block (ram,0x0002b760)
// WARNING: Removing unreachable block (ram,0x0002b774)
// WARNING: Removing unreachable block (ram,0x0002b7a0)
// WARNING: Removing unreachable block (ram,0x0002b7b0)
// WARNING: Removing unreachable block (ram,0x0002b7d8)
// WARNING: Removing unreachable block (ram,0x0002b7c4)

undefined8 FUN_0002b6d0(ulonglong param_1,int param_2)

{
  int in_r2;
  undefined8 uVar1;
  qword back_chain;
  word local_2f0;
  word local_190;
  dword local_8c;
  word local_58;
  word local_48;
  dword local_1c;
  qword local_10;
  qword local_8;
  
  if (((param_1 & 0xfff) == 0) && (param_2 == 0x174)) {
    HvpReleaseSpinLock((ulonglong)*(uint *)(in_r2 + 0x10000));
    uVar1 = 0xffffffffc8000002;
  }
  else {
    HvpReleaseSpinLock((ulonglong)*(uint *)(in_r2 + 0x10000));
    uVar1 = 0xffffffffc8000004;
  }
  return uVar1;
}



undefined8 FUN_0002b810(undefined8 param_1,ulonglong param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined8 in_r2;
  int iVar4;
  undefined8 uVar5;
  int iVar8;
  undefined8 uVar6;
  longlong lVar7;
  ulonglong uVar9;
  uint *puVar10;
  ulonglong uVar11;
  uint uVar12;
  longlong lVar13;
  qword back_chain;
  word local_90;
  word local_50;
  dword local_3c;
  
  uVar5 = __Save_R12_27_thru_31();
  iVar3 = (int)in_r2;
  uVar1 = *(uint *)(iVar3 + 0x10000);
  uVar11 = *(ulonglong *)((int)DWORD_ARRAY_00016260 + iVar3 + 0x318);
  if ((param_2 & 0xffffffff) < 0x11) {
    uVar5 = HvpPhysicalToReal(uVar5,param_2);
    memcpy(&local_90,uVar5,(ulonglong)(uint)((int)param_2 << 2));
    iVar4 = (int)in_r2;
    uVar12 = 0;
    if ((param_2 & 0xffffffff) != 0) {
      puVar10 = (uint *)&local_90;
      do {
        uVar5 = HvpPhysicalToReal((ulonglong)*puVar10,0x1000);
        memcpy((uVar12 << 0xc) + uVar11,uVar5,0x1000);
        iVar4 = (int)in_r2;
        uVar12 = uVar12 + 1;
        puVar10 = puVar10 + 1;
      } while ((ulonglong)uVar12 < (param_2 & 0xffffffff));
    }
    uVar12 = *(uint *)((int)uVar11 + 8);
    if (((ulonglong)uVar12 - 0x19c & 0xffffffff) < 0xfe65) {
      uVar9 = (ulonglong)*(uint *)((int)uVar11 + 0x10);
      if (uVar9 < (ulonglong)uVar12 - 0x184) {
        lVar7 = uVar9 + uVar11;
        uVar9 = lVar7 + 8;
        uVar2 = *(uint *)((int)lVar7 + 0x108);
        if (((ulonglong)uVar2 - 0x104 & 0xffffffff) < 0x71) {
          if (uVar2 < 0x174) {
            memset(uVar2 + uVar9,0,0x174 - (ulonglong)uVar2);
          }
          XeCryptSha(lVar7 + 0x17cU,
                     ((uVar11 & 0xffffffff) - (lVar7 + 0x17cU & 0xffffffff)) + (ulonglong)uVar12,
                     uVar11,(uVar9 & 0xffffffff) - (uVar11 & 0xffffffff),0,0,&local_50,0x14);
          iVar8 = XeCryptMemDiff(lVar7 + 0x164,&local_50,0x14);
          if (iVar8 == 0) {
            iVar8 = FUN_00029a68(uVar9,0);
            if (-1 < iVar8) {
              *(ulonglong *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x290) = uVar9;
              uVar5 = FUN_000298e8(0x40006);
              *(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar4 + 800) = uVar5;
              uVar6 = FUN_000298e8(0x4304);
              uVar5 = 0;
              *(undefined8 *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x310) = uVar6;
              goto LAB_0002b9e8;
            }
            uVar5 = 0xffffffffc8004005;
          }
          else {
            uVar5 = 0xffffffffc8004004;
          }
          goto LAB_0002b9bc;
        }
      }
      uVar5 = 0xffffffffc8004003;
    }
    else {
      uVar5 = 0xffffffffc8004002;
    }
  }
  else {
    uVar5 = 0xffffffffc8004001;
    iVar4 = iVar3;
  }
LAB_0002b9bc:
  lVar7 = *(longlong *)((int)DWORD_ARRAY_00016260 + iVar3 + 0x318);
  lVar13 = lVar7 + 0x10000;
  memset(lVar7,0,0x10000);
  *(longlong *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x290) = lVar13;
  *(longlong *)((int)DWORD_ARRAY_00016260 + iVar4 + 800) = lVar13;
  *(longlong *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x310) = lVar13;
LAB_0002b9e8:
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar5;
}



ulonglong FUN_0002bb08(void)

{
  ulonglong uVar1;
  qword back_chain;
  qword local_8;
  
  uVar1 = HvxTest();
  return uVar1 & 0xffffffff;
}



ulonglong * FUN_0002bb40(ulonglong param_1)

{
  ushort uVar1;
  int in_r2;
  ulonglong uVar2;
  ulonglong *puVar3;
  
  uVar2 = 0;
  uVar1 = *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x342);
  puVar3 = (ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x348);
  if (uVar1 != 0) {
    do {
      if ((*puVar3 >> 2 & 0x3f) == (param_1 & 0xffffffff)) {
        return puVar3;
      }
      uVar2 = uVar2 + 1;
      puVar3 = puVar3 + 1;
    } while ((uVar2 & 0xffffffff) < (ulonglong)uVar1);
  }
  return (ulonglong *)0;
}



undefined8 FUN_0002bb90(void)

{
  ushort uVar1;
  int in_r2;
  ulonglong uVar2;
  ulonglong *puVar3;
  ushort *puVar4;
  
  puVar4 = (ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x340);
  uVar1 = *(ushort *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x342);
  uVar2 = (ulonglong)uVar1;
  if (uVar1 != 0) {
    puVar3 = (ulonglong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x348);
    do {
      uVar2 = uVar2 - 1;
      *puVar3 = *puVar3 & 0xfffffffffffffffe;
      puVar3 = puVar3 + 1;
    } while ((uVar2 & 0xffffffff) != 0);
  }
  *puVar4 = *puVar4 & 0xfffe;
  return 0;
}



undefined8 FUN_0002bbe0(uint param_1)

{
  undefined8 uVar1;
  ulonglong *puVar2;
  qword back_chain;
  qword local_8;
  
  if (param_1 < 0x3f) {
    puVar2 = (ulonglong *)FUN_0002bb40();
    if (puVar2 == (ulonglong *)0x0) {
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



undefined8 FUN_0002bc40(uint param_1)

{
  undefined8 uVar1;
  ulonglong *puVar2;
  qword back_chain;
  qword local_8;
  
  if (param_1 < 0x3f) {
    puVar2 = (ulonglong *)FUN_0002bb40();
    if (puVar2 == (ulonglong *)0x0) {
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



undefined8 FUN_0002bca0(undefined8 param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  longlong in_r2;
  undefined8 uVar4;
  ulonglong uVar5;
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
  if ((*(ushort *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x340) & 2) == 0) {
    if (*(ushort *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x342) < 0x3f) {
      if ((((param_2 & 0xffffffff) < 0x3f) && ((param_3 & 0xffffffff) < 0x1000)) &&
         ((param_4 & 0xffffffff) < 0x1000)) {
        HvpSetRMCI(0);
        uVar5 = FUN_00029968(&local_1c0,uVar4,0,0x2c,1);
        HvpSetRMCI(1);
        if ((uVar5 & 0xffffffff) != 0) {
          XeCryptAesKey(&local_190,in_r2 + 0x16590);
          XeCryptAesEcb(&local_190,&local_1c0,&local_1c0,0);
          if (((((local_1c0 == 0x48000000) && (local_1bc == 0x485645)) &&
               ((local_1b8 == 0x48000000 &&
                (((ulonglong)local_198 <= (param_3 & 0xffffffff) &&
                 ((param_3 & 0xffffffff) < (ulonglong)(local_19c + local_198))))))) &&
              ((ulonglong)local_198 <= (param_4 & 0xffffffff))) &&
             ((param_4 & 0xffffffff) < (ulonglong)(local_19c + local_198))) {
            uVar1 = *(ushort *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x342);
            iVar3 = iVar2 + 0x165a8;
            *(short *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x342) = uVar1 + 1;
            uVar5 = (param_3 & 0xfff) << 0x28;
            iVar2 = (int)((longlong)(int)(uint)uVar1 << 3);
            *(ulonglong *)(iVar2 + iVar3) =
                 param_4 << 0x34 | *(ulonglong *)(iVar2 + iVar3) & 0xffffffffff | uVar5;
            *(ulonglong *)(iVar2 + iVar3) =
                 (((longlong)(int)(local_1b4 << 0x10) & 0xffffffffU |
                  (ulonglong)(local_1b0 & 0xffff)) << 6 | param_2 & 0x3f) << 2 |
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



// WARNING: Removing unreachable block (ram,0x0002c974)
// WARNING: Removing unreachable block (ram,0x0002c9a4)
// WARNING: Removing unreachable block (ram,0x0002c984)
// WARNING: Removing unreachable block (ram,0x0002c9b0)
// WARNING: Removing unreachable block (ram,0x0002c99c)
// WARNING: Removing unreachable block (ram,0x0002c9ac)

undefined8 FUN_0002c938(undefined8 param_1,undefined8 param_2)

{
  int in_r2;
  undefined8 uVar1;
  qword back_chain;
  
  __Save_R12_27_thru_31();
  uVar1 = *(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x6c);
  HvpAquireSpinLock(uVar1);
  FUN_000001e0(uVar1);
  return param_2;
}



undefined8 FUN_0002c9c8(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  longlong in_r2;
  int *piVar3;
  int iVar4;
  ulonglong uVar2;
  longlong lVar5;
  undefined8 uVar6;
  longlong lVar7;
  qword back_chain;
  word local_40;
  dword local_2c;
  
  piVar3 = (int *)__Save_R12_29_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  XeCryptSha(param_2,param_3,0,0,0,0,&local_40,0x14);
  iVar4 = XeCryptMemDiff(piVar3 + 3,&local_40,0x14);
  if (iVar4 != 0) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8003005;
  }
  if (*piVar3 == 0x43524c50) {
    lVar5 = ZEXT48(&PTR_DWORD_ARRAY_00010750) + in_r2;
LAB_0002ca50:
    lVar7 = 0;
LAB_0002ca54:
    uVar2 = FUN_000038d8(&local_40,piVar3 + 8,lVar5);
    if ((uVar2 & 0xffffffff) == 0) goto LAB_0002ca68;
  }
  else {
    if (*piVar3 == 0x43524c4c) {
      lVar5 = in_r2 + 0x10f90;
      lVar7 = in_r2 + 0x10a80;
      if (*(int *)((int)DWORD_ARRAY_00010760 + (int)in_r2 + 800) != 0x20) goto LAB_0002ca50;
      goto LAB_0002ca54;
    }
    lVar7 = 0;
LAB_0002ca68:
    uVar6 = 0xffffffffc8003003;
    if ((lVar7 == 0) ||
       (uVar2 = FUN_000038d8(&local_40,piVar3 + 8,lVar7), (uVar2 & 0xffffffff) == 0))
    goto LAB_0002ca94;
  }
  uVar6 = 0;
LAB_0002ca94:
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar6;
}



undefined8 FUN_0002cae8(undefined8 param_1,longlong param_2)

{
  undefined uVar1;
  uint uVar2;
  int in_r2;
  longlong lVar3;
  undefined8 uVar4;
  word *pwVar5;
  undefined *puVar6;
  longlong lVar7;
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
  uVar4 = FUN_0002c9c8(lVar3._4_4_,lVar3._4_4_ + 0x150,param_2 + -0x150);
  HvpReleaseSpinLock((ulonglong)uVar2);
  return uVar4;
}



void FUN_0002cbc0(undefined8 param_1,longlong param_2)

{
  undefined uVar1;
  uint uVar2;
  int in_r2;
  longlong lVar3;
  word *pwVar4;
  undefined *puVar5;
  longlong lVar6;
  qword back_chain;
  word local_1b0;
  word local_50;
  word local_40;
  dword local_30;
  
  lVar3 = __Save_R12_28_thru_31();
  puVar5 = (undefined *)(lVar3._4_4_ + 0x120);
  uVar2 = *(uint *)(in_r2 + 0x10000);
  FUN_00020060(puVar5,0x10);
  pwVar4 = &local_40;
  lVar6 = 0x10;
  do {
    uVar1 = *puVar5;
    puVar5 = puVar5 + 1;
    *(undefined *)pwVar4 = uVar1;
    pwVar4 = (word *)((int)pwVar4 + 1);
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  FUN_00020060(&local_50,0x10);
  XeCryptAesKey(&local_1b0,&local_50);
  XeCryptAesCbc(&local_1b0,lVar3._4_4_ + 0x140,0x10,lVar3 + 0x140,&local_40,1);
  XeCryptAesCbc(&local_1b0,lVar3._4_4_ + 0x150,param_2 + -0x150,lVar3 + 0x150,&local_40,1);
  XeCryptAesKey(&local_1b0,0x20);
  XeCryptAesEcb(&local_1b0,&local_50,lVar3._4_4_ + 0x130,1);
  HvpReleaseSpinLock((ulonglong)uVar2);
  return;
}



undefined8 FUN_0002cc98(undefined8 param_1,longlong param_2)

{
  undefined uVar1;
  uint uVar2;
  int in_r2;
  longlong lVar3;
  undefined8 uVar4;
  word *pwVar5;
  undefined *puVar6;
  longlong lVar7;
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
  uVar4 = FUN_0002c9c8(lVar3._4_4_,lVar3._4_4_ + 0x150,param_2 + -0x150);
  HvpReleaseSpinLock((ulonglong)uVar2);
  return uVar4;
}



void FUN_0002cd70(undefined8 param_1,longlong param_2,ulonglong param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int in_r2;
  longlong *plVar3;
  word *pwVar4;
  longlong lVar5;
  undefined *puVar6;
  longlong lVar7;
  qword back_chain;
  word local_180;
  word local_17c;
  word local_177;
  word local_60;
  word local_50;
  word local_40;
  dword local_30;
  
  plVar3 = (longlong *)__Save_R12_29_thru_31();
  uVar1 = *(uint *)(in_r2 + 0x10000);
  memcpy(&local_180);
  pwVar4 = &local_17c;
  lVar5 = *(longlong *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x104) + 0x9ca;
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
  memset((param_3 & 0xffffffff) + plVar3[1],0,(ulonglong)*(uint *)(plVar3 + 2) - (param_3 + 0x150));
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_0002ce68(void)

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
  XeCryptSha(*(longlong *)((int)DWORD_ARRAY_0001613c + in_r2 + 100) + 0x14,0x3ec,0,0,0,0,&local_30,
             0x14);
  iVar2 = XeCryptMemDiff(*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 100),&local_30,0x14);
  if (iVar2 != 0) {
    _v_MACHINE_CHECK_0();
  }
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

longlong FUN_0002cef0(longlong param_1)

{
  int in_r2;
  longlong lVar1;
  uint uVar2;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  FUN_0002ce68();
  if (param_1 != 0) {
    lVar1 = *(longlong *)((int)DWORD_ARRAY_0001613c + in_r2 + 100) + 0x20;
    uVar2 = 0;
    do {
      if (*(longlong *)lVar1 == param_1) {
        return lVar1;
      }
      uVar2 = uVar2 + 1;
      lVar1 = lVar1 + 0x10;
    } while (uVar2 < 0x3e);
  }
  return 0;
}



// WARNING: Could not reconcile some variable overlaps

undefined8 FUN_0002cf58(void)

{
  uint uVar1;
  uint uVar2;
  longlong in_r2;
  undefined8 uVar3;
  int iVar5;
  ulonglong uVar4;
  int iVar6;
  longlong lVar7;
  longlong *plVar8;
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
  lVar7 = *(longlong *)((int)DWORD_ARRAY_0001613c + (int)in_r2 + 0x104);
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  memcpy(&local_1f0,uVar3,0x1a8);
  iVar5 = XeCryptMemDiff(&local_1f0,lVar7 + 0x9c8,0x1a8);
  if ((iVar5 == 0) || (((*(uint *)((int)lVar7 + 0x9e0) ^ local_1d8) & 0xffffff) != 0)) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8003005;
  }
  XeCryptSha(&local_1f0,0xa8,0,0,0,0,&local_40,0x14);
  uVar4 = FUN_000038d8(&local_40,&local_148,in_r2 + 0x111b0);
  iVar5 = (int)in_r2;
  if ((uVar4 & 0xffffffff) == 0) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8003003;
  }
  lVar7 = ((ulonglong)_local_1ee & 0xffffffffff00) << 0x10;
  HvpAquireSpinLock(in_r2 + 0x16178);
  iVar6 = FUN_0002cef0(lVar7);
  if (iVar6 == 0) {
    iVar6 = (int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar5 + 100);
    uVar2 = *(uint *)(iVar6 + 0x14);
    if (0x3d < uVar2) {
      uVar3 = 0xffffffffc8003004;
      goto LAB_0002d0a8;
    }
    plVar8 = (longlong *)((uVar2 + 2) * 0x10 + iVar6);
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
  lVar7 = *(longlong *)((int)DWORD_ARRAY_0001613c + iVar5 + 100);
  XeCryptSha(lVar7 + 0x14,0x3ec,0,0,0,0,lVar7,0x14);
LAB_0002d0a8:
  FUN_000001e0(in_r2 + 0x16178);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar3;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_0002d6e8(void)

{
  int iVar1;
  longlong in_r2;
  int iVar2;
  longlong lVar3;
  longlong lVar4;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  lVar3 = FUN_00000298();
  lVar4 = FUN_00000270();
  iVar1 = (int)lVar3;
  iVar2 = (int)in_r2;
  *(longlong *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x2c) = lVar3 + 0xa000;
  *(longlong *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x24) = lVar3 + 0xc000;
  *(longlong *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x1c) = lVar4 + 0xfe00;
  *(longlong *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x14) = lVar3 + 0x8000;
  memcpy(lVar4 + 0xfe00,in_r2 + 0x11b28,0x21);
  *(word *)(iVar1 + 0x8600) = 0;
  *(undefined2 *)(iVar1 + 0x8608) = *(undefined2 *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x6bc);
  *(undefined **)(iVar1 + 0x8610) = (undefined *)0x8000;
  *(undefined4 *)(iVar1 + 0x861c) = *(undefined4 *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x6cc);
  return;
}



void FUN_0002d798(ulonglong param_1)

{
  byte bVar1;
  int iVar2;
  int in_r2;
  
  iVar2 = (int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x104);
  bVar1 = *(byte *)(iVar2 + 0x1a);
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 2) != 0) {
      param_1 = *(ulonglong *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x34) & param_1;
    }
  }
  else {
    param_1 = 0;
  }
  *(ulonglong *)(iVar2 + 0x30) = param_1;
  *(ulonglong *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14) + 0x630) = param_1;
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_0002d7e8(void)

{
  ushort uVar1;
  longlong in_r2;
  int iVar2;
  int iVar3;
  longlong lVar4;
  ushort uVar5;
  qword local_10;
  qword local_8;
  
  iVar2 = (int)in_r2;
  lVar4 = *(longlong *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x104);
  iVar3 = (int)lVar4;
  uVar1 = *(ushort *)(iVar3 + 0x1c);
  if ((*(ushort *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x6bc) & 4) == 0) {
    uVar5 = uVar1;
    if (*(longlong *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x6c0) - 0x710700U < 0x200) {
      lVar4 = lVar4 + 0xb72;
      uVar5 = uVar1 | 0x40;
      if (*(int *)(iVar3 + 0xc82) != 0x4f534947) {
        _v_MACHINE_CHECK_0();
      }
      iVar2 = (int)in_r2;
      iVar3 = XeCryptMemDiff(lVar4 + 0x120,ZEXT48("PLDS    DG-16D4S        9504") + in_r2,0x1c);
      if (iVar3 == 0) {
        uVar5 = uVar1 & 0xffdf | 0x40;
      }
    }
  }
  else {
    uVar5 = 0;
  }
  *(ushort *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar2 + 0x14) + 0x604) = uVar5;
  return;
}



// WARNING: Removing unreachable block (ram,0x0002d950)

void FUN_0002d8c0(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong in_r2;
  undefined8 uVar5;
  ulonglong uVar6;
  longlong lVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  longlong lVar10;
  word local_1d0;
  word local_70;
  word local_60;
  dword local_50;
  
  uVar5 = __Save_R12_25_thru_31();
  iVar4 = (int)in_r2;
  uVar1 = *(uint *)(iVar4 + 0x10000);
  lVar10 = *(longlong *)((int)DWORD_ARRAY_0001613c + iVar4 + 0x2c);
  lVar7 = *(longlong *)((int)DWORD_ARRAY_0001613c + iVar4 + 0x104);
  *(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar4 + 0x34) = uVar5;
  iVar2 = (int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar4 + 0x14);
  *(word *)(iVar2 + 0x600) = 0;
  *(undefined2 *)(iVar2 + 0x608) = *(undefined2 *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x6bc);
  *(undefined2 *)(iVar2 + 0x60a) = *(undefined2 *)((int)DWORD_ARRAY_00016260 + iVar4 + 0x6b4);
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
  FUN_0002d798(uVar5);
  FUN_0002d7e8();
  *(undefined4 *)(iVar2 + 0x618) = uVar9;
  *(undefined4 *)(iVar2 + 0x620) = uVar8;
  memcpy(lVar10,lVar7 + 0x9c8,0x1a8);
  *(undefined4 *)((int)lVar10 + 0x1a8) = 0x71;
  lVar7 = in_r2;
  memcpy(lVar10 + 0x1b0,ZEXT48(&PTR_DWORD_ARRAY_00010750) + in_r2,0x110);
  memcpy(lVar10 + 0x2c0,lVar7 + 0x10f90,0x110);
  memcpy(lVar10 + 0x3d0,lVar7 + 0x111b0,0x110);
  memcpy(lVar10 + 0x4e0,lVar7 + 0x112c0,0x110);
  memcpy(lVar10 + 0x5f0,lVar7 + 0x113d0,0x110);
  memcpy(lVar10 + 0x810,in_r2 + 0x10a80,0x110);
  XeCryptSha(0x20,0x10,0,0,0,0,lVar10 + 0xa30,0x10);
  FUN_00003620(*(undefined8 *)((int)DWORD_ARRAY_0001613c + iVar4 + 0x104),lVar10 + 0xa40,0x10);
  FUN_0000a458(&local_60);
  XeCryptAesKey(&local_1d0,&local_60);
  XeCryptAesEcb(&local_1d0,&local_70,lVar10 + 0xa50,1);
  uVar5 = HvpGetFlashBaseAddress();
  FUN_00000484(lVar10 + 0xa60,uVar5,0x10);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

void FUN_0002da88(void)

{
  int iVar1;
  int in_r2;
  undefined4 uVar2;
  longlong lVar3;
  int iVar4;
  qword back_chain;
  qword local_18;
  qword local_10;
  qword local_8;
  
  iVar4 = in_r2 + 0x16144;
  lVar3 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x248);
  HvpAquireSpinLock(iVar4);
  iVar1 = (int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14);
  if (*(short *)(iVar1 + 0x602) == 0x102) {
    uVar2 = 0x107;
  }
  else {
    uVar2 = 0x70000;
  }
  *(undefined4 *)(iVar1 + 0x614) = uVar2;
  iVar1 = (int)lVar3;
  *(undefined8 *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14) + 0x638) =
       *(undefined8 *)(iVar1 + 0x28);
  *(undefined8 *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14) + 0x640) =
       *(undefined8 *)(iVar1 + 0x30);
  memcpy(*(longlong *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14) + 0x700,lVar3 + 0x38,0x80);
  FUN_0002d7e8();
  FUN_000001e0(iVar4);
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_0002ddc8(ulonglong *param_1)

{
  int in_r2;
  int iVar1;
  short sVar2;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  iVar1 = in_r2 + 0x10000;
  FUN_0002d798(*(ulonglong *)
                ((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x104) + 0x30) & ~*param_1
               | param_1[1]);
  sVar2 = *(short *)(param_1 + 2);
  if (sVar2 != 0) {
    *(short *)((int)*(undefined8 *)(HvxKeysExCreateKeyVault + iVar1) + 200) = sVar2;
    if (sVar2 == 0x7fff) {
      FUN_00003830(0x1000,0);
      sVar2 = *(short *)((int)param_1 + 0x12);
    }
    *(short *)((int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14) + 0x602) = sVar2;
  }
  return 0;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_00030000(void)

{
  longlong in_r2;
  longlong lVar1;
  qword back_chain;
  qword local_10;
  qword local_8;
  
  lVar1 = in_r2 + 0x16cd4;
  HvpAquireSpinLock(lVar1);
  FUN_0000b488(in_r2 + 0x16d18,4);
  FUN_000001e0(lVar1);
  return;
}



longlong FUN_00030050(undefined8 param_1,longlong param_2)

{
  uint uVar1;
  longlong in_r2;
  int iVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  longlong lVar5;
  uint uVar6;
  
  uVar3 = __Save_R12_27_thru_31();
  iVar2 = (int)in_r2;
  lVar5 = 0;
  uVar6 = 0;
  HvpAquireSpinLock(in_r2 + 0x16cd4);
  uVar4 = 0;
  uVar1 = *(uint *)((int)DWORD_ARRAY_00016a20 + iVar2 + 0x2ec);
  if (uVar1 != 0) {
    do {
      if ((ulonglong)*(uint *)((int)(uVar4 << 3) + iVar2 + 0x16d10) == (uVar3 & 0xffffffff)) {
        uVar6 = *(uint *)((int)(uVar4 << 3) + iVar2 + 0x16d14);
        break;
      }
      uVar4 = uVar4 + 1;
    } while ((uVar4 & 0xffffffff) < (ulonglong)uVar1);
  }
  if ((uVar6 & 0x10) == 0) {
    if (param_2 != 0) {
      uVar3 = 0;
      do {
        if (lVar5 != 0) break;
        if ((1 << uVar3 & uVar6) != 0) {
          uVar4 = 0;
          do {
            if (*(longlong *)((int)(uVar3 << 3) + iVar2 + 0x16ce8) ==
                *(longlong *)((int)(uVar4 << 3) + (int)param_2)) {
              lVar5 = 1;
              break;
            }
            uVar4 = uVar4 + 1;
          } while ((uVar4 & 0xffffffff) < 4);
        }
        uVar3 = uVar3 + 1;
      } while ((uVar3 & 0xffffffff) < 4);
      goto LAB_000300ec;
    }
    if (uVar6 == 0) goto LAB_000300ec;
  }
  lVar5 = 1;
LAB_000300ec:
  FUN_000001e0(in_r2 + 0x16cd4);
  return lVar5;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

ulonglong FUN_00030170(void)

{
  uint uVar1;
  int in_r2;
  int iVar2;
  qword local_18;
  qword local_10;
  qword local_8;
  
  iVar2 = in_r2 + 0x16cd4;
  HvpAquireSpinLock(iVar2);
  uVar1 = *(uint *)((int)DWORD_ARRAY_00016a20 + in_r2 + 0x2f8);
  FUN_000001e0(iVar2);
  return (ulonglong)uVar1;
}



undefined8 FUN_000301c0(undefined8 param_1,ulonglong param_2)

{
  uint uVar1;
  longlong in_r2;
  undefined8 uVar2;
  ulonglong uVar3;
  int iVar4;
  longlong lVar5;
  uint uVar7;
  longlong lVar6;
  word local_1e0;
  word local_180;
  word local_80;
  word local_58;
  dword local_54;
  word local_50;
  word local_40;
  dword local_2c;
  
  uVar2 = __Save_R12_29_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if ((param_2 & 0xffffffff) == 0x138) {
    uVar2 = HvpPhysicalToReal(uVar2,0x138);
    memcpy(&local_180,uVar2,0x138);
    if ((local_54 == 0) || (1 < local_54)) {
      uVar2 = 0xffffffffc8005002;
    }
    else {
      j_XeCryptShaInit(&local_1e0);
      j_XeCryptShaUpdate(&local_1e0,&local_80,0x30);
      uVar7 = 0;
      if (local_54 != 0) {
        do {
          j_XeCryptShaUpdate(&local_1e0,&local_50 + uVar7 * 4,8);
          uVar7 = uVar7 + 1;
        } while (uVar7 < local_54);
      }
      j_XeCryptShaFinal(&local_1e0,&local_40,0x14);
      uVar3 = FUN_000038d8(&local_40,&local_180,in_r2 + 0x10f90);
      if (((uVar3 & 0xffffffff) == 0) &&
         ((*(int *)((int)DWORD_ARRAY_00010760 + (int)in_r2 + 800) != 0x20 ||
          (uVar3 = FUN_000038d8(&local_40,&local_180,in_r2 + 0x10a80), (uVar3 & 0xffffffff) == 0))))
      {
        uVar2 = 0xffffffffc8005000;
      }
      else {
        lVar5 = in_r2 + 0x16cd4;
        HvpAquireSpinLock(lVar5);
        lVar6 = in_r2 + 0x16d18;
        iVar4 = j_XeCryptMemDiff(lVar6,&local_58,4);
        if (iVar4 == 0) {
          uVar2 = 0;
          memcpy(in_r2 + 0x16ce0,&local_80,0x38);
          FUN_0000b488(lVar6,4);
        }
        else {
          uVar2 = 0xffffffffc8005001;
        }
        FUN_000001e0(lVar5);
      }
    }
    HvpReleaseSpinLock((ulonglong)uVar1);
  }
  else {
    HvpReleaseSpinLock((ulonglong)uVar1);
    uVar2 = 0xffffffffc8000004;
  }
  return uVar2;
}



void FUN_00030360(undefined8 param_1)

{
  qword local_30;
  qword local_28;
  qword local_20;
  qword local_18;
  qword local_8;
  
  FUN_00030050(param_1,&local_30);
  return;
}



void FUN_00030398(void)

{
  int in_r2;
  undefined8 uVar1;
  qword local_8;
  
  uVar1 = FUN_000002b8();
  *(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6f8) = uVar1;
  *(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6f0) = uVar1;
  FUN_0000b0d0(1,0xf,1);
  FUN_0000b0d0(2,0xe,1);
  return;
}



void FUN_000303f0(undefined8 param_1,int param_2,longlong param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int in_r2;
  longlong lVar5;
  ulonglong uVar6;
  uint *puVar7;
  uint uVar8;
  
  lVar5 = __Save_R12_25_thru_31();
  puVar7 = (uint *)param_3;
  uVar1 = puVar7[1];
  uVar2 = puVar7[2];
  iVar4 = (int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6f0);
  uVar8 = *(uint *)(iVar4 + 8);
  uVar3 = *(uint *)(iVar4 + 4);
  memcpy((ulonglong)uVar8 + lVar5 + 0x3000,(ulonglong)*puVar7 + param_3,
         (ulonglong)uVar1 - (ulonglong)*puVar7);
  memcpy((ulonglong)uVar3 + lVar5 + 0x2000,(ulonglong)uVar1 + param_3,(ulonglong)uVar2);
  uVar8 = uVar8 + 0x90003000;
  uVar6 = (ulonglong)(uVar8 >> 0xc & 0xffff);
  *(int *)(param_2 + 0xc) = uVar3 + 0x90002000;
  *(uint *)(param_2 + 8) = uVar8;
  FUN_0000b0d0(uVar6,9,(uVar8 + uVar1 + 0xfff >> 0xc & 0xffff) - uVar6);
  return;
}



undefined8 FUN_00030488(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int in_r2;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  longlong lVar8;
  uint uVar9;
  uint *puVar10;
  uint *puVar11;
  undefined4 *puVar12;
  
  iVar4 = __Save_R12_23_thru_31();
  if ((((*(uint *)(iVar4 + 0x138) != 0) && (0x4488 < *(uint *)(iVar4 + 0x138))) ||
      ((*(uint *)(iVar4 + 0x13c) != 0 && (*(uint *)(iVar4 + 0x13c) < 0x4489)))) ||
     ((iVar3 = (int)*(undefined8 *)((int)DWORD_ARRAY_0001613c + in_r2 + 0x14),
      (*(uint *)(iVar3 + 0x610) & *(uint *)(iVar4 + 0x134)) != *(uint *)(iVar4 + 0x134) ||
      ((*(ulonglong *)(iVar3 + 0x630) & *(ulonglong *)(iVar4 + 0x148)) !=
       *(ulonglong *)(iVar4 + 0x148))))) {
    return 0xffffffffc8007004;
  }
  lVar8 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6f8);
  puVar10 = (uint *)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6f0);
  uVar1 = *puVar10;
  if (3 < uVar1) {
    return 0xffffffffc8007006;
  }
  if (*(uint *)(iVar4 + 0x154) == 0) {
    puVar5 = (uint *)0x0;
  }
  else {
    puVar5 = (uint *)(*(int *)(iVar4 + 0x150) + iVar4);
  }
  if (*(uint *)(iVar4 + 0x15c) == 0) {
    puVar11 = (uint *)0x0;
  }
  else {
    puVar11 = (uint *)(*(int *)(iVar4 + 0x158) + iVar4);
  }
  if (puVar5 == (uint *)0x0) {
    uVar7 = 0;
    uVar6 = 0;
  }
  else {
    uVar7 = puVar5[1];
    uVar6 = puVar5[2];
    if ((*puVar5 & 0xf) != 0) {
      return 0xffffffffc8007002;
    }
    if ((uVar7 & 0xf) != 0) {
      return 0xffffffffc8007002;
    }
    if ((uVar6 & 0xf) != 0) {
      return 0xffffffffc8007002;
    }
    if (uVar7 <= *puVar5) {
      return 0xffffffffc8007002;
    }
    if (*(uint *)(iVar4 + 0x154) < uVar6 + uVar7) {
      return 0xffffffffc8007002;
    }
    if (0x5000 < puVar10[2] + uVar7) {
      return 0xffffffffc8007007;
    }
    if (0x1000 < puVar10[1] + uVar6) {
      return 0xffffffffc8007008;
    }
  }
  if (puVar11 == (uint *)0x0) {
    uVar9 = 0;
  }
  else {
    uVar9 = puVar11[2] + puVar11[1];
    if (((((*puVar11 & 0xf) != 0) || ((uVar9 & 0xf) != 0)) || (uVar9 <= *puVar11)) ||
       (*(uint *)(iVar4 + 0x15c) < uVar9)) {
      return 0xffffffffc8007002;
    }
    if (0x8000 < puVar10[3] + uVar9) {
      return 0xffffffffc8007009;
    }
  }
  uVar2 = *(undefined4 *)(iVar4 + 0x130);
  puVar12 = (undefined4 *)((uVar1 + 0x40) * 0x10 + (int)lVar8);
  if (puVar5 != (uint *)0x0) {
    *(undefined4 *)((uVar1 + 0x100) * 0x10 + (int)lVar8) = uVar2;
    FUN_000303f0(lVar8);
  }
  if (puVar11 != (uint *)0x0) {
    *puVar12 = uVar2;
    uVar1 = *puVar11;
    lVar8 = (ulonglong)
            *(uint *)((int)*(undefined8 *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6f0) + 0xc) + lVar8
            + 0x8000;
    memcpy(lVar8,puVar11,(ulonglong)puVar11[2] + (ulonglong)puVar11[1]);
    puVar12[1] = uVar1;
    *(longlong *)(puVar12 + 2) = lVar8;
  }
  *puVar10 = *puVar10 + 1;
  puVar10[1] = puVar10[1] + uVar6;
  puVar10[2] = puVar10[2] + uVar7;
  puVar10[3] = puVar10[3] + uVar9;
  return 0;
}



undefined8 FUN_00030710(undefined8 param_1,ulonglong param_2)

{
  uint uVar1;
  longlong in_r2;
  ulonglong uVar2;
  longlong lVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  qword local_1c0;
  dword local_1b4;
  word local_1b0;
  word local_50;
  dword local_3c;
  
  uVar2 = __Save_R12_27_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if ((uVar2 & 0x7f) != 0) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8007000;
  }
  if (((param_2 & 0x7f) != 0) ||
     (((((uint)uVar2 + (uint)param_2) - 1 ^ (uint)uVar2) & 0xffff0000) != 0)) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8007001;
  }
  lVar5 = in_r2 + 0x16918;
  HvpAquireSpinLock(lVar5);
  lVar3 = func_0x000033d8(uVar2,param_2,0x3a);
  if (*lVar3._4_4_ == 0x48585052) {
    lVar7 = in_r2 + 0x16280;
    if ((lVar3._4_4_[1] & 3U) == 0) {
      lVar6 = in_r2 + 0x16270;
      j_XeCryptRotSumSha(lVar3._4_4_,0x30,0,0,&local_50,0x14);
LAB_00030880:
      iVar4 = FUN_0000b3c0(lVar3._4_4_ + 0xc,&local_50,ZEXT48(&UNK_00010404) + in_r2,lVar7);
      if ((iVar4 != 0) && ((ulonglong)(uint)lVar3._4_4_[2] <= (param_2 & 0xffffffff))) {
        if (lVar6 != 0) {
          j_XeCryptAesKey(&local_1b0,lVar6);
          j_XeCryptAesCbc(&local_1b0,lVar3._4_4_ + 0x4c,(ulonglong)(uint)lVar3._4_4_[2] - 0x130,
                          lVar3 + 0x130,lVar3._4_4_ + 8,0);
        }
        j_XeCryptSha(lVar3._4_4_ + 0x4c,(ulonglong)(uint)lVar3._4_4_[2] - 0x130,0,0,0,0,&local_50,
                     0x14);
        iVar4 = j_XeCryptMemDiff(lVar3._4_4_ + 3,&local_50,0x14);
        if (iVar4 == 0) {
          uVar8 = FUN_00030488(lVar3._4_4_);
          goto LAB_00030938;
        }
      }
    }
  }
  else {
    if ((*lVar3._4_4_ != 0x48585043) ||
       (lVar7 = *(longlong *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x6f0) + 0x200,
       *(int *)lVar7 != 0x20)) {
      uVar8 = 0xffffffffc8007002;
      goto LAB_00030938;
    }
    if ((lVar3._4_4_[1] & 3U) == 3) {
      lVar6 = 0x20;
      j_XeCryptHmacSha(0x20,0x10,lVar3._4_4_,0x30,0,0,0,0);
      goto LAB_00030880;
    }
  }
  uVar8 = 0xffffffffc8007003;
LAB_00030938:
  HvpZeroCacheLines(lVar3._4_4_,(ulonglong)((uint)param_2 >> 7));
  HvpRelocateProtectedToPhysical(lVar3._4_4_,param_2,0x3a);
  FUN_000001e0(lVar5);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar8;
}



undefined8 FUN_00030970(int param_1)

{
  int in_r2;
  undefined8 uVar1;
  uint uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  lVar3 = *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x6f8) + 0x400;
  do {
    if (*(int *)lVar3 == param_1) goto LAB_000309a0;
    uVar2 = uVar2 + 1;
    lVar3 = lVar3 + 0x10;
  } while (uVar2 < 4);
  lVar3 = 0;
LAB_000309a0:
  if (lVar3 == 0) {
    return 0xffffffffc8007005;
  }
                    // WARNING: Could not recover jumptable at 0x000309c4. Too many branches
                    // WARNING: Treating indirect jump as call
  uVar1 = (*(code *)(*(int *)((int)lVar3 + 4) + (int)*(undefined8 *)((int)lVar3 + 8)))();
  return uVar1;
}



void FUN_000309c8(void)

{
  int in_r2;
  longlong lVar1;
  qword local_8;
  
  lVar1 = FUN_00000270();
  *(longlong *)((int)DWORD_ARRAY_00016260 + in_r2 + 0x280) = lVar1 + 0xfc00;
  return;
}



undefined8
FUN_000309f8(undefined8 param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4,
            ulonglong param_5,int param_6)

{
  undefined uVar1;
  uint uVar2;
  longlong in_r2;
  ulonglong uVar3;
  undefined8 uVar4;
  undefined *puVar5;
  word *pwVar6;
  longlong lVar7;
  longlong lVar8;
  word local_1b0;
  word local_50;
  word local_40;
  dword local_30;
  
  uVar3 = __Save_R12_29_thru_31();
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  if ((uVar3 & 0xffffffff) < 0x10) {
    if ((param_2 & 0xffffffff) < 4) {
      if (((param_4 & 0xffffffff) == 0x10) && (param_6 == 0x10)) {
        if (((param_3 & 0xf) == 0) && ((param_5 & 0xf) == 0)) {
          lVar7 = *(longlong *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x280);
          puVar5 = (undefined *)HvpPhysicalToReal(param_3,0x10);
          pwVar6 = &local_50;
          lVar8 = 0x10;
          do {
            uVar1 = *puVar5;
            puVar5 = puVar5 + 1;
            *(undefined *)pwVar6 = uVar1;
            pwVar6 = (word *)((int)pwVar6 + 1);
            lVar8 = lVar8 + -1;
          } while (lVar8 != 0);
          puVar5 = (undefined *)HvpPhysicalToReal(param_5,0x10);
          pwVar6 = &local_40;
          lVar8 = 0x10;
          do {
            uVar1 = *puVar5;
            puVar5 = puVar5 + 1;
            *(undefined *)pwVar6 = uVar1;
            pwVar6 = (word *)((int)pwVar6 + 1);
            lVar8 = lVar8 + -1;
          } while (lVar8 != 0);
          HvpAquireSpinLock(in_r2 + 0x164e8);
          j_XeCryptAesKey(&local_1b0,((param_2 & 0xffffffff) + 0x10) * 0x10 + lVar7);
          j_XeCryptAesCtr(&local_1b0,&local_50,0x10,(uVar3 & 0xffffffff) * 0x10 + lVar7,&local_40);
          FUN_000001e0(in_r2 + 0x164e8);
          HvpReleaseSpinLock((ulonglong)uVar2);
          uVar4 = 0;
        }
        else {
          HvpReleaseSpinLock((ulonglong)uVar2);
          uVar4 = 0xffffffffc8006006;
        }
      }
      else {
        HvpReleaseSpinLock((ulonglong)uVar2);
        uVar4 = 0xffffffffc8006005;
      }
    }
    else {
      HvpReleaseSpinLock((ulonglong)uVar2);
      uVar4 = 0xffffffffc8006003;
    }
  }
  else {
    HvpReleaseSpinLock((ulonglong)uVar2);
    uVar4 = 0xffffffffc8006002;
  }
  return uVar4;
}



// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00030b70(ulonglong param_1,int param_2,undefined8 param_3,ulonglong param_4)

{
  longlong in_r2;
  undefined8 uVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  longlong lVar5;
  longlong lVar6;
  dword local_140;
  qword local_138;
  word local_120;
  qword local_18;
  qword local_10;
  qword local_8;
  
  if ((param_1 & 0xffffffff) < 4) {
    if (param_2 == 0x103) {
      lVar5 = *(longlong *)((int)DWORD_ARRAY_0001613c + (int)in_r2 + 0xdc) + 0xa18;
    }
    else {
      if (param_2 != 0x104) {
        return 0xffffffffc8006004;
      }
      lVar5 = *(longlong *)((int)DWORD_ARRAY_0001613c + (int)in_r2 + 0xdc) + 0xda8;
    }
    if ((param_4 & 0xffffffff) == (ulonglong)*(uint *)lVar5 << 3) {
      if (((((uint)param_3 + (int)param_4) - 1 ^ (uint)param_3) & 0xfffff000) == 0) {
        uVar1 = HvpPhysicalToReal(param_3,param_4);
        j_XeCryptBnQw_SwapDwQwLeBe(uVar1,&local_120,0x20);
        iVar2 = j_HvxKeysRsaPrvCrypt(&local_120,&local_120,lVar5);
        if (iVar2 == 0) {
          uVar1 = 0xffffffffc8006007;
        }
        else {
          j_XeCryptBnQw_SwapDwQwLeBe(&local_120,&local_120,0x20);
          FUN_0000b480(&local_120,0x100);
          iVar3 = FUN_0000b430(&local_120,0x100,&local_138,&local_140,0);
          iVar2 = (int)in_r2;
          if (iVar3 == 0) {
            uVar1 = 0xffffffffc8006008;
          }
          else {
            if (local_140 == 0x10) {
              HvpAquireSpinLock(in_r2 + 0x164e8);
              lVar5 = ((param_1 & 0xffffffff) + 0x10) * 0x10 +
                      *(longlong *)((int)DWORD_ARRAY_00016260 + iVar2 + 0x280);
              lVar6 = 0x10;
              do {
                puVar4 = (undefined *)local_138;
                local_138 = local_138 + 1;
                *(undefined *)lVar5 = *puVar4;
                lVar5 = lVar5 + 1;
                lVar6 = lVar6 + -1;
              } while (lVar6 != 0);
              FUN_000001e0(in_r2 + 0x164e8);
              uVar1 = 0;
            }
            else {
              uVar1 = 0xffffffffc8006009;
            }
          }
        }
      }
      else {
        uVar1 = 0xffffffffc8006006;
      }
    }
    else {
      uVar1 = 0xffffffffc8006005;
    }
  }
  else {
    uVar1 = 0xffffffffc8006003;
  }
  return uVar1;
}



undefined8
FUN_00030d28(undefined8 param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4,
            ulonglong param_5,ulonglong param_6,undefined8 param_7)

{
  uint uVar1;
  longlong in_r2;
  int iVar3;
  undefined8 uVar2;
  longlong lVar4;
  longlong lVar5;
  word local_50;
  dword local_40;
  
  iVar3 = __Save_R12_26_thru_31();
  uVar1 = *(uint *)((int)in_r2 + 0x10000);
  if (iVar3 == 0) {
    if (0xf < (param_2 & 0xffffffff)) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8006002;
    }
    lVar4 = (param_2 & 0xffffffff) << 4;
  }
  else {
    if (iVar3 != 1) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8006001;
    }
    if (3 < (param_2 & 0xffffffff)) {
      HvpReleaseSpinLock((ulonglong)uVar1);
      return 0xffffffffc8006003;
    }
    lVar4 = ((param_2 & 0xffffffff) + 0x10) * 0x10;
  }
  lVar5 = *(longlong *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x280);
  if ((0x1000 < (param_4 & 0xffffffff)) || ((param_6 & 0xffffffff) != 0x10)) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8006005;
  }
  if (((param_3 & 0xfff) != 0) || ((param_5 & 0xf) != 0)) {
    HvpReleaseSpinLock((ulonglong)uVar1);
    return 0xffffffffc8006006;
  }
  HvpAquireSpinLock(in_r2 + 0x164e8);
  uVar2 = HvpPhysicalToReal(param_3,param_4);
  iVar3 = FUN_0000b478(uVar2,param_4,lVar4 + lVar5,0x10,&local_50,param_7);
  if (iVar3 != 0) {
    uVar2 = HvpPhysicalToReal(param_5,0x10);
    iVar3 = j_XeCryptMemDiff(uVar2,&local_50,0x10);
    if (iVar3 == 0) {
      uVar2 = 0;
      goto LAB_00030e78;
    }
  }
  uVar2 = 0xffffffffc800600a;
LAB_00030e78:
  FUN_000001e0(in_r2 + 0x164e8);
  HvpReleaseSpinLock((ulonglong)uVar1);
  return uVar2;
}



undefined8
FUN_00030ea8(undefined8 param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4,int param_5)

{
  bool bVar1;
  undefined uVar2;
  uint uVar3;
  char cVar4;
  longlong in_r2;
  ulonglong uVar5;
  undefined8 uVar6;
  int iVar7;
  undefined *puVar8;
  undefined *puVar10;
  longlong lVar9;
  word *pwVar11;
  int iVar12;
  longlong lVar13;
  word local_1a0;
  word local_40;
  dword local_30;
  
  uVar5 = __Save_R12_28_thru_31();
  uVar3 = *(uint *)((int)in_r2 + 0x10000);
  if (0xf < (uVar5 & 0xffffffff)) {
    HvpReleaseSpinLock((ulonglong)uVar3);
    return 0xffffffffc8006002;
  }
  if ((param_2 & 0xfff) == 0) {
    if ((param_3 & 0xffffffff) == 0x1000) {
      if ((param_4 & 0xf) != 0) goto LAB_00030ef0;
      if (param_5 == 0x10) {
        puVar8 = (undefined *)HvpPhysicalToReal(param_4,0x10);
        pwVar11 = &local_40;
        lVar13 = 0x10;
        puVar10 = puVar8;
        do {
          uVar2 = *puVar10;
          puVar10 = puVar10 + 1;
          *(undefined *)pwVar11 = uVar2;
          pwVar11 = (word *)((int)pwVar11 + 1);
          lVar13 = lVar13 + -1;
        } while (lVar13 != 0);
        lVar9 = *(longlong *)((int)DWORD_ARRAY_00016260 + (int)in_r2 + 0x280);
        lVar13 = HvpPhysicalToReal(param_2,0x1000);
        HvpAquireSpinLock(in_r2 + 0x164e8);
        j_XeCryptAesKey(&local_1a0,(uVar5 & 0xffffffff) * 0x10 + lVar9);
        FUN_000001e0(in_r2 + 0x164e8);
        iVar12 = 0x100;
        do {
          j_XeCryptAesEcb(&local_1a0,&local_40,lVar13,1);
          iVar7 = 0xf;
          do {
            cVar4 = *(char *)(iVar7 + (int)&local_40) + '\x01';
            *(char *)(iVar7 + (int)&local_40) = cVar4;
            if (cVar4 != '\0') break;
            bVar1 = iVar7 != 0;
            iVar7 = iVar7 + -1;
          } while (bVar1);
          iVar12 = iVar12 + -1;
          lVar13 = lVar13 + 0x10;
          if (iVar12 == 0) {
            pwVar11 = &local_40;
            lVar13 = 0x10;
            do {
              uVar2 = *(undefined *)pwVar11;
              pwVar11 = (word *)((int)pwVar11 + 1);
              *puVar8 = uVar2;
              puVar8 = puVar8 + 1;
              lVar13 = lVar13 + -1;
            } while (lVar13 != 0);
            HvpReleaseSpinLock((ulonglong)uVar3);
            return 0;
          }
        } while( true );
      }
    }
    HvpReleaseSpinLock((ulonglong)uVar3);
    uVar6 = 0xffffffffc8006005;
  }
  else {
LAB_00030ef0:
    HvpReleaseSpinLock((ulonglong)uVar3);
    uVar6 = 0xffffffffc8006006;
  }
  return uVar6;
}



undefined8 FUN_00031048(undefined8 param_1,ulonglong param_2,ulonglong param_3)

{
  longlong in_r2;
  int iVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  
  uVar2 = __Save_R12_29_thru_31();
  iVar1 = (int)in_r2;
  if ((uVar2 & 0xffffffff) < 4) {
    if ((param_2 & 0xfff) == 0) {
      if ((param_3 & 0xffffffff) == 0x14) {
        HvpAquireSpinLock(in_r2 + 0x164e8);
        uVar3 = HvpPhysicalToReal(param_2,0x14);
        j_XeCryptSha(((uVar2 & 0xffffffff) + 0x10) * 0x10 +
                     *(longlong *)((int)DWORD_ARRAY_00016260 + iVar1 + 0x280),0x10,0,0,0,0,uVar3,
                     0x14);
        FUN_000001e0(in_r2 + 0x164e8);
        uVar3 = 0;
      }
      else {
        uVar3 = 0xffffffffc8006005;
      }
    }
    else {
      uVar3 = 0xffffffffc8006006;
    }
  }
  else {
    uVar3 = 0xffffffffc8006003;
  }
  return uVar3;
}



ulonglong FUN_00031108(longlong param_1,uint param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = (ulonglong)(0x800080U >> param_1 | 0x1000100 << param_1);
  if (param_2 < 2) {
    if (param_2 == 1) {
      uVar1 = ~uVar1;
    }
    if ((param_3 & 2) == 0) {
      return uVar1;
    }
  }
  else {
    if (param_2 == 3) {
      uVar1 = ~uVar1;
    }
    if ((param_3 != 4) && (param_3 != 5)) {
      return uVar1;
    }
  }
  return ~uVar1;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_00031170(void)

{
  undefined8 in_r0;
  undefined8 uVar1;
  longlong lVar2;
  undefined4 uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  longlong lVar7;
  longlong lVar8;
  longlong lVar9;
  int iVar10;
  qword local_10;
  qword local_8;
  
  iVar10 = 2;
  uVar1 = 0x42b1800;
  do {
    lVar2 = HvpPhysicalToReal(uVar1,0x8000);
    uVar6 = 0;
    lVar7 = lVar2 + 0x80;
    do {
      uVar4 = 0;
      do {
        DataCaseBlockSetToZero(in_r0,lVar2);
        DataCaseBlockSetToZero(in_r0,lVar7);
        uVar5 = 0;
        do {
          lVar9 = lVar2;
          lVar8 = lVar7;
          uVar3 = FUN_00031108(uVar6);
          uVar5 = uVar5 + 1;
          *(undefined4 *)lVar9 = uVar3;
          *(undefined4 *)lVar8 = uVar3;
          lVar7 = lVar8 + 4;
          lVar2 = lVar9 + 4;
        } while ((uVar5 & 0xffffffff) < 8);
        dataCacheBlockFlush(lVar9 + 4);
        dataCacheBlockFlush(lVar8 + 4);
        uVar4 = uVar4 + 1;
        lVar2 = lVar9 + 0xe4;
        lVar7 = lVar8 + 0xe4;
      } while ((uVar4 & 0xffffffff) < 4);
      uVar6 = uVar6 + 1;
    } while ((uVar6 & 0xffffffff) < 8);
    iVar10 = iVar10 + -1;
    uVar1 = 0x142b1800;
  } while (iVar10 != 0);
  return;
}



void FUN_00031228(void)

{
  int iVar1;
  
  __Save_R12_29_thru_31();
  iVar1 = HvpBuildSocMMIORegs(0xe4000000);
  *(undefined4 *)(iVar1 + 0x28c) = 0x2000000;
  sync(0);
  FUN_000004a8(0x14);
  *(undefined4 *)(iVar1 + 0x28c) = 0;
  sync(0);
  FUN_000004a8(200);
  *(undefined4 *)(iVar1 + 0x288) = 0;
  sync(0);
  FUN_000004a8(0x14);
  *(undefined4 *)(iVar1 + 0x288) = 0x1000000;
  sync(0);
  FUN_000004a8(0x14);
  *(undefined4 *)(iVar1 + 0x288) = 0x5000000;
  sync(0);
  FUN_000004a8(0x14);
  *(undefined4 *)(iVar1 + 0x288) = 0x1000000;
  sync(0);
  FUN_000004a8(0x14);
  *(undefined4 *)(iVar1 + 0x288) = 0;
  sync(0);
  FUN_000004a8(0x14);
  return;
}



void FUN_000312e8(undefined8 param_1,int param_2,longlong param_3)

{
  longlong lVar1;
  uint uVar4;
  undefined8 uVar2;
  longlong lVar3;
  ulonglong uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  qword local_70;
  qword local_68;
  qword local_60;
  qword local_58;
  
  uVar4 = __Save_R12_24_thru_31();
  uVar2 = 0x42b1800;
  iVar10 = 2;
  do {
    lVar3 = HvpPhysicalToReal(uVar2,0x8000);
    uVar7 = 0;
    do {
      uVar5 = 0;
      do {
        FUN_00031108(uVar7,uVar5,0);
        uVar6 = 2;
        lVar1 = lVar3 + 8;
        do {
          lVar3 = lVar1;
          FUN_00031108(uVar7);
          uVar6 = uVar6 + 2;
          lVar1 = lVar3 + 8;
        } while ((uVar6 & 0xffffffff) < 8);
        dataCacheBlockFlush(lVar3 + 8);
        dataCacheBlockFlush(lVar3 + 0x88);
        uVar5 = uVar5 + 1;
        lVar3 = lVar3 + 0xe8;
      } while ((uVar5 & 0xffffffff) < 4);
      uVar7 = uVar7 + 1;
    } while ((uVar7 & 0xffffffff) < 8);
    iVar10 = iVar10 + -1;
    uVar2 = 0x142b1800;
  } while (iVar10 != 0);
  param_2 = param_2 - (int)param_3;
  iVar8 = 0;
  iVar10 = 0x10;
  do {
    piVar9 = (int *)param_3;
    if (*(char *)((int)&local_70 + iVar8) == '\0') {
      *(int *)(param_2 + (int)piVar9) = *(int *)(param_2 + (int)piVar9) + 1;
      *piVar9 = *piVar9 + (uVar4 & 0xff);
    }
    if (*(char *)((int)&local_60 + iVar8) == '\0') {
      *(int *)(param_2 + (int)piVar9) = *(int *)(param_2 + (int)piVar9) + 1;
      *piVar9 = *piVar9 + (uVar4 & 0xff) + -0x50;
    }
    iVar10 = iVar10 + -1;
    iVar8 = iVar8 + 1;
    param_3 = param_3 + 4;
  } while (iVar10 != 0);
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_00031478(void)

{
  int iVar1;
  undefined4 *puVar2;
  qword local_10;
  qword local_8;
  
  iVar1 = HvpBuildSocMMIORegs(0xe4000000);
  puVar2 = (undefined4 *)HvpBuildSocMMIORegs(0xe1020004);
  *(undefined4 *)(iVar1 + 0x2034) = 0;
  *(undefined4 *)(iVar1 + 0x2134) = 0;
  *(undefined4 *)(iVar1 + 0x202c) = 0x3c64;
  *(undefined4 *)(iVar1 + 0x212c) = 0x3c64;
  *(undefined4 *)(iVar1 + 0x202c) = 0x1280a;
  *(undefined4 *)(iVar1 + 0x212c) = 0x1280a;
  *(undefined4 *)(iVar1 + 0x202c) = 0x242f;
  *(undefined4 *)(iVar1 + 0x212c) = 0x242f;
  *(undefined4 *)(iVar1 + 0x202c) = 0x242f;
  *(undefined4 *)(iVar1 + 0x212c) = 0x242f;
  *(undefined4 *)(iVar1 + 0x202c) = 0x3c00;
  *(undefined4 *)(iVar1 + 0x212c) = 0x3c00;
  sync(0);
  instructionSynchronize();
  *(undefined4 *)(iVar1 + 0x2000) = 0x2000000;
  *(undefined4 *)(iVar1 + 0x2100) = 0x2000000;
  *(undefined4 *)(iVar1 + 0x2000) = 0x5160000;
  *(undefined4 *)(iVar1 + 0x2100) = 0x5160000;
  *(undefined4 *)(iVar1 + 0x2000) = 0x5060000;
  *(undefined4 *)(iVar1 + 0x2100) = 0x5060000;
  sync(0);
  *puVar2 = 0;
  sync(0);
  instructionSynchronize();
  FUN_000004a8(200);
  return;
}



// WARNING: Variable defined which should be unmapped: local_10

void FUN_00031560(void)

{
  int iVar1;
  undefined4 *puVar2;
  qword local_10;
  qword local_8;
  
  iVar1 = HvpBuildSocMMIORegs(0xe4000000);
  puVar2 = (undefined4 *)HvpBuildSocMMIORegs(0xe1020004);
  *puVar2 = 0x18000000;
  sync(0);
  instructionSynchronize();
  do {
  } while ((*(uint *)(iVar1 + 0x2140) | *(uint *)(iVar1 + 0x2040)) != 0x2000000);
  *(undefined4 *)(iVar1 + 0x2000) = 0;
  *(undefined4 *)(iVar1 + 0x2100) = 0;
  *(undefined4 *)(iVar1 + 0x2034) = 0;
  *(undefined4 *)(iVar1 + 0x2134) = 0;
  *(undefined4 *)(iVar1 + 0x202c) = 0x1280a;
  *(undefined4 *)(iVar1 + 0x212c) = 0x1280a;
  *(undefined4 *)(iVar1 + 0x202c) = 0x242f;
  *(undefined4 *)(iVar1 + 0x212c) = 0x242f;
  *(undefined4 *)(iVar1 + 0x202c) = 0x242f;
  *(undefined4 *)(iVar1 + 0x212c) = 0x242f;
  *(undefined4 *)(iVar1 + 0x202c) = 0x400;
  *(undefined4 *)(iVar1 + 0x212c) = 0x400;
  *(undefined4 *)(iVar1 + 0x2000) = 0x2000000;
  *(undefined4 *)(iVar1 + 0x2100) = 0x2000000;
  sync(0);
  FUN_000004a8(100);
  return;
}



void FUN_00031638(undefined8 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = __Save_R12_24_thru_31();
  iVar2 = HvpBuildSocMMIORegs(0xe4000000);
  FUN_00031560();
  *(uint *)(iVar2 + 0x284) = uVar1;
  *(uint *)(iVar2 + 0x284) = uVar1 | 0xc00;
  FUN_000004a8(5000);
  *(uint *)(iVar2 + 0x284) = uVar1 & 0xfffff3df;
  *(uint *)(iVar2 + 0x2004) = param_2 | 0x1000000;
  *(uint *)(iVar2 + 0x2104) = param_2 | 0x1000000;
  *(undefined4 *)(iVar2 + 0x200c) = 0x88809820;
  *(undefined4 *)(iVar2 + 0x210c) = 0x88809820;
  *(undefined4 *)(iVar2 + 0x201c) = 0x7bd82801;
  *(undefined4 *)(iVar2 + 0x211c) = 0x7bd82801;
  *(undefined4 *)(iVar2 + 0x2020) = 0xdb0e8203;
  *(undefined4 *)(iVar2 + 0x2120) = 0xdb0e8203;
  *(undefined4 *)(iVar2 + 0x2024) = 0x4b91970c;
  *(undefined4 *)(iVar2 + 0x2124) = 0x4b91970c;
  *(undefined4 *)(iVar2 + 0x10) = 0x12072006;
  *(undefined4 *)(iVar2 + 0x14) = 0xd802006;
  *(undefined4 *)(iVar2 + 0x2034) = 0;
  *(undefined4 *)(iVar2 + 0x2134) = 0;
  *(undefined4 *)(iVar2 + 0x202c) = 0x1280c;
  *(undefined4 *)(iVar2 + 0x212c) = 0x1280c;
  *(undefined4 *)(iVar2 + 0x202c) = 0x242f;
  *(undefined4 *)(iVar2 + 0x212c) = 0x242f;
  *(undefined4 *)(iVar2 + 0x202c) = 0xd802006;
  *(undefined4 *)(iVar2 + 0x212c) = 0xd802006;
  *(undefined4 *)(iVar2 + 0x202c) = 0x12072006;
  *(undefined4 *)(iVar2 + 0x212c) = 0x12072006;
  *(undefined4 *)(iVar2 + 0x2000) = 0x2000000;
  *(undefined4 *)(iVar2 + 0x2100) = 0x2000000;
  sync(0);
  FUN_000004a8(2000);
  FUN_00031228();
  FUN_00031478();
  return;
}



void FUN_00031778(undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = __Save_R12_27_thru_31();
  iVar2 = HvpBuildSocMMIORegs(0xe4000000);
  FUN_00031560();
  *(undefined4 *)(iVar2 + 0x2080) = uVar1;
  *(undefined4 *)(iVar2 + 0x2084) = param_2;
  *(undefined4 *)(iVar2 + 0x2180) = param_3;
  *(undefined4 *)(iVar2 + 0x2184) = param_4;
  sync(0);
  FUN_000004a8(100);
  FUN_00031228();
  FUN_00031478();
  return;
}



void FUN_000317d8(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = __Save_R12_26_thru_31();
  iVar4 = HvpBuildSocMMIORegs(0xe4000000);
  do {
    *(int *)(iVar4 + 0x2028) = uVar3 + 0x6000000;
    *(int *)(iVar4 + 0x2128) = uVar3 + 0x6000000;
    sync(0);
    FUN_000004a8(2000);
    *(uint *)(iVar4 + 0x2028) = uVar3;
    *(uint *)(iVar4 + 0x2128) = uVar3;
    sync(0);
    FUN_000004a8(2000);
    *(undefined4 *)(iVar4 + 0x2028) = 0x20000;
    FUN_000004a8(100);
    uVar1 = *(uint *)(iVar4 + 0x20a8);
    *(undefined4 *)(iVar4 + 0x2028) = 0;
    FUN_000004a8(100);
    uVar2 = *(uint *)(iVar4 + 0x20a8);
    *(undefined4 *)(iVar4 + 0x2028) = 0x10000;
    FUN_000004a8(100);
  } while ((uVar3 & 0xf3ff00) !=
           (((uVar1 & 0xf000000 | ~uVar2 >> 4 & 0xf00000 | *(uint *)(iVar4 + 0x20a8) & 0x10000000)
             >> 1 | uVar2 & 0x10000000) >> 7 | *(uint *)(iVar4 + 0x20a8) & 0xf000000) >> 4);
  return;
}



void FUN_000318a8(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  char *pcVar8;
  longlong in_r2;
  int iVar12;
  longlong lVar9;
  ulonglong uVar10;
  undefined8 uVar11;
  uint uVar13;
  char *pcVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  undefined8 *puVar18;
  int iVar19;
  uint uVar20;
  longlong lVar21;
  int iVar22;
  longlong lVar23;
  ulonglong uVar24;
  longlong lVar25;
  undefined8 in_spr131;
  dword local_600;
  dword local_5fc;
  dword local_5f8;
  dword local_5f4;
  word local_5c0;
  word local_580;
  word local_540;
  undefined4 local_53c [15];
  word local_500;
  word local_4c0;
  dword local_4b8;
  word local_440;
  word local_43e;
  dword local_60;
  
  __Save_R12_22_thru_31();
  uVar20 = 0;
  lVar21 = 0;
  uVar2 = *(uint *)((int)in_r2 + 0x10000);
  iVar12 = HvpBuildSocMMIORegs(0xe4000000);
  if (*(int *)(iVar12 + 0x209c) == 0xa0a0a0a) {
    lVar9 = HvpGetFlashBaseAddress();
    FUN_00000484(&local_4c0,lVar9,0x10);
    uVar10 = FUN_00003890((ulonglong)local_4b8,0x10);
    if ((uVar10 & 0xffffffff) != 0) {
      FUN_00000484(&local_440,(ulonglong)local_4b8 + lVar9,2);
      uVar15 = (uint)local_43e;
      if ((local_43e < 0x780) || (0x793 < local_43e)) {
        if ((0x793 < local_43e) && (local_43e < 0x79d)) {
          uVar15 = 0x760;
        }
      }
      else {
        uVar15 = 0x76f;
      }
      if ((uVar15 < 0x771) && (0x75f < uVar15)) {
        uVar11 = HvpPhysicalToReal(0x42b1800,0x2000);
        FUN_000084a8(uVar11,0x2000);
        FUN_000084a8(0,0x200);
        FUN_000084a8(&BYTE_00010000,0x200);
        FUN_000084a8(FUN_00020000,0x200);
        FUN_000084a8(FUN_00030000,0x200);
        FUN_000084a8(in_spr131,0x40);
        if (uVar15 < 0x76f) {
          FUN_00031638(0x19100020,0x2321204);
          lVar23 = 0;
          uVar10 = 0;
          lVar9 = in_r2 + 0x11a98;
          do {
            puVar18 = (undefined8 *)&local_5c0;
            lVar25 = 8;
            do {
              *puVar18 = 0;
              puVar18 = puVar18 + 1;
              lVar25 = lVar25 + -1;
            } while (lVar25 != 0);
            puVar18 = (undefined8 *)&local_580;
            lVar25 = 8;
            do {
              *puVar18 = 0;
              puVar18 = puVar18 + 1;
              lVar25 = lVar25 + -1;
            } while (lVar25 != 0);
            FUN_000317d8((ulonglong)*(uint *)lVar9);
            uVar24 = 0;
            do {
              FUN_00031778(uVar24,uVar24,uVar24,uVar24);
              FUN_00031170();
              FUN_000312e8(uVar24,&local_5c0,&local_580);
              uVar24 = uVar24 + 0x1010101;
            } while ((uVar24 & 0xffffffff) < 0x50505050);
            uVar13 = 0xff;
            iVar22 = 0;
            iVar19 = 0;
            iVar16 = 0x10;
            iVar17 = (int)((uVar10 & 0xffffffff) << 2);
            do {
              uVar3 = *(uint *)(iVar19 + (int)&local_5c0);
              if (uVar3 < uVar13) {
                uVar13 = uVar3 & 0xff;
              }
              if (uVar3 == 0) {
                *(undefined4 *)(iVar19 + (int)&local_5c0) = 1;
              }
              uVar3 = *(uint *)(iVar19 + (int)&local_5c0);
              cVar1 = *(char *)(iVar22 + (int)in_r2 + 0x11a88);
              trapWord(6,(ulonglong)uVar3,0);
              iVar16 = iVar16 + -1;
              uVar7 = *(uint *)((int)&local_580 + iVar19);
              *(undefined *)((int)&local_540 + iVar22 + iVar17) = (char)uVar3;
              uVar24 = (ulonglong)uVar7 / (ulonglong)uVar3;
              *(undefined4 *)((int)&local_500 + iVar19) = (int)uVar24;
              iVar19 = iVar19 + 4;
              *(char *)((int)&local_600 + iVar22 + iVar17) = cVar1 + (char)uVar24;
              iVar22 = iVar22 + 1;
            } while (iVar16 != 0);
            if (uVar20 < uVar13) {
              lVar21 = lVar23;
              uVar20 = uVar13;
            }
            uVar10 = uVar10 + 4;
            lVar23 = lVar23 + 1;
            lVar9 = lVar9 + 4;
          } while ((uVar10 & 0xffffffff) < 0x10);
          iVar16 = (int)(lVar21 << 2);
          iVar17 = (int)(in_r2 + 0x11a98);
          FUN_000317d8((ulonglong)*(uint *)(iVar16 + iVar17));
          iVar22 = (int)lVar21;
          uVar4 = local_53c[iVar22 * 4];
          uVar5 = local_53c[iVar22 * 4 + 1];
          uVar6 = local_53c[iVar22 * 4 + 2];
          *(undefined4 *)(iVar12 + 0x1610) = *(undefined4 *)(&local_540 + iVar22 * 8);
          *(undefined4 *)(iVar12 + 0x1614) = uVar4;
          *(undefined4 *)(iVar12 + 0x1618) = uVar5;
          *(undefined4 *)(iVar12 + 0x161c) = uVar6;
          FUN_00031778((ulonglong)(&local_600)[iVar22 * 4],(ulonglong)(&local_5fc)[iVar22 * 4],
                       (ulonglong)(&local_5f8)[iVar22 * 4],(ulonglong)(&local_5f4)[iVar22 * 4]);
          *(int *)(iVar12 + 0x18) = uVar15 * 0x10000 + 0xadde;
          *(undefined4 *)(iVar12 + 0x20) = *(undefined4 *)(iVar16 + iVar17);
          goto LAB_00031c54;
        }
        uVar20 = *(uint *)(iVar12 + 0x2080);
        iVar16 = 0;
        iVar17 = 0x10;
        uVar15 = *(uint *)(iVar12 + 0x2084);
        uVar13 = *(uint *)(iVar12 + 0x2180);
        uVar3 = *(uint *)(iVar12 + 0x2184);
        do {
          pcVar8 = (char *)(iVar16 + (int)in_r2 + 0x11a78);
          iVar17 = iVar17 + -1;
          pcVar14 = (char *)((int)&local_600 + iVar16);
          iVar16 = iVar16 + 1;
          *pcVar14 = *pcVar8 + *pcVar14;
        } while (iVar17 != 0);
        FUN_00031778((ulonglong)uVar20,(ulonglong)uVar15,(ulonglong)uVar13,(ulonglong)uVar3);
        iVar17 = 0x319adde;
      }
      else {
        iVar17 = uVar15 * 0x10000 + 0xadde;
      }
      *(int *)(iVar12 + 0x18) = iVar17;
    }
  }
LAB_00031c54:
  HvpReleaseSpinLock((ulonglong)uVar2);
  return;
}



void j__v_MACHINE_CHECK_0(void)

{
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



undefined8 FUN_00031c70(undefined8 param_1,ulonglong param_2)

{
  byte bVar1;
  ulonglong uVar2;
  longlong in_r2;
  ulonglong uVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  longlong *plVar7;
  longlong lVar6;
  longlong *plVar8;
  ulonglong *puVar9;
  int iVar10;
  longlong lVar11;
  undefined8 *puVar12;
  int iVar15;
  ulonglong uVar13;
  ulonglong uVar14;
  undefined8 *puVar16;
  undefined8 uVar17;
  uint uVar18;
  dword local_158;
  dword local_154;
  word local_150;
  
  uVar3 = __Save_R12_24_thru_31();
  uVar17 = 0;
  HvpAquireSpinLock(in_r2 + 0x16140);
  if ((uVar3 & 0xffffffff) == 0) {
    uVar4 = 2;
  }
  else {
    if ((uVar3 & 0xffffffff) != 1) goto LAB_00031e68;
    uVar4 = 3;
  }
  uVar5 = FUN_0000b0f8(uVar4);
  if ((((uVar5 & 0xffffffff) != 0) && ((param_2 & 0xfff) == 0)) &&
     (((uint)param_2 & 0xfff00000) < 0x20000000)) {
    puVar12 = (undefined8 *)FUN_000005d8(uVar3);
    plVar7 = (longlong *)FUN_000005ec(uVar3);
    if (*plVar7 == 0) {
      lVar6 = HvpPhysicalToReal(param_2,0x1000);
      uVar17 = countLeadingZeros((int)uVar3);
      plVar8 = (longlong *)FUN_000005ec((ulonglong)((uint)uVar17 >> 5 & 1));
      uVar18 = 0;
      if (*plVar8 != 0) {
        uVar18 = *(uint *)((int)plVar8 + 0xc);
      }
      do {
        do {
          FUN_0000b488(&local_154,4);
        } while (local_154 == 0);
      } while (((ulonglong)local_154 == (ulonglong)uVar18) || (local_154 == 0xffffffff));
      uVar18 = 0;
      iVar10 = 0;
      uVar5 = 0;
      uVar3 = 0;
      puVar9 = (ulonglong *)&local_150;
      lVar11 = lVar6 + 0x840;
      do {
        bVar1 = *(byte *)lVar11;
        if (((bVar1 & 2) == 0) || (iVar15 = 1, (bVar1 & 1) == 0)) {
          iVar15 = 0;
        }
        uVar2 = uVar5 & 0xffffffff;
        uVar13 = (ulonglong)(uint)(iVar15 << 4) |
                 ((uVar3 & 0xf | (ulonglong)local_154 << 4) << 5 | (ulonglong)((uint)bVar1 & 6)) <<
                 7;
        iVar15 = iVar10 + 0x10;
        uVar14 = uVar13 | 0x400;
        *puVar9 = uVar13;
        uVar5 = uVar5 + 2;
        iVar10 = iVar10 + 1;
        uVar3 = uVar3 + 1;
        *(ulonglong *)(&local_150 + iVar15 * 4) = uVar14;
        lVar11 = lVar11 + 1;
        puVar9 = puVar9 + 1;
        uVar18 = (((uint)(uVar14 >> 8) & 1) << 1 | (uint)(uVar14 >> 4) & 1) << uVar2 | uVar18;
      } while ((uVar5 & 0xffffffff) < 0x20);
      puVar16 = (undefined8 *)&local_150;
      lVar11 = 0x20;
      do {
        uVar17 = *puVar16;
        puVar16 = puVar16 + 1;
        *puVar12 = uVar17;
        puVar12 = puVar12 + 1;
        lVar11 = lVar11 + -1;
      } while (lVar11 != 0);
      uVar17 = 1;
      *(uint *)(plVar7 + 1) = uVar18;
      *plVar7 = lVar6;
      *(dword *)((int)plVar7 + 0xc) = local_154;
    }
  }
LAB_00031e68:
  FUN_000001e0(in_r2 + 0x16140);
  return uVar17;
}



undefined8 FUN_00031e80(void)

{
  longlong in_r2;
  ulonglong uVar1;
  longlong *plVar2;
  ulonglong *puVar3;
  int iVar4;
  longlong lVar5;
  uint uVar6;
  
  uVar1 = __Save_R12_29_thru_31();
  HvpAquireSpinLock(in_r2 + 0x16140);
  if ((uVar1 & 0xffffffff) < 2) {
    puVar3 = (ulonglong *)FUN_000005d8(uVar1);
    plVar2 = (longlong *)FUN_000005ec(uVar1);
    if (*plVar2 != 0) {
      lVar5 = 0;
      iVar4 = 0x20;
      *plVar2 = 0;
      *(undefined4 *)((int)plVar2 + 0xc) = 0;
      *(undefined4 *)(plVar2 + 1) = 0;
      do {
        uVar6 = (uint)lVar5;
        iVar4 = iVar4 + -1;
        lVar5 = lVar5 + 1;
        *puVar3 = (ulonglong)((uVar6 & 0xf) << 0xc) | 0xffffffff0200;
        puVar3 = puVar3 + 1;
      } while (iVar4 != 0);
    }
  }
  FUN_000001e0(in_r2 + 0x16140);
  return 0;
}



undefined8 FUN_00031f28(void)

{
  undefined4 uVar1;
  uint uVar2;
  longlong in_r2;
  ulonglong uVar3;
  longlong *plVar4;
  longlong lVar5;
  int iVar6;
  
  uVar3 = __Save_R12_27_thru_31();
  HvpAquireSpinLock(in_r2 + 0x16140);
  if ((uVar3 & 0xffffffff) < 2) {
    plVar4 = (longlong *)FUN_000005ec(uVar3);
    lVar5 = *plVar4;
    uVar1 = *(undefined4 *)((int)plVar4 + 0xc);
    uVar2 = *(uint *)(plVar4 + 1);
    if (lVar5 != 0) {
      iVar6 = *(int *)((int)lVar5 + 0x880);
      lVar5 = lVar5 + 0x884;
      if (iVar6 - 1U < 0x19f) {
        do {
          HvpFlushSingleTb(CONCAT44(uVar1,*(undefined4 *)lVar5),(ulonglong)uVar2);
          iVar6 = iVar6 + -1;
          lVar5 = lVar5 + 4;
        } while (iVar6 != 0);
      }
    }
  }
  FUN_000001e0(in_r2 + 0x16140);
  return 0;
}



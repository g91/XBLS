typedef unsigned char   undefined;

typedef unsigned int    dword;
typedef unsigned long long    qword;



// WARNING: Variable defined which should be unmapped: local_40
// WARNING: Variable defined which should be unmapped: local_38
// WARNING: Variable defined which should be unmapped: local_30
// WARNING: Variable defined which should be unmapped: local_28
// WARNING: Variable defined which should be unmapped: local_20
// WARNING: Variable defined which should be unmapped: local_18
// WARNING: Variable defined which should be unmapped: local_10

undefined8 FUN_00000120(longlong param_1,undefined8 param_2)

{
  int iVar1;
  undefined8 in_r2;
  undefined8 uVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  ulonglong uVar5;
  longlong lVar6;
  ulonglong uVar7;
  longlong lVar8;
  ulonglong uVar9;
  undefined8 in_spr139;
  qword back_chain;
  qword local_40;
  qword local_38;
  qword local_30;
  qword local_28;
  qword local_20;
  qword local_18;
  qword local_10;
  qword local_8;
  
  iVar1 = (int)param_1;
  *(undefined8 *)(iVar1 + 0x28) = 0x4d4d449700000000;
  *(undefined8 *)(iVar1 + 0x30) = 0x166f8f85d2404d70;
  *(dword *)(iVar1 + 0x38) = 0x8bf58222;
  *(dword *)(iVar1 + 0x3c) = 0xc8b25345;
  *(undefined8 *)(iVar1 + 0x40) = in_r2;
  *(undefined8 *)(iVar1 + 0x48) = in_spr139;
  puVar4 = (undefined8 *)(**(code **)((int)in_r2 + -0xe6e9a8c))(param_2,0x1000);
  uVar2 = FUN_00000328();
  uVar2 = FUN_00000330(uVar2,puVar4,0x10);
  lVar6 = 7;
  lVar8 = param_1 + 0x3a8;
  do {
    lVar8 = lVar8 + 8;
    uVar2 = FUN_00000330(uVar2,*(ulonglong *)lVar8 >> 0x10,*(ulonglong *)lVar8 & 0xffff);
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  FUN_00000338(uVar2,param_1 + 0xec);
  uVar2 = FUN_00000328();
  lVar6 = 8;
  uVar7 = param_1 + 0x400;
  *(undefined2 *)(iVar1 + 0xf8) = (short)(uVar7 >> 0x10);
  lVar8 = param_1 + 0x3f8;
  do {
    *(undefined8 *)((int)lVar8 + 8) = *puVar4;
    lVar8 = lVar8 + 0x10;
    *(undefined8 *)lVar8 = puVar4[1];
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  dataCacheBlockStore(uVar7);
  sync(0);
  FUN_00000330(uVar2,(uVar7 >> 6 & 0x3ff | 0xf800) + 0x8000020000010000,2);
  lVar6 = 0xd;
  lVar8 = param_1 + 0x340;
  do {
    lVar8 = lVar8 + 8;
    uVar7 = *(ulonglong *)lVar8;
    if ((uVar7 & 0x8000) == 0) {
      uVar9 = 1;
      uVar3 = uVar7 >> 0x10;
      uVar7 = uVar7 & 0x7f;
      uVar5 = uVar3;
      if (0xf < uVar7) {
        uVar5 = uVar3 & 0x3ffff | 0x8000000000000000;
      }
    }
    else {
      uVar9 = uVar7 & 0x3ff;
      uVar3 = uVar7 >> 0x10;
      uVar5 = (uVar7 >> 0x16 & 0xfff) + 0x8000020000010000;
      uVar7 = uVar9 << 1;
    }
    do {
      *(undefined *)uVar3 = *(undefined *)uVar3;
      dataCacheBlockStore(uVar3);
      uVar3 = uVar3 + 0x80;
      uVar9 = uVar9 - 1;
    } while (uVar9 != 0);
    sync(0);
    uVar2 = FUN_00000330(uVar3,uVar5,uVar7);
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  FUN_00000338(uVar2,param_1 + 0x50);
  uVar2 = FUN_00000328();
  uVar2 = FUN_00000330(uVar2,0x20,0x10);
  FUN_00000338(uVar2,param_1 + 100);
  lVar8 = 0x10;
  param_1 = param_1 + 0x70;
  puVar4 = (undefined8 *)0x10038;
  do {
    puVar4 = puVar4 + 1;
    param_1 = param_1 + 8;
    *(undefined8 *)param_1 = *puVar4;
    lVar8 = lVar8 + -1;
  } while (lVar8 != 0);
  return 0;
}



void FUN_00000328(void)

{
  code *UNRECOVERED_JUMPTABLE;
  
                    // WARNING: Could not recover jumptable at 0x00000344. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(&stack0x00000050);
  return;
}



void FUN_00000330(void)

{
  code *UNRECOVERED_JUMPTABLE;
  
                    // WARNING: Could not recover jumptable at 0x00000344. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(&stack0x00000050);
  return;
}



void FUN_00000338(undefined8 param_1,undefined8 param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  
                    // WARNING: Could not recover jumptable at 0x00000344. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(&stack0x00000050,param_2,0x14);
  return;
}



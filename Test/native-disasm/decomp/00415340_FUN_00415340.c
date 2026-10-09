// FUN_00415340 @ 00415340 size=425 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_00415340(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  bool bVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047aedc;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  if (DAT_004a2b10 != (int *)0x0) {
    ExceptionList = &local_10;
    (**(code **)(*DAT_004a2b10 + 8))(DAT_004a2b10);
  }
  DAT_004a2b10 = (int *)*param_1;
  puVar1 = param_1 + 1;
  *param_1 = 0;
  if ((int **)puVar1 != &DAT_004a2b14) {
    piVar2 = (int *)*puVar1;
    *puVar1 = 0;
    piVar3 = DAT_004a2b14;
    bVar4 = DAT_004a2b14 != (int *)0x0;
    DAT_004a2b14 = piVar2;
    if (bVar4) {
      FUN_004151a0(piVar3);
      FUN_0045a6a4(piVar3);
    }
  }
  puVar1 = param_1 + 2;
  if ((int **)puVar1 != &DAT_004a2b18) {
    piVar2 = (int *)*puVar1;
    *puVar1 = 0;
    piVar3 = DAT_004a2b18;
    bVar4 = DAT_004a2b18 != (int *)0x0;
    DAT_004a2b18 = piVar2;
    if (bVar4) {
      FUN_004151a0(piVar3);
      FUN_0045a6a4(piVar3);
    }
  }
  puVar1 = param_1 + 3;
  if ((int **)puVar1 != &DAT_004a2b1c) {
    piVar2 = (int *)*puVar1;
    *puVar1 = 0;
    piVar3 = DAT_004a2b1c;
    bVar4 = DAT_004a2b1c != (int *)0x0;
    DAT_004a2b1c = piVar2;
    if (bVar4) {
      FUN_004151a0(piVar3);
      FUN_0045a6a4(piVar3);
    }
  }
  puVar1 = param_1 + 4;
  if ((int **)puVar1 != &DAT_004a2b20) {
    piVar2 = (int *)*puVar1;
    *puVar1 = 0;
    piVar3 = DAT_004a2b20;
    bVar4 = DAT_004a2b20 != (int *)0x0;
    DAT_004a2b20 = piVar2;
    if (bVar4) {
      FUN_004151a0(piVar3);
      FUN_0045a6a4(piVar3);
    }
  }
  if ((void **)(param_1 + 5) != &DAT_004a2b24) {
    if (7 < DAT_004a2b38) {
      FUN_00402430(DAT_004a2b24,DAT_004a2b38 + 1,2);
    }
    DAT_004a2b38 = 7;
    _DAT_004a2b34 = 0;
    DAT_004a2b24 = (void *)((uint)DAT_004a2b24 & 0xffff0000);
    FUN_0043a920(&DAT_004a2b24,param_1 + 5);
  }
  _DAT_004a2b3c = param_1[0xb];
  _DAT_004a2b40 = param_1[0xc];
  _DAT_004a2b44 = param_1[0xd];
  uRam004a2b48 = param_1[0xe];
  uRam004a2b4c = param_1[0xf];
  uRam004a2b50 = param_1[0x10];
  _DAT_004a2b54 = param_1[0x11];
  _DAT_004a2b58 = param_1[0x12];
  _DAT_004a2b5c = param_1[0x13];
  ExceptionList = local_10;
  return &DAT_004a2b10;
}



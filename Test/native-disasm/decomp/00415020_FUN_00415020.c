// FUN_00415020 @ 00415020 size=171 callers=2

undefined4 __fastcall FUN_00415020(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ae2e;
  local_10 = ExceptionList;
  puVar1 = param_1 + 3;
  if (param_1[3] == 0) {
    ExceptionList = &local_10;
    puVar4 = FUN_0040b880(&local_18,param_1,0);
    local_8 = 0;
    puVar4 = FUN_00441b70(&local_14,puVar4);
    if (puVar1 != puVar4) {
      uVar2 = *puVar4;
      *puVar4 = 0;
      piVar3 = (int *)*puVar1;
      *puVar1 = uVar2;
      if (piVar3 != (int *)0x0) {
        FUN_004151a0(piVar3);
        FUN_0045a6a4(piVar3);
      }
    }
    if (local_14 != (int *)0x0) {
      FUN_004151a0(local_14);
      FUN_0045a6a4(local_14);
    }
    local_8 = 1;
    if (local_18 != (int *)0x0) {
      (**(code **)(*local_18 + 8))(local_18);
    }
  }
  ExceptionList = local_10;
  return *puVar1;
}



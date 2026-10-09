// FUN_00414ec0 @ 00414ec0 size=166 callers=6

int __fastcall FUN_00414ec0(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ae2e;
  local_10 = ExceptionList;
  piVar1 = param_1 + 1;
  if (param_1[1] == 0) {
    ExceptionList = &local_10;
    puVar3 = FUN_0040b9e0(&local_18,param_1);
    local_8 = 0;
    piVar4 = FUN_00441b70(&local_14,puVar3);
    if (piVar1 != piVar4) {
      iVar2 = *piVar4;
      *piVar4 = 0;
      piVar4 = (int *)*piVar1;
      *piVar1 = iVar2;
      if (piVar4 != (int *)0x0) {
        FUN_004151a0(piVar4);
        FUN_0045a6a4(piVar4);
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
  return *piVar1;
}



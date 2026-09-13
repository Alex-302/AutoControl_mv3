// FUN_00441810 @ 00441810 size=167 callers=1

undefined4 * __fastcall FUN_00441810(undefined4 *param_1,int param_2,int *param_3)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0047e080;
  local_10 = ExceptionList;
  local_8 = 0;
  piVar2 = (int *)(param_2 + 4);
  iVar3 = 2;
  ExceptionList = &local_10;
  do {
    if (*piVar2 != 0) {
      puVar1 = FUN_0040bb70(&local_14,&param_3,piVar2[-1],*piVar2,0x32);
      local_8._0_1_ = 1;
      if (param_3 != (int *)0x0) {
        (**(code **)(*param_3 + 8))(param_3);
      }
      param_3 = (int *)*puVar1;
      *puVar1 = 0;
      local_8._0_1_ = 2;
      if (local_14 != (int *)0x0) {
        (**(code **)(*local_14 + 8))(local_14);
      }
      local_8 = (uint)local_8._1_3_ << 8;
    }
    piVar2 = piVar2 + 2;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *param_1 = param_3;
  ExceptionList = local_10;
  return param_1;
}



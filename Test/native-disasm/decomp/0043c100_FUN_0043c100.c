// FUN_0043c100 @ 0043c100 size=144 callers=1

void __fastcall FUN_0043c100(int *param_1)

{
  ios_base *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  piVar1 = (ios_base *)(param_1 + 8);
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined ***)(piVar1 + *(int *)(*param_1 + 4) + -0x20) = &PTR_LAB_0048e968;
  *(int *)(piVar1 + *(int *)(*param_1 + 4) + -0x24) = *(int *)(*param_1 + 4) + -0x20;
  *(undefined ***)(piVar1 + *(int *)(param_1[4] + 4) + -0x10) = &PTR_LAB_0048f09c;
  *(int *)(piVar1 + *(int *)(param_1[4] + 4) + -0x14) = *(int *)(param_1[4] + 4) + -8;
  *(undefined ***)(piVar1 + *(int *)(*param_1 + 4) + -0x20) = &PTR_LAB_0048ec6c;
  *(int *)(piVar1 + *(int *)(*param_1 + 4) + -0x24) = *(int *)(*param_1 + 4) + -0x18;
  local_8 = 0;
  *(undefined ***)piVar1 = &PTR_FUN_0048e580;
  std::ios_base::_Ios_base_dtor(piVar1);
  ExceptionList = local_10;
  return;
}



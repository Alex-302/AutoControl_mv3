// FUN_00435840 @ 00435840 size=72 callers=1

void __fastcall FUN_00435840(int param_1)

{
  ios_base *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  piVar1 = (ios_base *)(param_1 + 0x68);
  ExceptionList = &local_10;
  FUN_0043b250((int)piVar1);
  local_8 = 0;
  *(undefined ***)piVar1 = &PTR_FUN_0048e580;
  std::ios_base::_Ios_base_dtor(piVar1);
  ExceptionList = local_10;
  return;
}



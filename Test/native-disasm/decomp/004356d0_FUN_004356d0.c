// FUN_004356d0 @ 004356d0 size=60 callers=1

void __fastcall FUN_004356d0(ios_base *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = &PTR_FUN_0048e580;
  std::ios_base::_Ios_base_dtor(param_1);
  ExceptionList = local_10;
  return;
}



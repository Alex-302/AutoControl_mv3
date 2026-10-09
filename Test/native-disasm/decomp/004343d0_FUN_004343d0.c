// FUN_004343d0 @ 004343d0 size=67 callers=5

void __thiscall FUN_004343d0(void *this,byte *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047dab0;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_00439c60(this,param_1);
  ExceptionList = local_10;
  return;
}



// FUN_00449820 @ 00449820 size=96 callers=1

int * __thiscall FUN_00449820(void *this,int *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e5e9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_8 = 0;
  FUN_00455a90(this,param_1);
  ExceptionList = local_10;
  return param_1;
}



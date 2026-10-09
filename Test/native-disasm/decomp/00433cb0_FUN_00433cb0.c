// FUN_00433cb0 @ 00433cb0 size=102 callers=1

uint * __fastcall FUN_00433cb0(uint *param_1,undefined1 *param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047d9e9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_8 = 0;
  FUN_00439500(param_2,param_1);
  ExceptionList = local_10;
  return param_1;
}



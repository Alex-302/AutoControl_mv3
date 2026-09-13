// FUN_0042a610 @ 0042a610 size=83 callers=1

undefined1 * __cdecl FUN_0042a610(undefined1 *param_1,void *param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00405e70(param_2);
  local_8 = 0;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}



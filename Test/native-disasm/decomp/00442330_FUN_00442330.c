// FUN_00442330 @ 00442330 size=91 callers=1

undefined4 * __fastcall FUN_00442330(undefined4 *param_1,void *param_2)

{
  void *this;
  int *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e12f;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this = operator_new(0x38);
  local_8 = 0;
  piVar1 = FUN_00421960(this,param_2);
  *param_1 = piVar1;
  ExceptionList = local_10;
  return param_1;
}



// FUN_00441fa0 @ 00441fa0 size=91 callers=1

undefined4 * __fastcall FUN_00441fa0(undefined4 *param_1,void *param_2)

{
  void *pvVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e0bf;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pvVar1 = operator_new(0x44);
  local_8 = 0;
  pvVar1 = FUN_0041bb40(pvVar1,param_2);
  *param_1 = pvVar1;
  ExceptionList = local_10;
  return param_1;
}



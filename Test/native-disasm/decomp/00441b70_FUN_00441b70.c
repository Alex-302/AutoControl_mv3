// FUN_00441b70 @ 00441b70 size=91 callers=4

undefined4 * __fastcall FUN_00441b70(undefined4 *param_1,undefined4 *param_2)

{
  void *pvVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e09f;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pvVar1 = operator_new(0x50);
  local_8 = 0;
  pvVar1 = FUN_00414c40(pvVar1,param_2);
  *param_1 = pvVar1;
  ExceptionList = local_10;
  return param_1;
}



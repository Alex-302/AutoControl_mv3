// FUN_0040b880 @ 0040b880 size=163 callers=3

undefined4 * __fastcall FUN_0040b880(undefined4 *param_1,undefined4 *param_2,LONG param_3)

{
  HRESULT HVar1;
  _union_2683 local_40;
  LONG local_2c;
  undefined4 *local_28;
  undefined4 local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  puStack_18 = &LAB_00479e29;
  local_1c = ExceptionList;
  local_40._0_4_ = 0;
  local_40.decVal.Hi32 = 0;
  local_40._8_4_ = (undefined4 *)0x0;
  local_40._12_4_ = 0;
  ExceptionList = &local_1c;
  *param_1 = 0;
  local_14 = 0;
  local_24 = 1;
  local_28 = param_1;
  HVar1 = AccessibleChildren((IAccessible *)*param_2,param_3,1,(VARIANT *)&local_40.n2,&local_2c);
  if ((HVar1 == 0) && (local_40.n2.vt == 9)) {
    (*(code *)**(undefined4 **)local_40._8_4_)(local_40._8_4_,&DAT_0048ec70,param_1);
  }
  VariantClear((VARIANTARG *)&local_40.n2);
  ExceptionList = local_1c;
  return param_1;
}



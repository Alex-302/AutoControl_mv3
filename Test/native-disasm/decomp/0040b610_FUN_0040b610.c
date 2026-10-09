// FUN_0040b610 @ 0040b610 size=61 callers=4

IAccessible ** __fastcall FUN_0040b610(IAccessible **param_1,POINT *param_2)

{
  _union_2683 local_20;
  
  *param_1 = (IAccessible *)0x0;
  local_20._0_4_ = 0;
  local_20.decVal.Hi32 = 0;
  local_20._8_4_ = 0;
  local_20._12_4_ = 0;
  AccessibleObjectFromPoint(*param_2,param_1,(VARIANT *)&local_20.n2);
  VariantClear((VARIANTARG *)&local_20.n2);
  return param_1;
}



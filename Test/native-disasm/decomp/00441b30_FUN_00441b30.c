// FUN_00441b30 @ 00441b30 size=57 callers=1

undefined4 * __fastcall FUN_00441b30(undefined4 *param_1)

{
  void *pvVar1;
  
  pvVar1 = (void *)GdipAlloc(8);
  if (pvVar1 != (void *)0x0) {
    pvVar1 = FUN_0040a650(pvVar1,L"Marlett");
    *param_1 = pvVar1;
    return param_1;
  }
  *param_1 = 0;
  return param_1;
}



// FUN_0045884d @ 0045884d size=40 callers=12

void __fastcall FUN_0045884d(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    if (iVar1 < 8) {
      FUN_00459572((LPCRITICAL_SECTION)(&DAT_0049ee68 + iVar1 * 0x18));
    }
    return;
  }
  ___acrt_unlock(4);
  return;
}



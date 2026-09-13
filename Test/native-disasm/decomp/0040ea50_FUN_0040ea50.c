// FUN_0040ea50 @ 0040ea50 size=188 callers=2

bool __fastcall FUN_0040ea50(HWND param_1,char param_2)

{
  ATOM AVar1;
  HANDLE pvVar2;
  
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a3310) {
    FUN_0045a219(&DAT_004a3310);
    if (DAT_004a3310 == -1) {
      AVar1 = GlobalAddAtomA("ACNH_isPopup");
      DAT_004a33cc = (LPCSTR)(uint)AVar1;
      FUN_0045a1da(&DAT_004a3310);
    }
  }
  if (param_2 == -1) {
    if (param_1 == DAT_004a2a50) {
      return false;
    }
    pvVar2 = GetPropA(param_1,DAT_004a33cc);
    if (pvVar2 == (HANDLE)0x0) {
      DAT_004a2a50 = param_1;
    }
    return pvVar2 != (HANDLE)0x0;
  }
  if (param_2 != '\0') {
    SetPropA(param_1,DAT_004a33cc,(HANDLE)0x1);
    return param_2 != '\0';
  }
  DAT_004a2a50 = param_1;
  return false;
}



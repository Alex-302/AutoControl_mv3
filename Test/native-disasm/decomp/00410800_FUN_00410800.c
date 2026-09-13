// FUN_00410800 @ 00410800 size=178 callers=5

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_00410800(char param_1)

{
  DWORD DVar1;
  tagPOINT local_10;
  
  if (param_1 == '\0') {
    DVar1 = GetTickCount();
    if (DVar1 - _DAT_0049fc50 < 0xfa) {
      return CONCAT44(DAT_0049fc3c,DAT_0049fc38);
    }
    GetCursorPos(&local_10);
    return CONCAT44(local_10.y,local_10.x);
  }
  _DAT_0049fc50 = DAT_004a26b4;
  if (200 < (uint)(DAT_004a26b4 - _DAT_004a32e8)) {
    GetCursorPos(&local_10);
    _DAT_004a32e8 = DAT_004a26b4;
    DAT_004a2a48 = local_10.x;
    DAT_004a2a4c = local_10.y;
    DAT_0049fc38 = local_10.x;
    DAT_0049fc3c = local_10.y;
    return CONCAT44(local_10.y,local_10.x);
  }
  DAT_0049fc38 = DAT_004a2a48;
  DAT_0049fc3c = DAT_004a2a4c;
  return CONCAT44(DAT_004a2a4c,DAT_004a2a48);
}



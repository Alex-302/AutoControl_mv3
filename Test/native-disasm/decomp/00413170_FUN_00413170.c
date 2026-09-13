// FUN_00413170 @ 00413170 size=88 callers=2

uint __fastcall FUN_00413170(uint param_1,char param_2)

{
  ushort uVar1;
  uint nVirtKey;
  
  nVirtKey = param_1 & 0x3ff;
  if (((param_1 & 0xfc00) != 0) && ((short)(param_1 & 0xfc00) != 0x400)) {
    return param_1 & 0x300;
  }
  if (param_2 != '\0') {
    uVar1 = GetKeyState(nVirtKey);
    return uVar1 & 1;
  }
  return (uint)((1 << ((byte)nVirtKey & 0x1f) & *(uint *)(DAT_004a28b0 + (nVirtKey >> 5) * 4)) != 0)
  ;
}



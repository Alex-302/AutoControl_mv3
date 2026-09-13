// FUN_00413200 @ 00413200 size=98 callers=5

bool __fastcall FUN_00413200(ushort *param_1)

{
  ushort uVar1;
  
  if (((*(char *)((int)param_1 + 3) < '\n') && ((char)param_1[1] != '\0')) &&
     ((uVar1 = *param_1, uVar1 < 0x200 || (0x203 < uVar1)))) {
    return ((*(uint *)(DAT_004a28b0 + (uint)(uVar1 >> 5) * 4) & 1 << ((byte)uVar1 & 0x1f)) != 0) !=
           (bool)DAT_004a23a2;
  }
  return (char)(DAT_004a255c / 0x5609) == '\0';
}



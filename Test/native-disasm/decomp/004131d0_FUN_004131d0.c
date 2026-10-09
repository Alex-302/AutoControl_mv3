// FUN_004131d0 @ 004131d0 size=41 callers=1

uint __fastcall FUN_004131d0(ushort *param_1)

{
  ushort uVar1;
  uint in_EAX;
  
  if ((*(char *)((int)param_1 + 3) < '\n') && ((char)param_1[1] != '\0')) {
    uVar1 = *param_1;
    in_EAX = (uint)uVar1;
    if ((uVar1 < 0x200) || (0x203 < uVar1)) {
      return CONCAT31((uint3)(byte)(uVar1 >> 8),1);
    }
  }
  return in_EAX & 0xffffff00;
}



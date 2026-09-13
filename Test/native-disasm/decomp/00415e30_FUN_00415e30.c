// FUN_00415e30 @ 00415e30 size=75 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

byte __fastcall FUN_00415e30(int param_1)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  
  bVar3 = DAT_004a23a0 == '\0';
  if (((bVar3 & DAT_004a23c5) == 0) && (0x3c < param_1 - _DAT_004a23b8)) {
    bVar2 = 1;
  }
  else {
    bVar2 = 0;
  }
  bVar1 = DAT_004a23a1 & DAT_004a23c5 & bVar3;
  return ((bVar1 ^ 1) & DAT_004a23c5 & bVar3 | bVar1 * '\x02') * '\x02' | bVar2;
}



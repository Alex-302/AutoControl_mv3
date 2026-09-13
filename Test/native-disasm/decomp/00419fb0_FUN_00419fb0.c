// FUN_00419fb0 @ 00419fb0 size=104 callers=2

uint __fastcall FUN_00419fb0(char param_1,uint param_2)

{
  uint uVar1;
  undefined3 uVar2;
  byte bVar3;
  
  if (param_2 == 0) {
    if (((*(byte *)(DAT_004a28b0 + 0x14) & 4) == 0) && ((*(byte *)(DAT_004a28b0 + 0x14) & 8) == 0))
    {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
    if (((*(byte *)(DAT_004a28b0 + 0x14) & 1) == 0) && ((*(byte *)(DAT_004a28b0 + 0x14) & 2) == 0))
    {
      bVar3 = 0;
    }
    else {
      bVar3 = 1;
    }
  }
  else {
    uVar1 = param_2 >> 3 & 0xffffff01;
    bVar3 = (byte)(param_2 >> 2) & 1;
  }
  uVar2 = (undefined3)(uVar1 >> 8);
  if (param_1 == '\0') {
    if ((char)uVar1 == '\0') {
      if (bVar3 == 0) {
        return uVar1;
      }
      goto LAB_0041a014;
    }
  }
  else if ((char)uVar1 != '\0') goto LAB_0041a008;
  if (bVar3 != 0) {
LAB_0041a008:
    return CONCAT31(uVar2,2);
  }
LAB_0041a014:
  return CONCAT31(uVar2,1);
}



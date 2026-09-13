// FUN_00415bf0 @ 00415bf0 size=275 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __fastcall FUN_00415bf0(POINT *param_1,uint param_2)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  undefined1 local_19;
  uint *local_18 [2];
  uint local_10;
  uint local_c;
  
  local_c = param_2;
  if ((DAT_0049fc4c != DAT_004a26b4) &&
     (((300 < (uint)(DAT_004a26b4 - DAT_0049fc4c) ||
       (uVar1 = param_1->x - _DAT_0049fc6c, uVar4 = (int)uVar1 >> 0x1f,
       3 < (int)((uVar1 ^ uVar4) - uVar4))) ||
      (uVar1 = param_1->y - _DAT_0049fc70, uVar4 = (int)uVar1 >> 0x1f,
      3 < (int)((uVar1 ^ uVar4) - uVar4))))) {
    local_19 = 0;
    piVar2 = FUN_00441bd0((int *)local_18);
    local_10 = local_10 & 0xffffff00;
    FUN_0044a210(&local_19,local_10,DAT_004a28c0,0,(uint *)*piVar2,piVar2[1]);
  }
  uVar1 = param_2 >> 5;
  uVar4 = param_2 & 0x1f;
  local_10 = 1 << (sbyte)uVar4;
  if ((DAT_004a28c0[uVar1] & local_10) == 0) {
    local_18[0] = (uint *)(DAT_004a27f0 + uVar1 * 4);
    uVar3 = FUN_00415b40(param_1,local_c);
    if ((char)uVar3 == '\0') {
      uVar3 = *local_18[0] & ~(1 << uVar4);
    }
    else {
      uVar3 = *local_18[0] | 1 << uVar4;
    }
    *local_18[0] = uVar3;
    DAT_004a28c0[uVar1] = DAT_004a28c0[uVar1] | 1 << uVar4;
    if (DAT_0049fc4c != DAT_004a26b4) {
      DAT_0049fc4c = DAT_004a26b4;
      _DAT_0049fc6c = param_1->x;
      _DAT_0049fc70 = param_1->y;
    }
  }
  return (*(uint *)(uVar1 * 4 + DAT_004a27f0) & local_10) != 0;
}



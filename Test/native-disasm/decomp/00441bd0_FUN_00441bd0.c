// FUN_00441bd0 @ 00441bd0 size=84 callers=1

int * __fastcall FUN_00441bd0(int *param_1)

{
  uint uVar1;
  
  uVar1 = DAT_004a28cc;
  *param_1 = DAT_004a28c0;
  param_1[1] = 0;
  if (uVar1 != 0) {
    if (((int)uVar1 < 0) && (uVar1 != 0)) {
      *param_1 = *param_1 + (~uVar1 >> 5) * -4 + -4;
      param_1[1] = uVar1 & 0x1f;
      return param_1;
    }
    *param_1 = *param_1 + (uVar1 >> 5) * 4;
    param_1[1] = uVar1 & 0x1f;
  }
  return param_1;
}



// FUN_0046fbac @ 0046fbac size=106 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0046fbac(double param_1)

{
  uint uVar1;
  float10 fVar2;
  float10 fVar3;
  
  uVar1 = __fpclass(param_1);
  if ((uVar1 & 0x90) == 0) {
    fVar2 = FUN_00475826(param_1);
    if ((float10)param_1 == fVar2) {
      fVar2 = (float10)param_1 * (float10)_DAT_0048f230;
      fVar3 = FUN_00475826((double)fVar2);
      if ((float10)(double)fVar2 == fVar3) {
        return 2;
      }
      return 1;
    }
  }
  return 0;
}



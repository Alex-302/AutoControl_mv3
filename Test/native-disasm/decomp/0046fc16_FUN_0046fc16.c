// FUN_0046fc16 @ 0046fc16 size=299 callers=0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0046fc16(int param_1,int param_2,int param_3,int param_4,undefined8 *param_5)

{
  double dVar1;
  double dVar2;
  int iVar3;
  
  dVar1 = ABS((double)CONCAT44(param_2,param_1));
  dVar2 = _DAT_004868d8;
  if (param_4 == 0x7ff00000) {
    if (param_3 == 0) {
      if ((dVar1 <= 1.0) && (dVar2 = 1.0, dVar1 < 1.0)) {
        dVar2 = 0.0;
      }
      goto LAB_0046fd3b;
    }
  }
  else if ((param_4 == -0x100000) && (param_3 == 0)) {
    if (dVar1 <= 1.0) {
      dVar2 = 1.0;
      if (dVar1 < 1.0) {
        dVar2 = _DAT_004868d8;
      }
    }
    else {
      dVar2 = 0.0;
    }
    goto LAB_0046fd3b;
  }
  if (param_2 == 0x7ff00000) {
    if (param_1 != 0) {
      return 0;
    }
    if (((double)CONCAT44(param_4,param_3) <= 0.0) &&
       (dVar2 = 0.0, 0.0 <= (double)CONCAT44(param_4,param_3))) {
      dVar2 = 1.0;
    }
  }
  else {
    if (param_2 != -0x100000) {
      return 0;
    }
    if (param_1 != 0) {
      return 0;
    }
    iVar3 = FUN_0046fbac((double)CONCAT44(param_4,param_3));
    if ((double)CONCAT44(param_4,param_3) <= 0.0) {
      if (0.0 <= (double)CONCAT44(param_4,param_3)) {
        dVar2 = 1.0;
      }
      else {
        dVar2 = 0.0;
        if (iVar3 == 1) {
          dVar2 = _DAT_004868e8;
        }
      }
    }
    else {
      dVar2 = _DAT_004868d8;
      if (iVar3 == 1) {
        dVar2 = -_DAT_004868d8;
      }
    }
  }
LAB_0046fd3b:
  *param_5 = dVar2;
  return 0;
}



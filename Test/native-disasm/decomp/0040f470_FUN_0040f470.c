// FUN_0040f470 @ 0040f470 size=55 callers=4

uint __fastcall FUN_0040f470(int param_1)

{
  int *piVar1;
  
  piVar1 = DAT_004a2514;
  while( true ) {
    if (piVar1 == DAT_004a2518) {
      return 0;
    }
    if (*piVar1 == param_1) break;
    piVar1 = piVar1 + 1;
  }
  if (piVar1 == DAT_004a2518) {
    return 0;
  }
  return (uint)~((int)piVar1 - (int)DAT_004a2514 >> 2) >> 0x1f;
}



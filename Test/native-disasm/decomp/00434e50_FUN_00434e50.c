// FUN_00434e50 @ 00434e50 size=104 callers=2

int __fastcall FUN_00434e50(int *param_1)

{
  int *piVar1;
  short *psVar2;
  int iVar3;
  short *psVar4;
  
  if (param_1[4] != 0) {
    piVar1 = param_1;
    if (7 < (uint)param_1[5]) {
      piVar1 = (int *)*param_1;
    }
    psVar4 = (short *)((int)piVar1 + (param_1[4] + -1) * 2);
    while( true ) {
      psVar2 = (short *)&stack0x00000004;
      iVar3 = 1;
      while (*psVar2 != *psVar4) {
        psVar2 = psVar2 + 1;
        iVar3 = iVar3 + -1;
        if (iVar3 == 0) {
          if (7 < (uint)param_1[5]) {
            param_1 = (int *)*param_1;
          }
          return (int)psVar4 - (int)param_1 >> 1;
        }
      }
      psVar2 = (short *)FUN_0043a000(param_1);
      if (psVar4 == psVar2) break;
      psVar4 = psVar4 + -1;
    }
  }
  return -1;
}



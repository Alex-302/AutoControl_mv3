// FUN_00442000 @ 00442000 size=69 callers=1

int __fastcall FUN_00442000(int *param_1,short *param_2)

{
  short *psVar1;
  short *psVar2;
  
  psVar1 = (short *)param_1[1];
  psVar2 = (short *)*param_1;
  if (psVar2 != psVar1) {
    do {
      if (*psVar2 == *param_2) break;
      psVar2 = psVar2 + 1;
    } while (psVar2 != psVar1);
  }
  if (psVar2 == psVar1) {
    return -1;
  }
  return (int)psVar2 - *param_1 >> 1;
}



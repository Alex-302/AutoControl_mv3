// FUN_00444df0 @ 00444df0 size=78 callers=4

void __fastcall FUN_00444df0(int *param_1)

{
  char *pcVar1;
  char *pcVar2;
  
  pcVar2 = (char *)*param_1;
  if (pcVar2 != (char *)0x0) {
    pcVar1 = (char *)param_1[1];
    for (; pcVar2 != pcVar1; pcVar2 = pcVar2 + 0x10) {
      FUN_00434820(pcVar2);
    }
    FUN_00402430((void *)*param_1,param_1[2] - *param_1 >> 4,0x10);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}



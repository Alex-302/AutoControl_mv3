// FUN_00452c60 @ 00452c60 size=86 callers=1

char * __fastcall FUN_00452c60(char *param_1,char *param_2,char *param_3,char *param_4)

{
  bool bVar1;
  char *pcVar2;
  
  pcVar2 = param_1;
  while ((pcVar2 != param_2 && (param_3 != param_4))) {
    bVar1 = FUN_004533d0(&stack0x0000000c,*pcVar2,*param_3);
    pcVar2 = pcVar2 + 1;
    param_3 = param_3 + 1;
    if (!bVar1) {
      return param_1;
    }
  }
  if (param_3 == param_4) {
    param_1 = pcVar2;
  }
  return param_1;
}



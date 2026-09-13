// FUN_00452b30 @ 00452b30 size=103 callers=1

void __fastcall
FUN_00452b30(undefined4 *param_1,char *param_2,char *param_3,char *param_4,char *param_5)

{
  char *pcVar1;
  bool bVar2;
  
  pcVar1 = param_3;
  while ((pcVar1 != param_4 && (param_2 != param_5))) {
    bVar2 = FUN_004533d0(&stack0x00000010,*pcVar1,*param_2);
    param_2 = param_2 + 1;
    pcVar1 = pcVar1 + 1;
    if (!bVar2) {
      *param_1 = param_3;
      return;
    }
  }
  if (param_2 == param_5) {
    param_3 = pcVar1;
  }
  *param_1 = param_3;
  return;
}



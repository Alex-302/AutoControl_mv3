// FUN_00454e60 @ 00454e60 size=89 callers=1

void * __thiscall FUN_00454e60(void *this,char *param_1,char *param_2,char *param_3,char *param_4)

{
  char *pcVar1;
  bool bVar2;
  
  pcVar1 = param_1;
  do {
    if (pcVar1 == param_2) {
      bVar2 = param_3 == param_4;
LAB_00454eaf:
      if (bVar2) {
        param_1 = pcVar1;
      }
      break;
    }
    bVar2 = true;
    if (param_3 == param_4) goto LAB_00454eaf;
    bVar2 = FUN_004533d0(&stack0x00000014,*pcVar1,*param_3);
    pcVar1 = pcVar1 + 1;
    param_3 = param_3 + 1;
  } while (bVar2);
  *(char **)this = param_1;
  return this;
}



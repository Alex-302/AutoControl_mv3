// FUN_004701e2 @ 004701e2 size=149 callers=4

int __cdecl FUN_004701e2(char *param_1,char *param_2,uint param_3,void *param_4)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  
  pcVar4 = param_1;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar4 = pcVar4 + (1 - (int)(param_1 + 1));
  if ((char *)(-1 - param_3) < pcVar4) {
    iVar3 = 0xc;
  }
  else {
    pcVar5 = pcVar4 + param_3 + 1;
    pcVar2 = __calloc_base((uint)pcVar5,1);
    if (param_3 != 0) {
      iVar3 = FUN_004754f8(pcVar2,(uint)pcVar5,param_2,param_3);
      if (iVar3 != 0) goto LAB_0047026b;
    }
    iVar3 = FUN_004754f8(pcVar2 + param_3,(int)pcVar5 - param_3,param_1,(uint)pcVar4);
    if (iVar3 != 0) {
LAB_0047026b:
                    /* WARNING: Subroutine does not return */
      __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
    }
    iVar3 = append(param_4,pcVar2);
    FID_conflict__free((void *)0x0);
  }
  return iVar3;
}



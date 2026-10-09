// FUN_00452ea0 @ 00452ea0 size=186 callers=1

int __cdecl FUN_00452ea0(char *param_1,int *param_2,int param_3,int param_4)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = 0;
  uVar4 = FUN_004383a0(&param_1,(int *)&stack0x00000014);
  cVar3 = (char)uVar4;
  while (cVar3 == '\0') {
    iVar5 = iVar5 + 1;
    if (*param_1 == '\x01') {
      if (*(char *)((int)param_2 + 0xd) == '\0') {
        piVar1 = (int *)param_2[2];
        if (*(char *)((int)piVar1 + 0xd) == '\0') {
          cVar3 = *(char *)(*piVar1 + 0xd);
          param_2 = piVar1;
          piVar1 = (int *)*piVar1;
          while (cVar3 == '\0') {
            cVar3 = *(char *)(*piVar1 + 0xd);
            param_2 = piVar1;
            piVar1 = (int *)*piVar1;
          }
        }
        else {
          cVar3 = *(char *)(param_2[1] + 0xd);
          piVar2 = (int *)param_2[1];
          piVar1 = param_2;
          while ((param_2 = piVar2, cVar3 == '\0' && (piVar1 == (int *)param_2[2]))) {
            cVar3 = *(char *)(param_2[1] + 0xd);
            piVar2 = (int *)param_2[1];
            piVar1 = param_2;
          }
        }
      }
    }
    else if (*param_1 == '\x02') {
      param_3 = param_3 + 0x10;
    }
    else {
      param_4 = param_4 + 1;
    }
    uVar4 = FUN_004383a0(&param_1,(int *)&stack0x00000014);
    cVar3 = (char)uVar4;
  }
  return iVar5;
}



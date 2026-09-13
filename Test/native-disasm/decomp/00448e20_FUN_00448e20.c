// FUN_00448e20 @ 00448e20 size=94 callers=4

int * __fastcall FUN_00448e20(int *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  puVar2 = (undefined4 *)*param_1;
  if (*(char *)((int)puVar2 + 0xd) != '\0') {
    *param_1 = puVar2[2];
    return param_1;
  }
  piVar5 = (int *)*puVar2;
  if (*(char *)((int)piVar5 + 0xd) == '\0') {
    iVar3 = piVar5[2];
    if (*(char *)(piVar5[2] + 0xd) == '\0') {
      do {
        iVar4 = iVar3;
        iVar3 = *(int *)(iVar4 + 8);
      } while (*(char *)(iVar3 + 0xd) == '\0');
      *param_1 = iVar4;
      return param_1;
    }
  }
  else {
    piVar5 = (int *)puVar2[1];
    cVar1 = *(char *)((int)piVar5 + 0xd);
    while ((cVar1 == '\0' && (*param_1 == *piVar5))) {
      *param_1 = (int)piVar5;
      piVar5 = (int *)piVar5[1];
      cVar1 = *(char *)((int)piVar5 + 0xd);
    }
    if (*(char *)(*param_1 + 0xd) != '\0') {
      return param_1;
    }
  }
  *param_1 = (int)piVar5;
  return param_1;
}



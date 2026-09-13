// FUN_00434070 @ 00434070 size=46 callers=2

int __fastcall FUN_00434070(char *param_1)

{
  char cVar1;
  
  cVar1 = *param_1;
  if (cVar1 == '\0') {
    return 0;
  }
  if (cVar1 != '\x01') {
    if (cVar1 != '\x02') {
      return 1;
    }
    return (*(int **)(param_1 + 8))[1] - **(int **)(param_1 + 8) >> 4;
  }
  return *(int *)(*(int *)(param_1 + 8) + 4);
}



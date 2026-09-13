// FUN_00404790 @ 00404790 size=380 callers=6

LPWSTR __fastcall FUN_00404790(LPWSTR param_1,HWND param_2,uint param_3,char param_4)

{
  uint uVar1;
  LPWSTR pWVar2;
  uint uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479309;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  param_1[8] = L'\0';
  param_1[9] = L'\0';
  param_1[10] = L'\0';
  param_1[0xb] = L'\0';
  param_1[10] = L'\a';
  param_1[0xb] = L'\0';
  param_1[8] = L'\0';
  param_1[9] = L'\0';
  pWVar2 = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    pWVar2 = *(LPWSTR *)param_1;
  }
  *pWVar2 = L'\0';
  FUN_0043a5b0(param_1,(param_4 != '\0') + param_3,0);
  local_8 = 0;
  pWVar2 = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    pWVar2 = *(LPWSTR *)param_1;
  }
  uVar3 = GetWindowTextW(param_2,pWVar2,*(int *)(param_1 + 8) + 1);
  if (*(uint *)(param_1 + 8) < uVar3) {
    FUN_0043a870(param_1,uVar3 - *(uint *)(param_1 + 8),0);
  }
  else {
    *(uint *)(param_1 + 8) = uVar3;
    if (*(uint *)(param_1 + 10) < 8) {
      param_1[uVar3] = L'\0';
    }
    else {
      *(undefined2 *)(*(int *)param_1 + uVar3 * 2) = 0;
    }
  }
  if ((param_4 != '\0') && (uVar3 = *(uint *)(param_1 + 8), uVar3 != 0)) {
    pWVar2 = param_1;
    if (7 < *(uint *)(param_1 + 10)) {
      pWVar2 = *(LPWSTR *)param_1;
    }
    if (*pWVar2 != L'\x202a') {
      pWVar2 = param_1;
      if (7 < *(uint *)(param_1 + 10)) {
        pWVar2 = *(LPWSTR *)param_1;
      }
      if (*pWVar2 != L'\x202b') {
        if (uVar3 <= param_3) {
          ExceptionList = local_10;
          return param_1;
        }
        uVar1 = uVar3 - 1;
        if (uVar1 <= uVar3) {
          *(uint *)(param_1 + 8) = uVar1;
          if (7 < *(uint *)(param_1 + 10)) {
            *(undefined2 *)(*(int *)param_1 + uVar1 * 2) = 0;
            ExceptionList = local_10;
            return param_1;
          }
          param_1[uVar1] = L'\0';
          ExceptionList = local_10;
          return param_1;
        }
                    /* WARNING: Subroutine does not return */
        FUN_00458ee4("invalid string position");
      }
    }
    FUN_00434f70(param_1,0,1);
  }
  ExceptionList = local_10;
  return param_1;
}



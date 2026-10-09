// FUN_00405650 @ 00405650 size=312 callers=1

LPWSTR __fastcall FUN_00405650(LPWSTR param_1,DWORD param_2)

{
  LPWSTR pWVar1;
  DWORD DVar2;
  int iVar3;
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
  pWVar1 = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    pWVar1 = *(LPWSTR *)param_1;
  }
  *pWVar1 = L'\0';
  if (*(uint *)(param_1 + 10) < 500) {
    FUN_0043d830(param_1,500);
  }
  pWVar1 = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    pWVar1 = *(LPWSTR *)param_1;
  }
  for (iVar3 = 0xfa; iVar3 != 0; iVar3 = iVar3 + -1) {
    pWVar1[0] = L'\0';
    pWVar1[1] = L'\0';
    pWVar1 = pWVar1 + 2;
  }
  param_1[8] = L'Ǵ';
  param_1[9] = L'\0';
  pWVar1 = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    pWVar1 = *(LPWSTR *)param_1;
  }
  pWVar1[500] = L'\0';
  local_8 = 0;
  pWVar1 = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    pWVar1 = *(LPWSTR *)param_1;
  }
  DVar2 = FormatMessageW(0x1200,(LPCVOID)0x0,param_2,0,pWVar1,*(DWORD *)(param_1 + 8),(va_list *)0x0
                        );
  if (*(uint *)(param_1 + 8) < DVar2) {
    FUN_0043a870(param_1,DVar2 - *(uint *)(param_1 + 8),0);
    ExceptionList = local_10;
    return param_1;
  }
  *(DWORD *)(param_1 + 8) = DVar2;
  if (*(uint *)(param_1 + 10) < 8) {
    param_1[DVar2] = L'\0';
    ExceptionList = local_10;
    return param_1;
  }
  *(undefined2 *)(*(int *)param_1 + DVar2 * 2) = 0;
  ExceptionList = local_10;
  return param_1;
}



// FUN_00404a40 @ 00404a40 size=314 callers=4

LPWSTR __fastcall FUN_00404a40(LPWSTR param_1,DWORD param_2)

{
  DWORD dwDesiredAccess;
  HANDLE hProcess;
  LPWSTR pWVar1;
  BOOL BVar2;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479339;
  local_10 = ExceptionList;
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
  local_8 = 0;
  dwDesiredAccess = 0x400;
  if (DAT_004a24ae != '\0') {
    dwDesiredAccess = 0x1000;
  }
  hProcess = OpenProcess(dwDesiredAccess,0,param_2);
  if (hProcess != (HANDLE)0x0) {
    if (*(uint *)(param_1 + 8) < 200) {
      FUN_0043a870(param_1,200 - *(uint *)(param_1 + 8),0);
    }
    else {
      param_1[8] = L'È';
      param_1[9] = L'\0';
      if (*(uint *)(param_1 + 10) < 8) {
        param_1[200] = L'\0';
      }
      else {
        *(undefined2 *)(*(int *)param_1 + 400) = 0;
      }
    }
    local_14 = *(uint *)(param_1 + 8);
    pWVar1 = param_1;
    if (7 < *(uint *)(param_1 + 10)) {
      pWVar1 = *(LPWSTR *)param_1;
    }
    BVar2 = QueryFullProcessImageNameW(hProcess,0,pWVar1,&local_14);
    if (BVar2 != 0) {
      if (*(uint *)(param_1 + 8) < local_14) {
        FUN_0043a870(param_1,local_14 - *(uint *)(param_1 + 8),0);
      }
      else {
        *(uint *)(param_1 + 8) = local_14;
        if (*(uint *)(param_1 + 10) < 8) {
          param_1[local_14] = L'\0';
        }
        else {
          *(undefined2 *)(*(int *)param_1 + local_14 * 2) = 0;
        }
      }
    }
    CloseHandle(hProcess);
  }
  ExceptionList = local_10;
  return param_1;
}



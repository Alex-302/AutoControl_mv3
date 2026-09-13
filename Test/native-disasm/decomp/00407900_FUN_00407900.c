// FUN_00407900 @ 00407900 size=362 callers=2

undefined4 * __fastcall FUN_00407900(undefined4 *param_1,LPCSTR param_2)

{
  char cVar1;
  undefined4 *puVar2;
  HANDLE hObject;
  LPCWSTR pWVar3;
  uint *puVar4;
  int iVar5;
  void *local_48 [5];
  uint local_34;
  undefined4 local_30;
  undefined4 local_20;
  uint local_1c;
  undefined4 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004796e1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 0xf;
  param_1[4] = 0;
  puVar2 = param_1;
  if (0xf < (uint)param_1[5]) {
    puVar2 = (undefined4 *)*param_1;
  }
  *(undefined1 *)puVar2 = 0;
  local_8 = 0;
  local_14 = 1;
  if (0xf < *(uint *)(param_2 + 0x14)) {
    param_2 = *(LPCSTR *)param_2;
  }
  local_18 = param_1;
  hObject = CreateFileA(param_2,0x80000000,7,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
  if (hObject != (HANDLE)0xffffffff) {
    local_1c = 7;
    local_20 = 0;
    local_30 = (LPCWSTR)((uint)local_30._2_2_ << 0x10);
    FUN_0043d830(&local_30,100);
    iVar5 = 0x32;
    pWVar3 = (LPCWSTR)&local_30;
    if (7 < local_1c) {
      pWVar3 = local_30;
    }
    for (; iVar5 != 0; iVar5 = iVar5 + -1) {
      pWVar3[0] = L'\0';
      pWVar3[1] = L'\0';
      pWVar3 = pWVar3 + 2;
    }
    local_20 = 100;
    pWVar3 = (LPCWSTR)&local_30;
    if (7 < local_1c) {
      pWVar3 = local_30;
    }
    pWVar3[100] = L'\0';
    local_8 = 1;
    pWVar3 = (LPCWSTR)&local_30;
    if (7 < local_1c) {
      pWVar3 = local_30;
    }
    cVar1 = HidD_GetProductString(hObject,pWVar3,200);
    if (cVar1 != '\0') {
      pWVar3 = (LPCWSTR)&local_30;
      if (7 < local_1c) {
        pWVar3 = local_30;
      }
      puVar4 = (uint *)FUN_004044f0((LPSTR)local_48,pWVar3,-1,0x7fffffff);
      FUN_00435570(param_1,puVar4);
      if (0xf < local_34) {
        FUN_00402430(local_48[0],local_34 + 1,1);
      }
    }
    CloseHandle(hObject);
    if (7 < local_1c) {
      FUN_00402430(local_30,local_1c + 1,2);
    }
  }
  ExceptionList = local_10;
  return param_1;
}



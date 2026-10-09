// FUN_00409a70 @ 00409a70 size=602 callers=1

DWORD __fastcall
FUN_00409a70(LPCWSTR param_1,char *param_2,char param_3,char param_4,uint param_5,int param_6)

{
  DWORD *pDVar1;
  char cVar2;
  LPCWSTR pWVar3;
  int *piVar4;
  uint *lpBuffer;
  BOOL BVar5;
  void *this;
  LPCWSTR pWVar6;
  int iVar7;
  DWORD DVar8;
  void *local_4c [5];
  uint local_38;
  HANDLE local_34 [2];
  LPCWSTR local_2c [2];
  FILETIME local_24;
  LPCWSTR local_1c;
  LPCWSTR local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00479c45;
  local_10 = ExceptionList;
  local_14 = 0;
  ExceptionList = &local_10;
  local_24.dwHighDateTime = (DWORD)param_2;
  if ((*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a2f48) &&
     (ExceptionList = &local_10, FUN_0045a219(&DAT_004a2f48), DAT_004a2f48 == -1)) {
    local_8 = 0;
    local_18 = (LPCWSTR)0x0;
    FUN_00436aa0(&local_18);
    _atexit(thunk_FUN_00432c60);
    local_8 = 0xffffffff;
    FUN_0045a1da(&DAT_004a2f48);
  }
  FUN_00436830(&local_1c,(ushort *)param_1);
  iVar7 = 0;
  if (local_1c != local_18) {
    do {
      local_1c = *(LPCWSTR *)local_1c;
      iVar7 = iVar7 + 1;
    } while (local_1c != local_18);
    if (iVar7 != 0) {
      FUN_00448d00(&local_18,(ushort *)param_1);
      pWVar3 = local_18;
      if (local_18 == DAT_004a2f94) {
        local_18 = param_1;
        FUN_0044a6c0(this,(int *)local_2c,this,&local_18);
        pWVar3 = local_2c[0];
      }
      pWVar3 = pWVar3 + 0x10;
      goto LAB_00409bd3;
    }
  }
  cVar2 = 'W';
  if (param_4 != '\0') {
    cVar2 = 'A';
  }
  piVar4 = FUN_00405440(local_34,param_1,cVar2,0);
  local_8 = 1;
  local_14 = 1;
  FUN_00448d00(&local_18,(ushort *)param_1);
  pWVar3 = local_18;
  pWVar6 = local_18;
  if (local_18 == DAT_004a2f94) {
    local_18 = param_1;
    FUN_0044a6c0(pWVar3,(int *)local_2c,pWVar3,&local_18);
    pWVar6 = local_2c[0];
  }
  pWVar3 = pWVar6 + 0x10;
  if (*(HANDLE *)(pWVar6 + 0x10) != (HANDLE)0x0) {
    CloseHandle(*(HANDLE *)(pWVar6 + 0x10));
  }
  *(int *)pWVar3 = *piVar4;
  *(int *)(pWVar6 + 0x12) = piVar4[1];
  *piVar4 = 0;
  piVar4[1] = 0;
LAB_00409bd3:
  local_8 = 0xffffffff;
  if (((local_14 & 1) != 0) && (local_34[0] != (HANDLE)0x0)) {
    CloseHandle(local_34[0]);
  }
  lpBuffer = FUN_00404220((uint *)local_4c,(char *)local_24.dwHighDateTime);
  if (*(HANDLE *)pWVar3 == (HANDLE)0x0) {
    DVar8 = *(DWORD *)(pWVar3 + 2);
  }
  else {
    pDVar1 = lpBuffer + 4;
    if (0xf < lpBuffer[5]) {
      lpBuffer = (uint *)*lpBuffer;
    }
    BVar5 = WriteFile(*(HANDLE *)pWVar3,lpBuffer,*pDVar1,&local_24.dwHighDateTime,(LPOVERLAPPED)0x0)
    ;
    if (BVar5 == 0) {
      DVar8 = GetLastError();
    }
    else {
      DVar8 = 0;
    }
  }
  if (0xf < local_38) {
    FUN_00402430(local_4c[0],local_38 + 1,1);
  }
  if ((param_3 != '\0') || (DVar8 != 0)) {
    if (param_5 != 0 || param_6 != 0) {
      local_24 = (FILETIME)
                 __allmul(param_5 + 0x30b66800,param_6 + 0xa97 + (uint)(0xcf4997ff < param_5),10000,
                          0);
      SetFileTime(*(HANDLE *)pWVar3,(FILETIME *)0x0,(FILETIME *)0x0,&local_24);
    }
    FUN_00436830(&local_24.dwLowDateTime,(ushort *)param_1);
    for (piVar4 = (int *)local_24.dwLowDateTime; piVar4 != (int *)local_24.dwHighDateTime;
        piVar4 = (int *)*piVar4) {
    }
    FUN_004369f0((int *)&param_3,(int *)local_24.dwLowDateTime,(int *)local_24.dwHighDateTime);
  }
  ExceptionList = local_10;
  return DVar8;
}



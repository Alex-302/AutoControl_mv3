// FUN_00405440 @ 00405440 size=499 callers=6

/* WARNING: Removing unreachable block (ram,0x004054d6) */

void * __thiscall FUN_00405440(void *this,LPCWSTR param_1,char param_2,uint param_3)

{
  char cVar1;
  DWORD DVar2;
  HANDLE pvVar3;
  LPCWSTR pszPath;
  byte *pbVar4;
  LPCWSTR lpFileName;
  int iVar5;
  undefined4 uVar6;
  BOOL BVar7;
  byte *pbVar8;
  code *pcVar9;
  undefined2 uVar10;
  undefined4 *in_stack_ffffff50;
  undefined4 local_8c [24];
  void *local_2c [5];
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  pcVar9 = GetLastError_exref;
  local_8 = 0xffffffff;
  puStack_c = &LAB_004793e3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  if ((param_2 == 'W') || (param_2 == 'A')) {
    cVar1 = '\0';
                    /* WARNING: Ignoring partial resolution of indirect */
    uVar10 = 0;
    FUN_0043a750(&stack0xffffff50,(undefined4 *)param_1,0,0xffffffff);
    pszPath = FUN_00403a70(local_8c,in_stack_ffffff50);
    local_8 = 0;
    if (*(int *)(pszPath + 8) != 0) {
      pbVar4 = (byte *)FUN_00404580((LPSTR)local_2c,pszPath,0x7fffffff);
      local_8 = CONCAT31(local_8._1_3_,1);
      pbVar8 = pbVar4;
      if (0xf < *(uint *)(pbVar4 + 0x14)) {
        pbVar8 = *(byte **)pbVar4;
      }
      cVar1 = FUN_00446870(pbVar8,pbVar8 + *(int *)(pbVar4 + 0x10),pbVar8,&DAT_004a275c,0x10);
      if (0xf < local_18) {
        FUN_00402430(local_2c[0],local_18 + 1,1);
      }
      if (cVar1 == '\0') {
        lpFileName = pszPath;
        if (7 < *(uint *)(pszPath + 10)) {
          lpFileName = *(LPCWSTR *)pszPath;
        }
        DVar2 = GetFileAttributesW(lpFileName);
        if (DVar2 == 0xffffffff) {
          if (7 < *(uint *)(pszPath + 10)) {
            pszPath = *(LPCWSTR *)pszPath;
          }
          iVar5 = SHCreateDirectory((HWND)0x0,pszPath);
          if (iVar5 != 0) {
            *(int *)((int)this + 4) = iVar5;
            FUN_00403c20(local_8c);
            ExceptionList = local_10;
            return this;
          }
        }
      }
    }
    if (7 < *(uint *)(param_1 + 10)) {
      param_1 = *(LPCWSTR *)param_1;
    }
    pvVar3 = CreateFileW(param_1,0x40000000,5,(LPSECURITY_ATTRIBUTES)0x0,4,param_3 | 0x80,
                         (HANDLE)0x0);
    *(HANDLE *)this = pvVar3;
    pcVar9 = GetLastError_exref;
    if ((pvVar3 != (HANDLE)0xffffffff) && (cVar1 == '\0')) {
      if (param_2 == 'A') {
        SetFilePointer(pvVar3,0,(PLONG)0x0,2);
        pcVar9 = GetLastError_exref;
      }
      else {
        BVar7 = SetEndOfFile(pvVar3);
        pcVar9 = GetLastError_exref;
        if (BVar7 == 0) {
          DVar2 = GetLastError();
          *(DWORD *)((int)this + 4) = DVar2;
        }
      }
    }
    FUN_00403c20(local_8c);
  }
  else {
    if (7 < *(uint *)(param_1 + 10)) {
      param_1 = *(LPCWSTR *)param_1;
    }
    DVar2 = 0x80000000;
    if (param_2 == 'P') {
      DVar2 = 0x80;
    }
    pvVar3 = CreateFileW(param_1,DVar2,5,(LPSECURITY_ATTRIBUTES)0x0,3,param_3 | 0x80,(HANDLE)0x0);
    *(HANDLE *)this = pvVar3;
  }
  if (*(int *)this == -1) {
    *(undefined4 *)this = 0;
    uVar6 = (*pcVar9)();
    *(undefined4 *)((int)this + 4) = uVar6;
  }
  ExceptionList = local_10;
  return this;
}



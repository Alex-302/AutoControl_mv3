// ___delayLoadHelper2@8 @ 00477293 size=645 callers=3

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___delayLoadHelper2@8
   
   Library: Visual Studio 2015 Release */

FARPROC ___delayLoadHelper2_8(uint *param_1,int *param_2)

{
  HMODULE pHVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  code *pcVar5;
  int iVar6;
  HMODULE hLibModule;
  FARPROC pFVar7;
  int local_34;
  uint *local_30;
  int *local_2c;
  LPCSTR local_28;
  uint local_24;
  char *local_20;
  HMODULE local_1c;
  FARPROC local_18;
  DWORD local_14;
  int *local_10;
  int *local_c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  DloadAcquireSectionWriteAccess();
  pcVar5 = DAT_0048cabc;
  local_34 = 0x24;
  local_30 = param_1;
  local_28 = (LPCSTR)(param_1[1] + 0x400000);
  local_c = (int *)(param_1[2] + 0x400000);
  local_10 = (int *)(param_1[5] + 0x400000);
  uVar2 = param_1[7];
  local_2c = param_2;
  local_24 = 0;
  local_20 = (char *)0x0;
  local_1c = (HMODULE)0x0;
  local_18 = (FARPROC)0x0;
  local_14 = 0;
  if ((*param_1 & 1) == 0) {
    local_c = &local_34;
    DloadReleaseSectionWriteAccess();
    RaiseException(0xc06d0057,0,1,(ULONG_PTR *)&local_c);
    return (FARPROC)0x0;
  }
  hLibModule = (HMODULE)*local_c;
  iVar6 = (int)((int)param_2 - (param_1[3] + 0x400000)) >> 2;
  uVar3 = *(uint *)(param_1[4] + 0x400000 + iVar6 * 4);
  local_24 = ~(uVar3 >> 0x1f) & 1;
  local_20 = IMAGE_DOS_HEADER_00400000.e_magic + uVar3 + 2;
  if (local_24 == 0) {
    local_20 = (char *)(uVar3 & 0xffff);
  }
  pFVar7 = (FARPROC)0x0;
  if (DAT_0048cabc != (code *)0x0) {
    (*(code *)PTR_guard_check_icall_004805b0)(0,&local_34);
    pFVar7 = (FARPROC)(*pcVar5)();
    if (pFVar7 != (FARPROC)0x0) goto LAB_004774da;
  }
  pcVar5 = DAT_0048cabc;
  if (hLibModule == (HMODULE)0x0) {
    if (DAT_0048cabc == (code *)0x0) {
LAB_004773a6:
      hLibModule = LoadLibraryExA(local_28,(HANDLE)0x0,0);
      if (hLibModule == (HMODULE)0x0) {
        local_14 = GetLastError();
        pcVar5 = DAT_0048cac0;
        if (DAT_0048cac0 == (code *)0x0) {
LAB_004773e2:
          local_c = &local_34;
          DloadReleaseSectionWriteAccess();
          RaiseException(0xc06d007e,0,1,(ULONG_PTR *)&local_c);
          return local_18;
        }
        (*(code *)PTR_guard_check_icall_004805b0)(3,&local_34);
        hLibModule = (HMODULE)(*pcVar5)();
        if (hLibModule == (HMODULE)0x0) goto LAB_004773e2;
      }
    }
    else {
      (*(code *)PTR_guard_check_icall_004805b0)(1,&local_34);
      hLibModule = (HMODULE)(*pcVar5)();
      if (hLibModule == (HMODULE)0x0) goto LAB_004773a6;
    }
    LOCK();
    pHVar1 = (HMODULE)*local_c;
    *local_c = (int)hLibModule;
    UNLOCK();
    if (pHVar1 == hLibModule) {
      FreeLibrary(hLibModule);
    }
  }
  pcVar5 = DAT_0048cabc;
  local_1c = hLibModule;
  if (DAT_0048cabc != (code *)0x0) {
    (*(code *)PTR_guard_check_icall_004805b0)(2,&local_34);
    pFVar7 = (FARPROC)(*pcVar5)();
  }
  if (((pFVar7 == (FARPROC)0x0) &&
      ((((param_1[5] == 0 || (param_1[7] == 0)) ||
        (iVar4 = hLibModule[0xf].unused, *(int *)((int)&hLibModule->unused + iVar4) != 0x4550)) ||
       (((*(uint *)((int)&hLibModule[2].unused + iVar4) != uVar2 ||
         (hLibModule != *(HMODULE *)((int)&hLibModule[0xd].unused + iVar4))) ||
        (pFVar7 = (FARPROC)local_10[iVar6], (FARPROC)local_10[iVar6] == (FARPROC)0x0)))))) &&
     (pFVar7 = GetProcAddress(hLibModule,local_20), pFVar7 == (FARPROC)0x0)) {
    local_14 = GetLastError();
    pcVar5 = DAT_0048cac0;
    if (DAT_0048cac0 != (code *)0x0) {
      (*(code *)PTR_guard_check_icall_004805b0)(4,&local_34);
      pFVar7 = (FARPROC)(*pcVar5)();
      if (pFVar7 != (FARPROC)0x0) goto LAB_004774d5;
    }
    local_10 = &local_34;
    DloadReleaseSectionWriteAccess();
    RaiseException(0xc06d007f,0,1,(ULONG_PTR *)&local_10);
    DloadAcquireSectionWriteAccess();
    pFVar7 = local_18;
  }
LAB_004774d5:
  *param_2 = (int)pFVar7;
LAB_004774da:
  pcVar5 = DAT_0048cabc;
  if (DAT_0048cabc != (code *)0x0) {
    local_14 = 0;
    local_1c = hLibModule;
    local_18 = pFVar7;
    (*(code *)PTR_guard_check_icall_004805b0)(5,&local_34);
    (*pcVar5)();
  }
  DloadReleaseSectionWriteAccess();
  return pFVar7;
}



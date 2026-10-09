// ___vcrt_getptd_noexit @ 0045f05b size=146 callers=1

/* Library Function - Single Match
    ___vcrt_getptd_noexit
   
   Library: Visual Studio 2015 Release */

LPVOID ___vcrt_getptd_noexit(void)

{
  DWORD dwErrCode;
  LPVOID pvVar1;
  int iVar2;
  LPVOID pvVar3;
  LPVOID _Memory;
  
  if (DAT_0049d0b0 == 0xffffffff) {
    return (LPVOID)0x0;
  }
  dwErrCode = GetLastError();
  pvVar1 = (LPVOID)___vcrt_FlsGetValue(DAT_0049d0b0);
  if (pvVar1 == (LPVOID)0xffffffff) {
LAB_0045f09b:
    pvVar1 = (LPVOID)0x0;
    goto LAB_0045f0e1;
  }
  if (pvVar1 != (LPVOID)0x0) goto LAB_0045f0e1;
  iVar2 = ___vcrt_FlsSetValue(DAT_0049d0b0,(LPVOID)0xffffffff);
  if (iVar2 == 0) goto LAB_0045f09b;
  pvVar3 = __calloc_base(1,0x28);
  if (pvVar3 == (LPVOID)0x0) {
LAB_0045f0c3:
    ___vcrt_FlsSetValue(DAT_0049d0b0,(LPVOID)0x0);
    pvVar1 = (LPVOID)0x0;
    _Memory = pvVar3;
  }
  else {
    iVar2 = ___vcrt_FlsSetValue(DAT_0049d0b0,pvVar3);
    if (iVar2 == 0) goto LAB_0045f0c3;
    _Memory = (void *)0x0;
    pvVar1 = pvVar3;
  }
  FID_conflict__free(_Memory);
LAB_0045f0e1:
  SetLastError(dwErrCode);
  return pvVar1;
}



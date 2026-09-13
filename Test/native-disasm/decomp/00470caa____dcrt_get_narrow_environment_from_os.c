// ___dcrt_get_narrow_environment_from_os @ 00470caa size=131 callers=1

/* Library Function - Single Match
    ___dcrt_get_narrow_environment_from_os
   
   Library: Visual Studio 2015 Release */

LPSTR ___dcrt_get_narrow_environment_from_os(void)

{
  LPWCH lpWideCharStr;
  wchar_t *pwVar1;
  size_t cbMultiByte;
  LPSTR lpMultiByteStr;
  int iVar2;
  LPSTR pCVar3;
  
  lpWideCharStr = GetEnvironmentStringsW();
  if (lpWideCharStr != (LPWCH)0x0) {
    pwVar1 = find_end_of_double_null_terminated_sequence(lpWideCharStr);
    iVar2 = (int)pwVar1 - (int)lpWideCharStr >> 1;
    cbMultiByte = WideCharToMultiByte(0,0,lpWideCharStr,iVar2,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
    if (cbMultiByte != 0) {
      lpMultiByteStr = __malloc_base(cbMultiByte);
      if (lpMultiByteStr == (LPSTR)0x0) {
LAB_00470d0c:
        pCVar3 = (LPSTR)0x0;
      }
      else {
        iVar2 = WideCharToMultiByte(0,0,lpWideCharStr,iVar2,lpMultiByteStr,cbMultiByte,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        if (iVar2 == 0) goto LAB_00470d0c;
        pCVar3 = lpMultiByteStr;
        lpMultiByteStr = (LPSTR)0x0;
      }
      FID_conflict__free(lpMultiByteStr);
      goto LAB_00470d19;
    }
  }
  pCVar3 = (LPSTR)0x0;
LAB_00470d19:
  if (lpWideCharStr != (LPWCH)0x0) {
    FreeEnvironmentStringsW(lpWideCharStr);
  }
  return pCVar3;
}



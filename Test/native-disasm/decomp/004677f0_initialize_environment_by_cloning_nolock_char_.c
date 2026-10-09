// initialize_environment_by_cloning_nolock<char> @ 004677f0 size=127 callers=1

/* Library Function - Single Match
    int __cdecl initialize_environment_by_cloning_nolock<char>(void)
   
   Library: Visual Studio 2015 Release */

int __cdecl initialize_environment_by_cloning_nolock<char>(void)

{
  uint cbMultiByte;
  uint *lpMultiByteStr;
  int iVar1;
  int *piVar2;
  
  piVar2 = DAT_0049f7c4;
  if (DAT_0049f7c4 == (int *)0x0) {
    return -1;
  }
  while( true ) {
    if (*piVar2 == 0) {
      return 0;
    }
    cbMultiByte = WideCharToMultiByte(0,0,(LPCWSTR)*piVar2,-1,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
    if (cbMultiByte == 0) break;
    lpMultiByteStr = __calloc_base(cbMultiByte,1);
    if ((lpMultiByteStr == (uint *)0x0) ||
       (iVar1 = WideCharToMultiByte(0,0,(LPCWSTR)*piVar2,-1,(LPSTR)lpMultiByteStr,cbMultiByte,
                                    (LPCSTR)0x0,(LPBOOL)0x0), iVar1 == 0)) {
      FID_conflict__free(lpMultiByteStr);
      return -1;
    }
    FUN_0047106d(lpMultiByteStr,0);
    FID_conflict__free((void *)0x0);
    piVar2 = piVar2 + 1;
  }
  return -1;
}



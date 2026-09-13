// expand_argument_wildcards<> @ 00470278 size=388 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Multiple Matches With Same Base Name
    int __cdecl expand_argument_wildcards<char>(char * const,char * const,class `anonymous
   namespace'::argument_list<char> &)
    int __cdecl expand_argument_wildcards<char>(char * const,char * const,class `anonymous
   namespace'::argument_list<char> &)
   
   Library: Visual Studio 2015 Release */

int __cdecl expand_argument_wildcards<>(uchar *param_1,uchar *param_2,int *param_3)

{
  uchar uVar1;
  byte bVar2;
  int iVar3;
  HANDLE hFindFile;
  BOOL BVar4;
  int iVar5;
  int iVar6;
  _WIN32_FIND_DATAA local_148;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  for (; (((param_2 != param_1 && (uVar1 = *param_2, uVar1 != '/')) && (uVar1 != '\\')) &&
         (uVar1 != ':')); param_2 = __mbsdec(param_1,param_2)) {
  }
  uVar1 = *param_2;
  if ((uVar1 == ':') && (param_2 != param_1 + 1)) {
    iVar3 = FUN_004701e2((char *)param_1,(char *)0x0,0,param_3);
  }
  else {
    if ((uVar1 == '/') || ((uVar1 == '\\' || (uVar1 == ':')))) {
      bVar2 = 1;
    }
    else {
      bVar2 = 0;
    }
    _memset(&local_148,0,0x140);
    hFindFile = FindFirstFileExA((LPCSTR)param_1,FindExInfoStandard,&local_148,FindExSearchNameMatch
                                 ,(LPVOID)0x0,0);
    if (hFindFile == (HANDLE)0xffffffff) {
      iVar3 = FUN_004701e2((char *)param_1,(char *)0x0,0,param_3);
    }
    else {
      iVar6 = param_3[1] - *param_3 >> 2;
      do {
        if (((local_148.cFileName[0] != '.') ||
            ((local_148.cFileName[1] != '\0' &&
             ((local_148.cFileName[1] != '.' || (local_148.cFileName[2] != '\0')))))) &&
           (iVar3 = FUN_004701e2(local_148.cFileName,(char *)param_1,
                                 -(uint)bVar2 & (uint)(param_2 + (1 - (int)param_1)),param_3),
           iVar3 != 0)) goto LAB_00470348;
        BVar4 = FindNextFileA(hFindFile,&local_148);
      } while (BVar4 != 0);
      iVar5 = param_3[1] - *param_3 >> 2;
      iVar3 = 0;
      if (iVar6 != iVar5) {
        _qsort((void *)(*param_3 + iVar6 * 4),iVar5 - iVar6,4,FUN_0047003a);
      }
    }
LAB_00470348:
    if (hFindFile != (HANDLE)0xffffffff) {
      FindClose(hFindFile);
    }
  }
  return iVar3;
}



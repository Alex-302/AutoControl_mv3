// operator()<<lambda_61cee617f5178ae960314fd4d05640a0>,<lambda_6978c1fb23f02e42e1d9e99668cc68aa>&,<lambda_9cd88cf8ad10232537feb2133f08c833>_> @ 00473b64 size=137 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    public: int __thiscall __crt_seh_guarded_call<int>::operator()<class
   <lambda_61cee617f5178ae960314fd4d05640a0>,class <lambda_6978c1fb23f02e42e1d9e99668cc68aa> &,class
   <lambda_9cd88cf8ad10232537feb2133f08c833> >(class <lambda_61cee617f5178ae960314fd4d05640a0>
   &&,class <lambda_6978c1fb23f02e42e1d9e99668cc68aa> &,class
   <lambda_9cd88cf8ad10232537feb2133f08c833> &&)
   
   Library: Visual Studio 2015 Release */

int __thiscall
__crt_seh_guarded_call<int>::
operator()<<lambda_61cee617f5178ae960314fd4d05640a0>,<lambda_6978c1fb23f02e42e1d9e99668cc68aa>&,<lambda_9cd88cf8ad10232537feb2133f08c833>_>
          (__crt_seh_guarded_call<int> *this,<lambda_61cee617f5178ae960314fd4d05640a0> *param_1,
          <lambda_6978c1fb23f02e42e1d9e99668cc68aa> *param_2,
          <lambda_9cd88cf8ad10232537feb2133f08c833> *param_3)

{
  uint _FileHandle;
  HANDLE hFile;
  BOOL BVar1;
  ulong *puVar2;
  DWORD DVar3;
  int *piVar4;
  int iVar5;
  
  iVar5 = 0;
  ___acrt_lowio_lock_fh(*(uint *)param_1);
  _FileHandle = **(uint **)param_2;
  if ((*(byte *)((&DAT_0049f8f8)[(int)_FileHandle >> 6] + 0x28 + (_FileHandle & 0x3f) * 0x30) & 1)
      != 0) {
    hFile = (HANDLE)__get_osfhandle(_FileHandle);
    BVar1 = FlushFileBuffers(hFile);
    if (BVar1 != 0) goto LAB_00473bd4;
    puVar2 = ___doserrno();
    DVar3 = GetLastError();
    *puVar2 = DVar3;
  }
  piVar4 = __errno();
  *piVar4 = 9;
  iVar5 = -1;
LAB_00473bd4:
  FUN_00473bf0();
  return iVar5;
}



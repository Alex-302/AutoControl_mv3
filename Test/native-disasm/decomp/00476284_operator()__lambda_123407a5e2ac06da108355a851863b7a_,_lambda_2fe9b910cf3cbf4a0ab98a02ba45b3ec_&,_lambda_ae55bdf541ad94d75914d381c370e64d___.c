// operator()<<lambda_123407a5e2ac06da108355a851863b7a>,<lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec>&,<lambda_ae55bdf541ad94d75914d381c370e64d>_> @ 00476284 size=115 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    public: int __thiscall __crt_seh_guarded_call<int>::operator()<class
   <lambda_123407a5e2ac06da108355a851863b7a>,class <lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec> &,class
   <lambda_ae55bdf541ad94d75914d381c370e64d> >(class <lambda_123407a5e2ac06da108355a851863b7a>
   &&,class <lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec> &,class
   <lambda_ae55bdf541ad94d75914d381c370e64d> &&)
   
   Library: Visual Studio 2015 Release */

int __thiscall
__crt_seh_guarded_call<int>::
operator()<<lambda_123407a5e2ac06da108355a851863b7a>,<lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec>&,<lambda_ae55bdf541ad94d75914d381c370e64d>_>
          (__crt_seh_guarded_call<int> *this,<lambda_123407a5e2ac06da108355a851863b7a> *param_1,
          <lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec> *param_2,
          <lambda_ae55bdf541ad94d75914d381c370e64d> *param_3)

{
  uint _FileHandle;
  int iVar1;
  int *piVar2;
  
  ___acrt_lowio_lock_fh(*(uint *)param_1);
  _FileHandle = **(uint **)param_2;
  if ((*(byte *)((&DAT_0049f8f8)[(int)_FileHandle >> 6] + 0x28 + (_FileHandle & 0x3f) * 0x30) & 1)
      == 0) {
    piVar2 = __errno();
    *piVar2 = 9;
    iVar1 = -1;
  }
  else {
    iVar1 = __close_nolock(_FileHandle);
  }
  FUN_004762fa();
  return iVar1;
}



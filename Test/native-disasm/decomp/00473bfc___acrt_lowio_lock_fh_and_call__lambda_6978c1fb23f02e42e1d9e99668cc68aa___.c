// __acrt_lowio_lock_fh_and_call<<lambda_6978c1fb23f02e42e1d9e99668cc68aa>_> @ 00473bfc size=40 callers=1

/* Library Function - Single Match
    int __cdecl __acrt_lowio_lock_fh_and_call<class <lambda_6978c1fb23f02e42e1d9e99668cc68aa>
   >(int,class <lambda_6978c1fb23f02e42e1d9e99668cc68aa> &&)
   
   Library: Visual Studio 2015 Release */

int __cdecl
__acrt_lowio_lock_fh_and_call<<lambda_6978c1fb23f02e42e1d9e99668cc68aa>_>
          (int param_1,<lambda_6978c1fb23f02e42e1d9e99668cc68aa> *param_2)

{
  int iVar1;
  int local_10;
  int local_c;
  __crt_seh_guarded_call<int> local_5;
  
  local_c = param_1;
  local_10 = param_1;
  iVar1 = __crt_seh_guarded_call<int>::
          operator()<<lambda_61cee617f5178ae960314fd4d05640a0>,<lambda_6978c1fb23f02e42e1d9e99668cc68aa>&,<lambda_9cd88cf8ad10232537feb2133f08c833>_>
                    (&local_5,(<lambda_61cee617f5178ae960314fd4d05640a0> *)&local_10,param_2,
                     (<lambda_9cd88cf8ad10232537feb2133f08c833> *)&local_c);
  return iVar1;
}



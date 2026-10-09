// __acrt_lowio_lock_fh_and_call<<lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec>_> @ 00476306 size=40 callers=1

/* Library Function - Single Match
    int __cdecl __acrt_lowio_lock_fh_and_call<class <lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec>
   >(int,class <lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec> &&)
   
   Library: Visual Studio 2015 Release */

int __cdecl
__acrt_lowio_lock_fh_and_call<<lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec>_>
          (int param_1,<lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec> *param_2)

{
  int iVar1;
  int local_10;
  int local_c;
  __crt_seh_guarded_call<int> local_5;
  
  local_c = param_1;
  local_10 = param_1;
  iVar1 = __crt_seh_guarded_call<int>::
          operator()<<lambda_123407a5e2ac06da108355a851863b7a>,<lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec>&,<lambda_ae55bdf541ad94d75914d381c370e64d>_>
                    (&local_5,(<lambda_123407a5e2ac06da108355a851863b7a> *)&local_10,param_2,
                     (<lambda_ae55bdf541ad94d75914d381c370e64d> *)&local_c);
  return iVar1;
}



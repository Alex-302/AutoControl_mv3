// __acrt_lock_and_call<<lambda_a463b7b0560cfcaf9b17f27c6ef46564>_> @ 004695ab size=40 callers=1

/* Library Function - Single Match
    int __cdecl __acrt_lock_and_call<class <lambda_a463b7b0560cfcaf9b17f27c6ef46564> >(enum
   __acrt_lock_id,class <lambda_a463b7b0560cfcaf9b17f27c6ef46564> &&)
   
   Library: Visual Studio 2015 Release */

int __cdecl
__acrt_lock_and_call<<lambda_a463b7b0560cfcaf9b17f27c6ef46564>_>
          (__acrt_lock_id param_1,<lambda_a463b7b0560cfcaf9b17f27c6ef46564> *param_2)

{
  int iVar1;
  __acrt_lock_id local_10;
  __acrt_lock_id local_c;
  __crt_seh_guarded_call<int> local_5;
  
  local_c = param_1;
  local_10 = param_1;
  iVar1 = __crt_seh_guarded_call<int>::
          operator()<<lambda_9227be29367c048ad7fd93a717dcb1a1>,<lambda_a463b7b0560cfcaf9b17f27c6ef46564>&,<lambda_ccea11b5727ccf69be64f5f5d9a08d9f>_>
                    (&local_5,(<lambda_9227be29367c048ad7fd93a717dcb1a1> *)&local_10,param_2,
                     (<lambda_ccea11b5727ccf69be64f5f5d9a08d9f> *)&local_c);
  return iVar1;
}



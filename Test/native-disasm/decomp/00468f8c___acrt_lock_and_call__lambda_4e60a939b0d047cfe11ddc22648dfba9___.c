// __acrt_lock_and_call<<lambda_4e60a939b0d047cfe11ddc22648dfba9>_> @ 00468f8c size=40 callers=1

/* Library Function - Single Match
    int __cdecl __acrt_lock_and_call<class <lambda_4e60a939b0d047cfe11ddc22648dfba9> >(enum
   __acrt_lock_id,class <lambda_4e60a939b0d047cfe11ddc22648dfba9> &&)
   
   Library: Visual Studio 2015 Release */

int __cdecl
__acrt_lock_and_call<<lambda_4e60a939b0d047cfe11ddc22648dfba9>_>
          (__acrt_lock_id param_1,<lambda_4e60a939b0d047cfe11ddc22648dfba9> *param_2)

{
  int iVar1;
  __acrt_lock_id local_10;
  __acrt_lock_id local_c;
  __crt_seh_guarded_call<int> local_5;
  
  local_c = param_1;
  local_10 = param_1;
  iVar1 = __crt_seh_guarded_call<int>::
          operator()<<lambda_800076c951b434888f4765a74a194fcc>,<lambda_4e60a939b0d047cfe11ddc22648dfba9>&,<lambda_6dbb1268764f43b569ce7b67e331d33a>_>
                    (&local_5,(<lambda_800076c951b434888f4765a74a194fcc> *)&local_10,param_2,
                     (<lambda_6dbb1268764f43b569ce7b67e331d33a> *)&local_c);
  return iVar1;
}



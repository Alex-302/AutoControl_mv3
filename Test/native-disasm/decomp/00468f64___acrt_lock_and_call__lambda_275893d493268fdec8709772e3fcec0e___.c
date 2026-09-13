// __acrt_lock_and_call<<lambda_275893d493268fdec8709772e3fcec0e>_> @ 00468f64 size=40 callers=1

/* Library Function - Single Match
    int __cdecl __acrt_lock_and_call<class <lambda_275893d493268fdec8709772e3fcec0e> >(enum
   __acrt_lock_id,class <lambda_275893d493268fdec8709772e3fcec0e> &&)
   
   Library: Visual Studio 2015 Release */

int __cdecl
__acrt_lock_and_call<<lambda_275893d493268fdec8709772e3fcec0e>_>
          (__acrt_lock_id param_1,<lambda_275893d493268fdec8709772e3fcec0e> *param_2)

{
  int iVar1;
  __acrt_lock_id local_10;
  __acrt_lock_id local_c;
  __crt_seh_guarded_call<int> local_5;
  
  local_c = param_1;
  local_10 = param_1;
  iVar1 = __crt_seh_guarded_call<int>::
          operator()<<lambda_995298e7d72eb4c2aab26c0585b3abe5>,<lambda_275893d493268fdec8709772e3fcec0e>&,<lambda_293819299cbf9a7022e18b56a874bb5c>_>
                    (&local_5,(<lambda_995298e7d72eb4c2aab26c0585b3abe5> *)&local_10,param_2,
                     (<lambda_293819299cbf9a7022e18b56a874bb5c> *)&local_c);
  return iVar1;
}



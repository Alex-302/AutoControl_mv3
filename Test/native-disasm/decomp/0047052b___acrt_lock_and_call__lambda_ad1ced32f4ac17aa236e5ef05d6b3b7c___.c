// __acrt_lock_and_call<<lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c>_> @ 0047052b size=40 callers=1

/* Library Function - Single Match
    void __cdecl __acrt_lock_and_call<class <lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c> >(enum
   __acrt_lock_id,class <lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c> &&)
   
   Library: Visual Studio 2015 Release */

void __cdecl
__acrt_lock_and_call<<lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c>_>
          (__acrt_lock_id param_1,<lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c> *param_2)

{
  __acrt_lock_id local_10;
  __acrt_lock_id local_c;
  __crt_seh_guarded_call<void> local_5;
  
  local_c = param_1;
  local_10 = param_1;
  __crt_seh_guarded_call<void>::
  operator()<<lambda_978dc153c237d78434369da87b74ff60>,<lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c>&,<lambda_4a8533e2866a575feecb8298ce776b0d>_>
            (&local_5,(<lambda_978dc153c237d78434369da87b74ff60> *)&local_10,param_2,
             (<lambda_4a8533e2866a575feecb8298ce776b0d> *)&local_c);
  return;
}



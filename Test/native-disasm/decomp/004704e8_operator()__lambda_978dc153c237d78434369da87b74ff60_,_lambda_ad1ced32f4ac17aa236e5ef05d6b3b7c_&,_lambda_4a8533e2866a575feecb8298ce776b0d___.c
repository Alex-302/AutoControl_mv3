// operator()<<lambda_978dc153c237d78434369da87b74ff60>,<lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c>&,<lambda_4a8533e2866a575feecb8298ce776b0d>_> @ 004704e8 size=55 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    public: void __thiscall __crt_seh_guarded_call<void>::operator()<class
   <lambda_978dc153c237d78434369da87b74ff60>,class <lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c> &,class
   <lambda_4a8533e2866a575feecb8298ce776b0d> >(class <lambda_978dc153c237d78434369da87b74ff60>
   &&,class <lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c> &,class
   <lambda_4a8533e2866a575feecb8298ce776b0d> &&)
   
   Library: Visual Studio 2015 Release */

void __thiscall
__crt_seh_guarded_call<void>::
operator()<<lambda_978dc153c237d78434369da87b74ff60>,<lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c>&,<lambda_4a8533e2866a575feecb8298ce776b0d>_>
          (__crt_seh_guarded_call<void> *this,<lambda_978dc153c237d78434369da87b74ff60> *param_1,
          <lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c> *param_2,
          <lambda_4a8533e2866a575feecb8298ce776b0d> *param_3)

{
  ___acrt_lock(*(int *)param_1);
  <lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c>::operator()(param_2);
  FUN_0047051f();
  return;
}



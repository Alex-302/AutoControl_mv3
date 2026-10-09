// operator()<<lambda_d92cfe8357b99225085016881b624cb0>,<lambda_b721fa326cdb32351d23dfa67958c160>&,<lambda_42d75b0848218ec137fa420c8ba9fdf9>_> @ 00465750 size=66 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    public: int __thiscall __crt_seh_guarded_call<int>::operator()<class
   <lambda_d92cfe8357b99225085016881b624cb0>,class <lambda_b721fa326cdb32351d23dfa67958c160> &,class
   <lambda_42d75b0848218ec137fa420c8ba9fdf9> >(class <lambda_d92cfe8357b99225085016881b624cb0>
   &&,class <lambda_b721fa326cdb32351d23dfa67958c160> &,class
   <lambda_42d75b0848218ec137fa420c8ba9fdf9> &&)
   
   Library: Visual Studio 2015 Release */

int __thiscall
__crt_seh_guarded_call<int>::
operator()<<lambda_d92cfe8357b99225085016881b624cb0>,<lambda_b721fa326cdb32351d23dfa67958c160>&,<lambda_42d75b0848218ec137fa420c8ba9fdf9>_>
          (__crt_seh_guarded_call<int> *this,<lambda_d92cfe8357b99225085016881b624cb0> *param_1,
          <lambda_b721fa326cdb32351d23dfa67958c160> *param_2,
          <lambda_42d75b0848218ec137fa420c8ba9fdf9> *param_3)

{
  int iVar1;
  
  __lock_file(*(FILE **)param_1);
  iVar1 = <lambda_b721fa326cdb32351d23dfa67958c160>::operator()(param_2);
  FUN_00465795();
  return iVar1;
}



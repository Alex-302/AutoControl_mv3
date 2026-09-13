// operator()<> @ 00467ca3 size=55 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Multiple Matches With Same Base Name
    public: void __thiscall __crt_seh_guarded_call<void>::operator()<class
   <lambda_4fdada1b837b2abbf20876fac97688ad>,class <lambda_b57350f2640456a0859d250846f69caf> &,class
   <lambda_eed5e4f92b5b7d55fa22c48c484aaa54> >(class <lambda_4fdada1b837b2abbf20876fac97688ad>
   &&,class <lambda_b57350f2640456a0859d250846f69caf> &,class
   <lambda_eed5e4f92b5b7d55fa22c48c484aaa54> &&)
    public: void __thiscall __crt_seh_guarded_call<void>::operator()<class
   <lambda_c76fdea48760d5f9368b465f31df4405>,class <lambda_e378711a6f6581bf7f0efd7cdf97f5d9> &,class
   <lambda_e927a58b2a85c081d733e8c6192ae2d2> >(class <lambda_c76fdea48760d5f9368b465f31df4405>
   &&,class <lambda_e378711a6f6581bf7f0efd7cdf97f5d9> &,class
   <lambda_e927a58b2a85c081d733e8c6192ae2d2> &&)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

void operator()<>(int *param_1,undefined4 *param_2)

{
  ___acrt_lock(*param_1);
  FID_conflict_operator__(param_2);
  FUN_00467cda();
  return;
}



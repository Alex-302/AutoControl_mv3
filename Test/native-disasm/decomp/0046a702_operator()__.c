// operator()<> @ 0046a702 size=68 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Multiple Matches With Same Base Name
    public: void __thiscall __crt_seh_guarded_call<void>::operator()<class
   <lambda_3518db117f0e7cdb002338c5d3c47b6c>,class <lambda_b2ea41f6bbb362cd97d94c6828d90b61> &,class
   <lambda_abdedf541bb04549bc734292b4a045d4> >(class <lambda_3518db117f0e7cdb002338c5d3c47b6c>
   &&,class <lambda_b2ea41f6bbb362cd97d94c6828d90b61> &,class
   <lambda_abdedf541bb04549bc734292b4a045d4> &&)
    public: void __thiscall __crt_seh_guarded_call<void>::operator()<class
   <lambda_a7e850c220f1c8d1e6efeecdedd162c6>,class <lambda_46720907175c18b6c9d2717bc0d2d362> &,class
   <lambda_9048902d66e8d99359bc9897bbb930a8> >(class <lambda_a7e850c220f1c8d1e6efeecdedd162c6>
   &&,class <lambda_46720907175c18b6c9d2717bc0d2d362> &,class
   <lambda_9048902d66e8d99359bc9897bbb930a8> &&)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

void operator()<>(int *param_1,undefined4 *param_2)

{
  ___acrt_lock(*param_1);
  replace_current_thread_locale_nolock
            (*(__acrt_ptd **)*param_2,(__crt_locale_data *)**(undefined4 **)param_2[1]);
  FUN_0046a746();
  return;
}



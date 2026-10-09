// operator()<<lambda_800076c951b434888f4765a74a194fcc>,<lambda_4e60a939b0d047cfe11ddc22648dfba9>&,<lambda_6dbb1268764f43b569ce7b67e331d33a>_> @ 00468ec2 size=66 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    public: int __thiscall __crt_seh_guarded_call<int>::operator()<class
   <lambda_800076c951b434888f4765a74a194fcc>,class <lambda_4e60a939b0d047cfe11ddc22648dfba9> &,class
   <lambda_6dbb1268764f43b569ce7b67e331d33a> >(class <lambda_800076c951b434888f4765a74a194fcc>
   &&,class <lambda_4e60a939b0d047cfe11ddc22648dfba9> &,class
   <lambda_6dbb1268764f43b569ce7b67e331d33a> &&)
   
   Library: Visual Studio 2015 Release */

int __thiscall
__crt_seh_guarded_call<int>::
operator()<<lambda_800076c951b434888f4765a74a194fcc>,<lambda_4e60a939b0d047cfe11ddc22648dfba9>&,<lambda_6dbb1268764f43b569ce7b67e331d33a>_>
          (__crt_seh_guarded_call<int> *this,<lambda_800076c951b434888f4765a74a194fcc> *param_1,
          <lambda_4e60a939b0d047cfe11ddc22648dfba9> *param_2,
          <lambda_6dbb1268764f43b569ce7b67e331d33a> *param_3)

{
  int iVar1;
  
  ___acrt_lock(*(int *)param_1);
  iVar1 = <lambda_4e60a939b0d047cfe11ddc22648dfba9>::operator()(param_2);
  FUN_00468f07();
  return iVar1;
}



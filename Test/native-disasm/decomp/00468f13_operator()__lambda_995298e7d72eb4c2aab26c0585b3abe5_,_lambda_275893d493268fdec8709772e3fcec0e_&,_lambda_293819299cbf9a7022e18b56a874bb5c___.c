// operator()<<lambda_995298e7d72eb4c2aab26c0585b3abe5>,<lambda_275893d493268fdec8709772e3fcec0e>&,<lambda_293819299cbf9a7022e18b56a874bb5c>_> @ 00468f13 size=66 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    public: int __thiscall __crt_seh_guarded_call<int>::operator()<class
   <lambda_995298e7d72eb4c2aab26c0585b3abe5>,class <lambda_275893d493268fdec8709772e3fcec0e> &,class
   <lambda_293819299cbf9a7022e18b56a874bb5c> >(class <lambda_995298e7d72eb4c2aab26c0585b3abe5>
   &&,class <lambda_275893d493268fdec8709772e3fcec0e> &,class
   <lambda_293819299cbf9a7022e18b56a874bb5c> &&)
   
   Library: Visual Studio 2015 Release */

int __thiscall
__crt_seh_guarded_call<int>::
operator()<<lambda_995298e7d72eb4c2aab26c0585b3abe5>,<lambda_275893d493268fdec8709772e3fcec0e>&,<lambda_293819299cbf9a7022e18b56a874bb5c>_>
          (__crt_seh_guarded_call<int> *this,<lambda_995298e7d72eb4c2aab26c0585b3abe5> *param_1,
          <lambda_275893d493268fdec8709772e3fcec0e> *param_2,
          <lambda_293819299cbf9a7022e18b56a874bb5c> *param_3)

{
  int iVar1;
  
  ___acrt_lock(*(int *)param_1);
  iVar1 = <lambda_275893d493268fdec8709772e3fcec0e>::operator()(param_2);
  FUN_00468f58();
  return iVar1;
}



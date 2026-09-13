// operator()<> @ 0046dd0f size=75 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Multiple Matches With Same Base Name
    public: void (__cdecl*__thiscall __crt_seh_guarded_call<void (__cdecl*)(int)>::operator()<class
   <lambda_a048d3beccc847880fc8490e18b82769>,class <lambda_ec61778202f4f5fc7e7711acc23c3bca> &,class
   <lambda_f7496a158712204296dd6628a163878e> >(class <lambda_a048d3beccc847880fc8490e18b82769>
   &&,class <lambda_ec61778202f4f5fc7e7711acc23c3bca> &,class
   <lambda_f7496a158712204296dd6628a163878e> &&))(int)
    public: void (__cdecl*__thiscall __crt_seh_guarded_call<void (__cdecl*)(int)>::operator()<class
   <lambda_cbab9ec6f41b0180b23cc171c22676b0>,class <lambda_44731a7d0e6d81c3e6aa82d741081786> &,class
   <lambda_4b292cb8dd18144e164572427af410ab> >(class <lambda_cbab9ec6f41b0180b23cc171c22676b0>
   &&,class <lambda_44731a7d0e6d81c3e6aa82d741081786> &,class
   <lambda_4b292cb8dd18144e164572427af410ab> &&))(int)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

uint operator()<>(int *param_1)

{
  byte bVar1;
  uint uVar2;
  
  ___acrt_lock(*param_1);
  bVar1 = (byte)DAT_0049d070 & 0x1f;
  uVar2 = DAT_0049d070 ^ _DAT_0049fb18;
  FUN_0046dd5d();
  return uVar2 >> bVar1 | uVar2 << 0x20 - bVar1;
}



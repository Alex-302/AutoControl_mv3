// operator()<<lambda_9227be29367c048ad7fd93a717dcb1a1>,<lambda_a463b7b0560cfcaf9b17f27c6ef46564>&,<lambda_ccea11b5727ccf69be64f5f5d9a08d9f>_> @ 00469527 size=117 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    public: int __thiscall __crt_seh_guarded_call<int>::operator()<class
   <lambda_9227be29367c048ad7fd93a717dcb1a1>,class <lambda_a463b7b0560cfcaf9b17f27c6ef46564> &,class
   <lambda_ccea11b5727ccf69be64f5f5d9a08d9f> >(class <lambda_9227be29367c048ad7fd93a717dcb1a1>
   &&,class <lambda_a463b7b0560cfcaf9b17f27c6ef46564> &,class
   <lambda_ccea11b5727ccf69be64f5f5d9a08d9f> &&)
   
   Library: Visual Studio 2015 Release */

int __thiscall
__crt_seh_guarded_call<int>::
operator()<<lambda_9227be29367c048ad7fd93a717dcb1a1>,<lambda_a463b7b0560cfcaf9b17f27c6ef46564>&,<lambda_ccea11b5727ccf69be64f5f5d9a08d9f>_>
          (__crt_seh_guarded_call<int> *this,<lambda_9227be29367c048ad7fd93a717dcb1a1> *param_1,
          <lambda_a463b7b0560cfcaf9b17f27c6ef46564> *param_2,
          <lambda_ccea11b5727ccf69be64f5f5d9a08d9f> *param_3)

{
  byte bVar1;
  BOOL BVar2;
  
  ___acrt_lock(*(int *)param_1);
  _DAT_0049f8f0 = __crt_fast_encode_pointer<>(**(uint **)param_2);
  BVar2 = EnumSystemLocalesW(<lambda_5a01b672d24c8480ee9d6bdb50dd3881>::<helper_func_stdcall>,1);
  bVar1 = 0x20 - ((byte)DAT_0049d070 & 0x1f) & 0x1f;
  _DAT_0049f8f0 = (0U >> bVar1 | 0 << 0x20 - bVar1) ^ DAT_0049d070;
  FUN_0046959f();
  return BVar2;
}



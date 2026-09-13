// operator()<> @ 0046a7fe size=60 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Multiple Matches With Same Base Name
    public: void __thiscall __crt_seh_guarded_call<void>::operator()<class
   <lambda_15ade71b0218206bbe3333a0c9b79046>,class <lambda_da44e0f8b0f19ba52fefafb335991732> &,class
   <lambda_207f2d024fc103971653565357d6cd41> >(class <lambda_15ade71b0218206bbe3333a0c9b79046>
   &&,class <lambda_da44e0f8b0f19ba52fefafb335991732> &,class
   <lambda_207f2d024fc103971653565357d6cd41> &&)
    public: void __thiscall __crt_seh_guarded_call<void>::operator()<class
   <lambda_9df27f884b057bc3edfc946cb5b7cf47>,class <lambda_e69574bed617af4e071282c136b37893> &,class
   <lambda_cc0d902bcbbeb830f749456577db4721> >(class <lambda_9df27f884b057bc3edfc946cb5b7cf47>
   &&,class <lambda_e69574bed617af4e071282c136b37893> &,class
   <lambda_cc0d902bcbbeb830f749456577db4721> &&)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

void operator()<>(int *param_1,undefined4 *param_2)

{
  ___acrt_lock(*param_1);
  LOCK();
  **(int **)(*(int *)*param_2 + 0x48) = **(int **)(*(int *)*param_2 + 0x48) + 1;
  UNLOCK();
  FUN_0046a83a();
  return;
}



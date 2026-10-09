// operator()<> @ 0046a752 size=85 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Multiple Matches With Same Base Name
    public: void __thiscall __crt_seh_guarded_call<void>::operator()<class
   <lambda_38edbb1296d33220d7e4dd0ed76b244a>,class <lambda_5ce1d447e08cb34b2473517608e21441> &,class
   <lambda_fb385d3da700c9147fc39e65dd577a8c> >(class <lambda_38edbb1296d33220d7e4dd0ed76b244a>
   &&,class <lambda_5ce1d447e08cb34b2473517608e21441> &,class
   <lambda_fb385d3da700c9147fc39e65dd577a8c> &&)
    public: void __thiscall __crt_seh_guarded_call<void>::operator()<class
   <lambda_51b6e8b1eb166f2a3faf91f424b38130>,class <lambda_6250bd4b2a391816dd638c3bf72b0bcb> &,class
   <lambda_0b5a4a3e68152e1d9b943535f5f47bed> >(class <lambda_51b6e8b1eb166f2a3faf91f424b38130>
   &&,class <lambda_6250bd4b2a391816dd638c3bf72b0bcb> &,class
   <lambda_0b5a4a3e68152e1d9b943535f5f47bed> &&)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

void operator()<>(int *param_1,undefined4 *param_2)

{
  int iVar1;
  int *_Memory;
  
  ___acrt_lock(*param_1);
  _Memory = *(int **)(*(int *)*param_2 + 0x48);
  if (_Memory != (int *)0x0) {
    LOCK();
    iVar1 = *_Memory;
    *_Memory = iVar1 + -1;
    UNLOCK();
    if ((iVar1 + -1 == 0) && (_Memory != &DAT_0049d788)) {
      FID_conflict__free(_Memory);
    }
  }
  FUN_0046a7a7();
  return;
}



// construct_ptd @ 0046a8e6 size=121 callers=2

/* Library Function - Single Match
    void __cdecl construct_ptd(struct __acrt_ptd * const,struct __crt_locale_data * * const)
   
   Library: Visual Studio 2015 Release */

void __cdecl construct_ptd(__acrt_ptd *param_1,__crt_locale_data **param_2)

{
  __acrt_ptd **local_c;
  __acrt_ptd **local_8;
  
  *(undefined4 *)(param_1 + 0x18) = 1;
  *(undefined **)param_1 = &DAT_00485bb0;
  *(undefined4 *)(param_1 + 0x350) = 1;
  *(undefined4 **)(param_1 + 0x48) = &DAT_0049d788;
  *(undefined2 *)(param_1 + 0x6c) = 0x43;
  *(undefined2 *)(param_1 + 0x172) = 0x43;
  *(undefined4 *)(param_1 + 0x34c) = 0;
  local_8 = &param_1;
  __acrt_lock_and_call<<lambda_e69574bed617af4e071282c136b37893>_>
            (5,(<lambda_e69574bed617af4e071282c136b37893> *)&local_8);
  local_c = &param_1;
  local_8 = (__acrt_ptd **)&param_2;
  __acrt_lock_and_call<<lambda_b2ea41f6bbb362cd97d94c6828d90b61>_>
            (4,(<lambda_b2ea41f6bbb362cd97d94c6828d90b61> *)&local_c);
  return;
}



// destroy_ptd @ 0046a980 size=169 callers=1

/* Library Function - Single Match
    void __cdecl destroy_ptd(struct __acrt_ptd * const)
   
   Library: Visual Studio 2015 Release */

void __cdecl destroy_ptd(__acrt_ptd *param_1)

{
  __acrt_ptd **local_8;
  
  if (*(undefined **)param_1 != &DAT_00485bb0) {
    FID_conflict__free(*(undefined **)param_1);
  }
  FID_conflict__free(*(void **)(param_1 + 0x3c));
  FID_conflict__free(*(void **)(param_1 + 0x30));
  FID_conflict__free(*(void **)(param_1 + 0x34));
  FID_conflict__free(*(void **)(param_1 + 0x38));
  FID_conflict__free(*(void **)(param_1 + 0x28));
  FID_conflict__free(*(void **)(param_1 + 0x2c));
  FID_conflict__free(*(void **)(param_1 + 0x40));
  FID_conflict__free(*(void **)(param_1 + 0x44));
  FID_conflict__free(*(void **)(param_1 + 0x360));
  local_8 = &param_1;
  __acrt_lock_and_call<<lambda_6250bd4b2a391816dd638c3bf72b0bcb>_>
            (5,(<lambda_6250bd4b2a391816dd638c3bf72b0bcb> *)&local_8);
  local_8 = &param_1;
  __acrt_lock_and_call<<lambda_be2b3da3f62db62e9dad5dc70221a656>_>
            (4,(<lambda_be2b3da3f62db62e9dad5dc70221a656> *)&local_8);
  return;
}



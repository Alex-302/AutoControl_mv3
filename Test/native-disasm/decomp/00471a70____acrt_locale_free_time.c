// ___acrt_locale_free_time @ 00471a70 size=228 callers=2

/* Library Function - Single Match
    ___acrt_locale_free_time
   
   Library: Visual Studio 2015 Release */

void __cdecl ___acrt_locale_free_time(void **param_1)

{
  if (param_1 != (void **)0x0) {
    free_crt_array_internal(param_1,7);
    free_crt_array_internal(param_1 + 7,7);
    free_crt_array_internal(param_1 + 0xe,0xc);
    free_crt_array_internal(param_1 + 0x1a,0xc);
    free_crt_array_internal(param_1 + 0x26,2);
    FID_conflict__free(param_1[0x28]);
    FID_conflict__free(param_1[0x29]);
    FID_conflict__free(param_1[0x2a]);
    free_crt_array_internal(param_1 + 0x2d,7);
    free_crt_array_internal(param_1 + 0x34,7);
    free_crt_array_internal(param_1 + 0x3b,0xc);
    free_crt_array_internal(param_1 + 0x47,0xc);
    free_crt_array_internal(param_1 + 0x53,2);
    FID_conflict__free(param_1[0x55]);
    FID_conflict__free(param_1[0x56]);
    FID_conflict__free(param_1[0x57]);
    FID_conflict__free(param_1[0x58]);
  }
  return;
}



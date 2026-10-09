// ___acrt_lowio_destroy_handle_array @ 0045f511 size=53 callers=1

/* Library Function - Single Match
    ___acrt_lowio_destroy_handle_array
   
   Library: Visual Studio 2015 Release */

void __cdecl ___acrt_lowio_destroy_handle_array(LPCRITICAL_SECTION param_1)

{
  LPCRITICAL_SECTION lpCriticalSection;
  
  if (param_1 != (LPCRITICAL_SECTION)0x0) {
    for (lpCriticalSection = param_1; lpCriticalSection != param_1 + 0x80;
        lpCriticalSection = lpCriticalSection + 2) {
      DeleteCriticalSection(lpCriticalSection);
    }
    FID_conflict__free(param_1);
  }
  return;
}



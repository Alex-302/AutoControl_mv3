// ___acrt_allocate_buffer_for_argv @ 00467608 size=85 callers=2

/* Library Function - Single Match
    ___acrt_allocate_buffer_for_argv
   
   Library: Visual Studio 2015 Release */

LPVOID __cdecl ___acrt_allocate_buffer_for_argv(uint param_1,uint param_2,uint param_3)

{
  LPVOID pvVar1;
  
  if ((param_1 < 0x3fffffff) && (param_2 < (uint)(0xffffffff / (ulonglong)param_3))) {
    if (param_2 * param_3 < param_1 * -4 - 1) {
      pvVar1 = __calloc_base(param_2 * param_3 + param_1 * 4,1);
      FID_conflict__free((void *)0x0);
      return pvVar1;
    }
  }
  return (LPVOID)0x0;
}



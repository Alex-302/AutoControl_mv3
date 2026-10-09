// ___acrt_locale_initialize_time @ 00471b54 size=127 callers=1

/* Library Function - Single Match
    ___acrt_locale_initialize_time
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___acrt_locale_initialize_time(__crt_locale_data *param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined **_Memory;
  
  if (*(int *)(param_1 + 0xb4) == 0) {
    _Memory = &PTR_DAT_00486728;
LAB_00471bbb:
    ___acrt_locale_release_lc_time_reference(*(undefined ***)(param_1 + 0x9c));
    *(undefined ***)(param_1 + 0x9c) = _Memory;
    uVar2 = 0;
  }
  else {
    _Memory = __calloc_base(1,0x164);
    if ((__crt_lc_time_data *)_Memory == (__crt_lc_time_data *)0x0) {
      FID_conflict__free((void *)0x0);
    }
    else {
      bVar1 = initialize_lc_time((__crt_lc_time_data *)_Memory,param_1);
      if (bVar1) {
        *(undefined4 *)((int)_Memory + 0xb0) = 1;
        FID_conflict__free((void *)0x0);
        goto LAB_00471bbb;
      }
      ___acrt_locale_free_time(_Memory);
      FID_conflict__free(_Memory);
    }
    uVar2 = 1;
  }
  return uVar2;
}



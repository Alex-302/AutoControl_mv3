// ___acrt_stdio_allocate_buffer_nolock @ 00473ee7 size=93 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    ___acrt_stdio_allocate_buffer_nolock
   
   Library: Visual Studio 2015 Release */

void __cdecl ___acrt_stdio_allocate_buffer_nolock(undefined4 *param_1)

{
  uint *puVar1;
  LPVOID pvVar2;
  
  _DAT_0049f560 = _DAT_0049f560 + 1;
  pvVar2 = __malloc_base(0x1000);
  param_1[1] = pvVar2;
  FID_conflict__free((void *)0x0);
  puVar1 = param_1 + 3;
  if (param_1[1] == 0) {
    LOCK();
    *puVar1 = *puVar1 | 0x400;
    UNLOCK();
    param_1[6] = 2;
    param_1[1] = param_1 + 5;
  }
  else {
    LOCK();
    *puVar1 = *puVar1 | 0x40;
    UNLOCK();
    param_1[6] = 0x1000;
  }
  param_1[2] = 0;
  *param_1 = param_1[1];
  return;
}



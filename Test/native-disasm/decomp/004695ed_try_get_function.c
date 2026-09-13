// try_get_function @ 004695ed size=156 callers=14

/* Library Function - Single Match
    void * __cdecl try_get_function(enum `anonymous namespace'::function_id,char const * const,enum
   A0x9b56aee1::module_id const * const,enum A0x9b56aee1::module_id const * const)
   
   Library: Visual Studio 2015 Release */

void * __cdecl
try_get_function(function_id param_1,char *param_2,module_id *param_3,module_id *param_4)

{
  uint *puVar1;
  HMODULE hModule;
  FARPROC pFVar2;
  byte bVar3;
  void *pvVar4;
  
  puVar1 = &DAT_0049f870 + param_1;
  bVar3 = (byte)DAT_0049d070 & 0x1f;
  pvVar4 = (void *)((DAT_0049d070 ^ *puVar1) >> bVar3 | (DAT_0049d070 ^ *puVar1) << 0x20 - bVar3);
  if (pvVar4 != (void *)0xffffffff) {
    if (pvVar4 != (void *)0x0) {
      return pvVar4;
    }
    for (; param_3 != param_4; param_3 = param_3 + 1) {
      hModule = try_get_module(*param_3);
      if (hModule != (HMODULE)0x0) goto LAB_00469645;
    }
    hModule = (HMODULE)0x0;
LAB_00469645:
    if ((hModule != (HMODULE)0x0) &&
       (pFVar2 = GetProcAddress(hModule,param_2), pFVar2 != (FARPROC)0x0)) {
      pvVar4 = __crt_fast_encode_pointer<void*>(pFVar2);
      LOCK();
      *puVar1 = (uint)pvVar4;
      UNLOCK();
      return pFVar2;
    }
    bVar3 = 0x20 - ((byte)DAT_0049d070 & 0x1f) & 0x1f;
    LOCK();
    *puVar1 = (0xffffffffU >> bVar3 | -1 << 0x20 - bVar3) ^ DAT_0049d070;
    UNLOCK();
  }
  return (void *)0x0;
}



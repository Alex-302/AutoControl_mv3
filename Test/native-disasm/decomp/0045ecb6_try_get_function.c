// try_get_function @ 0045ecb6 size=160 callers=5

/* Library Function - Single Match
    void * __cdecl try_get_function(enum `anonymous namespace'::function_id,char const * const,enum
   A0x89697e75::module_id const * const,enum A0x89697e75::module_id const * const)
   
   Library: Visual Studio 2015 Release */

void * __cdecl
try_get_function(function_id param_1,char *param_2,module_id *param_3,module_id *param_4)

{
  uint *puVar1;
  uint uVar2;
  HMODULE hModule;
  FARPROC pFVar3;
  byte bVar4;
  void *pvVar5;
  
  puVar1 = &DAT_0049f4b0 + param_1;
  LOCK();
  uVar2 = *puVar1;
  if (uVar2 == 0) {
    *puVar1 = 0;
    uVar2 = 0;
  }
  UNLOCK();
  bVar4 = (byte)DAT_0049d070 & 0x1f;
  pvVar5 = (void *)((DAT_0049d070 ^ uVar2) >> bVar4 | (DAT_0049d070 ^ uVar2) << 0x20 - bVar4);
  if (pvVar5 != (void *)0xffffffff) {
    if (pvVar5 != (void *)0x0) {
      return pvVar5;
    }
    for (; param_3 != param_4; param_3 = param_3 + 1) {
      hModule = try_get_module(*param_3);
      if (hModule != (HINSTANCE__ *)0x0) goto LAB_0045ed12;
    }
    hModule = (HMODULE)0x0;
LAB_0045ed12:
    if ((hModule != (HMODULE)0x0) &&
       (pFVar3 = GetProcAddress(hModule,param_2), pFVar3 != (FARPROC)0x0)) {
      pvVar5 = __crt_fast_encode_pointer<void*>(pFVar3);
      LOCK();
      *puVar1 = (uint)pvVar5;
      UNLOCK();
      return pFVar3;
    }
    bVar4 = 0x20 - ((byte)DAT_0049d070 & 0x1f) & 0x1f;
    LOCK();
    *puVar1 = (0xffffffffU >> bVar4 | -1 << 0x20 - bVar4) ^ DAT_0049d070;
    UNLOCK();
  }
  return (void *)0x0;
}



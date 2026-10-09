// free_environment<> @ 004677c1 size=47 callers=5

/* Library Function - Multiple Matches With Same Base Name
    void __cdecl free_environment<char>(char * * const)
    void __cdecl free_environment<wchar_t>(wchar_t * * const)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

void __cdecl free_environment<>(undefined4 *param_1)

{
  void *_Memory;
  undefined4 *puVar1;
  
  if (param_1 != (undefined4 *)0x0) {
    _Memory = (void *)*param_1;
    puVar1 = param_1;
    while (_Memory != (void *)0x0) {
      FID_conflict__free(_Memory);
      puVar1 = puVar1 + 1;
      _Memory = (void *)*puVar1;
    }
    FID_conflict__free(param_1);
  }
  return;
}



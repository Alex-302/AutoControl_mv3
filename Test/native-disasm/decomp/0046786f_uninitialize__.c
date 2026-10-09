// uninitialize<> @ 0046786f size=64 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Multiple Matches With Same Base Name
    public: void __thiscall __crt_state_management::dual_state_global<char * *>::uninitialize<void
   (__cdecl&)(char * * &)>(void (__cdecl&)(char * * &))
    public: void __thiscall __crt_state_management::dual_state_global<wchar_t *
   *>::uninitialize<void (__cdecl&)(wchar_t * * &)>(void (__cdecl&)(wchar_t * * &))
   
   Libraries: Visual Studio 2015 Debug, Visual Studio 2015 Release */

void __thiscall uninitialize<>(void *this,undefined *param_1)

{
  void *pvVar1;
  
  pvVar1 = (void *)((int)this + 4);
  for (; this != pvVar1; this = (void *)((int)this + 4)) {
    (*(code *)PTR_guard_check_icall_004805b0)(this);
    (*(code *)param_1)();
  }
  return;
}



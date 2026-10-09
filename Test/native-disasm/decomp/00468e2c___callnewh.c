// __callnewh @ 00468e2c size=68 callers=4

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __callnewh
   
   Library: Visual Studio 2015 Release */

int __cdecl __callnewh(size_t _Size)

{
  code *pcVar1;
  int iVar2;
  
  pcVar1 = (code *)__query_new_handler();
  if (pcVar1 != (code *)0x0) {
    (*(code *)PTR_guard_check_icall_004805b0)(_Size);
    iVar2 = (*pcVar1)();
    if (iVar2 != 0) {
      return 1;
    }
  }
  return 0;
}



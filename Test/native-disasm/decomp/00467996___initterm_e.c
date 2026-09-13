// __initterm_e @ 00467996 size=69 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __initterm_e
   
   Library: Visual Studio 2015 Release */

int __cdecl __initterm_e(undefined4 *param_1,undefined4 *param_2)

{
  code *pcVar1;
  int iVar2;
  
  do {
    if (param_1 == param_2) {
      return 0;
    }
    pcVar1 = (code *)*param_1;
    if (pcVar1 != (code *)0x0) {
      (*(code *)PTR_guard_check_icall_004805b0)();
      iVar2 = (*pcVar1)();
      if (iVar2 != 0) {
        return iVar2;
      }
    }
    param_1 = param_1 + 1;
  } while( true );
}



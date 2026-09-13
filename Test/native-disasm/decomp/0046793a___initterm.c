// __initterm @ 0046793a size=92 callers=3

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __initterm
   
   Library: Visual Studio 2015 Release */

void __cdecl __initterm(undefined4 *param_1,undefined4 *param_2)

{
  code *pcVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  uVar2 = ~-(uint)(param_2 < param_1) & (uint)((int)param_2 + (3 - (int)param_1)) >> 2;
  if (uVar2 != 0) {
    do {
      pcVar1 = (code *)*param_1;
      if (pcVar1 != (code *)0x0) {
        (*(code *)PTR_guard_check_icall_004805b0)();
        (*pcVar1)();
      }
      param_1 = param_1 + 1;
      uVar3 = uVar3 + 1;
    } while (uVar3 != uVar2);
  }
  return;
}



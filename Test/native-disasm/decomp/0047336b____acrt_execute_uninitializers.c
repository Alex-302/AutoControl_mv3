// ___acrt_execute_uninitializers @ 0047336b size=77 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_execute_uninitializers
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___acrt_execute_uninitializers(undefined4 *param_1,undefined4 *param_2)

{
  code *pcVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)(DAT_0049d070 ^ (uint)&stack0xfffffffc);
  if (param_1 != param_2) {
    puVar3 = param_2 + -1;
    do {
      pcVar1 = (code *)*puVar3;
      if (pcVar1 != (code *)0x0) {
        (*(code *)PTR_guard_check_icall_004805b0)(0);
        (*pcVar1)();
      }
      puVar2 = puVar3 + -1;
      puVar3 = puVar3 + -2;
    } while (puVar2 != param_1);
  }
  return CONCAT31((int3)((uint)puVar2 >> 8),1);
}



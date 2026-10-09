// ___acrt_execute_initializers @ 004732e8 size=131 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_execute_initializers
   
   Library: Visual Studio 2015 Release */

uint __cdecl ___acrt_execute_initializers(undefined4 *param_1,undefined4 *param_2)

{
  code *pcVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  puVar2 = (undefined4 *)(DAT_0049d070 ^ (uint)&stack0xfffffffc);
  puVar4 = param_1;
  if (param_1 == param_2) {
    uVar3 = CONCAT31((int3)((uint)puVar2 >> 8),1);
  }
  else {
    do {
      pcVar1 = (code *)*puVar4;
      if (pcVar1 != (code *)0x0) {
        (*(code *)PTR_guard_check_icall_004805b0)();
        puVar2 = (undefined4 *)(*pcVar1)();
        if ((char)puVar2 == '\0') break;
      }
      puVar4 = puVar4 + 2;
    } while (puVar4 != param_2);
    if (puVar4 == param_2) {
      uVar3 = CONCAT31((int3)((uint)puVar2 >> 8),1);
    }
    else {
      if (puVar4 != param_1) {
        puVar4 = puVar4 + -1;
        do {
          if ((puVar4[-1] != 0) && (pcVar1 = (code *)*puVar4, pcVar1 != (code *)0x0)) {
            (*(code *)PTR_guard_check_icall_004805b0)(0);
            (*pcVar1)();
          }
          puVar2 = puVar4 + -1;
          puVar4 = puVar4 + -2;
        } while (puVar2 != param_1);
      }
      uVar3 = (uint)puVar2 & 0xffffff00;
    }
  }
  return uVar3;
}



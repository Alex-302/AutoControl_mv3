// __Deletegloballocale @ 00458bf7 size=57 callers=1

/* Library Function - Single Match
    __Deletegloballocale
   
   Library: Visual Studio 2015 Release */

void __cdecl __Deletegloballocale(int *param_1)

{
  code *pcVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  if ((int *)*param_1 != (int *)0x0) {
    pcVar1 = *(code **)(*(int *)*param_1 + 8);
    guard_check_icall();
    puVar2 = (undefined4 *)(*pcVar1)();
    if (puVar2 != (undefined4 *)0x0) {
      uVar3 = 1;
      pcVar1 = *(code **)*puVar2;
      guard_check_icall();
      (*pcVar1)(uVar3);
    }
  }
  return;
}



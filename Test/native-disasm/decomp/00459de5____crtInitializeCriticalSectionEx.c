// ___crtInitializeCriticalSectionEx @ 00459de5 size=56 callers=1

/* Library Function - Single Match
    ___crtInitializeCriticalSectionEx
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl
___crtInitializeCriticalSectionEx(LPCRITICAL_SECTION param_1,DWORD param_2,undefined4 param_3)

{
  undefined4 uVar1;
  code *pcVar2;
  
  pcVar2 = (code *)(DAT_0049f000 ^ DAT_0049d070);
  if (pcVar2 == (code *)0x0) {
    InitializeCriticalSectionAndSpinCount(param_1,param_2);
    uVar1 = 1;
  }
  else {
    guard_check_icall();
    uVar1 = (*pcVar2)(param_1,param_2,param_3);
  }
  return uVar1;
}



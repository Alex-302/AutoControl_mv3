// __setfpcontrolword @ 0046a28f size=128 callers=1

/* Library Function - Single Match
    __setfpcontrolword
   
   Library: Visual Studio 2015 Release */

void __cdecl __setfpcontrolword(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  ___get_machine_control(799);
  ___get_machine_control(param_1);
  uVar1 = MXCSR;
  if (0 < DAT_0049f178) {
    uVar2 = ___get_machine_control_sse2(799);
    MXCSR = ___get_machine_control_sse2(param_1);
    MXCSR = ~uVar2 & uVar1 | MXCSR;
  }
  return;
}



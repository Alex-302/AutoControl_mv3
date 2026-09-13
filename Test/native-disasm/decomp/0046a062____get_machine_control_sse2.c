// ___get_machine_control_sse2 @ 0046a062 size=128 callers=2

/* Library Function - Single Match
    ___get_machine_control_sse2
   
   Library: Visual Studio 2015 Release */

uint __cdecl ___get_machine_control_sse2(uint param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((param_1 & 799) != 0) {
    if ((param_1 & 0x10) != 0) {
      uVar1 = 0x80;
    }
    if ((param_1 & 8) != 0) {
      uVar1 = uVar1 | 0x200;
    }
    if ((param_1 & 4) != 0) {
      uVar1 = uVar1 | 0x400;
    }
    if ((param_1 & 2) != 0) {
      uVar1 = uVar1 | 0x800;
    }
    if ((param_1 & 1) != 0) {
      uVar1 = uVar1 | 0x1000;
    }
    if ((param_1 & 0x300) == 0x300) {
      uVar1 = uVar1 | 0x6000;
    }
    else if ((param_1 & 0x200) == 0) {
      if ((param_1 & 0x100) != 0) {
        uVar1 = uVar1 | 0x4000;
      }
    }
    else {
      uVar1 = uVar1 | 0x2000;
    }
  }
  return uVar1;
}



// ___get_abstract_control_sse2 @ 00469f01 size=125 callers=1

/* Library Function - Single Match
    ___get_abstract_control_sse2
   
   Library: Visual Studio 2015 Release */

uint __cdecl ___get_abstract_control_sse2(uint param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((param_1 & 0x7e80) != 0) {
    if ((char)param_1 < '\0') {
      uVar1 = 0x10;
    }
    if ((param_1 & 0x200) != 0) {
      uVar1 = uVar1 | 8;
    }
    if ((param_1 & 0x400) != 0) {
      uVar1 = uVar1 | 4;
    }
    if ((param_1 & 0x800) != 0) {
      uVar1 = uVar1 | 2;
    }
    if ((param_1 & 0x1000) != 0) {
      uVar1 = uVar1 | 1;
    }
    if ((param_1 & 0x6000) == 0x6000) {
      uVar1 = uVar1 | 0x300;
    }
    else if ((param_1 & 0x4000) == 0) {
      if ((param_1 & 0x2000) != 0) {
        uVar1 = uVar1 | 0x200;
      }
    }
    else {
      uVar1 = uVar1 | 0x100;
    }
  }
  return uVar1;
}



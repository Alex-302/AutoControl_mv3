// ___get_abstract_control_x87 @ 00469f7e size=115 callers=1

/* Library Function - Single Match
    ___get_abstract_control_x87
   
   Library: Visual Studio 2015 Release */

uint __cdecl ___get_abstract_control_x87(uint param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((param_1 & 0xc3d) != 0) {
    if ((param_1 & 1) != 0) {
      uVar1 = 0x10;
    }
    if ((param_1 & 4) != 0) {
      uVar1 = uVar1 | 8;
    }
    if ((param_1 & 8) != 0) {
      uVar1 = uVar1 | 4;
    }
    if ((param_1 & 0x10) != 0) {
      uVar1 = uVar1 | 2;
    }
    if ((param_1 & 0x20) != 0) {
      uVar1 = uVar1 | 1;
    }
    if ((param_1 & 0xc00) == 0xc00) {
      uVar1 = uVar1 | 0x300;
    }
    else if ((param_1 & 0x800) == 0) {
      if ((param_1 & 0x400) != 0) {
        uVar1 = uVar1 | 0x200;
      }
    }
    else {
      uVar1 = uVar1 | 0x100;
    }
  }
  return uVar1;
}



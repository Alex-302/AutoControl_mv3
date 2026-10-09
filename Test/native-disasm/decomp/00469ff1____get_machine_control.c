// ___get_machine_control @ 00469ff1 size=113 callers=2

/* Library Function - Single Match
    ___get_machine_control
   
   Library: Visual Studio 2015 Release */

uint __cdecl ___get_machine_control(uint param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((param_1 & 799) != 0) {
    uVar1 = (uint)((param_1 & 0x10) != 0);
    if ((param_1 & 8) != 0) {
      uVar1 = uVar1 | 4;
    }
    if ((param_1 & 4) != 0) {
      uVar1 = uVar1 | 8;
    }
    if ((param_1 & 2) != 0) {
      uVar1 = uVar1 | 0x10;
    }
    if ((param_1 & 1) != 0) {
      uVar1 = uVar1 | 0x20;
    }
    if ((param_1 & 0x300) == 0x300) {
      uVar1 = uVar1 | 0xc00;
    }
    else if ((param_1 & 0x200) == 0) {
      if ((param_1 & 0x100) != 0) {
        uVar1 = uVar1 | 0x800;
      }
    }
    else {
      uVar1 = uVar1 | 0x400;
    }
  }
  return uVar1;
}



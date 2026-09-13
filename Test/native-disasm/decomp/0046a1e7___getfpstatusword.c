// __getfpstatusword @ 0046a1e7 size=168 callers=1

/* Library Function - Single Match
    __getfpstatusword
   
   Library: Visual Studio 2015 Release */

uint __getfpstatusword(void)

{
  uint uVar1;
  uint uVar2;
  ushort in_FPUStatusWord;
  undefined4 local_c;
  
  uVar2 = 0;
  local_c = 0;
  if (0 < DAT_0049f178) {
    local_c = MXCSR;
  }
  uVar1 = 0;
  if ((in_FPUStatusWord & 0x3d) != 0) {
    if ((in_FPUStatusWord & 1) != 0) {
      uVar1 = 0x100010;
    }
    if ((in_FPUStatusWord & 4) != 0) {
      uVar1 = uVar1 | 0x80008;
    }
    if ((in_FPUStatusWord & 8) != 0) {
      uVar1 = uVar1 | 0x40004;
    }
    if ((in_FPUStatusWord & 0x10) != 0) {
      uVar1 = uVar1 | 0x20002;
    }
    if ((in_FPUStatusWord & 0x20) != 0) {
      uVar1 = uVar1 | 0x10001;
    }
  }
  if ((local_c & 0x3d) != 0) {
    if ((local_c & 1) != 0) {
      uVar2 = 0x10000010;
    }
    if ((local_c & 4) != 0) {
      uVar2 = uVar2 | 0x8000008;
    }
    if ((local_c & 8) != 0) {
      uVar2 = uVar2 | 0x4000004;
    }
    if ((local_c & 0x10) != 0) {
      uVar2 = uVar2 | 0x2000002;
    }
    if ((local_c & 0x20) != 0) {
      uVar2 = uVar2 | 0x1000001;
    }
  }
  return uVar1 | uVar2;
}



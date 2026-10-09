// __getfpcontrolword @ 0046a1a4 size=67 callers=2

/* Library Function - Single Match
    __getfpcontrolword
   
   Library: Visual Studio 2015 Release */

uint __getfpcontrolword(void)

{
  uint uVar1;
  uint uVar2;
  ushort in_FPUControlWord;
  undefined4 local_c;
  
  local_c = 0;
  if (0 < DAT_0049f178) {
    local_c = MXCSR;
  }
  uVar1 = ___get_abstract_control_x87((uint)in_FPUControlWord);
  uVar2 = ___get_abstract_control_sse2(local_c);
  return (uVar2 | uVar1) & 799;
}



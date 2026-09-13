// FUN_00476608 @ 00476608 size=197 callers=1

uint __cdecl FUN_00476608(int param_1,uint param_2)

{
  uint in_EAX;
  uint uVar1;
  uint extraout_EAX;
  bool in_ZF;
  ushort in_FPUControlWord;
  unkbyte10 in_ST0;
  undefined4 unaff_retaddr;
  
  if (in_ZF) {
    if (((in_EAX & 0xfffff) != 0) || (param_1 != 0)) {
      uVar1 = FUN_0046fa4c();
      goto LAB_004766a1;
    }
    uVar1 = 0;
    if ((in_EAX & 0x80000000) == 0) goto LAB_00476635;
  }
  else {
    if ((((param_2 & 0x7ff00000) == 0) && ((param_2 & 0xfffff) == 0)) && (param_1 == 0)) {
      uVar1 = 2;
      goto LAB_004766a1;
    }
    if ((param_2 & 0x80000000) == 0) {
      log2(in_ST0);
      uVar1 = param_2;
LAB_00476635:
      if (DAT_0049fb24 != 0) {
        return uVar1;
      }
      uVar1 = __math_exit("log10",0x1b,unaff_retaddr,param_1,param_2);
      return uVar1;
    }
  }
  uVar1 = 1;
LAB_004766a1:
  if (DAT_0049fb24 != 0) {
    return uVar1;
  }
  __startOneArgErrorHandling("log10",0x1b,in_FPUControlWord,unaff_retaddr,param_1,param_2);
  return extraout_EAX;
}



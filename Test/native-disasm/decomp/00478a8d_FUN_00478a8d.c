// FUN_00478a8d @ 00478a8d size=157 callers=1

uint __cdecl FUN_00478a8d(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint extraout_EAX;
  bool in_ZF;
  ushort in_FPUControlWord;
  undefined4 unaff_retaddr;
  
  if (in_ZF) {
    if (((param_2 & 0xfffff) != 0) || (param_1 != 0)) {
      uVar2 = FUN_0046fa4c();
      goto LAB_00478b0b;
    }
    uVar2 = 0;
    uVar1 = param_2 & 0x80000000;
joined_r0x00478afc:
    if (uVar1 == 0) {
LAB_00478aae:
      if (DAT_0049fb24 != 0) {
        return uVar2;
      }
      uVar2 = __math_exit(&DAT_00490cb0,5,unaff_retaddr,param_1,param_2);
      return uVar2;
    }
  }
  else {
    uVar2 = param_2;
    if (in_FPUControlWord != 0x27f) {
      uVar2 = FUN_0046fa35();
    }
    if ((uVar2 & 0x80000000) == 0) goto LAB_00478aae;
    if (((uVar2 & 0x7ff00000) == 0) && (uVar1 = param_1, (uVar2 & 0xfffff) == 0))
    goto joined_r0x00478afc;
  }
  uVar2 = 1;
LAB_00478b0b:
  if (DAT_0049fb24 != 0) {
    return uVar2;
  }
  __startOneArgErrorHandling(&DAT_00490cb0,5,in_FPUControlWord,unaff_retaddr,param_1,param_2);
  return extraout_EAX;
}



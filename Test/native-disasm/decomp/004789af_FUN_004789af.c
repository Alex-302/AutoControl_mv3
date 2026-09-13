// FUN_004789af @ 004789af size=183 callers=1

uint __thiscall FUN_004789af(void *this,int param_1,uint param_2)

{
  uint uVar1;
  uint extraout_EAX;
  undefined1 in_ZF;
  ushort in_FPUControlWord;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 fVar2;
  undefined4 unaff_retaddr;
  
  uVar1 = __fload_withFB(this,(int)&param_1);
  if ((bool)in_ZF) {
    if (((uVar1 & 0xfffff) == 0) && (param_1 == 0)) {
LAB_00478a3a:
      uVar1 = 1;
    }
    else {
      uVar1 = FUN_0046fa4c();
    }
    if (DAT_0049fb24 == 0) {
      __startOneArgErrorHandling(&DAT_0048f5a0,0xd,in_FPUControlWord,unaff_retaddr,param_1,param_2);
      return extraout_EAX;
    }
  }
  else {
    fVar2 = extraout_ST0;
    if (in_FPUControlWord != 0x27f) {
      uVar1 = FUN_0046fa35();
      fVar2 = extraout_ST0_00;
    }
    if (uVar1 < 0x3ff00000) {
      fpatan(SQRT(((float10)1 - fVar2) * ((float10)1 + fVar2)),fVar2);
    }
    else {
      if ((0x3ff00000 < uVar1) || ((param_2 & 0xfffff) != 0 || param_1 != 0)) goto LAB_00478a3a;
      uVar1 = 0;
    }
    if (DAT_0049fb24 == 0) {
      uVar1 = __math_exit(&DAT_0048f5a0,0xd,unaff_retaddr,param_1,param_2);
      return uVar1;
    }
  }
  return uVar1;
}



// FUN_00477d8d @ 00477d8d size=68 callers=11

void __fastcall FUN_00477d8d(undefined4 param_1,uint param_2)

{
  ushort in_FPUControlWord;
  undefined8 in_XMM0_Qa;
  
  if ((param_2 == 8) ||
     ((*(byte *)((int)&DAT_0048f378 + param_2 + 7) & (byte)in_FPUControlWord) == 0)) {
    __except1(param_2,0,in_XMM0_Qa,(double)in_XMM0_Qa,(uint)in_FPUControlWord);
  }
  return;
}



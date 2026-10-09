// __libm_sse2_sqrt_precise @ 004784e0 size=254 callers=3

/* Library Function - Single Match
    __libm_sse2_sqrt_precise
   
   Library: Visual Studio 2015 Release */

void __fastcall __libm_sse2_sqrt_precise(void *param_1)

{
  int iVar1;
  ushort in_FPUControlWord;
  short in_XMM0_Wa;
  short in_XMM0_Wb;
  short in_XMM0_Wc;
  ushort in_XMM0_Wd;
  
  if (((MXCSR & 0x7f80) != 0x1f80) || ((in_FPUControlWord & 0x7f) != 0x7f)) {
    FUN_00478a84(param_1,CONCAT22(in_XMM0_Wb,in_XMM0_Wa),CONCAT22(in_XMM0_Wd,in_XMM0_Wc));
    return;
  }
  if (((in_XMM0_Wd & 0x7ff0) == 0x7ff0) &&
     (((((in_XMM0_Wd & 0xf) != 0 || (in_XMM0_Wc != 0)) || (in_XMM0_Wb != 0)) || (in_XMM0_Wa != 0))))
  {
    iVar1 = 0x3f5;
  }
  else {
    if (((in_XMM0_Wd & 0x8000) == 0) ||
       (((CONCAT22(in_XMM0_Wb,in_XMM0_Wa) == 0 && (in_XMM0_Wd == 0x8000)) && (in_XMM0_Wc == 0)))) {
      return;
    }
    iVar1 = 0x31;
  }
  ___libm_error_support
            ((undefined8 *)&stack0xfffffff8,(undefined8 *)&stack0xfffffff8,
             (undefined8 *)&stack0xfffffff8,iVar1);
  return;
}



// ___set_fpsr_sse2 @ 0046d0b1 size=72 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___set_fpsr_sse2
   
   Library: Visual Studio 2015 Release */

void __cdecl ___set_fpsr_sse2(uint param_1)

{
  if (0 < DAT_0049f178) {
    if (((param_1 & 0x40) == 0) || (DAT_0049d2f4 == 0)) {
      MXCSR = param_1 & 0xffffffbf;
    }
    else {
      MXCSR = param_1;
    }
  }
  return;
}



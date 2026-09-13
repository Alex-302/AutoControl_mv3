// __acrt_fp_classify @ 0046bca2 size=108 callers=2

/* Library Function - Single Match
    enum __acrt_fp_class __cdecl __acrt_fp_classify(double const &)
   
   Library: Visual Studio 2015 Release */

__acrt_fp_class __cdecl __acrt_fp_classify(double *param_1)

{
  uint uVar1;
  undefined4 uStack_14;
  
  uVar1 = *(uint *)((int)param_1 + 4);
  if ((uVar1 >> 0x14 & 0x7ff) == 0x7ff) {
    if (*(int *)param_1 == 0 && (uVar1 & 0xfffff) == 0) {
      uStack_14 = 1;
    }
    else if ((((uVar1 & 0x80000000) == 0) || (*(int *)param_1 != 0)) ||
            ((uVar1 & 0xfffff) != 0x80000)) {
      if ((uVar1 & 0x80000) == 0) {
        uStack_14 = 3;
      }
      else {
        uStack_14 = 2;
      }
    }
    else {
      uStack_14 = 4;
    }
  }
  else {
    uStack_14 = 0;
  }
  return uStack_14;
}



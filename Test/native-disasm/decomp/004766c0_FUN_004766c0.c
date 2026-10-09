// FUN_004766c0 @ 004766c0 size=470 callers=4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl FUN_004766c0(double param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ushort in_FPUControlWord;
  float10 fVar4;
  double dVar5;
  longlong lVar6;
  
  if ((DAT_004a33e4 == 0) || ((MXCSR & 0x7f80) != 0x1f80 || (in_FPUControlWord & 0x7f) != 0x7f)) {
    uVar2 = __ctrlfp();
    if ((param_1._6_2_ & 0x7ff0) == 0x7ff0) {
      iVar3 = __sptype(SUB84(param_1,0),(uint)((ulonglong)param_1 >> 0x20));
      if (iVar3 - 1U < 3) {
        __ctrlfp();
        return (float10)param_1;
      }
      dVar5 = _DAT_004851a8 + param_1;
      uVar1 = 8;
    }
    else {
      fVar4 = FUN_00475826(param_1);
      dVar5 = (double)fVar4;
      if (((float10)param_1 == fVar4) || ((uVar2 & 0x20) != 0)) {
        __ctrlfp();
        return (float10)dVar5;
      }
      dVar5 = (double)fVar4;
      uVar1 = 0x10;
    }
    fVar4 = __except1(uVar1,0xc,param_1,dVar5,uVar2);
    return fVar4;
  }
  uVar2 = (uint)((ulonglong)param_1 >> 0x20);
  uVar1 = uVar2 >> 0x14;
  lVar6 = CONCAT44(_UNK_0048c144,_DAT_0048c140 - (uVar2 >> 0x14 & _DAT_0048c160));
  if ((uVar1 & 0x800) == 0) {
    dVar5 = (double)(((ulonglong)param_1 >> lVar6) << lVar6);
    if (uVar1 < 0x3ff) {
      return (float10)(double)(-(ulonglong)(_DAT_0048c150 < param_1) & _DAT_0048c130);
    }
    if (uVar1 < 0x433) {
      return (float10)(dVar5 + (double)(-(ulonglong)(dVar5 < param_1) & _DAT_0048c130));
    }
  }
  else {
    if (uVar1 < 0xbff) {
      return (float10)_DAT_0048c170;
    }
    if (uVar1 < 0xc33) {
      return (float10)(double)(((ulonglong)param_1 >> lVar6) << lVar6);
    }
  }
  if (NAN(param_1)) {
    ___libm_error_support(&param_1,&param_1,&param_1,0x3ec);
  }
  return (float10)param_1;
}



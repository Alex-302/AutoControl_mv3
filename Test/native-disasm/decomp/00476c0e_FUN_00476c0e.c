// FUN_00476c0e @ 00476c0e size=614 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl FUN_00476c0e(double param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  undefined1 in_XMM0 [16];
  double dVar8;
  double dVar9;
  double dVar10;
  double local_c;
  
  iVar4 = 0;
  while( true ) {
    uVar2 = (uint)(ushort)(in_XMM0._6_2_ >> 4);
    dVar6 = (double)(in_XMM0._0_8_ & (ulonglong)_DAT_0048c180 | (ulonglong)DAT_0048c1f0);
    dVar7 = (double)(in_XMM0._0_8_ & _UNK_0048c188 | _UNK_0048c1f8);
    uVar1 = SUB82(_DAT_0048c1a0 + dVar6,0) & 0x7f0;
    dVar10 = (double)(_UNK_0048c1b8 & (ulonglong)dVar7);
    dVar9 = (double)(_DAT_0048c1b0 & (ulonglong)dVar6) * *(double *)(&DAT_0048c690 + uVar1) -
            _DAT_0048c190;
    dVar6 = (dVar6 - (double)(_DAT_0048c1b0 & (ulonglong)dVar6)) *
            *(double *)(&DAT_0048c690 + uVar1);
    dVar8 = (dVar7 - dVar10) * *(double *)(&UNK_0048c698 + uVar1);
    dVar7 = dVar6 + dVar9;
    in_XMM0._8_8_ = dVar8 + (dVar10 * *(double *)(&UNK_0048c698 + uVar1) - _UNK_0048c198);
    uVar3 = uVar2 - 1;
    if (uVar3 < 0x7fe) {
      iVar4 = (uVar2 - 0x3ff) + iVar4;
      dVar10 = (double)iVar4;
      iVar5 = 0;
      if (uVar1 + iVar4 * 0x400 == 0) {
        iVar5 = 0x10;
      }
      return (float10)(((_UNK_0048c248 * in_XMM0._8_8_ + _UNK_0048c258) * in_XMM0._8_8_ +
                       _UNK_0048c268) * in_XMM0._8_8_ * in_XMM0._8_8_ +
                       ((_DAT_0048c240 * dVar7 + _DAT_0048c250) * dVar7 + _DAT_0048c260) *
                       dVar7 * dVar7 * dVar7 * dVar7 * dVar7 + _DAT_0048c270 * dVar7 +
                       *(double *)(&UNK_0048c288 + uVar1) + dVar10 * _UNK_0048c1c8 +
                       (double)((ulonglong)dVar8 & *(ulonglong *)(&UNK_0048c1d8 + iVar5)) +
                      *(double *)(&DAT_0048c280 + uVar1) + dVar9 + dVar10 * _DAT_0048c1c0 +
                      (double)((ulonglong)dVar6 & *(ulonglong *)(&DAT_0048c1d0 + iVar5)));
    }
    local_c = (double)-(ulonglong)(_DAT_0048c200 == param_1);
    if (SUB82(local_c,0) != 0) break;
    if (uVar3 != 0xffffffff) {
      if (uVar3 < 0x7ff) {
        if (DAT_0048c1f0 ==
            (double)((ulonglong)param_1 & (ulonglong)_DAT_0048c180 | (ulonglong)DAT_0048c1f0)) {
          return (float10)_DAT_0048c228;
        }
        iVar4 = 0x3e9;
        local_c = _DAT_0048c180;
      }
      else if (((uVar2 & 0x7ff) < 0x7ff) ||
              (SUB84(param_1,0) == 0 && ((ulonglong)param_1 & 0xfffff00000000) == 0)) {
        local_c = -NAN;
        iVar4 = 9;
      }
      else {
        iVar4 = 0x3e9;
      }
      goto LAB_00476e1a;
    }
    in_XMM0._0_8_ = param_1 * DAT_0048c210;
    iVar4 = -0x34;
  }
  iVar4 = 8;
  local_c = DAT_0048c220;
LAB_00476e1a:
  ___libm_error_support(&param_1,&param_1,&local_c,iVar4);
  return (float10)local_c;
}



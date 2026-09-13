// FUN_00477def @ 00477def size=271 callers=1

/* WARNING: Removing unreachable block (ram,0x00477c33) */
/* WARNING: Removing unreachable block (ram,0x00477e59) */
/* WARNING: Removing unreachable block (ram,0x00477c38) */
/* WARNING: Removing unreachable block (ram,0x00477c46) */
/* WARNING: Removing unreachable block (ram,0x00477c50) */
/* WARNING: Removing unreachable block (ram,0x00477c5a) */
/* WARNING: Removing unreachable block (ram,0x00477c6c) */
/* WARNING: Removing unreachable block (ram,0x00477c7f) */
/* WARNING: Removing unreachable block (ram,0x00477c8d) */
/* WARNING: Removing unreachable block (ram,0x00477c97) */
/* WARNING: Removing unreachable block (ram,0x00477ca7) */

ulonglong FUN_00477def(void)

{
  int iVar1;
  undefined4 extraout_ECX;
  int extraout_ECX_00;
  undefined4 extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  double in_XMM0_Qa;
  ulonglong in_XMM0_Qb;
  int iVar2;
  double dVar3;
  ulonglong uVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  double dVar7;
  undefined1 auVar8 [16];
  longlong lVar9;
  ulonglong uVar10;
  undefined1 auVar11 [16];
  
  iVar1 = 5;
  if (((uint)((ulonglong)in_XMM0_Qa >> 0x20) & 0x7fffffff) < 0x7ff00000) {
    auVar5._0_8_ = ABS(in_XMM0_Qa);
    auVar5._8_8_ = in_XMM0_Qb & 0x7fffffffffffffff;
    dVar3 = DAT_0048f358;
    if (DAT_0048f368 < auVar5._0_8_) {
      FUN_00477d8d(5,1);
      FUN_00477d8d(extraout_ECX,0x10);
      iVar1 = extraout_ECX_00;
    }
    if (DAT_0048f370 <= auVar5._0_8_) {
      dVar7 = in_XMM0_Qa;
      if ((iVar1 == 4) && (DAT_0048f358 <= in_XMM0_Qa)) {
        dVar7 = in_XMM0_Qa - DAT_0048f358;
      }
      if ((int)((ulonglong)((longlong)dVar7 << 0x23) >> 0x20) != 0) {
        FUN_00477d8d(iVar1,0x10);
        iVar1 = extraout_ECX_03;
      }
      if ((dVar3 <= in_XMM0_Qa) || (in_XMM0_Qa < DAT_0048f350)) goto LAB_00477d7b;
    }
    else if (auVar5._0_8_ != 0.0) {
      FUN_00477d8d(iVar1,2);
      FUN_00477d8d(extraout_ECX_01,0x10);
      iVar1 = extraout_ECX_02;
    }
    uVar4 = 0;
    dVar3 = auVar5._0_8_;
    if (dVar3 != 0.0) {
      auVar8._8_8_ = 0;
      auVar8._0_8_ = DAT_0048f330;
      auVar6._8_8_ = 0;
      auVar6._0_8_ = DAT_0048f338;
      auVar6 = auVar5 & auVar8 | auVar6;
      lVar9 = (ulonglong)DAT_0048f390 - ((ulonglong)dVar3 >> 0x34);
      uVar10 = auVar6._0_8_ >> lVar9;
      iVar2 = -(uint)((int)DAT_0048f390 < (int)(auVar5._4_4_ >> 0x14));
      uVar4 = CONCAT44(iVar2,iVar2);
      uVar4 = ~uVar4 & uVar10 |
              auVar6._0_8_ << ((ulonglong)dVar3 >> 0x34) - (ulonglong)DAT_0048f390 & uVar4;
      uVar4 = ~-(ulonglong)(in_XMM0_Qa == dVar3) & -uVar4 |
              uVar4 & -(ulonglong)(in_XMM0_Qa == dVar3);
      if ((0 < (int)lVar9) &&
         (auVar11._0_8_ = uVar10 << lVar9, auVar11._8_8_ = (auVar6._8_8_ >> lVar9) << lVar9,
         SUB164(auVar6 ^ auVar11,0) != 0 || SUB164(auVar6 ^ auVar11,4) != 0)) {
        FUN_00477d8d(iVar1,0x10);
      }
    }
    return uVar4;
  }
LAB_00477d7b:
  FUN_00477d8d(iVar1,8);
  return 0x8000000000000000;
}



// FUN_00477bf0 @ 00477bf0 size=385 callers=2

/* WARNING: Removing unreachable block (ram,0x00477c38) */
/* WARNING: Removing unreachable block (ram,0x00477c46) */
/* WARNING: Removing unreachable block (ram,0x00477c7f) */
/* WARNING: Removing unreachable block (ram,0x00477c8d) */
/* WARNING: Removing unreachable block (ram,0x00477c97) */
/* WARNING: Removing unreachable block (ram,0x00477ca7) */

ulonglong FUN_00477bf0(void)

{
  double dVar1;
  float in_XMM0_Da;
  ulonglong in_XMM0_Qb;
  int iVar2;
  ulonglong uVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  longlong lVar7;
  ulonglong uVar8;
  undefined1 auVar9 [16];
  
  if ((((uint)ABS(in_XMM0_Da) < 0x7f800000) && (dVar1 = (double)in_XMM0_Da, dVar1 < DAT_0048f358))
     && (DAT_0048f350 <= dVar1)) {
    auVar4._0_8_ = ABS(dVar1);
    auVar4._8_8_ = in_XMM0_Qb & 0x7fffffffffffffff;
    uVar3 = 0;
    if (auVar4._0_8_ != 0.0) {
      auVar6._8_8_ = 0;
      auVar6._0_8_ = DAT_0048f330;
      auVar5._8_8_ = 0;
      auVar5._0_8_ = DAT_0048f338;
      auVar5 = auVar4 & auVar6 | auVar5;
      lVar7 = (ulonglong)DAT_0048f390 - ((ulonglong)auVar4._0_8_ >> 0x34);
      uVar8 = auVar5._0_8_ >> lVar7;
      iVar2 = -(uint)((int)DAT_0048f390 < (int)(uint)((ulonglong)((longlong)dVar1 << 1) >> 0x35));
      uVar3 = CONCAT44(iVar2,iVar2);
      uVar3 = ~uVar3 & uVar8 |
              auVar5._0_8_ << ((ulonglong)auVar4._0_8_ >> 0x34) - (ulonglong)DAT_0048f390 & uVar3;
      uVar3 = ~-(ulonglong)(dVar1 == auVar4._0_8_) & -uVar3 |
              uVar3 & -(ulonglong)(dVar1 == auVar4._0_8_);
      if ((0 < (int)lVar7) &&
         (auVar9._0_8_ = uVar8 << lVar7, auVar9._8_8_ = (auVar5._8_8_ >> lVar7) << lVar7,
         SUB164(auVar5 ^ auVar9,0) != 0 || SUB164(auVar5 ^ auVar9,4) != 0)) {
        FUN_00477d8d(1,0x10);
      }
    }
    return uVar3;
  }
  FUN_00477d8d(1,8);
  return 0x8000000000000000;
}



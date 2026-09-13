// FUN_0046eab9 @ 0046eab9 size=2822 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl FUN_0046eab9(double param_1,int param_2,uint param_3)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  ushort uVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  undefined1 auVar15 [16];
  ulonglong uVar14;
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  longlong lVar19;
  ulonglong in_XMM2_Qb;
  undefined1 auVar20 [16];
  longlong lVar23;
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  ulonglong in_XMM3_Qb;
  undefined1 auVar24 [16];
  ulonglong uVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  double dVar30;
  double dVar31;
  double dVar32;
  
  dVar11 = (double)((ulonglong)param_1 >> 0x2c);
  uVar10 = (ushort)((ulonglong)param_1 >> 0x30);
  uVar3 = (SUB82(dVar11,0) & 0xff) + 1 & 0x1fe;
  dVar31 = (double)((ulonglong)DAT_00486ad0 & (ulonglong)param_1 | (ulonglong)DAT_00486ae0) *
           *(double *)(&DAT_00488890 + uVar3 * 4);
  dVar28 = *(double *)(&DAT_00488890 + uVar3 * 4);
  dVar12 = *(double *)(&DAT_00488ca0 + uVar3 * 8);
  dVar30 = *(double *)(&UNK_00488ca8 + uVar3 * 8);
  uVar3 = 0x7fef - uVar10;
  iVar6 = SUB84(param_1,0);
  uVar7 = (uint)((ulonglong)param_1 >> 0x20);
  dVar29 = param_1;
  if ((uVar10 - 0x10 | uVar3) < 0x80000000) {
    uVar3 = 0;
    uVar8 = 0x3fe7f;
LAB_0046eb36:
    uVar4 = ((ushort)((ulonglong)dVar31 >> 0x26) & 0xff) + 1 & 0x1fe;
    dVar26 = (double)((ulonglong)dVar29 & (ulonglong)DAT_00486ad0 | (ulonglong)DAT_00486ae0);
    dVar13 = (double)(DAT_00486b28 & (ulonglong)dVar26);
    in_XMM3_Qb = in_XMM3_Qb >> 0x1f;
    dVar26 = dVar26 - dVar13;
    uVar5 = ((ushort)((ulonglong)(dVar31 * *(double *)(&DAT_004894b0 + uVar4 * 4)) >> 0x1f) & 0x1ff)
            + 1 & 0x3fe;
    dVar27 = dVar28 * *(double *)(&DAT_004894b0 + uVar4 * 4) *
             *(double *)(&DAT_0048a0d0 + uVar5 * 4);
    dVar31 = dVar31 * *(double *)(&DAT_004894b0 + uVar4 * 4) *
             *(double *)(&DAT_0048a0d0 + uVar5 * 4);
    dVar29 = dVar12 + *(double *)(&DAT_004898c0 + uVar4 * 8) +
             (double)(int)((longlong)dVar11 - (ulonglong)uVar8 >> 8) +
             *(double *)(&DAT_0048a8e0 + uVar5 * 8);
    dVar11 = dVar30 + *(double *)(&DAT_004898c8 + uVar4 * 8) +
             *(double *)(&DAT_0048a8e8 + uVar5 * 8);
    dVar12 = (double)(DAT_00486b28 & (ulonglong)dVar27);
    dVar27 = dVar27 - dVar12;
    dVar32 = DAT_00486b30 + dVar31;
    dVar30 = dVar29 + dVar32;
    dVar28 = (double)CONCAT44(param_3,param_2);
    uVar2 = (ushort)(param_3 >> 0x10);
    dVar29 = dVar29 - dVar30;
    uVar4 = (uint)(ushort)((ulonglong)dVar30 >> 0x30);
    dVar12 = (((dVar31 - dVar12 * dVar13) - dVar13 * dVar27) - dVar12 * dVar26) - dVar26 * dVar27;
    dVar13 = dVar32 - dVar12;
    dVar31 = dVar30 - dVar12;
    uVar8 = uVar2 & 0x7ff0;
    if (uVar8 < 0x7ff0) {
      iVar6 = (uVar8 - 0x3ff0) + (uVar4 & 0x7ff0);
      if ((0x40a0U - iVar6 | iVar6 - 0x3c70U) < 0x80000000) {
LAB_0046ec88:
        dVar26 = (double)(DAT_00486b28 & (ulonglong)dVar28);
        dVar27 = (double)(DAT_00486b28 & (ulonglong)dVar31);
        dVar12 = (dVar29 + dVar32) - (dVar12 - (dVar30 - dVar31));
        dVar30 = dVar26 * dVar27 * 128.0;
        uVar7 = (uint)ROUND(dVar30);
        dVar28 = dVar26 * (dVar31 - dVar27) + dVar27 * (dVar28 - dVar26) +
                 (dVar31 - dVar27) * (dVar28 - dVar26);
        if (0 < (int)(0x1ff7f - uVar7 | uVar7 + 0x1e1ff)) {
          iVar6 = (uVar7 & 0x7f) * 0x10;
          auVar15._0_8_ = (double)((ulonglong)((uVar3 + uVar7 & 0xffffff80) + 0x1ff80) << 0x2d);
          auVar15._8_4_ = 0;
          auVar15._12_4_ = (int)((ulonglong)auVar15._0_8_ >> 0x20);
          dVar29 = *(double *)(&DAT_0048b910 + iVar6) * auVar15._0_8_;
          dVar28 = (dVar30 - ((dVar30 + _DAT_00486ac0) - _DAT_00486ac0)) * 0.0078125 +
                   dVar28 + ((_DAT_0048b8f0 * dVar13 + _DAT_0048b900 * dVar13 * dVar13) *
                             dVar13 * dVar13 +
                             _UNK_0048b8f8 * dVar13 + _UNK_0048b908 * dVar13 * dVar13 +
                            dVar11 + dVar12) * (double)CONCAT44(param_3,param_2);
          return (float10)(dVar28 * dVar28 * dVar29 *
                           (_DAT_00486b10 + _DAT_00486b00 * dVar28) * dVar28 * dVar28 +
                           *(double *)(&UNK_0048b918 + iVar6) * auVar15._8_8_ +
                           (_UNK_00486b18 + _UNK_00486b08 * dVar28) * dVar28 * dVar28 * dVar29 +
                           DAT_00486b20 * dVar28 * dVar29 + dVar29);
        }
        if ((int)uVar7 < 1) {
          if ((int)uVar7 < -0x3fdff) {
LAB_0046f4e7:
            iVar9 = 0x19;
            dVar28 = (double)((ulonglong)(DAT_00486b68 * DAT_00486b68) | (ulonglong)uVar3 << 0x2d);
            goto LAB_0046f28e;
          }
          uVar3 = uVar3 + 0x80;
          uVar8 = (uVar7 & 0xffffff80) + 0x3fe80;
          uVar10 = 0;
        }
        else {
          if (0x3ffff < uVar7) goto LAB_0046f50a;
          uVar3 = uVar3 + 0x3ff00;
          uVar8 = uVar7 - 0x80 & 0xffffff80;
          uVar10 = 0x3ff0;
        }
        iVar6 = (uVar7 & 0x7f) * 0x10;
        uVar7 = ((int)-(uVar8 - 0x1ff80) >> 7) + 2;
        auVar18._0_8_ = (double)((ulonglong)uVar8 << 0x2d);
        auVar18._8_4_ = 0;
        auVar18._12_4_ = (int)((ulonglong)auVar18._0_8_ >> 0x20);
        dVar31 = *(double *)(&DAT_0048b910 + iVar6) * auVar18._0_8_;
        dVar12 = (dVar30 - ((dVar30 + _DAT_00486ac0) - _DAT_00486ac0)) * 0.0078125 +
                 dVar28 + ((_DAT_0048b8f0 * dVar13 + _DAT_0048b900 * dVar13 * dVar13) *
                           dVar13 * dVar13 +
                           _UNK_0048b8f8 * dVar13 + _UNK_0048b908 * dVar13 * dVar13 +
                          dVar11 + dVar12) * (double)CONCAT44(param_3,param_2);
        dVar28 = (double)((ulonglong)uVar3 << 0x2d);
        uVar25 = (ulonglong)(uVar7 + (uVar7 & 0x20));
        dVar30 = (double)(-1L << uVar25 & (ulonglong)dVar31);
        dVar12 = dVar12 * dVar12 * dVar31 *
                 (_DAT_00486b10 + _DAT_00486b00 * dVar12) * dVar12 * dVar12 +
                 *(double *)(&UNK_0048b918 + iVar6) * auVar18._8_8_ +
                 (_UNK_00486b18 + _UNK_00486b08 * dVar12) * dVar12 * dVar12 * dVar31 +
                 DAT_00486b20 * dVar12 * dVar31;
        dVar29 = (double)((ulonglong)(dVar30 + dVar12) & -1L << uVar25);
        dVar12 = dVar12 + (dVar30 - dVar29) + (dVar31 - dVar30);
        if ((int)(uVar8 - 0x1ff80) < 1) {
          dVar28 = dVar12 * dVar28 + dVar29 * dVar28;
          dVar28 = dVar28 + (double)((ulonglong)uVar10 << 0x30) * dVar28;
          iVar9 = 0x18;
          if ((((ushort)((ulonglong)dVar28 >> 0x30) & 0x7ff0) != 0x7ff0) &&
             (iVar9 = 0x19, ((ulonglong)dVar28 & 0x7ff0000000000000) != 0)) {
            return (float10)dVar28;
          }
        }
        else {
          dVar28 = (dVar12 + dVar29) * dVar28;
          dVar28 = dVar28 + (double)((ulonglong)uVar10 << 0x30) * dVar28;
          iVar9 = 0x18;
          if ((((ushort)((ulonglong)dVar28 >> 0x30) & 0x7ff0) != 0x7ff0) &&
             (iVar9 = 0x19, ((ulonglong)dVar28 & 0x7ff0000000000000) != 0)) {
            return (float10)dVar28;
          }
        }
      }
      else {
        dVar30 = dVar28 * dVar31;
        uVar7 = (ushort)((ulonglong)dVar30 >> 0x30) & 0x7ff0;
        uVar8 = uVar7 - 0x3c70;
        if ((0x40a0 - uVar7 | uVar8) < 0x80000000) goto LAB_0046ec88;
        if (0x7fffffff < uVar8) {
          return (float10)(double)((ulonglong)(uVar3 | 0x1ff80) << 0x2d);
        }
        if (((uVar2 ^ (uVar10 & 0x7ff0) + 0xc010) & 0x8000) != 0) goto LAB_0046f4e7;
LAB_0046f50a:
        iVar9 = 0x18;
        if (uVar3 == 0) {
          dVar28 = DAT_00486b60 * DAT_00486b60;
        }
        else {
          dVar28 = DAT_00486b58 * DAT_00486b60;
        }
      }
      goto LAB_0046f28e;
    }
    auVar20._4_4_ = param_3;
    auVar20._0_4_ = param_2;
    auVar20._8_8_ = in_XMM2_Qb;
    dVar28 = (double)CONCAT44(uVar3,uVar4);
    if (iVar6 == 0) {
      if (uVar7 == 0x3ff00000) goto LAB_0046f28b;
      dVar28 = (double)CONCAT44(uVar3,uVar7);
      if (uVar7 == 0xbff00000) {
        return (float10)1;
      }
    }
  }
  else {
    auVar20._4_4_ = param_3;
    auVar20._0_4_ = param_2;
    auVar20._8_8_ = in_XMM2_Qb;
    uVar8 = param_3 & DAT_00486af0._4_4_;
    if (uVar8 < 0x7ff00000) {
      if (param_2 == 0 && uVar8 == 0) {
        iVar9 = 0x1a;
        dVar28 = DAT_00486ae0;
        if (iVar6 != 0 || ((ulonglong)param_1 & 0x7fffffff00000000) != 0) {
          iVar9 = 0x1d;
          if (((uVar7 & 0x7fffffff) < 0x7ff00001) &&
             (((uVar7 & 0x7fffffff) < 0x7ff00000 || (iVar6 == 0)))) {
            return (float10)DAT_00486ae0;
          }
        }
        goto LAB_0046f28e;
      }
      if ((int)uVar3 < 0) {
        auVar24._0_8_ = CONCAT44(DAT_00486af0._4_4_,(undefined4)DAT_00486af0) << 0x34;
        auVar24._8_8_ = in_XMM3_Qb << 0x34;
        iVar9 = (uVar8 >> 0x14) - 0x3f3;
        in_XMM3_Qb = 0;
        uVar25 = (ulonglong)
                 CONCAT22((ushort)(-1 < iVar9) * (short)((uint)iVar9 >> 0x10),
                          (ushort)(-1 < (short)iVar9) * (short)iVar9);
        lVar19 = SUB168(auVar20 | auVar24,0) << uVar25;
        lVar23 = SUB168(auVar20 | auVar24,8) << uVar25;
        auVar21._0_4_ = -(uint)((int)lVar19 == 0);
        auVar21._4_4_ = -(uint)((int)((ulonglong)lVar19 >> 0x20) == 0);
        auVar21._8_4_ = -(uint)((int)lVar23 == 0);
        auVar21._12_4_ = -(uint)((int)((ulonglong)lVar23 >> 0x20) == 0);
        bVar1 = SUB161(auVar21 >> 7,0) & 1 | (SUB161(auVar21 >> 0xf,0) & 1) << 1 |
                (SUB161(auVar21 >> 0x17,0) & 1) << 2 | (SUB161(auVar21 >> 0x1f,0) & 1) << 3 |
                (SUB161(auVar21 >> 0x27,0) & 1) << 4 | (SUB161(auVar21 >> 0x2f,0) & 1) << 5 |
                (SUB161(auVar21 >> 0x37,0) & 1) << 6 | SUB161(auVar21 >> 0x3f,0) << 7;
        uVar8 = 0x7fef - uVar3 & 0x7fff;
        uVar25 = auVar21._8_8_;
        if (0x7fef < uVar8) {
          auVar16._0_4_ = -(uint)((int)((ulonglong)DAT_00486ad0 & (ulonglong)param_1) == 0);
          auVar16._4_4_ =
               -(uint)((int)(((ulonglong)DAT_00486ad0 & (ulonglong)param_1) >> 0x20) == 0);
          auVar16._8_4_ = 0xffffffff;
          auVar16._12_4_ = 0xffffffff;
          if ((byte)(SUB161(auVar16 >> 7,0) & 1 | (SUB161(auVar16 >> 0xf,0) & 1) << 1 |
                     (SUB161(auVar16 >> 0x17,0) & 1) << 2 | (SUB161(auVar16 >> 0x1f,0) & 1) << 3 |
                     (SUB161(auVar16 >> 0x27,0) & 1) << 4 | (SUB161(auVar16 >> 0x2f,0) & 1) << 5 |
                     (SUB161(auVar16 >> 0x37,0) & 1) << 6 | SUB161(auVar16 >> 0x3f,0) << 7) == 0xff)
          {
            if (((ulonglong)param_1 & 0x8000000000000000) != 0) {
              if ((bVar1 != 0xff) ||
                 (uVar14 = (ulonglong)(((param_3 & DAT_00486af0._4_4_) >> 0x14) - 0x3f4),
                 lVar19 = CONCAT44(param_3,param_2) << uVar14, lVar23 = uVar25 << uVar14,
                 auVar22._0_4_ = -(uint)((int)lVar19 == 0),
                 auVar22._4_4_ = -(uint)((int)((ulonglong)lVar19 >> 0x20) == 0),
                 auVar22._8_4_ = -(uint)((int)lVar23 == 0),
                 auVar22._12_4_ = -(uint)((int)((ulonglong)lVar23 >> 0x20) == 0),
                 (byte)(SUB161(auVar22 >> 7,0) & 1 | (SUB161(auVar22 >> 0xf,0) & 1) << 1 |
                        (SUB161(auVar22 >> 0x17,0) & 1) << 2 | (SUB161(auVar22 >> 0x1f,0) & 1) << 3
                        | (SUB161(auVar22 >> 0x27,0) & 1) << 4 |
                        (SUB161(auVar22 >> 0x2f,0) & 1) << 5 | (SUB161(auVar22 >> 0x37,0) & 1) << 6
                       | SUB161(auVar22 >> 0x3f,0) << 7) == 0xff)) {
                if ((param_3 & 0x80000000) != 0) {
                  return (float10)0;
                }
                goto LAB_0046f21f;
              }
              if ((param_3 & 0x80000000) == 0) {
                return (float10)_DAT_00486b48;
              }
              goto LAB_0046f0d9;
            }
            if ((param_3 & 0x80000000) != 0) {
              return (float10)0;
            }
            goto LAB_0046f21f;
          }
          goto LAB_0046f11f;
        }
        if (bVar1 == 0xff) {
          uVar14 = (ulonglong)(((param_3 & DAT_00486af0._4_4_) >> 0x14) - 0x3f4);
          in_XMM3_Qb = 0;
          lVar19 = CONCAT44(param_3,param_2) << uVar14;
          lVar23 = uVar25 << uVar14;
          auVar20._0_4_ = -(uint)((int)lVar19 == SUB84(DAT_00486b50,0));
          auVar20._4_4_ =
               -(uint)((int)((ulonglong)lVar19 >> 0x20) == (int)((ulonglong)DAT_00486b50 >> 0x20));
          auVar20._8_4_ = -(uint)((int)lVar23 == 0);
          auVar20._12_4_ = -(uint)((int)((ulonglong)lVar23 >> 0x20) == 0);
          uVar3 = (ushort)((ushort)(SUB161(auVar20 >> 7,0) & 1) |
                           (ushort)(SUB161(auVar20 >> 0xf,0) & 1) << 1 |
                           (ushort)(SUB161(auVar20 >> 0x17,0) & 1) << 2 |
                           (ushort)(SUB161(auVar20 >> 0x1f,0) & 1) << 3 |
                           (ushort)(SUB161(auVar20 >> 0x27,0) & 1) << 4 |
                           (ushort)(SUB161(auVar20 >> 0x2f,0) & 1) << 5 |
                           (ushort)(SUB161(auVar20 >> 0x37,0) & 1) << 6 |
                          (ushort)(SUB161(auVar20 >> 0x3f,0) & 1) << 7) + 0x3ff01 & 0x40000;
          if (0xf < uVar8) {
            uVar8 = 0xbfe7f;
            in_XMM3_Qb = 0;
            in_XMM2_Qb = auVar20._8_8_;
            goto LAB_0046eb36;
          }
          goto LAB_0046ef54;
        }
        dVar28 = (double)((ulonglong)param_1 >> 0x20);
        in_XMM2_Qb = uVar25 >> 0x20;
        uVar3 = 0;
        uVar8 = 0;
        if (iVar6 != 0 || ((ulonglong)param_1 & 0x7fffffff00000000) != 0) {
          iVar9 = 0x1c;
          dVar28 = DAT_00486b70;
          goto LAB_0046f28e;
        }
LAB_0046efda:
        dVar29 = dVar11;
        if ((uVar8 & 0x7fffffff) == 0) {
          if ((param_3 & 0x80000000) == 0) {
            if ((uVar8 & uVar3 << 0xd) == 0) {
              return (float10)0;
            }
LAB_0046f0d9:
            return (float10)DAT_00486b50;
          }
          iVar9 = 0x1b;
          dVar28 = (double)((ulonglong)(uVar8 & uVar3 << 0xd | 0x7ff00000) << 0x20);
          goto LAB_0046f28e;
        }
      }
      else {
        uVar3 = 0;
LAB_0046ef54:
        in_XMM2_Qb = auVar20._8_8_;
        dVar11 = param_1 * 1.8446744073709552e+19;
        uVar8 = uVar7;
        dVar29 = dVar11;
        dVar31 = DAT_00486ad0;
        dVar28 = DAT_00486ae0;
        if (iVar6 == 0) goto LAB_0046efda;
      }
      dVar11 = (double)(((ulonglong)dVar29 & CONCAT44(DAT_00486af0._4_4_,(undefined4)DAT_00486af0))
                       >> 0x2c);
      uVar8 = (SUB82(dVar11,0) & 0xff) + 1 & 0x1fe;
      dVar31 = (double)((ulonglong)dVar31 & (ulonglong)dVar29 | (ulonglong)dVar28) *
               *(double *)(&DAT_00488890 + uVar8 * 4);
      dVar28 = *(double *)(&DAT_00488890 + uVar8 * 4);
      dVar12 = *(double *)(&DAT_00488ca0 + uVar8 * 8);
      dVar30 = *(double *)(&UNK_00488ca8 + uVar8 * 8);
      uVar8 = 0x43e7f;
      goto LAB_0046eb36;
    }
    dVar28 = param_1;
    if ((0x7fefffff < (uVar7 & 0x7fffffff)) && ((0x7ff00000 < (uVar7 & 0x7fffffff) || (iVar6 != 0)))
       ) {
LAB_0046f11f:
      dVar28 = param_1 + param_1;
      iVar9 = 0x3ee;
      goto LAB_0046f28e;
    }
  }
  dVar12 = auVar20._0_8_;
  uVar25 = in_XMM3_Qb & auVar20._8_8_;
  auVar17._0_4_ = -(uint)((int)((ulonglong)DAT_00486ad0 & (ulonglong)dVar12) == 0);
  auVar17._4_4_ = -(uint)((int)(((ulonglong)DAT_00486ad0 & (ulonglong)dVar12) >> 0x20) == 0);
  auVar17._8_4_ = -(uint)((int)uVar25 == 0);
  auVar17._12_4_ = -(uint)((int)(uVar25 >> 0x20) == 0);
  if ((byte)(SUB161(auVar17 >> 7,0) & 1 | (SUB161(auVar17 >> 0xf,0) & 1) << 1 |
             (SUB161(auVar17 >> 0x17,0) & 1) << 2 | (SUB161(auVar17 >> 0x1f,0) & 1) << 3 |
             (SUB161(auVar17 >> 0x27,0) & 1) << 4 | (SUB161(auVar17 >> 0x2f,0) & 1) << 5 |
             (SUB161(auVar17 >> 0x37,0) & 1) << 6 | SUB161(auVar17 >> 0x3f,0) << 7) == 0xff) {
    if (dVar28 != -1.0) {
      if ((auVar20._6_2_ & 0x8000) == 0) {
        if ((uVar10 & 0x7ff0) < 0x3ff0) {
          return (float10)0;
        }
      }
      else if (0x3fef < (uVar10 & 0x7ff0)) {
        return (float10)0;
      }
LAB_0046f21f:
      return (float10)_DAT_00486b40;
    }
LAB_0046f28b:
    return (float10)1;
  }
  iVar9 = 0x3ee;
  dVar28 = dVar12 + dVar12;
LAB_0046f28e:
  ___libm_error_support(&param_1,(undefined8 *)&param_2,(undefined8 *)&stack0xfffffff4,iVar9);
  return (float10)dVar28;
}



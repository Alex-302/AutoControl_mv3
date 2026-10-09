// FUN_00466f34 @ 00466f34 size=439 callers=4

uint __cdecl FUN_00466f34(short *param_1,uint param_2)

{
  undefined1 (*pauVar1) [32];
  short *psVar2;
  undefined1 auVar3 [32];
  uint uVar4;
  undefined1 (*pauVar5) [32];
  short *psVar6;
  int iVar7;
  uint uVar8;
  undefined1 auVar9 [16];
  undefined1 in_ZMM1 [64];
  undefined1 auVar10 [64];
  
  psVar6 = param_1;
  if (DAT_0049f178 < 5) {
    if (DAT_0049f178 < 1) {
      for (; (psVar6 != param_1 + param_2 && (*psVar6 != 0)); psVar6 = psVar6 + 1) {
      }
    }
    else {
      if (((uint)param_1 & 1) == 0) {
        uVar8 = (-(uint)(((uint)param_1 & 0xf) != 0) & 0x10 - ((uint)param_1 & 0xf)) >> 1;
        if (param_2 < uVar8) {
          uVar8 = param_2;
        }
        for (; (psVar6 != param_1 + uVar8 && (*psVar6 != 0)); psVar6 = psVar6 + 1) {
        }
        uVar4 = (int)psVar6 - (int)param_1 >> 1;
        if (uVar4 != uVar8) {
          return uVar4;
        }
        psVar6 = param_1 + uVar4;
        auVar10 = ZEXT4864(in_ZMM1._16_48_) << 0x80;
        psVar2 = psVar6 + ((param_2 - uVar8) - (param_2 - uVar8 & 0xf));
        for (; psVar6 != psVar2; psVar6 = psVar6 + 8) {
          auVar9._0_2_ = -(ushort)(*psVar6 == 0);
          auVar9._2_2_ = -(ushort)(psVar6[1] == 0);
          auVar9._4_2_ = -(ushort)(psVar6[2] == 0);
          auVar9._6_2_ = -(ushort)(psVar6[3] == 0);
          auVar9._8_2_ = -(ushort)(psVar6[4] == auVar10._8_2_);
          auVar9._10_2_ = -(ushort)(psVar6[5] == auVar10._10_2_);
          auVar9._12_2_ = -(ushort)(psVar6[6] == auVar10._12_2_);
          auVar9._14_2_ = -(ushort)(psVar6[7] == auVar10._14_2_);
          if ((((((((((((((((SUB161(auVar9 >> 7,0) & 1) != 0 || (SUB161(auVar9 >> 0xf,0) & 1) != 0)
                          || (SUB161(auVar9 >> 0x17,0) & 1) != 0) ||
                         (SUB161(auVar9 >> 0x1f,0) & 1) != 0) || (SUB161(auVar9 >> 0x27,0) & 1) != 0
                        ) || (SUB161(auVar9 >> 0x2f,0) & 1) != 0) ||
                      (SUB161(auVar9 >> 0x37,0) & 1) != 0) || (SUB161(auVar9 >> 0x3f,0) & 1) != 0)
                    || (SUB161(auVar9 >> 0x47,0) & 1) != 0) || (SUB161(auVar9 >> 0x4f,0) & 1) != 0)
                  || (SUB161(auVar9 >> 0x57,0) & 1) != 0) || (SUB161(auVar9 >> 0x5f,0) & 1) != 0) ||
                (SUB161(auVar9 >> 0x67,0) & 1) != 0) || (SUB161(auVar9 >> 0x6f,0) & 1) != 0) ||
              (auVar9._14_2_ >> 7 & 1) != 0) || (auVar9._14_2_ & 0x8000) != 0) break;
        }
        for (; (psVar6 != param_1 + param_2 && (*psVar6 != 0)); psVar6 = psVar6 + 1) {
        }
        iVar7 = (int)psVar6 - (int)param_1;
        goto LAB_004670e1;
      }
      for (; (psVar6 != param_1 + param_2 && (*psVar6 != 0)); psVar6 = psVar6 + 1) {
      }
    }
  }
  else {
    if (((uint)param_1 & 1) == 0) {
      uVar8 = (-(uint)(((uint)param_1 & 0x1f) != 0) & 0x20 - ((uint)param_1 & 0x1f)) >> 1;
      if (param_2 < uVar8) {
        uVar8 = param_2;
      }
      for (; (psVar6 != param_1 + uVar8 && (*psVar6 != 0)); psVar6 = psVar6 + 1) {
      }
      uVar4 = (int)psVar6 - (int)param_1 >> 1;
      if (uVar4 != uVar8) {
        return uVar4;
      }
      pauVar5 = (undefined1 (*) [32])(param_1 + uVar4);
      pauVar1 = (undefined1 (*) [32])
                ((int)pauVar5 + ((param_2 - uVar8) - (param_2 - uVar8 & 0x1f)) * 2);
      while ((pauVar5 != pauVar1 &&
             (auVar3 = vpcmpeqw_avx2(ZEXT1232(ZEXT812(0)),*pauVar5),
             (((((((((((((((((((((((((((((((SUB321(auVar3 >> 7,0) & 1) == 0 &&
                                          (SUB321(auVar3 >> 0xf,0) & 1) == 0) &&
                                         (SUB321(auVar3 >> 0x17,0) & 1) == 0) &&
                                        (SUB321(auVar3 >> 0x1f,0) & 1) == 0) &&
                                       (SUB321(auVar3 >> 0x27,0) & 1) == 0) &&
                                      (SUB321(auVar3 >> 0x2f,0) & 1) == 0) &&
                                     (SUB321(auVar3 >> 0x37,0) & 1) == 0) &&
                                    (SUB321(auVar3 >> 0x3f,0) & 1) == 0) &&
                                   (SUB321(auVar3 >> 0x47,0) & 1) == 0) &&
                                  (SUB321(auVar3 >> 0x4f,0) & 1) == 0) &&
                                 (SUB321(auVar3 >> 0x57,0) & 1) == 0) &&
                                (SUB321(auVar3 >> 0x5f,0) & 1) == 0) &&
                               (SUB321(auVar3 >> 0x67,0) & 1) == 0) &&
                              (SUB321(auVar3 >> 0x6f,0) & 1) == 0) &&
                             (SUB321(auVar3 >> 0x77,0) & 1) == 0) &&
                            SUB321(auVar3 >> 0x7f,0) == '\0') && (SUB321(auVar3 >> 0x87,0) & 1) == 0
                           ) && (SUB321(auVar3 >> 0x8f,0) & 1) == 0) &&
                         (SUB321(auVar3 >> 0x97,0) & 1) == 0) && (SUB321(auVar3 >> 0x9f,0) & 1) == 0
                        ) && (SUB321(auVar3 >> 0xa7,0) & 1) == 0) &&
                      (SUB321(auVar3 >> 0xaf,0) & 1) == 0) && (SUB321(auVar3 >> 0xb7,0) & 1) == 0)
                    && SUB321(auVar3 >> 0xbf,0) == '\0') && (SUB321(auVar3 >> 199,0) & 1) == 0) &&
                  (SUB321(auVar3 >> 0xcf,0) & 1) == 0) && (SUB321(auVar3 >> 0xd7,0) & 1) == 0) &&
                (SUB321(auVar3 >> 0xdf,0) & 1) == 0) && (SUB321(auVar3 >> 0xe7,0) & 1) == 0) &&
              (SUB321(auVar3 >> 0xef,0) & 1) == 0) && (SUB321(auVar3 >> 0xf7,0) & 1) == 0) &&
             -1 < auVar3[0x1f]))) {
        pauVar5 = pauVar5 + 1;
      }
      for (; (pauVar5 != (undefined1 (*) [32])(param_1 + param_2) && (*(short *)*pauVar5 != 0));
          pauVar5 = (undefined1 (*) [32])(*pauVar5 + 2)) {
      }
      return (int)pauVar5 - (int)param_1 >> 1;
    }
    for (; (psVar6 != param_1 + param_2 && (*psVar6 != 0)); psVar6 = psVar6 + 1) {
    }
  }
  iVar7 = (int)psVar6 - (int)param_1;
LAB_004670e1:
  return iVar7 >> 1;
}



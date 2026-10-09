// FUN_00466e0d @ 00466e0d size=295 callers=1

uint __cdecl FUN_00466e0d(char *param_1,uint param_2)

{
  undefined1 auVar1 [32];
  char *pcVar2;
  uint uVar3;
  undefined1 (*pauVar4) [32];
  uint uVar5;
  undefined1 (*pauVar6) [32];
  char *pcVar7;
  undefined1 auVar8 [16];
  undefined1 in_ZMM1 [64];
  undefined1 auVar9 [64];
  
  if (DAT_0049f178 < 5) {
    if (DAT_0049f178 < 1) {
      for (pcVar2 = param_1; (pcVar2 != param_1 + param_2 && (*pcVar2 != '\0')); pcVar2 = pcVar2 + 1
          ) {
      }
      uVar3 = (int)pcVar2 - (int)param_1;
    }
    else {
      uVar5 = -(uint)(((uint)param_1 & 0xf) != 0) & 0x10 - ((uint)param_1 & 0xf);
      if (param_2 < uVar5) {
        uVar5 = param_2;
      }
      for (pcVar2 = param_1; (pcVar2 != param_1 + uVar5 && (*pcVar2 != '\0')); pcVar2 = pcVar2 + 1)
      {
      }
      uVar3 = (int)pcVar2 - (int)param_1;
      if (uVar3 == uVar5) {
        pcVar2 = param_1 + uVar3;
        auVar9 = ZEXT4864(in_ZMM1._16_48_) << 0x80;
        pcVar7 = pcVar2 + ((param_2 - uVar5) - (param_2 - uVar5 & 0xf));
        while ((pcVar2 != pcVar7 &&
               (auVar8[0] = -(*pcVar2 == '\0'), auVar8[1] = -(pcVar2[1] == '\0'),
               auVar8[2] = -(pcVar2[2] == '\0'), auVar8[3] = -(pcVar2[3] == '\0'),
               auVar8[4] = -(pcVar2[4] == '\0'), auVar8[5] = -(pcVar2[5] == '\0'),
               auVar8[6] = -(pcVar2[6] == '\0'), auVar8[7] = -(pcVar2[7] == '\0'),
               auVar8[8] = -(pcVar2[8] == auVar9[8]), auVar8[9] = -(pcVar2[9] == auVar9[9]),
               auVar8[10] = -(pcVar2[10] == auVar9[10]), auVar8[0xb] = -(pcVar2[0xb] == auVar9[0xb])
               , auVar8[0xc] = -(pcVar2[0xc] == auVar9[0xc]),
               auVar8[0xd] = -(pcVar2[0xd] == auVar9[0xd]),
               auVar8[0xe] = -(pcVar2[0xe] == auVar9[0xe]),
               auVar8[0xf] = -(pcVar2[0xf] == auVar9[0xf]),
               (((((((((((((((SUB161(auVar8 >> 7,0) & 1) == 0 && (SUB161(auVar8 >> 0xf,0) & 1) == 0)
                           && (SUB161(auVar8 >> 0x17,0) & 1) == 0) &&
                          (SUB161(auVar8 >> 0x1f,0) & 1) == 0) &&
                         (SUB161(auVar8 >> 0x27,0) & 1) == 0) && (SUB161(auVar8 >> 0x2f,0) & 1) == 0
                        ) && (SUB161(auVar8 >> 0x37,0) & 1) == 0) &&
                      (SUB161(auVar8 >> 0x3f,0) & 1) == 0) && (SUB161(auVar8 >> 0x47,0) & 1) == 0)
                    && (SUB161(auVar8 >> 0x4f,0) & 1) == 0) && (SUB161(auVar8 >> 0x57,0) & 1) == 0)
                  && (SUB161(auVar8 >> 0x5f,0) & 1) == 0) && (SUB161(auVar8 >> 0x67,0) & 1) == 0) &&
                (SUB161(auVar8 >> 0x6f,0) & 1) == 0) && (SUB161(auVar8 >> 0x77,0) & 1) == 0) &&
               -1 < auVar8[0xf]))) {
          pcVar2 = pcVar2 + 0x10;
        }
        for (; (pcVar2 != param_1 + param_2 && (*pcVar2 != '\0')); pcVar2 = pcVar2 + 1) {
        }
        uVar3 = (int)pcVar2 - (int)param_1;
      }
    }
  }
  else {
    uVar5 = -(uint)(((uint)param_1 & 0x1f) != 0) & 0x20 - ((uint)param_1 & 0x1f);
    if (param_2 < uVar5) {
      uVar5 = param_2;
    }
    for (pcVar2 = param_1; (pcVar2 != param_1 + uVar5 && (*pcVar2 != '\0')); pcVar2 = pcVar2 + 1) {
    }
    uVar3 = (int)pcVar2 - (int)param_1;
    if (uVar3 == uVar5) {
      pauVar4 = (undefined1 (*) [32])(param_1 + uVar3);
      pauVar6 = (undefined1 (*) [32])(((param_2 - uVar5) - (param_2 - uVar5 & 0x1f)) + (int)pauVar4)
      ;
      while ((pauVar4 != pauVar6 &&
             (auVar1 = vpcmpeqb_avx2(ZEXT1232(ZEXT812(0)),*pauVar4),
             (((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) == 0 &&
                                          (SUB321(auVar1 >> 0xf,0) & 1) == 0) &&
                                         (SUB321(auVar1 >> 0x17,0) & 1) == 0) &&
                                        (SUB321(auVar1 >> 0x1f,0) & 1) == 0) &&
                                       (SUB321(auVar1 >> 0x27,0) & 1) == 0) &&
                                      (SUB321(auVar1 >> 0x2f,0) & 1) == 0) &&
                                     (SUB321(auVar1 >> 0x37,0) & 1) == 0) &&
                                    (SUB321(auVar1 >> 0x3f,0) & 1) == 0) &&
                                   (SUB321(auVar1 >> 0x47,0) & 1) == 0) &&
                                  (SUB321(auVar1 >> 0x4f,0) & 1) == 0) &&
                                 (SUB321(auVar1 >> 0x57,0) & 1) == 0) &&
                                (SUB321(auVar1 >> 0x5f,0) & 1) == 0) &&
                               (SUB321(auVar1 >> 0x67,0) & 1) == 0) &&
                              (SUB321(auVar1 >> 0x6f,0) & 1) == 0) &&
                             (SUB321(auVar1 >> 0x77,0) & 1) == 0) &&
                            SUB321(auVar1 >> 0x7f,0) == '\0') && (SUB321(auVar1 >> 0x87,0) & 1) == 0
                           ) && (SUB321(auVar1 >> 0x8f,0) & 1) == 0) &&
                         (SUB321(auVar1 >> 0x97,0) & 1) == 0) && (SUB321(auVar1 >> 0x9f,0) & 1) == 0
                        ) && (SUB321(auVar1 >> 0xa7,0) & 1) == 0) &&
                      (SUB321(auVar1 >> 0xaf,0) & 1) == 0) && (SUB321(auVar1 >> 0xb7,0) & 1) == 0)
                    && SUB321(auVar1 >> 0xbf,0) == '\0') && (SUB321(auVar1 >> 199,0) & 1) == 0) &&
                  (SUB321(auVar1 >> 0xcf,0) & 1) == 0) && (SUB321(auVar1 >> 0xd7,0) & 1) == 0) &&
                (SUB321(auVar1 >> 0xdf,0) & 1) == 0) && (SUB321(auVar1 >> 0xe7,0) & 1) == 0) &&
              (SUB321(auVar1 >> 0xef,0) & 1) == 0) && (SUB321(auVar1 >> 0xf7,0) & 1) == 0) &&
             -1 < auVar1[0x1f]))) {
        pauVar4 = pauVar4 + 1;
      }
      for (; (pauVar4 != (undefined1 (*) [32])(param_1 + param_2) && ((*pauVar4)[0] != '\0'));
          pauVar4 = (undefined1 (*) [32])(*pauVar4 + 1)) {
      }
      uVar3 = (int)pauVar4 - (int)param_1;
    }
  }
  return uVar3;
}



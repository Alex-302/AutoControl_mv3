// FUN_00445a10 @ 00445a10 size=2109 callers=15

undefined4 __fastcall FUN_00445a10(void *param_1)

{
  int iVar1;
  byte bVar2;
  byte *pbVar3;
  char *pcVar4;
  uint uVar5;
  bool bVar6;
  bool bVar7;
  
  while( true ) {
    *(undefined4 *)((int)param_1 + 0x3c) = 0;
    *(int *)((int)param_1 + 0x38) = *(int *)((int)param_1 + 0x40);
    if (*(int *)((int)param_1 + 0x44) - *(int *)((int)param_1 + 0x40) < 5) {
      FUN_004463d0(param_1,5);
    }
    pbVar3 = *(byte **)((int)param_1 + 0x40);
    bVar2 = *pbVar3;
    if (((&DAT_0048f0f0)[bVar2] & 0x20) == 0) break;
    do {
      *(byte **)((int)param_1 + 0x40) = pbVar3 + 1;
      if (*(byte **)((int)param_1 + 0x44) <= pbVar3 + 1) {
        FUN_004463d0(param_1,1);
      }
      pbVar3 = *(byte **)((int)param_1 + 0x40);
    } while (((&DAT_0048f0f0)[*pbVar3] & 0x20) != 0);
  }
  if (bVar2 < 0x5c) {
    if (bVar2 < 0x2e) {
      if (bVar2 < 0x23) {
        if (bVar2 == 0) {
          *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
          *(undefined4 *)((int)param_1 + 0x48) = 0xf;
          return *(undefined4 *)((int)param_1 + 0x48);
        }
        if (0x21 < bVar2) {
          uVar5 = 0;
          pbVar3 = (byte *)(*(int *)((int)param_1 + 0x40) + 1);
          *(byte **)((int)param_1 + 0x40) = pbVar3;
          *(byte **)((int)param_1 + 0x3c) = pbVar3;
          bVar2 = *pbVar3;
          if ((bVar2 < 0x20) || ((0x7f < bVar2 && ((bVar2 < 0xc2 || (0xf4 < bVar2))))))
          goto LAB_0044623f;
LAB_00445ae0:
          if ((char)(&DAT_0048f0f0)[bVar2] < '\0') goto LAB_00445de2;
          if (bVar2 < 0xe1) {
            if (0x5c < bVar2) {
              if (0xc1 < bVar2) {
                if (0xdf < bVar2) {
                  *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
                  if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
                    FUN_004463d0(param_1,1);
                  }
                  bVar2 = **(byte **)((int)param_1 + 0x40);
                  bVar6 = bVar2 < 0x9f;
                  bVar7 = bVar2 == 0x9f;
                  goto LAB_00445dab;
                }
                goto LAB_00445db9;
              }
              goto LAB_00445b41;
            }
            if (bVar2 < 0x20) goto LAB_00445b41;
            *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
            if (bVar2 < 0x23) {
              *(undefined4 *)((int)param_1 + 0x48) = 4;
              return *(undefined4 *)((int)param_1 + 0x48);
            }
            if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
              FUN_004463d0(param_1,1);
            }
            bVar2 = **(byte **)((int)param_1 + 0x40);
            if (bVar2 < 0x66) {
              if (bVar2 < 0x30) {
                if ((bVar2 != 0x22) && (bVar2 < 0x2f)) goto LAB_00445b41;
              }
              else if (bVar2 < 0x5d) {
                if (bVar2 < 0x5c) goto LAB_00445b41;
              }
              else if (bVar2 != 0x62) goto LAB_00445b41;
              goto LAB_00445de2;
            }
            if (bVar2 < 0x72) {
              if ((bVar2 < 0x67) || (bVar2 == 0x6e)) goto LAB_00445de2;
              goto LAB_00445b41;
            }
            if (bVar2 < 0x74) {
              bVar6 = bVar2 < 0x72;
              bVar7 = bVar2 == 0x72;
            }
            else {
              if (bVar2 < 0x75) goto LAB_00445de2;
              if (0x75 < bVar2) goto LAB_00445b41;
              pbVar3 = *(byte **)((int)param_1 + 0x40) + 1;
              *(byte **)((int)param_1 + 0x40) = pbVar3;
              if (*(byte **)((int)param_1 + 0x44) <= pbVar3) {
                FUN_004463d0(param_1,1);
              }
              bVar2 = **(byte **)((int)param_1 + 0x40);
              if (bVar2 < 0x41) {
                if (bVar2 < 0x30) goto LAB_00445b41;
                bVar6 = bVar2 < 0x39;
                bVar7 = bVar2 == 0x39;
LAB_00445bdf:
                if (!bVar6 && !bVar7) goto LAB_00445b41;
              }
              else if (0x46 < bVar2) {
                if (0x60 < bVar2) {
                  bVar6 = bVar2 < 0x66;
                  bVar7 = bVar2 == 0x66;
                  goto LAB_00445bdf;
                }
                goto LAB_00445b41;
              }
              pbVar3 = *(byte **)((int)param_1 + 0x40) + 1;
              *(byte **)((int)param_1 + 0x40) = pbVar3;
              if (*(byte **)((int)param_1 + 0x44) <= pbVar3) {
                FUN_004463d0(param_1,1);
              }
              bVar2 = **(byte **)((int)param_1 + 0x40);
              if (bVar2 < 0x41) {
                if (bVar2 < 0x30) goto LAB_00445b41;
                bVar6 = bVar2 < 0x39;
                bVar7 = bVar2 == 0x39;
LAB_00445c1c:
                if (!bVar6 && !bVar7) goto LAB_00445b41;
              }
              else if (0x46 < bVar2) {
                if (0x60 < bVar2) {
                  bVar6 = bVar2 < 0x66;
                  bVar7 = bVar2 == 0x66;
                  goto LAB_00445c1c;
                }
                goto LAB_00445b41;
              }
              pbVar3 = *(byte **)((int)param_1 + 0x40) + 1;
              *(byte **)((int)param_1 + 0x40) = pbVar3;
              if (*(byte **)((int)param_1 + 0x44) <= pbVar3) {
                FUN_004463d0(param_1,1);
              }
              bVar2 = **(byte **)((int)param_1 + 0x40);
              if (bVar2 < 0x41) {
                if (bVar2 < 0x30) goto LAB_00445b41;
                bVar6 = bVar2 < 0x39;
                bVar7 = bVar2 == 0x39;
LAB_00445c59:
                if (!bVar6 && !bVar7) goto LAB_00445b41;
              }
              else if (0x46 < bVar2) {
                if (0x60 < bVar2) {
                  bVar6 = bVar2 < 0x66;
                  bVar7 = bVar2 == 0x66;
                  goto LAB_00445c59;
                }
                goto LAB_00445b41;
              }
              pbVar3 = *(byte **)((int)param_1 + 0x40) + 1;
              *(byte **)((int)param_1 + 0x40) = pbVar3;
              if (*(byte **)((int)param_1 + 0x44) <= pbVar3) {
                FUN_004463d0(param_1,1);
              }
              bVar2 = **(byte **)((int)param_1 + 0x40);
              if (bVar2 < 0x41) {
                if (0x2f < bVar2) {
                  bVar6 = bVar2 < 0x39;
                  bVar7 = bVar2 == 0x39;
                  goto LAB_00445ddc;
                }
                goto LAB_00445b41;
              }
              if (bVar2 < 0x47) goto LAB_00445de2;
              if (bVar2 < 0x61) goto LAB_00445b41;
              bVar6 = bVar2 < 0x66;
              bVar7 = bVar2 == 0x66;
            }
          }
          else {
            if (bVar2 < 0xf0) {
              if (bVar2 != 0xed) goto LAB_00445d90;
              *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
              if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
                FUN_004463d0(param_1,1);
              }
              bVar2 = **(byte **)((int)param_1 + 0x40);
              if (bVar2 < 0x80) goto LAB_00445b41;
              bVar6 = bVar2 < 0x9f;
              bVar7 = bVar2 == 0x9f;
            }
            else {
              if (bVar2 < 0xf1) {
                *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
                if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
                  FUN_004463d0(param_1,1);
                }
                bVar2 = **(byte **)((int)param_1 + 0x40);
                if (bVar2 < 0x90) goto LAB_00445b41;
                bVar6 = bVar2 < 0xbf;
                bVar7 = bVar2 == 0xbf;
              }
              else if (bVar2 < 0xf4) {
                *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
                if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
                  FUN_004463d0(param_1,1);
                }
                bVar2 = **(byte **)((int)param_1 + 0x40);
                if (bVar2 < 0x80) goto LAB_00445b41;
                bVar6 = bVar2 < 0xbf;
                bVar7 = bVar2 == 0xbf;
              }
              else {
                if (0xf4 < bVar2) goto LAB_00445b41;
                *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
                if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
                  FUN_004463d0(param_1,1);
                }
                bVar2 = **(byte **)((int)param_1 + 0x40);
                if (bVar2 < 0x80) goto LAB_00445b41;
                bVar6 = bVar2 < 0x8f;
                bVar7 = bVar2 == 0x8f;
              }
              if (!bVar6 && !bVar7) goto LAB_00445b41;
LAB_00445d90:
              *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
              if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
                FUN_004463d0(param_1,1);
              }
              bVar2 = **(byte **)((int)param_1 + 0x40);
              bVar6 = bVar2 < 0x7f;
              bVar7 = bVar2 == 0x7f;
LAB_00445dab:
              if (bVar6 || bVar7) goto LAB_00445b41;
              bVar6 = bVar2 < 0xbf;
              bVar7 = bVar2 == 0xbf;
            }
            if (!bVar6 && !bVar7) goto LAB_00445b41;
LAB_00445db9:
            *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
            if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
              FUN_004463d0(param_1,1);
            }
            bVar2 = **(byte **)((int)param_1 + 0x40);
            if (bVar2 < 0x80) goto LAB_00445b41;
            bVar6 = bVar2 < 0xbf;
            bVar7 = bVar2 == 0xbf;
          }
LAB_00445ddc:
          if (!bVar6 && !bVar7) goto LAB_00445b41;
LAB_00445de2:
          *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
          if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
            FUN_004463d0(param_1,1);
          }
          bVar2 = **(byte **)((int)param_1 + 0x40);
          goto LAB_00445ae0;
        }
      }
      else if (0x2b < bVar2) {
        *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
        if (bVar2 < 0x2d) {
          *(undefined4 *)((int)param_1 + 0x48) = 0xd;
          return *(undefined4 *)((int)param_1 + 0x48);
        }
        bVar2 = **(byte **)((int)param_1 + 0x40);
        if (bVar2 < 0x30) goto LAB_0044623f;
        if (bVar2 < 0x31) {
          pbVar3 = *(byte **)((int)param_1 + 0x40) + 1;
          uVar5 = 2;
          *(byte **)((int)param_1 + 0x40) = pbVar3;
          *(byte **)((int)param_1 + 0x3c) = pbVar3;
          bVar2 = *pbVar3;
          if (bVar2 < 0x3a) {
            if (bVar2 != 0x2e) {
              if (bVar2 < 0x30) {
                *(undefined4 *)((int)param_1 + 0x48) = 6;
                return *(undefined4 *)((int)param_1 + 0x48);
              }
              goto LAB_00445f40;
            }
            goto LAB_00445fd1;
          }
          if (bVar2 < 0x46) {
            if (bVar2 < 0x45) {
              *(undefined4 *)((int)param_1 + 0x48) = 6;
              return *(undefined4 *)((int)param_1 + 0x48);
            }
          }
          else {
LAB_00445e88:
            uVar5 = 2;
            if (bVar2 != 0x65) {
              *(undefined4 *)((int)param_1 + 0x48) = 6;
              return *(undefined4 *)((int)param_1 + 0x48);
            }
          }
        }
        else {
          if (0x39 < bVar2) goto LAB_0044623f;
          uVar5 = 2;
          while( true ) {
            *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
            *(int *)((int)param_1 + 0x3c) = *(int *)((int)param_1 + 0x40);
            if (*(int *)((int)param_1 + 0x44) - *(int *)((int)param_1 + 0x40) < 3) {
              FUN_004463d0(param_1,3);
            }
            bVar2 = **(byte **)((int)param_1 + 0x40);
            if (0x39 < bVar2) break;
            if (bVar2 == 0x2e) goto LAB_00445fd1;
            if (bVar2 < 0x30) {
              *(undefined4 *)((int)param_1 + 0x48) = 6;
              return *(undefined4 *)((int)param_1 + 0x48);
            }
          }
          if (0x45 < bVar2) goto LAB_00445e88;
          if (bVar2 < 0x45) goto LAB_00446202;
        }
        goto LAB_0044604f;
      }
    }
    else if (bVar2 < 0x3a) {
      if (0x2f < bVar2) {
        uVar5 = 1;
        if (bVar2 < 0x31) {
          pbVar3 = (byte *)(*(int *)((int)param_1 + 0x40) + 1);
          *(byte **)((int)param_1 + 0x40) = pbVar3;
          *(byte **)((int)param_1 + 0x3c) = pbVar3;
          bVar2 = *pbVar3;
          if (bVar2 < 0x3a) {
            if (bVar2 != 0x2e) {
              if (bVar2 < 0x30) goto LAB_00445b58;
LAB_00445f40:
              while( true ) {
                *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
                if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
                  FUN_004463d0(param_1,1);
                }
                if (**(byte **)((int)param_1 + 0x40) < 0x30) break;
                if (0x39 < **(byte **)((int)param_1 + 0x40)) {
                  *(undefined4 *)((int)param_1 + 0x48) = 0xe;
                  return *(undefined4 *)((int)param_1 + 0x48);
                }
              }
              goto LAB_0044623f;
            }
LAB_00445fd1:
            *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
            if ((0x2f < **(byte **)((int)param_1 + 0x40)) &&
               (**(byte **)((int)param_1 + 0x40) < 0x3a)) {
              uVar5 = 3;
              do {
                *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
                *(int *)((int)param_1 + 0x3c) = *(int *)((int)param_1 + 0x40);
                if (*(int *)((int)param_1 + 0x44) - *(int *)((int)param_1 + 0x40) < 3) {
                  FUN_004463d0(param_1,3);
                }
                bVar2 = **(byte **)((int)param_1 + 0x40);
                if (0x44 < bVar2) {
                  if ((0x45 < bVar2) && (bVar2 != 0x65)) {
                    *(undefined4 *)((int)param_1 + 0x48) = 7;
                    return *(undefined4 *)((int)param_1 + 0x48);
                  }
                  goto LAB_0044604f;
                }
              } while ((0x2f < bVar2) && (bVar2 < 0x3a));
              goto LAB_0044601d;
            }
            goto LAB_00445b41;
          }
          if (bVar2 < 0x46) {
            if (bVar2 < 0x45) {
              *(undefined4 *)((int)param_1 + 0x48) = 5;
              return *(undefined4 *)((int)param_1 + 0x48);
            }
          }
          else {
LAB_00446049:
            if (bVar2 != 0x65) goto LAB_00445b58;
          }
        }
        else {
          do {
            *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
            *(int *)((int)param_1 + 0x3c) = *(int *)((int)param_1 + 0x40);
            if (*(int *)((int)param_1 + 0x44) - *(int *)((int)param_1 + 0x40) < 3) {
              FUN_004463d0(param_1,3);
            }
            bVar2 = **(byte **)((int)param_1 + 0x40);
          } while (((&DAT_0048f0f0)[bVar2] & 0x40) != 0);
          if (bVar2 < 0x45) {
            if (bVar2 != 0x2e) goto LAB_00445b58;
            goto LAB_00445fd1;
          }
          if (0x45 < bVar2) goto LAB_00446049;
        }
LAB_0044604f:
        *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
        bVar2 = **(byte **)((int)param_1 + 0x40);
        if (bVar2 < 0x2d) {
          if (bVar2 != 0x2b) goto LAB_00445b41;
LAB_00446068:
          pbVar3 = *(byte **)((int)param_1 + 0x40) + 1;
          *(byte **)((int)param_1 + 0x40) = pbVar3;
          bVar2 = *pbVar3 - 0x30;
          bVar6 = bVar2 < 9;
          bVar7 = bVar2 == 9;
        }
        else {
          if (bVar2 < 0x2e) goto LAB_00446068;
          if (bVar2 < 0x30) goto LAB_00445b41;
          bVar6 = bVar2 < 0x39;
          bVar7 = bVar2 == 0x39;
        }
        if (bVar6 || bVar7) {
          while( true ) {
            *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
            if (*(uint *)((int)param_1 + 0x44) <= *(uint *)((int)param_1 + 0x40)) {
              FUN_004463d0(param_1,1);
            }
            if (**(byte **)((int)param_1 + 0x40) < 0x30) break;
            if (0x39 < **(byte **)((int)param_1 + 0x40)) {
              *(undefined4 *)((int)param_1 + 0x48) = 7;
              return *(undefined4 *)((int)param_1 + 0x48);
            }
          }
          goto LAB_0044601d;
        }
        goto LAB_00445b41;
      }
    }
    else {
      if (bVar2 < 0x3b) {
        *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
        *(undefined4 *)((int)param_1 + 0x48) = 0xc;
        return *(undefined4 *)((int)param_1 + 0x48);
      }
      if (0x5a < bVar2) {
        *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
        *(undefined4 *)((int)param_1 + 0x48) = 8;
        return *(undefined4 *)((int)param_1 + 0x48);
      }
    }
  }
  else if (bVar2 < 0x6f) {
    if (0x65 < bVar2) {
      if (bVar2 < 0x67) {
        iVar1 = *(int *)((int)param_1 + 0x40);
        uVar5 = 0;
        pcVar4 = (char *)(iVar1 + 1);
        *(char **)((int)param_1 + 0x40) = pcVar4;
        *(char **)((int)param_1 + 0x3c) = pcVar4;
        if (*pcVar4 != 'a') goto LAB_0044623f;
        *(char **)((int)param_1 + 0x40) = (char *)(iVar1 + 2);
        if (((*(char *)(iVar1 + 2) == 'l') &&
            (*(char **)((int)param_1 + 0x40) = (char *)(iVar1 + 3), *(char *)(iVar1 + 3) == 's')) &&
           (*(char **)((int)param_1 + 0x40) = (char *)(iVar1 + 4), *(char *)(iVar1 + 4) == 'e')) {
          *(undefined4 *)((int)param_1 + 0x48) = 2;
          *(int *)((int)param_1 + 0x40) = iVar1 + 5;
          return *(undefined4 *)((int)param_1 + 0x48);
        }
      }
      else {
        if (bVar2 < 0x6e) goto LAB_0044623c;
        iVar1 = *(int *)((int)param_1 + 0x40);
        uVar5 = 0;
        pcVar4 = (char *)(iVar1 + 1);
        *(char **)((int)param_1 + 0x40) = pcVar4;
        *(char **)((int)param_1 + 0x3c) = pcVar4;
        if (*pcVar4 != 'u') goto LAB_0044623f;
        *(char **)((int)param_1 + 0x40) = (char *)(iVar1 + 2);
        if ((*(char *)(iVar1 + 2) == 'l') &&
           (*(char **)((int)param_1 + 0x40) = (char *)(iVar1 + 3), *(char *)(iVar1 + 3) == 'l')) {
          *(undefined4 *)((int)param_1 + 0x48) = 3;
          *(int *)((int)param_1 + 0x40) = iVar1 + 4;
          return *(undefined4 *)((int)param_1 + 0x48);
        }
      }
LAB_00445b41:
      *(undefined4 *)((int)param_1 + 0x40) = *(undefined4 *)((int)param_1 + 0x3c);
      if (1 < uVar5) {
        if (uVar5 == 2) {
LAB_00446202:
          *(undefined4 *)((int)param_1 + 0x48) = 6;
          return *(undefined4 *)((int)param_1 + 0x48);
        }
LAB_0044601d:
        *(undefined4 *)((int)param_1 + 0x48) = 7;
        return *(undefined4 *)((int)param_1 + 0x48);
      }
      if (uVar5 != 0) {
LAB_00445b58:
        *(undefined4 *)((int)param_1 + 0x48) = 5;
        return *(undefined4 *)((int)param_1 + 0x48);
      }
      goto LAB_0044623f;
    }
    if (bVar2 == 0x5d) {
      *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
      *(undefined4 *)((int)param_1 + 0x48) = 10;
      return *(undefined4 *)((int)param_1 + 0x48);
    }
  }
  else if (bVar2 < 0x7b) {
    if (bVar2 == 0x74) {
      iVar1 = *(int *)((int)param_1 + 0x40);
      uVar5 = 0;
      pcVar4 = (char *)(iVar1 + 1);
      *(char **)((int)param_1 + 0x40) = pcVar4;
      *(char **)((int)param_1 + 0x3c) = pcVar4;
      if (*pcVar4 != 'r') goto LAB_0044623f;
      *(char **)((int)param_1 + 0x40) = (char *)(iVar1 + 2);
      if ((*(char *)(iVar1 + 2) == 'u') &&
         (*(char **)((int)param_1 + 0x40) = (char *)(iVar1 + 3), *(char *)(iVar1 + 3) == 'e')) {
        *(undefined4 *)((int)param_1 + 0x48) = 1;
        *(int *)((int)param_1 + 0x40) = iVar1 + 4;
        return *(undefined4 *)((int)param_1 + 0x48);
      }
      goto LAB_00445b41;
    }
  }
  else {
    if (bVar2 < 0x7c) {
      *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
      *(undefined4 *)((int)param_1 + 0x48) = 9;
      return *(undefined4 *)((int)param_1 + 0x48);
    }
    if (bVar2 == 0x7d) {
      *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
      *(undefined4 *)((int)param_1 + 0x48) = 0xb;
      return *(undefined4 *)((int)param_1 + 0x48);
    }
  }
LAB_0044623c:
  *(int *)((int)param_1 + 0x40) = *(int *)((int)param_1 + 0x40) + 1;
LAB_0044623f:
  *(undefined4 *)((int)param_1 + 0x48) = 0xe;
  return *(undefined4 *)((int)param_1 + 0x48);
}



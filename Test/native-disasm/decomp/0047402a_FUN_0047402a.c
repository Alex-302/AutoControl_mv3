// FUN_0047402a @ 0047402a size=5019 callers=3

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl
FUN_0047402a(int param_1,uint param_2,int param_3,int *param_4,char *param_5,rsize_t param_6)

{
  byte bVar1;
  ulonglong uVar2;
  bool bVar3;
  int *piVar4;
  char cVar5;
  __acrt_fp_class _Var6;
  rsize_t rVar7;
  uint uVar8;
  errno_t eVar9;
  uint uVar10;
  int iVar11;
  undefined4 extraout_EDX;
  uint *puVar12;
  int iVar13;
  uint *puVar14;
  uint *puVar15;
  uint *puVar16;
  char *pcVar17;
  uint *puVar18;
  uint uVar19;
  float10 fVar20;
  ulonglong uVar21;
  longlong lVar22;
  __uint64 _Var23;
  char *_Src;
  double dVar24;
  uint local_964 [115];
  uint local_798 [2];
  char local_790;
  int local_788;
  int *local_784;
  char *local_780;
  char *local_77c;
  uint local_778;
  uint *local_774;
  uint local_770;
  undefined8 local_76c;
  uint *local_764;
  uint *local_760;
  uint *local_75c;
  uint *local_758;
  uint *local_754;
  uint *local_750;
  undefined1 local_749;
  uint *local_748;
  uint local_744 [115];
  uint *local_578;
  uint local_574 [115];
  uint *local_3a8;
  uint local_3a4 [115];
  uint *local_1d8;
  uint local_1d4 [115];
  uint local_8;
  
  pcVar17 = param_5;
  piVar4 = param_4;
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  local_784 = param_4;
  local_780 = param_5;
  scoped_fp_state_reset(local_798);
  uVar10 = param_2;
  iVar11 = param_1;
  cVar5 = '-';
  if ((param_2 & 0x80000000) == 0) {
    cVar5 = ' ';
  }
  *piVar4 = (int)cVar5;
  piVar4[2] = (int)pcVar17;
  if (((param_2 & 0x7ff00000) == 0) && (param_1 == 0 && (param_2 & 0xfffff) == 0)) {
    _Src = "0";
    local_784[1] = 0;
  }
  else {
    _Var6 = __acrt_fp_classify((double *)&param_1);
    if (_Var6 != 0) {
      local_784[1] = 1;
    }
    if (_Var6 == 1) {
      _Src = "1#INF";
    }
    else if (_Var6 == 2) {
      _Src = "1#QNAN";
    }
    else if (_Var6 == 3) {
      _Src = "1#SNAN";
    }
    else {
      if (_Var6 != 4) {
        param_2 = uVar10 & 0x7fffffff;
        local_788 = 0;
        local_77c = (char *)(param_3 + 1);
        uVar21 = CONCAT44(uVar10,iVar11) & 0x7fffffffffffffff;
        local_76c._4_4_ = (uint)(uVar21 >> 0x20);
        uVar10 = local_76c._4_4_ >> 0x14;
        if (uVar10 != 0) {
          iVar13 = 0x100000;
        }
        else {
          iVar13 = 0;
        }
        local_76c._0_4_ = (uint)uVar21;
        uVar8 = (uint)local_76c;
        uVar19 = (local_76c._4_4_ & 0xfffff) + iVar13;
        puVar14 = (uint *)(uVar10 + ((uVar10 == 0) - 0x433));
        param_1 = iVar11;
        local_76c = uVar21;
        local_750 = puVar14;
        fVar20 = (float10)FUN_004765b0();
        dVar24 = (double)fVar20;
        FUN_004766c0(dVar24);
        uVar21 = FUN_00477890((int)((ulonglong)dVar24 >> 0x20),extraout_EDX);
        local_770 = (uint)uVar21;
        if ((local_770 == 0x7fffffff) || (local_770 == 0x80000000)) {
          local_770 = 0;
        }
        local_1d4[0] = uVar8;
        local_1d4[1] = uVar19;
        uVar10 = (uint)(uVar19 != 0);
        puVar12 = (uint *)(uVar10 + 1);
        local_1d8 = puVar12;
        if ((int)puVar14 < 0) {
          if (puVar14 == (uint *)0xfffffc02) {
LAB_004746cc:
            uVar10 = local_1d4[uVar10];
            local_76c = local_76c & 0xffffffff;
            iVar11 = 0x1f;
            if (uVar10 != 0) {
              for (; uVar10 >> iVar11 == 0; iVar11 = iVar11 + -1) {
              }
            }
            if (uVar10 == 0) {
              iVar11 = 0;
            }
            else {
              iVar11 = iVar11 + 1;
            }
            local_749 = iVar11 == 0x20;
            if ((puVar12 == (uint *)0x73) && ((bool)local_749)) {
              bVar3 = true;
            }
            else {
              bVar3 = false;
            }
            if (((uint *)0x73 < puVar12) || (bVar3)) {
              local_578 = (uint *)0x0;
              local_1d8 = (uint *)0x0;
              _memcpy_s(local_1d4,0x1cc,local_574,0);
            }
            else {
              puVar15 = (uint *)0x72;
              if (puVar12 < (uint *)0x72) {
                puVar15 = puVar12;
              }
              if (puVar15 != (uint *)0xffffffff) {
                puVar18 = local_1d4 + (int)puVar15;
                puVar16 = puVar15;
                local_758 = puVar18;
                do {
                  if (puVar16 < puVar12) {
                    local_754 = (uint *)*puVar18;
                  }
                  else {
                    local_754 = (uint *)0x0;
                  }
                  if ((uint *)((int)puVar16 + -1) < puVar12) {
                    uVar10 = puVar18[-1];
                  }
                  else {
                    uVar10 = 0;
                  }
                  puVar18 = puVar18 + -1;
                  puVar16 = (uint *)((int)puVar16 + -1);
                  *local_758 = uVar10 >> 0x1f ^ (int)local_754 * 2;
                  local_758 = local_758 + -1;
                  puVar12 = local_1d8;
                  puVar14 = local_750;
                } while (puVar16 != (uint *)0xffffffff);
              }
              local_1d8 = puVar15;
              if ((bool)local_749) {
                local_1d8 = (uint *)((int)puVar15 + 1);
              }
            }
            uVar10 = 1U - (int)puVar14 >> 5;
            _memset(local_574,0,uVar10 * 4);
            local_574[uVar10] = 1 << ((byte)(1U - (int)puVar14) & 0x1f);
          }
          else {
            local_574[0] = 0;
            puVar15 = (uint *)0x2;
            local_574[1] = 0x100000;
            local_578 = (uint *)0x2;
            if (puVar12 != (uint *)0x2) goto LAB_004746cc;
            iVar11 = 0;
            do {
              if (*(int *)((int)local_574 + iVar11) != *(int *)((int)local_1d4 + iVar11))
              goto LAB_004746cc;
              iVar11 = iVar11 + 4;
            } while (iVar11 != 8);
            local_76c = local_76c & 0xffffffff;
            iVar11 = 0x1f;
            if (uVar19 != 0) {
              for (; uVar19 >> iVar11 == 0; iVar11 = iVar11 + -1) {
              }
            }
            if (uVar19 == 0) {
              iVar11 = 0;
            }
            else {
              iVar11 = iVar11 + 1;
            }
            local_749 = 0x20U - iVar11 < 2;
            puVar14 = local_1d4 + 2;
            local_758 = puVar14;
            do {
              if (puVar15 < puVar12) {
                local_754 = (uint *)*puVar14;
              }
              else {
                local_754 = (uint *)0x0;
              }
              if ((uint *)((int)puVar15 + -1) < puVar12) {
                uVar10 = puVar14[-1];
              }
              else {
                uVar10 = 0;
              }
              puVar14 = puVar14 + -1;
              puVar15 = (uint *)((int)puVar15 + -1);
              *local_758 = uVar10 >> 0x1e ^ (int)local_754 << 2;
              local_758 = local_758 + -1;
              puVar12 = local_1d8;
            } while (puVar15 != (uint *)0xffffffff);
            local_1d8 = (uint *)((byte)local_749 + 2);
            local_75c = (uint *)(2 - (int)local_750);
            uVar10 = (uint)local_75c >> 5;
            _memset(local_574,0,uVar10 * 4);
            local_574[uVar10] = 1 << ((byte)local_75c & 0x1f);
          }
          local_578 = (uint *)(uVar10 + 1);
          local_3a8 = local_578;
          _memcpy_s(local_3a4,0x1cc,local_574,(int)local_578 * 4);
        }
        else {
          local_574[0] = 0;
          local_574[1] = 0x100000;
          local_578 = (uint *)0x2;
          if (puVar12 == (uint *)0x2) {
            iVar11 = 0;
            do {
              if (*(int *)((int)local_574 + iVar11) != *(int *)((int)local_1d4 + iVar11))
              goto LAB_004743dc;
              iVar11 = iVar11 + 4;
            } while (iVar11 != 8);
            local_760 = (uint *)((int)local_750 + 2U & 0x1f);
            local_774 = (uint *)(0x20 - (int)local_760);
            puVar14 = (uint *)((int)local_750 + 2U >> 5);
            local_754 = puVar14;
            lVar22 = __allshl((byte)local_774,0);
            local_76c = local_76c & 0xffffffff;
            local_75c = (uint *)((int)lVar22 + -1);
            iVar11 = 0x1f;
            if (uVar19 != 0) {
              for (; uVar19 >> iVar11 == 0; iVar11 = iVar11 + -1) {
              }
            }
            local_778 = ~(uint)local_75c;
            if (uVar19 == 0) {
              iVar11 = 0;
            }
            else {
              iVar11 = iVar11 + 1;
            }
            local_758 = (uint *)((int)puVar14 + 2);
            local_749 = (uint *)(0x20 - iVar11) < local_760;
            if ((local_758 == (uint *)0x73) && ((bool)local_749)) {
              bVar3 = true;
            }
            else {
              bVar3 = false;
            }
            if ((0x73 < local_758) || (bVar3)) {
              local_578 = (uint *)0x0;
              local_1d8 = (uint *)0x0;
              _memcpy_s(local_1d4,0x1cc,local_574,0);
            }
            else {
              if (0x71 < local_758) {
                local_758 = (uint *)0x72;
              }
              local_764 = local_758;
              if (local_758 != (uint *)0xffffffff) {
                puVar15 = (uint *)((int)local_758 - (int)local_754);
                local_750 = local_1d4 + (int)puVar15;
                do {
                  puVar14 = local_754;
                  if (local_764 < local_754) break;
                  if (puVar15 < puVar12) {
                    uVar10 = *local_750;
                  }
                  else {
                    uVar10 = 0;
                  }
                  if ((uint *)((int)puVar15 + -1) < puVar12) {
                    uVar19 = local_750[-1];
                  }
                  else {
                    uVar19 = 0;
                  }
                  local_1d4[(int)local_764] =
                       (uVar19 & local_778) >> ((byte)local_774 & 0x1f) |
                       (uVar10 & (uint)local_75c) << ((byte)local_760 & 0x1f);
                  local_764 = (uint *)((int)local_764 + -1);
                  puVar15 = (uint *)((int)puVar15 + -1);
                  local_750 = local_750 + -1;
                  puVar12 = local_1d8;
                } while (local_764 != (uint *)0xffffffff);
              }
              if (puVar14 != (uint *)0x0) {
                puVar12 = local_1d4;
                for (; puVar14 != (uint *)0x0; puVar14 = (uint *)((int)puVar14 + -1)) {
                  *puVar12 = 0;
                  puVar12 = puVar12 + 1;
                }
              }
              local_1d8 = local_758;
              if ((bool)local_749) {
                local_1d8 = (uint *)((int)local_758 + 1);
              }
            }
            local_574[0] = 4;
          }
          else {
LAB_004743dc:
            local_754 = (uint *)((int)local_750 + 1U & 0x1f);
            local_774 = (uint *)(0x20 - (int)local_754);
            puVar14 = (uint *)((int)local_750 + 1U >> 5);
            local_750 = puVar14;
            lVar22 = __allshl((byte)local_774,0);
            uVar10 = local_1d4[uVar10];
            local_75c = (uint *)((int)lVar22 + -1);
            local_76c = local_76c & 0xffffffff;
            iVar11 = 0x1f;
            if (uVar10 != 0) {
              for (; uVar10 >> iVar11 == 0; iVar11 = iVar11 + -1) {
              }
            }
            local_778 = ~(uint)local_75c;
            if (uVar10 == 0) {
              iVar11 = 0;
            }
            else {
              iVar11 = iVar11 + 1;
            }
            local_764 = (uint *)((int)puVar12 + (int)puVar14);
            local_749 = (uint *)(0x20 - iVar11) < local_754;
            if ((local_764 == (uint *)0x73) && ((bool)local_749)) {
              bVar3 = true;
            }
            else {
              bVar3 = false;
            }
            if (((uint *)0x73 < local_764) || (bVar3)) {
              local_578 = (uint *)0x0;
              local_1d8 = (uint *)0x0;
              _memcpy_s(local_1d4,0x1cc,local_574,0);
            }
            else {
              if ((uint *)0x71 < local_764) {
                local_764 = (uint *)0x72;
              }
              local_758 = local_764;
              if (local_764 != (uint *)0xffffffff) {
                puVar15 = (uint *)((int)local_764 - (int)local_750);
                local_760 = local_1d4 + (int)puVar15;
                do {
                  puVar14 = local_750;
                  if (local_758 < local_750) break;
                  if (puVar15 < puVar12) {
                    uVar10 = *local_760;
                  }
                  else {
                    uVar10 = 0;
                  }
                  if ((uint *)((int)puVar15 + -1) < puVar12) {
                    uVar19 = local_760[-1];
                  }
                  else {
                    uVar19 = 0;
                  }
                  local_760 = local_760 + -1;
                  local_1d4[(int)local_758] =
                       (uVar10 & (uint)local_75c) << ((byte)local_754 & 0x1f) |
                       (uVar19 & local_778) >> ((byte)local_774 & 0x1f);
                  local_758 = (uint *)((int)local_758 + -1);
                  puVar15 = (uint *)((int)puVar15 + -1);
                  puVar12 = local_1d8;
                } while (local_758 != (uint *)0xffffffff);
              }
              if (puVar14 != (uint *)0x0) {
                puVar12 = local_1d4;
                for (; puVar14 != (uint *)0x0; puVar14 = (uint *)((int)puVar14 + -1)) {
                  *puVar12 = 0;
                  puVar12 = puVar12 + 1;
                }
              }
              local_1d8 = local_764;
              if ((bool)local_749) {
                local_1d8 = (uint *)((int)local_764 + 1);
              }
            }
            local_574[0] = 2;
          }
          local_3a8 = (uint *)0x1;
          local_574[1] = 0;
          local_578 = (uint *)0x1;
          _memcpy_s(local_3a4,0x1cc,local_574,4);
        }
        local_778 = 10;
        if ((int)local_770 < 0) {
          local_75c = (uint *)(-local_770 % 10);
          for (local_758 = (uint *)(-local_770 / 10); local_758 != (uint *)0x0;
              local_758 = (uint *)((int)local_758 - (int)local_750)) {
            local_750 = local_758;
            if ((uint *)0x26 < local_758) {
              local_750 = (uint *)0x26;
            }
            uVar10 = (uint)(byte)(&DAT_00484f56)[(int)local_750 * 4];
            bVar1 = (&DAT_00484f57)[(int)local_750 * 4];
            local_578 = (uint *)(uVar10 + bVar1);
            _memset(local_574,0,uVar10 * 4);
            FUN_0045c870(local_574 + uVar10,
                         (uint *)(&DAT_00484650 +
                                 (uint)*(ushort *)(&DAT_00484f54 + (int)local_750 * 4) * 4),
                         (uint)bVar1 << 2);
            uVar10 = local_1d4[0];
            local_764 = local_578;
            if (local_578 < (uint *)0x2) {
              if (local_574[0] == 0) {
LAB_00474d55:
                local_1d8 = (uint *)0x0;
                rVar7 = 0;
                puVar14 = local_964;
                goto LAB_00474fe1;
              }
              if ((local_574[0] == 1) || (local_1d8 == (uint *)0x0)) goto LAB_00474ff2;
              uVar19 = 0;
              local_76c = CONCAT44(local_1d8,(uint)local_76c);
              puVar14 = (uint *)0x0;
              do {
                lVar22 = (ulonglong)local_574[0] * (ulonglong)local_1d4[(int)puVar14] +
                         (ulonglong)uVar19;
                local_1d4[(int)puVar14] = (uint)lVar22;
                uVar19 = (uint)((ulonglong)lVar22 >> 0x20);
                puVar14 = (uint *)((int)puVar14 + 1);
              } while (puVar14 != local_1d8);
LAB_00474db5:
              if (uVar19 == 0) goto LAB_00474ff2;
              if (local_1d8 < (uint *)0x73) {
                local_1d4[(int)local_1d8] = uVar19;
                local_1d8 = (uint *)((int)local_1d8 + 1);
                goto LAB_00474ff2;
              }
LAB_00475090:
              local_1d8 = (uint *)0x0;
              _memcpy_s(local_1d4,0x1cc,local_964,0);
              bVar3 = false;
            }
            else {
              if (local_1d8 < (uint *)0x2) {
                local_1d8 = local_578;
                _memcpy_s(local_1d4,0x1cc,local_574,(int)local_578 << 2);
                if (uVar10 != 0) {
                  if ((uVar10 != 1) && (local_1d8 != (uint *)0x0)) {
                    uVar19 = 0;
                    local_76c = CONCAT44(local_1d8,(uint)local_76c);
                    puVar14 = (uint *)0x0;
                    do {
                      lVar22 = (ulonglong)uVar10 * (ulonglong)local_1d4[(int)puVar14] +
                               (ulonglong)uVar19;
                      local_1d4[(int)puVar14] = (uint)lVar22;
                      uVar19 = (uint)((ulonglong)lVar22 >> 0x20);
                      puVar14 = (uint *)((int)puVar14 + 1);
                    } while (puVar14 != local_1d8);
                    goto LAB_00474db5;
                  }
                  goto LAB_00474ff2;
                }
                goto LAB_00474d55;
              }
              puVar14 = local_574;
              if (local_578 < local_1d8) {
                local_774 = local_1d4;
                local_764 = local_1d8;
                local_754 = local_578;
              }
              else {
                puVar14 = local_1d4;
                local_774 = local_574;
                local_754 = local_1d8;
              }
              local_1d8 = (uint *)0x0;
              puVar12 = (uint *)0x0;
              local_748 = (uint *)0x0;
              if (local_754 != (uint *)0x0) {
                local_788 = (int)puVar14 - (int)local_744;
                do {
                  uVar10 = *(uint *)((int)local_744 + local_788 + (int)puVar12 * 4);
                  local_76c = CONCAT44(uVar10,(uint)local_76c);
                  if (uVar10 == 0) {
                    if (puVar12 == local_1d8) {
                      local_744[(int)puVar12] = 0;
                      local_1d8 = (uint *)((int)puVar12 + 1);
                      local_748 = local_1d8;
                    }
                  }
                  else {
                    uVar19 = 0;
                    local_760 = (uint *)0x0;
                    puVar14 = puVar12;
                    if (local_764 != (uint *)0x0) {
                      do {
                        if (puVar14 == (uint *)0x73) break;
                        if (puVar14 == local_1d8) {
                          local_744[(int)puVar14] = 0;
                          local_748 = (uint *)((int)local_760 + 1U + (int)puVar12);
                        }
                        lVar22 = (ulonglong)local_774[(int)local_760] * (ulonglong)uVar10 +
                                 (ulonglong)uVar19;
                        uVar8 = (uint)lVar22;
                        puVar15 = local_744 + (int)puVar14;
                        uVar19 = *puVar15;
                        *puVar15 = *puVar15 + uVar8;
                        uVar19 = (int)((ulonglong)lVar22 >> 0x20) + (uint)CARRY4(uVar19,uVar8);
                        local_760 = (uint *)((int)local_760 + 1);
                        puVar14 = (uint *)((int)puVar14 + 1);
                        local_1d8 = local_748;
                      } while (local_760 != local_764);
                      do {
                        if (uVar19 == 0) break;
                        if (puVar14 == (uint *)0x73) goto LAB_00475090;
                        if (puVar14 == local_1d8) {
                          local_744[(int)puVar14] = 0;
                          local_748 = (uint *)((int)puVar14 + 1);
                        }
                        puVar15 = local_744 + (int)puVar14;
                        uVar10 = *puVar15;
                        *puVar15 = *puVar15 + uVar19;
                        uVar19 = (uint)CARRY4(uVar10,uVar19);
                        puVar14 = (uint *)((int)puVar14 + 1);
                        local_1d8 = local_748;
                      } while( true );
                    }
                    if (puVar14 == (uint *)0x73) goto LAB_00475090;
                  }
                  puVar12 = (uint *)((int)puVar12 + 1);
                } while (puVar12 != local_754);
              }
              rVar7 = (int)local_1d8 << 2;
              puVar14 = local_744;
LAB_00474fe1:
              _memcpy_s(local_1d4,0x1cc,puVar14,rVar7);
LAB_00474ff2:
              bVar3 = true;
            }
            if (!bVar3) goto LAB_004750de;
          }
          if (local_75c != (uint *)0x0) {
            uVar10 = *(uint *)(&DAT_00484fec + (int)local_75c * 2);
            local_76c = CONCAT44(uVar10,(uint)local_76c);
            if (uVar10 == 0) {
LAB_004750de:
              local_1d8 = (uint *)0x0;
              puVar14 = local_1d4;
              goto LAB_004750eb;
            }
            if ((uVar10 != 1) && (local_1d8 != (uint *)0x0)) {
              uVar19 = 0;
              puVar14 = (uint *)0x0;
              do {
                lVar22 = (ulonglong)uVar10 * (ulonglong)local_1d4[(int)puVar14] + (ulonglong)uVar19;
                local_1d4[(int)puVar14] = (uint)lVar22;
                uVar19 = (uint)((ulonglong)lVar22 >> 0x20);
                puVar14 = (uint *)((int)puVar14 + 1);
              } while (puVar14 != local_1d8);
              if (uVar19 != 0) {
                if ((uint *)0x72 < local_1d8) goto LAB_004750de;
                local_1d4[(int)local_1d8] = uVar19;
                local_1d8 = (uint *)((int)local_1d8 + 1);
              }
            }
          }
        }
        else {
          local_774 = (uint *)(local_770 / 10);
          local_76c = CONCAT44(local_770 % 10,(uint)local_76c);
          uVar10 = local_770 % 10;
          if (local_774 != (uint *)0x0) {
            do {
              local_760 = local_774;
              if ((uint *)0x26 < local_774) {
                local_760 = (uint *)0x26;
              }
              uVar10 = (uint)(byte)(&DAT_00484f56)[(int)local_760 * 4];
              bVar1 = (&DAT_00484f57)[(int)local_760 * 4];
              local_578 = (uint *)(uVar10 + bVar1);
              _memset(local_574,0,uVar10 * 4);
              FUN_0045c870(local_574 + uVar10,
                           (uint *)(&DAT_00484650 +
                                   (uint)*(ushort *)(&DAT_00484f54 + (int)local_760 * 4) * 4),
                           (uint)bVar1 << 2);
              uVar10 = local_3a4[0];
              local_764 = local_578;
              if (local_578 < (uint *)0x2) {
                if (local_574[0] == 0) {
                  rVar7 = 0;
                  local_748 = (uint *)0x0;
                  local_3a8 = (uint *)0x0;
LAB_00474b9e:
                  puVar14 = local_744;
                  goto LAB_00474ba5;
                }
                if ((local_574[0] == 1) || (local_3a8 == (uint *)0x0)) goto LAB_00474bb6;
                uVar19 = 0;
                puVar14 = (uint *)0x0;
                do {
                  lVar22 = (ulonglong)local_574[0] * (ulonglong)local_3a4[(int)puVar14] +
                           (ulonglong)uVar19;
                  local_3a4[(int)puVar14] = (uint)lVar22;
                  uVar19 = (uint)((ulonglong)lVar22 >> 0x20);
                  puVar14 = (uint *)((int)puVar14 + 1);
                } while (puVar14 != local_3a8);
LAB_004749f6:
                local_75c = local_3a8;
                if (uVar19 == 0) goto LAB_00474bb6;
                if (local_3a8 < (uint *)0x73) {
                  local_3a4[(int)local_3a8] = uVar19;
                  local_3a8 = (uint *)((int)local_3a8 + 1);
                  goto LAB_00474bb6;
                }
                local_578 = (uint *)0x0;
                puVar14 = local_574;
LAB_00474c13:
                local_3a8 = (uint *)0x0;
                _memcpy_s(local_3a4,0x1cc,puVar14,0);
                bVar3 = false;
              }
              else {
                if ((uint *)0x1 < local_3a8) {
                  puVar14 = local_574;
                  if (local_578 < local_3a8) {
                    local_754 = local_3a4;
                    local_764 = local_3a8;
                    local_758 = local_578;
                  }
                  else {
                    puVar14 = local_3a4;
                    local_754 = local_574;
                    local_758 = local_3a8;
                  }
                  local_3a8 = (uint *)0x0;
                  puVar12 = (uint *)0x0;
                  local_748 = (uint *)0x0;
                  if (local_758 != (uint *)0x0) {
                    local_788 = (int)puVar14 - (int)local_744;
                    do {
                      local_75c = *(uint **)((int)local_744 + local_788 + (int)puVar12 * 4);
                      if (local_75c == (uint *)0x0) {
                        if (puVar12 == local_3a8) {
                          local_744[(int)puVar12] = 0;
                          local_3a8 = (uint *)((int)puVar12 + 1);
                          local_748 = local_3a8;
                        }
                      }
                      else {
                        uVar10 = 0;
                        local_750 = (uint *)0x0;
                        puVar14 = puVar12;
                        if (local_764 != (uint *)0x0) {
                          do {
                            if (puVar14 == (uint *)0x73) break;
                            if (puVar14 == local_3a8) {
                              local_744[(int)puVar14] = 0;
                              local_748 = (uint *)((int)local_750 + 1U + (int)puVar12);
                            }
                            lVar22 = (ulonglong)local_754[(int)local_750] * ZEXT48(local_75c) +
                                     (ulonglong)uVar10;
                            uVar19 = (uint)lVar22;
                            puVar15 = local_744 + (int)puVar14;
                            uVar10 = *puVar15;
                            *puVar15 = *puVar15 + uVar19;
                            uVar10 = (int)((ulonglong)lVar22 >> 0x20) + (uint)CARRY4(uVar10,uVar19);
                            local_750 = (uint *)((int)local_750 + 1);
                            puVar14 = (uint *)((int)puVar14 + 1);
                            local_3a8 = local_748;
                          } while (local_750 != local_764);
                          do {
                            if (uVar10 == 0) break;
                            if (puVar14 == (uint *)0x73) goto LAB_00474bfe;
                            if (puVar14 == local_3a8) {
                              local_744[(int)puVar14] = 0;
                              local_748 = (uint *)((int)puVar14 + 1);
                            }
                            puVar15 = local_744 + (int)puVar14;
                            uVar19 = *puVar15;
                            *puVar15 = *puVar15 + uVar10;
                            uVar10 = (uint)CARRY4(uVar19,uVar10);
                            puVar14 = (uint *)((int)puVar14 + 1);
                            local_3a8 = local_748;
                          } while( true );
                        }
                        if (puVar14 == (uint *)0x73) {
LAB_00474bfe:
                          puVar14 = local_964;
                          goto LAB_00474c13;
                        }
                      }
                      puVar12 = (uint *)((int)puVar12 + 1);
                    } while (puVar12 != local_758);
                  }
                  rVar7 = (int)local_3a8 << 2;
                  goto LAB_00474b9e;
                }
                local_3a8 = local_578;
                _memcpy_s(local_3a4,0x1cc,local_574,(int)local_578 << 2);
                if (uVar10 != 0) {
                  if ((uVar10 != 1) && (local_3a8 != (uint *)0x0)) {
                    uVar19 = 0;
                    puVar14 = (uint *)0x0;
                    do {
                      lVar22 = (ulonglong)uVar10 * (ulonglong)local_3a4[(int)puVar14] +
                               (ulonglong)uVar19;
                      local_3a4[(int)puVar14] = (uint)lVar22;
                      uVar19 = (uint)((ulonglong)lVar22 >> 0x20);
                      puVar14 = (uint *)((int)puVar14 + 1);
                    } while (puVar14 != local_3a8);
                    goto LAB_004749f6;
                  }
                  goto LAB_00474bb6;
                }
                local_578 = (uint *)0x0;
                local_3a8 = (uint *)0x0;
                rVar7 = 0;
                puVar14 = local_574;
LAB_00474ba5:
                _memcpy_s(local_3a4,0x1cc,puVar14,rVar7);
LAB_00474bb6:
                bVar3 = true;
              }
              if (!bVar3) goto LAB_00474c38;
              local_774 = (uint *)((int)local_774 - (int)local_760);
            } while (local_774 != (uint *)0x0);
            uVar10 = local_76c._4_4_;
          }
          if (uVar10 != 0) {
            uVar10 = *(uint *)(&DAT_00484fec + uVar10 * 2);
            if (uVar10 == 0) {
LAB_00474c38:
              local_3a8 = (uint *)0x0;
              puVar14 = local_3a4;
LAB_004750eb:
              _memcpy_s(puVar14,0x1cc,local_964,0);
            }
            else if (uVar10 != 1) {
              local_76c = CONCAT44(local_3a8,(uint)local_76c);
              if (local_3a8 != (uint *)0x0) {
                uVar19 = 0;
                puVar14 = (uint *)0x0;
                do {
                  lVar22 = (ulonglong)uVar10 * (ulonglong)local_3a4[(int)puVar14] +
                           (ulonglong)uVar19;
                  local_3a4[(int)puVar14] = (uint)lVar22;
                  uVar19 = (uint)((ulonglong)lVar22 >> 0x20);
                  puVar14 = (uint *)((int)puVar14 + 1);
                } while (puVar14 != local_3a8);
                if (uVar19 != 0) {
                  if ((uint *)0x72 < local_3a8) goto LAB_00474c38;
                  local_3a4[(int)local_3a8] = uVar19;
                  local_3a8 = (uint *)((int)local_3a8 + 1);
                }
              }
            }
          }
        }
        pcVar17 = local_780;
        local_750 = (uint *)local_780;
        if (local_1d8 != (uint *)0x0) {
          uVar10 = 0;
          puVar14 = (uint *)0x0;
          do {
            lVar22 = (ulonglong)local_1d4[(int)puVar14] * 10 + (ulonglong)uVar10;
            local_1d4[(int)puVar14] = (uint)lVar22;
            uVar10 = (uint)((ulonglong)lVar22 >> 0x20);
            puVar14 = (uint *)((int)puVar14 + 1);
          } while (puVar14 != local_1d8);
          local_76c = CONCAT44(uVar10,(uint)local_76c);
          if (uVar10 != 0) {
            if (local_1d8 < (uint *)0x73) {
              local_1d4[(int)local_1d8] = uVar10;
              local_1d8 = (uint *)((int)local_1d8 + 1);
            }
            else {
              local_1d8 = (uint *)0x0;
              _memcpy_s(local_1d4,0x1cc,local_964,0);
            }
          }
        }
        _Var23 = __crt_strtox::divide((big_integer *)&local_1d8,(big_integer *)&local_3a8);
        if ((int)_Var23 == 10) {
          local_770 = local_770 + 1;
          local_750 = (uint *)(pcVar17 + 1);
          *pcVar17 = '1';
          if (local_3a8 != (uint *)0x0) {
            uVar10 = 0;
            puVar14 = (uint *)0x0;
            do {
              lVar22 = (ulonglong)local_3a4[(int)puVar14] * 10 + (ulonglong)uVar10;
              local_3a4[(int)puVar14] = (uint)lVar22;
              uVar10 = (uint)((ulonglong)lVar22 >> 0x20);
              puVar14 = (uint *)((int)puVar14 + 1);
            } while (puVar14 != local_3a8);
            if (uVar10 != 0) {
              if (local_3a8 < (uint *)0x73) {
                local_3a4[(int)local_3a8] = uVar10;
                local_3a8 = (uint *)((int)local_3a8 + 1);
              }
              else {
                local_3a8 = (uint *)0x0;
                _memcpy_s(local_3a4,0x1cc,local_964,0);
              }
            }
          }
LAB_0047524f:
          pcVar17 = pcVar17 + 1;
          uVar10 = local_770;
        }
        else {
          if ((int)_Var23 != 0) {
            local_750 = (uint *)(pcVar17 + 1);
            *pcVar17 = (char)_Var23 + '0';
            goto LAB_0047524f;
          }
          uVar10 = local_770 - 1;
        }
        local_784[1] = uVar10;
        if ((-1 < (int)uVar10) && (local_77c < 0x80000000)) {
          local_77c = (char *)((int)local_77c + uVar10);
        }
        uVar10 = param_6 - 1;
        if (local_77c <= param_6 - 1) {
          uVar10 = (uint)local_77c;
        }
        local_77c = local_780 + uVar10;
        if (pcVar17 != local_77c) {
          do {
            puVar14 = local_750;
            if (local_1d8 == (uint *)0x0) break;
            uVar10 = 0;
            puVar12 = (uint *)0x0;
            do {
              lVar22 = (ulonglong)local_1d4[(int)puVar12] * 1000000000 + (ulonglong)uVar10;
              local_1d4[(int)puVar12] = (uint)lVar22;
              uVar10 = (uint)((ulonglong)lVar22 >> 0x20);
              puVar12 = (uint *)((int)puVar12 + 1);
            } while (puVar12 != local_1d8);
            if (uVar10 != 0) {
              if (local_1d8 < (uint *)0x73) {
                local_1d4[(int)local_1d8] = uVar10;
                local_1d8 = (uint *)((int)local_1d8 + 1);
              }
              else {
                local_1d8 = (uint *)0x0;
                _memcpy_s(local_1d4,0x1cc,local_964,0);
              }
            }
            uVar21 = __crt_strtox::divide((big_integer *)&local_1d8,(big_integer *)&local_3a8);
            uVar19 = 8;
            uVar10 = (int)local_77c - (int)puVar14;
            do {
              uVar2 = uVar21 & 0xffffffff;
              uVar21 = uVar2 / local_778;
              if (uVar19 <= uVar10) {
                *(char *)((int)puVar14 + uVar19) = (char)(uVar2 % (ulonglong)local_778) + '0';
              }
              uVar19 = uVar19 - 1;
            } while (uVar19 != 0xffffffff);
            if (9 < uVar10) {
              uVar10 = 9;
            }
            pcVar17 = (char *)((int)puVar14 + uVar10);
            local_750 = (uint *)pcVar17;
          } while (pcVar17 != local_77c);
        }
        *pcVar17 = '\0';
        goto LAB_00475392;
      }
      _Src = "1#IND";
    }
  }
  eVar9 = _strcpy_s(pcVar17,param_6,_Src);
  if (eVar9 != 0) {
                    /* WARNING: Subroutine does not return */
    __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
  }
LAB_00475392:
  if (local_790 != '\0') {
    fesetenv(local_798);
  }
  return;
}



// convert_decimal_string_to_floating_type_common @ 00460de4 size=7619 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    enum SLD_STATUS __cdecl __crt_strtox::convert_decimal_string_to_floating_type_common(struct
   __crt_strtox::floating_point_string const &,class __crt_strtox::floating_point_value const &)
   
   Library: Visual Studio 2015 Release */

SLD_STATUS __cdecl
__crt_strtox::convert_decimal_string_to_floating_type_common
          (floating_point_string *param_1,floating_point_value *param_2)

{
  floating_point_string *pfVar1;
  floating_point_string **ppfVar2;
  SLD_STATUS SVar3;
  byte bVar4;
  uint uVar5;
  floating_point_string *pfVar6;
  int iVar7;
  floating_point_string *pfVar8;
  floating_point_string *pfVar9;
  uint uVar10;
  uint uVar11;
  floating_point_string *pfVar12;
  floating_point_string *pfVar13;
  bool bVar14;
  longlong lVar15;
  __uint64 _Var16;
  floating_point_string fVar17;
  rsize_t rVar18;
  undefined1 local_b2c [460];
  uint local_960;
  floating_point_value *local_95c;
  floating_point_string *local_958;
  floating_point_string *local_954;
  uint local_950;
  uint local_94c;
  floating_point_string *local_948;
  undefined1 local_941;
  floating_point_string *local_940;
  floating_point_string *local_93c;
  floating_point_string *local_938;
  floating_point_string *local_934;
  floating_point_string *local_930;
  floating_point_string *local_92c;
  floating_point_string *local_928;
  floating_point_string *local_924;
  floating_point_string *local_920;
  floating_point_string *local_91c;
  floating_point_string *local_918;
  floating_point_string *local_914 [115];
  floating_point_string *local_748;
  floating_point_string *local_744 [115];
  floating_point_string *local_578;
  floating_point_string *local_574 [115];
  floating_point_string *local_3a8;
  floating_point_string *local_3a4 [115];
  floating_point_string *local_1d8;
  floating_point_string *local_1d4;
  uint local_1d0;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  local_954 = param_1;
  local_95c = param_2;
  uVar11 = *(uint *)param_1;
  local_958 = (floating_point_string *)
              (((param_2[4] == (floating_point_value)0x0) - 1 & 0x1d) + 0x19);
  if ((int)uVar11 < 0) {
    uVar11 = 0;
  }
  uVar10 = *(uint *)(param_1 + 4);
  uVar5 = uVar11;
  if (uVar10 <= uVar11) {
    uVar5 = uVar10;
  }
  local_940 = param_1 + uVar10 + 8;
  pfVar8 = param_1 + uVar5 + 8;
  local_938 = (floating_point_string *)(uVar11 - uVar5);
  local_924 = local_940 + -(int)pfVar8;
  pfVar12 = param_1 + 8;
  local_91c = (floating_point_string *)0x0;
  uVar11 = 0;
  local_1d8 = (floating_point_string *)0x0;
  local_920 = (floating_point_string *)0x0;
  local_930 = pfVar8;
  local_928 = pfVar12;
  if (pfVar12 != pfVar8) {
    do {
      if (uVar11 == 9) {
        local_928 = pfVar12;
        pfVar8 = local_91c;
        if (local_91c != (floating_point_string *)0x0) {
          pfVar6 = (floating_point_string *)0x0;
          pfVar8 = (floating_point_string *)0x0;
          do {
            lVar15 = ZEXT48((&local_1d4)[(int)pfVar8]) * 1000000000 + ZEXT48(pfVar6);
            (&local_1d4)[(int)pfVar8] = (floating_point_string *)lVar15;
            pfVar6 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
            pfVar8 = pfVar8 + 1;
          } while (pfVar8 != local_91c);
          pfVar8 = local_1d8;
          if (pfVar6 != (floating_point_string *)0x0) {
            if (local_1d8 < (floating_point_string *)0x73) {
              (&local_1d4)[(int)local_1d8] = pfVar6;
              local_1d8 = local_1d8 + 1;
              pfVar8 = local_1d8;
            }
            else {
              local_748 = (floating_point_string *)0x0;
              local_1d8 = (floating_point_string *)0x0;
              _memcpy_s(&local_1d4,0x1cc,local_744,0);
              pfVar8 = local_1d8;
            }
          }
        }
        local_91c = pfVar8;
        if (local_920 != (floating_point_string *)0x0) {
          pfVar6 = (floating_point_string *)0x0;
          pfVar8 = local_920;
          if (local_91c != (floating_point_string *)0x0) {
            do {
              ppfVar2 = &local_1d4 + (int)pfVar6;
              pfVar13 = *ppfVar2;
              *ppfVar2 = pfVar8 + (int)*ppfVar2;
              pfVar8 = (floating_point_string *)(uint)CARRY4((uint)pfVar13,(uint)pfVar8);
              pfVar6 = pfVar6 + 1;
              local_91c = local_1d8;
            } while (pfVar6 != local_1d8);
          }
          if (pfVar8 != (floating_point_string *)0x0) {
            if (local_91c < (floating_point_string *)0x73) {
              (&local_1d4)[(int)local_91c] = pfVar8;
              local_91c = local_1d8 + 1;
              local_1d8 = local_91c;
            }
            else {
              local_748 = (floating_point_string *)0x0;
              local_1d8 = (floating_point_string *)0x0;
              _memcpy_s(&local_1d4,0x1cc,local_744,0);
              local_91c = local_1d8;
            }
          }
        }
        local_920 = (floating_point_string *)0x0;
        uVar11 = 0;
        pfVar8 = local_930;
      }
      local_920 = (floating_point_string *)((int)local_920 * 10 + (uint)(byte)*pfVar12);
      uVar11 = uVar11 + 1;
      pfVar12 = pfVar12 + 1;
    } while (pfVar12 != pfVar8);
    local_928 = pfVar12;
    if (uVar11 != 0) {
      local_94c = uVar11 % 10;
      pfVar8 = local_91c;
      for (local_93c = (floating_point_string *)(uVar11 / 10);
          local_93c != (floating_point_string *)0x0; local_93c = local_93c + -(int)local_934) {
        local_934 = local_93c;
        if ((floating_point_string *)0x26 < local_93c) {
          local_934 = (floating_point_string *)0x26;
        }
        uVar11 = (uint)(byte)(&DAT_00484f56)[(int)local_934 * 4];
        bVar4 = (&DAT_00484f57)[(int)local_934 * 4];
        local_748 = (floating_point_string *)(uVar11 + bVar4);
        _memset(local_744,0,uVar11 * 4);
        FUN_0045c870((uint *)(local_744 + uVar11),
                     (uint *)(&DAT_00484650 +
                             (uint)*(ushort *)(&DAT_00484f54 + (int)local_934 * 4) * 4),
                     (uint)bVar4 << 2);
        pfVar12 = local_1d4;
        if (local_748 < (floating_point_string *)0x2) {
          if (local_744[0] == (floating_point_string *)0x0) {
            local_918 = (floating_point_string *)0x0;
            local_1d8 = (floating_point_string *)0x0;
            rVar18 = 0;
            ppfVar2 = local_914;
            goto LAB_00461359;
          }
          if ((local_744[0] == (floating_point_string *)0x1) ||
             (pfVar8 == (floating_point_string *)0x0)) {
            bVar14 = true;
          }
          else {
            pfVar6 = (floating_point_string *)0x0;
            pfVar12 = (floating_point_string *)0x0;
            do {
              lVar15 = ZEXT48(local_744[0]) * ZEXT48((&local_1d4)[(int)pfVar12]) + ZEXT48(pfVar6);
              (&local_1d4)[(int)pfVar12] = (floating_point_string *)lVar15;
              pfVar6 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
              pfVar12 = pfVar12 + 1;
            } while (pfVar12 != pfVar8);
LAB_004610e5:
            if (pfVar6 != (floating_point_string *)0x0) {
              if ((floating_point_string *)0x72 < local_1d8) {
                ppfVar2 = local_744;
                local_748 = (floating_point_string *)0x0;
LAB_00461118:
                local_1d8 = (floating_point_string *)0x0;
                _memcpy_s(&local_1d4,0x1cc,ppfVar2,0);
                bVar14 = false;
                pfVar8 = local_1d8;
                local_91c = local_1d8;
                goto LAB_00461376;
              }
              (&local_1d4)[(int)local_1d8] = pfVar6;
              local_1d8 = local_1d8 + 1;
            }
            bVar14 = true;
            pfVar8 = local_1d8;
            local_91c = local_1d8;
          }
        }
        else {
          if (pfVar8 < (floating_point_string *)0x2) {
            local_1d8 = local_748;
            _memcpy_s(&local_1d4,0x1cc,local_744,(int)local_748 << 2);
            if (pfVar12 != (floating_point_string *)0x0) {
              bVar14 = true;
              local_91c = local_1d8;
              pfVar8 = local_1d8;
              if ((pfVar12 != (floating_point_string *)0x1) &&
                 (local_1d8 != (floating_point_string *)0x0)) {
                pfVar6 = (floating_point_string *)0x0;
                pfVar8 = (floating_point_string *)0x0;
                do {
                  lVar15 = ZEXT48(pfVar12) * ZEXT48((&local_1d4)[(int)pfVar8]) + ZEXT48(pfVar6);
                  (&local_1d4)[(int)pfVar8] = (floating_point_string *)lVar15;
                  pfVar6 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
                  pfVar8 = pfVar8 + 1;
                } while (pfVar8 != local_1d8);
                goto LAB_004610e5;
              }
              goto LAB_00461376;
            }
            rVar18 = 0;
            local_748 = (floating_point_string *)0x0;
            local_1d8 = (floating_point_string *)0x0;
            ppfVar2 = local_744;
          }
          else {
            ppfVar2 = local_744;
            if (local_748 < pfVar8) {
              local_928 = (floating_point_string *)&local_1d4;
              pfVar12 = pfVar8;
              pfVar8 = local_748;
            }
            else {
              ppfVar2 = &local_1d4;
              local_928 = (floating_point_string *)local_744;
              pfVar12 = local_748;
            }
            local_1d8 = (floating_point_string *)0x0;
            pfVar6 = (floating_point_string *)0x0;
            local_3a8 = (floating_point_string *)0x0;
            if (pfVar8 != (floating_point_string *)0x0) {
              local_950 = (int)ppfVar2 - (int)local_3a4;
              do {
                local_960 = *(uint *)((int)local_3a4 + local_950 + (int)pfVar6 * 4);
                if (local_960 == 0) {
                  if (pfVar6 == local_1d8) {
                    local_3a4[(int)pfVar6] = (floating_point_string *)0x0;
                    local_1d8 = pfVar6 + 1;
                    local_3a8 = local_1d8;
                  }
                }
                else {
                  local_92c = (floating_point_string *)0x0;
                  local_948 = (floating_point_string *)0x0;
                  pfVar13 = pfVar6;
                  if (pfVar12 != (floating_point_string *)0x0) {
                    do {
                      pfVar9 = local_92c;
                      if (pfVar13 == (floating_point_string *)0x73) break;
                      if (pfVar13 == local_1d8) {
                        local_3a4[(int)pfVar13] = (floating_point_string *)0x0;
                        local_3a8 = local_948 + 1 + (int)pfVar6;
                      }
                      uVar11 = *(uint *)(local_928 + (int)local_948 * 4);
                      uVar10 = (uint)((ulonglong)uVar11 * (ulonglong)local_960);
                      ppfVar2 = local_3a4 + (int)pfVar13;
                      pfVar9 = *ppfVar2;
                      *ppfVar2 = local_92c + uVar10 + (int)*ppfVar2;
                      pfVar9 = (floating_point_string *)
                               ((int)((ulonglong)uVar11 * (ulonglong)local_960 >> 0x20) +
                                (uint)CARRY4(uVar10,(uint)local_92c) +
                               (uint)CARRY4((uint)pfVar9,(uint)(local_92c + uVar10)));
                      local_948 = local_948 + 1;
                      pfVar13 = pfVar13 + 1;
                      local_1d8 = local_3a8;
                      local_92c = pfVar9;
                    } while (local_948 != pfVar12);
                    do {
                      if (pfVar9 == (floating_point_string *)0x0) break;
                      if (pfVar13 == (floating_point_string *)0x73) goto LAB_004613e4;
                      if (pfVar13 == local_1d8) {
                        local_3a4[(int)pfVar13] = (floating_point_string *)0x0;
                        local_3a8 = pfVar13 + 1;
                      }
                      ppfVar2 = local_3a4 + (int)pfVar13;
                      pfVar1 = *ppfVar2;
                      *ppfVar2 = pfVar9 + (int)*ppfVar2;
                      pfVar9 = (floating_point_string *)(uint)CARRY4((uint)pfVar1,(uint)pfVar9);
                      pfVar13 = pfVar13 + 1;
                      local_1d8 = local_3a8;
                    } while( true );
                  }
                  if (pfVar13 == (floating_point_string *)0x73) {
LAB_004613e4:
                    ppfVar2 = local_914;
                    local_918 = (floating_point_string *)0x0;
                    local_91c = pfVar8;
                    goto LAB_00461118;
                  }
                }
                pfVar6 = pfVar6 + 1;
              } while (pfVar6 != pfVar8);
            }
            rVar18 = (int)local_1d8 << 2;
            ppfVar2 = local_3a4;
            local_91c = pfVar8;
          }
LAB_00461359:
          _memcpy_s(&local_1d4,0x1cc,ppfVar2,rVar18);
          bVar14 = true;
          pfVar8 = local_1d8;
          local_91c = local_1d8;
        }
LAB_00461376:
        if (!bVar14) goto LAB_004613ab;
      }
      if (local_94c != 0) {
        uVar11 = *(uint *)(&DAT_00484fec + local_94c * 2);
        if (uVar11 == 0) {
LAB_004613ab:
          local_748 = (floating_point_string *)0x0;
          local_1d8 = (floating_point_string *)0x0;
          _memcpy_s(&local_1d4,0x1cc,local_744,0);
LAB_004613dc:
          local_91c = local_1d8;
        }
        else if ((uVar11 != 1) && (local_91c != (floating_point_string *)0x0)) {
          pfVar8 = (floating_point_string *)0x0;
          pfVar12 = (floating_point_string *)0x0;
          do {
            lVar15 = (ulonglong)uVar11 * ZEXT48((&local_1d4)[(int)pfVar12]) + ZEXT48(pfVar8);
            (&local_1d4)[(int)pfVar12] = (floating_point_string *)lVar15;
            pfVar8 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
            pfVar12 = pfVar12 + 1;
          } while (pfVar12 != local_91c);
          if (pfVar8 == (floating_point_string *)0x0) goto LAB_004613dc;
          if ((floating_point_string *)0x72 < local_1d8) goto LAB_004613ab;
          (&local_1d4)[(int)local_1d8] = pfVar8;
          local_91c = local_1d8 + 1;
          local_1d8 = local_91c;
        }
      }
      if (local_920 != (floating_point_string *)0x0) {
        pfVar12 = (floating_point_string *)0x0;
        pfVar8 = local_920;
        if (local_91c != (floating_point_string *)0x0) {
          do {
            ppfVar2 = &local_1d4 + (int)pfVar12;
            pfVar6 = *ppfVar2;
            *ppfVar2 = pfVar8 + (int)*ppfVar2;
            pfVar8 = (floating_point_string *)(uint)CARRY4((uint)pfVar6,(uint)pfVar8);
            local_91c = local_1d8;
            pfVar12 = pfVar12 + 1;
          } while (pfVar12 != local_1d8);
        }
        if (pfVar8 != (floating_point_string *)0x0) {
          if (local_91c < (floating_point_string *)0x73) {
            (&local_1d4)[(int)local_91c] = pfVar8;
            local_91c = local_1d8 + 1;
            local_1d8 = local_91c;
          }
          else {
            local_748 = (floating_point_string *)0x0;
            local_1d8 = (floating_point_string *)0x0;
            _memcpy_s(&local_1d4,0x1cc,local_744,0);
            local_91c = local_1d8;
          }
        }
      }
    }
  }
  if (local_938 == (floating_point_string *)0x0) {
LAB_00461914:
    if (local_91c == (floating_point_string *)0x0) goto LAB_0046191c;
    pfVar8 = (&local_1d4)[(int)(local_91c + -1)];
    local_938 = (floating_point_string *)0x0;
    iVar7 = 0x1f;
    if (pfVar8 != (floating_point_string *)0x0) {
      for (; (uint)pfVar8 >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (pfVar8 == (floating_point_string *)0x0) {
      iVar7 = 0;
    }
    else {
      iVar7 = iVar7 + 1;
    }
    local_948 = (floating_point_string *)((int)(local_91c + -1) * 0x20 + iVar7);
  }
  else {
    local_94c = (uint)local_938 % 10;
    pfVar8 = local_91c;
    for (local_92c = (floating_point_string *)((uint)local_938 / 10); local_91c = pfVar8,
        local_92c != (floating_point_string *)0x0; local_92c = local_92c + -(int)local_948) {
      local_948 = local_92c;
      if ((floating_point_string *)0x26 < local_92c) {
        local_948 = (floating_point_string *)0x26;
      }
      uVar11 = (uint)(byte)(&DAT_00484f56)[(int)local_948 * 4];
      bVar4 = (&DAT_00484f57)[(int)local_948 * 4];
      local_748 = (floating_point_string *)(uVar11 + bVar4);
      _memset(local_744,0,uVar11 * 4);
      FUN_0045c870((uint *)(local_744 + uVar11),
                   (uint *)(&DAT_00484650 +
                           (uint)*(ushort *)(&DAT_00484f54 + (int)local_948 * 4) * 4),
                   (uint)bVar4 << 2);
      pfVar12 = local_1d4;
      if (local_748 < (floating_point_string *)0x2) {
        if (local_744[0] == (floating_point_string *)0x0) {
          local_918 = (floating_point_string *)0x0;
          ppfVar2 = local_914;
LAB_004615bc:
          local_1d8 = (floating_point_string *)0x0;
          _memcpy_s(&local_1d4,0x1cc,ppfVar2,0);
        }
        else {
          if ((local_744[0] == (floating_point_string *)0x1) ||
             (pfVar8 == (floating_point_string *)0x0)) {
            bVar14 = true;
            goto LAB_004618a5;
          }
          pfVar6 = (floating_point_string *)0x0;
          pfVar12 = (floating_point_string *)0x0;
          do {
            lVar15 = ZEXT48(local_744[0]) * ZEXT48((&local_1d4)[(int)pfVar12]) + ZEXT48(pfVar6);
            (&local_1d4)[(int)pfVar12] = (floating_point_string *)lVar15;
            pfVar6 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
            pfVar12 = pfVar12 + 1;
          } while (pfVar12 != pfVar8);
LAB_004616bc:
          if (pfVar6 != (floating_point_string *)0x0) {
            if ((floating_point_string *)0x72 < local_1d8) {
              local_748 = (floating_point_string *)0x0;
              local_1d8 = (floating_point_string *)0x0;
              _memcpy_s(&local_1d4,0x1cc,local_744,0);
              bVar14 = false;
              local_91c = local_1d8;
              goto LAB_004618a5;
            }
            (&local_1d4)[(int)local_1d8] = pfVar6;
            local_1d8 = local_1d8 + 1;
          }
        }
        bVar14 = true;
        local_91c = local_1d8;
      }
      else if (pfVar8 < (floating_point_string *)0x2) {
        local_1d8 = local_748;
        _memcpy_s(&local_1d4,0x1cc,local_744,(int)local_748 << 2);
        if (pfVar12 == (floating_point_string *)0x0) {
          local_748 = (floating_point_string *)0x0;
          ppfVar2 = local_744;
          goto LAB_004615bc;
        }
        bVar14 = true;
        local_91c = local_1d8;
        if ((pfVar12 != (floating_point_string *)0x1) && (local_1d8 != (floating_point_string *)0x0)
           ) {
          pfVar6 = (floating_point_string *)0x0;
          pfVar8 = (floating_point_string *)0x0;
          do {
            lVar15 = ZEXT48(pfVar12) * ZEXT48((&local_1d4)[(int)pfVar8]) + ZEXT48(pfVar6);
            (&local_1d4)[(int)pfVar8] = (floating_point_string *)lVar15;
            pfVar6 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
            pfVar8 = pfVar8 + 1;
          } while (pfVar8 != local_1d8);
          goto LAB_004616bc;
        }
      }
      else {
        local_920 = (floating_point_string *)local_744;
        local_93c = (floating_point_string *)&local_1d4;
        pfVar12 = pfVar8;
        local_928 = local_748;
        if (pfVar8 <= local_748) {
          local_920 = (floating_point_string *)&local_1d4;
          local_93c = (floating_point_string *)local_744;
          pfVar12 = local_748;
          local_928 = pfVar8;
        }
        local_1d8 = (floating_point_string *)0x0;
        pfVar8 = (floating_point_string *)0x0;
        local_3a8 = (floating_point_string *)0x0;
        if (local_928 != (floating_point_string *)0x0) {
          local_920 = local_920 + -(int)local_3a4;
          do {
            local_938 = *(floating_point_string **)
                         ((int)local_3a4 + (int)(local_920 + (int)pfVar8 * 4));
            if (local_938 == (floating_point_string *)0x0) {
              if (pfVar8 == local_1d8) {
                local_3a4[(int)pfVar8] = (floating_point_string *)0x0;
                local_1d8 = pfVar8 + 1;
                local_3a8 = local_1d8;
              }
            }
            else {
              uVar11 = 0;
              local_934 = (floating_point_string *)0x0;
              pfVar6 = pfVar8;
              if (pfVar12 != (floating_point_string *)0x0) {
                do {
                  if (pfVar6 == (floating_point_string *)0x73) break;
                  if (pfVar6 == local_1d8) {
                    local_3a4[(int)pfVar6] = (floating_point_string *)0x0;
                    local_3a8 = local_934 + 1 + (int)pfVar8;
                  }
                  lVar15 = (ulonglong)*(uint *)(local_93c + (int)local_934 * 4) * ZEXT48(local_938)
                           + (ulonglong)uVar11;
                  uVar11 = (uint)lVar15;
                  ppfVar2 = local_3a4 + (int)pfVar6;
                  pfVar13 = *ppfVar2;
                  *ppfVar2 = *ppfVar2 + uVar11;
                  uVar11 = (int)((ulonglong)lVar15 >> 0x20) + (uint)CARRY4((uint)pfVar13,uVar11);
                  local_934 = local_934 + 1;
                  pfVar6 = pfVar6 + 1;
                  local_1d8 = local_3a8;
                } while (local_934 != pfVar12);
                do {
                  if (uVar11 == 0) break;
                  if (pfVar6 == (floating_point_string *)0x73) goto LAB_00461923;
                  if (pfVar6 == local_1d8) {
                    local_3a4[(int)pfVar6] = (floating_point_string *)0x0;
                    local_3a8 = pfVar6 + 1;
                  }
                  ppfVar2 = local_3a4 + (int)pfVar6;
                  pfVar13 = *ppfVar2;
                  *ppfVar2 = *ppfVar2 + uVar11;
                  uVar11 = (uint)CARRY4((uint)pfVar13,uVar11);
                  pfVar6 = pfVar6 + 1;
                  local_1d8 = local_3a8;
                } while( true );
              }
              if (pfVar6 == (floating_point_string *)0x73) {
LAB_00461923:
                local_918 = (floating_point_string *)0x0;
                local_1d8 = (floating_point_string *)0x0;
                _memcpy_s(&local_1d4,0x1cc,local_914,0);
                bVar14 = false;
                goto LAB_00461899;
              }
            }
            pfVar8 = pfVar8 + 1;
          } while (pfVar8 != local_928);
        }
        _memcpy_s(&local_1d4,0x1cc,local_3a4,(int)local_1d8 << 2);
        bVar14 = true;
LAB_00461899:
        local_91c = local_1d8;
      }
LAB_004618a5:
      if (!bVar14) goto LAB_004619ca;
      pfVar8 = local_91c;
    }
    if (local_94c == 0) goto LAB_00461914;
    uVar11 = *(uint *)(&DAT_00484fec + local_94c * 2);
    if (uVar11 == 0) {
      local_748 = (floating_point_string *)0x0;
      local_1d8 = (floating_point_string *)0x0;
      _memcpy_s(&local_1d4,0x1cc,local_744,0);
      local_91c = local_1d8;
      goto LAB_00461914;
    }
    if (uVar11 == 1) goto LAB_00461914;
    if (pfVar8 != (floating_point_string *)0x0) {
      pfVar12 = (floating_point_string *)0x0;
      pfVar6 = (floating_point_string *)0x0;
      do {
        lVar15 = (ulonglong)uVar11 * ZEXT48((&local_1d4)[(int)pfVar6]) + ZEXT48(pfVar12);
        (&local_1d4)[(int)pfVar6] = (floating_point_string *)lVar15;
        pfVar12 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
        pfVar6 = pfVar6 + 1;
      } while (pfVar6 != pfVar8);
      local_91c = local_1d8;
      if (pfVar12 != (floating_point_string *)0x0) {
        local_91c = pfVar8;
        if ((floating_point_string *)0x72 < local_1d8) {
LAB_004619ca:
          local_1d8 = (floating_point_string *)0x0;
          local_748 = (floating_point_string *)0x0;
          _memcpy_s(&local_1d4,0x1cc,local_744,0);
          assemble_floating_point_infinity((bool)local_954[0x308],local_95c);
          return 3;
        }
        (&local_1d4)[(int)local_1d8] = pfVar12;
        local_1d8 = local_1d8 + 1;
        local_91c = local_1d8;
      }
      goto LAB_00461914;
    }
LAB_0046191c:
    local_948 = (floating_point_string *)0x0;
  }
  if ((local_958 <= local_948) || (local_924 == (floating_point_string *)0x0)) {
    bVar14 = local_924 != (floating_point_string *)0x0;
    fVar17 = local_954[0x308];
    goto LAB_00462b87;
  }
  pfVar8 = (floating_point_string *)0x0;
  local_920 = (floating_point_string *)0x0;
  uVar11 = 0;
  local_578 = (floating_point_string *)0x0;
  local_928 = (floating_point_string *)0x0;
  if (local_930 != local_940) {
    do {
      pfVar12 = local_928;
      pfVar6 = local_930;
      if (uVar11 == 9) {
        if (pfVar8 != (floating_point_string *)0x0) {
          pfVar6 = (floating_point_string *)0x0;
          pfVar13 = (floating_point_string *)0x0;
          do {
            lVar15 = ZEXT48(local_574[(int)pfVar13]) * 1000000000 + ZEXT48(pfVar6);
            local_574[(int)pfVar13] = (floating_point_string *)lVar15;
            pfVar6 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
            pfVar13 = pfVar13 + 1;
          } while (pfVar13 != pfVar8);
          pfVar8 = local_578;
          if (pfVar6 != (floating_point_string *)0x0) {
            if (local_578 < (floating_point_string *)0x73) {
              local_574[(int)local_578] = pfVar6;
              local_578 = local_578 + 1;
              pfVar8 = local_578;
            }
            else {
              local_748 = (floating_point_string *)0x0;
              local_578 = (floating_point_string *)0x0;
              _memcpy_s(local_574,0x1cc,local_744,0);
              pfVar8 = local_578;
            }
          }
        }
        pfVar6 = local_930;
        if (pfVar12 != (floating_point_string *)0x0) {
          pfVar13 = (floating_point_string *)0x0;
          if (pfVar8 != (floating_point_string *)0x0) {
            do {
              ppfVar2 = local_574 + (int)pfVar13;
              pfVar8 = *ppfVar2;
              *ppfVar2 = pfVar12 + (int)*ppfVar2;
              pfVar12 = (floating_point_string *)(uint)CARRY4((uint)pfVar8,(uint)pfVar12);
              pfVar13 = pfVar13 + 1;
              pfVar8 = local_578;
            } while (pfVar13 != local_578);
          }
          if (pfVar12 != (floating_point_string *)0x0) {
            if (pfVar8 < (floating_point_string *)0x73) {
              local_574[(int)pfVar8] = pfVar12;
              local_578 = local_578 + 1;
              pfVar8 = local_578;
            }
            else {
              local_748 = (floating_point_string *)0x0;
              local_578 = (floating_point_string *)0x0;
              _memcpy_s(local_574,0x1cc,local_744,0);
              pfVar8 = local_578;
            }
          }
        }
        local_928 = (floating_point_string *)0x0;
        uVar11 = 0;
      }
      local_928 = (floating_point_string *)((int)local_928 * 10 + (uint)(byte)*pfVar6);
      uVar11 = uVar11 + 1;
      local_930 = pfVar6 + 1;
    } while (local_930 != local_940);
    local_920 = pfVar8;
    if (uVar11 != 0) {
      local_950 = uVar11 % 10;
      for (local_93c = (floating_point_string *)(uVar11 / 10);
          local_93c != (floating_point_string *)0x0; local_93c = local_93c + -(int)local_92c) {
        local_92c = local_93c;
        if ((floating_point_string *)0x26 < local_93c) {
          local_92c = (floating_point_string *)0x26;
        }
        uVar11 = (uint)(byte)(&DAT_00484f56)[(int)local_92c * 4];
        bVar4 = (&DAT_00484f57)[(int)local_92c * 4];
        local_748 = (floating_point_string *)(uVar11 + bVar4);
        _memset(local_744,0,uVar11 * 4);
        FUN_0045c870((uint *)(local_744 + uVar11),
                     (uint *)(&DAT_00484650 +
                             (uint)*(ushort *)(&DAT_00484f54 + (int)local_92c * 4) * 4),
                     (uint)bVar4 << 2);
        pfVar12 = local_574[0];
        if (local_748 < (floating_point_string *)0x2) {
          if (local_744[0] == (floating_point_string *)0x0) {
            local_918 = (floating_point_string *)0x0;
            local_578 = (floating_point_string *)0x0;
            rVar18 = 0;
            ppfVar2 = local_914;
            goto LAB_00461ef8;
          }
          if ((local_744[0] == (floating_point_string *)0x1) ||
             (pfVar8 == (floating_point_string *)0x0)) {
            bVar14 = true;
          }
          else {
            pfVar6 = (floating_point_string *)0x0;
            pfVar12 = (floating_point_string *)0x0;
            do {
              lVar15 = ZEXT48(local_744[0]) * ZEXT48(local_574[(int)pfVar12]) + ZEXT48(pfVar6);
              local_574[(int)pfVar12] = (floating_point_string *)lVar15;
              pfVar6 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
              pfVar12 = pfVar12 + 1;
            } while (pfVar12 != pfVar8);
LAB_00461c9a:
            if (pfVar6 != (floating_point_string *)0x0) {
              if ((floating_point_string *)0x72 < local_578) {
                local_748 = (floating_point_string *)0x0;
                local_578 = (floating_point_string *)0x0;
                _memcpy_s(local_574,0x1cc,local_744,0);
                bVar14 = false;
                pfVar8 = local_578;
                local_920 = local_578;
                goto LAB_00461f15;
              }
              local_574[(int)local_578] = pfVar6;
              local_578 = local_578 + 1;
            }
            bVar14 = true;
            pfVar8 = local_578;
            local_920 = local_578;
          }
        }
        else {
          if (pfVar8 < (floating_point_string *)0x2) {
            local_578 = local_748;
            _memcpy_s(local_574,0x1cc,local_744,(int)local_748 << 2);
            if (pfVar12 != (floating_point_string *)0x0) {
              bVar14 = true;
              local_920 = local_578;
              pfVar8 = local_578;
              if ((pfVar12 != (floating_point_string *)0x1) &&
                 (local_578 != (floating_point_string *)0x0)) {
                pfVar6 = (floating_point_string *)0x0;
                pfVar8 = (floating_point_string *)0x0;
                do {
                  lVar15 = ZEXT48(pfVar12) * ZEXT48(local_574[(int)pfVar8]) + ZEXT48(pfVar6);
                  local_574[(int)pfVar8] = (floating_point_string *)lVar15;
                  pfVar6 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
                  pfVar8 = pfVar8 + 1;
                } while (pfVar8 != local_578);
                goto LAB_00461c9a;
              }
              goto LAB_00461f15;
            }
            rVar18 = 0;
            local_748 = (floating_point_string *)0x0;
            local_578 = (floating_point_string *)0x0;
            ppfVar2 = local_744;
          }
          else {
            ppfVar2 = local_744;
            if (local_748 < pfVar8) {
              local_940 = (floating_point_string *)local_574;
            }
            else {
              ppfVar2 = local_574;
              local_940 = (floating_point_string *)local_744;
            }
            local_930 = local_748;
            pfVar12 = pfVar8;
            if (local_748 >= pfVar8) {
              pfVar12 = local_748;
              local_930 = pfVar8;
            }
            local_578 = (floating_point_string *)0x0;
            pfVar8 = (floating_point_string *)0x0;
            local_3a8 = (floating_point_string *)0x0;
            if (local_930 != (floating_point_string *)0x0) {
              local_94c = (int)ppfVar2 - (int)local_3a4;
              do {
                local_938 = *(floating_point_string **)
                             ((int)local_3a4 + local_94c + (int)pfVar8 * 4);
                if (local_938 == (floating_point_string *)0x0) {
                  if (pfVar8 == local_578) {
                    local_3a4[(int)pfVar8] = (floating_point_string *)0x0;
                    local_578 = pfVar8 + 1;
                    local_3a8 = local_578;
                  }
                }
                else {
                  uVar11 = 0;
                  local_934 = (floating_point_string *)0x0;
                  pfVar6 = pfVar8;
                  if (pfVar12 != (floating_point_string *)0x0) {
                    do {
                      if (pfVar6 == (floating_point_string *)0x73) break;
                      if (pfVar6 == local_578) {
                        local_3a4[(int)pfVar6] = (floating_point_string *)0x0;
                        local_3a8 = local_934 + 1 + (int)pfVar8;
                      }
                      lVar15 = (ulonglong)*(uint *)(local_940 + (int)local_934 * 4) *
                               ZEXT48(local_938) + (ulonglong)uVar11;
                      uVar11 = (uint)lVar15;
                      ppfVar2 = local_3a4 + (int)pfVar6;
                      pfVar13 = *ppfVar2;
                      *ppfVar2 = *ppfVar2 + uVar11;
                      uVar11 = (int)((ulonglong)lVar15 >> 0x20) + (uint)CARRY4((uint)pfVar13,uVar11)
                      ;
                      local_934 = local_934 + 1;
                      pfVar6 = pfVar6 + 1;
                      local_578 = local_3a8;
                    } while (local_934 != pfVar12);
                    do {
                      if (uVar11 == 0) break;
                      if (pfVar6 == (floating_point_string *)0x73) goto LAB_00461fac;
                      if (pfVar6 == local_578) {
                        local_3a4[(int)pfVar6] = (floating_point_string *)0x0;
                        local_3a8 = pfVar6 + 1;
                      }
                      ppfVar2 = local_3a4 + (int)pfVar6;
                      pfVar13 = *ppfVar2;
                      *ppfVar2 = *ppfVar2 + uVar11;
                      uVar11 = (uint)CARRY4((uint)pfVar13,uVar11);
                      pfVar6 = pfVar6 + 1;
                      local_578 = local_3a8;
                    } while( true );
                  }
                  if (pfVar6 == (floating_point_string *)0x73) {
LAB_00461fac:
                    local_918 = (floating_point_string *)0x0;
                    local_578 = (floating_point_string *)0x0;
                    _memcpy_s(local_574,0x1cc,local_914,0);
                    bVar14 = false;
                    pfVar8 = local_578;
                    local_920 = local_578;
                    goto LAB_00461f15;
                  }
                }
                pfVar8 = pfVar8 + 1;
              } while (pfVar8 != local_930);
            }
            rVar18 = (int)local_578 << 2;
            ppfVar2 = local_3a4;
          }
LAB_00461ef8:
          _memcpy_s(local_574,0x1cc,ppfVar2,rVar18);
          bVar14 = true;
          pfVar8 = local_578;
          local_920 = local_578;
        }
LAB_00461f15:
        if (!bVar14) goto LAB_00461ffe;
      }
      pfVar12 = local_920;
      if (local_950 != 0) {
        uVar11 = *(uint *)(&DAT_00484fec + local_950 * 2);
        if (uVar11 == 0) {
LAB_00461ffe:
          local_578 = (floating_point_string *)0x0;
          local_748 = (floating_point_string *)0x0;
          _memcpy_s(local_574,0x1cc,local_744,0);
          pfVar8 = local_578;
          pfVar12 = local_578;
        }
        else if ((uVar11 != 1) && (pfVar8 != (floating_point_string *)0x0)) {
          pfVar6 = (floating_point_string *)0x0;
          pfVar12 = (floating_point_string *)0x0;
          do {
            lVar15 = (ulonglong)uVar11 * ZEXT48(local_574[(int)pfVar12]) + ZEXT48(pfVar6);
            local_574[(int)pfVar12] = (floating_point_string *)lVar15;
            pfVar6 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
            pfVar12 = pfVar12 + 1;
          } while (pfVar12 != pfVar8);
          pfVar8 = local_578;
          pfVar12 = local_578;
          if (pfVar6 != (floating_point_string *)0x0) {
            if ((floating_point_string *)0x72 < local_578) goto LAB_00461ffe;
            local_574[(int)local_578] = pfVar6;
            local_578 = local_578 + 1;
            pfVar8 = local_578;
            pfVar12 = local_578;
          }
        }
      }
      local_920 = pfVar12;
      if (local_928 != (floating_point_string *)0x0) {
        pfVar6 = (floating_point_string *)0x0;
        pfVar12 = local_928;
        if (pfVar8 != (floating_point_string *)0x0) {
          do {
            ppfVar2 = local_574 + (int)pfVar6;
            pfVar8 = *ppfVar2;
            *ppfVar2 = pfVar12 + (int)*ppfVar2;
            pfVar12 = (floating_point_string *)(uint)CARRY4((uint)pfVar8,(uint)pfVar12);
            local_920 = local_578;
            pfVar6 = pfVar6 + 1;
            pfVar8 = local_578;
          } while (pfVar6 != local_578);
        }
        if (pfVar12 != (floating_point_string *)0x0) {
          if (pfVar8 < (floating_point_string *)0x73) {
            local_574[(int)pfVar8] = pfVar12;
            local_578 = local_578 + 1;
            pfVar8 = local_578;
            local_920 = local_578;
          }
          else {
            local_748 = (floating_point_string *)0x0;
            local_578 = (floating_point_string *)0x0;
            _memcpy_s(local_574,0x1cc,local_744,0);
            pfVar8 = local_578;
            local_920 = local_578;
          }
        }
      }
    }
  }
  local_93c = local_924;
  if (*(int *)local_954 < 0) {
    local_93c = local_924 + -*(int *)local_954;
  }
  local_3a4[1] = (floating_point_string *)0x0;
  local_950 = (uint)local_93c % 10;
  local_3a4[0] = (floating_point_string *)0x1;
  local_924 = (floating_point_string *)0x1;
  local_3a8 = (floating_point_string *)0x1;
  for (local_93c = (floating_point_string *)((uint)local_93c / 10);
      local_93c != (floating_point_string *)0x0; local_93c = local_93c + -(int)local_934) {
    local_934 = local_93c;
    if ((floating_point_string *)0x26 < local_93c) {
      local_934 = (floating_point_string *)0x26;
    }
    uVar11 = (uint)(byte)(&DAT_00484f56)[(int)local_934 * 4];
    bVar4 = (&DAT_00484f57)[(int)local_934 * 4];
    local_748 = (floating_point_string *)(uVar11 + bVar4);
    _memset(local_744,0,uVar11 * 4);
    FUN_0045c870((uint *)(local_744 + uVar11),
                 (uint *)(&DAT_00484650 + (uint)*(ushort *)(&DAT_00484f54 + (int)local_934 * 4) * 4)
                 ,(uint)bVar4 << 2);
    pfVar12 = local_3a4[0];
    if (local_748 < (floating_point_string *)0x2) {
      if (local_744[0] == (floating_point_string *)0x0) {
        local_918 = (floating_point_string *)0x0;
        ppfVar2 = local_914;
LAB_00462190:
        local_3a8 = (floating_point_string *)0x0;
        _memcpy_s(local_3a4,0x1cc,ppfVar2,0);
      }
      else {
        if ((local_744[0] == (floating_point_string *)0x1) ||
           (local_924 == (floating_point_string *)0x0)) {
          bVar14 = true;
          goto LAB_004624a7;
        }
        pfVar12 = (floating_point_string *)0x0;
        pfVar6 = (floating_point_string *)0x0;
        do {
          lVar15 = ZEXT48(local_744[0]) * ZEXT48(local_3a4[(int)pfVar6]) + ZEXT48(pfVar12);
          local_3a4[(int)pfVar6] = (floating_point_string *)lVar15;
          pfVar12 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
          pfVar6 = pfVar6 + 1;
        } while (pfVar6 != local_924);
LAB_004622b6:
        if (pfVar12 != (floating_point_string *)0x0) {
          if ((floating_point_string *)0x72 < local_3a8) {
            local_748 = (floating_point_string *)0x0;
            local_3a8 = (floating_point_string *)0x0;
            _memcpy_s(local_3a4,0x1cc,local_744,0);
            bVar14 = false;
            local_924 = local_3a8;
            goto LAB_004624a7;
          }
          local_3a4[(int)local_3a8] = pfVar12;
          local_3a8 = local_3a8 + 1;
        }
      }
      bVar14 = true;
      local_924 = local_3a8;
    }
    else if (local_924 < (floating_point_string *)0x2) {
      local_3a8 = local_748;
      local_938 = local_3a4[0];
      _memcpy_s(local_3a4,0x1cc,local_744,(int)local_748 << 2);
      if (pfVar12 == (floating_point_string *)0x0) {
        local_748 = (floating_point_string *)0x0;
        ppfVar2 = local_744;
        goto LAB_00462190;
      }
      bVar14 = true;
      local_924 = local_3a8;
      if ((pfVar12 != (floating_point_string *)0x1) && (local_3a8 != (floating_point_string *)0x0))
      {
        pfVar12 = (floating_point_string *)0x0;
        pfVar6 = (floating_point_string *)0x0;
        do {
          lVar15 = ZEXT48(local_938) * ZEXT48(local_3a4[(int)pfVar6]) + ZEXT48(pfVar12);
          local_3a4[(int)pfVar6] = (floating_point_string *)lVar15;
          pfVar12 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
          pfVar6 = pfVar6 + 1;
          pfVar8 = local_920;
        } while (pfVar6 != local_3a8);
        goto LAB_004622b6;
      }
    }
    else {
      ppfVar2 = local_744;
      if (local_748 < local_924) {
        local_940 = (floating_point_string *)local_3a4;
      }
      else {
        ppfVar2 = local_3a4;
        local_940 = (floating_point_string *)local_744;
      }
      local_92c = local_748;
      pfVar12 = local_924;
      if (local_748 >= local_924) {
        local_92c = local_924;
        pfVar12 = local_748;
      }
      local_3a8 = (floating_point_string *)0x0;
      pfVar6 = (floating_point_string *)0x0;
      local_918 = (floating_point_string *)0x0;
      if (local_92c != (floating_point_string *)0x0) {
        local_94c = (int)ppfVar2 - (int)local_914;
        do {
          local_938 = *(floating_point_string **)((int)local_914 + local_94c + (int)pfVar6 * 4);
          if (local_938 == (floating_point_string *)0x0) {
            if (pfVar6 == local_3a8) {
              local_914[(int)pfVar6] = (floating_point_string *)0x0;
              local_3a8 = pfVar6 + 1;
              local_918 = local_3a8;
            }
          }
          else {
            local_930 = (floating_point_string *)0x0;
            local_928 = (floating_point_string *)0x0;
            pfVar13 = pfVar6;
            if (pfVar12 != (floating_point_string *)0x0) {
              do {
                if (pfVar13 == (floating_point_string *)0x73) break;
                if (pfVar13 == local_3a8) {
                  local_914[(int)pfVar13] = (floating_point_string *)0x0;
                  local_918 = local_928 + 1 + (int)pfVar6;
                }
                uVar11 = *(uint *)(local_940 + (int)local_928 * 4);
                uVar10 = (uint)((ulonglong)uVar11 * ZEXT48(local_938));
                ppfVar2 = local_914 + (int)pfVar13;
                pfVar9 = *ppfVar2;
                *ppfVar2 = local_930 + uVar10 + (int)*ppfVar2;
                local_930 = (floating_point_string *)
                            ((int)((ulonglong)uVar11 * ZEXT48(local_938) >> 0x20) +
                             (uint)CARRY4(uVar10,(uint)local_930) +
                            (uint)CARRY4((uint)pfVar9,(uint)(local_930 + uVar10)));
                local_928 = local_928 + 1;
                pfVar13 = pfVar13 + 1;
                local_3a8 = local_918;
              } while (local_928 != pfVar12);
              do {
                if (local_930 == (floating_point_string *)0x0) break;
                if (pfVar13 == (floating_point_string *)0x73) goto LAB_0046251f;
                if (pfVar13 == local_3a8) {
                  local_914[(int)pfVar13] = (floating_point_string *)0x0;
                  local_918 = pfVar13 + 1;
                }
                ppfVar2 = local_914 + (int)pfVar13;
                pfVar9 = *ppfVar2;
                *ppfVar2 = local_930 + (int)*ppfVar2;
                local_930 = (floating_point_string *)(uint)CARRY4((uint)pfVar9,(uint)local_930);
                pfVar13 = pfVar13 + 1;
                local_3a8 = local_918;
              } while( true );
            }
            if (pfVar13 == (floating_point_string *)0x73) {
LAB_0046251f:
              local_3a8 = (floating_point_string *)0x0;
              _memcpy_s(local_3a4,0x1cc,local_b2c,0);
              bVar14 = false;
              goto LAB_0046249b;
            }
          }
          pfVar6 = pfVar6 + 1;
        } while (pfVar6 != local_92c);
      }
      _memcpy_s(local_3a4,0x1cc,local_914,(int)local_3a8 << 2);
      bVar14 = true;
LAB_0046249b:
      local_924 = local_3a8;
    }
LAB_004624a7:
    if (!bVar14) goto LAB_004625d5;
  }
  if (local_950 != 0) {
    local_938 = *(floating_point_string **)(&DAT_00484fec + local_950 * 2);
    if (local_938 == (floating_point_string *)0x0) {
      local_3a8 = local_938;
      _memcpy_s(local_3a4,0x1cc,local_b2c,0);
LAB_0046250e:
      local_924 = local_3a8;
    }
    else if ((local_938 != (floating_point_string *)0x1) &&
            (local_924 != (floating_point_string *)0x0)) {
      pfVar12 = (floating_point_string *)0x0;
      pfVar6 = (floating_point_string *)0x0;
      do {
        lVar15 = ZEXT48(local_938) * ZEXT48(local_3a4[(int)pfVar6]) + ZEXT48(pfVar12);
        local_3a4[(int)pfVar6] = (floating_point_string *)lVar15;
        pfVar12 = (floating_point_string *)((ulonglong)lVar15 >> 0x20);
        pfVar6 = pfVar6 + 1;
      } while (pfVar6 != local_924);
      if (pfVar12 == (floating_point_string *)0x0) goto LAB_0046250e;
      if ((floating_point_string *)0x72 < local_3a8) {
LAB_004625d5:
        local_3a8 = (floating_point_string *)0x0;
        _memcpy_s(local_3a4,0x1cc,local_b2c,0);
        assemble_floating_point_zero((bool)local_954[0x308],local_95c);
        return 2;
      }
      local_3a4[(int)local_3a8] = pfVar12;
      local_924 = local_3a8 + 1;
      local_3a8 = local_924;
    }
  }
  if (pfVar8 == (floating_point_string *)0x0) {
    uVar11 = 0;
  }
  else {
    pfVar12 = local_574[(int)(pfVar8 + -1)];
    local_938 = (floating_point_string *)0x0;
    iVar7 = 0x1f;
    if (pfVar12 != (floating_point_string *)0x0) {
      for (; (uint)pfVar12 >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (pfVar12 == (floating_point_string *)0x0) {
      iVar7 = 0;
    }
    else {
      iVar7 = iVar7 + 1;
    }
    uVar11 = (int)(pfVar8 + -1) * 0x20 + iVar7;
  }
  if (local_924 == (floating_point_string *)0x0) {
    uVar10 = 0;
  }
  else {
    pfVar12 = local_3a4[(int)(local_924 + -1)];
    local_938 = (floating_point_string *)0x0;
    iVar7 = 0x1f;
    if (pfVar12 != (floating_point_string *)0x0) {
      for (; (uint)pfVar12 >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (pfVar12 == (floating_point_string *)0x0) {
      iVar7 = 0;
    }
    else {
      iVar7 = iVar7 + 1;
    }
    uVar10 = (int)(local_924 + -1) * 0x20 + iVar7;
  }
  local_930 = (floating_point_string *)(-(uint)(uVar11 < uVar10) & uVar10 - uVar11);
  if (local_930 != (floating_point_string *)0x0) {
    local_93c = (floating_point_string *)((uint)local_930 & 0x1f);
    pfVar6 = (floating_point_string *)((uint)local_930 >> 5);
    local_94c = 0x20 - (int)local_93c;
    local_928 = pfVar6;
    lVar15 = __allshl((byte)local_94c,0);
    pfVar12 = local_574[(int)(pfVar8 + -1)];
    local_950 = (int)lVar15 - 1;
    iVar7 = 0x1f;
    if (pfVar12 != (floating_point_string *)0x0) {
      for (; (uint)pfVar12 >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    local_938 = (floating_point_string *)~local_950;
    if (pfVar12 == (floating_point_string *)0x0) {
      iVar7 = 0;
    }
    else {
      iVar7 = iVar7 + 1;
    }
    local_934 = pfVar6 + (int)pfVar8;
    local_941 = (floating_point_string *)(0x20 - iVar7) < local_93c;
    if ((local_934 == (floating_point_string *)0x73) && ((bool)local_941)) {
      bVar14 = true;
    }
    else {
      bVar14 = false;
    }
    if (((floating_point_string *)0x73 < local_934) || (bVar14)) {
      local_578 = (floating_point_string *)0x0;
      _memcpy_s(local_574,0x1cc,local_b2c,0);
      pfVar8 = local_578;
    }
    else {
      if ((floating_point_string *)0x71 < local_934) {
        local_934 = (floating_point_string *)0x72;
      }
      local_92c = local_934;
      if (local_934 != (floating_point_string *)0xffffffff) {
        pfVar12 = local_934 + -(int)local_928;
        ppfVar2 = local_574 + (int)pfVar12;
        do {
          pfVar6 = local_928;
          if (local_92c < local_928) break;
          if (pfVar12 < pfVar8) {
            local_940 = *ppfVar2;
          }
          else {
            local_940 = (floating_point_string *)0x0;
          }
          if (pfVar12 + -1 < pfVar8) {
            pfVar8 = ppfVar2[-1];
          }
          else {
            pfVar8 = (floating_point_string *)0x0;
          }
          ppfVar2 = ppfVar2 + -1;
          local_574[(int)local_92c] =
               (floating_point_string *)
               (((uint)pfVar8 & (uint)local_938) >> ((byte)local_94c & 0x1f) |
               ((uint)local_940 & local_950) << ((byte)local_93c & 0x1f));
          local_92c = local_92c + -1;
          pfVar12 = pfVar12 + -1;
          pfVar8 = local_578;
        } while (local_92c != (floating_point_string *)0xffffffff);
      }
      if (pfVar6 != (floating_point_string *)0x0) {
        ppfVar2 = local_574;
        for (; pfVar6 != (floating_point_string *)0x0; pfVar6 = pfVar6 + -1) {
          *ppfVar2 = (floating_point_string *)0x0;
          ppfVar2 = ppfVar2 + 1;
        }
      }
      local_578 = local_934 + 1;
      if (!(bool)local_941) {
        local_578 = local_934;
      }
      pfVar8 = local_578;
    }
  }
  local_958 = local_958 + -(int)local_948;
  pfVar12 = local_958;
  if (local_948 != (floating_point_string *)0x0) {
    if (local_958 < local_930) {
      bVar14 = true;
      fVar17 = local_954[0x308];
LAB_00462b87:
      SVar3 = assemble_floating_point_value_from_big_integer
                        ((big_integer *)&local_1d8,(uint)local_948,(bool)fVar17,bVar14,local_95c);
      return SVar3;
    }
    pfVar12 = local_958 + -(int)local_930;
  }
  if (pfVar8 <= local_924) {
    if (pfVar8 < local_924) {
LAB_004628a7:
      local_930 = local_930 + 1;
    }
    else {
      pfVar6 = pfVar8 + -1;
      if (pfVar6 != (floating_point_string *)0xffffffff) {
        do {
          if (local_574[(int)pfVar6] != local_3a4[(int)pfVar6]) break;
          pfVar6 = pfVar6 + -1;
        } while (pfVar6 != (floating_point_string *)0xffffffff);
        if ((pfVar6 != (floating_point_string *)0xffffffff) &&
           (local_574[(int)pfVar6] <= local_3a4[(int)pfVar6])) goto LAB_004628a7;
      }
    }
  }
  local_93c = (floating_point_string *)((uint)pfVar12 & 0x1f);
  pfVar12 = (floating_point_string *)((uint)pfVar12 >> 5);
  local_94c = 0x20 - (int)local_93c;
  local_928 = pfVar12;
  lVar15 = __allshl((byte)local_94c,0);
  pfVar6 = local_574[(int)(pfVar8 + -1)];
  local_950 = (int)lVar15 - 1;
  iVar7 = 0x1f;
  if (pfVar6 != (floating_point_string *)0x0) {
    for (; (uint)pfVar6 >> iVar7 == 0; iVar7 = iVar7 + -1) {
    }
  }
  local_938 = (floating_point_string *)~local_950;
  if (pfVar6 == (floating_point_string *)0x0) {
    iVar7 = 0;
  }
  else {
    iVar7 = iVar7 + 1;
  }
  local_934 = pfVar12 + (int)pfVar8;
  local_941 = 0x20U - iVar7 < local_93c;
  if ((local_934 == (floating_point_string *)0x73) && ((bool)local_941)) {
    bVar14 = true;
  }
  else {
    bVar14 = false;
  }
  if (((floating_point_string *)0x73 < local_934) || (bVar14)) {
    local_578 = (floating_point_string *)0x0;
    _memcpy_s(local_574,0x1cc,local_b2c,0);
  }
  else {
    if ((floating_point_string *)0x71 < local_934) {
      local_934 = (floating_point_string *)0x72;
    }
    local_92c = local_934;
    if (local_934 != (floating_point_string *)0xffffffff) {
      pfVar6 = local_934 + -(int)local_928;
      ppfVar2 = local_574 + (int)pfVar6;
      do {
        pfVar12 = local_928;
        if (local_92c < local_928) break;
        if (pfVar6 < pfVar8) {
          local_940 = *ppfVar2;
        }
        else {
          local_940 = (floating_point_string *)0x0;
        }
        if (pfVar6 + -1 < pfVar8) {
          pfVar8 = ppfVar2[-1];
        }
        else {
          pfVar8 = (floating_point_string *)0x0;
        }
        ppfVar2 = ppfVar2 + -1;
        local_574[(int)local_92c] =
             (floating_point_string *)
             (((uint)pfVar8 & (uint)local_938) >> ((byte)local_94c & 0x1f) |
             ((uint)local_940 & local_950) << ((byte)local_93c & 0x1f));
        local_92c = local_92c + -1;
        pfVar6 = pfVar6 + -1;
        pfVar8 = local_578;
      } while (local_92c != (floating_point_string *)0xffffffff);
    }
    if (pfVar12 != (floating_point_string *)0x0) {
      ppfVar2 = local_574;
      for (; pfVar12 != (floating_point_string *)0x0; pfVar12 = pfVar12 + -1) {
        *ppfVar2 = (floating_point_string *)0x0;
        ppfVar2 = ppfVar2 + 1;
      }
    }
    local_578 = local_934;
    if ((bool)local_941) {
      local_578 = local_934 + 1;
    }
  }
  _Var16 = divide((big_integer *)&local_578,(big_integer *)&local_3a8);
  local_928 = (floating_point_string *)(_Var16 >> 0x20);
  uVar11 = (uint)_Var16;
  bVar14 = local_578 == (floating_point_string *)0x0;
  if (local_928 == (floating_point_string *)0x0) {
    iVar7 = 0x1f;
    if (uVar11 != 0) {
      for (; uVar11 >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (uVar11 == 0) {
      pfVar8 = (floating_point_string *)0x0;
    }
    else {
      pfVar8 = (floating_point_string *)(iVar7 + 1);
    }
  }
  else {
    iVar7 = 0x1f;
    if (local_928 != (floating_point_string *)0x0) {
      for (; (uint)local_928 >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (local_928 == (floating_point_string *)0x0) {
      iVar7 = 0;
    }
    else {
      iVar7 = iVar7 + 1;
    }
    pfVar8 = (floating_point_string *)(iVar7 + 0x20);
  }
  local_92c._0_1_ = bVar14;
  if (pfVar8 <= local_958) goto LAB_00462aee;
  bVar4 = (char)pfVar8 - (char)local_958;
  if (bVar14) {
    local_940 = (floating_point_string *)uVar11;
    lVar15 = __allshl(bVar4,0);
    _Var16 = CONCAT44(local_928,local_940);
    local_92c._0_1_ = 1;
    if (((uint)(lVar15 + -1) & uVar11) != 0 ||
        ((uint)((ulonglong)(lVar15 + -1) >> 0x20) & (uint)local_928) != 0) goto LAB_00462ad0;
  }
  else {
LAB_00462ad0:
    local_92c._0_1_ = 0;
  }
  local_940 = (floating_point_string *)_Var16;
  _Var16 = __aullshr(bVar4,(uint)(_Var16 >> 0x20));
LAB_00462aee:
  local_928 = (floating_point_string *)(_Var16 >> 0x20);
  local_940 = (floating_point_string *)_Var16;
  lVar15 = __allshl((byte)local_958,-(uint)((floating_point_string *)0x1 < local_91c) & local_1d0);
  if (local_948 == (floating_point_string *)0x0) {
    pfVar8 = (floating_point_string *)(-1 - (int)local_930);
  }
  else {
    pfVar8 = local_948 + -2;
  }
  SVar3 = assemble_floating_point_value
                    (lVar15 + CONCAT44(local_928,local_940),(int)pfVar8,(bool)local_954[0x308],
                     (bool)local_92c._0_1_,local_95c);
  return SVar3;
}



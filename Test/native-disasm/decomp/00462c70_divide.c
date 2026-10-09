// divide @ 00462c70 size=1192 callers=3

/* WARNING: Removing unreachable block (ram,0x00462fd7) */
/* WARNING: Removing unreachable block (ram,0x00462fb2) */
/* Library Function - Single Match
    unsigned __int64 __cdecl __crt_strtox::divide(struct __crt_strtox::big_integer &,struct
   __crt_strtox::big_integer const &)
   
   Library: Visual Studio 2015 Release */

__uint64 __cdecl __crt_strtox::divide(big_integer *param_1,big_integer *param_2)

{
  int iVar1;
  ulonglong uVar2;
  uint uVar3;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint uVar4;
  uint uVar5;
  big_integer *pbVar6;
  uint uVar7;
  big_integer *pbVar8;
  uint uVar9;
  undefined4 uVar10;
  bool bVar11;
  undefined8 uVar12;
  longlong lVar13;
  ulonglong uVar14;
  undefined1 local_21c [460];
  big_integer *local_50;
  undefined4 local_4c;
  undefined8 local_48;
  int local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_2c;
  int local_28;
  uint local_24;
  int local_20;
  int local_1c;
  uint local_18;
  big_integer *local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  iVar1 = *(int *)param_1;
  if (iVar1 == 0) {
    return 0;
  }
  local_3c = *(uint *)param_2;
  if (local_3c == 0) {
    return 0;
  }
  local_10 = iVar1 - 1;
  uVar7 = local_3c - 1;
  if (uVar7 == 0) {
    local_2c = *(uint *)(param_2 + 4);
    if (local_2c == 1) {
      uVar7 = *(uint *)(param_1 + 4);
      *(undefined4 *)param_1 = 0;
      _memcpy_s(param_1 + 4,0x1cc,local_21c,0);
      return (__uint64)uVar7;
    }
    if (local_10 == 0) {
      uVar7 = *(uint *)(param_1 + 4);
      *(undefined4 *)param_1 = 0;
      _memcpy_s(param_1 + 4,0x1cc,local_21c,0);
      uVar5 = uVar7 % local_2c;
      *(uint *)(param_1 + 4) = uVar5;
      *(uint *)param_1 = (uint)(uVar5 != 0);
      return (ulonglong)uVar7 / (ulonglong)local_2c;
    }
    uVar7 = 0;
    local_c = 0;
    local_8 = 0;
    local_14 = (big_integer *)0x0;
    if (local_10 != 0xffffffff) {
      pbVar6 = param_1 + iVar1 * 4;
      local_20 = iVar1;
      do {
        uVar12 = __aulldvrm(*(uint *)pbVar6,uVar7,local_2c,0);
        local_48 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),(undefined4)local_48);
        pbVar6 = pbVar6 + -4;
        local_14 = param_1;
        local_8 = local_c;
        local_20 = local_20 + -1;
        uVar7 = extraout_ECX;
        local_c = (int)uVar12;
      } while (local_20 != 0);
      local_20 = 0;
    }
    *(undefined4 *)param_1 = 0;
    _memcpy_s(param_1 + 4,0x1cc,local_21c,0);
    *(uint *)(param_1 + 4) = uVar7;
    *(big_integer **)(param_1 + 8) = local_14;
    *(uint *)param_1 = (local_14 != (big_integer *)0x0) + 1;
    return CONCAT44(local_8,local_c);
  }
  if (uVar7 <= local_10) {
    local_20 = local_10 - uVar7;
    if (local_20 <= (int)local_10) {
      pbVar6 = param_1 + iVar1 * 4;
      pbVar8 = param_2 + (local_10 - local_20) * 4 + 4;
      uVar7 = local_10;
      do {
        if (*(int *)pbVar8 != *(int *)pbVar6) {
          if (*(uint *)(param_1 + uVar7 * 4 + 4) <= *(uint *)(param_2 + (uVar7 - local_20) * 4 + 4))
          goto LAB_00462e26;
          break;
        }
        uVar7 = uVar7 - 1;
        pbVar8 = pbVar8 + -4;
        pbVar6 = pbVar6 + -4;
      } while (local_20 <= (int)uVar7);
    }
    local_20 = local_20 + 1;
LAB_00462e26:
    if (local_20 != 0) {
      local_38 = *(uint *)(param_2 + local_3c * 4);
      local_24 = *(uint *)(param_2 + local_3c * 4 + -4);
      local_28 = 0x1f;
      if (local_38 != 0) {
        for (; local_38 >> local_28 == 0; local_28 = local_28 + -1) {
        }
      }
      if (local_38 == 0) {
        local_28 = 0x20;
      }
      else {
        local_28 = 0x1f - local_28;
      }
      local_40 = 0x20 - local_28;
      if (local_28 != 0) {
        uVar7 = local_24 >> ((byte)local_40 & 0x1f);
        local_24 = local_24 << ((byte)local_28 & 0x1f);
        local_38 = local_38 << ((byte)local_28 & 0x1f) | uVar7;
        if (2 < local_3c) {
          local_24 = local_24 | *(uint *)(param_2 + local_3c * 4 + -8) >> ((byte)local_40 & 0x1f);
        }
      }
      local_4c = 0;
      local_20 = local_20 + -1;
      if (local_20 < 0) {
        uVar10 = 0;
        local_4c = 0;
      }
      else {
        local_14 = param_1 + local_20 * 4 + 4;
        local_c = local_20 + local_3c;
        local_50 = param_1 + local_c * 4 + -4;
        uVar10 = local_4c;
        do {
          local_4c = uVar10;
          if (local_10 < local_c) {
            local_34 = 0;
          }
          else {
            local_34 = *(uint *)(local_50 + 8);
          }
          uVar7 = *(uint *)(local_50 + 4);
          local_18 = *(uint *)local_50;
          local_2c = 0;
          local_8 = local_34;
          if (local_28 != 0) {
            uVar7 = local_18 >> ((byte)local_40 & 0x1f);
            lVar13 = __allshl((byte)local_28,local_34);
            local_8 = (uint)((ulonglong)lVar13 >> 0x20);
            uVar7 = uVar7 | (uint)lVar13;
            local_18 = local_18 << ((byte)local_28 & 0x1f);
            if (2 < local_c) {
              local_18 = local_18 |
                         *(uint *)(param_1 + (local_3c + local_20) * 4 + -8) >>
                         ((byte)local_40 & 0x1f);
            }
          }
          local_48 = __aulldvrm(uVar7,local_8,local_38,0);
          local_1c = (int)(local_48 >> 0x20);
          local_8 = (uint)local_48;
          local_2c = 0;
          uVar14 = (ulonglong)extraout_ECX_00;
          if (local_1c != 0) {
            lVar13 = __allmul((uint)(local_48 - 0xffffffff),(int)(local_48 - 0xffffffff >> 0x20),
                              local_38,0);
            uVar14 = lVar13 + uVar14;
            local_2c = (uint)(uVar14 >> 0x20);
            local_48 = 0xffffffff;
          }
          local_1c = (int)(local_48 >> 0x20);
          uVar7 = (uint)uVar14;
          uVar2 = local_48;
          if ((int)(uVar14 >> 0x20) == 0) {
            while( true ) {
              uVar5 = (uint)local_48;
              local_8 = local_18;
              uVar14 = __allmul(local_24,0,uVar5,(int)(local_48 >> 0x20));
              if (uVar14 <= CONCAT44(uVar7,local_8)) break;
              bVar11 = uVar5 != 0;
              uVar5 = uVar5 - 1;
              local_1c = local_1c + -1 + (uint)bVar11;
              bVar11 = CARRY4(uVar7,local_38);
              uVar7 = uVar7 + local_38;
              local_48 = CONCAT44(local_1c,uVar5);
              if (local_2c + bVar11 != 0) break;
              local_2c = 0;
            }
            uVar2 = CONCAT44(local_1c,uVar5);
          }
          if (uVar2 != 0) {
            uVar5 = 0;
            uVar7 = 0;
            if (local_3c != 0) {
              local_10 = local_3c;
              pbVar8 = local_14;
              pbVar6 = param_2;
              do {
                pbVar6 = pbVar6 + 4;
                lVar13 = (local_48 & 0xffffffff) * (ulonglong)*(uint *)pbVar6;
                uVar3 = (uint)lVar13;
                uVar9 = uVar5 + uVar3;
                uVar5 = uVar7 + (int)((ulonglong)lVar13 >> 0x20) + local_48._4_4_ * *(uint *)pbVar6
                        + (uint)CARRY4(uVar5,uVar3);
                uVar7 = 0;
                if (*(uint *)pbVar8 < uVar9) {
                  bVar11 = 0xfffffffe < uVar5;
                  uVar5 = uVar5 + 1;
                  uVar7 = (uint)bVar11;
                }
                *(uint *)pbVar8 = *(uint *)pbVar8 - uVar9;
                pbVar8 = pbVar8 + 4;
                local_10 = local_10 - 1;
              } while (local_10 != 0);
            }
            if ((uVar7 != 0) || (local_34 < uVar5)) {
              if (local_3c != 0) {
                uVar5 = 0;
                pbVar8 = local_14;
                uVar7 = local_3c;
                pbVar6 = param_2;
                do {
                  pbVar6 = pbVar6 + 4;
                  uVar3 = *(uint *)pbVar8;
                  uVar9 = *(uint *)pbVar6;
                  uVar4 = uVar3 + *(uint *)pbVar6;
                  *(uint *)pbVar8 = uVar4 + uVar5;
                  uVar5 = (uint)CARRY4(uVar3,uVar9) + (uint)CARRY4(uVar4,uVar5);
                  uVar7 = uVar7 - 1;
                  pbVar8 = pbVar8 + 4;
                } while (uVar7 != 0);
              }
              uVar2 = uVar2 - 1;
            }
            local_10 = local_c - 1;
          }
          local_1c = (int)(uVar2 >> 0x20);
          uVar10 = (undefined4)uVar2;
          local_14 = local_14 + -4;
          local_20 = local_20 + -1;
          local_50 = local_50 + -4;
          local_c = local_c - 1;
        } while (-1 < local_20);
      }
      uVar7 = local_10 + 1;
      if (uVar7 < *(uint *)param_1) {
        pbVar6 = param_1 + (local_10 + 2) * 4;
        uVar5 = uVar7;
        do {
          *(undefined4 *)pbVar6 = 0;
          pbVar6 = pbVar6 + 4;
          uVar5 = uVar5 + 1;
        } while (uVar5 < *(uint *)param_1);
      }
      *(uint *)param_1 = uVar7;
      while ((uVar7 != 0 && (*(int *)(param_1 + *(int *)param_1 * 4) == 0))) {
        uVar7 = *(int *)param_1 - 1;
        *(uint *)param_1 = uVar7;
      }
      return CONCAT44(local_4c,uVar10);
    }
  }
  return 0;
}



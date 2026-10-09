// FUN_0046872c @ 0046872c size=740 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

wchar_t * __cdecl FUN_0046872c(int param_1,int param_2,wchar_t *param_3)

{
  short *psVar1;
  short sVar2;
  ushort uVar3;
  bool bVar4;
  wchar_t *pwVar5;
  size_t sVar6;
  wchar_t *pwVar7;
  __acrt_ptd *p_Var8;
  uint uVar9;
  short *psVar10;
  ushort *puVar11;
  undefined4 *puVar12;
  int iVar13;
  undefined **ppuVar14;
  int iVar15;
  bool bVar16;
  int local_1c8;
  int local_1c0;
  __acrt_ptd local_1bc [172];
  __acrt_ptd local_110 [2];
  undefined2 local_10e [131];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  if (param_2 != 0) {
    if (param_3 == (wchar_t *)0x0) {
      return *(wchar_t **)(param_1 + (param_2 + 2) * 0x10);
    }
    pwVar5 = FUN_00468a11(param_1,param_2,param_3);
    return pwVar5;
  }
  bVar4 = true;
  iVar13 = 0;
  local_1c0 = 0;
  if (param_3 != (wchar_t *)0x0) {
    if (((*param_3 == L'L') && (param_3[1] == L'C')) && (param_3[2] == L'_')) {
      do {
        pwVar5 = _wcspbrk(param_3,L"=;");
        if (((pwVar5 == (wchar_t *)0x0) || (sVar6 = (int)pwVar5 - (int)param_3 >> 1, sVar6 == 0)) ||
           (*pwVar5 == L';')) {
          return (wchar_t *)0x0;
        }
        ppuVar14 = &PTR_u_LC_COLLATE_00485c84;
        local_1c8 = 1;
        do {
          iVar13 = _wcsncmp((wchar_t *)*ppuVar14,param_3,sVar6);
          if (iVar13 == 0) {
            psVar10 = (short *)*ppuVar14;
            psVar1 = psVar10 + 1;
            do {
              sVar2 = *psVar10;
              psVar10 = psVar10 + 1;
            } while (sVar2 != 0);
            if (sVar6 == (int)psVar10 - (int)psVar1 >> 1) break;
          }
          local_1c8 = local_1c8 + 1;
          ppuVar14 = ppuVar14 + 3;
        } while ((int)ppuVar14 < 0x485cb5);
        pwVar5 = pwVar5 + 1;
        sVar6 = _wcscspn(pwVar5,L";");
        if ((sVar6 == 0) && (*pwVar5 != L';')) {
          return (wchar_t *)0x0;
        }
        if (local_1c8 < 6) {
          iVar13 = FUN_0047002f((wchar_t *)local_110,0x83,pwVar5,sVar6);
          if (iVar13 != 0) {
                    /* WARNING: Subroutine does not return */
            __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
          }
          if (0x105 < sVar6 * 2) {
                    /* WARNING: Subroutine does not return */
            ___report_rangecheckfailure();
          }
          *(undefined2 *)(local_110 + sVar6 * 2) = 0;
          pwVar7 = FUN_00468a11(param_1,local_1c8,(wchar_t *)local_110);
          if (pwVar7 != (wchar_t *)0x0) {
            local_1c0 = local_1c0 + 1;
          }
        }
      } while ((pwVar5[sVar6] != L'\0') && (param_3 = pwVar5 + sVar6 + 1, *param_3 != L'\0'));
    }
    else {
      p_Var8 = FUN_0046815b(param_3,local_110,0x83,local_1bc,0x55,(undefined4 *)0x0);
      if (p_Var8 == (__acrt_ptd *)0x0) {
        return (wchar_t *)0x0;
      }
      puVar12 = (undefined4 *)(param_1 + 0x20);
      iVar15 = 0;
      do {
        if (iVar15 != 0) {
          puVar11 = (ushort *)*puVar12;
          p_Var8 = local_110;
          do {
            bVar16 = *(ushort *)p_Var8 < *puVar11;
            if (*(ushort *)p_Var8 != *puVar11) {
LAB_0046898a:
              uVar9 = -(uint)bVar16 | 1;
              goto LAB_00468991;
            }
            if (*(ushort *)p_Var8 == 0) break;
            uVar3 = *(ushort *)(p_Var8 + 2);
            bVar16 = uVar3 < puVar11[1];
            if (uVar3 != puVar11[1]) goto LAB_0046898a;
            p_Var8 = p_Var8 + 4;
            puVar11 = puVar11 + 2;
          } while (uVar3 != 0);
          uVar9 = 0;
LAB_00468991:
          if (uVar9 == 0) {
            iVar13 = iVar13 + 1;
          }
          else {
            pwVar5 = FUN_00468a11(param_1,iVar15,(wchar_t *)local_110);
            if (pwVar5 == (wchar_t *)0x0) {
              bVar4 = false;
            }
            else {
              iVar13 = iVar13 + 1;
            }
          }
        }
        iVar15 = iVar15 + 1;
        puVar12 = puVar12 + 4;
      } while (iVar15 < 6);
      local_1c0 = iVar13;
      if (bVar4) goto LAB_004689e7;
    }
    if (local_1c0 == 0) {
      return (wchar_t *)0x0;
    }
  }
LAB_004689e7:
  pwVar5 = (wchar_t *)FUN_00468593(param_1);
  return pwVar5;
}



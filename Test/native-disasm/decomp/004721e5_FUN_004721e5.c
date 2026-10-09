// FUN_004721e5 @ 004721e5 size=745 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint FUN_004721e5(wchar_t *param_1)

{
  short *psVar1;
  wchar_t wVar2;
  short sVar3;
  bool bVar4;
  __acrt_ptd *p_Var5;
  int iVar6;
  undefined3 extraout_var;
  uint uVar7;
  undefined3 extraout_var_00;
  short *psVar8;
  wchar_t *pwVar9;
  WCHAR local_88 [64];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  p_Var5 = FUN_0046aa74();
  iVar6 = ___acrt_GetLocaleInfoEx_16
                    (param_1,(-(uint)(*(int *)(p_Var5 + 100) != 0) & 0xfffff005) + 0x1002,local_88,
                     0x40);
  if (iVar6 == 0) {
    *(undefined4 *)(p_Var5 + 0x58) = 0;
    return 1;
  }
  iVar6 = __wcsicmp(*(wchar_t **)(p_Var5 + 0x54),local_88);
  if (iVar6 != 0) goto LAB_00472338;
  iVar6 = ___acrt_GetLocaleInfoEx_16
                    (param_1,(-(uint)(*(int *)(p_Var5 + 0x60) != 0) & 0xfffff002) + 0x1001,local_88,
                     0x40);
  if (iVar6 == 0) {
    *(undefined4 *)(p_Var5 + 0x58) = 0;
LAB_00472374:
    uVar7 = 1;
  }
  else {
    iVar6 = __wcsicmp(*(wchar_t **)(p_Var5 + 0x50),local_88);
    pwVar9 = param_1;
    if (iVar6 == 0) {
      *(uint *)(p_Var5 + 0x58) = *(uint *)(p_Var5 + 0x58) | 0x304;
      do {
        wVar2 = *pwVar9;
        pwVar9 = pwVar9 + 1;
      } while (wVar2 != L'\0');
LAB_004722b1:
      iVar6 = FUN_0047002f((wchar_t *)(p_Var5 + 0x2a0),0x55,param_1,
                           ((int)pwVar9 - (int)(param_1 + 1) >> 1) + 1);
      if (iVar6 != 0) goto LAB_004724c9;
    }
    else if (((byte)p_Var5[0x58] & 2) == 0) {
      if ((*(int *)(p_Var5 + 0x5c) == 0) ||
         (iVar6 = __wcsnicmp(*(wchar_t **)(p_Var5 + 0x50),local_88,*(size_t *)(p_Var5 + 0x5c)),
         iVar6 != 0)) {
        if ((((byte)p_Var5[0x58] & 1) != 0) ||
           (bVar4 = _TestDefaultCountry(param_1), CONCAT31(extraout_var,bVar4) == 0))
        goto LAB_00472338;
        *(uint *)(p_Var5 + 0x58) = *(uint *)(p_Var5 + 0x58) | 1;
        do {
          wVar2 = *pwVar9;
          pwVar9 = pwVar9 + 1;
        } while (wVar2 != L'\0');
      }
      else {
        *(uint *)(p_Var5 + 0x58) = *(uint *)(p_Var5 + 0x58) | 2;
        do {
          wVar2 = *pwVar9;
          pwVar9 = pwVar9 + 1;
        } while (wVar2 != L'\0');
      }
      goto LAB_004722b1;
    }
LAB_00472338:
    if ((*(uint *)(p_Var5 + 0x58) & 0x300) != 0x300) {
      iVar6 = ___acrt_GetLocaleInfoEx_16
                        (param_1,(-(uint)(*(int *)(p_Var5 + 0x60) != 0) & 0xfffff002) + 0x1001,
                         local_88,0x40);
      if (iVar6 == 0) {
        *(undefined4 *)(p_Var5 + 0x58) = 0;
        goto LAB_00472374;
      }
      iVar6 = __wcsicmp(*(wchar_t **)(p_Var5 + 0x50),local_88);
      if (iVar6 == 0) {
        *(uint *)(p_Var5 + 0x58) = *(uint *)(p_Var5 + 0x58) | 0x200;
        pwVar9 = param_1;
        if (*(int *)(p_Var5 + 0x60) == 0) {
          if (*(int *)(p_Var5 + 0x5c) != 0) {
            psVar8 = *(short **)(p_Var5 + 0x50);
            psVar1 = psVar8 + 1;
            do {
              sVar3 = *psVar8;
              psVar8 = psVar8 + 1;
            } while (sVar3 != 0);
            if ((int)psVar8 - (int)psVar1 >> 1 == *(int *)(p_Var5 + 0x5c)) {
              bVar4 = _TestDefaultCountry(param_1);
              if (CONCAT31(extraout_var_00,bVar4) == 0) {
                psVar8 = *(short **)(p_Var5 + 0x50);
                psVar1 = psVar8 + 1;
                do {
                  sVar3 = *psVar8;
                  psVar8 = psVar8 + 1;
                } while (sVar3 != 0);
                iVar6 = _GetPrimaryLen(*(ushort **)(p_Var5 + 0x50));
                if (iVar6 == (int)psVar8 - (int)psVar1 >> 1) goto LAB_004724a6;
              }
              *(uint *)(p_Var5 + 0x58) = *(uint *)(p_Var5 + 0x58) | 0x100;
              if (*(short *)(p_Var5 + 0x2a0) == 0) {
                do {
                  wVar2 = *pwVar9;
                  pwVar9 = pwVar9 + 1;
                } while (wVar2 != L'\0');
                goto LAB_004723d0;
              }
              goto LAB_004724a6;
            }
          }
          *(uint *)(p_Var5 + 0x58) = *(uint *)(p_Var5 + 0x58) | 0x100;
          if (*(short *)(p_Var5 + 0x2a0) == 0) {
            do {
              wVar2 = *pwVar9;
              pwVar9 = pwVar9 + 1;
            } while (wVar2 != L'\0');
            goto LAB_004723d0;
          }
        }
        else {
          *(uint *)(p_Var5 + 0x58) = *(uint *)(p_Var5 + 0x58) | 0x100;
          if (*(short *)(p_Var5 + 0x2a0) == 0) {
            do {
              wVar2 = *pwVar9;
              pwVar9 = pwVar9 + 1;
            } while (wVar2 != L'\0');
LAB_004723d0:
            iVar6 = FUN_0047002f((wchar_t *)(p_Var5 + 0x2a0),0x55,param_1,
                                 ((int)pwVar9 - (int)(param_1 + 1) >> 1) + 1);
            if (iVar6 != 0) {
LAB_004724c9:
                    /* WARNING: Subroutine does not return */
              __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
            }
          }
        }
      }
    }
LAB_004724a6:
    uVar7 = ~(*(uint *)(p_Var5 + 0x58) >> 2) & 1;
  }
  return uVar7;
}



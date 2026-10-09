// FUN_00468a11 @ 00468a11 size=971 callers=3

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

wchar_t * __cdecl FUN_00468a11(int param_1,int param_2,wchar_t *param_3)

{
  rsize_t _SizeInWords;
  wchar_t wVar1;
  undefined2 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  code *pcVar6;
  int *piVar7;
  __acrt_ptd *p_Var8;
  __acrt_ptd *p_Var9;
  __acrt_ptd *p_Var10;
  uint uVar11;
  undefined4 *_Memory;
  errno_t eVar12;
  wchar_t *pwVar13;
  BOOL BVar14;
  int iVar15;
  wchar_t *pwVar16;
  __crt_locale_pointers *p_Var17;
  int iVar18;
  bool bVar19;
  int local_2d0;
  int local_2c4;
  __crt_locale_pointers *local_2c0;
  __acrt_ptd local_2bc [172];
  WORD local_210 [128];
  wchar_t local_110 [132];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  p_Var8 = FUN_0046aa74();
  p_Var9 = p_Var8 + 0x278;
  p_Var10 = FUN_0046815b(param_3,(__acrt_ptd *)local_110,0x83,local_2bc,0x55,&local_2c4);
  if (p_Var10 != (__acrt_ptd *)0x0) {
    iVar18 = (param_2 + 2) * 0x10;
    pwVar13 = local_110;
    pwVar16 = *(wchar_t **)(iVar18 + param_1);
    do {
      local_2c0 = (__crt_locale_pointers *)0x0;
      bVar19 = (ushort)*pwVar13 < (ushort)*pwVar16;
      if (*pwVar13 != *pwVar16) {
LAB_00468ae5:
        uVar11 = -(uint)bVar19 | 1;
        goto LAB_00468aea;
      }
      if (*pwVar13 == L'\0') break;
      wVar1 = pwVar13[1];
      bVar19 = (ushort)wVar1 < (ushort)pwVar16[1];
      if (wVar1 != pwVar16[1]) goto LAB_00468ae5;
      pwVar13 = pwVar13 + 2;
      pwVar16 = pwVar16 + 2;
    } while (wVar1 != L'\0');
    uVar11 = 0;
LAB_00468aea:
    if (uVar11 == 0) {
      return *(wchar_t **)(iVar18 + param_1);
    }
    pwVar13 = local_110;
    do {
      wVar1 = *pwVar13;
      pwVar13 = pwVar13 + 1;
    } while (wVar1 != L'\0');
    _SizeInWords = ((int)pwVar13 - (int)(local_110 + 1) >> 1) + 1;
    _Memory = __malloc_base(_SizeInWords * 2 + 4);
    if (_Memory != (undefined4 *)0x0) {
      puVar2 = *(undefined2 **)(iVar18 + param_1);
      uVar3 = *(undefined4 *)(param_1 + 0xa0 + param_2 * 4);
      uVar4 = *(undefined4 *)(param_1 + 8);
      eVar12 = _wcscpy_s((wchar_t *)(_Memory + 1),_SizeInWords,local_110);
      if (eVar12 != 0) {
                    /* WARNING: Subroutine does not return */
        __invoke_watson((wchar_t *)local_2c0,(wchar_t *)local_2c0,(wchar_t *)local_2c0,
                        (uint)local_2c0,(uintptr_t)local_2c0);
      }
      *(undefined4 **)(iVar18 + param_1) = _Memory + 1;
      if ((local_110[0] == L'C') && (local_110[1] == 0)) {
        *(__crt_locale_pointers **)(param_1 + 0xa0 + param_2 * 4) = local_2c0;
      }
      else {
        pwVar13 = FUN_00467e68((wchar_t *)local_2bc);
        *(wchar_t **)(param_1 + 0xa0 + param_2 * 4) = pwVar13;
      }
      if (param_2 == 2) {
        *(int *)(param_1 + 8) = local_2c4;
        p_Var10 = p_Var9;
        p_Var17 = local_2c0;
        local_2d0 = *(int *)(p_Var8 + 0x298);
        local_2c4 = *(int *)(p_Var8 + 0x29c);
        do {
          if (*(int *)(param_1 + 8) == *(int *)p_Var10) {
            if (p_Var17 != (__crt_locale_pointers *)0x0) {
              *(int *)p_Var9 = *(int *)(p_Var9 + (int)p_Var17 * 8);
              *(undefined4 *)(p_Var8 + 0x27c) = *(undefined4 *)(p_Var8 + (int)p_Var17 * 8 + 0x27c);
              *(int *)(p_Var9 + (int)p_Var17 * 8) = local_2d0;
              *(int *)(p_Var8 + (int)p_Var17 * 8 + 0x27c) = local_2c4;
            }
            break;
          }
          p_Var17 = p_Var17 + 1;
          iVar15 = *(int *)p_Var10;
          iVar5 = *(int *)(p_Var10 + 4);
          *(int *)p_Var10 = local_2d0;
          *(int *)(p_Var10 + 4) = local_2c4;
          p_Var10 = p_Var10 + 8;
          local_2d0 = iVar15;
          local_2c4 = iVar5;
        } while ((int)p_Var17 < 5);
        if (p_Var17 == (__crt_locale_pointers *)0x5) {
          BVar14 = ___acrt_GetStringTypeA
                             (local_2c0,1,
                              "\x01\x02\x03\x04\x05\x06\a\b\t\n\v\f\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f"
                              ,0x7f,local_210,*(UINT *)(param_1 + 8),1);
          p_Var17 = local_2c0;
          if (BVar14 == 0) {
            *(__crt_locale_pointers **)(p_Var8 + 0x27c) = local_2c0;
          }
          else {
            do {
              local_210[(int)p_Var17] = local_210[(int)p_Var17] & 0x1ff;
              p_Var17 = p_Var17 + 1;
            } while (p_Var17 < (__crt_locale_pointers *)0x7f);
            iVar15 = _memcmp(local_210,PTR_DAT_0049d1f0,0xfe);
            *(uint *)(p_Var8 + 0x27c) = (uint)(iVar15 == 0);
          }
          *(int *)p_Var9 = *(int *)(param_1 + 8);
        }
        *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(p_Var8 + 0x27c);
      }
      else if (param_2 == 1) {
        *(int *)(param_1 + 0x10) = local_2c4;
      }
      else if (param_2 == 5) {
        *(int *)(param_1 + 0x14) = local_2c4;
      }
      pcVar6 = (code *)(&PTR_FUN_00485c80)[param_2 * 3];
      (*(code *)PTR_guard_check_icall_004805b0)(param_1);
      iVar15 = (*pcVar6)();
      if (iVar15 == 0) {
        if (puVar2 != &DAT_0049d2f0) {
          piVar7 = *(int **)(param_1 + 0x28 + param_2 * 0x10);
          LOCK();
          iVar15 = *piVar7 + -1;
          *piVar7 = iVar15;
          UNLOCK();
          if (iVar15 == 0) {
            FID_conflict__free(*(void **)(param_1 + 0x28 + param_2 * 0x10));
            FID_conflict__free(*(void **)(param_1 + 0x24 + param_2 * 0x10));
            FID_conflict__free(*(void **)(param_1 + 0xa0 + param_2 * 4));
            *(__crt_locale_pointers **)(iVar18 + param_1) = local_2c0;
            *(__crt_locale_pointers **)(param_1 + 0xa0 + param_2 * 4) = local_2c0;
          }
        }
        *_Memory = 1;
        pwVar13 = *(wchar_t **)(iVar18 + param_1);
        *(undefined4 **)(param_1 + 0x28 + param_2 * 0x10) = _Memory;
        return pwVar13;
      }
      *(undefined2 **)(iVar18 + param_1) = puVar2;
      FID_conflict__free(*(void **)(param_1 + 0xa0 + param_2 * 4));
      *(undefined4 *)(param_1 + 0xa0 + param_2 * 4) = uVar3;
      FID_conflict__free(_Memory);
      *(undefined4 *)(param_1 + 8) = uVar4;
    }
  }
  return (wchar_t *)0x0;
}



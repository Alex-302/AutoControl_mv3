// ___acrt_locale_initialize_ctype @ 0046615b size=926 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_locale_initialize_ctype
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___acrt_locale_initialize_ctype(undefined4 *param_1)

{
  BYTE *pBVar1;
  undefined4 *puVar2;
  byte bVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  LPCSTR pCVar7;
  BOOL BVar8;
  BYTE *pBVar9;
  uint uVar10;
  undefined4 uVar11;
  undefined4 *puVar12;
  undefined2 *puVar13;
  undefined4 *puVar14;
  undefined4 *local_4c;
  undefined4 local_48;
  undefined4 *local_44;
  undefined4 *local_40;
  LPWORD local_3c;
  undefined4 *local_38;
  LPCSTR local_34;
  uint local_30;
  undefined4 *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  _cpinfo local_1c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  uVar11 = 0;
  local_40 = param_1;
  local_20 = (undefined4 *)0x0;
  local_24 = (undefined4 *)0x0;
  local_28 = (undefined4 *)0x0;
  local_34 = (LPCSTR)0x0;
  local_4c = param_1;
  local_48 = 0;
  if ((wchar_t *)param_1[0x2a] == (wchar_t *)0x0) {
    piVar4 = (int *)param_1[0x23];
    if (piVar4 != (int *)0x0) {
      LOCK();
      *piVar4 = *piVar4 + -1;
      UNLOCK();
    }
    param_1[0x23] = 0;
    param_1[0x24] = 0;
    *param_1 = &DAT_00485698;
    param_1[0x25] = &DAT_00485918;
    param_1[0x26] = &DAT_00485a98;
    param_1[1] = 1;
    return 0;
  }
  local_2c = (undefined4 *)0x0;
  if ((param_1[2] != 0) ||
     (iVar6 = FUN_0046e1c8((__crt_locale_pointers *)&local_4c,0,(wchar_t *)param_1[0x2a],0x1004,
                           param_1 + 2), iVar6 == 0)) {
    local_2c = __calloc_base(1,4);
    FID_conflict__free((void *)0x0);
    local_20 = __calloc_base(0x180,2);
    FID_conflict__free((void *)0x0);
    local_24 = __calloc_base(0x180,1);
    FID_conflict__free((void *)0x0);
    local_28 = __calloc_base(0x180,1);
    FID_conflict__free((void *)0x0);
    pCVar7 = __calloc_base(0x101,1);
    local_34 = pCVar7;
    FID_conflict__free((void *)0x0);
    if ((local_2c != (undefined4 *)0x0) &&
       ((((local_20 != (undefined4 *)0x0 && (pCVar7 != (LPCSTR)0x0)) &&
         (local_24 != (undefined4 *)0x0)) && (local_28 != (undefined4 *)0x0)))) {
      iVar6 = 0;
      do {
        pCVar7[iVar6] = (CHAR)iVar6;
        iVar6 = iVar6 + 1;
      } while (iVar6 < 0x100);
      BVar8 = GetCPInfo(param_1[2],&local_1c);
      if ((BVar8 != 0) && (local_1c.MaxCharSize < 6)) {
        local_30 = local_1c.MaxCharSize & 0xffff;
        iVar6 = ___acrt_LCMapStringA
                          ((__crt_locale_pointers *)0x0,(wchar_t *)param_1[0x2a],0x100,pCVar7 + 1,
                           0xff,(char *)((int)local_24 + 0x81),0xff,param_1[2],0);
        if ((iVar6 != 0) &&
           (iVar6 = ___acrt_LCMapStringA
                              ((__crt_locale_pointers *)0x0,(wchar_t *)param_1[0x2a],0x200,
                               pCVar7 + 1,0xff,(char *)((int)local_28 + 0x81),0xff,param_1[2],0),
           iVar6 != 0)) {
          if ((1 < (int)local_30) && (local_1c.LeadByte[0] != '\0')) {
            pBVar9 = local_1c.LeadByte + 1;
            do {
              bVar3 = *pBVar9;
              if (bVar3 == 0) break;
              for (uVar10 = (uint)pBVar9[-1]; (int)uVar10 <= (int)(uint)bVar3; uVar10 = uVar10 + 1)
              {
                pCVar7[uVar10] = ' ';
                bVar3 = *pBVar9;
              }
              pBVar1 = pBVar9 + 1;
              pBVar9 = pBVar9 + 2;
            } while (*pBVar1 != 0);
          }
          local_3c = (LPWORD)(local_20 + 0x40);
          BVar8 = ___acrt_GetStringTypeA
                            ((__crt_locale_pointers *)0x0,1,pCVar7,0x100,local_3c,param_1[2],0);
          puVar5 = local_40;
          if (BVar8 != 0) {
            puVar2 = (undefined4 *)((int)local_20 + 0xfe);
            *(undefined2 *)puVar2 = 0;
            *(undefined1 *)((int)local_24 + 0x7f) = 0;
            local_44 = local_24 + 0x20;
            *(undefined1 *)((int)local_28 + 0x7f) = 0;
            *(undefined1 *)local_44 = 0;
            local_38 = local_28 + 0x20;
            *(undefined1 *)local_38 = 0;
            if ((1 < (int)local_30) && (local_1c.LeadByte[0] != '\0')) {
              pBVar9 = local_1c.LeadByte + 1;
              do {
                if (*pBVar9 == 0) break;
                uVar10 = (uint)pBVar9[-1];
                if (uVar10 <= *pBVar9) {
                  puVar13 = (undefined2 *)((int)local_20 + uVar10 * 2 + 0x100);
                  do {
                    uVar10 = uVar10 + 1;
                    *puVar13 = 0x8000;
                    puVar13 = puVar13 + 1;
                  } while ((int)uVar10 <= (int)(uint)*pBVar9);
                }
                pBVar1 = pBVar9 + 1;
                pBVar9 = pBVar9 + 2;
              } while (*pBVar1 != 0);
            }
            puVar12 = local_20 + 0x80;
            for (iVar6 = 0x3f; iVar6 != 0; iVar6 = iVar6 + -1) {
              *local_20 = *puVar12;
              puVar12 = puVar12 + 1;
              local_20 = local_20 + 1;
            }
            *(undefined2 *)local_20 = *(undefined2 *)puVar12;
            puVar12 = local_24 + 0x40;
            puVar14 = local_24;
            for (iVar6 = 0x1f; iVar6 != 0; iVar6 = iVar6 + -1) {
              *puVar14 = *puVar12;
              puVar12 = puVar12 + 1;
              puVar14 = puVar14 + 1;
            }
            *(undefined2 *)puVar14 = *(undefined2 *)puVar12;
            *(undefined1 *)((int)puVar14 + 2) = *(undefined1 *)((int)puVar12 + 2);
            puVar12 = local_28 + 0x40;
            puVar14 = local_28;
            for (iVar6 = 0x1f; iVar6 != 0; iVar6 = iVar6 + -1) {
              *puVar14 = *puVar12;
              puVar12 = puVar12 + 1;
              puVar14 = puVar14 + 1;
            }
            *(undefined2 *)puVar14 = *(undefined2 *)puVar12;
            *(undefined1 *)((int)puVar14 + 2) = *(undefined1 *)((int)puVar12 + 2);
            piVar4 = (int *)local_40[0x23];
            local_20 = puVar2;
            if (piVar4 != (int *)0x0) {
              LOCK();
              iVar6 = *piVar4;
              *piVar4 = iVar6 + -1;
              UNLOCK();
              if (iVar6 + -1 == 0) {
                FID_conflict__free((void *)(local_40[0x24] + -0xfe));
                FID_conflict__free((void *)(puVar5[0x25] + -0x80));
                FID_conflict__free((void *)(puVar5[0x26] + -0x80));
                FID_conflict__free((void *)puVar5[0x23]);
              }
            }
            *local_2c = 1;
            puVar5[0x23] = local_2c;
            *puVar5 = local_3c;
            puVar5[0x24] = local_20;
            puVar5[0x25] = local_44;
            puVar5[0x26] = local_38;
            puVar5[1] = local_30;
            goto LAB_0046649f;
          }
        }
      }
    }
  }
  FID_conflict__free(local_2c);
  FID_conflict__free(local_20);
  FID_conflict__free(local_24);
  FID_conflict__free(local_28);
  uVar11 = 1;
LAB_0046649f:
  FID_conflict__free(local_34);
  return uVar11;
}



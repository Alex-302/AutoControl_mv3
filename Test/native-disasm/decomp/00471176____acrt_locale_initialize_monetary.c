// ___acrt_locale_initialize_monetary @ 00471176 size=956 callers=1

/* Library Function - Single Match
    ___acrt_locale_initialize_monetary
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___acrt_locale_initialize_monetary(int param_1)

{
  char cVar1;
  wchar_t *pwVar2;
  int *piVar3;
  undefined **ppuVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  undefined4 uVar27;
  char *pcVar28;
  char *pcVar29;
  undefined **ppuVar30;
  int local_1c [2];
  undefined **local_14;
  undefined4 *local_10;
  undefined4 *local_c;
  undefined **local_8;
  
  local_10 = (undefined4 *)0x0;
  local_1c[0] = param_1;
  local_1c[1] = 0;
  if ((*(int *)(param_1 + 0xac) == 0) && (*(int *)(param_1 + 0xb0) == 0)) {
    local_c = (undefined4 *)0x0;
    ppuVar4 = &PTR_DAT_0049d180;
LAB_004714e5:
    puVar5 = local_10;
    piVar3 = *(int **)(param_1 + 0x84);
    if (piVar3 != (int *)0x0) {
      LOCK();
      *piVar3 = *piVar3 + -1;
      UNLOCK();
    }
    piVar3 = *(int **)(param_1 + 0x7c);
    if (piVar3 != (int *)0x0) {
      LOCK();
      iVar6 = *piVar3;
      *piVar3 = iVar6 + -1;
      UNLOCK();
      if (iVar6 + -1 == 0) {
        FID_conflict__free(*(void **)(param_1 + 0x88));
        FID_conflict__free(*(void **)(param_1 + 0x7c));
      }
    }
    *(undefined4 **)(param_1 + 0x7c) = local_c;
    uVar27 = 0;
    *(undefined4 **)(param_1 + 0x84) = puVar5;
    *(undefined ***)(param_1 + 0x88) = ppuVar4;
  }
  else {
    ppuVar4 = __calloc_base(1,0x50);
    local_8 = ppuVar4;
    FID_conflict__free((void *)0x0);
    if (ppuVar4 != (undefined **)0x0) {
      puVar5 = __calloc_base(1,4);
      local_c = puVar5;
      FID_conflict__free((void *)0x0);
      if (puVar5 == (undefined4 *)0x0) {
        FID_conflict__free(ppuVar4);
      }
      else {
        if (*(int *)(param_1 + 0xac) == 0) {
          ppuVar4 = &PTR_DAT_0049d180;
          ppuVar30 = local_8;
          for (iVar6 = 0x14; iVar6 != 0; iVar6 = iVar6 + -1) {
            *ppuVar30 = *ppuVar4;
            ppuVar4 = ppuVar4 + 1;
            ppuVar30 = ppuVar30 + 1;
          }
LAB_00471497:
          *local_8 = (undefined *)**(undefined4 **)(param_1 + 0x88);
          local_8[1] = *(undefined **)(*(int *)(param_1 + 0x88) + 4);
          local_8[2] = *(undefined **)(*(int *)(param_1 + 0x88) + 8);
          local_8[0xc] = *(undefined **)(*(int *)(param_1 + 0x88) + 0x30);
          local_8[0xd] = *(undefined **)(*(int *)(param_1 + 0x88) + 0x34);
          *local_c = 1;
          ppuVar4 = local_8;
          if (local_10 != (undefined4 *)0x0) {
            *local_10 = 1;
          }
          goto LAB_004714e5;
        }
        puVar5 = __calloc_base(1,4);
        local_10 = puVar5;
        FID_conflict__free((void *)0x0);
        if (puVar5 == (undefined4 *)0x0) {
          FID_conflict__free(ppuVar4);
          FID_conflict__free(local_c);
        }
        else {
          pwVar2 = *(wchar_t **)(param_1 + 0xac);
          iVar6 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,1,pwVar2,0x15,(int *)(ppuVar4 + 3))
          ;
          iVar7 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,1,pwVar2,0x14,(int *)(local_8 + 4))
          ;
          iVar8 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,1,pwVar2,0x16,(int *)(local_8 + 5))
          ;
          iVar9 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,1,pwVar2,0x17,(int *)(local_8 + 6))
          ;
          local_14 = local_8 + 7;
          iVar10 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,1,pwVar2,0x18,(int *)local_14);
          iVar11 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,1,pwVar2,0x50,(int *)(local_8 + 8)
                               );
          iVar12 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,1,pwVar2,0x51,(int *)(local_8 + 9)
                               );
          iVar13 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,0,pwVar2,0x1a,
                                (int *)(local_8 + 10));
          iVar14 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,0,pwVar2,0x19,
                                (int *)((int)local_8 + 0x29));
          iVar15 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,0,pwVar2,0x54,
                                (int *)((int)local_8 + 0x2a));
          iVar16 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,0,pwVar2,0x55,
                                (int *)((int)local_8 + 0x2b));
          iVar17 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,0,pwVar2,0x56,
                                (int *)(local_8 + 0xb));
          iVar18 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,0,pwVar2,0x57,
                                (int *)((int)local_8 + 0x2d));
          iVar19 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,0,pwVar2,0x52,
                                (int *)((int)local_8 + 0x2e));
          iVar20 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,0,pwVar2,0x53,
                                (int *)((int)local_8 + 0x2f));
          iVar21 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,2,pwVar2,0x15,
                                (int *)(local_8 + 0xe));
          iVar22 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,2,pwVar2,0x14,
                                (int *)(local_8 + 0xf));
          iVar23 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,2,pwVar2,0x16,
                                (int *)(local_8 + 0x10));
          iVar24 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,2,pwVar2,0x17,
                                (int *)(local_8 + 0x11));
          iVar25 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,2,pwVar2,0x50,
                                (int *)(local_8 + 0x12));
          iVar26 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,2,pwVar2,0x51,
                                (int *)(local_8 + 0x13));
          ppuVar4 = local_8;
          if (iVar26 == 0 &&
              (((((((((((((((((((iVar6 == 0 && iVar7 == 0) && iVar8 == 0) && iVar9 == 0) &&
                             iVar10 == 0) && iVar11 == 0) && iVar12 == 0) && iVar13 == 0) &&
                         iVar14 == 0) && iVar15 == 0) && iVar16 == 0) && iVar17 == 0) && iVar18 == 0
                     ) && iVar19 == 0) && iVar20 == 0) && iVar21 == 0) && iVar22 == 0) &&
                iVar23 == 0) && iVar24 == 0) && iVar25 == 0)) {
            pcVar28 = *local_14;
            while (*pcVar28 != '\0') {
              cVar1 = *pcVar28;
              if ((cVar1 < '0') || ('9' < cVar1)) {
                pcVar29 = pcVar28;
                if (cVar1 != ';') goto LAB_0047146d;
                do {
                  *pcVar29 = pcVar29[1];
                  pcVar29 = pcVar29 + 1;
                } while (*pcVar29 != '\0');
              }
              else {
                *pcVar28 = cVar1 + -0x30;
LAB_0047146d:
                pcVar28 = pcVar28 + 1;
              }
            }
            goto LAB_00471497;
          }
          ___acrt_locale_free_monetary((int)local_8);
          FID_conflict__free(ppuVar4);
          FID_conflict__free(local_c);
          FID_conflict__free(local_10);
        }
      }
    }
    uVar27 = 1;
  }
  return uVar27;
}



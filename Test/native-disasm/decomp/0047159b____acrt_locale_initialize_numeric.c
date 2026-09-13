// ___acrt_locale_initialize_numeric @ 0047159b size=540 callers=1

/* Library Function - Single Match
    ___acrt_locale_initialize_numeric
   
   Library: Visual Studio 2015 Release */

undefined ** __cdecl ___acrt_locale_initialize_numeric(int param_1)

{
  char cVar1;
  wchar_t *pwVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined **ppuVar10;
  char *pcVar11;
  undefined4 *puVar12;
  int local_1c [2];
  undefined4 *local_14;
  undefined **local_10;
  undefined4 *local_c;
  undefined **local_8;
  
  local_1c[0] = param_1;
  local_1c[1] = 0;
  if ((*(int *)(param_1 + 0xb0) == 0) && (*(int *)(param_1 + 0xac) == 0)) {
    puVar12 = (undefined4 *)0x0;
    local_c = (undefined4 *)0x0;
    ppuVar10 = &PTR_DAT_0049d180;
  }
  else {
    local_10 = (undefined **)0x1;
    local_8 = __calloc_base(1,0x50);
    if (local_8 == (undefined **)0x0) {
      return (undefined **)0x1;
    }
    puVar12 = *(undefined4 **)(param_1 + 0x88);
    ppuVar10 = local_8;
    for (iVar8 = 0x14; iVar8 != 0; iVar8 = iVar8 + -1) {
      *ppuVar10 = (undefined *)*puVar12;
      puVar12 = puVar12 + 1;
      ppuVar10 = ppuVar10 + 1;
    }
    puVar12 = __malloc_base(4);
    local_c = puVar12;
    FID_conflict__free((void *)0x0);
    if (puVar12 == (undefined4 *)0x0) {
      FID_conflict__free(local_8);
      return (undefined **)0x1;
    }
    *puVar12 = 0;
    if (*(int *)(param_1 + 0xb0) == 0) {
      *local_8 = PTR_DAT_0049d180;
      local_8[1] = PTR_DAT_0049d184;
      local_8[2] = PTR_DAT_0049d188;
      local_8[0xc] = PTR_DAT_0049d1b0;
      local_8[0xd] = PTR_DAT_0049d1b4;
      puVar12 = (undefined4 *)0x0;
    }
    else {
      puVar12 = __malloc_base(4);
      local_14 = puVar12;
      FID_conflict__free((void *)0x0);
      if (puVar12 == (undefined4 *)0x0) {
LAB_004716df:
        FID_conflict__free(local_8);
        FID_conflict__free(local_c);
        return local_10;
      }
      *puVar12 = 0;
      pwVar2 = *(wchar_t **)(param_1 + 0xb0);
      iVar8 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,1,pwVar2,0xe,(int *)local_8);
      iVar4 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,1,pwVar2,0xf,(int *)(local_8 + 1));
      local_10 = local_8 + 2;
      iVar5 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,1,pwVar2,0x10,(int *)local_10);
      iVar6 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,2,pwVar2,0xe,(int *)(local_8 + 0xc));
      iVar7 = FUN_0046e1c8((__crt_locale_pointers *)local_1c,2,pwVar2,0xf,(int *)(local_8 + 0xd));
      if (iVar7 != 0 || (((iVar8 != 0 || iVar4 != 0) || iVar5 != 0) || iVar6 != 0)) {
        ___acrt_locale_free_numeric(local_8);
        local_10 = (undefined **)0xffffffff;
        goto LAB_004716df;
      }
      pcVar9 = *local_10;
      while (puVar12 = local_14, *pcVar9 != '\0') {
        cVar1 = *pcVar9;
        if ((cVar1 < '0') || ('9' < cVar1)) {
          pcVar11 = pcVar9;
          if (cVar1 != ';') goto LAB_0047170c;
          do {
            *pcVar11 = pcVar11[1];
            pcVar11 = pcVar11 + 1;
          } while (*pcVar11 != '\0');
        }
        else {
          *pcVar9 = cVar1 + -0x30;
LAB_0047170c:
          pcVar9 = pcVar9 + 1;
        }
      }
    }
    *local_c = 1;
    ppuVar10 = local_8;
    if (puVar12 != (undefined4 *)0x0) {
      *puVar12 = 1;
    }
  }
  piVar3 = *(int **)(param_1 + 0x80);
  if (piVar3 != (int *)0x0) {
    LOCK();
    *piVar3 = *piVar3 + -1;
    UNLOCK();
  }
  piVar3 = *(int **)(param_1 + 0x7c);
  if (piVar3 != (int *)0x0) {
    LOCK();
    iVar8 = *piVar3;
    *piVar3 = iVar8 + -1;
    UNLOCK();
    if (iVar8 + -1 == 0) {
      FID_conflict__free(*(void **)(param_1 + 0x7c));
      FID_conflict__free(*(void **)(param_1 + 0x88));
    }
  }
  *(undefined4 **)(param_1 + 0x7c) = local_c;
  *(undefined4 **)(param_1 + 0x80) = puVar12;
  *(undefined ***)(param_1 + 0x88) = ppuVar10;
  return (undefined **)0x0;
}



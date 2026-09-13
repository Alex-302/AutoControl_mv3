// FUN_00470052 @ 00470052 size=399 callers=1

int __cdecl FUN_00470052(int *param_1,undefined4 *param_2)

{
  char *pcVar1;
  char cVar2;
  undefined4 *puVar3;
  uint uVar4;
  int *piVar5;
  uchar *puVar6;
  int iVar7;
  LPVOID pvVar8;
  char *pcVar9;
  undefined4 *puVar10;
  char *pcVar11;
  undefined4 *puVar12;
  undefined4 *local_24;
  undefined4 *local_20;
  undefined4 local_1c;
  int local_18;
  char *local_14;
  char *local_10;
  char *local_c;
  undefined4 local_8;
  
  if (param_2 == (undefined4 *)0x0) {
    piVar5 = __errno();
    iVar7 = 0x16;
    *piVar5 = 0x16;
    FUN_00465fa2();
  }
  else {
    *param_2 = 0;
    local_24 = (undefined4 *)0x0;
    local_20 = (undefined4 *)0x0;
    local_1c = 0;
    iVar7 = *param_1;
    puVar12 = local_24;
    puVar3 = local_20;
    while (local_24 = puVar12, local_20 = puVar3, iVar7 != 0) {
      uVar4 = (uint)local_8 >> 0x18;
      local_8 = (char *)CONCAT13((char)uVar4,0x3f2a);
      puVar6 = (uchar *)_strpbrk((char *)*param_1,(char *)&local_8);
      if (puVar6 == (uchar *)0x0) {
        iVar7 = FUN_004701e2((char *)*param_1,(char *)0x0,0,&local_24);
      }
      else {
        iVar7 = expand_argument_wildcards<>((uchar *)*param_1,puVar6,(int *)&local_24);
      }
      if (iVar7 != 0) goto LAB_004701c4;
      param_1 = param_1 + 1;
      puVar12 = local_24;
      puVar3 = local_20;
      iVar7 = *param_1;
    }
    local_c = (char *)0x0;
    local_8 = (char *)0x0;
    local_10 = (char *)(((int)puVar3 - (int)puVar12 >> 2) + 1);
    pcVar11 = (char *)(~-(uint)(puVar3 < puVar12) & ((int)puVar3 - (int)puVar12) + 3U >> 2);
    if (pcVar11 != (char *)0x0) {
      local_8 = (char *)0x0;
      puVar10 = puVar12;
      do {
        pcVar9 = (char *)*puVar10;
        pcVar1 = pcVar9 + 1;
        do {
          cVar2 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar2 != '\0');
        local_8 = pcVar9 + (int)(local_8 + (1 - (int)pcVar1));
        puVar10 = puVar10 + 1;
        local_c = local_c + 1;
      } while (local_c != pcVar11);
    }
    pvVar8 = ___acrt_allocate_buffer_for_argv((uint)local_10,(uint)local_8,1);
    if (pvVar8 == (LPVOID)0x0) {
      iVar7 = -1;
    }
    else {
      local_10 = (char *)((int)pvVar8 + (int)local_10 * 4);
      local_14 = local_10;
      if (puVar12 != puVar3) {
        local_18 = (int)pvVar8 - (int)puVar12;
        do {
          local_c = (char *)*puVar12;
          pcVar11 = local_c + 1;
          do {
            cVar2 = *local_c;
            local_c = local_c + 1;
          } while (cVar2 != '\0');
          local_c = local_c + (1 - (int)pcVar11);
          iVar7 = FUN_004754f8(local_10,(uint)(local_14 + ((int)local_8 - (int)local_10)),
                               (char *)*puVar12,(uint)local_c);
          if (iVar7 != 0) {
                    /* WARNING: Subroutine does not return */
            __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
          }
          *(char **)(local_18 + (int)puVar12) = local_10;
          puVar12 = puVar12 + 1;
          local_10 = local_10 + (int)local_c;
        } while (puVar12 != puVar3);
      }
      iVar7 = 0;
      *param_2 = pvVar8;
    }
    FID_conflict__free((void *)0x0);
LAB_004701c4:
    ~argument_list<>(&local_24);
  }
  return iVar7;
}



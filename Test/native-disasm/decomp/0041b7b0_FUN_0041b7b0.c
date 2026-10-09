// FUN_0041b7b0 @ 0041b7b0 size=896 callers=1

HMENU __fastcall FUN_0041b7b0(void *param_1)

{
  int *piVar1;
  undefined1 uVar2;
  int *piVar3;
  char cVar4;
  undefined4 uVar5;
  char *pcVar6;
  LPCSTR pCVar7;
  void *this;
  void *pvVar8;
  LPWSTR ****_Memory;
  int iVar9;
  int *piVar10;
  MENUITEMINFOW local_c8;
  int local_98 [4];
  void *local_88 [4];
  undefined4 local_78;
  uint local_74;
  LPWSTR ***local_70 [4];
  UINT local_60;
  uint local_5c;
  void *local_58 [4];
  undefined4 local_48;
  uint local_44;
  void *local_40 [4];
  undefined4 local_30;
  uint local_2c;
  uint local_28;
  char *local_24;
  int *local_20;
  int local_1c;
  int local_18;
  HMENU local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8._0_1_ = 0xff;
  local_8._1_3_ = 0xffffff;
  puStack_c = &LAB_0047b7c3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = CreatePopupMenu();
  FUN_00434120(param_1,&local_24);
  FUN_004340a0(this,local_98);
  uVar5 = FUN_004383a0(&local_24,local_98);
  cVar4 = (char)uVar5;
  piVar10 = local_20;
  iVar9 = local_18;
  do {
    if (cVar4 != '\0') {
      ExceptionList = local_10;
      return local_14;
    }
    pcVar6 = FUN_00433bc0(&local_24);
    local_2c = 0xf;
    local_30 = 0;
    local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
    FUN_0043ace0(local_40,(uint *)"title",5);
    local_8 = 0;
    pCVar7 = (LPCSTR)FUN_004342f0(pcVar6,local_88,local_40,(uint *)&DAT_0048e75c);
    local_8._0_1_ = 1;
    FUN_00404640((LPWSTR)local_70,pCVar7);
    local_8._0_1_ = 3;
    uVar2 = (undefined1)local_8;
    local_8._0_1_ = 3;
    if (0xf < local_74) {
      pvVar8 = local_88[0];
      if ((0xfff < local_74 + 1) &&
         ((((((uint)local_88[0] & 0x1f) != 0 ||
            (pvVar8 = *(void **)((int)local_88[0] + -4), uVar2 = (undefined1)local_8,
            local_88[0] <= pvVar8)) || ((uint)((int)local_88[0] - (int)pvVar8) < 4)) ||
          (0x23 < (uint)((int)local_88[0] - (int)pvVar8))))) goto LAB_0041bb2b;
      FID_conflict__free(pvVar8);
    }
    local_74 = 0xf;
    local_78 = 0;
    local_88[0] = (void *)((uint)local_88[0] & 0xffffff00);
    local_8._0_1_ = 4;
    if (0xf < local_2c) {
      pvVar8 = local_40[0];
      if ((0xfff < local_2c + 1) &&
         (((uVar2 = (undefined1)local_8, ((uint)local_40[0] & 0x1f) != 0 ||
           (pvVar8 = *(void **)((int)local_40[0] + -4), local_40[0] <= pvVar8)) ||
          (((uint)((int)local_40[0] - (int)pvVar8) < 4 ||
           (0x23 < (uint)((int)local_40[0] - (int)pvVar8))))))) goto LAB_0041bb2b;
      FID_conflict__free(pvVar8);
    }
    local_2c = 0xf;
    local_30 = 0;
    local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
    local_44 = 0xf;
    local_48 = 0;
    local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
    FUN_0043ace0(local_58,(uint *)&DAT_0048cf30,2);
    local_8._0_1_ = 5;
    pcVar6 = (char *)FUN_00439c60(pcVar6,(byte *)local_58);
    local_8._0_1_ = 4;
    if (0xf < local_44) {
      pvVar8 = local_58[0];
      if ((0xfff < local_44 + 1) &&
         (((uVar2 = (undefined1)local_8, ((uint)local_58[0] & 0x1f) != 0 ||
           (pvVar8 = *(void **)((int)local_58[0] + -4), local_58[0] <= pvVar8)) ||
          (((uint)((int)local_58[0] - (int)pvVar8) < 4 ||
           (0x23 < (uint)((int)local_58[0] - (int)pvVar8))))))) goto LAB_0041bb2b;
      FID_conflict__free(pvVar8);
    }
    local_44 = 0xf;
    local_48 = 0;
    local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
    FUN_00453810(pcVar6,&local_28);
    local_c8.cbSize = 0x30;
    _memset(&local_c8.fMask,0,0x2c);
    local_c8.fType = 0;
    local_c8.wID = local_28;
    local_c8.fMask = 0x142;
    if (local_28 == 0) {
      local_c8.fType = 0x800;
    }
    local_c8.dwTypeData = (LPWSTR)local_70;
    if (7 < local_5c) {
      local_c8.dwTypeData = (LPWSTR)local_70[0];
    }
    local_c8.cch = local_60;
    InsertMenuItemW(local_14,0xffffffff,1,&local_c8);
    local_8._0_1_ = 0xff;
    local_8._1_3_ = 0xffffff;
    if (7 < local_5c) {
      uVar2 = (undefined1)local_8;
      if ((0x7fffffff < local_5c + 1) ||
         ((_Memory = (LPWSTR ****)local_70[0], 0xfff < (local_5c + 1) * 2 &&
          ((((((uint)local_70[0] & 0x1f) != 0 ||
             (_Memory = (LPWSTR ****)local_70[0][-1], local_70[0] <= _Memory)) ||
            ((uint)((int)local_70[0] - (int)_Memory) < 4)) ||
           (0x23 < (uint)((int)local_70[0] - (int)_Memory))))))) {
LAB_0041bb2b:
        local_8._0_1_ = uVar2;
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      FID_conflict__free(_Memory);
    }
    local_5c = 7;
    local_70[0] = (LPWSTR ***)((uint)local_70[0] & 0xffff0000);
    local_60 = 0;
    if (*local_24 == '\x01') {
      if (*(char *)((int)piVar10 + 0xd) == '\0') {
        piVar1 = (int *)piVar10[2];
        if (*(char *)((int)piVar1 + 0xd) == '\0') {
          cVar4 = *(char *)(*piVar1 + 0xd);
          piVar10 = piVar1;
          piVar1 = (int *)*piVar1;
          while (local_20 = piVar10, cVar4 == '\0') {
            cVar4 = *(char *)(*piVar1 + 0xd);
            piVar10 = piVar1;
            piVar1 = (int *)*piVar1;
          }
        }
        else {
          cVar4 = *(char *)(piVar10[1] + 0xd);
          piVar3 = (int *)piVar10[1];
          piVar1 = piVar10;
          while ((piVar10 = piVar3, local_20 = piVar10, cVar4 == '\0' &&
                 (piVar1 == (int *)piVar10[2]))) {
            cVar4 = *(char *)(piVar10[1] + 0xd);
            piVar3 = (int *)piVar10[1];
            piVar1 = piVar10;
          }
        }
      }
    }
    else if (*local_24 == '\x02') {
      local_1c = local_1c + 0x10;
    }
    else {
      iVar9 = iVar9 + 1;
      local_18 = iVar9;
    }
    uVar5 = FUN_004383a0(&local_24,local_98);
    cVar4 = (char)uVar5;
  } while( true );
}



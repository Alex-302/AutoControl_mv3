// FUN_004156f0 @ 004156f0 size=1034 callers=1

uint __fastcall FUN_004156f0(POINT *param_1,uint param_2,HWND param_3)

{
  int iVar1;
  LONG *pLVar2;
  BOOL BVar3;
  uint uVar4;
  uint *this;
  int *piVar5;
  undefined4 *puVar6;
  void *this_00;
  byte *pbVar7;
  int *piVar8;
  uint *puVar9;
  uint *puVar10;
  LPRECT ptVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  bool bVar15;
  POINT *pPVar16;
  RECT local_20;
  tagRECT local_10;
  
  switch(param_2) {
  case 3:
    pLVar2 = (LONG *)FUN_0040e5c0(param_3,'\x01',&local_10.left);
    local_20.left = *pLVar2;
    local_20.top = pLVar2[1];
    local_20.right = pLVar2[2];
    local_20.bottom = pLVar2[3];
    BVar3 = PtInRect(&local_20,*param_1);
    return (uint)(BVar3 != 0);
  case 4:
  case 10:
  case 0x14:
    uVar4 = FUN_00414760(param_1,param_3,param_2);
    return uVar4;
  }
  if (param_2 < 10) {
    if (0x13 < param_2) goto LAB_00415917;
LAB_0041591c:
    this = (uint *)(param_2 - 0x3c);
    if ((uint *)0x14 < (uint *)(param_2 - 0x3c)) goto switchD_004157cc_caseD_d;
  }
  else {
    if (param_2 < 0x14) {
      this = (uint *)FUN_00414760(param_1,param_3,10);
      if ((char)this == '\0') goto switchD_004157cc_caseD_d;
      piVar5 = FUN_00415240(param_1);
      if (((uint *)0x68 < DAT_004a23a4) && (param_2 != 0x10)) {
        pPVar16 = param_1;
        puVar6 = (undefined4 *)FUN_00414ec0(piVar5);
        this_00 = (void *)FUN_00415020(puVar6);
        piVar5 = (int *)FUN_004150d0(this_00,&pPVar16->x);
      }
      this = DAT_004a23a4;
      switch(param_2) {
      case 0xc:
        uVar4 = FUN_00415570(piVar5);
        return uVar4;
      case 0xf:
        piVar8 = FUN_00414dc0(piVar5);
        if (*piVar8 != 0x2b) {
          return 0;
        }
        pbVar7 = (byte *)FUN_00414e10(piVar5);
        if ((*pbVar7 & 1) != 0) {
          return 0;
        }
        piVar5 = (int *)FUN_00414ec0(piVar5);
        piVar5 = FUN_00414dc0(piVar5);
        bVar15 = *piVar5 == 0x25;
        goto LAB_0041580a;
      case 0x10:
        uVar4 = FUN_004154f0(piVar5);
        return uVar4;
      case 0x11:
        if (DAT_004a23a4 < (uint *)0x64) {
          piVar8 = FUN_00414e60(piVar5);
          if (piVar8[2] != piVar8[3]) {
            return 0;
          }
          piVar8 = FUN_00414dc0(piVar5);
          if (*piVar8 != 0x10) {
            return 0;
          }
          piVar5 = (int *)FUN_00414ec0(piVar5);
          piVar5 = FUN_00414dc0(piVar5);
          if (*piVar5 != 0x25) {
            return 0;
          }
          return 1;
        }
        this = (uint *)FUN_00414dc0(piVar5);
        if (*this == 0x25) {
          piVar5 = (int *)FUN_00415020(piVar5);
          this = (uint *)FUN_00414dc0(piVar5);
          if ((*this == 0x2b) && (this = (uint *)FUN_00414e10(piVar5), (*this & 0x100000) == 0)) {
            piVar5 = FUN_00414e60(piVar5);
            local_20.right = piVar5[2];
            if (local_20.right < 0xb) {
              return 0;
            }
            if (local_20.right == piVar5[3]) {
              local_20.left = *piVar5;
              local_20.top = piVar5[1];
              local_20.right = local_20.left + local_20.right;
              local_20.bottom = local_20.top + piVar5[3];
              BVar3 = PtInRect(&local_20,*param_1);
              if (BVar3 != 0) {
                return 1;
              }
              return 0;
            }
            return 0;
          }
        }
      }
      goto switchD_004157cc_caseD_d;
    }
LAB_00415917:
    if (0x27 < param_2) goto LAB_0041591c;
  }
  this = (uint *)FUN_00414760(param_1,param_3,0x14);
  if ((char)this != '\0') {
    this = FUN_00415240(param_1);
    if (param_2 == 0x15) {
      piVar5 = FUN_00414dc0((int *)this);
      return CONCAT31((int3)((uint)piVar5 >> 8),*piVar5 == 0x2a);
    }
    if (param_2 == 0x1e) {
      this = (uint *)FUN_00415660(this,'\x01');
      if (*this != 0) {
        piVar5 = FUN_00414e60((int *)this);
        ptVar11 = FUN_00404c00(param_3,'\x01',&local_10);
        if (DAT_004a23d7 == 'Y') {
          return CONCAT31((int3)((uint)(piVar5[3] / 2) >> 8),*piVar5 - ptVar11->left < piVar5[3] / 2
                         );
        }
        return CONCAT31((int3)((uint)(piVar5[3] / 2) >> 8),
                        (ptVar11->right - piVar5[2]) - *piVar5 < piVar5[3] / 2);
      }
    }
    else if (param_2 == 0x21) {
      puVar9 = (uint *)FUN_00415660(this,'\0');
      this = puVar9;
      if (*puVar9 != 0) {
        piVar5 = FUN_00414e60((int *)puVar9);
        ptVar11 = FUN_00404c00(param_3,'\x01',&local_10);
        iVar1 = piVar5[2];
        local_20.left = ptVar11->left;
        local_20.top = ptVar11->top;
        local_20.right = ptVar11->right;
        local_20.bottom = ptVar11->bottom;
        iVar14 = piVar5[3];
        if (piVar5[3] < iVar1) {
          iVar14 = iVar1;
        }
        iVar12 = 3;
        iVar13 = 8;
        if (DAT_004a23d7 == 'Y') {
          iVar12 = 8;
          iVar13 = 3;
        }
        this = (uint *)(*piVar5 - local_20.left);
        if ((iVar13 * iVar14 < (int)this) &&
           (this = (uint *)((local_20.right - *piVar5) - iVar1), iVar12 * iVar14 < (int)this)) {
          piVar5 = (int *)FUN_00414f70((int *)puVar9);
          return CONCAT31((int3)((uint)piVar5 >> 8),*piVar5 == 0);
        }
      }
    }
    else if ((param_2 - 0x3c < 0x15) && (this = (uint *)FUN_00415660(this,'\x01'), *this != 0)) {
      puVar9 = FUN_00414d10((int *)this);
      puVar10 = (uint *)FUN_00434e50((int *)puVar9);
      this = puVar10;
      if (puVar10 != (uint *)0xffffffff) {
        this = puVar9;
        if (7 < puVar9[5]) {
          this = (uint *)*puVar9;
        }
        if (*(short *)((int)this + (int)puVar10 * 2) == 0xb) {
          this = (uint *)0x0;
          if (puVar9[4] - (int)puVar10 != 1) {
            if (param_2 == 0x3c) {
              return 1;
            }
            bVar15 = param_2 - 0x3c == (puVar9[4] - (int)puVar10) - 1;
LAB_0041580a:
            if (bVar15) {
              return 1;
            }
            return 0;
          }
        }
      }
    }
  }
switchD_004157cc_caseD_d:
  return (uint)this & 0xffffff00;
}



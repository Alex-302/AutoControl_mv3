// FUN_0041fa40 @ 0041fa40 size=701 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

LRESULT FUN_0041fa40(int param_1,WPARAM param_2,int param_3)

{
  POINT pt;
  ushort uVar1;
  uint uVar2;
  LRESULT LVar3;
  HWND hwnd;
  HWND hWnd;
  UINT UVar4;
  undefined *puVar5;
  int iVar6;
  undefined1 extraout_DL;
  uint uVar7;
  int iVar8;
  
  if ((*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a3308) &&
     (FUN_0045a219(&DAT_004a3308), DAT_004a3308 == -1)) {
    uVar2 = GetSystemMetrics(0x44);
    DAT_004a3354 = (uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f);
    FUN_0045a1da(&DAT_004a3308);
  }
  if (param_1 != 2) goto switchD_0041fbc4_caseD_203;
  if (DAT_004a2427 != '\0') {
    iVar6 = *(int *)(param_3 + 4);
    if ((((iVar6 == 0x201) || (iVar6 == 0x204)) || (iVar6 == 0x207)) &&
       (uVar2 = GetWindowLongA(DAT_004a2994,-0x14), (uVar2 >> 3 & 1) == 0)) {
      FUN_0040ee50(DAT_004a2994);
    }
    goto switchD_0041fbc4_caseD_203;
  }
  uVar2 = *(uint *)(param_3 + 4);
  if (uVar2 < 0x201) {
    if (uVar2 == 0x200) {
      if (DAT_0049da5e != -0x8000) {
        iVar6 = (int)DAT_0049da5c;
        uVar2 = *(short *)(param_3 + 0xc) - iVar6;
        uVar7 = (int)uVar2 >> 0x1f;
        if ((DAT_004a3354 < (int)((uVar2 ^ uVar7) - uVar7)) ||
           (uVar2 = (int)*(short *)(param_3 + 0xe) - (int)DAT_0049da5e, uVar7 = (int)uVar2 >> 0x1f,
           DAT_004a3354 < (int)((uVar2 ^ uVar7) - uVar7))) {
          DAT_004a2399 = '\x01';
          iVar8 = (int)DAT_0049da5e;
          hwnd = GetDesktopWindow();
          pt.y = iVar8;
          pt.x = iVar6;
          hWnd = ChildWindowFromPointEx(hwnd,pt,5);
          if (hWnd == hwnd) {
            hWnd = (HWND)0x0;
          }
          PostMessageA(hWnd,0x201,1,_DAT_0049da5c);
        }
      }
      goto switchD_0041fbc4_caseD_203;
    }
    if (uVar2 == 0x100) {
      if (*(int *)(param_3 + 8) == 0xd) goto switchD_0041fbc4_caseD_208;
      goto switchD_0041fbc4_caseD_203;
    }
    if ((uVar2 != 0x101) || (*(int *)(param_3 + 8) != 0x5d)) goto switchD_0041fbc4_caseD_203;
    *(undefined4 *)(param_3 + 0xc) = 0x80008000;
switchD_0041fbc4_caseD_205:
    FUN_0041f520((int)*(short *)(param_3 + 0xc),(int)*(short *)(param_3 + 0xe));
  }
  else {
    switch(uVar2) {
    case 0x201:
      _DAT_0049da5c = *(LPARAM *)(param_3 + 0xc);
      if (DAT_004a2399 == '\0') {
        FUN_0041fa10();
        UVar4 = FUN_0041d3c0('\0',(int)DAT_0049da5c,(int)DAT_0049da5e);
        if (UVar4 != 0) {
          return -1;
        }
        DAT_004a2437 = '\x01';
      }
      else {
        DAT_004a2399 = '\0';
      }
      break;
    case 0x202:
      _DAT_0049da5c = DAT_0048e600;
      if (DAT_004a2437 == '\0') goto switchD_0041fbc4_caseD_208;
      DAT_004a2437 = '\0';
      break;
    case 0x204:
    case 0x207:
      FUN_0041fa10();
      return -1;
    case 0x205:
      goto switchD_0041fbc4_caseD_205;
    case 0x208:
switchD_0041fbc4_caseD_208:
      UVar4 = DAT_004a29c0;
      if (uVar2 != 0x100) {
        UVar4 = FUN_0041d3c0('\0',*(LONG *)(param_3 + 0x14),*(LONG *)(param_3 + 0x18));
      }
      if (UVar4 != 0) {
        puVar5 = FUN_00419890(UVar4);
        if (*(int *)(param_3 + 4) == 0x100) {
          uVar2 = 0;
        }
        else {
          uVar2 = *(uint *)(param_3 + 8);
        }
        uVar2 = FUN_00419fb0(*(int *)(param_3 + 4) == 0x208,uVar2);
        uVar1 = FUN_0041a020(puVar5[0x24],(char)uVar2);
        if ((char)uVar1 != '\0') {
          FUN_00419cf0(UVar4,extraout_DL);
        }
        if ((char)(uVar1 >> 8) != '\0') {
          EndMenu();
        }
      }
      return -1;
    }
  }
switchD_0041fbc4_caseD_203:
  LVar3 = CallNextHookEx((HHOOK)0x0,param_1,param_2,param_3);
  return LVar3;
}



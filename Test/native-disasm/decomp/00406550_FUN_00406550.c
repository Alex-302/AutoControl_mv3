// FUN_00406550 @ 00406550 size=188 callers=1

undefined4 __fastcall FUN_00406550(HWND param_1,RECT *param_2,POINT *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  HWND hwnd;
  HWND pHVar5;
  BOOL BVar6;
  int iVar7;
  uint uVar8;
  
  iVar1 = param_2->right;
  iVar2 = param_2->left;
  uVar8 = 1;
  iVar3 = param_2->bottom;
  iVar4 = param_2->top;
  while( true ) {
    hwnd = GetDesktopWindow();
    pHVar5 = ChildWindowFromPointEx(hwnd,*param_3,5);
    if (pHVar5 == hwnd) {
      pHVar5 = (HWND)0x0;
    }
    if (pHVar5 == param_1) break;
    BVar6 = PtInRect(param_2,*param_3);
    if (BVar6 == 0) {
      return 0;
    }
    iVar7 = 10;
    if ((uVar8 & 2) != 0) {
      iVar7 = -10;
    }
    if ((uVar8 & 1) == 0) {
      param_3->x = param_3->x +
                   (int)((float)(int)(iVar7 * uVar8) *
                        ((float)(iVar1 - iVar2) / (float)(iVar3 - iVar4)));
      uVar8 = uVar8 + 1;
    }
    else {
      param_3->y = param_3->y + iVar7 * uVar8;
      uVar8 = uVar8 + 1;
    }
  }
  return CONCAT31((int3)((uint)pHVar5 >> 8),1);
}



// FUN_0040b4b0 @ 0040b4b0 size=310 callers=4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __fastcall FUN_0040b4b0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  float local_2c;
  HDC local_28;
  double local_24;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  undefined4 local_8;
  
  iVar4 = param_1[4];
  iVar3 = GdipGetFontSize(*param_2,&local_2c);
  if (iVar3 != 0) {
    param_2[1] = iVar3;
  }
  fVar5 = roundf((float)((double)iVar4 + (double)(&DAT_0048f2d0)[-(iVar4 >> 0x1f)]) * local_2c *
                 _DAT_0048f224);
  local_2c = (float)fVar5;
  iVar4 = (int)fVar5;
  local_28 = GetDC((HWND)0x0);
  if (local_28 != (HDC)0x0) {
    local_2c = 0.0;
    GdipCreateFromHDC(local_28,&local_2c);
    fVar2 = local_2c;
    GdipSetPageUnit(local_2c,2);
    puVar1 = param_1 + 4;
    local_8 = 0;
    local_c = 0.0;
    local_10 = 0;
    local_14 = 0;
    if (7 < (uint)param_1[5]) {
      param_1 = (undefined4 *)*param_1;
    }
    local_24 = 0.0;
    uStack_1c = 0;
    uStack_18 = 0;
    iVar3 = GdipMeasureString(fVar2,param_1,*puVar1,*param_2,&local_24,0,&local_14,0,0);
    if (iVar3 == 0) {
      local_24 = (double)local_c;
      fVar5 = FUN_004766c0(local_24);
      local_24 = (double)fVar5;
      iVar4 = (int)fVar5;
    }
    ReleaseDC((HWND)0x0,local_28);
    GdipDeleteGraphics();
  }
  return iVar4;
}



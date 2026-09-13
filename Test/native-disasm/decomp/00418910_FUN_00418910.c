// FUN_00418910 @ 00418910 size=931 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_00418910(undefined4 *param_1)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  float fVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  float10 fVar10;
  int local_2c;
  int local_28;
  float local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  
  fVar6 = 0.0;
  local_2c = 0;
  local_28 = 0;
  pcVar7 = (char *)&DAT_004a25b4;
  if (0xf < DAT_004a25c8) {
    pcVar7 = DAT_004a25b4;
  }
  local_1c = (int)(pcVar7 + DAT_004a25c4) - (int)pcVar7;
  if (pcVar7 + DAT_004a25c4 < pcVar7) {
    local_1c = 0;
  }
  if (local_1c != 0) {
    do {
      local_24 = 0.0;
      iVar9 = *(int *)(DAT_004a25a8 + *pcVar7 * 4);
      iVar2 = GdipGetImageHeight(*(undefined4 *)(iVar9 + 4),&local_24);
      if (iVar2 != 0) {
        *(int *)(iVar9 + 8) = iVar2;
      }
      if ((uint)fVar6 <= (uint)local_24) {
        local_24 = 0.0;
        iVar2 = GdipGetImageHeight(*(undefined4 *)(iVar9 + 4),&local_24);
        fVar6 = local_24;
        if (iVar2 != 0) {
          *(int *)(iVar9 + 8) = iVar2;
        }
      }
      local_24 = 0.0;
      iVar2 = GdipGetImageWidth(*(undefined4 *)(iVar9 + 4),&local_24);
      if (iVar2 != 0) {
        *(int *)(iVar9 + 8) = iVar2;
      }
      pcVar7 = pcVar7 + 1;
      local_2c = local_2c + 1;
      local_28 = local_28 + (int)local_24;
    } while (local_2c != local_1c);
  }
  iVar9 = local_28;
  if ((char)_DAT_004a25dc != '\0') {
    local_24 = 0.0;
    iVar2 = *(int *)((uint)((char)_DAT_004a25dc != 'S') * 4 + 0x20 + DAT_004a25a8);
    iVar3 = GdipGetImageHeight(*(undefined4 *)(iVar2 + 4),&local_24);
    if (iVar3 != 0) {
      *(int *)(iVar2 + 8) = iVar3;
    }
    if ((uint)fVar6 <= (uint)local_24) {
      local_24 = 0.0;
      iVar3 = GdipGetImageHeight(*(undefined4 *)(iVar2 + 4),&local_24);
      fVar6 = local_24;
      if (iVar3 != 0) {
        *(int *)(iVar2 + 8) = iVar3;
      }
    }
    local_24 = 0.0;
    iVar3 = GdipGetImageWidth(*(undefined4 *)(iVar2 + 4),&local_24);
    if (iVar3 != 0) {
      *(int *)(iVar2 + 8) = iVar3;
    }
    iVar9 = iVar9 + (int)local_24;
  }
  fVar10 = roundf((float)((double)(int)fVar6 + (double)(&DAT_0048f2d0)[-((int)fVar6 >> 0x1f)]) *
                  _DAT_0048f21c);
  local_24 = (float)fVar10;
  iVar2 = (int)fVar10;
  if ((DAT_004a25dc != '\0') && (DAT_004a25c4 != 0)) {
    iVar9 = iVar9 + iVar2;
  }
  iVar3 = (int)fVar6 + iVar2 * 2;
  pvVar1 = (void *)(iVar9 + iVar2 * 2);
  local_14 = iVar3;
  FUN_0040a870(param_1,pvVar1,iVar3);
  local_20 = 0;
  GdipCreateFromHDC(*param_1,&local_20);
  local_28 = local_20;
  GdipGraphicsClear(local_20,DAT_004a25d8);
  local_10 = 0;
  local_c = GdipCreatePen1(0x78808080,0x3f800000,0,&local_10);
  iVar4 = GdipSetPenMode(local_10,1);
  iVar9 = local_28;
  if (iVar4 != 0) {
    local_c = iVar4;
  }
  GdipDrawRectangleI(local_28,local_10,0,0,(int)pvVar1 + -1,iVar3 + -1);
  pcVar7 = (char *)&DAT_004a25b4;
  if (0xf < DAT_004a25c8) {
    pcVar7 = DAT_004a25b4;
  }
  pcVar8 = (char *)&DAT_004a25b4;
  if (0xf < DAT_004a25c8) {
    pcVar8 = DAT_004a25b4;
  }
  local_1c = 0;
  local_18 = (int)(pcVar7 + DAT_004a25c4) - (int)pcVar8;
  if (pcVar7 + DAT_004a25c4 < pcVar8) {
    local_18 = 0;
  }
  iVar4 = local_2c;
  if (local_18 != 0) {
    do {
      iVar9 = *(int *)(DAT_004a25a8 + *pcVar8 * 4);
      if (iVar9 == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = *(undefined4 *)(iVar9 + 4);
      }
      GdipDrawImageI(local_28,uVar5,iVar2,(int)local_24);
      local_2c = 0;
      iVar3 = GdipGetImageWidth(*(undefined4 *)(iVar9 + 4),&local_2c);
      if (iVar3 != 0) {
        *(int *)(iVar9 + 8) = iVar3;
      }
      pcVar8 = pcVar8 + 1;
      iVar2 = iVar2 + local_2c;
      local_1c = local_1c + 1;
      iVar3 = local_14;
      iVar9 = local_28;
      iVar4 = iVar2;
    } while (local_1c != local_18);
  }
  local_2c = iVar4;
  if (DAT_004a25dc != '\0') {
    local_1c = 0;
    local_14 = (int)local_24 + iVar2;
    if (DAT_004a25c4 == 0) {
      local_14 = iVar2;
    }
    iVar2 = *(int *)((uint)(DAT_004a25dc != 'S') * 4 + 0x20 + DAT_004a25a8);
    iVar4 = GdipGetImageHeight(*(undefined4 *)(iVar2 + 4),&local_1c);
    if (iVar4 != 0) {
      *(int *)(iVar2 + 8) = iVar4;
    }
    GdipDrawImageI(iVar9,*(undefined4 *)(iVar2 + 4),local_14,(uint)(iVar3 - local_1c) >> 1);
  }
  GdipDeletePen(local_10);
  GdipDeleteGraphics(iVar9);
  return param_1;
}



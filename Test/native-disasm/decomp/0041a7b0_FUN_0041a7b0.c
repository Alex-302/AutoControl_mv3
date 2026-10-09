// FUN_0041a7b0 @ 0041a7b0 size=2177 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall
FUN_0041a7b0(float param_1,int *param_2,byte *param_3,undefined4 *param_4,char param_5,char param_6,
            char param_7)

{
  undefined4 *puVar1;
  byte *pbVar2;
  float *pfVar3;
  float *pfVar4;
  float fVar5;
  undefined4 uVar6;
  float fVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  undefined4 *puVar11;
  int iVar12;
  float10 fVar13;
  byte *pbVar14;
  undefined **local_68;
  float *local_64;
  undefined4 local_60;
  byte *local_5c;
  float *local_58;
  undefined4 local_54;
  float local_50;
  byte *local_4c;
  float local_48;
  byte *local_44;
  byte *local_40;
  byte *local_3c;
  float local_38;
  byte *local_34;
  float local_30;
  float local_2c;
  int local_28;
  float local_24;
  int local_20;
  float *local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b668;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_3c = (byte *)param_2;
  local_38 = param_1;
  FUN_00436020(&DAT_004a296c,(int *)&param_3,param_3);
  pbVar2 = param_3;
  if (param_3 == DAT_004a2970) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid unordered_map<K, T> key");
  }
  param_3 = (byte *)0x0;
  local_20 = 0;
  if ((*(byte *)((int)param_4 + 0x26) & 1) == 0) {
    local_20 = (int)param_5;
  }
  local_20 = local_20 * 7;
  iVar9 = *(int *)local_3c;
  local_18 = *(int *)(local_3c + 8) - iVar9;
  iVar12 = *(int *)(local_3c + 4);
  local_28 = *(int *)(local_3c + 0xc) - iVar12;
  local_24 = (float)DAT_004a29c8 * _DAT_0048f218;
  local_1c = (float *)GdipCreateFromHDC(local_38,&param_3);
  local_5c = param_3;
  local_8 = 0;
  pfVar3 = (float *)GdipSetPageUnit(param_3,2);
  pbVar10 = param_3;
  if (pfVar3 != (float *)0x0) {
    local_1c = pfVar3;
  }
  pfVar4 = (float *)GdipTranslateWorldTransform(param_3,(float)iVar9,(float)iVar12,0);
  pfVar3 = local_1c;
  if (pfVar4 != (float *)0x0) {
    pfVar3 = pfVar4;
  }
  pfVar4 = (float *)GdipSetClipRectI(pbVar10,0,0,local_18,local_28,0);
  if (pfVar4 != (float *)0x0) {
    pfVar3 = pfVar4;
  }
  pfVar4 = (float *)GdipGraphicsClear(pbVar10,*(undefined4 *)(pbVar2 + 0x90));
  iVar9 = local_20;
  puVar11 = param_4;
  local_1c = pfVar3;
  if (pfVar4 != (float *)0x0) {
    local_1c = pfVar4;
  }
  if (*(char *)(param_4 + 9) == '\x03') goto LAB_0041b019;
  fVar13 = roundf((float)((int)*(short *)(pbVar2 + local_20 * 4 + 0x2e) +
                         (int)*(short *)(pbVar2 + local_20 * 4 + 0x2c)) * local_24);
  local_30 = 0.0;
  local_34 = (byte *)(float)fVar13;
  GdipCreateSolidFill(*(undefined4 *)(pbVar2 + iVar9 * 4 + 0x24),&local_30);
  fVar5 = local_30;
  iVar9 = (int)(float)local_34;
  fVar7 = local_30;
  pfVar3 = (float *)GdipFillRectangleI(param_3,local_30,iVar9,iVar9,local_18 + iVar9 * -2,
                                       local_28 + iVar9 * -2);
  local_58 = local_1c;
  if (pfVar3 != (float *)0x0) {
    local_58 = pfVar3;
  }
  local_1c = local_58;
  GdipDeleteBrush(fVar5);
  iVar12 = local_20;
  fVar13 = roundf((float)((int)*(short *)(pbVar2 + local_20 * 4 + 0x30) +
                          (int)*(short *)(pbVar2 + local_20 * 4 + 0x2e) +
                         (int)*(short *)(pbVar2 + local_20 * 4 + 0x2c)) *
                  (float)DAT_004a29c8 * _DAT_0048f218);
  local_30 = (float)fVar13;
  fVar13 = roundf((float)((int)*(short *)(pbVar2 + iVar12 * 4 + 0x32) +
                          (int)*(short *)(pbVar2 + iVar12 * 4 + 0x2e) +
                         (int)*(short *)(pbVar2 + iVar12 * 4 + 0x2c)) *
                  (float)DAT_004a29c8 * _DAT_0048f218);
  local_2c = (float)fVar13;
  if (*(char *)(puVar11 + 9) == '\x01') {
    local_54 = 0;
    local_50 = (float)GdipCreatePen1(*(undefined4 *)(pbVar2 + 0x94),0x3f800000,0,&local_54);
    local_5c = (byte *)0x0;
    local_58 = (float *)GdipCreatePen1(*(undefined4 *)(pbVar2 + 0x98),0x3f800000,0,&local_5c);
    fVar13 = roundf(local_24);
    local_3c = (byte *)(float)fVar13;
    iVar9 = (int)fVar13 + (int)(float)local_34;
    local_18 = (local_18 - iVar9) + -1;
    iVar12 = local_28 / 2;
    GdipDrawLineI(param_3,local_5c,iVar9,iVar12,local_18,iVar12);
    pbVar10 = param_3;
    GdipDrawLineI(param_3,local_54,iVar9,iVar12 + 1,local_18,iVar12 + 1);
    GdipDeletePen(local_5c);
    GdipDeletePen(local_54);
    goto LAB_0041b019;
  }
  fVar5 = (float)FUN_0041a380((int)puVar11);
  pfVar3 = local_1c;
  if (fVar5 != 0.0) {
    local_50 = fVar5;
    fVar13 = roundf((float)(int)((uint)DAT_004a29c8 + (int)local_2c) +
                    (float)(int)*(short *)(pbVar2 + local_20 * 4 + 0x38) * local_24);
    local_34 = (byte *)0x0;
    local_3c = (byte *)(float)fVar13;
    iVar9 = GdipGetImageHeight(*(undefined4 *)((int)fVar5 + 4),&local_34);
    if (iVar9 != 0) {
      *(int *)((int)fVar5 + 8) = iVar9;
    }
    local_4c = local_34;
    local_38 = 0.0;
    iVar9 = GdipGetImageWidth(*(undefined4 *)((int)fVar5 + 4),&local_38);
    if (iVar9 != 0) {
      *(int *)((int)fVar5 + 8) = iVar9;
    }
    local_34 = (byte *)((local_28 - (int)(float)local_3c) - (int)local_2c);
    iVar12 = local_18 + (int)local_30 * -2;
    local_4c = (byte *)((iVar12 * (int)local_4c) / (int)local_38);
    pbVar10 = local_4c;
    if ((int)local_34 < (int)local_4c) {
      iVar12 = ((int)local_34 * iVar12) / (int)local_4c;
      pbVar10 = local_34;
    }
    iVar9 = (local_18 - iVar12) / 2;
    fVar7 = *(float *)((int)local_50 + 4);
    pfVar4 = (float *)GdipDrawImageRectI(param_3,fVar7,iVar9,(int)(float)local_3c,iVar12,pbVar10);
    pfVar3 = local_1c;
    local_58 = local_1c;
    if (pfVar4 != (float *)0x0) {
      pfVar3 = pfVar4;
      local_58 = pfVar4;
    }
  }
  if (*(char *)(puVar11 + 9) == '3') {
    local_50 = (float)(uint)*(ushort *)(puVar11 + 8);
    FUN_00436f60(&local_4c,(byte *)&local_50);
    if (local_4c == DAT_004a2564) {
      local_1c = (float *)&DAT_004a298c;
    }
    else {
      local_1c = (float *)(&DAT_004a298c + local_4c[10]);
    }
  }
  else {
    local_1c = (float *)(puVar11 + 6);
  }
  local_50 = *local_1c;
  if (local_50 != 0.0) {
    local_3c = (byte *)0x0;
    iVar9 = GdipGetImageHeight(*(undefined4 *)((int)local_50 + 4),&local_3c);
    if (iVar9 != 0) {
      *(int *)((int)local_50 + 8) = iVar9;
    }
    local_4c = local_3c;
    local_38 = 0.0;
    local_50 = *local_1c;
    iVar9 = GdipGetImageWidth(*(undefined4 *)((int)local_50 + 4),&local_38);
    if (iVar9 != 0) {
      *(int *)((int)local_50 + 8) = iVar9;
    }
    uVar8 = (uint)DAT_004a29c8;
    local_50 = (float)((int)(uVar8 * (int)local_4c) / (int)local_38);
    fVar5 = local_50;
    if ((int)(uint)DAT_004a29c8 < (int)local_50) {
      uVar8 = (int)(DAT_004a29c8 * uVar8) / (int)local_50;
      fVar5 = (float)(uint)DAT_004a29c8;
    }
    if (*local_1c == 0.0) {
      fVar7 = 0.0;
    }
    else {
      fVar7 = *(float *)((int)*local_1c + 4);
    }
    iVar9 = (int)local_30;
    pfVar4 = (float *)GdipDrawImageRectI(param_3,fVar7,iVar9,(int)local_2c,uVar8,fVar5);
    local_58 = pfVar3;
    if (pfVar4 != (float *)0x0) {
      local_58 = pfVar4;
    }
  }
  uVar6 = DAT_004a29b8;
  if ((*(byte *)((int)puVar11 + 0x26) & 1) == 0) {
    uVar6 = *(undefined4 *)(pbVar2 + local_20 * 4 + 0x20);
  }
  local_68 = &PTR_FUN_0048e4a4;
  local_1c = (float *)0x0;
  local_60 = GdipCreateSolidFill(uVar6,&local_1c);
  iVar12 = (int)local_30;
  local_64 = local_1c;
  fVar13 = roundf((float)(int)*(short *)(pbVar2 + local_20 * 4 + 0x34) * local_24 + (float)iVar12);
  local_50 = (float)DAT_004a29c8 + (float)fVar13;
  local_4c = (byte *)((float)((int)((uint)DAT_004a29c8 - (uint)DAT_004a29ca) / 2) +
                     (float)(int)local_2c);
  pbVar14 = (byte *)(((float)local_18 - local_50) - (float)iVar12);
  pbVar10 = param_3;
  if (((*(byte *)((int)puVar11 + 0x26) & 2) != 0) && (param_7 != '\0')) {
    param_3 = (byte *)((float)pbVar14 - (float)DAT_004a29ce);
    local_40 = (byte *)((float)param_3 + local_50);
    local_3c = local_4c;
    FUN_0040a5d0(&local_5c,fVar7,iVar9,DAT_004a29a4,&local_40,(int)&local_68);
    pbVar10 = local_5c;
    pbVar14 = param_3;
  }
  if ((~(*(byte *)((int)puVar11 + 0x26) >> 4) & 1) != 0) {
    local_3c = (byte *)(float)DAT_004a29c8;
    local_54 = 0;
    local_48 = local_50;
    local_44 = local_4c;
    local_40 = pbVar14;
    local_50 = (float)GdipCreateStringFormat(0,0,&local_54);
    fVar7 = (float)GdipSetStringFormatTrimming(local_54,3);
    if (fVar7 != 0.0) {
      local_50 = fVar7;
    }
    puVar1 = puVar11 + 4;
    if (7 < (uint)puVar11[5]) {
      puVar11 = (undefined4 *)*puVar11;
    }
    FUN_0040a570(&local_5c,puVar11,*puVar1,DAT_004a29a0,&local_48,&local_54,(int)&local_68);
    GdipDeleteStringFormat(local_54);
    pbVar10 = local_5c;
  }
  iVar9 = local_20;
  fVar13 = roundf((float)(int)*(short *)(pbVar2 + local_20 * 4 + 0x2e) * local_24);
  param_3 = (byte *)(float)fVar13;
  iVar12 = local_18;
  if (_DAT_0048d5bc < (float)param_3) {
    local_5c = (byte *)0x0;
    local_58 = (float *)GdipCreatePen1(*(undefined4 *)(pbVar2 + iVar9 * 4 + 0x28),param_3,0,
                                       &local_5c);
    pfVar3 = (float *)GdipSetPenMode(local_5c,1);
    if (pfVar3 != (float *)0x0) {
      local_58 = pfVar3;
    }
    fVar13 = roundf((float)(int)*(short *)(pbVar2 + iVar9 * 4 + 0x2c) * local_24);
    iVar12 = local_18;
    local_50 = (float)fVar13;
    fVar7 = (float)((float)param_3 < DAT_0048f248) + local_50 + local_50;
    GdipDrawRectangle(pbVar10,local_5c,local_50,local_50,(float)local_18 - fVar7,
                      (float)local_28 - fVar7);
    GdipDeletePen(local_5c);
  }
  if (param_6 == '\0') goto LAB_0041b010;
  fVar7 = (float)(iVar12 + -1);
  local_38 = 0.0;
  local_3c = (byte *)0x1;
  local_2c = 0.0;
  param_3 = (byte *)0x1;
  switch(param_6) {
  case 'B':
    local_3c = (byte *)(local_28 + -1);
    local_2c = fVar7;
    break;
  default:
    goto switchD_0041afb6_caseD_43;
  case 'L':
    break;
  case 'R':
    local_38 = fVar7;
    local_2c = fVar7;
    break;
  case 'T':
    local_2c = fVar7;
    goto switchD_0041afb6_caseD_43;
  }
  param_3 = (byte *)(local_28 + -1);
switchD_0041afb6_caseD_43:
  local_5c = (byte *)0x0;
  local_58 = (float *)GdipCreatePen1(*(undefined4 *)(pbVar2 + local_20 * 4 + 0x20),0x40000000,0,
                                     &local_5c);
  GdipDrawLineI(pbVar10,local_5c,local_38,local_3c,local_2c,param_3);
  GdipDeletePen(local_5c);
LAB_0041b010:
  GdipDeleteBrush(local_1c);
LAB_0041b019:
  GdipDeleteGraphics(pbVar10);
  ExceptionList = local_10;
  return;
}



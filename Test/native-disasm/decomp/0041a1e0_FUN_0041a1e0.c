// FUN_0041a1e0 @ 0041a1e0 size=406 callers=1

int * __fastcall FUN_0041a1e0(int *param_1,float param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  float10 fVar5;
  float in_XMM0_Da;
  int *local_10;
  int *local_c;
  float local_8;
  undefined4 local_4;
  
  piVar2 = param_3;
  local_4 = 0;
  local_c = param_1;
  local_8 = param_2;
  if (param_3 == (int *)0x0) {
    piVar4 = (int *)0x10;
  }
  else {
    piVar4 = param_3 + 1;
    param_3 = (int *)0x0;
    iVar3 = GdipGetImageWidth(*piVar4,&param_3);
    if (iVar3 != 0) {
      piVar2[2] = iVar3;
    }
    local_c = param_3;
    local_10 = (int *)0x0;
    iVar3 = GdipGetImageHeight(piVar2[1],&local_10);
    if (iVar3 != 0) {
      piVar2[2] = iVar3;
    }
    param_3 = (int *)0x0;
    if (local_10 < local_c) {
      iVar3 = GdipGetImageWidth(piVar2[1],&param_3);
      piVar4 = param_3;
      if (iVar3 != 0) {
        piVar2[2] = iVar3;
      }
    }
    else {
      iVar3 = GdipGetImageHeight(piVar2[1],&param_3);
      piVar4 = param_3;
      if (iVar3 != 0) {
        piVar2[2] = iVar3;
      }
    }
  }
  piVar1 = (int *)((int)piVar4 * 3);
  param_3 = piVar1;
  local_10 = piVar1;
  FUN_0040e670();
  if (in_XMM0_Da < DAT_0048f22c) {
    fVar5 = roundf((float)(int)piVar1 / in_XMM0_Da);
    param_3 = (int *)(int)fVar5;
  }
  else {
    fVar5 = roundf((float)(int)piVar1 * in_XMM0_Da);
    local_8 = (float)fVar5;
    local_10 = (int *)(int)fVar5;
  }
  FUN_00441e10(param_1,&local_10,&param_3);
  local_c = (int *)0x0;
  if (*param_1 != 0) {
    GdipGetImageGraphicsContext(*(undefined4 *)(*param_1 + 4),&local_c);
  }
  piVar1 = local_c;
  GdipSetPageUnit(local_c,2);
  GdipGraphicsClear(piVar1,0xffffffff);
  if (piVar2 != (int *)0x0) {
    GdipDrawImageI(piVar1,piVar2[1],(int)local_10 / 2 - (int)piVar4 / 2,
                   (int)param_3 / 2 - (int)piVar4 / 2);
  }
  GdipDeleteGraphics(piVar1);
  return param_1;
}



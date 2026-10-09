// FUN_0040af40 @ 0040af40 size=227 callers=3

undefined4 * __fastcall
FUN_0040af40(undefined4 *param_1,HDC param_2,int param_3,int param_4,int param_5,int param_6,
            int param_7,int param_8)

{
  undefined4 uVar1;
  HDC hdcDest;
  undefined4 *puVar2;
  BOOL BVar3;
  undefined4 local_10;
  HDC local_c;
  undefined4 *local_8;
  undefined4 *local_4;
  
  local_c = (HDC)0x26200a;
  local_8 = param_1;
  FUN_00441420(&local_4,&param_7,&param_8,&local_c);
  local_10 = 0;
  if (local_4 != (undefined4 *)0x0) {
    GdipGetImageGraphicsContext(local_4[1],&local_10);
  }
  uVar1 = local_10;
  local_c = (HDC)0x0;
  GdipGetDC(local_10,&local_c);
  hdcDest = local_c;
  SetStretchBltMode(local_c,4);
  BVar3 = StretchBlt(hdcDest,0,0,param_7,param_8,param_2,param_3,param_4,param_5,param_6,0xcc0020);
  GdipReleaseDC(uVar1,hdcDest);
  puVar2 = local_8;
  if (BVar3 != 0) {
    *local_8 = local_4;
    GdipDeleteGraphics(uVar1);
    return puVar2;
  }
  *local_8 = 0;
  GdipDeleteGraphics(uVar1);
  if (local_4 != (undefined4 *)0x0) {
    (**(code **)*local_4)(1);
  }
  return puVar2;
}



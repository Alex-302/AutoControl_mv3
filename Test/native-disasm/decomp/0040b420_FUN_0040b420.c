// FUN_0040b420 @ 0040b420 size=135 callers=1

int __fastcall FUN_0040b420(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  undefined4 local_c;
  undefined4 local_8;
  float local_4;
  
  local_c = 0;
  GdipCreateFromHWND(*(undefined4 *)
                      (&DAT_004a2470 + *(int *)(*(int *)ThreadLocalStoragePointer + 4) * 4),&local_c
                    );
  uVar1 = local_c;
  GdipGetDpiY(local_c,&local_8);
  iVar2 = GdipGetFontHeightGivenDPI(*param_1,local_8,&local_4);
  if (iVar2 != 0) {
    param_1[1] = iVar2;
  }
  fVar3 = roundf(local_4);
  local_4 = (float)fVar3;
  GdipDeleteGraphics(uVar1);
  return (int)local_4;
}



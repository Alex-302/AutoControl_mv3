// FUN_00441490 @ 00441490 size=119 callers=1

int * __fastcall FUN_00441490(int *param_1,undefined4 *param_2,int *param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int *local_4;
  
  local_4 = param_1;
  puVar1 = (undefined4 *)GdipAlloc(8);
  if (puVar1 == (undefined4 *)0x0) {
    *param_1 = 0;
    return param_1;
  }
  local_4 = (int *)0x0;
  if (*param_3 != 0) {
    uVar2 = GdipCreateFontFromLogfontA(*param_2,*param_3,&local_4);
    puVar1[1] = uVar2;
    *puVar1 = local_4;
    *param_1 = (int)puVar1;
    return param_1;
  }
  uVar2 = GdipCreateFontFromDC(*param_2,&local_4);
  puVar1[1] = uVar2;
  *puVar1 = local_4;
  *param_1 = (int)puVar1;
  return param_1;
}



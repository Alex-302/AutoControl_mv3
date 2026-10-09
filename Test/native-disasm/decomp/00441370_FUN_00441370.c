// FUN_00441370 @ 00441370 size=82 callers=1

undefined4 * __fastcall FUN_00441370(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *local_4;
  
  local_4 = param_1;
  puVar1 = (undefined4 *)GdipAlloc(0x10);
  if (puVar1 != (undefined4 *)0x0) {
    uVar2 = *param_2;
    *puVar1 = &PTR_FUN_0048ed48;
    local_4 = (undefined4 *)0x0;
    uVar2 = GdipCreateBitmapFromStream(uVar2,&local_4);
    puVar1[2] = uVar2;
    puVar1[1] = local_4;
    *param_1 = puVar1;
    return param_1;
  }
  *param_1 = 0;
  return param_1;
}



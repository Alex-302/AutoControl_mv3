// FUN_00441e10 @ 00441e10 size=101 callers=1

undefined4 * __fastcall FUN_00441e10(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 *local_4;
  
  local_4 = param_1;
  puVar2 = (undefined4 *)GdipAlloc(0x10);
  if (puVar2 != (undefined4 *)0x0) {
    uVar3 = *param_2;
    uVar1 = *param_3;
    *puVar2 = &PTR_FUN_0048ed48;
    local_4 = (undefined4 *)0x0;
    uVar3 = GdipCreateBitmapFromScan0(uVar3,uVar1,0,0x26200a,0,&local_4);
    puVar2[2] = uVar3;
    puVar2[1] = local_4;
    *param_1 = puVar2;
    return param_1;
  }
  *param_1 = 0;
  return param_1;
}



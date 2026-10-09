// FUN_00441420 @ 00441420 size=103 callers=2

undefined4 * __fastcall
FUN_00441420(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *local_4;
  
  local_4 = param_1;
  puVar3 = (undefined4 *)GdipAlloc(0x10);
  if (puVar3 != (undefined4 *)0x0) {
    uVar4 = *param_3;
    uVar1 = *param_4;
    uVar2 = *param_2;
    *puVar3 = &PTR_FUN_0048ed48;
    local_4 = (undefined4 *)0x0;
    uVar4 = GdipCreateBitmapFromScan0(uVar2,uVar4,0,uVar1,0,&local_4);
    puVar3[2] = uVar4;
    puVar3[1] = local_4;
    *param_1 = puVar3;
    return param_1;
  }
  *param_1 = 0;
  return param_1;
}



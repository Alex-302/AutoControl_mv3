// FUN_004057a0 @ 004057a0 size=267 callers=2

undefined4 * __fastcall FUN_004057a0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  uint *puVar3;
  CHAR local_58 [24];
  short local_40 [4];
  LPCWSTR pWStack_38;
  undefined4 uStack_34;
  undefined4 *local_2c;
  undefined4 local_28;
  int *local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  puStack_18 = &LAB_00479417;
  local_1c = ExceptionList;
  ExceptionList = &local_1c;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 0xf;
  param_1[4] = 0;
  puVar1 = param_1;
  if (0xf < (uint)param_1[5]) {
    puVar1 = (undefined4 *)*param_1;
  }
  *(undefined1 *)puVar1 = 0;
  local_28 = 1;
  local_24 = (int *)0x0;
  local_14 = 1;
  local_2c = param_1;
  iVar2 = SHGetPropertyStoreForWindow(param_2,&DAT_00483d14,&local_24);
  if (iVar2 == 0) {
    local_40[0] = 0;
    local_40[1] = 0;
    local_40[2] = 0;
    local_40[3] = 0;
    pWStack_38 = (LPCWSTR)0x0;
    uStack_34 = 0;
    iVar2 = (**(code **)(*local_24 + 0x14))(local_24,&DAT_00483d34,local_40);
    if ((-1 < iVar2) && (local_40[0] == 0x1f)) {
      puVar3 = (uint *)FUN_004044f0(local_58,pWStack_38,-1,0x7fffffff);
      FUN_00435570(param_1,puVar3);
      FUN_004061c0((undefined4 *)local_58);
    }
    PropVariantClear((PROPVARIANT *)local_40);
  }
  local_14 = 2;
  if (local_24 != (int *)0x0) {
    (**(code **)(*local_24 + 8))(local_24);
  }
  ExceptionList = local_1c;
  return param_1;
}



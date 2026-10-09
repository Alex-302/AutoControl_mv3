// FUN_00426e50 @ 00426e50 size=219 callers=2

undefined1 * __cdecl FUN_00426e50(undefined1 *param_1)

{
  int *piVar1;
  undefined **local_44 [9];
  undefined ***local_20;
  uint local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047b2e8;
  local_10 = ExceptionList;
  local_14 = 0;
  if ((DAT_0049da5e == -0x8000) && (DAT_004a2444 == '\0')) {
    local_20 = local_44;
    local_44[0] = &PTR_LAB_0048e3d0;
    local_8 = 0;
    ExceptionList = &local_10;
    piVar1 = FUN_0040f6b0(DAT_004a23dc,(int *)local_20,0);
    *(undefined8 *)(param_1 + 8) = 0;
    local_1c = CONCAT31(local_1c._1_3_,piVar1 != (int *)0x0);
    *(uint *)(param_1 + 8) = local_1c;
    *param_1 = 4;
    *(undefined4 *)(param_1 + 0xc) = local_18;
    if (local_20 != (undefined ***)0x0) {
      (*(code *)(*local_20)[4])(local_20 != local_44);
    }
    ExceptionList = local_10;
    return param_1;
  }
  local_1c = local_1c & 0xffffff00;
  *(undefined8 *)(param_1 + 8) = 0;
  *(uint *)(param_1 + 8) = local_1c;
  *(undefined4 *)(param_1 + 0xc) = local_18;
  *param_1 = 4;
  return param_1;
}



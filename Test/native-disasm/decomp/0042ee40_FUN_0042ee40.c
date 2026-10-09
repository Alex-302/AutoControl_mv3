// FUN_0042ee40 @ 0042ee40 size=247 callers=1

void * __cdecl FUN_0042ee40(void *param_1,undefined4 param_2)

{
  LPSTR pCVar1;
  undefined **local_54;
  void **local_50;
  undefined4 local_4c;
  void *local_44 [4];
  undefined4 local_34;
  undefined ***local_30;
  void *local_2c [4];
  undefined4 local_1c;
  uint local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_0047d2f8;
  local_10 = ExceptionList;
  local_14 = 0;
  local_18 = 7;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffff0000);
  local_50 = local_2c;
  local_4c = param_2;
  local_30 = &local_54;
  local_54 = &PTR_LAB_0048f0d0;
  local_8 = 1;
  uStack_7 = 0;
  ExceptionList = &local_10;
  FUN_0040f7a0(DAT_004a23dc,(int *)local_30);
  local_8 = 0;
  if (local_30 != (undefined ***)0x0) {
    (*(code *)(*local_30)[4])(local_30 != &local_54);
  }
  pCVar1 = FUN_00404580((LPSTR)local_44,(LPCWSTR)local_2c,0x7fffffff);
  _local_8 = CONCAT31(uStack_7,2);
  FUN_00440c80(param_1,(undefined4 *)pCVar1);
  if (&DAT_0000000f < local_30) {
    FUN_00402430(local_44[0],(uint)((int)local_30 + 1),1);
  }
  local_30 = (undefined ***)0xf;
  local_34 = 0;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  if (7 < local_18) {
    FUN_00402430(local_2c[0],local_18 + 1,2);
  }
  ExceptionList = local_10;
  return param_1;
}



// FUN_0042e4e0 @ 0042e4e0 size=226 callers=1

void * __cdecl FUN_0042e4e0(void *param_1,void *param_2)

{
  LPCWSTR pWVar1;
  LPSTR pCVar2;
  void *local_5c [5];
  uint local_48;
  void *local_44 [4];
  undefined4 local_34;
  uint local_30;
  void *local_2c [4];
  undefined4 local_1c;
  uint local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d218;
  local_10 = ExceptionList;
  local_14 = 0;
  ExceptionList = &local_10;
  FUN_00440d90(param_2,local_5c);
  local_8 = 0;
  pWVar1 = FUN_0042e190((undefined2 *)local_44,local_5c);
  local_8._0_1_ = 1;
  pCVar2 = FUN_00404580((LPSTR)local_2c,pWVar1,0x7fffffff);
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_00440c80(param_1,(undefined4 *)pCVar2);
  if (0xf < local_18) {
    FUN_00402430(local_2c[0],local_18 + 1,1);
  }
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  if (7 < local_30) {
    FUN_00402430(local_44[0],local_30 + 1,2);
  }
  local_30 = 7;
  local_34 = 0;
  local_44[0] = (void *)((uint)local_44[0] & 0xffff0000);
  if (0xf < local_48) {
    FUN_00402430(local_5c[0],local_48 + 1,1);
  }
  ExceptionList = local_10;
  return param_1;
}



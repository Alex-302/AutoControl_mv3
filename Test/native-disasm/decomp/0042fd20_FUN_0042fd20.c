// FUN_0042fd20 @ 0042fd20 size=178 callers=1

void * __cdecl FUN_0042fd20(void *param_1,char *param_2)

{
  LPWSTR pWVar1;
  LPSTR pCVar2;
  void *local_48 [5];
  uint local_34;
  void *local_30 [4];
  undefined4 local_20;
  uint local_1c;
  undefined4 local_18;
  DWORD local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d530;
  local_10 = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_10;
  FUN_00453810(param_2,&local_14);
  pWVar1 = FUN_00405650((LPWSTR)local_48,local_14);
  local_8 = 0;
  pCVar2 = FUN_00404580((LPSTR)local_30,pWVar1,0x7fffffff);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00440c80(param_1,(undefined4 *)pCVar2);
  if (0xf < local_1c) {
    FUN_00402430(local_30[0],local_1c + 1,1);
  }
  local_1c = 0xf;
  local_20 = 0;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  if (7 < local_34) {
    FUN_00402430(local_48[0],local_34 + 1,2);
  }
  ExceptionList = local_10;
  return param_1;
}



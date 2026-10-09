// FUN_0042fde0 @ 0042fde0 size=220 callers=1

undefined1 * __cdecl FUN_0042fde0(undefined1 *param_1,char *param_2)

{
  uint uVar1;
  LPSTR pCVar2;
  undefined1 *extraout_ECX;
  WCHAR local_23c [262];
  void *local_30 [5];
  uint local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d548;
  local_10 = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_10;
  _memset(local_23c,0,0x208);
  FUN_004536b0(param_2,&local_14);
  uVar1 = SHGetFolderPathW(0,local_14 | 0x8000,0,0,local_23c);
  if (uVar1 != 0) {
    *param_1 = 0;
    *(undefined8 *)(param_1 + 8) = 0;
    FUN_00450f50(param_1,uVar1 & 0xffff);
    ExceptionList = local_10;
    return extraout_ECX;
  }
  pCVar2 = FUN_004044f0((LPSTR)local_30,local_23c,-1,0x7fffffff);
  local_8 = 0;
  FUN_00440c80(param_1,(undefined4 *)pCVar2);
  if (0xf < local_1c) {
    FUN_00402430(local_30[0],local_1c + 1,1);
  }
  ExceptionList = local_10;
  return param_1;
}



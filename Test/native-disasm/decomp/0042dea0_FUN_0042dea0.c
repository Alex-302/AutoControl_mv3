// FUN_0042dea0 @ 0042dea0 size=742 callers=1

undefined1 * __cdecl FUN_0042dea0(undefined1 *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *this;
  LPCWSTR pszSound;
  BOOL BVar3;
  LPCSTR pszSound_00;
  uint uVar4;
  void **ppvVar5;
  void *local_4c [5];
  uint local_38;
  void *local_34 [4];
  undefined4 local_24;
  uint local_20;
  int *local_1c;
  int *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d1b8;
  local_10 = ExceptionList;
  local_14 = 0;
  local_20 = 0xf;
  local_24 = 0;
  local_34[0] = (void *)((uint)local_34[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_34,(uint *)&DAT_0048db28,4);
  local_8 = 0;
  cVar1 = FUN_00441100(param_2,local_34);
  local_8 = 0xffffffff;
  uVar4 = -(uint)(cVar1 != '\0') & 8;
  if (0xf < local_20) {
    FUN_00402430(local_34[0],local_20 + 1,1);
  }
  local_20 = 0xf;
  local_24 = 0;
  local_34[0] = (void *)((uint)local_34[0] & 0xffffff00);
  FUN_0043ace0(local_34,(uint *)"filePath",8);
  if (*param_2 == '\x01') {
    FUN_004437f0(*(void **)(param_2 + 8),(int *)&local_1c,(byte *)local_34);
    iVar2 = FUN_00447a70(local_1c,local_18);
  }
  else {
    iVar2 = 0;
  }
  if (0xf < local_20) {
    FUN_00402430(local_34[0],local_20 + 1,1);
  }
  if (iVar2 == 0) {
    local_20 = 0xf;
    local_24 = 0;
    local_34[0] = (void *)((uint)local_34[0] & 0xffffff00);
    FUN_0043ace0(local_34,(uint *)"sysEvent",8);
    if (*param_2 == '\x01') {
      FUN_004437f0(*(void **)(param_2 + 8),(int *)&local_1c,(byte *)local_34);
      iVar2 = FUN_00447a70(local_1c,local_18);
    }
    else {
      iVar2 = 0;
    }
    if (0xf < local_20) {
      FUN_00402430(local_34[0],local_20 + 1,1);
    }
    if (iVar2 == 0) {
      BVar3 = PlaySoundA((LPCSTR)0x0,(HMODULE)0x0,0);
      local_1c = (int *)CONCAT31(local_1c._1_3_,BVar3 != 0);
      *(undefined8 *)(param_1 + 8) = 0;
      *(int **)(param_1 + 8) = local_1c;
      *(int **)(param_1 + 0xc) = local_18;
      *param_1 = 4;
      ExceptionList = local_10;
      return param_1;
    }
    FUN_004355e0(local_4c,(uint *)"sysEvent");
    local_8 = 2;
    pszSound_00 = (LPCSTR)FUN_004342f0(param_2,local_34,local_4c,(uint *)&DAT_0048e75c);
    if (0xf < *(uint *)(pszSound_00 + 0x14)) {
      pszSound_00 = *(LPCSTR *)pszSound_00;
    }
    BVar3 = PlaySoundA(pszSound_00,(HMODULE)0x0,uVar4 | 0x210003);
    local_1c = (int *)CONCAT31(local_1c._1_3_,BVar3 != 0);
    *(undefined8 *)(param_1 + 8) = 0;
    *(int **)(param_1 + 8) = local_1c;
    *(int **)(param_1 + 0xc) = local_18;
    *param_1 = 4;
    if (0xf < local_20) {
      FUN_00402430(local_34[0],local_20 + 1,1);
    }
    local_20 = 0xf;
    local_34[0] = (void *)((uint)local_34[0] & 0xffffff00);
  }
  else {
    ppvVar5 = local_4c;
    this = FUN_00440e70(param_2,(uint *)"filePath");
    FUN_00440d90(this,ppvVar5);
    local_8 = 1;
    pszSound = FUN_00404640((LPWSTR)local_34,(LPCSTR)local_4c);
    if (7 < *(uint *)(pszSound + 10)) {
      pszSound = *(LPCWSTR *)pszSound;
    }
    BVar3 = PlaySoundW(pszSound,(HMODULE)0x0,uVar4 | 0x220003);
    local_1c = (int *)CONCAT31(local_1c._1_3_,BVar3 != 0);
    *(undefined8 *)(param_1 + 8) = 0;
    *(int **)(param_1 + 8) = local_1c;
    *(int **)(param_1 + 0xc) = local_18;
    *param_1 = 4;
    if (7 < local_20) {
      FUN_00402430(local_34[0],local_20 + 1,2);
    }
    local_20 = 7;
    local_34[0] = (void *)((uint)local_34[0] & 0xffff0000);
  }
  local_24 = 0;
  if (0xf < local_38) {
    FUN_00402430(local_4c[0],local_38 + 1,1);
  }
  ExceptionList = local_10;
  return param_1;
}



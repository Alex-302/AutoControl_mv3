// FUN_0042ab40 @ 0042ab40 size=531 callers=1

char * __cdecl FUN_0042ab40(char *param_1,HWND param_2)

{
  undefined8 uVar1;
  HWND pHVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  HWND pHVar6;
  DWORD DVar7;
  uint dwNewLong;
  LONG *pLVar8;
  bool bVar9;
  void *local_64 [4];
  undefined4 local_54;
  uint local_50;
  void *local_4c [4];
  undefined4 local_3c;
  uint local_38;
  char local_34 [8];
  undefined8 local_2c;
  undefined8 local_24;
  POINT local_1c;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ca09;
  local_10 = ExceptionList;
  bVar9 = false;
  local_14 = 0;
  local_38 = 0xf;
  local_3c = 0;
  local_4c[0] = (void *)((uint)local_4c[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_4c,(uint *)&DAT_0048d65c,1);
  pHVar6 = param_2;
  if ((char)param_2->unused == '\x01') {
    FUN_004437f0((void *)param_2[2].unused,&local_1c.x,(byte *)local_4c);
    iVar4 = FUN_00447a70((int *)local_1c.x,(int *)local_1c.y);
  }
  else {
    iVar4 = 0;
  }
  if (0xf < local_38) {
    FUN_00402430(local_4c[0],local_38 + 1,1);
  }
  local_38 = 0xf;
  local_3c = 0;
  local_4c[0] = (void *)((uint)local_4c[0] & 0xffffff00);
  if (iVar4 == 0) {
    local_50 = 0xf;
    local_54 = 0;
    local_64[0] = (void *)((uint)local_64[0] & 0xffffff00);
    FUN_0043ace0(local_64,(uint *)"usePrvMsPos",0xb);
    local_8 = 0;
    bVar9 = true;
    local_14 = 1;
    cVar3 = FUN_00441100(pHVar6,local_64);
    if (cVar3 == '\0') {
      local_24 = FUN_00410800('\0');
    }
    else {
      local_24 = CONCAT44(DAT_004a23e4,DAT_004a23e0);
    }
    pLVar8 = (LONG *)&local_2c;
    local_2c = local_24;
  }
  else {
    pcVar5 = (char *)FUN_00440e70(pHVar6,(uint *)&DAT_0048d65c);
    FUN_004536b0(pcVar5,(uint *)&param_2);
    pHVar2 = param_2;
    pcVar5 = (char *)FUN_00440e70(pHVar6,(uint *)&DAT_0048d660);
    FUN_004536b0(pcVar5,(uint *)&param_2);
    pLVar8 = (LONG *)&local_24;
    local_24 = CONCAT44(param_2,pHVar2);
  }
  local_1c.x = *pLVar8;
  local_1c.y = pLVar8[1];
  if ((bVar9) && (0xf < local_50)) {
    FUN_00402430(local_64[0],local_50 + 1,1);
  }
  pHVar6 = FUN_00404e30(&local_1c,'\0');
  param_2 = pHVar6;
  DVar7 = GetWindowThreadProcessId(pHVar6,(LPDWORD)0x0);
  if (DVar7 == DAT_004a2450) {
    dwNewLong = GetWindowLongA(pHVar6,-0x14);
    SetWindowLongA(pHVar6,-0x14,dwNewLong | 0x20);
    pHVar6 = FUN_00404e30(&local_1c,'\0');
    SetWindowLongA(param_2,-0x14,dwNewLong);
  }
  local_34[0] = '\0';
  local_2c = 0;
  *param_1 = '\0';
  param_1[8] = '\0';
  param_1[9] = '\0';
  param_1[10] = '\0';
  param_1[0xb] = '\0';
  param_1[0xc] = '\0';
  param_1[0xd] = '\0';
  param_1[0xe] = '\0';
  param_1[0xf] = '\0';
  FUN_00450f50(local_34,(int)pHVar6);
  cVar3 = *param_1;
  *param_1 = local_34[0];
  uVar1 = *(undefined8 *)(param_1 + 8);
  *(LONG *)(param_1 + 8) = (LONG)local_2c;
  *(undefined4 *)(param_1 + 0xc) = local_2c._4_4_;
  local_34[0] = cVar3;
  local_2c = uVar1;
  FUN_00434820(local_34);
  ExceptionList = local_10;
  return param_1;
}



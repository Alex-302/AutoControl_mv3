// FUN_0042c1c0 @ 0042c1c0 size=169 callers=1

void __fastcall FUN_0042c1c0(void *param_1)

{
  char *pcVar1;
  uint uVar2;
  void *local_2c [4];
  undefined4 local_1c;
  uint local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047cc88;
  local_10 = ExceptionList;
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_2c,(uint *)"trigInstId",10);
  local_8 = 0;
  pcVar1 = (char *)FUN_00440dd0(param_1,(uint *)"evtId");
  FUN_00453970(pcVar1,(ushort *)&local_14);
  uVar2 = FUN_004409d0(param_1,local_2c,0);
  DAT_004a26c4 = (undefined1)uVar2;
  DAT_004a26b4 = GetTickCount();
  FUN_00413390(local_14,'\x01');
  if (0xf < local_18) {
    FUN_00402430(local_2c[0],local_18 + 1,1);
  }
  ExceptionList = local_10;
  return;
}



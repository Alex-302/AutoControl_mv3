// FUN_0042b520 @ 0042b520 size=447 callers=1

undefined1 * __cdecl FUN_0042b520(undefined1 *param_1,void *param_2)

{
  char *pcVar1;
  uint *puVar2;
  undefined4 *this;
  undefined4 *puVar3;
  uint uVar4;
  char **ppcVar5;
  undefined4 local_64 [4];
  char *local_54;
  undefined8 local_50;
  int local_48;
  void *local_40 [2];
  int local_38;
  void *local_34;
  undefined4 local_30;
  int local_2c;
  void *local_28;
  undefined4 local_24;
  int local_20;
  uint local_1c;
  uint local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047cbdb;
  local_10 = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_10;
  pcVar1 = (char *)FUN_00440e70(param_2,(uint *)"state");
  FUN_00453610(pcVar1,&local_11);
  DAT_004a23a3 = local_11;
  if (local_11 == '\0') {
    puVar3 = local_64;
    this = FUN_00440e70(param_2,(uint *)&DAT_0048da44);
    FUN_004340a0(this,puVar3);
    ppcVar5 = &local_54;
    puVar3 = FUN_00440e70(param_2,(uint *)&DAT_0048da44);
    FUN_00434120(puVar3,ppcVar5);
    local_1c = local_1c & 0xffffff00;
    local_28 = (void *)0x0;
    local_24 = 0;
    local_20 = 0;
    FUN_0044a270(&local_28,local_54,local_50,local_48);
    local_8 = 1;
    local_18 = 2;
    puVar2 = FUN_0040cab0((uint *)&local_34,&local_28);
    local_8 = 2;
    uVar4 = 6;
  }
  else {
    puVar2 = (uint *)FUN_0040c920((int *)local_40);
    local_8 = 0;
    uVar4 = 1;
  }
  *param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  local_18 = uVar4;
  FUN_0044ddf0(param_1,puVar2);
  if ((uVar4 & 4) != 0) {
    uVar4 = uVar4 & 0xfffffffb;
    if (local_34 != (void *)0x0) {
      FUN_00402430(local_34,local_2c - (int)local_34 >> 1,2);
      local_34 = (void *)0x0;
      local_30 = 0;
      local_2c = 0;
    }
  }
  if ((uVar4 & 2) != 0) {
    uVar4 = uVar4 & 0xfffffffd;
    if (local_28 != (void *)0x0) {
      FUN_00402430(local_28,local_20 - (int)local_28 >> 1,2);
    }
  }
  if (((uVar4 & 1) != 0) && (local_40[0] != (void *)0x0)) {
    FUN_00402430(local_40[0],local_38 - (int)local_40[0] >> 1,2);
  }
  ExceptionList = local_10;
  return param_1;
}



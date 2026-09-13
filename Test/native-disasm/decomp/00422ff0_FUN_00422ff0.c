// FUN_00422ff0 @ 00422ff0 size=309 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00422ff0(void)

{
  DWORD DVar1;
  uint *puVar2;
  undefined4 *puVar3;
  void *local_70 [5];
  uint local_5c;
  void *local_58 [5];
  uint local_44;
  void *local_40 [4];
  undefined4 local_30;
  uint local_2c;
  void *local_28 [4];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047be10;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  DVar1 = GetTickCount();
  if (10000 < DVar1 - _DAT_0049fc34) {
    _DAT_0049fc34 = DVar1;
    puVar2 = (uint *)FUN_00403380((undefined2 *)local_58);
    local_8 = 0;
    puVar3 = (undefined4 *)FUN_00441ee0((undefined2 *)local_28,puVar2,(uint *)L".tabs");
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_004229b0(0x4a290c,puVar3);
    if (7 < local_14) {
      FUN_00402430(local_28[0],local_14 + 1,2);
    }
    local_8 = 0xffffffff;
    local_28[0] = (void *)((uint)local_28[0] & 0xffff0000);
    local_14 = 7;
    local_18 = 0;
    if (7 < local_44) {
      FUN_00402430(local_58[0],local_44 + 1,2);
    }
    puVar2 = (uint *)FUN_00403380((undefined2 *)local_70);
    local_8 = 2;
    puVar3 = (undefined4 *)FUN_00441ee0((undefined2 *)local_40,puVar2,(uint *)L".sess");
    local_8 = CONCAT31(local_8._1_3_,3);
    FUN_004229b0(0x4a292c,puVar3);
    if (7 < local_2c) {
      FUN_00402430(local_40[0],local_2c + 1,2);
    }
    local_2c = 7;
    local_40[0] = (void *)((uint)local_40[0] & 0xffff0000);
    local_30 = 0;
    if (7 < local_5c) {
      FUN_00402430(local_70[0],local_5c + 1,2);
    }
  }
  ExceptionList = local_10;
  return;
}



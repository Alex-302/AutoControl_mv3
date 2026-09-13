// FUN_00445320 @ 00445320 size=462 callers=3

void __fastcall FUN_00445320(int param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  void *local_94 [5];
  uint local_80;
  void *pvStack_7c;
  undefined1 *puStack_78;
  undefined4 local_74;
  void *local_70 [4];
  undefined4 local_60;
  uint local_5c;
  void *local_58 [4];
  undefined4 local_48;
  uint local_44;
  undefined4 **local_40 [4];
  undefined4 local_30;
  uint local_2c;
  undefined4 **local_28;
  undefined1 local_24;
  void *local_20 [3];
  undefined **local_14;
  undefined8 local_10;
  uint local_8;
  
  local_74 = 0xffffffff;
  puStack_78 = &LAB_0047e3ec;
  pvStack_7c = ExceptionList;
  local_8 = 0;
  local_2c = 0xf;
  local_30 = 0;
  local_40[0] = (undefined4 **)((uint)local_40[0] & 0xffffff00);
  ExceptionList = &pvStack_7c;
  FUN_0043ace0(local_40,(uint *)"parse error - unexpected ",0x19);
  local_74 = 0;
  if (*(int *)(param_1 + 0x30) == 0xe) {
    puVar1 = (uint *)FUN_004459d0((void *)(param_1 + 0x34),(undefined1 *)local_94);
    local_74 = CONCAT31(local_74._1_3_,1);
    local_8 = 1;
    puVar1 = (uint *)FUN_00442600((undefined1 *)local_70,(uint *)&DAT_0048e050,puVar1);
    local_74 = 2;
    local_8 = 3;
    puVar2 = (undefined4 *)FUN_004412a0((undefined1 *)local_58,puVar1,(uint *)&DAT_0048e050);
    local_74 = 3;
    uVar3 = 7;
  }
  else {
    puVar2 = (undefined4 *)FUN_00446250((undefined1 *)local_20,*(int *)(param_1 + 0x30));
    local_74 = 4;
    uVar3 = 8;
  }
  local_8 = uVar3;
  FUN_0043b0c0(local_40,puVar2,0,0xffffffff);
  if ((uVar3 & 8) != 0) {
    uVar3 = uVar3 & 0xfffffff7;
    if (0xf < local_10._4_4_) {
      FUN_00402430(local_20[0],local_10._4_4_ + 1,1);
    }
    local_10 = 0xf00000000;
    local_20[0] = (void *)((uint)local_20[0] & 0xffffff00);
  }
  if ((uVar3 & 4) != 0) {
    uVar3 = uVar3 & 0xfffffffb;
    if (0xf < local_44) {
      FUN_00402430(local_58[0],local_44 + 1,1);
    }
    local_44 = 0xf;
    local_48 = 0;
    local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
  }
  if ((uVar3 & 2) != 0) {
    uVar3 = uVar3 & 0xfffffffd;
    if (0xf < local_5c) {
      FUN_00402430(local_70[0],local_5c + 1,1);
    }
    local_5c = 0xf;
    local_60 = 0;
    local_70[0] = (void *)((uint)local_70[0] & 0xffffff00);
  }
  local_74 = 0;
  if (((uVar3 & 1) != 0) && (0xf < local_80)) {
    FUN_00402430(local_94[0],local_80 + 1,1);
  }
  local_14 = std::exception::vftable;
  local_28 = local_40;
  if (0xf < local_2c) {
    local_28 = local_40[0];
  }
  local_10 = 0;
  local_24 = 1;
  ___std_exception_copy(&local_28,(undefined4 *)&local_10);
  local_14 = std::invalid_argument::vftable;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)&local_14,&DAT_00499edc);
}



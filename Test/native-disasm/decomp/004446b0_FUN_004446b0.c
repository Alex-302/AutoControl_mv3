// FUN_004446b0 @ 004446b0 size=620 callers=5

void __thiscall FUN_004446b0(void *this,int param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  void *local_94 [5];
  uint local_80;
  void *local_7c [4];
  undefined4 local_6c;
  uint local_68;
  void *local_64 [4];
  undefined4 local_54;
  uint local_50;
  undefined4 **local_4c [4];
  undefined4 local_3c;
  uint local_38;
  void *local_34 [3];
  undefined **local_28;
  undefined8 local_24;
  undefined4 **local_1c;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e322;
  local_10 = ExceptionList;
  local_18 = 0;
  if (param_1 != *(int *)((int)this + 0x30)) {
    local_38 = 0xf;
    local_3c = 0;
    local_4c[0] = (undefined4 **)((uint)local_4c[0] & 0xffffff00);
    ExceptionList = &local_10;
    FUN_0043ace0(local_4c,(uint *)"parse error - unexpected ",0x19);
    local_8 = 0;
    if (*(int *)((int)this + 0x30) == 0xe) {
      puVar1 = (uint *)FUN_004459d0((void *)((int)this + 0x34),(undefined1 *)local_94);
      local_8 = CONCAT31(local_8._1_3_,1);
      local_18 = 1;
      puVar1 = (uint *)FUN_00442600((undefined1 *)local_7c,(uint *)&DAT_0048e050,puVar1);
      local_8 = 2;
      local_18 = 3;
      puVar2 = (undefined4 *)FUN_004412a0((undefined1 *)local_64,puVar1,(uint *)&DAT_0048e050);
      local_8 = 3;
      uVar3 = 7;
    }
    else {
      puVar2 = (undefined4 *)FUN_00446250((undefined1 *)local_34,*(int *)((int)this + 0x30));
      local_8 = 4;
      uVar3 = 8;
    }
    local_18 = uVar3;
    FUN_0043b0c0(local_4c,puVar2,0,0xffffffff);
    if ((uVar3 & 8) != 0) {
      uVar3 = uVar3 & 0xfffffff7;
      if (0xf < local_24._4_4_) {
        FUN_00402430(local_34[0],local_24._4_4_ + 1,1);
      }
      local_24 = 0xf00000000;
      local_34[0] = (void *)((uint)local_34[0] & 0xffffff00);
    }
    if ((uVar3 & 4) != 0) {
      uVar3 = uVar3 & 0xfffffffb;
      if (0xf < local_50) {
        FUN_00402430(local_64[0],local_50 + 1,1);
      }
      local_50 = 0xf;
      local_54 = 0;
      local_64[0] = (void *)((uint)local_64[0] & 0xffffff00);
    }
    if ((uVar3 & 2) != 0) {
      uVar3 = uVar3 & 0xfffffffd;
      if (0xf < local_68) {
        FUN_00402430(local_7c[0],local_68 + 1,1);
      }
      local_68 = 0xf;
      local_6c = 0;
      local_7c[0] = (void *)((uint)local_7c[0] & 0xffffff00);
    }
    local_8 = 0;
    if (((uVar3 & 1) != 0) && (0xf < local_80)) {
      FUN_00402430(local_94[0],local_80 + 1,1);
    }
    puVar1 = (uint *)FUN_00446250((undefined1 *)local_94,param_1);
    local_8._0_1_ = 5;
    puVar2 = (undefined4 *)FUN_00442600((undefined1 *)local_7c,(uint *)"; expected ",puVar1);
    local_8 = CONCAT31(local_8._1_3_,6);
    FUN_0043b0c0(local_4c,puVar2,0,0xffffffff);
    if (0xf < local_68) {
      FUN_00402430(local_7c[0],local_68 + 1,1);
    }
    local_8 = local_8 & 0xffffff00;
    local_68 = 0xf;
    local_6c = 0;
    local_7c[0] = (void *)((uint)local_7c[0] & 0xffffff00);
    if (0xf < local_80) {
      FUN_00402430(local_94[0],local_80 + 1,1);
    }
    local_28 = std::exception::vftable;
    local_1c = local_4c;
    if (0xf < local_38) {
      local_1c = local_4c[0];
    }
    local_24 = 0;
    local_18 = CONCAT31(local_18._1_3_,1);
    ___std_exception_copy(&local_1c,(undefined4 *)&local_24);
    local_28 = std::invalid_argument::vftable;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_28,&DAT_00499edc);
  }
  return;
}



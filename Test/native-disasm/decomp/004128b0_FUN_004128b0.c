// FUN_004128b0 @ 004128b0 size=455 callers=1

void * __thiscall FUN_004128b0(void *this,void *param_1)

{
  char cVar1;
  uint *puVar2;
  undefined1 *puVar3;
  uint uVar4;
  void *local_48 [4];
  undefined4 local_38;
  uint local_34;
  void *local_30 [4];
  undefined4 local_20;
  uint local_1c;
  void *local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0047ab46;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x14) = 0xf;
  *(undefined4 *)((int)this + 0x10) = 0;
  puVar3 = this;
  if (0xf < *(uint *)((int)this + 0x14)) {
    puVar3 = *(undefined1 **)this;
  }
  *puVar3 = 0;
  local_8 = 0;
  local_1c = 0xf;
  local_20 = 0;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  local_18 = this;
  FUN_0043ace0(local_30,(uint *)"style",5);
  local_8 = CONCAT31(local_8._1_3_,1);
  puVar2 = FUN_004342f0(param_1,local_48,local_30,(uint *)"_default_");
  if (this != puVar2) {
    if (0xf < *(uint *)((int)this + 0x14)) {
      FUN_00402430(*(void **)this,*(int *)((int)this + 0x14) + 1,1);
    }
    *(undefined4 *)((int)this + 0x14) = 0xf;
    *(undefined4 *)((int)this + 0x10) = 0;
    puVar3 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      puVar3 = *(undefined1 **)this;
    }
    *puVar3 = 0;
    FUN_0043b1c0(this,puVar2);
  }
  if (0xf < local_34) {
    FUN_00402430(local_48[0],local_34 + 1,1);
  }
  local_8 = local_8 & 0xffffff00;
  local_34 = 0xf;
  local_38 = 0;
  local_48[0] = (void *)((uint)local_48[0] & 0xffffff00);
  if (0xf < local_1c) {
    FUN_00402430(local_30[0],local_1c + 1,1);
  }
  local_1c = 0xf;
  local_20 = 0;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  FUN_0043ace0(local_30,(uint *)"layout",6);
  local_8._0_1_ = 3;
  uVar4 = FUN_004409d0(param_1,local_30,0x43);
  *(char *)((int)this + 0x18) = (char)uVar4;
  local_8._0_1_ = 0;
  if (0xf < local_1c) {
    FUN_00402430(local_30[0],local_1c + 1,1);
  }
  local_1c = 0xf;
  local_20 = 0;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  FUN_0043ace0(local_30,(uint *)"centerGroups",0xc);
  local_8 = CONCAT31(local_8._1_3_,4);
  cVar1 = FUN_00441100(param_1,local_30);
  *(char *)((int)this + 0x19) = cVar1;
  if (0xf < local_1c) {
    FUN_00402430(local_30[0],local_1c + 1,1);
  }
  ExceptionList = local_10;
  return this;
}



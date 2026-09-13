// FUN_00420e70 @ 00420e70 size=927 callers=1

void * __thiscall FUN_00420e70(void *this,void *param_1)

{
  void *this_00;
  char cVar1;
  char *pcVar2;
  uint uVar3;
  void *local_44 [4];
  undefined4 local_34;
  uint local_30;
  void *local_2c [4];
  undefined4 local_1c;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  this_00 = param_1;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047bba0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pcVar2 = (char *)FUN_00440dd0(param_1,(uint *)&DAT_0048cf60);
  FUN_00455dc0(pcVar2,(char *)((int)&param_1 + 3));
  *(char *)((int)this + 7) = param_1._3_1_;
  if (param_1._3_1_ == '\x04') {
    pcVar2 = (char *)FUN_00440dd0(this_00,(uint *)"seqId");
    FUN_00453970(pcVar2,(ushort *)&param_1);
    *(undefined2 *)this = param_1._0_2_;
    pcVar2 = (char *)FUN_00440dd0(this_00,(uint *)"stepId");
    FUN_004536b0(pcVar2,(uint *)&param_1);
    *(undefined1 *)((int)this + 4) = param_1._0_1_;
    local_18 = 0xf;
    local_1c = 0;
    local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
    FUN_0043ace0(local_2c,(uint *)"maxTime",7);
    local_8 = 0;
    uVar3 = FUN_004409d0(this_00,local_2c,0);
    *(short *)((int)this + 2) = (short)uVar3;
    local_8 = 0xffffffff;
    if (0xf < local_18) {
      FUN_00402430(local_2c[0],local_18 + 1,1);
    }
  }
  else if (param_1._3_1_ == '\x01') {
    pcVar2 = (char *)FUN_00440dd0(this_00,(uint *)&DAT_0048d720);
    FUN_00453970(pcVar2,(ushort *)&param_1);
    *(undefined2 *)this = param_1._0_2_;
    FUN_004355e0(local_2c,(uint *)&DAT_0048d728);
    local_8 = 1;
    uVar3 = FUN_004409d0(this_00,local_2c,0);
    *(short *)((int)this + 2) = (short)uVar3;
    local_8 = 0xffffffff;
    if (0xf < local_18) {
      FUN_00402430(local_2c[0],local_18 + 1,1);
    }
    FUN_004355e0(local_2c,(uint *)"toggleState");
    local_8 = 2;
    cVar1 = FUN_00441100(this_00,local_2c);
    *(char *)((int)this + 4) = cVar1;
    local_8 = 0xffffffff;
    if (0xf < local_18) {
      FUN_00402430(local_2c[0],local_18 + 1,1);
    }
  }
  else if (param_1._3_1_ == '\x03') {
    pcVar2 = (char *)FUN_00440dd0(this_00,(uint *)"testIdx");
    FUN_00453970(pcVar2,(ushort *)&param_1);
    *(undefined2 *)this = param_1._0_2_;
  }
  else if ((param_1._3_1_ == '\a') || (param_1._3_1_ == '\b')) {
    FUN_004355e0(local_2c,(uint *)"actIdx");
    local_8 = 3;
    uVar3 = FUN_004409d0(this_00,local_2c,0xffff);
    *(short *)this = (short)uVar3;
    local_8 = 0xffffffff;
    FUN_004061c0(local_2c);
    pcVar2 = (char *)FUN_00440dd0(this_00,(uint *)"value");
    FUN_004536b0(pcVar2,(uint *)&param_1);
    *(undefined1 *)((int)this + 2) = param_1._0_1_;
  }
  else if (param_1._3_1_ == '\r') {
    FUN_004355e0(local_2c,(uint *)"menuNum");
    local_8 = 4;
    uVar3 = FUN_004409d0(this_00,local_2c,0);
    *(short *)this = (short)uVar3;
    local_8 = 0xffffffff;
    FUN_004061c0(local_2c);
  }
  else if (param_1._3_1_ == '\x05') {
    pcVar2 = (char *)FUN_00440dd0(this_00,(uint *)"swtchId");
    FUN_00453970(pcVar2,(ushort *)&param_1);
    *(undefined2 *)this = param_1._0_2_;
    pcVar2 = (char *)FUN_00440dd0(this_00,(uint *)"state");
    FUN_00453610(pcVar2,(char *)((int)&param_1 + 3));
    *(char *)((int)this + 2) = param_1._3_1_;
    pcVar2 = (char *)FUN_00440dd0(this_00,(uint *)&DAT_0048d764);
    FUN_004536b0(pcVar2,(uint *)&param_1);
    *(undefined1 *)((int)this + 3) = param_1._0_1_;
  }
  else {
    FUN_004355e0(local_2c,(uint *)"value");
    local_8 = 5;
    uVar3 = FUN_004409d0(this_00,local_2c,0);
    *(uint *)this = uVar3;
    local_8 = 0xffffffff;
    FUN_004061c0(local_2c);
  }
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  FUN_0043ace0(local_2c,(uint *)"negate",6);
  local_8 = 6;
  cVar1 = FUN_00441100(this_00,local_2c);
  *(char *)((int)this + 6) = cVar1;
  local_8 = 0xffffffff;
  if (0xf < local_18) {
    FUN_00402430(local_2c[0],local_18 + 1,1);
  }
  local_30 = 0xf;
  local_34 = 0;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  FUN_0043ace0(local_44,(uint *)&DAT_0048d774,4);
  local_8 = 7;
  uVar3 = FUN_004409d0(this_00,local_44,0);
  *(char *)((int)this + 5) = (char)uVar3;
  if (0xf < local_30) {
    FUN_00402430(local_44[0],local_30 + 1,1);
  }
  ExceptionList = local_10;
  return this;
}



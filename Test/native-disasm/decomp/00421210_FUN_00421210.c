// FUN_00421210 @ 00421210 size=1599 callers=1

void * __thiscall FUN_00421210(void *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  void *pvVar3;
  uint uVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  char *pcVar8;
  int *piVar9;
  char *pcVar10;
  void *this_00;
  void *in_stack_ffffff60;
  void *local_78 [5];
  uint local_64;
  void *local_60 [4];
  undefined4 local_50;
  uint local_4c;
  int local_48 [4];
  char *local_38;
  int local_34;
  int local_30;
  int local_2c;
  void *local_28;
  int *local_24;
  int *local_20;
  int *local_1c;
  undefined1 local_18 [8];
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  pcVar10 = param_1;
  puStack_c = &LAB_0047bc25;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  local_8 = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined8 *)((int)this + 0x14) = 0;
  *(undefined2 *)((int)this + 0x1c) = 0;
  local_28 = this;
  pcVar2 = (char *)FUN_00440dd0(param_1,(uint *)&DAT_0048cf60);
  FUN_00455dc0(pcVar2,(char *)((int)&param_1 + 3));
  *(char *)((int)this + 0x1e) = param_1._3_1_;
  *(undefined2 *)((int)this + 0x1f) = 0;
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  FUN_0043ace0(local_60,(uint *)"block",5);
  local_8._0_1_ = 1;
  cVar1 = FUN_00441100(pcVar10,local_60);
  *(char *)((int)this + 0x21) = cVar1;
  local_8 = (uint)local_8._1_3_ << 8;
  if (0xf < local_4c) {
    FUN_00402430(local_60[0],local_4c + 1,1);
  }
  *(undefined1 *)((int)this + 0x22) = 1;
  if (*(char *)((int)this + 0x1e) == '\a') {
    pcVar2 = "seqId";
    pvVar3 = (void *)FUN_00440dd0(pcVar10,(uint *)"param");
    pcVar2 = (char *)FUN_00440dd0(pvVar3,(uint *)pcVar2);
    FUN_00453970(pcVar2,(ushort *)&param_1);
    pcVar2 = "stepId";
    *(undefined2 *)((int)this + 0xc) = param_1._0_2_;
    pvVar3 = (void *)FUN_00440dd0(pcVar10,(uint *)"param");
    pcVar2 = (char *)FUN_00440dd0(pvVar3,(uint *)pcVar2);
    FUN_004536b0(pcVar2,(uint *)&param_1);
    *(undefined1 *)((int)this + 0xe) = param_1._0_1_;
  }
  else {
    local_4c = 0xf;
    local_50 = 0;
    local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
    FUN_0043ace0(local_60,(uint *)"evtId",5);
    if (*pcVar10 == '\x01') {
      FUN_004437f0(*(void **)(pcVar10 + 8),(int *)&local_24,(byte *)local_60);
      iVar5 = FUN_00447a70(local_24,local_20);
    }
    else {
      iVar5 = 0;
    }
    if (0xf < local_4c) {
      FUN_00402430(local_60[0],local_4c + 1,1);
    }
    if (iVar5 == 0) {
      FUN_004355e0(&stack0xffffff60,(uint *)"actIdx");
      iVar5 = FUN_004341b0(pcVar10,in_stack_ffffff60);
      if (iVar5 == 0) {
        if (*(char *)((int)this + 0x1e) == '\x04') {
          FUN_004355e0(local_60,(uint *)"timeout");
          local_8._0_1_ = 3;
          uVar4 = FUN_004409d0(pcVar10,local_60,0);
          *(short *)((int)this + 0xc) = (short)uVar4;
          local_8 = (uint)local_8._1_3_ << 8;
          FUN_004061c0(local_60);
          pcVar2 = (char *)FUN_00440dd0(pcVar10,(uint *)"state");
          FUN_00453610(pcVar2,(char *)((int)&param_1 + 3));
          *(char *)((int)this + 0xe) = param_1._3_1_;
        }
        else {
          FUN_004355e0(local_60,(uint *)"param");
          local_8._0_1_ = 4;
          uVar4 = FUN_004409d0(pcVar10,local_60,0);
          *(uint *)((int)this + 0xc) = uVar4;
          local_8 = (uint)local_8._1_3_ << 8;
          FUN_004061c0(local_60);
        }
      }
      else {
        pcVar2 = (char *)FUN_00440dd0(pcVar10,(uint *)"actIdx");
        FUN_00453970(pcVar2,(ushort *)&param_1);
        *(undefined2 *)((int)this + 0xc) = param_1._0_2_;
      }
    }
    else {
      FUN_004355e0(local_60,(uint *)"delay");
      local_8._0_1_ = 2;
      uVar4 = FUN_004409d0(pcVar10,local_60,0);
      *(short *)((int)this + 0xc) = (short)uVar4;
      local_8 = (uint)local_8._1_3_ << 8;
      if (0xf < local_4c) {
        FUN_00402430(local_60[0],local_4c + 1,1);
      }
      pcVar2 = (char *)FUN_00440dd0(pcVar10,(uint *)"evtId");
      FUN_00453970(pcVar2,(ushort *)&param_1);
      *(undefined2 *)((int)this + 0xe) = param_1._0_2_;
    }
  }
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  FUN_0043ace0(local_60,(uint *)"autoRep",7);
  if (*pcVar10 == '\x01') {
    FUN_004437f0(*(void **)(pcVar10 + 8),(int *)&local_24,(byte *)local_60);
    iVar5 = FUN_00447a70(local_24,local_20);
  }
  else {
    iVar5 = 0;
  }
  if (0xf < local_4c) {
    FUN_00402430(local_60[0],local_4c + 1,1);
  }
  if (iVar5 != 0) {
    pcVar2 = (char *)FUN_00440dd0(pcVar10,(uint *)"autoRep");
    FUN_00453610(pcVar2,(char *)((int)&param_1 + 3));
    *(char *)((int)this + 0x22) = param_1._3_1_;
  }
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  FUN_0043ace0(local_60,(uint *)&DAT_0048d7ac,3);
  local_8._0_1_ = 6;
  local_38 = (char *)((uint)local_38 & 0xffffff00);
  FUN_004381d0(&local_30,'\0');
  local_8._0_1_ = 7;
  puVar6 = (undefined1 *)FUN_004343d0(pcVar10,(byte *)local_60);
  param_1 = (char *)CONCAT13(*puVar6,param_1._0_3_);
  FUN_00434820((char *)&local_38);
  local_8._0_1_ = 0;
  if (0xf < local_4c) {
    FUN_00402430(local_60[0],local_4c + 1,1);
  }
  if (param_1._3_1_ == '\x01') {
    pvVar3 = (void *)FUN_00440dd0(pcVar10,(uint *)&DAT_0048d7ac);
    FUN_00434120(pvVar3,&local_38);
    while( true ) {
      local_4c = 0xf;
      local_50 = 0;
      local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
      FUN_0043ace0(local_60,(uint *)&DAT_0048d7ac,3);
      local_8._0_1_ = 8;
      pvVar3 = (void *)FUN_00439c60(pcVar10,(byte *)local_60);
      local_8._0_1_ = 0;
      if (0xf < local_4c) {
        FUN_00402430(local_60[0],local_4c + 1,1);
      }
      local_4c = 0xf;
      local_50 = 0;
      local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
      FUN_004340a0(pvVar3,local_48);
      uVar7 = FUN_004383a0(&local_38,local_48);
      if ((char)uVar7 != '\0') break;
      pcVar2 = FUN_00433b30(&local_38,(undefined1 *)local_78);
      local_8._0_1_ = 9;
      pcVar8 = FUN_00433bc0(&local_38);
      FUN_004536b0(pcVar8,(uint *)local_18);
      if (0xf < *(uint *)(pcVar2 + 0x14)) {
        pcVar2 = *(char **)pcVar2;
      }
      piVar9 = __errno();
      *piVar9 = 0;
      local_1c = (int *)_strtol(pcVar2,&param_1,10);
      if (pcVar2 == param_1) {
                    /* WARNING: Subroutine does not return */
        FUN_00458ea4("invalid stoi argument");
      }
      piVar9 = __errno();
      if (*piVar9 == 0x22) {
                    /* WARNING: Subroutine does not return */
        FUN_00458ee4("stoi argument out of range");
      }
      local_8._0_1_ = 0;
      *(undefined1 *)((int)this + 0x14 + (int)local_1c) = local_18[0];
      if (0xf < local_64) {
        FUN_00402430(local_78[0],local_64 + 1,1);
      }
      if (*local_38 == '\x01') {
        local_20 = (int *)((uint)local_20 & 0xffffff00);
        FUN_00447660(&local_34);
      }
      else if (*local_38 == '\x02') {
        local_30 = local_30 + 0x10;
      }
      else {
        local_2c = local_2c + 1;
      }
    }
  }
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  FUN_0043ace0(local_60,(uint *)"preconds",8);
  local_8._0_1_ = 0xb;
  local_38 = (char *)((uint)local_38 & 0xffffff00);
  FUN_004381d0(&local_30,'\0');
  local_8._0_1_ = 0xc;
  puVar6 = (undefined1 *)FUN_004343d0(pcVar10,(byte *)local_60);
  param_1 = (char *)CONCAT13(*puVar6,param_1._0_3_);
  FUN_00434820((char *)&local_38);
  local_8 = (uint)local_8._1_3_ << 8;
  if (0xf < local_4c) {
    FUN_00402430(local_60[0],local_4c + 1,1);
  }
  if (param_1._3_1_ == '\x02') {
    pvVar3 = (void *)FUN_00440dd0(pcVar10,(uint *)"preconds");
    FUN_00434120(pvVar3,&local_38);
    FUN_004340a0(this_00,local_48);
    uVar7 = FUN_004383a0(&local_38,local_48);
    cVar1 = (char)uVar7;
    while (cVar1 == '\0') {
      pcVar10 = FUN_00433bc0(&local_38);
      if (*(int *)((int)this + 4) == *(int *)((int)this + 8)) {
        FUN_00443e60(this);
      }
      local_20 = *(int **)((int)this + 4);
      local_8._0_1_ = 0xd;
      local_1c = local_20;
      if (local_20 != (int *)0x0) {
        FUN_00420e70(local_20,pcVar10);
      }
      local_8 = (uint)local_8._1_3_ << 8;
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 8;
      if (*local_38 == '\x01') {
        param_1 = (char *)((uint)param_1 & 0xffffff00);
        FUN_00447660(&local_34);
      }
      else if (*local_38 == '\x02') {
        local_30 = local_30 + 0x10;
      }
      else {
        local_2c = local_2c + 1;
      }
      uVar7 = FUN_004383a0(&local_38,local_48);
      cVar1 = (char)uVar7;
    }
  }
  ExceptionList = local_10;
  return this;
}



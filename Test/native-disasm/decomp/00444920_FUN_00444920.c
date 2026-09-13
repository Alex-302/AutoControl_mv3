// FUN_00444920 @ 00444920 size=1170 callers=3

char * __thiscall FUN_00444920(void *this,char *param_1,uint param_2)

{
  undefined8 uVar1;
  byte bVar2;
  undefined1 uVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  undefined1 *this_00;
  uint uVar7;
  uint uVar8;
  undefined3 uVar9;
  char in_stack_ffffff7c;
  undefined4 in_stack_ffffff80;
  char *pcVar10;
  undefined4 uVar11;
  uint *puVar12;
  undefined4 uVar13;
  void *local_68 [5];
  uint local_54;
  char local_50 [16];
  char local_40 [16];
  char local_30 [8];
  uint local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined8 local_1c;
  undefined1 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e368;
  local_10 = ExceptionList;
  local_20 = 0;
  local_30[0] = '\b';
  ExceptionList = &local_10;
  FUN_004381d0(&local_28,'\b');
  local_8._0_1_ = 0;
  local_8._1_3_ = 0;
  switch(*(int *)((int)this + 0x30)) {
  case 1:
    uVar6 = FUN_00445a10((void *)((int)this + 0x34));
    uVar1 = local_1c;
    *(undefined4 *)((int)this + 0x30) = uVar6;
    local_1c = CONCAT71(local_1c._1_7_,1);
    local_28 = (uint)local_1c;
    local_1c._4_4_ = SUB84(uVar1,4);
    local_30[0] = '\x04';
    local_24 = local_1c._4_4_;
    break;
  case 2:
    uVar6 = FUN_00445a10((void *)((int)this + 0x34));
    *(undefined4 *)((int)this + 0x30) = uVar6;
    local_24 = (undefined4)((ulonglong)local_1c >> 0x20);
    local_1c._0_4_ = (uint)local_1c & 0xffffff00;
    local_28 = (uint)local_1c;
    local_30[0] = '\x04';
    break;
  case 3:
    uVar6 = FUN_00445a10((void *)((int)this + 0x34));
    *(undefined4 *)((int)this + 0x30) = uVar6;
    local_30[0] = '\0';
    break;
  case 4:
    uVar11 = 0x444c81;
    FUN_00445600((void *)((int)this + 0x34),local_68);
    local_8._0_1_ = 6;
    uVar13 = 0x444c8d;
    uVar6 = FUN_00445a10((void *)((int)this + 0x34));
    *(undefined4 *)((int)this + 0x30) = uVar6;
    FUN_00440c80(&stack0xffffff7c,local_68);
    FUN_004348c0(local_30,in_stack_ffffff7c,in_stack_ffffff80,uVar11,uVar13);
    local_8._0_1_ = 0;
    FUN_004061c0(local_68);
    break;
  case 5:
  case 6:
  case 7:
    FUN_004454f0((void *)((int)this + 0x34),local_30,*(int *)((int)this + 0x30));
    uVar6 = FUN_00445a10((void *)((int)this + 0x34));
    *(undefined4 *)((int)this + 0x30) = uVar6;
    break;
  case 8:
    cVar4 = (char)param_2;
    if ((char)param_2 != '\0') {
      if (*(int *)((int)this + 0x2c) != 0) {
        iVar5 = *(int *)this;
        *(int *)this = iVar5 + 1;
        cVar4 = FUN_004452f0((void *)((int)this + 8),iVar5,2,local_30);
        param_2 = CONCAT31(param_2._1_3_,cVar4);
        if (cVar4 == '\0') goto LAB_00444baf;
      }
      local_30[0] = '\x02';
      FUN_004381d0(&local_1c,'\x02');
      local_28 = (uint)local_1c;
      local_24 = local_1c._4_4_;
    }
LAB_00444baf:
    iVar5 = FUN_00445a10((void *)((int)this + 0x34));
    *(int *)((int)this + 0x30) = iVar5;
    if (iVar5 == 10) {
      uVar6 = FUN_00445a10((void *)((int)this + 0x34));
      *(undefined4 *)((int)this + 0x30) = uVar6;
    }
    else {
      if (iVar5 == 0xd) {
        FUN_00445320((int)this);
      }
      if (*(int *)((int)this + 0x30) != 0xd) goto LAB_00444c01;
      do {
        uVar6 = FUN_00445a10((void *)((int)this + 0x34));
        *(undefined4 *)((int)this + 0x30) = uVar6;
LAB_00444c01:
        FUN_00444920(this,local_40,param_2);
        local_8._0_1_ = 5;
        if ((cVar4 != '\0') && (local_40[0] != '\b')) {
          FUN_00433e10(local_30,local_40);
        }
        local_8._0_1_ = 0;
        FUN_00434820(local_40);
      } while (*(int *)((int)this + 0x30) == 0xd);
      FUN_004446b0(this,10);
      uVar6 = FUN_00445a10((void *)((int)this + 0x34));
      *(undefined4 *)((int)this + 0x30) = uVar6;
      if (cVar4 == '\0') goto LAB_00444a0d;
    }
    if (*(int *)((int)this + 0x2c) == 0) goto LAB_00444a0d;
    uVar6 = 3;
    goto LAB_004449e3;
  case 9:
    uVar8 = (param_2 & 0xff) << 8;
    if ((char)param_2 != '\0') {
      if (*(int *)((int)this + 0x2c) != 0) {
        iVar5 = *(int *)this;
        *(int *)this = iVar5 + 1;
        in_stack_ffffff7c = -0x6b;
        bVar2 = FUN_004452f0((void *)((int)this + 8),iVar5,0,local_30);
        uVar8 = (uint)bVar2 << 8;
        param_2 = CONCAT31(param_2._1_3_,bVar2);
        if (bVar2 == 0) goto LAB_004449b8;
      }
      local_30[0] = '\x01';
      FUN_004381d0(&local_1c,'\x01');
      local_28 = (uint)local_1c;
      local_24 = local_1c._4_4_;
    }
LAB_004449b8:
    iVar5 = FUN_00445a10((void *)((int)this + 0x34));
    *(int *)((int)this + 0x30) = iVar5;
    if (iVar5 != 0xb) {
      if (iVar5 == 0xd) {
        FUN_00445320((int)this);
      }
      uVar7 = uVar8;
      if (*(int *)((int)this + 0x30) != 0xd) goto LAB_00444a54;
      do {
        uVar6 = FUN_00445a10((void *)((int)this + 0x34));
        *(undefined4 *)((int)this + 0x30) = uVar6;
        uVar7 = uVar8;
LAB_00444a54:
        FUN_004446b0(this,4);
        FUN_00445600((void *)((int)this + 0x34),local_68);
        uVar8 = uVar7 & 0xffffff00;
        local_8._0_1_ = 1;
        if ((char)(uVar7 >> 8) != '\0') {
          uVar9 = (undefined3)(uVar7 >> 8);
          if (*(int *)((int)this + 0x2c) == 0) {
            uVar8 = CONCAT31(uVar9,1);
          }
          else {
            FUN_00440c80(local_50,local_68);
            local_8._0_1_ = 2;
            uVar3 = (undefined1)local_8;
            local_8._0_1_ = 2;
            local_14 = 4;
            local_1c = CONCAT44(*(undefined4 *)this,(uint)local_1c);
            if (*(int **)((int)this + 0x2c) == (int *)0x0) goto LAB_00444d33;
            in_stack_ffffff7c = -0x50;
            uVar3 = (**(code **)(**(int **)((int)this + 0x2c) + 8))();
            local_8._0_1_ = 1;
            uVar8 = CONCAT31(uVar9,uVar3);
            FUN_00434820(local_50);
          }
        }
        uVar6 = FUN_00445a10((void *)((int)this + 0x34));
        *(undefined4 *)((int)this + 0x30) = uVar6;
        FUN_004446b0(this,0xc);
        uVar6 = FUN_00445a10((void *)((int)this + 0x34));
        *(undefined4 *)((int)this + 0x30) = uVar6;
        pcVar10 = local_40;
        uVar6 = 0x444aef;
        uVar7 = param_2;
        FUN_00444920(this,pcVar10,param_2);
        if ((((char)(uVar8 >> 8) != '\0') && ((char)uVar8 != '\0')) && (local_40[0] != '\b')) {
          local_1c = CONCAT44(&stack0xffffff7c,(uint)local_1c);
          FUN_00434900(&stack0xffffff7c,local_40);
          local_8._0_1_ = 4;
          this_00 = FUN_00434440(local_30,(byte *)local_68);
          local_8._0_1_ = 3;
          FUN_004348c0(this_00,in_stack_ffffff7c,uVar6,pcVar10,uVar7);
        }
        FUN_00434820(local_40);
        local_8._0_1_ = 0;
        if (0xf < local_54) {
          in_stack_ffffff7c = 'N';
          FUN_00402430(local_68[0],local_54 + 1,1);
        }
      } while (*(int *)((int)this + 0x30) == 0xd);
      FUN_004446b0(this,0xb);
    }
    uVar6 = FUN_00445a10((void *)((int)this + 0x34));
    *(undefined4 *)((int)this + 0x30) = uVar6;
    if (((char)(uVar8 >> 8) == '\0') || (*(int *)((int)this + 0x2c) == 0)) goto LAB_00444a0d;
    uVar6 = 1;
LAB_004449e3:
    pcVar10 = local_30;
    *(int *)this = *(int *)this + -1;
    uVar11 = *(undefined4 *)this;
    cVar4 = FUN_004452f0((void *)((int)this + 8),uVar11,uVar6,pcVar10);
    if (cVar4 == '\0') {
      FUN_004381d0(&stack0xffffff84,'\b');
      FUN_004348c0(local_30,'\b',uVar11,uVar6,pcVar10);
    }
LAB_00444a0d:
    FUN_00434900(param_1,local_30);
    FUN_00434820(local_30);
    ExceptionList = local_10;
    return param_1;
  default:
    FUN_00445320((int)this);
  }
  if (((char)param_2 != '\0') && (*(int *)((int)this + 0x2c) != 0)) {
    param_2 = CONCAT31(param_2._1_3_,5);
    local_1c = CONCAT44(*(undefined4 *)this,(uint)local_1c);
    uVar3 = (undefined1)local_8;
    if (*(int **)((int)this + 0x2c) == (int *)0x0) {
LAB_00444d33:
      local_8._0_1_ = uVar3;
                    /* WARNING: Subroutine does not return */
      FUN_00458e87();
    }
    pcVar10 = local_30;
    puVar12 = &param_2;
    iVar5 = (int)&local_1c + 4;
    cVar4 = (**(code **)(**(int **)((int)this + 0x2c) + 8))();
    if (cVar4 == '\0') {
      FUN_004381d0(&stack0xffffff84,'\b');
      FUN_004348c0(local_30,'\b',iVar5,puVar12,pcVar10);
    }
  }
  uVar6 = local_24;
  uVar8 = local_28;
  local_1c = 0;
  *param_1 = local_30[0];
  local_28 = 0;
  *(uint *)(param_1 + 8) = uVar8;
  local_24 = 0;
  *(undefined4 *)(param_1 + 0xc) = uVar6;
  local_30[0] = '\0';
  FUN_00434820(local_30);
  ExceptionList = local_10;
  return param_1;
}



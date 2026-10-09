// FUN_0042b8d0 @ 0042b8d0 size=821 callers=1

undefined1 * __cdecl FUN_0042b8d0(undefined1 *param_1,void *param_2)

{
  POINT Point;
  char cVar1;
  short sVar2;
  HWND pHVar3;
  BOOL BVar4;
  int *piVar5;
  undefined4 uVar6;
  uint uVar7;
  char cVar8;
  int local_bc [5];
  undefined4 local_a8;
  void *local_a4 [4];
  undefined4 local_94;
  uint local_90;
  void *local_8c [4];
  undefined4 local_7c;
  uint local_78;
  void *local_74 [4];
  undefined4 local_64;
  uint local_60;
  void *local_5c [4];
  undefined4 local_4c;
  uint local_48;
  void *local_44 [4];
  undefined4 local_34;
  uint local_30;
  undefined1 local_2c [12];
  HWND pHStack_20;
  POINT local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047cc4e;
  local_10 = ExceptionList;
  local_a8 = 0;
  local_30 = 0xf;
  local_34 = 0;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_44,(uint *)&DAT_0048d814,3);
  local_8 = 0;
  pHVar3 = (HWND)FUN_00442390(param_2,local_44);
  local_8 = 0xffffffff;
  if (0xf < local_30) {
    FUN_00402430(local_44[0],local_30 + 1,1);
  }
  local_30 = 0xf;
  local_34 = 0;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  GetCursorPos((LPPOINT)(local_2c + 8));
  local_1c.x = local_2c._8_4_;
  local_1c.y = (LONG)pHStack_20;
  if (pHVar3 == (HWND)0x0) {
LAB_0042ba15:
    Point.y = local_1c.y;
    Point.x = local_1c.x;
    pHVar3 = WindowFromPoint(Point);
    local_90 = 0xf;
    local_94 = 0;
    local_a4[0] = (void *)((uint)local_a4[0] & 0xffffff00);
    pHStack_20 = pHVar3;
    FUN_0043ace0(local_a4,(uint *)"kpModKs",7);
    local_8 = 1;
    local_78 = 0xf;
    local_7c = 0;
    local_8c[0] = (void *)((uint)local_8c[0] & 0xffffff00);
    FUN_0043ace0(local_8c,(uint *)"method",6);
    local_8._0_1_ = 2;
    local_60 = 0xf;
    local_64 = 0;
    local_74[0] = (void *)((uint)local_74[0] & 0xffffff00);
    FUN_0043ace0(local_74,(uint *)"steps",5);
    local_8._0_1_ = 3;
    local_48 = 0xf;
    local_4c = 0;
    local_5c[0] = (void *)((uint)local_5c[0] & 0xffffff00);
    FUN_0043ace0(local_5c,(uint *)&DAT_0048da64,4);
    local_8 = CONCAT31(local_8._1_3_,4);
    cVar1 = FUN_00441100(param_2,local_a4);
    uVar7 = FUN_004409d0(param_2,local_8c,0);
    cVar8 = (char)uVar7;
    uVar7 = FUN_004409d0(param_2,local_74,1);
    sVar2 = (short)uVar7;
    uVar7 = FUN_004409d0(param_2,local_5c,0x56);
    FUN_0040cbf0(pHVar3,&local_1c.x,(char)uVar7,sVar2,cVar8,cVar1);
    if (0xf < local_48) {
      FUN_00402430(local_5c[0],local_48 + 1,1);
    }
    local_48 = 0xf;
    local_4c = 0;
    local_5c[0] = (void *)((uint)local_5c[0] & 0xffffff00);
    if (0xf < local_60) {
      FUN_00402430(local_74[0],local_60 + 1,1);
    }
    local_60 = 0xf;
    local_64 = 0;
    local_74[0] = (void *)((uint)local_74[0] & 0xffffff00);
    if (0xf < local_78) {
      FUN_00402430(local_8c[0],local_78 + 1,1);
    }
    local_78 = 0xf;
    local_7c = 0;
    local_8c[0] = (void *)((uint)local_8c[0] & 0xffffff00);
    if (0xf < local_90) {
      FUN_00402430(local_a4[0],local_90 + 1,1);
    }
    FUN_00442050(param_1,(int *)&pHStack_20);
    ExceptionList = local_10;
    return param_1;
  }
  BVar4 = IsWindowVisible(pHVar3);
  if ((BVar4 != 0) && (BVar4 = IsIconic(pHVar3), BVar4 == 0)) {
    piVar5 = (int *)FUN_0040e9b0(pHVar3,'\x01',local_bc);
    local_2c._0_4_ = *piVar5;
    local_2c._4_4_ = piVar5[1];
    local_2c._8_4_ = piVar5[2];
    pHStack_20 = (HWND)piVar5[3];
    local_1c.x = (int)(local_2c._0_4_ + local_2c._8_4_) / 2;
    local_1c.y = ((int)&pHStack_20->unused + local_2c._4_4_) / 2;
    uVar6 = FUN_00406550(pHVar3,(RECT *)local_2c,&local_1c);
    if ((char)uVar6 != '\0') goto LAB_0042ba15;
  }
  local_1c.x = local_1c.x & 0xffffff00;
  *(undefined8 *)(param_1 + 8) = 0;
  *(LONG *)(param_1 + 8) = local_1c.x;
  *(LONG *)(param_1 + 0xc) = local_1c.y;
  *param_1 = 4;
  ExceptionList = local_10;
  return param_1;
}



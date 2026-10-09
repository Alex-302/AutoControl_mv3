// FUN_004123b0 @ 004123b0 size=1272 callers=3

void * __thiscall FUN_004123b0(void *this,void *param_1)

{
  uint *puVar1;
  undefined8 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  void *pvVar8;
  uint *puVar9;
  void *pvVar10;
  char cVar11;
  int iVar12;
  uint local_f8 [8];
  char local_d8 [8];
  undefined1 local_d0 [8];
  char local_c8 [8];
  undefined1 local_c0 [8];
  void *local_b8 [4];
  undefined4 local_a8;
  uint local_a4;
  undefined4 local_a0 [6];
  undefined2 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined2 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined2 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined2 local_34;
  void *local_30;
  void *local_2c [4];
  undefined4 local_1c;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ab15;
  local_10 = ExceptionList;
  local_a0[3] = 0;
  local_88 = 2;
  local_6c = 2;
  local_50 = 2;
  local_34 = 2;
  cVar11 = '\0';
  local_a0[0] = DAT_004a29a8;
  local_a0[1] = 0;
  local_a0[2] = 0;
  local_a0[4] = 0x30005;
  local_a0[5] = 0x20005;
  local_84 = DAT_004a29b0;
  local_80 = DAT_004a29b4;
  local_7c = 0;
  local_78 = 0;
  local_74 = 0x30005;
  local_70 = 0x20005;
  local_68 = DAT_004a29a8;
  local_64 = 0;
  local_60 = 0xff4281f4;
  local_5c = 0x20000;
  local_58 = 0x10003;
  local_54 = 0x20005;
  local_4c = DAT_004a29b0;
  local_48 = DAT_004a29b4;
  local_44 = 0xff4281f4;
  local_40 = 0x20000;
  local_3c = 0x10003;
  local_38 = 0x20005;
  ExceptionList = &local_10;
  local_30 = this;
  do {
    local_18 = 0xf;
    local_1c = 0;
    local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
    FUN_0043ace0(local_2c,(uint *)"itemStates",10);
    local_8 = 1;
    local_d8[0] = '\0';
    FUN_004381d0(local_d0,'\0');
    local_8._0_1_ = 3;
    local_c8[0] = '\0';
    FUN_004381d0(local_c0,'\0');
    uVar7 = (uint)cVar11;
    local_8 = CONCAT31(local_8._1_3_,4);
    iVar12 = uVar7 * 0x1c;
    iVar6 = uVar7 * 7;
    pvVar8 = (void *)FUN_004343d0(param_1,(byte *)local_2c);
    pvVar8 = (void *)FUN_00434360(pvVar8,uVar7);
    puVar9 = FUN_00411440(pvVar8,local_a0 + iVar6,local_f8);
    pvVar8 = local_30;
    uVar3 = puVar9[1];
    uVar4 = puVar9[2];
    uVar5 = puVar9[3];
    uVar2 = *(undefined8 *)(puVar9 + 4);
    uVar7 = puVar9[6];
    puVar1 = (uint *)(iVar12 + (int)local_30);
    *puVar1 = *puVar9;
    puVar1[1] = uVar3;
    puVar1[2] = uVar4;
    puVar1[3] = uVar5;
    *(undefined8 *)(iVar12 + 0x10 + (int)local_30) = uVar2;
    *(uint *)(iVar12 + 0x18 + (int)local_30) = uVar7;
    FUN_00434820(local_c8);
    FUN_00434820(local_d8);
    local_8 = 0xffffffff;
    if (0xf < local_18) {
      pvVar10 = local_2c[0];
      if ((0xfff < local_18 + 1) &&
         ((((((uint)local_2c[0] & 0x1f) != 0 ||
            (pvVar10 = *(void **)((int)local_2c[0] + -4), local_2c[0] <= pvVar10)) ||
           ((uint)((int)local_2c[0] - (int)pvVar10) < 4)) ||
          (0x23 < (uint)((int)local_2c[0] - (int)pvVar10))))) goto LAB_00412624;
      FID_conflict__free(pvVar10);
    }
    cVar11 = cVar11 + '\x01';
  } while (cVar11 < '\x04');
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  FUN_0043ace0(local_2c,(uint *)"bgColor",7);
  local_8 = 5;
  uVar7 = FUN_00441990(param_1,local_2c,DAT_004a29ac);
  *(uint *)((int)pvVar8 + 0x70) = uVar7;
  local_8 = 0xffffffff;
  if (0xf < local_18) {
    pvVar10 = local_2c[0];
    if (0xfff < local_18 + 1) {
      if (((uint)local_2c[0] & 0x1f) != 0) {
LAB_00412624:
        local_8 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar10 = *(void **)((int)local_2c[0] + -4);
      if (local_2c[0] <= pvVar10) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_2c[0] - (int)pvVar10) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_2c[0] - (int)pvVar10)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar10);
  }
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  FUN_0043ace0(local_2c,(uint *)"sepLiteColr",0xb);
  local_8 = 6;
  uVar7 = FUN_00441990(param_1,local_2c,0xd9ffffff);
  *(uint *)((int)pvVar8 + 0x74) = uVar7;
  local_8 = 0xffffffff;
  if (0xf < local_18) {
    pvVar10 = local_2c[0];
    if (0xfff < local_18 + 1) {
      if (((uint)local_2c[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar10 = *(void **)((int)local_2c[0] + -4);
      if (local_2c[0] <= pvVar10) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_2c[0] - (int)pvVar10) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_2c[0] - (int)pvVar10)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar10);
  }
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  FUN_0043ace0(local_2c,(uint *)"sepDarkColr",0xb);
  local_8 = 7;
  uVar7 = FUN_004409d0(param_1,local_2c,0x61000000);
  *(uint *)((int)pvVar8 + 0x78) = uVar7;
  local_8 = 0xffffffff;
  if (0xf < local_18) {
    pvVar10 = local_2c[0];
    if (0xfff < local_18 + 1) {
      if (((uint)local_2c[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar10 = *(void **)((int)local_2c[0] + -4);
      if (local_2c[0] <= pvVar10) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_2c[0] - (int)pvVar10) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_2c[0] - (int)pvVar10)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar10);
  }
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  FUN_0043ace0(local_2c,(uint *)"padding",7);
  local_8 = 8;
  uVar7 = FUN_004409d0(param_1,local_2c,2);
  *(short *)((int)pvVar8 + 0x7e) = (short)uVar7;
  local_8 = 0xffffffff;
  if (0xf < local_18) {
    pvVar10 = local_2c[0];
    if (0xfff < local_18 + 1) {
      if (((uint)local_2c[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar10 = *(void **)((int)local_2c[0] + -4);
      if (local_2c[0] <= pvVar10) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_2c[0] - (int)pvVar10) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_2c[0] - (int)pvVar10)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar10);
  }
  local_a4 = 0xf;
  local_a8 = 0;
  local_b8[0] = (void *)((uint)local_b8[0] & 0xffffff00);
  FUN_0043ace0(local_b8,(uint *)"itemMaxWidth",0xc);
  local_8 = 9;
  uVar7 = FUN_004409d0(param_1,local_b8,300);
  *(short *)((int)pvVar8 + 0x7c) = (short)uVar7;
  if (0xf < local_a4) {
    pvVar10 = local_b8[0];
    if (0xfff < local_a4 + 1) {
      if (((uint)local_b8[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar10 = *(void **)((int)local_b8[0] + -4);
      if (local_b8[0] <= pvVar10) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_b8[0] - (int)pvVar10) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_b8[0] - (int)pvVar10)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar10);
  }
  ExceptionList = local_10;
  return pvVar8;
}



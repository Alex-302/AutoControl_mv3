// FUN_0044e860 @ 0044e860 size=1020 callers=11

undefined4 __fastcall FUN_0044e860(int *param_1,uint *param_2,uint *param_3)

{
  char *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  uint *puVar5;
  undefined4 uVar6;
  byte *pbVar7;
  uint uVar8;
  undefined1 uVar9;
  uint *extraout_EDX;
  uint *extraout_EDX_00;
  uint *extraout_EDX_01;
  uint *extraout_EDX_02;
  uint *extraout_EDX_03;
  uint *extraout_EDX_04;
  uint *extraout_EDX_05;
  uint *extraout_EDX_06;
  uint *extraout_EDX_07;
  uint *puVar10;
  undefined4 *unaff_FS_OFFSET;
  bool bVar11;
  undefined8 uVar12;
  int local_30;
  int local_2c [3];
  int local_20;
  int local_1c;
  int local_18;
  uint *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_10 = *unaff_FS_OFFSET;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e718;
  *unaff_FS_OFFSET = &local_10;
  if ((0 < param_1[0x1f]) && (iVar4 = param_1[0x1f] + -1, param_1[0x1f] = iVar4, iVar4 < 1)) {
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(0xc);
  }
  if ((0 < param_1[0x1e]) && (iVar4 = param_1[0x1e] + -1, param_1[0x1e] = iVar4, iVar4 < 1)) {
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(0xb);
  }
  local_14 = (uint *)((uint)local_14 & 0xffffff00);
  puVar10 = param_3;
joined_r0x0044e8b5:
  if (puVar10 == (uint *)0x0) {
LAB_0044eab0:
    cVar2 = (char)local_14;
LAB_0044eab3:
    iVar4 = param_1[0x1f];
    if (0 < iVar4) {
      iVar4 = iVar4 + 1;
      param_1[0x1f] = iVar4;
    }
    *unaff_FS_OFFSET = local_10;
    return CONCAT31((int3)((uint)iVar4 >> 8),cVar2 == '\0');
  }
  uVar8 = puVar10[1];
  switch(uVar8) {
  case 1:
  case 8:
  case 9:
  case 0x11:
  case 0x14:
    break;
  case 2:
    if ((param_1[0x18] & 0x101U) != 1) {
      if (((param_1[0x18] & 0x100U) == 0) && (*param_1 == param_1[0x13])) break;
      local_14 = (uint *)CONCAT31((int3)((uint)*param_1 >> 8),*(char *)(*param_1 + -1) != '\n');
      goto LAB_0044ea9a;
    }
LAB_0044e923:
    cVar2 = '\x01';
    goto LAB_0044eab3;
  case 3:
    if (((*(byte *)(param_1 + 0x18) & 2) != 0) ||
       (((char *)*param_1 != (char *)param_1[0x14] && (*(char *)*param_1 != '\n'))))
    goto LAB_0044e923;
    break;
  case 4:
    uVar8 = param_1[0x18];
    if ((((uVar8 & 4) == 0) || (*param_1 != param_1[0x13])) &&
       (((uVar8 & 8) == 0 || (*param_1 != param_1[0x14])))) {
      if ((*param_1 == param_1[0x13]) && ((uVar8 & 0x100) == 0)) {
        param_3._3_1_ = false;
      }
      else {
        puVar5 = FUN_0045c740((uint *)
                              "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_",
                              *(char *)(*param_1 + -1));
        param_3._3_1_ = puVar5 != (uint *)0x0;
        param_2 = extraout_EDX;
      }
      if ((char *)*param_1 == (char *)param_1[0x14]) {
        bVar11 = false;
      }
      else {
        puVar5 = FUN_0045c740((uint *)
                              "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_",
                              *(char *)*param_1);
        bVar11 = puVar5 != (uint *)0x0;
        param_2 = extraout_EDX_00;
      }
      bVar3 = bVar11 ^ param_3._3_1_;
    }
    else {
      bVar3 = 0;
    }
    if (bVar3 == ((byte)puVar10[2] & 1)) goto LAB_0044e923;
    break;
  case 5:
    pcVar1 = (char *)*param_1;
    if (((pcVar1 == (char *)param_1[0x14]) || (*pcVar1 == '\n')) || (*pcVar1 == '\r'))
    goto LAB_0044e923;
    *param_1 = (int)(pcVar1 + 1);
    break;
  case 6:
    pbVar7 = FUN_0044efd0((byte *)*param_1,(byte *)param_1[0x14],(byte *)puVar10[7],
                          (byte *)puVar10[7] + puVar10[6],param_1[0x1c],param_1[0x17]);
    if (pbVar7 == (byte *)*param_1) goto LAB_0044e923;
    *param_1 = (int)pbVar7;
    param_2 = extraout_EDX_01;
    break;
  case 7:
    if ((*param_1 == param_1[0x14]) ||
       (uVar6 = FUN_00452560(param_1,(int)puVar10), (char)uVar6 == '\0')) goto LAB_0044e923;
    local_14 = (uint *)((uint)local_14 & 0xffffff00);
    param_2 = extraout_EDX_02;
    goto LAB_0044ea9e;
  case 10:
  case 0xb:
    local_30 = *param_1;
    local_1c = local_30;
    uVar12 = FUN_00450ec0(local_2c,param_2,param_1 + 1);
    local_20 = param_1[4];
    local_8 = 0;
    local_18 = local_20;
    uVar6 = FUN_0044e860(param_1,(uint *)((ulonglong)uVar12 >> 0x20),(uint *)puVar10[5]);
    if ((bool)(char)uVar6 == (uVar8 == 0xb)) {
      *param_1 = local_30;
      param_1[4] = local_18;
      FUN_00450dd0(param_1 + 1,local_2c);
      local_14 = (uint *)CONCAT31(local_14._1_3_,1);
    }
    else {
      *param_1 = local_1c;
    }
    local_8 = 0xffffffff;
    FUN_004483a0((int)&local_30);
    param_2 = extraout_EDX_03;
    break;
  case 0xc:
    goto switchD_0044e8cf_caseD_c;
  case 0xd:
    param_2 = (uint *)puVar10[5];
    *(int *)(param_1[5] + (int)param_2 * 8) = *param_1;
    uVar8 = param_1[4];
    if (puVar10[5] < uVar8) {
      do {
        uVar8 = uVar8 - 1;
        param_2 = (uint *)(param_1[1] + (uVar8 >> 5) * 4);
        *param_2 = *param_2 & ~(1 << (uVar8 & 0x1f));
      } while (puVar10[5] < uVar8);
    }
    break;
  case 0xe:
    uVar8 = puVar10[5];
    if ((*(char *)((int)param_1 + 0x65) != '\0') || (*(int *)(uVar8 + 0x14) != 0)) {
      puVar5 = (uint *)(param_1[1] + (*(uint *)(uVar8 + 0x14) >> 5) * 4);
      *puVar5 = *puVar5 | 1 << (*(uint *)(uVar8 + 0x14) & 0x1f);
      param_2 = *(uint **)(uVar8 + 0x14);
      *(int *)(param_1[5] + 4 + (int)param_2 * 8) = *param_1;
    }
    break;
  case 0xf:
    uVar8 = puVar10[5];
    param_2 = (uint *)(param_1[1] + (uVar8 >> 5) * 4);
    if ((*param_2 & 1 << ((byte)uVar8 & 0x1f)) != 0) {
      pbVar7 = (byte *)*param_1;
      param_2 = *(uint **)(param_1[5] + uVar8 * 8);
      puVar5 = *(uint **)(param_1[5] + 4 + uVar8 * 8);
      if ((param_2 != puVar5) &&
         (pbVar7 = FUN_0044efd0(pbVar7,(byte *)param_1[0x14],(byte *)param_2,(byte *)puVar5,
                                param_1[0x1c],param_1[0x17]), param_2 = extraout_EDX_04,
         pbVar7 == (byte *)*param_1)) goto LAB_0044e923;
      *param_1 = (int)pbVar7;
    }
    break;
  case 0x10:
    cVar2 = FUN_00452090(param_1,param_2,(uint)puVar10);
    local_14 = (uint *)((uint)local_14 & 0xff);
    param_2 = extraout_EDX_05;
    if (cVar2 == '\0') {
      local_14 = (uint *)0x1;
    }
    goto switchD_0044e8cf_caseD_c;
  case 0x12:
    bVar3 = (byte)(puVar10[2] >> 1);
    iVar4 = 0;
LAB_0044ebcc:
    bVar3 = FUN_004523a0(param_1,param_2,(int)puVar10,bVar3 & 1,iVar4);
    param_2 = local_14;
    uVar9 = SUB41(local_14,0);
    if (bVar3 == 0) {
      uVar9 = 1;
    }
    local_14 = (uint *)CONCAT31(local_14._1_3_,uVar9);
    goto LAB_0044ebe1;
  case 0x13:
    param_2 = (uint *)puVar10[5];
    if (param_2[9] == 0) {
      iVar4 = *(int *)(param_1[0x10] + param_2[8] * 8);
      bVar3 = (byte)(param_2[2] >> 1);
      puVar10 = param_2;
      goto LAB_0044ebcc;
    }
LAB_0044ebe1:
    puVar10 = (uint *)0x0;
    break;
  case 0x15:
    if ((((param_1[0x18] & 0x2020U) == 0) || (param_1[0x13] != *param_1)) &&
       (((char)param_1[0x1d] == '\0' || (*param_1 == param_1[0x14])))) {
      if (((char)param_1[0x19] != '\0') &&
         (uVar8 = FUN_004526a0((int)param_1), param_2 = extraout_EDX_06, (char)uVar8 == '\0'))
      goto LAB_0044ebe1;
      FUN_004506b0(param_1 + 8,param_1);
      *(undefined1 *)(param_1 + 0x19) = 1;
      puVar10 = (uint *)0x0;
      param_2 = extraout_EDX_07;
    }
    else {
      local_14._1_3_ = (undefined3)((uint)local_14 >> 8);
      local_14 = (uint *)CONCAT31(local_14._1_3_,1);
      puVar10 = (uint *)0x0;
    }
    break;
  default:
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(0xd);
  }
switchD_0044e8cf_caseD_1:
LAB_0044ea9a:
  if ((char)local_14 != '\0') goto LAB_0044eab0;
LAB_0044ea9e:
  if (puVar10 == (uint *)0x0) goto LAB_0044eab0;
  puVar10 = (uint *)puVar10[3];
  goto joined_r0x0044e8b5;
switchD_0044e8cf_caseD_c:
  puVar10 = (uint *)0x0;
  goto switchD_0044e8cf_caseD_1;
}



// FUN_0044e410 @ 0044e410 size=1017 callers=11

undefined4 __fastcall FUN_0044e410(int *param_1,uint *param_2,uint *param_3)

{
  char *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  uint *puVar5;
  int *piVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  byte *pbVar9;
  uint uVar10;
  undefined1 uVar11;
  uint *extraout_EDX;
  uint *extraout_EDX_00;
  uint *extraout_EDX_01;
  uint *extraout_EDX_02;
  uint *extraout_EDX_03;
  uint *extraout_EDX_04;
  uint *extraout_EDX_05;
  uint *extraout_EDX_06;
  uint *extraout_EDX_07;
  uint *puVar12;
  bool bVar13;
  undefined8 uVar14;
  int local_34;
  int local_30 [3];
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  uint *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_10 = ExceptionList;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e6f8;
  ExceptionList = &local_10;
  if ((0 < param_1[0x1f]) &&
     (iVar4 = param_1[0x1f] + -1, ExceptionList = &local_10, param_1[0x1f] = iVar4, iVar4 < 1)) {
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(0xc);
  }
  if ((0 < param_1[0x1e]) && (iVar4 = param_1[0x1e] + -1, param_1[0x1e] = iVar4, iVar4 < 1)) {
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(0xb);
  }
  local_14 = (uint *)((uint)local_14 & 0xffffff00);
  puVar12 = param_3;
joined_r0x0044e465:
  if (puVar12 == (uint *)0x0) {
LAB_0044e65f:
    cVar2 = (char)local_14;
LAB_0044e662:
    iVar4 = param_1[0x1f];
    if (0 < iVar4) {
      iVar4 = iVar4 + 1;
      param_1[0x1f] = iVar4;
    }
    ExceptionList = local_10;
    return CONCAT31((int3)((uint)iVar4 >> 8),cVar2 == '\0');
  }
  uVar10 = puVar12[1];
  switch(uVar10) {
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
      goto LAB_0044e649;
    }
LAB_0044e4d3:
    cVar2 = '\x01';
    goto LAB_0044e662;
  case 3:
    if (((*(byte *)(param_1 + 0x18) & 2) != 0) ||
       (((char *)*param_1 != (char *)param_1[0x14] && (*(char *)*param_1 != '\n'))))
    goto LAB_0044e4d3;
    break;
  case 4:
    uVar10 = param_1[0x18];
    if ((((uVar10 & 4) == 0) || (*param_1 != param_1[0x13])) &&
       (((uVar10 & 8) == 0 || (*param_1 != param_1[0x14])))) {
      if ((*param_1 == param_1[0x13]) && ((uVar10 & 0x100) == 0)) {
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
        bVar13 = false;
      }
      else {
        puVar5 = FUN_0045c740((uint *)
                              "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_",
                              *(char *)*param_1);
        bVar13 = puVar5 != (uint *)0x0;
        param_2 = extraout_EDX_00;
      }
      bVar3 = bVar13 ^ param_3._3_1_;
    }
    else {
      bVar3 = 0;
    }
    if (bVar3 == ((byte)puVar12[2] & 1)) goto LAB_0044e4d3;
    break;
  case 5:
    pcVar1 = (char *)*param_1;
    if (((pcVar1 == (char *)param_1[0x14]) || (*pcVar1 == '\n')) || (*pcVar1 == '\r'))
    goto LAB_0044e4d3;
    *param_1 = (int)(pcVar1 + 1);
    break;
  case 6:
    piVar6 = FUN_0044ee50(&local_1c,(byte *)puVar12[7],(byte *)*param_1,(byte *)param_1[0x14],
                          (byte *)puVar12[7] + puVar12[6],param_1[0x1c],param_1[0x17]);
    if (*piVar6 == *param_1) goto LAB_0044e4d3;
    *param_1 = *piVar6;
    param_2 = extraout_EDX_01;
    break;
  case 7:
    if ((*param_1 == param_1[0x14]) ||
       (uVar7 = FUN_00451ea0(param_1,(int)puVar12), (char)uVar7 == '\0')) goto LAB_0044e4d3;
    local_14 = (uint *)((uint)local_14 & 0xffffff00);
    param_2 = extraout_EDX_02;
    goto LAB_0044e64d;
  case 10:
  case 0xb:
    iVar4 = *param_1;
    local_34 = iVar4;
    uVar14 = FUN_00450ec0(local_30,param_2,param_1 + 1);
    local_24 = param_1[4];
    local_8 = 0;
    local_18 = local_24;
    uVar7 = FUN_0044e410(param_1,(uint *)((ulonglong)uVar14 >> 0x20),(uint *)puVar12[5]);
    if ((bool)(char)uVar7 == (uVar10 == 0xb)) {
      *param_1 = local_34;
      param_1[4] = local_18;
      FUN_00450dd0(param_1 + 1,local_30);
      local_14 = (uint *)CONCAT31(local_14._1_3_,1);
    }
    else {
      *param_1 = iVar4;
    }
    local_8 = 0xffffffff;
    FUN_004483a0((int)&local_34);
    param_2 = extraout_EDX_03;
    break;
  case 0xc:
    goto switchD_0044e47f_caseD_c;
  case 0xd:
    param_2 = (uint *)puVar12[5];
    *(int *)(param_1[5] + (int)param_2 * 8) = *param_1;
    uVar10 = param_1[4];
    if (puVar12[5] < uVar10) {
      do {
        uVar10 = uVar10 - 1;
        param_2 = (uint *)(param_1[1] + (uVar10 >> 5) * 4);
        *param_2 = *param_2 & ~(1 << (uVar10 & 0x1f));
      } while (puVar12[5] < uVar10);
    }
    break;
  case 0xe:
    uVar10 = puVar12[5];
    if ((*(char *)((int)param_1 + 0x65) != '\0') || (*(int *)(uVar10 + 0x14) != 0)) {
      puVar5 = (uint *)(param_1[1] + (*(uint *)(uVar10 + 0x14) >> 5) * 4);
      *puVar5 = *puVar5 | 1 << (*(uint *)(uVar10 + 0x14) & 0x1f);
      param_2 = *(uint **)(uVar10 + 0x14);
      *(int *)(param_1[5] + 4 + (int)param_2 * 8) = *param_1;
    }
    break;
  case 0xf:
    uVar10 = puVar12[5];
    param_2 = (uint *)(param_1[1] + (uVar10 >> 5) * 4);
    if ((*param_2 & 1 << ((byte)uVar10 & 0x1f)) != 0) {
      pbVar9 = (byte *)*param_1;
      puVar8 = (undefined4 *)(param_1[5] + uVar10 * 8);
      puVar5 = (uint *)*puVar8;
      param_2 = (uint *)puVar8[1];
      if (puVar5 != param_2) {
        puVar8 = FUN_00452940(&local_20,param_1[0x1c],pbVar9,(byte *)param_1[0x14],(byte *)puVar5,
                              (byte *)param_2,param_1[0x17]);
        pbVar9 = (byte *)*puVar8;
        param_2 = extraout_EDX_04;
        if (pbVar9 == (byte *)*param_1) goto LAB_0044e4d3;
      }
      *param_1 = (int)pbVar9;
    }
    break;
  case 0x10:
    cVar2 = FUN_004519d0(param_1,param_2,(uint)puVar12);
    local_14 = (uint *)((uint)local_14 & 0xff);
    param_2 = extraout_EDX_05;
    if (cVar2 == '\0') {
      local_14 = (uint *)0x1;
    }
    goto switchD_0044e47f_caseD_c;
  case 0x12:
    bVar3 = (byte)(puVar12[2] >> 1);
    iVar4 = 0;
LAB_0044e779:
    bVar3 = FUN_00451ce0(param_1,param_2,(int)puVar12,bVar3 & 1,iVar4);
    param_2 = local_14;
    uVar11 = SUB41(local_14,0);
    if (bVar3 == 0) {
      uVar11 = 1;
    }
    local_14 = (uint *)CONCAT31(local_14._1_3_,uVar11);
    goto LAB_0044e78e;
  case 0x13:
    param_2 = (uint *)puVar12[5];
    if (param_2[9] == 0) {
      iVar4 = *(int *)(param_1[0x10] + param_2[8] * 8);
      bVar3 = (byte)(param_2[2] >> 1);
      puVar12 = param_2;
      goto LAB_0044e779;
    }
LAB_0044e78e:
    puVar12 = (uint *)0x0;
    break;
  case 0x15:
    if ((((param_1[0x18] & 0x2020U) == 0) || (param_1[0x13] != *param_1)) &&
       (((char)param_1[0x1d] == '\0' || (*param_1 == param_1[0x14])))) {
      if (((char)param_1[0x19] != '\0') &&
         (uVar10 = FUN_00451fe0((int)param_1), param_2 = extraout_EDX_06, (char)uVar10 == '\0'))
      goto LAB_0044e78e;
      FUN_00450670(param_1 + 8,param_1);
      *(undefined1 *)(param_1 + 0x19) = 1;
      puVar12 = (uint *)0x0;
      param_2 = extraout_EDX_07;
    }
    else {
      local_14._1_3_ = (undefined3)((uint)local_14 >> 8);
      local_14 = (uint *)CONCAT31(local_14._1_3_,1);
      puVar12 = (uint *)0x0;
    }
    break;
  default:
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(0xd);
  }
switchD_0044e47f_caseD_1:
LAB_0044e649:
  if ((char)local_14 != '\0') goto LAB_0044e65f;
LAB_0044e64d:
  if (puVar12 == (uint *)0x0) goto LAB_0044e65f;
  puVar12 = (uint *)puVar12[3];
  goto joined_r0x0044e465;
switchD_0044e47f_caseD_c:
  puVar12 = (uint *)0x0;
  goto switchD_0044e47f_caseD_1;
}



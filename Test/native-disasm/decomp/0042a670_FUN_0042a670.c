// FUN_0042a670 @ 0042a670 size=1136 callers=1

/* WARNING: Removing unreachable block (ram,0x0042aa55) */

undefined1 * __cdecl FUN_0042a670(undefined1 *param_1,char *param_2)

{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  char *pcVar6;
  uint *puVar7;
  int *piVar8;
  int iVar9;
  void *this;
  int iVar10;
  undefined1 uVar11;
  void *in_stack_ffffff44;
  void **ppvVar12;
  undefined **local_94;
  int **local_90;
  void *local_84 [5];
  undefined ***local_70;
  void *local_68 [4];
  undefined4 local_58;
  uint local_54;
  undefined4 *local_50;
  char *local_4c;
  int local_48;
  int local_44;
  int local_40;
  void *local_3c [2];
  int local_34 [2];
  undefined4 local_2c;
  uint local_28;
  int *local_24;
  int *local_20;
  int *local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c9d7;
  local_10 = ExceptionList;
  local_28 = 0xf;
  local_2c = 0;
  local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_3c,(uint *)"icons",5);
  local_8 = 1;
  local_4c = (char *)((uint)local_4c & 0xffffff00);
  FUN_004381d0(&local_44,'\0');
  pcVar6 = param_2;
  local_8 = CONCAT31(local_8._1_3_,2);
  pcVar3 = (char *)FUN_004343d0(param_2,(byte *)local_3c);
  cVar1 = *pcVar3;
  FUN_00434820((char *)&local_4c);
  local_8 = 0xffffffff;
  if (0xf < local_28) {
    FUN_00402430(local_3c[0],local_28 + 1,1);
  }
  if (cVar1 != '\x02') goto LAB_0042a90d;
  local_1c = (int *)0x0;
  local_18 = (int *)0x0;
  local_14 = (int *)0x0;
  local_8 = 3;
  bVar2 = false;
  puVar4 = FUN_00440e70(pcVar6,(uint *)"icons");
  FUN_00434120(puVar4,&local_4c);
  FUN_004340a0(this,local_34);
  uVar5 = FUN_004383a0(&local_4c,local_34);
  if ((char)uVar5 == '\0') {
    do {
      pcVar6 = FUN_00433bc0(&local_4c);
      FUN_00440d90(pcVar6,local_84);
      local_8._0_1_ = 4;
      puVar7 = FUN_00404220((uint *)local_68,(char *)local_84);
      local_8._0_1_ = 5;
      piVar8 = FUN_0040a960((int *)&local_50,puVar7);
      local_8 = CONCAT31(local_8._1_3_,6);
      if ((piVar8 < local_18) && (local_1c <= piVar8)) {
        iVar10 = (int)piVar8 - (int)local_1c;
        if (local_18 == local_14) {
          FUN_00435ca0((int *)&local_1c);
        }
        if (local_18 != (int *)0x0) {
          iVar9 = local_1c[iVar10 >> 2];
          local_1c[iVar10 >> 2] = 0;
LAB_0042a7fb:
          *local_18 = iVar9;
        }
      }
      else {
        if (local_18 == local_14) {
          FUN_00435ca0((int *)&local_1c);
        }
        if (local_18 != (int *)0x0) {
          iVar9 = *piVar8;
          *piVar8 = 0;
          goto LAB_0042a7fb;
        }
      }
      local_18 = local_18 + 1;
      if (local_50 != (undefined4 *)0x0) {
        (**(code **)*local_50)();
      }
      if (0xf < local_54) {
        FUN_00402430(local_68[0],local_54 + 1,1);
      }
      local_8 = CONCAT31(local_8._1_3_,3);
      local_54 = 0xf;
      local_58 = 0;
      local_68[0] = (void *)((uint)local_68[0] & 0xffffff00);
      if (&DAT_0000000f < local_70) {
        FUN_00402430(local_84[0],(uint)((int)local_70 + 1),1);
      }
      if (local_18[-1] == 0) {
        bVar2 = true;
      }
      if (*local_4c == '\x01') {
        local_20 = (int *)((uint)local_20 & 0xffffff00);
        FUN_00447660(&local_48);
      }
      else if (*local_4c == '\x02') {
        local_44 = local_44 + 0x10;
      }
      else {
        local_40 = local_40 + 1;
      }
      uVar5 = FUN_004383a0(&local_4c,local_34);
    } while ((char)uVar5 == '\0');
    pcVar6 = param_2;
    if (!bVar2) goto LAB_0042a8b2;
  }
  else {
LAB_0042a8b2:
    local_90 = &local_1c;
    local_94 = &PTR_LAB_0048eed0;
    local_70 = &local_94;
    local_8 = CONCAT31(local_8._1_3_,7);
    FUN_0040f7a0(DAT_004a23dc,(int *)local_70);
    if (local_70 != (undefined ***)0x0) {
      (*(code *)(*local_70)[4])();
    }
  }
  local_8 = 0xffffffff;
  FUN_00435c40((int *)&local_1c);
LAB_0042a90d:
  local_28 = 0xf;
  local_2c = 0;
  local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
  FUN_0043ace0(local_3c,(uint *)"bgColor",7);
  if (*pcVar6 == '\x01') {
    FUN_004437f0(*(void **)(pcVar6 + 8),(int *)&local_24,(byte *)local_3c);
    iVar9 = FUN_00447a70(local_24,local_20);
  }
  else {
    iVar9 = 0;
  }
  if (0xf < local_28) {
    FUN_00402430(local_3c[0],local_28 + 1,1);
  }
  if (iVar9 != 0) {
    pcVar3 = (char *)FUN_00440e70(pcVar6,(uint *)"bgColor");
    FUN_00453810(pcVar3,(uint *)&param_2);
    DAT_004a25d8 = param_2;
  }
  local_28 = 0xf;
  local_2c = 0;
  local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
  FUN_0043ace0(local_3c,(uint *)"posRef",6);
  if (*pcVar6 == '\x01') {
    FUN_004437f0(*(void **)(pcVar6 + 8),(int *)&local_24,(byte *)local_3c);
    iVar9 = FUN_00447a70(local_24,local_20);
  }
  else {
    iVar9 = 0;
  }
  if (0xf < local_28) {
    FUN_00402430(local_3c[0],local_28 + 1,1);
  }
  if (iVar9 != 0) {
    ppvVar12 = local_84;
    puVar4 = FUN_00440e70(pcVar6,(uint *)"posRef");
    puVar4 = FUN_00440bb0(puVar4,ppvVar12);
    if (0xf < (uint)puVar4[5]) {
      puVar4 = (undefined4 *)*puVar4;
    }
    DAT_004a25dd._0_1_ = *(undefined1 *)puVar4;
    if (&DAT_0000000f < local_70) {
      FUN_00402430(local_84[0],(uint)((int)local_70 + 1),1);
    }
  }
                    /* WARNING: Ignoring partial resolution of indirect */
  uVar11 = 0;
  FUN_0043ace0(&stack0xffffff44,(uint *)"posAnchor",9);
  iVar9 = FUN_004341b0(pcVar6,in_stack_ffffff44);
  if (iVar9 != 0) {
    ppvVar12 = local_68;
    puVar4 = FUN_00440e70(pcVar6,(uint *)"posAnchor");
    puVar4 = FUN_00440bb0(puVar4,ppvVar12);
    if (0xf < (uint)puVar4[5]) {
      puVar4 = (undefined4 *)*puVar4;
    }
    DAT_004a25dd._1_1_ = *(undefined1 *)puVar4;
    if (0xf < local_54) {
      FUN_00402430(local_68[0],local_54 + 1,1);
    }
  }
  local_8 = 8;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}



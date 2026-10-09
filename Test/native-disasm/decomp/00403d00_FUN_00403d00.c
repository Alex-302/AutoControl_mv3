// FUN_00403d00 @ 00403d00 size=1060 callers=1

void __fastcall FUN_00403d00(byte *param_1)

{
  uint *puVar1;
  byte *pbVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  int *piVar7;
  undefined4 *puVar8;
  uint *puVar9;
  uint *puVar10;
  void **ppvVar11;
  void **ppvVar12;
  byte *pbVar13;
  byte *pbVar14;
  byte *pbVar15;
  void **this;
  undefined4 local_98 [6];
  undefined4 local_80;
  undefined4 local_7c;
  undefined1 local_78;
  undefined4 *local_74;
  int iStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 local_64;
  undefined1 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined1 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 local_48;
  undefined4 *local_44 [4];
  int *local_34;
  void *local_30 [4];
  undefined4 local_20;
  uint local_1c;
  uint *local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0047925a;
  local_10 = ExceptionList;
  local_80 = 0;
  local_7c = 0;
  local_78 = 0;
  local_74 = (undefined4 *)0x0;
  iStack_70 = 0;
  uStack_6c = 0;
  uStack_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_8 = 0;
  ExceptionList = &local_10;
  piVar7 = FUN_00433840(local_44,"[/@]([^/\\:@]+)[:/]",1);
  local_8 = CONCAT31(local_8._1_3_,1);
  pbVar15 = param_1;
  pbVar2 = param_1;
  if (0xf < *(uint *)(param_1 + 0x14)) {
    pbVar15 = *(byte **)param_1;
    pbVar2 = *(byte **)param_1;
  }
  pbVar13 = param_1;
  if (0xf < *(uint *)(param_1 + 0x14)) {
    pbVar13 = *(byte **)param_1;
  }
  local_11 = FUN_004466f0(&local_7c,piVar7,pbVar13,pbVar15 + *(int *)(param_1 + 0x10),pbVar13,pbVar2
                         );
  if (local_44[0] != (undefined4 *)0x0) {
    LOCK();
    iVar3 = local_44[0][8] + -1;
    local_44[0][8] = iVar3;
    UNLOCK();
    if (iVar3 == 0) {
      FUN_004033e0(local_44[0],(undefined4 *)0x0);
    }
  }
  local_44[0] = (undefined4 *)0x0;
  local_8._0_1_ = 2;
  if ((local_34 != (int *)0x0) &&
     (puVar8 = (undefined4 *)(**(code **)(*local_34 + 8))(), puVar8 != (undefined4 *)0x0)) {
    (**(code **)*puVar8)(1);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  if (local_11 != '\0') {
    puVar8 = &local_50;
    if (1 < (uint)((iStack_70 - (int)local_74) / 0xc)) {
      puVar8 = local_74 + 3;
    }
    local_18 = (uint *)FUN_00433a80(puVar8,(undefined1 *)local_30);
    puVar1 = (uint *)(param_1 + 0x18);
    if (puVar1 != local_18) {
      if (0xf < *(uint *)(param_1 + 0x2c)) {
        FUN_00402430((void *)*puVar1,*(uint *)(param_1 + 0x2c) + 1,1);
      }
      param_1[0x2c] = 0xf;
      param_1[0x2d] = 0;
      param_1[0x2e] = 0;
      param_1[0x2f] = 0;
      param_1[0x28] = 0;
      param_1[0x29] = 0;
      param_1[0x2a] = 0;
      param_1[0x2b] = 0;
      puVar9 = puVar1;
      if (0xf < *(uint *)(param_1 + 0x2c)) {
        puVar9 = (uint *)*puVar1;
      }
      *(byte *)puVar9 = 0;
      FUN_0043b1c0(puVar1,local_18);
    }
    local_8 = local_8 & 0xffffff00;
    if (0xf < local_1c) {
      FUN_00402430(local_30[0],local_1c + 1,1);
    }
  }
  local_18 = FUN_00433840(local_44,"[^:/](/[^?#]*)",1);
  local_8 = CONCAT31(local_8._1_3_,4);
  pbVar15 = param_1;
  pbVar2 = param_1;
  if (0xf < *(uint *)(param_1 + 0x14)) {
    pbVar15 = *(byte **)param_1;
    pbVar2 = *(byte **)param_1;
  }
  pbVar13 = param_1;
  if (0xf < *(uint *)(param_1 + 0x14)) {
    pbVar13 = *(byte **)param_1;
  }
  local_11 = FUN_004466f0(&local_7c,(int *)local_18,pbVar13,pbVar15 + *(int *)(param_1 + 0x10),
                          pbVar13,pbVar2);
  if (local_44[0] != (undefined4 *)0x0) {
    LOCK();
    piVar7 = local_44[0] + 8;
    iVar3 = *piVar7;
    *piVar7 = *piVar7 + -1;
    UNLOCK();
    if (iVar3 == 1) {
      FUN_004033e0(local_44[0],(undefined4 *)0x0);
    }
  }
  local_44[0] = (undefined4 *)0x0;
  local_8._0_1_ = 5;
  if ((local_34 != (int *)0x0) &&
     (puVar8 = (undefined4 *)(**(code **)(*local_34 + 8))(), puVar8 != (undefined4 *)0x0)) {
    (**(code **)*puVar8)(1);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  if (local_11 != '\0') {
    puVar8 = &local_50;
    if (1 < (uint)((iStack_70 - (int)local_74) / 0xc)) {
      puVar8 = local_74 + 3;
    }
    puVar9 = (uint *)FUN_00433a80(puVar8,(undefined1 *)local_30);
    puVar1 = (uint *)(param_1 + 0x30);
    if (puVar1 != puVar9) {
      if (0xf < *(uint *)(param_1 + 0x44)) {
        FUN_00402430((void *)*puVar1,*(uint *)(param_1 + 0x44) + 1,1);
      }
      param_1[0x44] = 0xf;
      param_1[0x45] = 0;
      param_1[0x46] = 0;
      param_1[0x47] = 0;
      param_1[0x40] = 0;
      param_1[0x41] = 0;
      param_1[0x42] = 0;
      param_1[0x43] = 0;
      puVar10 = puVar1;
      if (0xf < *(uint *)(param_1 + 0x44)) {
        puVar10 = (uint *)*puVar1;
      }
      *(undefined1 *)puVar10 = 0;
      FUN_0043b1c0(puVar1,puVar9);
    }
    local_8 = local_8 & 0xffffff00;
    if (0xf < local_1c) {
      FUN_00402430(local_30[0],local_1c + 1,1);
    }
  }
  local_18 = FUN_00433840(local_44,
                          "[^.]+(\\.(gov|com|org|edu|net|co|mil|eu|ac|info|biz|leg|int|nom|name|gob|web))?\\.(?!\\d+)[^.]+$"
                          ,0x700);
  pbVar2 = param_1 + 0x18;
  local_8 = CONCAT31(local_8._1_3_,7);
  pbVar13 = pbVar2;
  pbVar15 = pbVar2;
  if (0xf < *(uint *)(param_1 + 0x2c)) {
    pbVar13 = *(byte **)pbVar2;
    pbVar15 = *(byte **)pbVar2;
  }
  pbVar14 = pbVar2;
  if (0xf < *(uint *)(param_1 + 0x2c)) {
    pbVar14 = *(byte **)pbVar2;
  }
  cVar6 = FUN_004466f0(&local_7c,(int *)local_18,pbVar14,pbVar13 + *(int *)(param_1 + 0x28),pbVar14,
                       pbVar15);
  if (cVar6 == '\0') {
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
    FUN_0043ade0(local_30,(undefined4 *)pbVar2,0,0xffffffff);
    ppvVar11 = local_30;
    bVar5 = false;
    bVar4 = true;
  }
  else {
    iVar3 = iStack_70 - (int)local_74 >> 0x1f;
    puVar8 = &local_50;
    if ((iStack_70 - (int)local_74) / 0xc + iVar3 != iVar3) {
      puVar8 = local_74;
    }
    ppvVar11 = (void **)FUN_00433a80(puVar8,(undefined1 *)local_98);
    bVar5 = true;
    bVar4 = false;
  }
  this = (void **)(param_1 + 0x48);
  if (this != ppvVar11) {
    if (0xf < *(uint *)(param_1 + 0x5c)) {
      FUN_00402430(*this,*(uint *)(param_1 + 0x5c) + 1,1);
    }
    param_1[0x5c] = 0xf;
    param_1[0x5d] = 0;
    param_1[0x5e] = 0;
    param_1[0x5f] = 0;
    param_1[0x58] = 0;
    param_1[0x59] = 0;
    param_1[0x5a] = 0;
    param_1[0x5b] = 0;
    ppvVar12 = this;
    if (0xf < *(uint *)(param_1 + 0x5c)) {
      ppvVar12 = *this;
    }
    *(byte *)ppvVar12 = 0;
    FUN_0043b1c0(this,(uint *)ppvVar11);
  }
  if (bVar4) {
    if (0xf < local_1c) {
      FUN_00402430(local_30[0],local_1c + 1,1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  }
  if (bVar5) {
    FUN_004061c0(local_98);
  }
  FUN_004337d0((int *)local_44);
  FUN_004041d0((int)&local_7c);
  ExceptionList = local_10;
  return;
}



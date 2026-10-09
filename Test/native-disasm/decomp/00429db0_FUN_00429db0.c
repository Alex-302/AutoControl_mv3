// FUN_00429db0 @ 00429db0 size=733 callers=1

void __fastcall FUN_00429db0(void *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  uint *puVar3;
  char *pcVar4;
  uint *puVar5;
  uint *puVar6;
  void *this;
  void *this_00;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  int iVar7;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint *local_18;
  uint *local_14;
  uint *local_10 [3];
  
  pcVar4 = (char *)FUN_00434550(param_1,0);
  FUN_004536b0(pcVar4,&local_20);
  local_24 = local_20;
  pcVar4 = (char *)FUN_00434550(param_1,1);
  FUN_004536b0(pcVar4,&local_20);
  local_1c = local_20;
  FUN_00437090(&local_18,(byte *)&local_24);
  iVar7 = 0;
  puVar5 = local_18;
  if (local_18 != local_14) {
    do {
      puVar5 = (uint *)*puVar5;
      iVar7 = iVar7 + 1;
    } while (puVar5 != local_14);
    if (iVar7 != 0) {
      FUN_00437190(&local_18,(byte *)&local_24);
      puVar5 = local_18;
      if (local_18 == DAT_004a27d4) {
        local_18 = &local_24;
        FUN_0044a880(this,(int *)local_10,this,&local_18);
        puVar5 = local_10[0];
      }
      local_20 = puVar5[3];
      FUN_00437090(&local_18,(byte *)&local_24);
      for (puVar5 = local_18; puVar5 != local_14; puVar5 = (uint *)*puVar5) {
      }
      FUN_00437230((int *)&local_18,(int *)local_18,(int *)local_14);
      FUN_00437190(&local_18,(byte *)&local_1c);
      puVar5 = local_18;
      if (local_18 == DAT_004a27d4) {
        local_18 = &local_1c;
        FUN_0044a880(this_00,(int *)local_10,this_00,&local_18);
        puVar5 = local_10[0];
      }
      puVar5[3] = local_20;
      FUN_00436250(&DAT_004a2770,(int *)&local_18,(byte *)&local_20);
      puVar5 = local_18;
      if (local_18 == DAT_004a2774) {
        local_18 = &local_20;
        FUN_0044a3a0(&DAT_004a2770,(int *)local_10,extraout_ECX,&local_18);
        puVar5 = local_10[0];
      }
      puVar6 = DAT_004a2774;
      if (puVar5[3] == local_24) {
        FUN_00436250(&DAT_004a2770,(int *)&local_18,(byte *)&local_20);
        puVar5 = local_18;
        if (local_18 == puVar6) {
          local_18 = &local_20;
          FUN_0044a3a0(&DAT_004a2770,(int *)local_10,extraout_ECX_00,&local_18);
          puVar5 = local_10[0];
        }
        puVar5[3] = local_1c;
      }
    }
  }
  FUN_00436350(&DAT_004a290c,(int *)&local_18,(byte *)&local_24);
  iVar7 = 0;
  puVar5 = local_18;
  if (local_18 != local_14) {
    do {
      puVar5 = (uint *)*puVar5;
      iVar7 = iVar7 + 1;
    } while (puVar5 != local_14);
    if (iVar7 != 0) {
      FUN_00436250(&DAT_004a290c,(int *)&local_18,(byte *)&local_24);
      puVar5 = local_18;
      if (local_18 == DAT_004a2910) {
        local_18 = &local_24;
        FUN_0044a600(&DAT_004a290c,(int *)local_10,extraout_ECX_01,&local_18);
        puVar5 = local_10[0];
      }
      puVar3 = DAT_004a2910;
      puVar5 = puVar5 + 3;
      FUN_00436250(&DAT_004a290c,(int *)&local_18,(byte *)&local_1c);
      puVar6 = local_18;
      if (local_18 == puVar3) {
        local_18 = &local_1c;
        FUN_0044a600(&DAT_004a290c,(int *)local_10,extraout_ECX_02,&local_18);
        puVar6 = local_10[0];
      }
      puVar6 = puVar6 + 3;
      if (puVar6 != puVar5) {
        uVar1 = *puVar5;
        *puVar5 = 0;
        puVar2 = (undefined4 *)*puVar6;
        *puVar6 = uVar1;
        if (puVar2 != (undefined4 *)0x0) {
          (**(code **)*puVar2)(1);
        }
      }
      FUN_00436350(&DAT_004a290c,(int *)&local_18,(byte *)&local_24);
      for (puVar5 = local_18; puVar5 != local_14; puVar5 = (uint *)*puVar5) {
      }
      FUN_00436410(&DAT_004a290c,&local_18,(int *)local_18,(int *)local_14);
    }
  }
  return;
}



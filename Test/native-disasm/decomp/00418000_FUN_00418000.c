// FUN_00418000 @ 00418000 size=377 callers=1

void __fastcall FUN_00418000(char *param_1)

{
  bool bVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined **local_70;
  undefined1 local_6c;
  undefined ***local_4c;
  char local_48 [16];
  void *local_38 [3];
  char local_2c [8];
  undefined8 local_24;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b1e0;
  local_10 = ExceptionList;
  if (*(char *)((int)*(void **)(param_1 + 4) + 0x34) != '\0') {
    ExceptionList = &local_10;
    FUN_00417e10(*(void **)(param_1 + 4),'\x01');
    ExceptionList = local_10;
    return;
  }
  ExceptionList = &local_10;
  FUN_00416fe0(local_48,(undefined4 *)0x1,1000);
  local_8._0_1_ = 0;
  local_8._1_3_ = 0;
  if (*param_1 != '\0') {
    local_1c = CONCAT31(local_1c._1_3_,1);
    uVar3 = local_1c;
    local_2c[0] = '\x04';
    local_24 = CONCAT44(local_18,local_1c);
    local_8._0_1_ = 1;
    local_8._1_3_ = 0;
    pcVar2 = (char *)FUN_00440e70(local_48,(uint *)"noEvt");
    local_8._0_1_ = 0;
    local_2c[0] = *pcVar2;
    *pcVar2 = '\x04';
    local_24 = *(undefined8 *)(pcVar2 + 8);
    *(undefined4 *)(pcVar2 + 8) = uVar3;
    *(undefined4 *)(pcVar2 + 0xc) = local_18;
    FUN_00434820(local_2c);
  }
  FUN_00408600(0x2e4,local_48);
  FUN_00417e10(*(void **)(param_1 + 4),'\x01');
  if (*(char *)(*(int *)(param_1 + 4) + 0x35) != '\0') {
    pcVar2 = (char *)FUN_00440e70(local_48,(uint *)"trueFmt");
    bVar1 = FUN_00441d30(pcVar2);
    if (bVar1) {
      FUN_00416e80();
      local_8._0_1_ = 2;
      uVar3 = FUN_00416e20((byte *)local_38);
      local_11 = (undefined1)uVar3;
      FUN_00418180(local_38);
      if (*param_1 == '\0') {
        local_6c = local_11;
        local_4c = &local_70;
        local_70 = &PTR_LAB_0048ef08;
        local_8._0_1_ = 3;
        FUN_0040f6b0(DAT_004a2458,(int *)local_4c,0);
        if (local_4c != (undefined ***)0x0) {
          (*(code *)(*local_4c)[4])(local_4c != &local_70);
        }
      }
      FUN_004061c0(local_38);
    }
  }
  FUN_00434820(local_48);
  ExceptionList = local_10;
  return;
}



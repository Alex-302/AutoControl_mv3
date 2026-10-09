// FUN_004466f0 @ 004466f0 size=381 callers=5

undefined1 __fastcall
FUN_004466f0(undefined4 *param_1,int *param_2,byte *param_3,byte *param_4,undefined4 param_5,
            undefined4 param_6)

{
  int iVar1;
  byte *pbVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 uVar5;
  undefined1 local_94 [32];
  undefined1 local_74 [32];
  void *local_54;
  undefined4 local_50;
  int local_4c;
  byte *local_40;
  uint local_34;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e44b;
  local_10 = ExceptionList;
  iVar1 = *param_2;
  if (iVar1 == 0) {
    return 0;
  }
  uVar5 = 0;
  ExceptionList = &local_10;
  FUN_00448530(local_94,param_3,param_4,param_2 + 1,iVar1,*(undefined4 *)(iVar1 + 0x1c),
               *(undefined4 *)(iVar1 + 0x14));
  local_8 = 0;
  uVar3 = FUN_00449b30(local_94,param_1);
  if ((char)uVar3 == '\0') {
    if (param_3 == param_4) goto LAB_00446817;
    local_34 = local_34 & 0xffffdfff | 0x100;
    piVar4 = (int *)FUN_00449920(local_94,&local_14,param_3 + 1,param_4,0);
    pbVar2 = (byte *)*piVar4;
    while (pbVar2 != param_4) {
      local_40 = pbVar2;
      uVar3 = FUN_00449b30(local_94,param_1);
      if ((char)uVar3 != '\0') goto LAB_00446800;
      piVar4 = (int *)FUN_00449920(local_94,&local_14,pbVar2 + 1,param_4,0);
      pbVar2 = (byte *)*piVar4;
    }
    local_40 = param_4;
    uVar3 = FUN_00449b30(local_94,param_1);
    if ((char)uVar3 == '\0') goto LAB_00446817;
  }
LAB_00446800:
  uVar5 = 1;
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = param_6;
    param_1[5] = param_3;
    *(bool *)(param_1 + 7) = param_3 != (byte *)param_1[6];
  }
LAB_00446817:
  if (local_54 != (void *)0x0) {
    FUN_00402430(local_54,local_4c - (int)local_54 >> 3,8);
    local_54 = (void *)0x0;
    local_50 = 0;
    local_4c = 0;
  }
  FUN_00448330((int)local_74);
  FUN_00448330((int)local_94);
  ExceptionList = local_10;
  return uVar5;
}



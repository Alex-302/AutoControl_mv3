// FUN_00446870 @ 00446870 size=337 callers=2

undefined1 __fastcall
FUN_00446870(byte *param_1,byte *param_2,undefined4 param_3,int *param_4,uint param_5)

{
  int iVar1;
  bool bVar2;
  byte *pbVar3;
  undefined1 uVar4;
  int local_94 [8];
  undefined1 local_74 [32];
  void *local_54;
  undefined4 local_50;
  int local_4c;
  byte *local_40;
  uint local_34;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e44b;
  local_10 = ExceptionList;
  iVar1 = *param_4;
  if (iVar1 == 0) {
    return 0;
  }
  uVar4 = 0;
  ExceptionList = &local_10;
  FUN_004483e0(local_94,param_1,param_2,param_4 + 1,iVar1,*(undefined4 *)(iVar1 + 0x1c),
               *(undefined4 *)(iVar1 + 0x14),param_5);
  local_8 = 0;
  bVar2 = FUN_00449e60(local_94);
  if (bVar2) {
LAB_004468e7:
    uVar4 = 1;
  }
  else if ((param_1 != param_2) && ((param_5 & 0x40) == 0)) {
    local_34 = local_34 & 0xffffdfff | 0x100;
    for (pbVar3 = FUN_00449c70(local_94,param_1 + 1,param_2,0); pbVar3 != param_2;
        pbVar3 = FUN_00449c70(local_94,pbVar3 + 1,param_2,0)) {
      local_40 = pbVar3;
      bVar2 = FUN_00449e60(local_94);
      if (bVar2) goto LAB_004468e7;
    }
    local_40 = param_2;
    bVar2 = FUN_00449e60(local_94);
    if (bVar2) {
      uVar4 = 1;
    }
  }
  if (local_54 != (void *)0x0) {
    FUN_00402430(local_54,local_4c - (int)local_54 >> 3,8);
    local_54 = (void *)0x0;
    local_50 = 0;
    local_4c = 0;
  }
  FUN_00448330((int)local_74);
  FUN_00448330((int)local_94);
  ExceptionList = local_10;
  return uVar4;
}



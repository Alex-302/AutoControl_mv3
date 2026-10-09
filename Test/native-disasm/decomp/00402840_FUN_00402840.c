// FUN_00402840 @ 00402840 size=267 callers=1

undefined1 * __thiscall FUN_00402840(void *this,undefined1 *param_1)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  void **ppvVar4;
  uint uVar5;
  uint *puVar6;
  uint *puVar7;
  void *local_48 [4];
  undefined4 local_38;
  uint local_34;
  void *local_30 [4];
  undefined4 local_20;
  uint local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_00479119;
  local_10 = ExceptionList;
  local_18 = 0;
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 == 0) {
    local_34 = 0xf;
    local_48[0] = (void *)((uint)local_48[0] & 0xffffff00);
    ppvVar4 = local_48;
    bVar3 = true;
    bVar2 = false;
    local_38 = 0;
    ExceptionList = &local_10;
  }
  else {
    puVar7 = *(uint **)(iVar1 + 0x18);
    if (puVar7 == (uint *)0x0) {
      puVar7 = (uint *)(iVar1 + 0x1c);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
    if ((char)*puVar7 == '\0') {
      uVar5 = 0;
    }
    else {
      puVar6 = puVar7;
      do {
        uVar5 = *puVar6;
        puVar6 = (uint *)((int)puVar6 + 1);
      } while ((char)uVar5 != '\0');
      uVar5 = (int)puVar6 - ((int)puVar7 + 1);
    }
    ExceptionList = &local_10;
    FUN_0043ace0(local_30,puVar7,uVar5);
    ppvVar4 = local_30;
    bVar3 = false;
    bVar2 = true;
  }
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  FUN_0043b1c0(param_1,(uint *)ppvVar4);
  if (bVar2) {
    if (0xf < local_1c) {
      FUN_00402430(local_30[0],local_1c + 1,1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  }
  if ((bVar3) && (0xf < local_34)) {
    FUN_00402430(local_48[0],local_34 + 1,1);
  }
  ExceptionList = local_10;
  return param_1;
}



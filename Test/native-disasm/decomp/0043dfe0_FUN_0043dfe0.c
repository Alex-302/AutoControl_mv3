// FUN_0043dfe0 @ 0043dfe0 size=198 callers=1

undefined1 * __thiscall FUN_0043dfe0(void *this,undefined1 *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  void *local_20 [4];
  undefined4 local_10;
  uint local_c;
  
  if (((*(uint *)((int)this + 0x3c) & 2) == 0) &&
     (uVar1 = **(uint **)((int)this + 0x20), uVar1 != 0)) {
    uVar3 = *(uint *)((int)this + 0x38);
    if (*(uint *)((int)this + 0x38) < uVar1) {
      uVar3 = uVar1;
    }
    puVar2 = *(undefined4 **)((int)this + 0x10);
  }
  else {
    if (((*(uint *)((int)this + 0x3c) & 4) != 0) || (**(int **)((int)this + 0x1c) == 0)) {
      local_c = 0xf;
      local_10 = 0;
      local_20[0] = (void *)((uint)local_20[0]._1_3_ << 8);
      goto LAB_0043e064;
    }
    puVar2 = *(undefined4 **)((int)this + 0xc);
    uVar3 = **(int **)((int)this + 0x2c) + **(int **)((int)this + 0x1c);
  }
  local_c = 0xf;
  local_10 = 0;
  local_20[0] = (void *)((uint)local_20[0]._1_3_ << 8);
  FUN_0043ace0(local_20,(uint *)*puVar2,uVar3 - (int)*puVar2);
LAB_0043e064:
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  FUN_0043b1c0(param_1,(uint *)local_20);
  if (0xf < local_c) {
    FUN_00402430(local_20[0],local_c + 1,1);
  }
  return param_1;
}



// FUN_00403a70 @ 00403a70 size=417 callers=5

void * __thiscall FUN_00403a70(void *this,undefined4 *param_1)

{
  undefined4 *this_00;
  int iVar1;
  undefined4 **ppuVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint in_stack_00000014;
  uint in_stack_00000018;
  ushort *in_stack_ffffffa4;
  void *local_34 [4];
  uint local_24;
  uint local_20;
  undefined4 local_1c;
  void *local_18;
  ushort local_14 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791ee;
  local_10 = ExceptionList;
  local_1c = 0;
  local_8 = 0;
  ExceptionList = &local_10;
  local_18 = this;
  iVar1 = FUN_0043a160(&param_1,(short *)&DAT_0048cc54,this,1);
  uVar6 = iVar1 + 1;
  if (uVar6 <= in_stack_00000014) {
    ppuVar2 = &param_1;
    if (7 < in_stack_00000018) {
      ppuVar2 = (undefined4 **)param_1;
    }
    local_14[0] = 0x5c;
    local_14[1] = 0;
    in_stack_00000014 = uVar6;
    *(undefined2 *)((int)ppuVar2 + uVar6 * 2) = 0;
    iVar1 = FUN_0043a2d0(&param_1,local_14);
    uVar6 = iVar1 + 1;
    if (iVar1 == -1) {
      uVar6 = 0;
    }
    FUN_00434e10(&param_1,(undefined2 *)local_34,uVar6,0xffffffff);
    local_8 = CONCAT31(local_8._1_3_,1);
    local_14[0] = 0x2e;
    local_14[1] = 0;
    uVar3 = FUN_0043a2d0(local_34,local_14);
    uVar4 = local_24;
    if (uVar3 < local_24) {
      local_14[0] = 0x2e;
      local_14[1] = 0;
      uVar4 = FUN_0043a2d0(local_34,local_14);
    }
    FUN_00434e10(&param_1,this,0,uVar6);
    this_00 = (undefined4 *)((int)this + 0x18);
    local_8._0_1_ = 2;
    *(undefined4 *)((int)this + 0x2c) = 7;
    *(undefined4 *)((int)this + 0x28) = 0;
    puVar5 = this_00;
    if (7 < *(uint *)((int)this + 0x2c)) {
      puVar5 = (undefined4 *)*this_00;
    }
    *(undefined2 *)puVar5 = 0;
    FUN_0043a750(this_00,local_34,0,0xffffffff);
    local_8._0_1_ = 3;
    FUN_00434e10(local_34,(undefined2 *)((int)this + 0x30),0,uVar4);
    local_8 = CONCAT31(local_8._1_3_,4);
    if (uVar4 + 1 < local_24) {
      local_24 = uVar4 + 1;
    }
    FUN_00434e10(local_34,(undefined2 *)&stack0xffffffa4,local_24,0xffffffff);
    FUN_004039b0((void *)((int)this + 0x48),in_stack_ffffffa4);
    if (7 < local_20) {
      FUN_00402430(local_34[0],local_20 + 1,2);
    }
    local_20 = 7;
    local_34[0] = (void *)((uint)local_34[0] & 0xffff0000);
    local_24 = 0;
    if (7 < in_stack_00000018) {
      FUN_00402430(param_1,in_stack_00000018 + 1,2);
    }
    ExceptionList = local_10;
    return this;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ee4("invalid string position");
}



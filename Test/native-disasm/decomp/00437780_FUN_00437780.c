// FUN_00437780 @ 00437780 size=208 callers=2

void * __thiscall FUN_00437780(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  puVar1 = (undefined4 *)((int)this + 4);
  ExceptionList = &local_10;
  *(undefined4 *)this = *param_1;
  *puVar1 = 0;
  *(undefined4 *)((int)this + 8) = 0;
  uVar2 = FUN_00448fe0((undefined4 *)0x0,(undefined4 *)0x0);
  *puVar1 = uVar2;
  *puVar1 = param_1[1];
  param_1[1] = uVar2;
  uVar2 = *(undefined4 *)((int)this + 8);
  *(undefined4 *)((int)this + 8) = param_1[2];
  param_1[2] = uVar2;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0xc) = param_1[3];
  *(undefined4 *)((int)this + 0x10) = param_1[4];
  *(undefined4 *)((int)this + 0x14) = param_1[5];
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *(undefined4 *)((int)this + 0x18) = param_1[6];
  *(undefined4 *)((int)this + 0x1c) = param_1[7];
  local_8 = 0;
  FUN_0043edd0(param_1 + 1);
  FUN_00435e50(param_1,8);
  ExceptionList = local_10;
  return this;
}



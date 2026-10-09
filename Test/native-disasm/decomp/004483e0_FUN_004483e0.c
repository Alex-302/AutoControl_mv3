// FUN_004483e0 @ 004483e0 size=321 callers=1

void * __thiscall
FUN_004483e0(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
            undefined4 param_5,undefined4 param_6,uint param_7)

{
  undefined1 uVar1;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e55e;
  local_10 = ExceptionList;
  local_14 = 0;
  ExceptionList = &local_10;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  FUN_0043ef20((undefined4 *)((int)this + 4),0,&local_14);
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  local_8 = 0;
  local_14 = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 0x28) = 0;
  *(undefined4 *)((int)this + 0x2c) = 0;
  FUN_0043ef20((undefined4 *)((int)this + 0x24),0,&local_14);
  *(undefined4 *)((int)this + 0x30) = 0;
  *(undefined4 *)((int)this + 0x34) = 0;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 0x3c) = 0;
  *(undefined4 *)((int)this + 0x40) = 0;
  *(undefined4 *)((int)this + 0x44) = 0;
  *(undefined4 *)((int)this + 0x48) = 0;
  local_8 = CONCAT31(local_8._1_3_,2);
  *(undefined4 *)((int)this + 0x50) = param_2;
  *(undefined4 *)((int)this + 0x54) = param_1;
  *(undefined4 *)((int)this + 0x5c) = param_6;
  *(int *)((int)this + 0x58) = param_4;
  *(uint *)((int)this + 0x60) = param_7;
  *(undefined1 *)((int)this + 100) = 0;
  *(undefined4 *)((int)this + 0x68) = param_5;
  if (((*(byte *)(param_4 + 8) & 8) == 0) || ((param_7 & 0x10) != 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)((int)this + 0x6c) = uVar1;
  *(undefined4 *)((int)this + 0x70) = param_3;
  FUN_00449010((undefined4 *)((int)this + 0x40),*(uint *)(param_4 + 0x18));
  ExceptionList = local_10;
  return this;
}



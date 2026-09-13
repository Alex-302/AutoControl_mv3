// FUN_00448530 @ 00448530 size=172 callers=1

void * __thiscall
FUN_00448530(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
            undefined4 param_5,undefined4 param_6)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e58e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00448a50(this);
  local_8 = 0;
  FUN_00448a50((undefined4 *)((int)this + 0x20));
  *(undefined4 *)((int)this + 0x40) = 0;
  *(undefined4 *)((int)this + 0x44) = 0;
  *(undefined4 *)((int)this + 0x48) = 0;
  local_8 = CONCAT31(local_8._1_3_,2);
  *(undefined4 *)((int)this + 0x4c) = 0;
  *(undefined4 *)((int)this + 0x50) = param_2;
  *(undefined4 *)((int)this + 0x54) = param_1;
  *(undefined4 *)((int)this + 0x5c) = param_6;
  *(undefined4 *)((int)this + 0x68) = param_5;
  *(int *)((int)this + 0x58) = param_4;
  *(undefined4 *)((int)this + 0x60) = 0;
  *(undefined1 *)((int)this + 100) = 0;
  *(byte *)((int)this + 0x6c) = *(byte *)(param_4 + 8) >> 3 & 1;
  *(undefined4 *)((int)this + 0x70) = param_3;
  FUN_00449010((undefined4 *)((int)this + 0x40),*(uint *)(param_4 + 0x18));
  ExceptionList = local_10;
  return this;
}



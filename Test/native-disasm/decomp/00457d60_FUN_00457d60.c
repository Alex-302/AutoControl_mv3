// FUN_00457d60 @ 00457d60 size=153 callers=1

void * __thiscall FUN_00457d60(void *this,undefined4 *param_1)

{
  uint *puVar1;
  undefined1 *puVar2;
  char local_24 [8];
  undefined1 local_1c [8];
  void *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ec96;
  local_10 = ExceptionList;
  puVar1 = (uint *)*param_1;
  ExceptionList = &local_10;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x14) = 0xf;
  *(undefined4 *)((int)this + 0x10) = 0;
  puVar2 = this;
  if (0xf < *(uint *)((int)this + 0x14)) {
    puVar2 = *(undefined1 **)this;
  }
  *puVar2 = 0;
  local_14 = this;
  FUN_0043b1c0(this,puVar1);
  local_8 = 1;
  local_24[0] = '\0';
  FUN_004381d0(local_1c,'\0');
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_004123b0((void *)((int)this + 0x18),local_24);
  FUN_00434820(local_24);
  ExceptionList = local_10;
  return this;
}



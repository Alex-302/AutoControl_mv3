// FUN_00404130 @ 00404130 size=145 callers=1

void * __thiscall FUN_00404130(void *this,uint *param_1)

{
  undefined1 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047928b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x14) = 0xf;
  *(undefined4 *)((int)this + 0x10) = 0;
  puVar1 = this;
  if (0xf < *(uint *)((int)this + 0x14)) {
    puVar1 = *(undefined1 **)this;
  }
  *puVar1 = 0;
  FUN_0043b1c0(this,param_1);
  local_8 = 0;
  _eh_vector_constructor_iterator_((void *)((int)this + 0x18),0x18,3,FUN_00435660,FUN_004061c0);
  local_8 = 1;
  FUN_00403d00(this);
  ExceptionList = local_10;
  return this;
}



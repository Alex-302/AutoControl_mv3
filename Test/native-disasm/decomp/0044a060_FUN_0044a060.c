// FUN_0044a060 @ 0044a060 size=215 callers=1

void * __thiscall FUN_0044a060(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *this_00;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e613;
  local_10 = ExceptionList;
  this_00 = (undefined4 *)((int)this + 0x14);
  ExceptionList = &local_10;
  *(undefined4 *)this = param_2;
  *(undefined4 *)((int)this + 4) = param_2;
  *(undefined4 *)((int)this + 8) = param_3;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  local_14 = 0;
  *this_00 = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  FUN_0043ef20(this_00,0,&local_14);
  *(undefined4 *)((int)this + 0x20) = 0;
  if (*(int *)((int)this + 0x18) - (int)*this_00 >> 2 != 0) {
    FUN_0043ca10(this_00,&local_14,(uint *)*this_00,*(uint **)((int)this + 0x18));
  }
  *(undefined4 *)((int)this + 0x20) = 0;
  local_8 = 1;
  FUN_0044edd0((void *)((int)this + 0x24),param_1);
  *(undefined4 *)((int)this + 0x3c) = param_1;
  *(undefined4 *)((int)this + 0x40) = 1;
  *(undefined4 *)((int)this + 0x50) = 0x8775dfb;
  FUN_00449160(this);
  ExceptionList = local_10;
  return this;
}



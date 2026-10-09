// FUN_0043f780 @ 0043f780 size=159 callers=1

void * __thiscall FUN_0043f780(void *this,undefined4 param_1)

{
  char *pcVar1;
  void *this_00;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047ab50;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined ***)((int)this + *(int *)(*(int *)this + 4)) = &PTR_LAB_0048ec6c;
  *(int *)(*(int *)(*(int *)this + 4) + -4 + (int)this) = *(int *)(*(int *)this + 4) + -0x18;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  this_00 = (void *)(*(int *)(*(int *)this + 4) + (int)this);
  FUN_004030f0(this_00);
  *(undefined4 *)((int)this_00 + 0x38) = param_1;
  *(undefined4 *)((int)this_00 + 0x3c) = 0;
  pcVar1 = FUN_004405c0(this_00);
  *(char *)((int)this_00 + 0x40) = (char)pcVar1;
  if (*(int *)((int)this_00 + 0x38) == 0) {
    FUN_00402f00(this_00,*(uint *)((int)this_00 + 0xc) | 4,'\0');
  }
  ExceptionList = local_10;
  return this;
}



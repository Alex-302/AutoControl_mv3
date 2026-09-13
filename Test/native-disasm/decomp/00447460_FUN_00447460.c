// FUN_00447460 @ 00447460 size=304 callers=1

void * __thiscall
FUN_00447460(void *this,undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  undefined4 *this_00;
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e4d3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = param_2;
  this_00 = (undefined4 *)((int)this + 0x14);
  *(undefined4 *)((int)this + 4) = param_2;
  *(undefined4 *)((int)this + 8) = param_3;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  param_2 = 0;
  *this_00 = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  FUN_0043ef20(this_00,0,&param_2);
  *(undefined4 *)((int)this + 0x20) = 0;
  if (*(int *)((int)this + 0x18) - (int)*this_00 >> 2 != 0) {
    FUN_0043ca10(this_00,&param_2,(uint *)*this_00,*(uint **)((int)this + 0x18));
  }
  uVar3 = param_4;
  *(undefined4 *)((int)this + 0x20) = 0;
  local_8 = 1;
  FUN_00449430((void *)((int)this + 0x24),param_1,param_4);
  *(uint *)((int)this + 0x40) = uVar3;
  uVar3 = uVar3 & 0x3f;
  *(undefined4 *)((int)this + 0x3c) = param_1;
  if ((uVar3 == 1) || (uVar3 == 0)) {
    uVar2 = 0x8775dfb;
  }
  else if (uVar3 == 2) {
    uVar2 = 0x6e000300;
  }
  else if (uVar3 == 4) {
    uVar2 = 0x7080001b;
  }
  else if (uVar3 == 8) {
    uVar2 = 0x7181a01b;
  }
  else if (uVar3 == 0x10) {
    uVar2 = 0x6e080304;
  }
  else {
    uVar2 = 0;
    if (uVar3 == 0x20) {
      uVar2 = 0x7088001f;
    }
  }
  *(uint *)((int)this + 0x50) = uVar2;
  if ((uVar2 & 0x40000000) != 0) {
    puVar1 = (uint *)(*(int *)((int)this + 0x24) + 8);
    *puVar1 = *puVar1 | 8;
  }
  FUN_00449160(this);
  ExceptionList = local_10;
  return this;
}



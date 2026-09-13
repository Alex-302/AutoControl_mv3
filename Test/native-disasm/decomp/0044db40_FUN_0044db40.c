// FUN_0044db40 @ 0044db40 size=130 callers=1

uint __fastcall FUN_0044db40(int *param_1)

{
  uint uVar1;
  void *this;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047e6e0;
  local_10 = ExceptionList;
  this = (void *)(*(int *)(*param_1 + 4) + (int)param_1);
  ExceptionList = &local_10;
  if (*(int *)((int)this + 0xc) == 0) {
    ExceptionList = &local_10;
    if (*(int **)((int)this + 0x3c) != (int *)0x0) {
      ExceptionList = &local_10;
      FUN_00440030(*(int **)((int)this + 0x3c));
    }
    this = (void *)(*(int *)(*param_1 + 4) + (int)param_1);
    if (*(int *)((int)this + 0xc) == 0) {
      ExceptionList = local_10;
      return CONCAT31((int3)((uint)*param_1 >> 8),1);
    }
  }
  uVar1 = *(uint *)((int)this + 0xc) | 6;
  if (*(int *)((int)this + 0x38) != 0) {
    uVar1 = *(uint *)((int)this + 0xc) | 2;
  }
  uVar1 = FUN_00402f00(this,uVar1,'\0');
  ExceptionList = local_10;
  return uVar1 & 0xffffff00;
}



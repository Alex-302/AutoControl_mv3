// FUN_004339e0 @ 004339e0 size=159 callers=2

void * __thiscall FUN_004339e0(void *this,undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int local_1c [3];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  if (this != param_1) {
    local_8 = 0;
    uVar3 = 0;
    uVar1 = *(uint *)((int)this + 0xc);
    iVar4 = *(int *)this;
    if (uVar1 != 0) {
      if (((int)uVar1 < 0) && (uVar1 != 0)) {
        iVar2 = (-uVar1 - 1 >> 5) * -4 + -4;
      }
      else {
        iVar2 = (uVar1 >> 5) * 4;
      }
      iVar4 = iVar4 + iVar2;
      uVar3 = uVar1 & 0x1f;
    }
    ExceptionList = &local_10;
    FUN_0043cb70(this,local_1c,*(int *)this,0,iVar4,uVar3);
    FUN_00437850(this,param_1);
    *(undefined4 *)((int)this + 0xc) = param_1[3];
    param_1[3] = 0;
  }
  ExceptionList = local_10;
  return this;
}



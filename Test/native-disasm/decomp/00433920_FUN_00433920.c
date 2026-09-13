// FUN_00433920 @ 00433920 size=94 callers=1

void __thiscall FUN_00433920(void *this,void *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int local_10 [3];
  
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
  FUN_0043ca60(this,local_10,1,param_1,iVar4,uVar3);
  return;
}



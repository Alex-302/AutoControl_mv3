// FUN_0044d9f0 @ 0044d9f0 size=149 callers=2

int __thiscall FUN_0044d9f0(void *this,uint param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)((int)this + 4) - *(int *)this;
  iVar2 = iVar3 * 0x2aaaaaab;
  uVar1 = iVar3 / 0xc;
  if (param_1 < uVar1) {
    iVar2 = *(int *)((int)this + 4) + (param_1 - uVar1) * 0xc;
    *(int *)((int)this + 4) = iVar2;
    return iVar2;
  }
  if (uVar1 < param_1) {
    FUN_0044dbd0(this,param_1 - uVar1);
    FUN_004533a0(*(undefined4 **)((int)this + 4),
                 param_1 - (*(int *)((int)this + 4) - *(int *)this) / 0xc);
    iVar2 = (param_1 - (*(int *)((int)this + 4) - *(int *)this) / 0xc) * 0xc;
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + iVar2;
  }
  return iVar2;
}



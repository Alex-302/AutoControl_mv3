// FUN_0043ca60 @ 0043ca60 size=268 callers=2

void __thiscall
FUN_0043ca60(void *this,int *param_1,uint param_2,void *param_3,int param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  uVar3 = FUN_0043efa0(this,param_2,param_4,param_5);
  uVar2 = *(uint *)this;
  uVar1 = uVar3 + param_2;
  if (((int)uVar1 < 0) && (uVar1 != 0)) {
    iVar4 = (-uVar1 - 1 >> 5) * -4 + -4;
  }
  else {
    iVar4 = (uVar1 >> 5) * 4;
  }
  if (((int)uVar3 < 0) && (uVar3 != 0)) {
    iVar5 = (-uVar3 - 1 >> 5) * -4 + -4;
  }
  else {
    iVar5 = (uVar3 >> 5) * 4;
  }
  param_2 = uVar2 & 0xffffff00;
  uVar6 = uVar3 & 0x1f;
  FUN_0044a210(param_3,param_2,(uint *)(uVar2 + iVar5),uVar6,(uint *)(uVar2 + iVar4),uVar1 & 0x1f);
  iVar4 = *(int *)this;
  if (((int)uVar3 < 0) && (uVar3 != 0)) {
    param_1[1] = uVar6;
    *param_1 = iVar4 + (-uVar3 - 1 >> 5) * -4 + -4;
    return;
  }
  param_1[1] = uVar6;
  *param_1 = iVar4 + (uVar3 >> 5) * 4;
  return;
}



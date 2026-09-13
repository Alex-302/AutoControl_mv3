// FUN_0044d710 @ 0044d710 size=187 callers=4

void __thiscall FUN_0044d710(void *this,uint param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  undefined1 local_20 [4];
  int local_1c [4];
  int local_c [3];
  
  local_20[0] = 0;
  uVar1 = *(uint *)((int)this + 0xc);
  if (uVar1 < param_1) {
    iVar5 = *(int *)this;
    uVar4 = 0;
    if (uVar1 != 0) {
      if (((int)uVar1 < 0) && (uVar1 != 0)) {
        iVar2 = (-uVar1 - 1 >> 5) * -4 + -4;
      }
      else {
        iVar2 = (uVar1 >> 5) * 4;
      }
      iVar5 = iVar5 + iVar2;
      uVar4 = uVar1 & 0x1f;
    }
    FUN_0043ca60(this,local_1c,param_1 - uVar1,local_20,iVar5,uVar4);
    return;
  }
  if (param_1 < uVar1) {
    piVar3 = FUN_00433980(this,local_1c + 2);
    local_1c[1] = 0;
    iVar5 = *piVar3;
    iVar2 = piVar3[1];
    local_1c[0] = *(int *)this;
    piVar3 = (int *)FUN_0043eec0(local_1c,local_c,param_1);
    FUN_0043cb70(this,local_1c,*piVar3,piVar3[1],iVar5,iVar2);
  }
  return;
}



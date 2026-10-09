// FUN_0043efa0 @ 0043efa0 size=226 callers=1

int __thiscall FUN_0043efa0(void *this,uint param_1,int param_2,int param_3)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 local_20;
  undefined4 local_1c;
  uint *local_18;
  int local_14;
  int local_10 [2];
  int local_8 [2];
  
  uVar3 = param_1;
  iVar6 = (param_2 - *(int *)this >> 2) * 0x20 + param_3;
  if (param_1 != 0) {
    if (-*(int *)((int)this + 0xc) - 1U < param_1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<bool> too long");
    }
    param_1 = 0;
    FUN_0043fea0(this,uVar3 + 0x1f + *(int *)((int)this + 0xc) >> 5,&param_1);
    iVar1 = *(int *)((int)this + 0xc);
    if (iVar1 == 0) {
      *(uint *)((int)this + 0xc) = uVar3;
      return iVar6;
    }
    FUN_00433980(this,(int *)&local_18);
    local_1c = 0;
    *(uint *)((int)this + 0xc) = uVar3 + iVar1;
    local_20 = *(undefined4 *)this;
    piVar4 = FUN_00433980(this,local_10);
    puVar2 = (uint *)*piVar4;
    uVar3 = piVar4[1];
    puVar5 = (undefined4 *)FUN_0043eec0(&local_20,local_8,iVar6);
    param_1 = param_1 & 0xffffff00;
    FUN_00450370(&local_18,param_1,(uint *)*puVar5,puVar5[1],local_18,local_14,puVar2,uVar3);
  }
  return iVar6;
}



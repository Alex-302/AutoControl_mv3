// FUN_004506f0 @ 004506f0 size=234 callers=10

void * __thiscall FUN_004506f0(void *this,int *param_1)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  if (this != param_1) {
    puVar1 = (uint *)*param_1;
    puVar2 = (uint *)param_1[1];
    if (puVar1 == puVar2) {
      *(undefined4 *)((int)this + 4) = *(undefined4 *)this;
      return this;
    }
    puVar3 = *(uint **)this;
    uVar6 = *(int *)((int)this + 4) - (int)puVar3 >> 3;
    uVar7 = (int)puVar2 - (int)puVar1 >> 3;
    if (uVar7 <= uVar6) {
      FUN_0045b0e0(puVar3,puVar1,(int)puVar2 - (int)puVar1);
      *(int *)((int)this + 4) = *(int *)this + (param_1[1] - *param_1 >> 3) * 8;
      return this;
    }
    uVar5 = *(int *)((int)this + 8) - (int)puVar3 >> 3;
    if (uVar7 <= uVar5) {
      puVar2 = puVar1 + uVar6 * 2;
      FUN_0045b0e0(puVar3,puVar1,(int)puVar2 - (int)puVar1);
      iVar4 = param_1[1];
      puVar1 = *(uint **)((int)this + 4);
      FUN_0045b0e0(puVar1,puVar2,iVar4 - (int)puVar2);
      *(int *)((int)this + 4) = (iVar4 - (int)puVar2) + (int)puVar1;
      return this;
    }
    if (puVar3 != (uint *)0x0) {
      FUN_00402430(puVar3,uVar5,8);
    }
    uVar6 = FUN_00450d00(this,param_1[1] - *param_1 >> 3);
    if ((char)uVar6 != '\0') {
      puVar1 = *(uint **)this;
      uVar6 = param_1[1] - *param_1;
      FUN_0045b0e0(puVar1,(uint *)*param_1,uVar6);
      *(uint *)((int)this + 4) = uVar6 + (int)puVar1;
    }
  }
  return this;
}



// FUN_004507e0 @ 004507e0 size=211 callers=10

void * __thiscall FUN_004507e0(void *this,int *param_1)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  undefined4 uVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  
  if (this != param_1) {
    puVar1 = (uint *)*param_1;
    puVar5 = (uint *)param_1[1];
    if (puVar1 == puVar5) {
      *(undefined4 *)((int)this + 4) = *(undefined4 *)this;
      return this;
    }
    puVar2 = *(uint **)this;
    uVar7 = (int)puVar5 - (int)puVar1 >> 3;
    uVar6 = *(int *)((int)this + 4) - (int)puVar2 >> 3;
    if (uVar7 <= uVar6) {
      FUN_0045b0e0(puVar2,puVar1,(int)puVar5 - (int)puVar1);
      *(int *)((int)this + 4) = *(int *)this + (param_1[1] - *param_1 >> 3) * 8;
      return this;
    }
    uVar3 = *(int *)((int)this + 8) - (int)puVar2 >> 3;
    if (uVar3 < uVar7) {
      if (puVar2 != (uint *)0x0) {
        FUN_00402430(puVar2,uVar3,8);
      }
      uVar6 = FUN_00450d00(this,param_1[1] - *param_1 >> 3);
      if ((char)uVar6 == '\0') {
        return this;
      }
      puVar8 = *(undefined4 **)this;
      puVar5 = (uint *)*param_1;
    }
    else {
      puVar5 = puVar1 + uVar6 * 2;
      FUN_0045b0e0(puVar2,puVar1,(int)puVar5 - (int)puVar1);
      puVar8 = *(undefined4 **)((int)this + 4);
    }
    uVar4 = FUN_00453290(puVar5,(undefined4 *)param_1[1],puVar8);
    *(undefined4 *)((int)this + 4) = uVar4;
  }
  return this;
}



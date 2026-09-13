// FUN_0043c8a0 @ 0043c8a0 size=92 callers=1

undefined4 __thiscall FUN_0043c8a0(void *this,uint param_1)

{
  void *pvVar1;
  int iVar2;
  uint *puVar3;
  undefined4 uVar4;
  ulonglong uVar5;
  
  puVar3 = FUN_0043fde0(param_1);
  uVar5 = FUN_0045b0e0(puVar3,*(uint **)this,*(int *)((int)this + 4) - (int)*(uint **)this);
  uVar4 = (undefined4)uVar5;
  pvVar1 = *(void **)this;
  iVar2 = *(int *)((int)this + 4);
  if (pvVar1 != (void *)0x0) {
    uVar4 = FUN_00402430(pvVar1,*(int *)((int)this + 8) - (int)pvVar1 >> 4,0x10);
  }
  *(uint **)((int)this + 8) = puVar3 + param_1 * 4;
  *(uint *)((int)this + 4) = (iVar2 - (int)pvVar1 & 0xfffffff0U) + (int)puVar3;
  *(uint **)this = puVar3;
  return uVar4;
}



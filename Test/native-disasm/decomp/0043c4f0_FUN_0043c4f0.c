// FUN_0043c4f0 @ 0043c4f0 size=164 callers=1

void __thiscall FUN_0043c4f0(void *this,uint param_1)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  
  puVar3 = FUN_0043fc10(param_1);
  FUN_004500a0(*(int *)this,*(int *)((int)this + 4),puVar3);
  puVar1 = *(uint **)this;
  iVar2 = *(int *)((int)this + 4);
  if (puVar1 != (uint *)0x0) {
    FUN_004479e0(puVar1,*(uint **)((int)this + 4));
    FUN_00402430(*(void **)this,(*(int *)((int)this + 8) - (int)*(void **)this) / 0x28,0x28);
  }
  *(uint **)((int)this + 8) = puVar3 + param_1 * 10;
  *(uint **)((int)this + 4) = puVar3 + ((iVar2 - (int)puVar1) / 0x28) * 10;
  *(uint **)this = puVar3;
  return;
}



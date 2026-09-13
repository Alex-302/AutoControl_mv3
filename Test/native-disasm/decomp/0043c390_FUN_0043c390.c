// FUN_0043c390 @ 0043c390 size=174 callers=1

void __thiscall FUN_0043c390(void *this,uint param_1)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  
  puVar3 = FUN_0043e6a0(param_1);
  FUN_00450000(*(uint **)this,*(uint **)((int)this + 4),puVar3);
  puVar1 = *(uint **)this;
  iVar2 = *(int *)((int)this + 4);
  if (puVar1 != (uint *)0x0) {
    FUN_00447db0(puVar1,*(uint **)((int)this + 4));
    FUN_00402430(*(void **)this,(*(int *)((int)this + 8) - (int)*(void **)this) / 0x1c,0x1c);
  }
  *(uint **)((int)this + 8) = puVar3 + param_1 * 7;
  *(uint **)((int)this + 4) = puVar3 + ((iVar2 - (int)puVar1) / 0x1c) * 7;
  *(uint **)this = puVar3;
  return;
}



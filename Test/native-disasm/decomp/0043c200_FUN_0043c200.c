// FUN_0043c200 @ 0043c200 size=132 callers=1

void __thiscall FUN_0043c200(void *this,uint param_1)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  
  puVar3 = FUN_0043f9c0(param_1);
  FUN_0045b0e0(puVar3,*(uint **)this,*(int *)((int)this + 4) - (int)*(uint **)this);
  iVar1 = *(int *)((int)this + 4);
  iVar2 = *(int *)this;
  if (*(int *)this != 0) {
    FUN_00402430(*(void **)this,(*(int *)((int)this + 8) - *(int *)this) / 0x14,0x14);
  }
  *(uint **)((int)this + 8) = puVar3 + param_1 * 5;
  *(uint **)((int)this + 4) = puVar3 + ((iVar1 - iVar2) / 0x14) * 5;
  *(uint **)this = puVar3;
  return;
}



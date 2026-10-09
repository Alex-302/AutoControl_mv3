// FUN_004378c0 @ 004378c0 size=95 callers=1

/* WARNING: Removing unreachable block (ram,0x00437915) */

void __thiscall FUN_004378c0(void *this,uint param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = param_1;
  uVar2 = param_1 + 0x1f >> 5;
  if (uVar2 < (uint)((int)*(uint **)((int)this + 4) - *(int *)this >> 2)) {
    FUN_0043ca10(this,&param_1,(uint *)(*(int *)this + uVar2 * 4),*(uint **)((int)this + 4));
  }
  *(uint *)((int)this + 0xc) = uVar3;
  uVar3 = uVar3 & 0x1f;
  if (uVar3 != 0) {
    puVar1 = (uint *)(*(int *)this + uVar2 * 4 + -4);
    *puVar1 = *puVar1 & (1 << (sbyte)uVar3) - 1U;
  }
  return;
}



// FUN_004364b0 @ 004364b0 size=142 callers=3

void __thiscall FUN_004364b0(void *this,uint param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if ((uint)((*(int *)((int)this + 8) - *(int *)((int)this + 4)) / 0x28) < param_1) {
    iVar1 = (*(int *)((int)this + 4) - *(int *)this) / 0x28;
    if (0x6666666U - iVar1 < param_1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar4 = param_1 + iVar1;
    uVar2 = (*(int *)((int)this + 8) - *(int *)this) / 0x28;
    uVar3 = 0;
    if (uVar2 <= 0x6666666 - (uVar2 >> 1)) {
      uVar3 = (uVar2 >> 1) + uVar2;
    }
    if (uVar4 <= uVar3) {
      uVar4 = uVar3;
    }
    FUN_0043c4f0(this,uVar4);
  }
  return;
}



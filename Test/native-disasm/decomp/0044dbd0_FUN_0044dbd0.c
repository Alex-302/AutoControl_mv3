// FUN_0044dbd0 @ 0044dbd0 size=139 callers=1

void __thiscall FUN_0044dbd0(void *this,uint param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if ((uint)((*(int *)((int)this + 8) - *(int *)((int)this + 4)) / 0xc) < param_1) {
    iVar1 = (*(int *)((int)this + 4) - *(int *)this) / 0xc;
    if (0x15555555U - iVar1 < param_1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar4 = param_1 + iVar1;
    uVar2 = (*(int *)((int)this + 8) - *(int *)this) / 0xc;
    uVar3 = 0;
    if (uVar2 <= 0x15555555 - (uVar2 >> 1)) {
      uVar3 = (uVar2 >> 1) + uVar2;
    }
    if (uVar4 <= uVar3) {
      uVar4 = uVar3;
    }
    FUN_0044dc60(this,uVar4);
  }
  return;
}



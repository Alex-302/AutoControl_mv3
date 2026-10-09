// FUN_00440190 @ 00440190 size=95 callers=2

void __thiscall FUN_00440190(void *this,uint param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if ((uint)(*(int *)((int)this + 8) - *(int *)((int)this + 4) >> 2) < param_1) {
    iVar2 = *(int *)((int)this + 4) - *(int *)this >> 2;
    if (0x3fffffffU - iVar2 < param_1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar3 = iVar2 + param_1;
    uVar4 = *(int *)((int)this + 8) - *(int *)this >> 2;
    uVar1 = 0;
    if (uVar4 <= 0x3fffffff - (uVar4 >> 1)) {
      uVar1 = (uVar4 >> 1) + uVar4;
    }
    if (uVar3 <= uVar1) {
      uVar3 = uVar1;
    }
    FUN_0043c290(this,uVar3);
  }
  return;
}



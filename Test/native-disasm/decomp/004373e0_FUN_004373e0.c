// FUN_004373e0 @ 004373e0 size=266 callers=1

void __thiscall FUN_004373e0(void *this,uint param_1)

{
  uint uVar1;
  uint uVar2;
  double dVar3;
  void *local_4;
  
  uVar2 = 8;
  local_4 = this;
  if (8 < param_1) {
    do {
      if (0xffffffe < uVar2) {
        if (uVar2 < param_1) {
                    /* WARNING: Subroutine does not return */
          FUN_00458ee4("invalid hash bucket count");
        }
        break;
      }
      uVar2 = uVar2 * 2;
    } while (uVar2 < param_1);
  }
  dVar3 = (double)(int)uVar2 + (double)(&DAT_0048f2d0)[-((int)uVar2 >> 0x1f)];
  while (((float)dVar3 <=
          (float)((double)*(int *)((int)this + 8) +
                 (double)(&DAT_0048f2d0)[-(*(int *)((int)this + 8) >> 0x1f)]) / *(float *)this &&
         (uVar2 < 0xfffffff))) {
    uVar2 = uVar2 * 2;
    dVar3 = (double)(int)uVar2 + (double)(&DAT_0048f2d0)[-((int)uVar2 >> 0x1f)];
  }
  uVar1 = uVar2 * 2;
  if ((uint)(*(int *)((int)this + 0x14) - *(int *)((int)this + 0xc) >> 2) < uVar1) {
    if (0x3fffffff < uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    FUN_0043e4f0((void *)((int)this + 0xc),uVar1);
  }
  param_1 = *(uint *)((int)this + 4);
  *(undefined4 *)((int)this + 0x10) = *(undefined4 *)((int)this + 0xc);
  FUN_0043fa20((void *)((int)this + 0xc),(int *)&local_4,*(uint **)((int)this + 0xc),uVar1,&param_1)
  ;
  *(uint *)((int)this + 0x1c) = uVar2;
  *(uint *)((int)this + 0x18) = uVar2 - 1;
  FUN_0043c970(this);
  return;
}



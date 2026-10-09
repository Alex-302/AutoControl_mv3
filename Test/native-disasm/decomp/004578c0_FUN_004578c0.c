// FUN_004578c0 @ 004578c0 size=80 callers=1

void __thiscall FUN_004578c0(void *this,undefined1 *param_1,undefined1 *param_2)

{
  uint uVar1;
  undefined1 uVar2;
  int iVar3;
  
  do {
    if (param_1 == param_2) {
      return;
    }
    uVar2 = *param_1;
    if (*(uint *)this <= *(uint *)((int)this + 4)) {
      uVar1 = *(uint *)((int)this + 4) + 0x10;
      iVar3 = FUN_0046320d(*(void **)((int)this + 8),uVar1);
      if (iVar3 == 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00458e6a();
      }
      *(int *)((int)this + 8) = iVar3;
      *(uint *)this = uVar1;
    }
    param_1 = param_1 + 1;
    *(undefined1 *)(*(int *)((int)this + 8) + *(int *)((int)this + 4)) = uVar2;
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  } while( true );
}



// FUN_00435e50 @ 00435e50 size=110 callers=46

void __thiscall FUN_00435e50(void *this,int param_1)

{
  uint uVar1;
  int iVar2;
  void *local_4;
  
  iVar2 = param_1;
  uVar1 = param_1 * 2;
  local_4 = this;
  if ((uint)(*(int *)((int)this + 0x14) - *(int *)((int)this + 0xc) >> 2) < uVar1) {
    if (0x3fffffff < uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    FUN_0043e4f0((void *)((int)this + 0xc),uVar1);
  }
  param_1 = *(int *)((int)this + 4);
  *(undefined4 *)((int)this + 0x10) = *(undefined4 *)((int)this + 0xc);
  FUN_0043fa20((void *)((int)this + 0xc),(int *)&local_4,*(uint **)((int)this + 0xc),uVar1,&param_1)
  ;
  *(int *)((int)this + 0x1c) = iVar2;
  *(int *)((int)this + 0x18) = iVar2 + -1;
  return;
}



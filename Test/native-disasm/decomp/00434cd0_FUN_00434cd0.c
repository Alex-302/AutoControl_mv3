// FUN_00434cd0 @ 00434cd0 size=90 callers=59

void __thiscall FUN_00434cd0(void *this,undefined1 *param_1)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar1 = *(undefined1 **)((int)this + 4);
  if ((param_1 < puVar1) && (puVar2 = *(undefined1 **)this, puVar2 <= param_1)) {
    if (puVar1 == *(undefined1 **)((int)this + 8)) {
      FUN_00439fa0(this);
    }
    if (*(undefined1 **)((int)this + 4) != (undefined1 *)0x0) {
      **(undefined1 **)((int)this + 4) = param_1[*(int *)this - (int)puVar2];
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
      return;
    }
  }
  else {
    if (puVar1 == *(undefined1 **)((int)this + 8)) {
      FUN_00439fa0(this);
    }
    if (*(undefined1 **)((int)this + 4) != (undefined1 *)0x0) {
      **(undefined1 **)((int)this + 4) = *param_1;
    }
  }
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  return;
}



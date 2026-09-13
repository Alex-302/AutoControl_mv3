// FUN_00433540 @ 00433540 size=98 callers=3

void __thiscall FUN_00433540(void *this,undefined2 *param_1)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  
  puVar1 = *(undefined2 **)((int)this + 4);
  if ((param_1 < puVar1) && (puVar2 = *(undefined2 **)this, puVar2 <= param_1)) {
    if (puVar1 == *(undefined2 **)((int)this + 8)) {
      FUN_004375a0(this);
    }
    if (*(undefined2 **)((int)this + 4) != (undefined2 *)0x0) {
      **(undefined2 **)((int)this + 4) =
           *(undefined2 *)(*(int *)this + ((int)param_1 - (int)puVar2 >> 1) * 2);
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 2;
      return;
    }
  }
  else {
    if (puVar1 == *(undefined2 **)((int)this + 8)) {
      FUN_004375a0(this);
    }
    if (*(undefined2 **)((int)this + 4) != (undefined2 *)0x0) {
      **(undefined2 **)((int)this + 4) = *param_1;
    }
  }
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 2;
  return;
}



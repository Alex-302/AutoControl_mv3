// FUN_00432e80 @ 00432e80 size=95 callers=6

void __thiscall FUN_00432e80(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = *(undefined4 **)((int)this + 4);
  if ((param_1 < puVar1) && (puVar2 = *(undefined4 **)this, puVar2 <= param_1)) {
    if (puVar1 == *(undefined4 **)((int)this + 8)) {
      FUN_00435b90(this);
    }
    if (*(undefined4 **)((int)this + 4) != (undefined4 *)0x0) {
      **(undefined4 **)((int)this + 4) =
           *(undefined4 *)(*(int *)this + ((int)param_1 - (int)puVar2 >> 2) * 4);
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 4;
      return;
    }
  }
  else {
    if (puVar1 == *(undefined4 **)((int)this + 8)) {
      FUN_00435b90(this);
    }
    if (*(undefined4 **)((int)this + 4) != (undefined4 *)0x0) {
      **(undefined4 **)((int)this + 4) = *param_1;
    }
  }
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 4;
  return;
}



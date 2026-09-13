// FUN_004382c0 @ 004382c0 size=127 callers=1

void __thiscall FUN_004382c0(void *this,undefined1 *param_1)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = *(undefined1 **)((int)this + 4);
  if ((param_1 < puVar2) && (puVar1 = *(undefined1 **)this, puVar1 <= param_1)) {
    if (puVar2 == *(undefined1 **)((int)this + 8)) {
      FUN_0043d4c0(this);
    }
    puVar2 = *(undefined1 **)((int)this + 4);
    if (puVar2 == (undefined1 *)0x0) goto LAB_00438333;
    param_1 = (undefined1 *)(((int)param_1 - (int)puVar1 & 0xfffffff0U) + *(int *)this);
  }
  else {
    if (puVar2 == *(undefined1 **)((int)this + 8)) {
      FUN_0043d4c0(this);
    }
    puVar2 = *(undefined1 **)((int)this + 4);
    if (puVar2 == (undefined1 *)0x0) goto LAB_00438333;
  }
  *puVar2 = *param_1;
  *(undefined4 *)(puVar2 + 8) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(puVar2 + 0xc) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(param_1 + 8) = 0;
  *param_1 = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
LAB_00438333:
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 0x10;
  return;
}



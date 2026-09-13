// FUN_00433020 @ 00433020 size=150 callers=1

void __thiscall FUN_00433020(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = *(undefined4 **)((int)this + 4);
  if ((param_1 < puVar1) && (puVar2 = *(undefined4 **)this, puVar2 <= param_1)) {
    if (puVar1 == *(undefined4 **)((int)this + 8)) {
      FUN_00436d20(this);
    }
    puVar1 = *(undefined4 **)((int)this + 4);
    if (puVar1 == (undefined4 *)0x0) goto LAB_004330ad;
    param_1 = (undefined4 *)(*(int *)this + (((int)param_1 - (int)puVar2) / 0x1c) * 0x1c);
    *puVar1 = *param_1;
  }
  else {
    if (puVar1 == *(undefined4 **)((int)this + 8)) {
      FUN_00436d20(this);
    }
    puVar1 = *(undefined4 **)((int)this + 4);
    if (puVar1 == (undefined4 *)0x0) goto LAB_004330ad;
    *puVar1 = *param_1;
  }
  puVar1[6] = 0xf;
  puVar1[5] = 0;
  *(undefined1 *)(puVar1 + 1) = 0;
  FUN_0043b1c0(puVar1 + 1,param_1 + 1);
LAB_004330ad:
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 0x1c;
  return;
}



// FUN_00437920 @ 00437920 size=69 callers=1

undefined1 * __thiscall FUN_00437920(void *this,undefined1 *param_1)

{
  uint *puVar1;
  uint *puVar2;
  
  if (*(char *)((int)this + 8) == '\0') {
    puVar2 = (uint *)0x0;
    puVar1 = (uint *)0x0;
  }
  else {
    puVar2 = *(uint **)this;
    puVar1 = *(uint **)((int)this + 4);
  }
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  if (puVar2 != puVar1) {
    FUN_0043ace0(param_1,puVar2,(int)puVar1 - (int)puVar2);
  }
  return param_1;
}



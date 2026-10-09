// FUN_0043a100 @ 0043a100 size=82 callers=3

void __thiscall FUN_0043a100(void *this,int param_1,uint param_2,undefined2 param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (param_2 == 1) {
    if (7 < *(uint *)((int)this + 0x14)) {
      this = *(void **)this;
    }
    *(undefined2 *)((int)this + param_1 * 2) = param_3;
    return;
  }
  if (7 < *(uint *)((int)this + 0x14)) {
    this = *(void **)this;
  }
  if (param_2 != 0) {
    puVar2 = (undefined4 *)((int)this + param_1 * 2);
    for (uVar1 = param_2 >> 1; uVar1 != 0; uVar1 = uVar1 - 1) {
      *puVar2 = CONCAT22(param_3,param_3);
      puVar2 = puVar2 + 1;
    }
    for (uVar1 = (uint)((param_2 & 1) != 0); uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined2 *)puVar2 = param_3;
      puVar2 = (undefined4 *)((int)puVar2 + 2);
    }
  }
  return;
}



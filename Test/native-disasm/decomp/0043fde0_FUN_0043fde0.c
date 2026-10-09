// FUN_0043fde0 @ 0043fde0 size=86 callers=10

void * FUN_0043fde0(uint param_1)

{
  uint uVar1;
  void *pvVar2;
  void *pvVar3;
  
  if (param_1 == 0) {
    return (void *)0x0;
  }
  if (0xfffffff < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458e6a();
  }
  uVar1 = param_1 * 0x10;
  if (uVar1 < 0x1000) {
    pvVar2 = operator_new(uVar1);
    return pvVar2;
  }
  if (uVar1 < uVar1 + 0x23) {
    pvVar2 = operator_new(uVar1 + 0x23);
    pvVar3 = (void *)((int)pvVar2 + 0x23U & 0xffffffe0);
    *(void **)((int)pvVar3 + -4) = pvVar2;
    return pvVar3;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458e6a();
}



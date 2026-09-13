// FUN_0043f9c0 @ 0043f9c0 size=89 callers=2

void * FUN_0043f9c0(uint param_1)

{
  uint uVar1;
  void *pvVar2;
  void *pvVar3;
  
  if (param_1 == 0) {
    return (void *)0x0;
  }
  if (0xccccccc < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458e6a();
  }
  uVar1 = param_1 * 0x14;
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



// FUN_0043d730 @ 0043d730 size=71 callers=6

void * FUN_0043d730(uint param_1)

{
  void *pvVar1;
  void *pvVar2;
  
  if (param_1 == 0) {
    return (void *)0x0;
  }
  if (0xfff < param_1) {
    if (param_1 < param_1 + 0x23) {
      pvVar1 = operator_new(param_1 + 0x23);
      pvVar2 = (void *)((int)pvVar1 + 0x23U & 0xffffffe0);
      *(void **)((int)pvVar2 + -4) = pvVar1;
      return pvVar2;
    }
                    /* WARNING: Subroutine does not return */
    FUN_00458e6a();
  }
  pvVar1 = operator_new(param_1);
  return pvVar1;
}



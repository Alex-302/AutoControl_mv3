// FUN_0043fc70 @ 0043fc70 size=41 callers=1

void FUN_0043fc70(void)

{
  void *pvVar1;
  
  pvVar1 = operator_new(0x28);
  if (pvVar1 != (void *)0x0) {
    *(void **)pvVar1 = pvVar1;
  }
  if ((undefined4 *)((int)pvVar1 + 4) != (undefined4 *)0x0) {
    *(undefined4 *)((int)pvVar1 + 4) = pvVar1;
  }
  if ((undefined4 *)((int)pvVar1 + 8) != (undefined4 *)0x0) {
    *(undefined4 *)((int)pvVar1 + 8) = pvVar1;
  }
  *(undefined2 *)((int)pvVar1 + 0xc) = 0x101;
  return;
}



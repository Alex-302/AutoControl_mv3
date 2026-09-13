// FUN_00452d40 @ 00452d40 size=95 callers=1

undefined4 * __thiscall FUN_00452d40(void *this,uint *param_1)

{
  undefined4 *this_00;
  undefined4 *puVar1;
  
  puVar1 = FUN_004535d0(this);
  this_00 = puVar1 + 4;
  *(undefined2 *)(puVar1 + 3) = 0;
  if (this_00 != (undefined4 *)0x0) {
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[9] = 0xf;
    puVar1[8] = 0;
    if (0xf < (uint)puVar1[9]) {
      *(undefined1 *)*this_00 = 0;
      FUN_0043b1c0(this_00,param_1);
      return puVar1;
    }
    *(undefined1 *)this_00 = 0;
    FUN_0043b1c0(this_00,param_1);
  }
  return puVar1;
}



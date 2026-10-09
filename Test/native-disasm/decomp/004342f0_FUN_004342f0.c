// FUN_004342f0 @ 004342f0 size=101 callers=14

undefined4 * __thiscall
FUN_004342f0(void *this,undefined4 *param_1,undefined4 *param_2,uint *param_3)

{
  uint uVar1;
  uint *puVar2;
  uint in_stack_ffffffd0;
  void *pvVar3;
  
  pvVar3 = (void *)(in_stack_ffffffd0 & 0xffffff00);
  if ((char)*param_3 == '\0') {
    uVar1 = 0;
  }
  else {
    puVar2 = param_3;
    do {
      uVar1 = *puVar2;
      puVar2 = (uint *)((int)puVar2 + 1);
    } while ((char)uVar1 != '\0');
    uVar1 = (int)puVar2 - ((int)param_3 + 1);
  }
  FUN_0043ace0(&stack0xffffffd0,param_3,uVar1);
  FUN_00442830(this,param_1,param_2,pvVar3);
  return param_1;
}



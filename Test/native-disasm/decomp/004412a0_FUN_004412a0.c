// FUN_004412a0 @ 004412a0 size=92 callers=12

undefined1 * __fastcall FUN_004412a0(undefined1 *param_1,uint *param_2,uint *param_3)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  undefined8 uVar4;
  
  if ((char)*param_3 == '\0') {
    uVar2 = 0;
    puVar1 = param_2;
  }
  else {
    puVar1 = (uint *)((int)param_3 + 1);
    puVar3 = param_3;
    do {
      uVar2 = *puVar3;
      puVar3 = (uint *)((int)puVar3 + 1);
    } while ((char)uVar2 != '\0');
    uVar2 = (int)puVar3 - (int)puVar1;
  }
  uVar4 = FUN_0043af90(param_2,puVar1,param_3,uVar2);
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  FUN_0043b1c0(param_1,(uint *)uVar4);
  return param_1;
}



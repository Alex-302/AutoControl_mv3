// FUN_00441ee0 @ 00441ee0 size=108 callers=5

undefined2 * __fastcall FUN_00441ee0(undefined2 *param_1,uint *param_2,uint *param_3)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  undefined8 uVar4;
  
  if ((short)*param_3 == 0) {
    uVar1 = 0;
    puVar3 = param_2;
  }
  else {
    puVar3 = (uint *)((int)param_3 + 2);
    puVar2 = param_3;
    do {
      uVar1 = *puVar2;
      puVar2 = (uint *)((int)puVar2 + 2);
    } while ((short)uVar1 != 0);
    uVar1 = (int)puVar2 - (int)puVar3 >> 1;
  }
  uVar4 = FUN_0043dbe0(param_2,puVar3,param_3,uVar1);
  *(undefined4 *)(param_1 + 10) = 7;
  *(undefined4 *)(param_1 + 8) = 0;
  *param_1 = 0;
  FUN_0043a920(param_1,(uint *)uVar4);
  return param_1;
}



// FUN_00435130 @ 00435130 size=61 callers=1

undefined8 __thiscall FUN_00435130(void *this,uint *param_1)

{
  uint uVar1;
  uint *puVar2;
  undefined8 uVar3;
  
  if ((short)*param_1 == 0) {
    uVar3 = FUN_0043dbe0(this,param_1,param_1,0);
    return uVar3;
  }
  puVar2 = param_1;
  do {
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 2);
  } while ((short)uVar1 != 0);
  uVar3 = FUN_0043dbe0(this,param_1,param_1,(int)puVar2 - ((int)param_1 + 2) >> 1);
  return uVar3;
}



// FUN_00444450 @ 00444450 size=53 callers=8

undefined8 __thiscall FUN_00444450(void *this,uint *param_1)

{
  uint uVar1;
  uint *puVar2;
  undefined8 uVar3;
  
  if ((char)*param_1 == '\0') {
    uVar3 = FUN_0043af90(this,(uint *)0x0,param_1,0);
    return uVar3;
  }
  puVar2 = param_1;
  do {
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
  puVar2 = (uint *)((int)puVar2 - ((int)param_1 + 1));
  uVar3 = FUN_0043af90(this,puVar2,param_1,(uint)puVar2);
  return uVar3;
}



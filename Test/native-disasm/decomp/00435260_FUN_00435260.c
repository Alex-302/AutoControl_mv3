// FUN_00435260 @ 00435260 size=85 callers=3

void * __thiscall FUN_00435260(void *this,uint *param_1)

{
  uint uVar1;
  uint *puVar2;
  
  *(undefined4 *)((int)this + 0x14) = 7;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined2 *)this = 0;
  if ((short)*param_1 == 0) {
    FUN_0043a650(this,param_1,0);
    return this;
  }
  puVar2 = param_1;
  do {
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 2);
  } while ((short)uVar1 != 0);
  FUN_0043a650(this,param_1,(int)puVar2 - ((int)param_1 + 2) >> 1);
  return this;
}



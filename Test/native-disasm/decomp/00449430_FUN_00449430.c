// FUN_00449430 @ 00449430 size=125 callers=1

void * __thiscall FUN_00449430(void *this,undefined4 param_1,uint param_2)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(0x24);
  puVar1[1] = 0x14;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  *puVar1 = &PTR_LAB_0048eb3c;
  puVar1[6] = 0;
  puVar1[7] = 0;
  puVar1[8] = 0;
  *(undefined4 **)this = puVar1;
  *(undefined4 **)((int)this + 4) = puVar1;
  *(undefined4 *)((int)this + 0xc) = param_1;
  *(uint *)((int)this + 8) = param_2;
  *(uint *)((int)this + 0x10) = ~(param_2 >> 3) & 0x100;
  *(uint *)((int)this + 0x14) = ~(param_2 >> 9) & 4;
  return this;
}



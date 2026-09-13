// FUN_00403470 @ 00403470 size=71 callers=1

void * __thiscall FUN_00403470(void *this,byte param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  *(undefined ***)this = &PTR_FUN_0048e43c;
  puVar2 = *(undefined4 **)((int)this + 0x14);
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)puVar2[3];
    puVar2[3] = 0;
    (**(code **)*puVar2)(1);
    puVar2 = puVar1;
  }
  *(undefined ***)this = &PTR_LAB_0048ecb0;
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4(this);
  }
  return this;
}



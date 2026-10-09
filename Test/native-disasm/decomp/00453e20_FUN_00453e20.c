// FUN_00453e20 @ 00453e20 size=44 callers=2

void __thiscall FUN_00453e20(void *this,char param_1)

{
  undefined4 *puVar1;
  
  puVar1 = FUN_00455860((void *)((int)this + 0x24),param_1);
  FUN_00449310(this);
  FUN_004494b0((void *)((int)this + 0x24),(int)puVar1);
  *(undefined4 **)((int)this + 0x28) = puVar1;
  return;
}



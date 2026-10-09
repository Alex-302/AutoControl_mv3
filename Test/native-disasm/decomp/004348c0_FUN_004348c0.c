// FUN_004348c0 @ 004348c0 size=58 callers=28

void * __thiscall
FUN_004348c0(void *this,char param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  cVar1 = *(char *)this;
  *(char *)this = param_1;
  uVar2 = *(undefined4 *)((int)this + 0xc);
  uVar3 = *(undefined4 *)((int)this + 8);
  *(undefined4 *)((int)this + 8) = param_3;
  *(undefined4 *)((int)this + 0xc) = param_4;
  param_1 = cVar1;
  param_3 = uVar3;
  param_4 = uVar2;
  FUN_00434820(&param_1);
  return this;
}



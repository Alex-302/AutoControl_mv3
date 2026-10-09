// FUN_004355e0 @ 004355e0 size=77 callers=60

void * __thiscall FUN_004355e0(void *this,uint *param_1)

{
  uint uVar1;
  uint *puVar2;
  
  *(undefined4 *)((int)this + 0x14) = 0xf;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined1 *)this = 0;
  if ((char)*param_1 == '\0') {
    FUN_0043ace0(this,param_1,0);
    return this;
  }
  puVar2 = param_1;
  do {
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
  FUN_0043ace0(this,param_1,(int)puVar2 - ((int)param_1 + 1));
  return this;
}



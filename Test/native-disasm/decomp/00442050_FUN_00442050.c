// FUN_00442050 @ 00442050 size=101 callers=5

void * __thiscall FUN_00442050(void *this,int *param_1)

{
  char cVar1;
  undefined8 uVar2;
  char local_10 [8];
  undefined8 local_8;
  
  local_10[0] = '\0';
  local_8 = 0;
  *(undefined1 *)this = 0;
  *(undefined8 *)((int)this + 8) = 0;
  FUN_00450f50(local_10,*param_1);
  cVar1 = *(char *)this;
  *(char *)this = local_10[0];
  uVar2 = *(undefined8 *)((int)this + 8);
  *(undefined4 *)((int)this + 8) = (undefined4)local_8;
  *(undefined4 *)((int)this + 0xc) = local_8._4_4_;
  local_10[0] = cVar1;
  local_8 = uVar2;
  FUN_00434820(local_10);
  return this;
}



// FUN_00434b00 @ 00434b00 size=80 callers=6

void * __thiscall FUN_00434b00(void *this,char *param_1,char *param_2)

{
  undefined4 *puVar1;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  
  local_c = 0;
  *(undefined1 *)this = 0;
  local_14 = param_1;
  local_10 = param_2;
  *(undefined8 *)((int)this + 8) = 0;
  FUN_004476b0(param_1,param_2);
  *(undefined1 *)this = 2;
  puVar1 = FUN_004429e0((int *)&local_14);
  *(undefined4 **)((int)this + 8) = puVar1;
  return this;
}



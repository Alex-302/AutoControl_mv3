// FUN_00444080 @ 00444080 size=219 callers=2

void * __thiscall FUN_00444080(void *this,char *param_1)

{
  char *pcVar1;
  undefined4 uVar2;
  char *pcVar3;
  int *in_stack_0000002c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e290;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 0x2c) = 0;
  local_8 = 1;
  if (in_stack_0000002c != (int *)0x0) {
    uVar2 = (**(code **)*in_stack_0000002c)((int)this + 8);
    *(undefined4 *)((int)this + 0x2c) = uVar2;
  }
  *(undefined4 *)((int)this + 0x30) = 0;
  pcVar1 = param_1;
  do {
    pcVar3 = pcVar1;
    pcVar1 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  *(undefined4 *)((int)this + 0x34) = 0;
  *(undefined4 *)((int)this + 0x4c) = 0xf;
  *(undefined4 *)((int)this + 0x48) = 0;
  *(undefined1 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 100) = 0xf;
  *(undefined4 *)((int)this + 0x60) = 0;
  *(undefined1 *)((int)this + 0x50) = 0;
  *(char **)((int)this + 0x68) = param_1;
  *(undefined4 *)((int)this + 0x70) = 0;
  *(undefined4 *)((int)this + 0x7c) = 0xf;
  *(char **)((int)this + 0x74) = param_1;
  *(char **)((int)this + 0x6c) = param_1;
  *(char **)((int)this + 0x78) = pcVar3;
  if (in_stack_0000002c != (int *)0x0) {
    (**(code **)(*in_stack_0000002c + 0x10))(in_stack_0000002c != (int *)&stack0x00000008);
  }
  ExceptionList = local_10;
  return this;
}



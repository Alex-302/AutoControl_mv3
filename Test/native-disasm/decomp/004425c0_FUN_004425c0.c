// FUN_004425c0 @ 004425c0 size=61 callers=1

void * __thiscall FUN_004425c0(void *this,void *param_1)

{
  uint in_stack_00000018;
  
  *(undefined4 *)((int)this + 0x14) = 7;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined2 *)this = 0;
  FUN_0043a920(this,(uint *)&param_1);
  if (7 < in_stack_00000018) {
    FUN_00402430(param_1,in_stack_00000018 + 1,2);
  }
  return this;
}



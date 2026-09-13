// FUN_004341b0 @ 004341b0 size=87 callers=5

int __thiscall FUN_004341b0(void *this,void *param_1)

{
  int iVar1;
  uint in_stack_00000018;
  int *local_8;
  int *local_4;
  
  if (*(char *)this == '\x01') {
    FUN_004437f0(*(void **)((int)this + 8),(int *)&local_8,(byte *)&param_1);
    iVar1 = FUN_00447a70(local_8,local_4);
  }
  else {
    iVar1 = 0;
  }
  if (0xf < in_stack_00000018) {
    FUN_00402430(param_1,in_stack_00000018 + 1,1);
  }
  return iVar1;
}



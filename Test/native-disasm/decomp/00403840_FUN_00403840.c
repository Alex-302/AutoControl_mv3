// FUN_00403840 @ 00403840 size=168 callers=1

void * __thiscall FUN_00403840(void *this,char *param_1)

{
  int iVar1;
  int iVar2;
  char **ppcVar3;
  int iVar4;
  int in_stack_00000014;
  uint in_stack_00000018;
  
  ppcVar3 = &param_1;
  if (0xf < in_stack_00000018) {
    ppcVar3 = (char **)param_1;
  }
  iVar2 = (in_stack_00000014 + (int)ppcVar3) - (int)ppcVar3;
  iVar4 = 0;
  if ((char **)(in_stack_00000014 + (int)ppcVar3) < ppcVar3) {
    iVar2 = 0;
  }
  if (iVar2 != 0) {
    do {
      iVar1 = _toupper((int)*(char *)ppcVar3);
      iVar4 = iVar4 + 1;
      *(char *)ppcVar3 = (char)iVar1;
      ppcVar3 = (char **)((int)ppcVar3 + 1);
    } while (iVar4 != iVar2);
  }
  *(undefined4 *)((int)this + 0x14) = 0xf;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined1 *)this = 0;
  if (in_stack_00000018 < 0x10) {
    if (in_stack_00000014 + 1U != 0) {
      FUN_0045b0e0(this,(uint *)&param_1,in_stack_00000014 + 1U);
      *(int *)((int)this + 0x10) = in_stack_00000014;
      *(uint *)((int)this + 0x14) = in_stack_00000018;
      return this;
    }
  }
  else {
    *(char **)this = param_1;
  }
  *(int *)((int)this + 0x10) = in_stack_00000014;
  *(uint *)((int)this + 0x14) = in_stack_00000018;
  return this;
}



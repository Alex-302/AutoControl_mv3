// FUN_004038f0 @ 004038f0 size=185 callers=1

void * __thiscall FUN_004038f0(void *this,wint_t *param_1)

{
  wint_t wVar1;
  wint_t **ppwVar2;
  uint uVar3;
  wint_t **ppwVar4;
  uint uVar5;
  int in_stack_00000014;
  uint in_stack_00000018;
  
  ppwVar2 = &param_1;
  if (7 < in_stack_00000018) {
    ppwVar2 = (wint_t **)param_1;
  }
  ppwVar2 = (wint_t **)((int)ppwVar2 + in_stack_00000014 * 2);
  ppwVar4 = &param_1;
  if (7 < in_stack_00000018) {
    ppwVar4 = (wint_t **)param_1;
  }
  uVar3 = (uint)((int)ppwVar2 + (1 - (int)ppwVar4)) >> 1;
  uVar5 = 0;
  if (ppwVar2 < ppwVar4) {
    uVar3 = 0;
  }
  if (uVar3 != 0) {
    do {
      wVar1 = _towupper(*(wint_t *)ppwVar4);
      uVar5 = uVar5 + 1;
      *(wint_t *)ppwVar4 = wVar1;
      ppwVar4 = (wint_t **)((int)ppwVar4 + 2);
    } while (uVar5 != uVar3);
  }
  *(undefined4 *)((int)this + 0x14) = 7;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined2 *)this = 0;
  if (in_stack_00000018 < 8) {
    if (in_stack_00000014 + 1 != 0) {
      FUN_0045b0e0(this,(uint *)&param_1,(in_stack_00000014 + 1) * 2);
      *(int *)((int)this + 0x10) = in_stack_00000014;
      *(uint *)((int)this + 0x14) = in_stack_00000018;
      return this;
    }
  }
  else {
    *(wint_t **)this = param_1;
  }
  *(int *)((int)this + 0x10) = in_stack_00000014;
  *(uint *)((int)this + 0x14) = in_stack_00000018;
  return this;
}



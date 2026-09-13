// FUN_004039b0 @ 004039b0 size=185 callers=1

void * __thiscall FUN_004039b0(void *this,ushort *param_1)

{
  int iVar1;
  ushort **ppuVar2;
  uint uVar3;
  ushort **ppuVar4;
  uint uVar5;
  int in_stack_00000014;
  uint in_stack_00000018;
  
  ppuVar2 = &param_1;
  if (7 < in_stack_00000018) {
    ppuVar2 = (ushort **)param_1;
  }
  ppuVar2 = (ushort **)((int)ppuVar2 + in_stack_00000014 * 2);
  ppuVar4 = &param_1;
  if (7 < in_stack_00000018) {
    ppuVar4 = (ushort **)param_1;
  }
  uVar3 = (uint)((int)ppuVar2 + (1 - (int)ppuVar4)) >> 1;
  uVar5 = 0;
  if (ppuVar2 < ppuVar4) {
    uVar3 = 0;
  }
  if (uVar3 != 0) {
    do {
      iVar1 = _tolower((uint)*(ushort *)ppuVar4);
      uVar5 = uVar5 + 1;
      *(ushort *)ppuVar4 = (ushort)iVar1;
      ppuVar4 = (ushort **)((int)ppuVar4 + 2);
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
    *(ushort **)this = param_1;
  }
  *(int *)((int)this + 0x10) = in_stack_00000014;
  *(uint *)((int)this + 0x14) = in_stack_00000018;
  return this;
}



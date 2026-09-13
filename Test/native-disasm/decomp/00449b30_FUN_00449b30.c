// FUN_00449b30 @ 00449b30 size=320 callers=3

undefined4 __thiscall FUN_00449b30(void *this,undefined4 *param_1)

{
  undefined4 uVar1;
  uint *extraout_EDX;
  uint uVar2;
  int *this_00;
  int iVar3;
  
  if (param_1 != (undefined4 *)0x0) {
    *(undefined1 *)(param_1 + 1) = 1;
    FUN_0044d9f0(param_1 + 2,0);
  }
  *(undefined4 *)((int)this + 0x4c) = *(undefined4 *)((int)this + 0x54);
  *(undefined4 *)this = *(undefined4 *)((int)this + 0x54);
  FUN_0044d710((void *)((int)this + 4),*(uint *)((int)this + 0x68));
  FUN_0044d610((void *)((int)this + 0x14),*(uint *)((int)this + 0x68));
  *(undefined1 *)((int)this + 0x74) = 0;
  *(undefined4 *)((int)this + 0x78) = 10000000;
  *(undefined4 *)((int)this + 0x7c) = 1000;
  *(bool *)((int)this + 0x65) = param_1 != (undefined4 *)0x0;
  *(undefined1 *)((int)this + 100) = 0;
  uVar1 = FUN_0044e410(this,extraout_EDX,*(uint **)((int)this + 0x58));
  if ((char)uVar1 != '\0') {
    if (param_1 != (undefined4 *)0x0) {
      this_00 = param_1 + 2;
      FUN_0044d9f0(this_00,*(uint *)((int)this + 0x68));
      uVar2 = 0;
      if (*(int *)((int)this + 0x68) != 0) {
        iVar3 = 0;
        do {
          if ((*(uint *)(*(int *)((int)this + 0x24) + (uVar2 >> 5) * 4) & 1 << ((byte)uVar2 & 0x1f))
              == 0) {
            *(undefined1 *)(iVar3 + 8 + *this_00) = 0;
            *(undefined4 *)(iVar3 + *this_00) = *(undefined4 *)((int)this + 0x50);
            uVar1 = *(undefined4 *)((int)this + 0x50);
          }
          else {
            *(undefined1 *)(iVar3 + 8 + *this_00) = 1;
            *(undefined4 *)(iVar3 + *this_00) =
                 *(undefined4 *)(*(int *)((int)this + 0x34) + uVar2 * 8);
            uVar1 = *(undefined4 *)(*(int *)((int)this + 0x34) + 4 + uVar2 * 8);
          }
          uVar2 = uVar2 + 1;
          *(undefined4 *)(iVar3 + 4 + *this_00) = uVar1;
          iVar3 = iVar3 + 0xc;
        } while (uVar2 < *(uint *)((int)this + 0x68));
      }
      *param_1 = *(undefined4 *)((int)this + 0x4c);
      param_1[5] = *(undefined4 *)((int)this + 0x4c);
      iVar3 = *(int *)*this_00;
      param_1[6] = iVar3;
      *(bool *)(param_1 + 7) = param_1[5] != iVar3;
      param_1[8] = *(undefined4 *)(*this_00 + 4);
      iVar3 = *(int *)((int)this + 0x50);
      param_1[9] = iVar3;
      *(bool *)(param_1 + 10) = param_1[8] != iVar3;
      param_1[0xb] = *(undefined4 *)((int)this + 0x50);
      uVar1 = *(undefined4 *)((int)this + 0x50);
      param_1[0xc] = uVar1;
    }
    return CONCAT31((int3)((uint)uVar1 >> 8),1);
  }
  return uVar1;
}



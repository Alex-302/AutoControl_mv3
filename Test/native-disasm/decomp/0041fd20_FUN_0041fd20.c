// FUN_0041fd20 @ 0041fd20 size=202 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0041fd20(void *this,byte param_1)

{
  void *pvVar1;
  short sVar2;
  undefined4 uVar3;
  void *pvVar4;
  void *pvVar5;
  tagPOINT local_8;
  
  *(undefined1 *)((int)this + 0x45) = 0x4e;
  pvVar1 = *(void **)((int)this + 0x20);
  pvVar4 = _memchr(*(void **)((int)this + 0x1c),(uint)param_1,
                   (int)pvVar1 - (int)*(void **)((int)this + 0x1c));
  pvVar5 = pvVar1;
  if (pvVar4 != (void *)0x0) {
    pvVar5 = pvVar4;
  }
  if (pvVar5 == pvVar1) {
    FUN_00434cd0((void *)((int)this + 0x1c),&param_1);
  }
  sVar2 = DAT_004a26b0;
  *(short *)((int)this + 0x34) = DAT_004a26b0;
  *(int *)((int)this + 0x30) = DAT_004a26b4;
  uVar3 = DAT_004a2a4c;
  if (((ushort)(sVar2 - 1U) < 6) && (sVar2 != 3)) {
    if (200 < (uint)(DAT_004a26b4 - _DAT_004a32e8)) {
      GetCursorPos(&local_8);
      DAT_004a2a48 = local_8.x;
      DAT_004a2a4c = local_8.y;
      _DAT_004a32e8 = DAT_004a26b4;
      *(LONG *)((int)this + 0x28) = local_8.x;
      *(LONG *)((int)this + 0x2c) = local_8.y;
      return;
    }
    *(LONG *)((int)this + 0x28) = DAT_004a2a48;
    *(undefined4 *)((int)this + 0x2c) = uVar3;
  }
  return;
}



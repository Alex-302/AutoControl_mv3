// FUN_00416c70 @ 00416c70 size=73 callers=1

undefined4 __thiscall FUN_00416c70(void *this,int *param_1,char param_2)

{
  uint in_EAX;
  HANDLE pvVar1;
  
  if ((*param_1 != 0) && (param_1[1] != 0)) {
    if (param_2 == '\0') {
      EmptyClipboard();
    }
    if (this == (void *)0x5b) {
      this = DAT_004a26f4;
    }
    pvVar1 = SetClipboardData((UINT)this,(HANDLE)*param_1);
    in_EAX = 0;
    if (pvVar1 != (HANDLE)0x0) {
      return CONCAT31((int3)((uint)pvVar1 >> 8),1);
    }
  }
  *(undefined1 *)(param_1 + 2) = 1;
  return in_EAX & 0xffffff00;
}



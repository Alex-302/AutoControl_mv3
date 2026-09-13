// FUN_00415660 @ 00415660 size=130 callers=4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __thiscall FUN_00415660(void *this,char param_1)

{
  int *piVar1;
  uint uVar2;
  undefined4 local_10;
  undefined4 uStack_c;
  int iStack_8;
  undefined4 uStack_4;
  
  uVar2 = 0;
  while( true ) {
    if ((uVar2 != 0) && (this = (void *)FUN_00414ec0(this), this == (int *)0x0)) {
      return (int *)&DAT_004a26f8;
    }
    if (*(int *)((int)this + 0x2c) == 0) {
      piVar1 = *(int **)this;
      local_10 = 0;
      uStack_c = 0;
      iStack_8 = 0;
      uStack_4 = 0;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 0x34))
                  (piVar1,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_10);
      }
      *(int *)((int)this + 0x2c) = iStack_8;
    }
    if ((*(int *)((int)this + 0x2c) == 0x2b) ||
       ((param_1 != '\0' && (*(int *)((int)this + 0x2c) == 0x39)))) break;
    uVar2 = uVar2 + 1;
    if (1 < uVar2) {
      return (int *)&DAT_004a26f8;
    }
  }
  return this;
}



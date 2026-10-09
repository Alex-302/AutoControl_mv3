// FUN_00456900 @ 00456900 size=150 callers=2

ushort __thiscall FUN_00456900(void *this,byte *param_1,byte *param_2,char param_3)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined **ppuVar4;
  int iVar5;
  void *local_4;
  
  iVar5 = 0;
  if (PTR_s_alnum_0048eda0 != (undefined *)0x0) {
    iVar2 = 0;
    ppuVar4 = &PTR_s_alnum_0048eda0;
    local_4 = this;
    do {
      if (((int)param_2 - (int)param_1 == *(int *)((int)&DAT_0048eda8 + iVar2)) &&
         (uVar3 = FUN_00457a70(param_1,param_2,(int)*ppuVar4,(int *)&local_4), (char)uVar3 != '\0'))
      break;
      iVar5 = iVar5 + 1;
      iVar2 = iVar5 * 0x10;
      ppuVar4 = &PTR_s_alnum_0048eda0 + iVar5 * 4;
    } while ((&PTR_s_alnum_0048eda0)[iVar5 * 4] != (undefined *)0x0);
  }
  uVar1 = 0;
  if ((&PTR_s_alnum_0048eda0)[iVar5 * 4] != (undefined *)0x0) {
    uVar1 = (&DAT_0048edac)[iVar5 * 8];
  }
  if ((param_3 != '\0') && ((uVar1 & 3) != 0)) {
    uVar1 = uVar1 | 3;
  }
  return uVar1;
}



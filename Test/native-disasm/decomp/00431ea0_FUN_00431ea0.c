// FUN_00431ea0 @ 00431ea0 size=110 callers=1

void FUN_00431ea0(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((param_1 < DAT_004a250c) && (DAT_004a2508 <= param_1)) {
    iVar2 = (int)param_1 - (int)DAT_004a2508;
    if (DAT_004a250c == DAT_004a2510) {
      FUN_00435a90();
    }
    if (DAT_004a250c == (undefined4 *)0x0) goto LAB_00431f01;
    uVar1 = DAT_004a2508[iVar2 >> 2];
  }
  else {
    if (DAT_004a250c == DAT_004a2510) {
      FUN_00435a90();
    }
    if (DAT_004a250c == (undefined4 *)0x0) goto LAB_00431f01;
    uVar1 = *param_1;
  }
  *DAT_004a250c = uVar1;
LAB_00431f01:
  DAT_004a250c = DAT_004a250c + 1;
  return;
}



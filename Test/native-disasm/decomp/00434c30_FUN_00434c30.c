// FUN_00434c30 @ 00434c30 size=158 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00434c30(uint *param_1)

{
  uint *this;
  int iVar1;
  
  if ((param_1 < DAT_004a2554) && (_DAT_004a2550 <= param_1)) {
    iVar1 = (int)param_1 - (int)_DAT_004a2550;
    if (DAT_004a2554 == _DAT_004a2558) {
      FUN_00439f00();
    }
    if (DAT_004a2554 == (uint *)0x0) goto LAB_00434cc0;
    param_1 = _DAT_004a2550 + (iVar1 / 0x18) * 6;
  }
  else {
    if (DAT_004a2554 == _DAT_004a2558) {
      FUN_00439f00();
    }
    if (DAT_004a2554 == (uint *)0x0) goto LAB_00434cc0;
  }
  this = DAT_004a2554;
  DAT_004a2554[4] = 0;
  this[5] = 0xf;
  this[4] = 0;
  *(undefined1 *)this = 0;
  FUN_0043b1c0(this,param_1);
LAB_00434cc0:
  DAT_004a2554 = DAT_004a2554 + 6;
  return;
}



// FUN_00432210 @ 00432210 size=59 callers=2

void FUN_00432210(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = DAT_004a25ac;
  piVar2 = DAT_004a25a8;
  if (DAT_004a25a8 != DAT_004a25ac) {
    do {
      if ((undefined4 *)*piVar2 != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)*piVar2)(1);
      }
      piVar2 = piVar2 + 1;
    } while (piVar2 != piVar1);
    DAT_004a25ac = DAT_004a25a8;
    return;
  }
  DAT_004a25ac = DAT_004a25a8;
  return;
}



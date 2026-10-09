// FUN_0041ef30 @ 0041ef30 size=95 callers=1

void FUN_0041ef30(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = DAT_004a2508;
  do {
    if (piVar1 == DAT_004a250c) {
LAB_0041ef5b:
      DAT_004a2436 = 0;
      DeleteMenu(DAT_004a2528,0xfffffffd,0);
      return;
    }
    if ((HMENU)*piVar1 == DAT_004a2528) {
      if (((piVar1 != DAT_004a250c) && (iVar2 = (int)piVar1 - (int)DAT_004a2508 >> 2, -1 < iVar2))
         && (iVar2 < ((int)DAT_004a250c - (int)DAT_004a2508 >> 2) + -1)) {
        DAT_004a2436 = 1;
        return;
      }
      goto LAB_0041ef5b;
    }
    piVar1 = piVar1 + 1;
  } while( true );
}



// FUN_0041eb70 @ 0041eb70 size=123 callers=1

uint __fastcall FUN_0041eb70(char param_1)

{
  int *piVar1;
  uint uVar2;
  BOOL BVar3;
  int iVar4;
  
  piVar1 = DAT_004a2508;
  if ((param_1 == '\0') &&
     (uVar2 = FUN_0041d600(DAT_004a2528,DAT_004a2520), piVar1 = DAT_004a2508, (char)uVar2 == '\0'))
  {
    return uVar2;
  }
  do {
    if (piVar1 == DAT_004a250c) {
LAB_0041ebaf:
      DAT_004a2436 = 0;
      BVar3 = DeleteMenu(DAT_004a2528,0xfffffffd,0);
      return (uint)(BVar3 != 0);
    }
    if ((HMENU)*piVar1 == DAT_004a2528) {
      if (piVar1 != DAT_004a250c) {
        iVar4 = (int)piVar1 - (int)DAT_004a2508 >> 2;
        if ((-1 < iVar4) && (iVar4 < ((int)DAT_004a250c - (int)DAT_004a2508 >> 2) + -1)) {
          DAT_004a2436 = 1;
          return CONCAT31((int3)((int)piVar1 - (int)DAT_004a2508 >> 10),1);
        }
      }
      goto LAB_0041ebaf;
    }
    piVar1 = piVar1 + 1;
  } while( true );
}



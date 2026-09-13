// FUN_00454be0 @ 00454be0 size=184 callers=4

void FUN_00454be0(void)

{
  uint uVar1;
  int *piVar2;
  undefined1 uVar3;
  undefined1 *unaff_EBX;
  int unaff_EBP;
  int *unaff_ESI;
  
code_r0x00454be0:
  do {
    while( true ) {
      if (unaff_EBX == *(undefined1 **)(unaff_EBP + 0xc)) {
        ExceptionList = *(void **)(unaff_EBP + -0xc);
        return;
      }
      uVar1 = unaff_ESI[4];
      uVar3 = *unaff_EBX;
      *(undefined1 *)(unaff_EBP + 0xb) = uVar3;
      if (~uVar1 < 2) {
                    /* WARNING: Subroutine does not return */
        FUN_00458ec4("string too long");
      }
      uVar1 = uVar1 + 1;
      if (uVar1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
        FUN_00458ec4("string too long");
      }
      if (uVar1 <= (uint)unaff_ESI[5]) break;
      FUN_0043f5f0(unaff_ESI,uVar1);
      uVar3 = *(undefined1 *)(unaff_EBP + 0xb);
      if (uVar1 != 0) goto LAB_00454c2f;
LAB_00454cba:
      unaff_EBX = unaff_EBX + 1;
    }
    if (uVar1 == 0) {
      unaff_ESI[4] = 0;
      if ((uint)unaff_ESI[5] < 0x10) {
        unaff_EBX = unaff_EBX + 1;
        *(undefined1 *)unaff_ESI = 0;
      }
      else {
        unaff_EBX = unaff_EBX + 1;
        *(undefined1 *)*unaff_ESI = 0;
      }
      goto code_r0x00454be0;
    }
LAB_00454c2f:
    piVar2 = unaff_ESI;
    if (0xf < (uint)unaff_ESI[5]) {
      piVar2 = (int *)*unaff_ESI;
    }
    *(undefined1 *)((int)piVar2 + unaff_ESI[4]) = uVar3;
    unaff_ESI[4] = uVar1;
    if ((uint)unaff_ESI[5] < 0x10) {
      *(undefined1 *)((int)unaff_ESI + uVar1) = 0;
      goto LAB_00454cba;
    }
    unaff_EBX = unaff_EBX + 1;
    *(undefined1 *)(*unaff_ESI + uVar1) = 0;
  } while( true );
}



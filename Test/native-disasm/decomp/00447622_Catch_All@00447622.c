// Catch_All@00447622 @ 00447622 size=49 callers=1

void Catch_All_00447622(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int unaff_EBP;
  
  iVar1 = *(int *)(unaff_EBP + -0x14);
  puVar3 = *(undefined4 **)(iVar1 + 0x24);
  while (puVar3 != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)puVar3[3];
    puVar3[3] = 0;
    (**(code **)*puVar3)(1);
    puVar3 = puVar2;
  }
  *(undefined4 *)(iVar1 + 0x24) = 0;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)0x0,(byte *)0x0);
}



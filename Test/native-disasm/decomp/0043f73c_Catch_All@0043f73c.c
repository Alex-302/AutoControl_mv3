// Catch_All@0043f73c @ 0043f73c size=59 callers=1

void Catch_All_0043f73c(void)

{
  int unaff_EBP;
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(unaff_EBP + -0x14);
  if (0xf < (uint)puVar1[5]) {
    FUN_00402430((void *)*puVar1,puVar1[5] + 1,1);
  }
  puVar1[5] = 0xf;
  puVar1[4] = 0;
  if (0xf < (uint)puVar1[5]) {
    puVar1 = (undefined4 *)*puVar1;
  }
  *(undefined1 *)puVar1 = 0;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)0x0,(byte *)0x0);
}



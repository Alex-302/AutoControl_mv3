// Catch_All@0043e173 @ 0043e173 size=42 callers=1

undefined * Catch_All_0043e173(void)

{
  int *piVar1;
  int unaff_EBP;
  
  piVar1 = *(int **)(unaff_EBP + -0x14);
  FUN_00402f00((void *)(*(int *)(*piVar1 + 4) + (int)piVar1),
               *(uint *)(*(int *)(*piVar1 + 4) + 0xc + (int)piVar1) | 4,'\x01');
  return &DAT_0043e19d;
}



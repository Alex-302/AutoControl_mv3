// Catch@00439db2 @ 00439db2 size=78 callers=1

void Catch_00439db2(void)

{
  uint *puVar1;
  undefined4 *puVar2;
  int unaff_EBP;
  
  puVar1 = (uint *)FUN_00403360((undefined1 *)(unaff_EBP + -0x4c),*(uint *)(unaff_EBP + 8));
  *(undefined1 *)(unaff_EBP + -4) = 2;
  puVar1 = (uint *)FUN_00442600((undefined1 *)(unaff_EBP + -100),(uint *)"array index ",puVar1);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  puVar2 = (undefined4 *)
           FUN_004412a0((undefined1 *)(unaff_EBP + -0x7c),puVar1,(uint *)" is out of range");
  *(undefined1 *)(unaff_EBP + -4) = 4;
  FUN_00402540((void *)(unaff_EBP + -0x34),puVar2);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)(unaff_EBP + -0x34),&DAT_00499ebc);
}



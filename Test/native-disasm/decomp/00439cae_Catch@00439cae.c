// Catch@00439cae @ 00439cae size=65 callers=1

void Catch_00439cae(void)

{
  uint *puVar1;
  undefined4 *puVar2;
  int unaff_EBP;
  
  puVar1 = FUN_00442660((uint *)(unaff_EBP + -0x4c),(uint *)"key \'",*(undefined4 **)(unaff_EBP + 8)
                       );
  *(undefined1 *)(unaff_EBP + -4) = 2;
  puVar2 = (undefined4 *)
           FUN_004412a0((undefined1 *)(unaff_EBP + -100),puVar1,(uint *)"\' not found");
  *(undefined1 *)(unaff_EBP + -4) = 3;
  FUN_00402540((void *)(unaff_EBP + -0x34),puVar2);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)(unaff_EBP + -0x34),&DAT_00499ebc);
}



// Catch_All@0043d32c @ 0043d32c size=77 callers=1

void Catch_All_0043d32c(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int unaff_EBP;
  
  iVar1 = *(int *)(unaff_EBP + -0x18);
  iVar2 = *(int *)(unaff_EBP + -0x1c);
  pcVar3 = *(char **)(unaff_EBP + -0x14);
  if (1 < iVar1) {
    FUN_0043f5c0(pcVar3,pcVar3 + iVar2 * 0x10);
  }
  if (0 < iVar1) {
    FUN_0043f5c0(pcVar3 + iVar2 * 0x10,pcVar3 + (*(int *)(unaff_EBP + 0x10) + iVar2) * 0x10);
  }
  FUN_00402430(pcVar3,*(uint *)(unaff_EBP + -0x20),0x10);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)0x0,(byte *)0x0);
}



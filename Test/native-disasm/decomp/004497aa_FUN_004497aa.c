// FUN_004497aa @ 004497aa size=109 callers=6

void FUN_004497aa(void)

{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  void *this;
  uint uVar4;
  uint unaff_EBX;
  int unaff_EBP;
  int *unaff_EDI;
  
  *(undefined4 *)(unaff_EBP + -4) = 1;
  if (*(char *)(unaff_EBP + -0x11) == '\0') {
    unaff_EBX = unaff_EBX | 2;
  }
  this = (void *)(*(int *)(*unaff_EDI + 4) + (int)unaff_EDI);
  if (unaff_EBX != 0) {
    uVar4 = *(uint *)((int)this + 0xc) | unaff_EBX;
    uVar3 = uVar4 | 4;
    if (*(int *)((int)this + 0x38) != 0) {
      uVar3 = uVar4;
    }
    FUN_00402f00(this,uVar3,'\0');
  }
  *(undefined4 *)(unaff_EBP + -4) = 4;
  piVar1 = *(int **)(*(int *)(**(int **)(unaff_EBP + -0x28) + 4) + 0x38 +
                    (int)*(int **)(unaff_EBP + -0x28));
  if ((piVar1 != (int *)0x0) && (pcVar2 = *(code **)(*piVar1 + 8), pcVar2 != guard_check_icall)) {
    (*pcVar2)();
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}



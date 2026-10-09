// FUN_0043e33a @ 0043e33a size=120 callers=2

void __fastcall FUN_0043e33a(uint param_1)

{
  int *piVar1;
  code *pcVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  int unaff_EBP;
  int *unaff_ESI;
  void *this;
  
  *(undefined4 *)(unaff_EBP + -4) = 1;
  this = (void *)(*(int *)(*unaff_ESI + 4) + (int)unaff_ESI);
  if (param_1 != 0) {
    uVar5 = *(uint *)((int)this + 0xc) | param_1;
    uVar4 = uVar5 | 4;
    if (*(int *)((int)this + 0x38) != 0) {
      uVar4 = uVar5;
    }
    FUN_00402f00(this,uVar4,'\0');
  }
  *(undefined4 *)(unaff_EBP + -4) = 4;
  bVar3 = thunk_FUN_0045c732();
  if (!bVar3) {
    FUN_00440100(unaff_ESI);
  }
  *(undefined1 *)(unaff_EBP + -4) = 5;
  piVar1 = *(int **)(*(int *)(*unaff_ESI + 4) + 0x38 + (int)unaff_ESI);
  if ((piVar1 != (int *)0x0) && (pcVar2 = *(code **)(*piVar1 + 8), pcVar2 != guard_check_icall)) {
    (*pcVar2)();
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}



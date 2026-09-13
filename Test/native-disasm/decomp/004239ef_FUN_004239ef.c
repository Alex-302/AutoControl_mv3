// FUN_004239ef @ 004239ef size=376 callers=1

int __fastcall FUN_004239ef(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *this;
  uint uVar3;
  int unaff_EBP;
  int unaff_ESI;
  undefined8 uVar4;
  char *pcVar5;
  void *in_stack_ffffffe8;
  undefined4 uVar6;
  
  FUN_004420c0((char *)(unaff_EBP + -0x38),param_2,*(int *)(unaff_ESI + 4) + param_2);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  if (*(char *)(unaff_EBP + -0x38) == '\x01') {
    FUN_004355e0(&stack0xffffffe8,(uint *)&DAT_0048d80c);
    pcVar5 = (char *)0x423a31;
    iVar2 = FUN_004341b0((void *)(unaff_EBP + -0x38),in_stack_ffffffe8);
    if (iVar2 != 0) {
      uVar6 = 0;
      this = FUN_00440e70((void *)(unaff_EBP + -0x38),(uint *)&DAT_0048d80c);
      FUN_00440bb0(this,(undefined4 *)&stack0xffffffe4);
      pcVar5 = FUN_00403840((void *)(unaff_EBP + -0x28),pcVar5);
      *(undefined1 *)(unaff_EBP + -4) = 3;
      uVar4 = FUN_004037c0(pcVar5," \t\n\r\f\v");
      uVar3 = FUN_004409d0(&DAT_004a28d0,(undefined4 *)uVar4,uVar6);
      *(uint *)(unaff_EBP + 0x10) = uVar3 & 0xffff;
      *(undefined1 *)(unaff_EBP + -4) = 2;
      FUN_004061c0((undefined4 *)(unaff_EBP + -0x28));
      if (*(short *)(unaff_EBP + 0x10) == 0) {
        FUN_00434820((char *)(unaff_EBP + -0x38));
        ExceptionList = *(void **)(unaff_EBP + -0xc);
        return -5;
      }
      FUN_004355e0((void *)(unaff_EBP + -0x28),(uint *)&DAT_0048d80c);
      *(undefined1 *)(unaff_EBP + -4) = 4;
      FUN_00434210((void *)(unaff_EBP + -0x38),(byte *)(unaff_EBP + -0x28));
      FUN_004061c0((undefined4 *)(unaff_EBP + -0x28));
      *(undefined1 *)(unaff_EBP + 0x17) = 0;
      *(int *)(unaff_EBP + -0x1c) = unaff_EBP + -0x38;
      *(int *)(unaff_EBP + -0x18) = unaff_EBP + 0x17;
      *(int *)(unaff_EBP + -0x54) = unaff_EBP + 0x10;
      *(undefined ***)(unaff_EBP + -0x60) = &PTR_LAB_0048ef20;
      *(undefined8 *)(unaff_EBP + -0x5c) = *(undefined8 *)(unaff_EBP + -0x1c);
      *(int **)(unaff_EBP + -0x3c) = (int *)(unaff_EBP + -0x60);
      *(undefined1 *)(unaff_EBP + -4) = 5;
      FUN_0040f7a0(DAT_004a2458,(int *)(unaff_EBP + -0x60));
      FUN_0040fe40((int *)(unaff_EBP + -0x60));
      cVar1 = *(char *)(unaff_EBP + 0x17);
      FUN_00434820((char *)(unaff_EBP + -0x38));
      ExceptionList = *(void **)(unaff_EBP + -0xc);
      return (cVar1 != '\0') + 1;
    }
  }
  FUN_00434820((char *)(unaff_EBP + -0x38));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return -4;
}



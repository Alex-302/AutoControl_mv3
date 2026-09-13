// FUN_0043df60 @ 0043df60 size=123 callers=2

void __fastcall FUN_0043df60(int param_1)

{
  int iVar1;
  
  if ((*(byte *)(param_1 + 0x3c) & 1) != 0) {
    if (**(int **)(param_1 + 0x20) == 0) {
      iVar1 = **(int **)(param_1 + 0x2c) + **(int **)(param_1 + 0x1c);
    }
    else {
      iVar1 = **(int **)(param_1 + 0x30) + **(int **)(param_1 + 0x20);
    }
    FUN_00402430((void *)**(undefined4 **)(param_1 + 0xc),
                 iVar1 - (int)**(undefined4 **)(param_1 + 0xc),1);
  }
  **(undefined4 **)(param_1 + 0xc) = 0;
  **(undefined4 **)(param_1 + 0x1c) = 0;
  **(undefined4 **)(param_1 + 0x2c) = 0;
  **(undefined4 **)(param_1 + 0x10) = 0;
  **(undefined4 **)(param_1 + 0x20) = 0;
  **(undefined4 **)(param_1 + 0x30) = 0;
  *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xfffffffe;
  *(undefined4 *)(param_1 + 0x38) = 0;
  return;
}



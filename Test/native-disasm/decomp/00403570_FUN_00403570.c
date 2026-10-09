// FUN_00403570 @ 00403570 size=172 callers=4

void __fastcall FUN_00403570(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  for (; (param_1 != param_2 && (param_1 != 0)); param_1 = *(int *)(param_1 + 0xc)) {
    iVar2 = param_3;
    switch(*(undefined4 *)(param_1 + 4)) {
    case 10:
    case 0xb:
      FUN_00403570(*(int *)(param_1 + 0x14),0,0);
      break;
    case 0x10:
      if (param_3 != 0) {
        *(undefined4 *)(param_3 + 0x24) = 0;
      }
      for (iVar1 = *(int *)(param_1 + 0x18); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x18)) {
        FUN_00403570(*(int *)(iVar1 + 0xc),*(int *)(iVar1 + 0x14),param_3);
      }
      break;
    case 0x12:
      iVar2 = param_1;
      if (param_3 != 0) {
        *(undefined4 *)(param_3 + 0x24) = 0;
        *(undefined4 *)(param_1 + 0x24) = 0;
        iVar2 = param_3;
      }
      break;
    case 0x13:
      if (param_3 == *(int *)(param_1 + 0x14)) {
        if (*(int *)(param_3 + 0x24) == -1) {
          *(undefined4 *)(param_3 + 0x24) = 1;
        }
        iVar2 = 0;
      }
    }
    param_3 = iVar2;
  }
  return;
}



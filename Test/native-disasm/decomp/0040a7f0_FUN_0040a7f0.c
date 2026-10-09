// FUN_0040a7f0 @ 0040a7f0 size=74 callers=2

int __fastcall FUN_0040a7f0(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  switch(*(undefined2 *)(param_1 + 0xe)) {
  case 1:
  case 4:
  case 8:
    iVar1 = *(int *)(param_1 + 0x20);
    if (iVar1 == 0) {
      return (1 << ((byte)*(undefined2 *)(param_1 + 0xe) & 0x1f)) * 4;
    }
    break;
  case 0x10:
  case 0x20:
    if (*(int *)(param_1 + 0x10) == 3) {
      return 0xc;
    }
  }
  return iVar1 * 4;
}



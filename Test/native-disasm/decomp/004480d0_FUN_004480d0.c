// FUN_004480d0 @ 004480d0 size=44 callers=1

int __fastcall FUN_004480d0(undefined1 *param_1,undefined1 *param_2)

{
  int iVar1;
  
  iVar1 = 0;
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    switch(*param_1) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 0xb:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
      iVar1 = iVar1 + 5;
      break;
    case 8:
    case 9:
    case 10:
    case 0xc:
    case 0xd:
    case 0x22:
    case 0x5c:
      iVar1 = iVar1 + 1;
    }
  }
  return iVar1;
}



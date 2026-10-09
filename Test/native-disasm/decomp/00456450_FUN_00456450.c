// FUN_00456450 @ 00456450 size=83 callers=1

uint __fastcall FUN_00456450(int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x50);
  if ((uVar1 & 0x400000) != 0) {
    switch(*(undefined1 *)(param_1 + 0x48)) {
    case 0x44:
    case 0x53:
    case 0x57:
    case 99:
    case 100:
    case 0x73:
    case 0x77:
      goto switchD_0045646e_caseD_44;
    default:
switchD_0045646e_caseD_45:
      return 1;
    }
  }
  switch(*(undefined1 *)(param_1 + 0x48)) {
  case 0x22:
  case 0x2f:
    return (uint)((byte)(uVar1 >> 0x18) & 1);
  default:
switchD_0045646e_caseD_44:
    return 0;
  case 0x24:
  case 0x2a:
  case 0x2e:
  case 0x5b:
  case 0x5c:
  case 0x5e:
  case 0x7c:
    goto switchD_0045646e_caseD_45;
  case 0x28:
  case 0x29:
  case 0x2b:
  case 0x3f:
  case 0x7b:
  case 0x7d:
    return (uint)((byte)(uVar1 >> 0x17) & 1);
  }
}



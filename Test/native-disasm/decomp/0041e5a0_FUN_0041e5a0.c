// FUN_0041e5a0 @ 0041e5a0 size=130 callers=1

uint __fastcall FUN_0041e5a0(uint *param_1,int param_2)

{
  undefined1 *puVar1;
  char cVar2;
  uint uVar3;
  undefined *puVar4;
  
  uVar3 = *(uint *)(param_2 + 4);
  if (*param_1 != uVar3) {
    puVar1 = (undefined1 *)((int)param_1 + 0xe);
    param_1 = (uint *)0x0;
    switch(*puVar1) {
    case 0:
    case 0x30:
    case 0x32:
    case 0x33:
    case 0xaa:
    case 0xaf:
      cVar2 = *(char *)(param_2 + 0xe);
      param_1 = (uint *)0x0;
      if (((((cVar2 == -0x56) || (cVar2 == -0x51)) || (cVar2 == '2')) ||
          ((cVar2 == '0' || (cVar2 == '3')))) ||
         ((cVar2 == '\0' ||
          ((cVar2 == '\x02' && (param_1 = (uint *)FUN_00419890(uVar3), (char)param_1[9] == '\0')))))
         ) {
LAB_0041e5f2:
        return CONCAT31((int3)((uint)param_1 >> 8),2);
      }
      break;
    case 0x2e:
    case 0x2f:
      cVar2 = *(char *)(param_2 + 0xe);
      param_1 = (uint *)0x0;
      if ((cVar2 == '.') || (cVar2 == '/')) goto LAB_0041e5f2;
      if (cVar2 == '\x02') {
        puVar4 = FUN_00419890(uVar3);
        param_1 = (uint *)0x0;
        if ((puVar4[0x24] & 0x7f) == 0x2f) {
          return 2;
        }
      }
    }
  }
  return (uint)param_1 & 0xffffff00;
}



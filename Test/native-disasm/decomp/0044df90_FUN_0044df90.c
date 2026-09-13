// FUN_0044df90 @ 0044df90 size=49 callers=1

uint __fastcall FUN_0044df90(int *param_1)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = (char *)(*param_1 + 1);
  if (pcVar2 != (char *)param_1[2]) {
    if (((param_1[0x14] & 8U) == 0) && ((*pcVar2 == '(' || (*pcVar2 == ')')))) {
LAB_0044dfbb:
      return CONCAT31((int3)((uint)pcVar2 >> 8),1);
    }
    if ((param_1[0x14] & 0x10U) == 0) {
      cVar1 = *pcVar2;
      pcVar2 = (char *)CONCAT31((int3)((uint)pcVar2 >> 8),cVar1);
      if ((cVar1 == '{') || (cVar1 == '}')) goto LAB_0044dfbb;
    }
  }
  return (uint)pcVar2 & 0xffffff00;
}



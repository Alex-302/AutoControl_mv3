// FUN_0041a020 @ 0041a020 size=142 callers=2

ushort __fastcall FUN_0041a020(byte param_1,char param_2)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  undefined2 local_2;
  
  bVar1 = param_1 & 0x7f;
  if (param_2 == '\0') {
    if ((bVar1 != 0x2a) && (bVar1 != 0x2d)) {
      bVar3 = bVar1 == 0x2f;
      goto LAB_0041a054;
    }
  }
  else {
    if (param_2 == '\x01') {
      bVar3 = bVar1 == 0x2a;
LAB_0041a054:
      if (bVar3) goto LAB_0041a09a;
    }
    else if (param_2 == '\x02') {
      if ((bVar1 == 0x2c) || (bVar1 == 0x30)) goto LAB_0041a09a;
      bVar3 = bVar1 == 0x33;
      goto LAB_0041a054;
    }
    if ((((bVar1 != 3) && (bVar1 != 2)) && (bVar1 != 1)) && ((bVar1 != 0 && (bVar1 != 0x32)))) {
      bVar2 = 1;
      if ((param_2 == '\0') ||
         ((param_2 == '\x02' && (((bVar1 == 0x2e || (bVar1 == 0x2f)) || (bVar1 == 0x2d)))))) {
        return 0x101;
      }
      goto LAB_0041a09c;
    }
  }
LAB_0041a09a:
  bVar2 = 0;
LAB_0041a09c:
  local_2 = (ushort)bVar2;
  return local_2;
}



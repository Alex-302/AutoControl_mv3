// FUN_00412a80 @ 00412a80 size=73 callers=1

uint __fastcall FUN_00412a80(uint param_1)

{
  uint in_EAX;
  
  if ((((6 < param_1) &&
       ((((in_EAX = param_1 - 0x15, 10 < in_EAX || (param_1 == 0x1b)) && (param_1 < 0xe3)) &&
        ((param_1 < 0x3a || (0x40 < param_1)))))) && ((param_1 < 0xc1 || (0xda < param_1)))) &&
     (((param_1 != 0x11 && (param_1 != 0x10)) && (param_1 != 0x12)))) {
    return CONCAT31((int3)(in_EAX >> 8),1);
  }
  return in_EAX & 0xffffff00;
}



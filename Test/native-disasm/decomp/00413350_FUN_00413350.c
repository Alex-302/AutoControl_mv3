// FUN_00413350 @ 00413350 size=60 callers=1

uint FUN_00413350(void)

{
  uint in_EAX;
  
  if ((DAT_004a26b3 == '\x01') &&
     (in_EAX = CONCAT22((short)(in_EAX >> 0x10),DAT_004a26c2) & 0xfffffc00,
     (DAT_004a26c2 & 0xfc00) != 0x1000)) {
    in_EAX = DAT_004a26b0 - 1;
    if ((5 < (ushort)in_EAX) || (DAT_004a26b0 == 3)) {
      return CONCAT31((int3)(in_EAX >> 8),1);
    }
  }
  return in_EAX & 0xffffff00;
}



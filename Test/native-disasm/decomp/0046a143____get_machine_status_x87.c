// ___get_machine_status_x87 @ 0046a143 size=97 callers=2

/* Library Function - Single Match
    ___get_machine_status_x87
   
   Library: Visual Studio 2015 Release */

byte __cdecl ___get_machine_status_x87(uint param_1)

{
  byte bVar1;
  
  bVar1 = 0;
  if ((param_1 & 0x1f) != 0) {
    bVar1 = (param_1 & 0x100010) == 0x100010;
    if ((param_1 & 0x80008) == 0x80008) {
      bVar1 = bVar1 | 4;
    }
    if ((param_1 & 0x40004) == 0x40004) {
      bVar1 = bVar1 | 8;
    }
    if ((param_1 & 0x20002) == 0x20002) {
      bVar1 = bVar1 | 0x10;
    }
    if ((param_1 & 0x10001) == 0x10001) {
      bVar1 = bVar1 | 0x20;
    }
  }
  return bVar1;
}



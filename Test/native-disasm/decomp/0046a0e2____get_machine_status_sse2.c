// ___get_machine_status_sse2 @ 0046a0e2 size=97 callers=2

/* Library Function - Single Match
    ___get_machine_status_sse2
   
   Library: Visual Studio 2015 Release */

byte __cdecl ___get_machine_status_sse2(uint param_1)

{
  byte bVar1;
  
  bVar1 = 0;
  if ((param_1 & 0x1f) != 0) {
    bVar1 = (param_1 & 0x10000010) == 0x10000010;
    if ((param_1 & 0x8000008) == 0x8000008) {
      bVar1 = bVar1 | 4;
    }
    if ((param_1 & 0x4000004) == 0x4000004) {
      bVar1 = bVar1 | 8;
    }
    if ((param_1 & 0x2000002) == 0x2000002) {
      bVar1 = bVar1 | 0x10;
    }
    if ((param_1 & 0x1000001) == 0x1000001) {
      bVar1 = bVar1 | 0x20;
    }
  }
  return bVar1;
}



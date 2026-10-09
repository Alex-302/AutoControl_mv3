// __initialize_onexit_table @ 0046926a size=61 callers=4

/* Library Function - Single Match
    __initialize_onexit_table
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl __initialize_onexit_table(uint *param_1)

{
  byte bVar1;
  undefined4 uVar2;
  uint uVar3;
  
  if (param_1 == (uint *)0x0) {
    uVar2 = 0xffffffff;
  }
  else {
    if (*param_1 == param_1[2]) {
      bVar1 = 0x20 - ((byte)DAT_0049d070 & 0x1f) & 0x1f;
      uVar3 = (0U >> bVar1 | 0 << 0x20 - bVar1) ^ DAT_0049d070;
      *param_1 = uVar3;
      param_1[1] = uVar3;
      param_1[2] = uVar3;
    }
    uVar2 = 0;
  }
  return uVar2;
}



// __isatty @ 00473c93 size=86 callers=4

/* Library Function - Single Match
    __isatty
   
   Library: Visual Studio 2015 Release */

int __cdecl __isatty(int _FileHandle)

{
  int *piVar1;
  
  if (_FileHandle == -2) {
    piVar1 = __errno();
    *piVar1 = 9;
  }
  else {
    if ((-1 < _FileHandle) && ((uint)_FileHandle < DAT_0049faf8)) {
      return *(byte *)((&DAT_0049f8f8)[_FileHandle >> 6] + 0x28 + (_FileHandle & 0x3fU) * 0x30) &
             0x40;
    }
    piVar1 = __errno();
    *piVar1 = 9;
    FUN_00465fa2();
  }
  return 0;
}



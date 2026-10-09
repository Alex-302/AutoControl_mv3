// __get_osfhandle @ 0045f6b5 size=106 callers=7

/* Library Function - Single Match
    __get_osfhandle
   
   Library: Visual Studio 2015 Release */

intptr_t __cdecl __get_osfhandle(int _FileHandle)

{
  ulong *puVar1;
  int *piVar2;
  int iVar3;
  
  if (_FileHandle == -2) {
    puVar1 = ___doserrno();
    *puVar1 = 0;
    piVar2 = __errno();
    *piVar2 = 9;
  }
  else {
    if ((-1 < _FileHandle) && ((uint)_FileHandle < DAT_0049faf8)) {
      iVar3 = (_FileHandle & 0x3fU) * 0x30;
      if ((*(byte *)((&DAT_0049f8f8)[_FileHandle >> 6] + 0x28 + iVar3) & 1) != 0) {
        return *(intptr_t *)((&DAT_0049f8f8)[_FileHandle >> 6] + 0x18 + iVar3);
      }
    }
    puVar1 = ___doserrno();
    *puVar1 = 0;
    piVar2 = __errno();
    *piVar2 = 9;
    FUN_00465fa2();
  }
  return -1;
}



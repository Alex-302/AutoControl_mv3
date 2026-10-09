// __close @ 0047632e size=127 callers=1

/* Library Function - Single Match
    __close
   
   Library: Visual Studio 2015 Release */

int __cdecl __close(int _FileHandle)

{
  ulong *puVar1;
  int *piVar2;
  int iVar3;
  int *local_8;
  
  if (_FileHandle == -2) {
    puVar1 = ___doserrno();
    *puVar1 = 0;
    piVar2 = __errno();
    *piVar2 = 9;
  }
  else {
    if (((-1 < _FileHandle) && ((uint)_FileHandle < DAT_0049faf8)) &&
       ((*(byte *)((&DAT_0049f8f8)[_FileHandle >> 6] + 0x28 + (_FileHandle & 0x3fU) * 0x30) & 1) !=
        0)) {
      local_8 = &_FileHandle;
      iVar3 = __acrt_lowio_lock_fh_and_call<<lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec>_>
                        (_FileHandle,(<lambda_2fe9b910cf3cbf4a0ab98a02ba45b3ec> *)&local_8);
      return iVar3;
    }
    puVar1 = ___doserrno();
    *puVar1 = 0;
    piVar2 = __errno();
    *piVar2 = 9;
    FUN_00465fa2();
  }
  return -1;
}



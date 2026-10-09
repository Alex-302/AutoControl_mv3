// __commit @ 00473c24 size=111 callers=1

/* Library Function - Single Match
    __commit
   
   Library: Visual Studio 2015 Release */

int __cdecl __commit(int _FileHandle)

{
  int *piVar1;
  int iVar2;
  int *local_8;
  
  if (_FileHandle == -2) {
    piVar1 = __errno();
    *piVar1 = 9;
  }
  else {
    if (((-1 < _FileHandle) && ((uint)_FileHandle < DAT_0049faf8)) &&
       ((*(byte *)((&DAT_0049f8f8)[_FileHandle >> 6] + 0x28 + (_FileHandle & 0x3fU) * 0x30) & 1) !=
        0)) {
      local_8 = &_FileHandle;
      iVar2 = __acrt_lowio_lock_fh_and_call<<lambda_6978c1fb23f02e42e1d9e99668cc68aa>_>
                        (_FileHandle,(<lambda_6978c1fb23f02e42e1d9e99668cc68aa> *)&local_8);
      return iVar2;
    }
    piVar1 = __errno();
    *piVar1 = 9;
    FUN_00465fa2();
  }
  return -1;
}



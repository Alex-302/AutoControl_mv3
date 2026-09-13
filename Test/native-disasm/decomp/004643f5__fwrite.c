// _fwrite @ 004643f5 size=88 callers=2

/* Library Function - Single Match
    _fwrite
   
   Library: Visual Studio 2015 Release */

size_t __cdecl _fwrite(void *_Str,size_t _Size,size_t _Count,FILE *_File)

{
  int *piVar1;
  uint uVar2;
  FILE **local_14;
  void **local_10;
  size_t *local_c;
  size_t *local_8;
  
  if ((_Size != 0) && (_Count != 0)) {
    if (_File != (FILE *)0x0) {
      local_14 = &_File;
      local_10 = &_Str;
      local_c = &_Size;
      local_8 = &_Count;
      uVar2 = __acrt_lock_stream_and_call<<lambda_b51c0495177f500e782686251704ae76>_>
                        (_File,(<lambda_b51c0495177f500e782686251704ae76> *)&local_14);
      return uVar2;
    }
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
  }
  return 0;
}



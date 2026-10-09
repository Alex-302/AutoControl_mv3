// _fclose @ 00473ae4 size=115 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _fclose
   
   Library: Visual Studio 2015 Release */

int __cdecl _fclose(FILE *_File)

{
  int *piVar1;
  int iVar2;
  
  if (_File == (FILE *)0x0) {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
  }
  else {
    if (((uint)_File->_flag >> 0xc & 1) == 0) {
      __lock_file(_File);
      iVar2 = __fclose_nolock(_File);
      FUN_00473b5a();
      return iVar2;
    }
    __acrt_stdio_free_stream();
  }
  return -1;
}



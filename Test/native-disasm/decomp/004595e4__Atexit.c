// _Atexit @ 004595e4 size=46 callers=1

/* Library Function - Single Match
    void __cdecl _Atexit(void (__cdecl*)(void))
   
   Libraries: Visual Studio 2012 Release, Visual Studio 2015 Release, Visual Studio 2017 Release */

void __cdecl _Atexit(_func_void *param_1)

{
  code *pcVar1;
  PVOID pvVar2;
  int iVar3;
  BOOL BVar4;
  
  if (DAT_0049d008 != 0) {
    DAT_0049d008 = DAT_0049d008 + -1;
    pvVar2 = EncodePointer(param_1);
    *(PVOID *)(DAT_0049d008 * 4 + 0x49efb0) = pvVar2;
    return;
  }
  iVar3 = ___acrt_get_sigabrt_handler();
  if (iVar3 != 0) {
    _raise(0x16);
  }
  if (((byte)DAT_0049d1dc & 2) != 0) {
    BVar4 = IsProcessorFeaturePresent(0x17);
    if (BVar4 != 0) {
      pcVar1 = (code *)swi(0x29);
      (*pcVar1)();
    }
    ___acrt_call_reportfault(3,0x40000015,1);
  }
                    /* WARNING: Subroutine does not return */
  __exit(3);
}



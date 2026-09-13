// operator_new @ 0045a31d size=51 callers=118

/* Library Function - Single Match
    void * __cdecl operator new(unsigned int)
   
   Library: Visual Studio 2015 Release */

void * __cdecl operator_new(uint param_1)

{
  int iVar1;
  void *pvVar2;
  
  while( true ) {
    do {
      pvVar2 = (void *)FUN_004665ab(param_1);
      if (pvVar2 != (void *)0x0) {
        return pvVar2;
      }
      iVar1 = __callnewh(param_1);
    } while (iVar1 != 0);
    if (param_1 != 0xffffffff) break;
    FUN_0045ac5e();
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458e6a();
}



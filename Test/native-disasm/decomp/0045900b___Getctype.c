// __Getctype @ 0045900b size=107 callers=1

/* Library Function - Single Match
    __Getctype
   
   Library: Visual Studio 2015 Release */

_Ctypevec * __cdecl __Getctype(_Ctypevec *__return_storage_ptr__)

{
  UINT UVar1;
  short *psVar2;
  ushort *puVar3;
  wchar_t **ppwVar4;
  wchar_t *pwVar5;
  int iVar6;
  
  UVar1 = ____lc_codepage_func();
  __return_storage_ptr__->_Page = UVar1;
  psVar2 = __calloc_base(0x100,2);
  __return_storage_ptr__->_Table = psVar2;
  if (psVar2 == (short *)0x0) {
    puVar3 = ___pctype_func();
    __return_storage_ptr__->_Delfl = 0;
    __return_storage_ptr__->_Table = (short *)puVar3;
  }
  else {
    puVar3 = ___pctype_func();
    __return_storage_ptr__->_Delfl = 1;
    psVar2 = __return_storage_ptr__->_Table;
    for (iVar6 = 0x80; iVar6 != 0; iVar6 = iVar6 + -1) {
      *(undefined4 *)psVar2 = *(undefined4 *)puVar3;
      puVar3 = puVar3 + 2;
      psVar2 = psVar2 + 2;
    }
  }
  ppwVar4 = ____lc_locale_name_func();
  pwVar5 = ppwVar4[1];
  __return_storage_ptr__->_LocaleName = pwVar5;
  if (pwVar5 != (wchar_t *)0x0) {
    pwVar5 = FUN_00466962(pwVar5);
    __return_storage_ptr__->_LocaleName = pwVar5;
  }
  return __return_storage_ptr__;
}



// __mbtowc_l @ 0046ba50 size=250 callers=1

/* Library Function - Single Match
    __mbtowc_l
   
   Library: Visual Studio 2015 Release */

int __cdecl __mbtowc_l(wchar_t *_DstCh,char *_SrcCh,size_t _SrcSizeInBytes,_locale_t _Locale)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int local_14;
  localeinfo_struct local_10;
  char local_8;
  
  if ((_SrcCh == (char *)0x0) || (_SrcSizeInBytes == 0)) {
    return 0;
  }
  if (*_SrcCh == '\0') {
    if (_DstCh == (wchar_t *)0x0) {
      return 0;
    }
    *_DstCh = L'\0';
    return 0;
  }
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,(__crt_locale_pointers *)_Locale);
  if ((local_10.locinfo)->locale_name[2] == (wchar_t *)0x0) {
    if (_DstCh != (wchar_t *)0x0) {
      *_DstCh = (ushort)(byte)*_SrcCh;
    }
    uVar3 = 1;
    goto LAB_0046bb32;
  }
  iVar1 = __isleadbyte_l((uint)(byte)*_SrcCh,&local_10);
  if (iVar1 == 0) {
    uVar3 = 1;
    iVar1 = MultiByteToWideChar((local_10.locinfo)->lc_collate_cp,9,_SrcCh,1,_DstCh,
                                (uint)(_DstCh != (wchar_t *)0x0));
    if (iVar1 != 0) goto LAB_0046bb32;
LAB_0046bb24:
    piVar2 = __errno();
    uVar3 = 0xffffffff;
    *piVar2 = 0x2a;
  }
  else {
    if ((int)(local_10.locinfo)->lc_codepage < 2) {
LAB_0046baf1:
      uVar3 = (local_10.locinfo)->lc_codepage;
LAB_0046baf4:
      if ((_SrcSizeInBytes < uVar3) || (_SrcCh[1] == '\0')) goto LAB_0046bb24;
    }
    else {
      uVar3 = (local_10.locinfo)->lc_codepage;
      if ((int)_SrcSizeInBytes < (int)uVar3) goto LAB_0046baf4;
      iVar1 = MultiByteToWideChar((local_10.locinfo)->lc_collate_cp,9,_SrcCh,
                                  (local_10.locinfo)->lc_codepage,_DstCh,
                                  (uint)(_DstCh != (wchar_t *)0x0));
      if (iVar1 == 0) goto LAB_0046baf1;
    }
    uVar3 = (local_10.locinfo)->lc_codepage;
  }
LAB_0046bb32:
  if (local_8 != '\0') {
    *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
    return uVar3;
  }
  return uVar3;
}



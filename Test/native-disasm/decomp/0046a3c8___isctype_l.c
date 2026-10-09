// __isctype_l @ 0046a3c8 size=210 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __isctype_l
   
   Library: Visual Studio 2015 Release */

int __cdecl __isctype_l(int _C,int _Type,_locale_t _Locale)

{
  int iVar1;
  BOOL BVar2;
  int local_24;
  localeinfo_struct local_20;
  char local_18;
  CHAR local_14;
  CHAR local_13;
  undefined1 local_12;
  ushort local_10 [4];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_24,(__crt_locale_pointers *)_Locale);
  if (_C + 1U < 0x101) {
    local_10[0] = *(ushort *)((local_20.locinfo)->refcount + _C * 2);
  }
  else {
    iVar1 = __isleadbyte_l(_C >> 8 & 0xff,&local_20);
    if (iVar1 == 0) {
      local_13 = '\0';
      iVar1 = 1;
      local_14 = (CHAR)_C;
    }
    else {
      local_12 = 0;
      iVar1 = 2;
      local_14 = (CHAR)((uint)_C >> 8);
      local_13 = (CHAR)_C;
    }
    local_10[0] = 0;
    local_10[1] = 0;
    local_10[2] = 0;
    BVar2 = ___acrt_GetStringTypeA
                      ((__crt_locale_pointers *)&local_20,1,&local_14,iVar1,local_10,
                       (local_20.locinfo)->lc_collate_cp,1);
    if (BVar2 == 0) {
      if (local_18 != '\0') {
        *(uint *)(local_24 + 0x350) = *(uint *)(local_24 + 0x350) & 0xfffffffd;
      }
      return 0;
    }
  }
  if (local_18 != '\0') {
    *(uint *)(local_24 + 0x350) = *(uint *)(local_24 + 0x350) & 0xfffffffd;
  }
  return (uint)local_10[0] & _Type;
}



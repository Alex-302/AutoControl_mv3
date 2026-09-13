// ___acrt_CompareStringA @ 00476ba8 size=72 callers=1

/* Library Function - Single Match
    ___acrt_CompareStringA
   
   Library: Visual Studio 2015 Release */

void __cdecl
___acrt_CompareStringA
          (__crt_locale_pointers *param_1,wchar_t *param_2,ulong param_3,char *param_4,int param_5,
          char *param_6,int param_7,int param_8)

{
  int local_14;
  __crt_locale_pointers local_10 [8];
  char local_8;
  
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,param_1);
  InternalCompareStringA(local_10,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  if (local_8 != '\0') {
    *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
  }
  return;
}



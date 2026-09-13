// getSystemCP @ 00470655 size=115 callers=2

/* Library Function - Single Match
    int __cdecl getSystemCP(int)
   
   Library: Visual Studio 2015 Release */

int __cdecl getSystemCP(int param_1)

{
  int local_14;
  int local_10;
  char local_8;
  
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,(__crt_locale_pointers *)0x0);
  DAT_0049fc04 = 0;
  if (param_1 == -2) {
    DAT_0049fc04 = 1;
    param_1 = GetOEMCP();
  }
  else if (param_1 == -3) {
    DAT_0049fc04 = 1;
    param_1 = GetACP();
  }
  else if (param_1 == -4) {
    DAT_0049fc04 = 1;
    param_1 = *(UINT *)(local_10 + 8);
  }
  if (local_8 != '\0') {
    *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
  }
  return param_1;
}



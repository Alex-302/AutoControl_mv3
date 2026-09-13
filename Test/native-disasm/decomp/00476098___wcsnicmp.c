// __wcsnicmp @ 00476098 size=184 callers=2

/* Library Function - Single Match
    __wcsnicmp
   
   Library: Visual Studio 2015 Release */

int __cdecl __wcsnicmp(wchar_t *_Str1,wchar_t *_Str2,size_t _MaxCount)

{
  wchar_t wVar1;
  int *piVar2;
  int iVar3;
  wchar_t wVar4;
  
  if (DAT_0049f7f4 == 0) {
    iVar3 = 0;
    if (_MaxCount != 0) {
      if ((_Str1 == (wchar_t *)0x0) || (_Str2 == (wchar_t *)0x0)) {
        piVar2 = __errno();
        *piVar2 = 0x16;
        FUN_00465fa2();
        iVar3 = 0x7fffffff;
      }
      else {
        iVar3 = (int)_Str1 - (int)_Str2;
        do {
          wVar4 = *(wchar_t *)(iVar3 + (int)_Str2);
          if ((0x40 < (ushort)wVar4) && ((ushort)wVar4 < 0x5b)) {
            wVar4 = wVar4 + L' ';
          }
          wVar1 = *_Str2;
          if ((0x40 < (ushort)wVar1) && ((ushort)wVar1 < 0x5b)) {
            wVar1 = wVar1 + L' ';
          }
          _Str2 = _Str2 + 1;
          _MaxCount = _MaxCount - 1;
        } while (((_MaxCount != 0) && (wVar4 != L'\0')) && (wVar4 == wVar1));
        iVar3 = (uint)(ushort)wVar4 - (uint)(ushort)wVar1;
      }
    }
  }
  else {
    iVar3 = __wcsnicmp_l(_Str1,_Str2,_MaxCount,(_locale_t)0x0);
  }
  return iVar3;
}



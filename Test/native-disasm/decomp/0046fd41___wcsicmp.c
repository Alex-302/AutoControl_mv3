// __wcsicmp @ 0046fd41 size=149 callers=13

/* Library Function - Single Match
    __wcsicmp
   
   Library: Visual Studio 2015 Release */

int __cdecl __wcsicmp(wchar_t *_Str1,wchar_t *_Str2)

{
  wchar_t wVar1;
  int *piVar2;
  int iVar3;
  wchar_t wVar4;
  
  if (DAT_0049f7f4 != 0) {
    iVar3 = __wcsicmp_l(_Str1,_Str2,(_locale_t)0x0);
    return iVar3;
  }
  if ((_Str1 != (wchar_t *)0x0) && (_Str2 != (wchar_t *)0x0)) {
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
    } while ((wVar4 != L'\0') && (wVar4 == wVar1));
    return (uint)(ushort)wVar4 - (uint)(ushort)wVar1;
  }
  piVar2 = __errno();
  *piVar2 = 0x16;
  FUN_00465fa2();
  return 0x7fffffff;
}



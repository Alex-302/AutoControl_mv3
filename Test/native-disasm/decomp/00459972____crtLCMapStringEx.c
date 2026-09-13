// ___crtLCMapStringEx @ 00459972 size=86 callers=3

/* Library Function - Single Match
    ___crtLCMapStringEx
   
   Library: Visual Studio 2015 Release */

int __cdecl
___crtLCMapStringEx(LPCWSTR lpLocaleName,DWORD dwMapFlags,LPCWSTR lpSrcStr,int cchSrc,
                   LPWSTR lpDestStr,int cchDest)

{
  int iVar1;
  LCID Locale;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  pcVar2 = (code *)(DAT_0049f08c ^ DAT_0049d070);
  if (pcVar2 == (code *)0x0) {
    Locale = ___crtDownlevelLocaleNameToLCID((int)lpLocaleName);
    iVar1 = LCMapStringW(Locale,dwMapFlags,lpSrcStr,cchSrc,lpDestStr,cchDest);
  }
  else {
    uVar5 = 0;
    uVar4 = 0;
    uVar3 = 0;
    guard_check_icall();
    iVar1 = (*pcVar2)(lpLocaleName,dwMapFlags,lpSrcStr,cchSrc,lpDestStr,cchDest,uVar3,uVar4,uVar5);
  }
  return iVar1;
}



// ___crtCompareStringEx @ 004598f2 size=86 callers=1

/* Library Function - Single Match
    ___crtCompareStringEx
   
   Library: Visual Studio 2015 Release */

int __cdecl
___crtCompareStringEx
          (LPCWSTR lpLocaleName,DWORD dwCmpFlags,LPCWSTR lpString1,int cchCount1,LPCWSTR lpString2,
          int cchCount2)

{
  int iVar1;
  LCID Locale;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  pcVar2 = (code *)(DAT_0049f084 ^ DAT_0049d070);
  if (pcVar2 == (code *)0x0) {
    Locale = ___crtDownlevelLocaleNameToLCID((int)lpLocaleName);
    iVar1 = CompareStringW(Locale,dwCmpFlags,lpString1,cchCount1,lpString2,cchCount2);
  }
  else {
    uVar5 = 0;
    uVar4 = 0;
    uVar3 = 0;
    guard_check_icall();
    iVar1 = (*pcVar2)(lpLocaleName,dwCmpFlags,lpString1,cchCount1,lpString2,cchCount2,uVar3,uVar4,
                      uVar5);
  }
  return iVar1;
}



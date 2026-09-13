// __Strxfrm @ 0045871c size=172 callers=1

/* Library Function - Single Match
    __Strxfrm
   
   Library: Visual Studio 2015 Release */

size_t __cdecl __Strxfrm(char *_String1,char *_End1,char *param_3,char *param_4,_Collvec *param_5)

{
  wchar_t **ppwVar1;
  UINT _CchDest;
  _locale_t _Plocinfo;
  LPCSTR pCVar2;
  LPCSTR pCVar3;
  LPCSTR _LpSrcStr;
  BOOL unaff_EDI;
  LPSTR _LpDestStr;
  
  _LpSrcStr = param_4 + -(int)param_3;
  _LpDestStr = _End1 + -(int)_String1;
  if (param_5 == (_Collvec *)0x0) {
    ppwVar1 = ____lc_locale_name_func();
    _Plocinfo = (_locale_t)ppwVar1[1];
    _CchDest = ____lc_collate_cp_func();
  }
  else {
    _Plocinfo = (_locale_t)param_5->_LocaleName;
    _CchDest = param_5->_Page;
  }
  if ((_Plocinfo == (_locale_t)0x0) && (_CchDest == 0)) {
    pCVar3 = _LpSrcStr;
    if (_LpSrcStr <= _LpDestStr) {
      FUN_0045c870((uint *)_String1,(uint *)param_3,(uint)_LpSrcStr);
    }
  }
  else {
    pCVar2 = (LPCSTR)___crtLCMapStringA(_Plocinfo,(LPCWSTR)&DAT_00000400,(DWORD)param_3,_LpSrcStr,0,
                                        (LPSTR)0x0,_CchDest,1,unaff_EDI);
    pCVar3 = (LPCSTR)0xffffffff;
    if ((pCVar2 != (LPCSTR)0x0) && (pCVar3 = pCVar2, (int)pCVar2 <= (int)_LpDestStr)) {
      ___crtLCMapStringA(_Plocinfo,(LPCWSTR)&DAT_00000400,(DWORD)param_3,_LpSrcStr,(int)_String1,
                         _LpDestStr,_CchDest,1,unaff_EDI);
    }
  }
  return (size_t)pCVar3;
}



// __Strcoll @ 00459191 size=147 callers=1

/* Library Function - Single Match
    __Strcoll
   
   Library: Visual Studio 2015 Release */

int __cdecl __Strcoll(char *param_1,char *param_2,char *param_3,char *param_4,_Collvec *param_5)

{
  wchar_t **ppwVar1;
  UINT _CchCount2;
  LPCSTR _Size;
  int iVar2;
  int *piVar3;
  _locale_t _Plocinfo;
  LPCSTR _LpString1;
  int unaff_EDI;
  LPCSTR _LpString2;
  
  _LpString1 = param_2 + -(int)param_1;
  _LpString2 = param_4 + -(int)param_3;
  if (param_5 == (_Collvec *)0x0) {
    ppwVar1 = ____lc_locale_name_func();
    _Plocinfo = (_locale_t)ppwVar1[1];
    _CchCount2 = ____lc_collate_cp_func();
  }
  else {
    _Plocinfo = (_locale_t)param_5->_LocaleName;
    _CchCount2 = param_5->_Page;
  }
  if (_Plocinfo == (_locale_t)0x0) {
    _Size = _LpString1;
    if ((int)_LpString2 <= (int)_LpString1) {
      _Size = _LpString2;
    }
    iVar2 = _memcmp(param_1,param_3,(size_t)_Size);
    if ((iVar2 == 0) && (_LpString1 != _LpString2)) {
      iVar2 = (uint)((int)_LpString2 <= (int)_LpString1) * 2 + -1;
    }
  }
  else {
    iVar2 = ___crtCompareStringA
                      (_Plocinfo,(LPCWSTR)&DAT_00001000,(DWORD)param_1,_LpString1,(int)param_3,
                       _LpString2,_CchCount2,unaff_EDI);
    if (iVar2 == 0) {
      piVar3 = __errno();
      *piVar3 = 0x16;
      iVar2 = 0x7fffffff;
    }
    else {
      iVar2 = iVar2 + -2;
    }
  }
  return iVar2;
}



// __Toupper @ 00459224 size=250 callers=2

/* Library Function - Single Match
    __Toupper
   
   Library: Visual Studio 2015 Release */

int __cdecl __Toupper(int param_1,_Ctypevec *param_2)

{
  wchar_t **ppwVar1;
  int iVar2;
  ushort *puVar3;
  uint uVar4;
  LPCSTR _LpSrcStr;
  BOOL unaff_EBX;
  _locale_t _Plocinfo;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  uint local_10;
  UINT local_c;
  byte local_8;
  undefined1 local_7;
  
  if (param_2 == (_Ctypevec *)0x0) {
    ppwVar1 = ____lc_locale_name_func();
    _Plocinfo = (_locale_t)ppwVar1[2];
    local_c = ____lc_codepage_func();
  }
  else {
    _Plocinfo = (_locale_t)param_2->_LocaleName;
    local_c = param_2->_Page;
  }
  if (_Plocinfo == (_locale_t)0x0) {
    if (0x19 < param_1 - 0x61U) {
      return param_1;
    }
    return param_1 + -0x20;
  }
  if ((uint)param_1 < 0x100) {
    if (param_2 != (_Ctypevec *)0x0) {
      if ((*(byte *)(param_2->_Table + param_1) & 2) == 0) {
        return param_1;
      }
      goto LAB_0045928b;
    }
    iVar2 = _islower(param_1);
    if (iVar2 == 0) {
      return param_1;
    }
  }
  else {
LAB_0045928b:
    if (param_2 != (_Ctypevec *)0x0) {
      local_18 = (undefined1)((uint)param_1 >> 8);
      uVar4 = (uint)(int)param_2->_Table[param_1 >> 8 & 0xff] >> 0xf & 1;
      goto LAB_004592c2;
    }
  }
  local_10 = param_1 >> 8;
  puVar3 = ___pctype_func();
  local_18 = (undefined1)local_10;
  uVar4 = puVar3[local_10 & 0xff] & 0x8000;
LAB_004592c2:
  if (uVar4 == 0) {
    local_17 = 0;
    _LpSrcStr = (LPCSTR)0x1;
    local_18 = (char)param_1;
  }
  else {
    local_16 = 0;
    _LpSrcStr = (LPCSTR)0x2;
    local_17 = (char)param_1;
  }
  iVar2 = ___crtLCMapStringA(_Plocinfo,(LPCWSTR)&DAT_00000200,(DWORD)&local_18,_LpSrcStr,
                             (int)&local_8,(LPSTR)0x3,local_c,1,unaff_EBX);
  if ((iVar2 != 0) && (param_1 = (int)local_8, iVar2 != 1)) {
    param_1 = (int)CONCAT11(local_8,local_7);
  }
  return param_1;
}



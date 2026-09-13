// ___crtCompareStringA @ 00459612 size=658 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* Library Function - Single Match
    ___crtCompareStringA
   
   Library: Visual Studio 2015 Release */

int __cdecl
___crtCompareStringA
          (_locale_t _Plocinfo,LPCWSTR _LocaleName,DWORD _DwCmpFlags,LPCSTR _LpString1,
          int _CchCount1,LPCSTR _LpString2,int _CchCount2,int _Code_page)

{
  uint uVar1;
  uint uVar2;
  BOOL BVar3;
  int cchWideChar;
  LPCWSTR pWVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  BYTE *pBVar8;
  int iVar9;
  LPWSTR lpWideCharStr;
  LPCWSTR local_20;
  _cpinfo local_1c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  if ((int)_LpString1 < 1) {
    if ((int)_LpString1 < -1) {
      return 0;
    }
  }
  else {
    _LpString1 = (LPCSTR)___strncnt((char *)_DwCmpFlags,(int)_LpString1);
  }
  if ((int)_LpString2 < 1) {
    if ((int)_LpString2 < -1) {
      return 0;
    }
  }
  else {
    _LpString2 = (LPCSTR)___strncnt((char *)_CchCount1,(int)_LpString2);
  }
  if ((_LpString1 == (LPCSTR)0x0) || (_LpString2 == (LPCSTR)0x0)) {
    if (_LpString1 == _LpString2) {
      return 2;
    }
    if (1 < (int)_LpString2) {
      return 1;
    }
    if (1 < (int)_LpString1) {
      return 3;
    }
    BVar3 = GetCPInfo(_CchCount2,&local_1c);
    if (BVar3 == 0) {
      return 0;
    }
    if (0 < (int)_LpString1) {
      if (local_1c.MaxCharSize < 2) {
        return 3;
      }
      pBVar8 = local_1c.LeadByte;
      while( true ) {
        if (local_1c.LeadByte[0] == 0) {
          return 3;
        }
        if (pBVar8[1] == 0) break;
        if ((*pBVar8 <= *(byte *)_DwCmpFlags) && (*(byte *)_DwCmpFlags <= pBVar8[1])) {
          return 2;
        }
        pBVar8 = pBVar8 + 2;
        local_1c.LeadByte[0] = *pBVar8;
      }
      return 3;
    }
    if (0 < (int)_LpString2) {
      if (local_1c.MaxCharSize < 2) {
        return 1;
      }
      pBVar8 = local_1c.LeadByte;
      while( true ) {
        if (local_1c.LeadByte[0] == 0) {
          return 1;
        }
        if (pBVar8[1] == 0) break;
        if ((*pBVar8 <= *(byte *)_CchCount1) && (*(byte *)_CchCount1 <= pBVar8[1])) {
          return 2;
        }
        pBVar8 = pBVar8 + 2;
        local_1c.LeadByte[0] = *pBVar8;
      }
      return 1;
    }
  }
  iVar9 = 0;
  cchWideChar = MultiByteToWideChar(_CchCount2,9,(LPCSTR)_DwCmpFlags,(int)_LpString1,(LPWSTR)0x0,0);
  if (cchWideChar == 0) {
    return 0;
  }
  uVar2 = cchWideChar * 2;
  uVar1 = uVar2 + 8;
  if ((uVar1 & -(uint)(uVar2 < uVar1)) == 0) {
    local_20 = (LPCWSTR)0x0;
  }
  else {
    if ((-(uint)(uVar2 < uVar1) & uVar1) < 0x401) {
      pWVar4 = (LPCWSTR)&stack0xffffffc4;
      local_20 = (LPCWSTR)&stack0xffffffc4;
      if (&stack0x00000000 == (undefined1 *)0x3c) goto LAB_00459887;
    }
    else {
      pWVar4 = __malloc_base(-(uint)(uVar2 < uVar2 + 8) & uVar2 + 8);
      local_20 = pWVar4;
      if (pWVar4 == (LPCWSTR)0x0) goto LAB_00459887;
      pWVar4[0] = L'\xdddd';
      pWVar4[1] = L'\0';
    }
    local_20 = pWVar4 + 4;
  }
  if (((local_20 == (LPCWSTR)0x0) ||
      (iVar5 = MultiByteToWideChar(_CchCount2,1,(LPCSTR)_DwCmpFlags,(int)_LpString1,local_20,
                                   cchWideChar), iVar5 == 0)) ||
     (iVar5 = MultiByteToWideChar(_CchCount2,9,(LPCSTR)_CchCount1,(int)_LpString2,(LPWSTR)0x0,0),
     iVar5 == 0)) goto LAB_00459887;
  uVar2 = iVar5 * 2;
  uVar1 = uVar2 + 8;
  if ((uVar1 & -(uint)(uVar2 < uVar1)) == 0) {
    lpWideCharStr = (LPWSTR)0x0;
  }
  else if ((-(uint)(uVar2 < uVar1) & uVar1) < 0x401) {
    puVar6 = (undefined4 *)&stack0xffffffc4;
    lpWideCharStr = (LPWSTR)&stack0xffffffc4;
    if (&stack0x00000000 != (undefined1 *)0x3c) {
LAB_00459838:
      lpWideCharStr = (LPWSTR)(puVar6 + 2);
    }
  }
  else {
    puVar6 = __malloc_base(-(uint)(uVar2 < uVar2 + 8) & uVar2 + 8);
    lpWideCharStr = (LPWSTR)0x0;
    if (puVar6 != (undefined4 *)0x0) {
      *puVar6 = 0xdddd;
      goto LAB_00459838;
    }
  }
  if ((lpWideCharStr != (LPWSTR)0x0) &&
     (iVar7 = MultiByteToWideChar(_CchCount2,1,(LPCSTR)_CchCount1,(int)_LpString2,lpWideCharStr,
                                  iVar5), iVar7 != 0)) {
    iVar9 = ___crtCompareStringEx
                      ((LPCWSTR)_Plocinfo,(DWORD)_LocaleName,local_20,cchWideChar,lpWideCharStr,
                       iVar5);
  }
  __freea_crt((int)lpWideCharStr);
LAB_00459887:
  __freea_crt((int)local_20);
  return iVar9;
}



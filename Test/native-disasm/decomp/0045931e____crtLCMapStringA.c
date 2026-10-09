// ___crtLCMapStringA @ 0045931e size=515 callers=4

/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___crtLCMapStringA
   
   Library: Visual Studio 2015 Release */

int __cdecl
___crtLCMapStringA(_locale_t _Plocinfo,LPCWSTR _LocaleName,DWORD _DwMapFlag,LPCSTR _LpSrcStr,
                  int _CchSrc,LPSTR _LpDestStr,int _CchDest,int _Code_page,BOOL _BError)

{
  uint uVar1;
  uint uVar2;
  LPCSTR pCVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  LPCWSTR pWVar7;
  LPCSTR cbMultiByte;
  int iVar8;
  LPCWSTR local_c;
  
  cbMultiByte = _LpSrcStr;
  if (0 < (int)_LpSrcStr) {
    pCVar3 = (LPCSTR)___strncnt((char *)_DwMapFlag,(int)_LpSrcStr);
    cbMultiByte = pCVar3 + 1;
    if ((int)_LpSrcStr <= (int)pCVar3) {
      cbMultiByte = pCVar3;
    }
  }
  iVar8 = 0;
  iVar4 = MultiByteToWideChar(_CchDest,(uint)(_Code_page != 0) * 8 + 1,(LPCSTR)_DwMapFlag,
                              (int)cbMultiByte,(LPWSTR)0x0,0);
  if (iVar4 == 0) {
    return 0;
  }
  uVar2 = iVar4 * 2;
  uVar1 = uVar2 + 8;
  if ((uVar1 & -(uint)(uVar2 < uVar1)) == 0) {
    local_c = (LPCWSTR)0x0;
  }
  else if ((-(uint)(uVar2 < uVar1) & uVar1) < 0x401) {
    pWVar7 = (LPCWSTR)&stack0xffffffe4;
    local_c = (LPCWSTR)&stack0xffffffe4;
    if (&stack0x00000000 != (undefined1 *)0x1c) {
LAB_004593d0:
      local_c = pWVar7 + 4;
    }
  }
  else {
    pWVar7 = __malloc_base(-(uint)(uVar2 < uVar2 + 8) & uVar2 + 8);
    local_c = pWVar7;
    if (pWVar7 != (LPCWSTR)0x0) {
      pWVar7[0] = L'\xdddd';
      pWVar7[1] = L'\0';
      goto LAB_004593d0;
    }
  }
  if (((local_c == (LPCWSTR)0x0) ||
      (iVar5 = MultiByteToWideChar(_CchDest,1,(LPCSTR)_DwMapFlag,(int)cbMultiByte,local_c,iVar4),
      iVar5 == 0)) ||
     (iVar5 = ___crtLCMapStringEx((LPCWSTR)_Plocinfo,(DWORD)_LocaleName,local_c,iVar4,(LPWSTR)0x0,0)
     , iVar5 == 0)) goto LAB_00459502;
  if (((uint)_LocaleName & 0x400) != 0) {
    iVar8 = iVar5;
    if ((_LpDestStr != (LPSTR)0x0) && (iVar5 <= (int)_LpDestStr)) {
      ___crtLCMapStringEx((LPCWSTR)_Plocinfo,(DWORD)_LocaleName,local_c,iVar4,(LPWSTR)_CchSrc,
                          (int)_LpDestStr);
    }
    goto LAB_00459502;
  }
  uVar2 = iVar5 * 2;
  uVar1 = uVar2 + 8;
  if ((uVar1 & -(uint)(uVar2 < uVar1)) == 0) {
    pWVar7 = (LPCWSTR)0x0;
LAB_004594ad:
    if ((pWVar7 != (LPCWSTR)0x0) &&
       (iVar4 = ___crtLCMapStringEx((LPCWSTR)_Plocinfo,(DWORD)_LocaleName,local_c,iVar4,pWVar7,iVar5
                                   ), iVar4 != 0)) {
      if (_LpDestStr == (LPSTR)0x0) {
        _LpDestStr = (LPSTR)0x0;
        _CchSrc = 0;
      }
      iVar4 = WideCharToMultiByte(_CchDest,0,pWVar7,iVar5,(LPSTR)_CchSrc,(int)_LpDestStr,(LPCSTR)0x0
                                  ,(LPBOOL)0x0);
      iVar5 = iVar8;
      if (iVar4 != 0) {
        __freea_crt((int)pWVar7);
        iVar8 = iVar4;
        goto LAB_00459502;
      }
    }
  }
  else if ((-(uint)(uVar2 < uVar1) & uVar1) < 0x401) {
    puVar6 = (undefined4 *)&stack0xffffffe4;
    pWVar7 = (LPCWSTR)&stack0xffffffe4;
    if (&stack0x00000000 != (undefined1 *)0x1c) {
LAB_004594a6:
      pWVar7 = (LPCWSTR)(puVar6 + 2);
      goto LAB_004594ad;
    }
  }
  else {
    puVar6 = __malloc_base(-(uint)(uVar2 < uVar2 + 8) & uVar2 + 8);
    pWVar7 = (LPCWSTR)0x0;
    if (puVar6 != (undefined4 *)0x0) {
      *puVar6 = 0xdddd;
      goto LAB_004594a6;
    }
  }
  iVar8 = iVar5;
  __freea_crt((int)pWVar7);
LAB_00459502:
  __freea_crt((int)local_c);
  return iVar8;
}



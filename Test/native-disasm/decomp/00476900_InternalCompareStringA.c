// InternalCompareStringA @ 00476900 size=680 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* Library Function - Single Match
    int __cdecl InternalCompareStringA(struct __crt_locale_pointers *,wchar_t const *,unsigned
   long,char const *,int,char const *,int,int)
   
   Library: Visual Studio 2015 Release */

int __cdecl
InternalCompareStringA
          (__crt_locale_pointers *param_1,wchar_t *param_2,ulong param_3,char *param_4,int param_5,
          char *param_6,int param_7,int param_8)

{
  uint uVar1;
  BOOL BVar2;
  int cchWideChar;
  wchar_t *pwVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  BYTE *pBVar7;
  LPWSTR lpWideCharStr;
  int iVar8;
  wchar_t *local_20;
  _cpinfo local_1c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  if (param_5 < 1) {
    if (param_5 < -1) {
      return 0;
    }
  }
  else {
    param_5 = ___strncnt(param_4,param_5);
  }
  if (param_7 < 1) {
    if (param_7 < -1) {
      return 0;
    }
  }
  else {
    param_7 = ___strncnt(param_6,param_7);
  }
  if (param_8 == 0) {
    param_8 = *(int *)(*(int *)param_1 + 8);
  }
  if ((param_5 == 0) || (param_7 == 0)) {
    if (param_5 == param_7) {
      return 2;
    }
    if (1 < param_7) {
      return 1;
    }
    if (1 < param_5) {
      return 3;
    }
    BVar2 = GetCPInfo(param_8,&local_1c);
    if (BVar2 == 0) {
      return 0;
    }
    if (0 < param_5) {
      if (local_1c.MaxCharSize < 2) {
        return 3;
      }
      pBVar7 = local_1c.LeadByte;
      while( true ) {
        if (local_1c.LeadByte[0] == 0) {
          return 3;
        }
        if (pBVar7[1] == 0) break;
        if ((*pBVar7 <= (byte)*param_4) && ((byte)*param_4 <= pBVar7[1])) {
          return 2;
        }
        pBVar7 = pBVar7 + 2;
        local_1c.LeadByte[0] = *pBVar7;
      }
      return 3;
    }
    if (0 < param_7) {
      if (local_1c.MaxCharSize < 2) {
        return 1;
      }
      pBVar7 = local_1c.LeadByte;
      while( true ) {
        if (local_1c.LeadByte[0] == 0) {
          return 1;
        }
        if (pBVar7[1] == 0) break;
        if ((*pBVar7 <= (byte)*param_6) && ((byte)*param_6 <= pBVar7[1])) {
          return 2;
        }
        pBVar7 = pBVar7 + 2;
        local_1c.LeadByte[0] = *pBVar7;
      }
      return 1;
    }
  }
  iVar8 = 0;
  cchWideChar = MultiByteToWideChar(param_8,9,param_4,param_5,(LPWSTR)0x0,0);
  if (cchWideChar == 0) {
    return 0;
  }
  uVar1 = cchWideChar * 2;
  if ((uVar1 + 8 & -(uint)(uVar1 < uVar1 + 8)) == 0) {
    local_20 = (wchar_t *)0x0;
  }
  else {
    if ((-(uint)(uVar1 < uVar1 + 8) & uVar1 + 8) < 0x401) {
      pwVar3 = (wchar_t *)&stack0xffffffc4;
      local_20 = (wchar_t *)&stack0xffffffc4;
      if (&stack0x00000000 == (undefined1 *)0x3c) goto LAB_00476b8b;
    }
    else {
      pwVar3 = __malloc_base(-(uint)(uVar1 < uVar1 + 8) & uVar1 + 8);
      local_20 = pwVar3;
      if (pwVar3 == (wchar_t *)0x0) goto LAB_00476b8b;
      pwVar3[0] = L'\xdddd';
      pwVar3[1] = L'\0';
    }
    local_20 = pwVar3 + 4;
  }
  if (((local_20 == (wchar_t *)0x0) ||
      (iVar4 = MultiByteToWideChar(param_8,1,param_4,param_5,local_20,cchWideChar), iVar4 == 0)) ||
     (iVar4 = MultiByteToWideChar(param_8,9,param_6,param_7,(LPWSTR)0x0,0), iVar4 == 0))
  goto LAB_00476b8b;
  uVar1 = iVar4 * 2;
  if ((uVar1 + 8 & -(uint)(uVar1 < uVar1 + 8)) == 0) {
    lpWideCharStr = (LPWSTR)0x0;
LAB_00476b44:
    if ((lpWideCharStr != (LPWSTR)0x0) &&
       (iVar6 = MultiByteToWideChar(param_8,1,param_6,param_7,lpWideCharStr,iVar4), iVar6 != 0)) {
      iVar8 = ___acrt_CompareStringEx_36
                        (param_2,param_3,local_20,cchWideChar,lpWideCharStr,iVar4,
                         (_nlsversioninfo *)0x0,(void *)0x0,0);
    }
  }
  else if ((-(uint)(uVar1 < uVar1 + 8) & uVar1 + 8) < 0x401) {
    puVar5 = (undefined4 *)&stack0xffffffc4;
    lpWideCharStr = (LPWSTR)&stack0xffffffc4;
    if (&stack0x00000000 != (undefined1 *)0x3c) {
LAB_00476b3d:
      lpWideCharStr = (LPWSTR)(puVar5 + 2);
      goto LAB_00476b44;
    }
  }
  else {
    puVar5 = __malloc_base(-(uint)(uVar1 < uVar1 + 8) & uVar1 + 8);
    lpWideCharStr = (LPWSTR)0x0;
    if (puVar5 != (undefined4 *)0x0) {
      *puVar5 = 0xdddd;
      goto LAB_00476b3d;
    }
  }
  __freea_crt((int)lpWideCharStr);
LAB_00476b8b:
  __freea_crt((int)local_20);
  return iVar8;
}



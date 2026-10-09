// FUN_00467f9b @ 00467f9b size=302 callers=1

undefined4 __cdecl FUN_00467f9b(wchar_t *param_1,wchar_t *param_2)

{
  wchar_t wVar1;
  int iVar2;
  size_t sVar3;
  wchar_t *pwVar4;
  uint uVar5;
  int local_8;
  
  _memset(param_1,0,0x1ca);
  if (*param_2 == L'\0') {
    return 0;
  }
  if ((*param_2 == L'.') && (param_2[1] != L'\0')) {
    iVar2 = FUN_0047002f(param_1 + 0x80,0x10,param_2 + 1,0xf);
    if (iVar2 == 0) {
      param_1[0x8f] = L'\0';
      return 0;
    }
  }
  else {
    local_8 = 0;
    while( true ) {
      sVar3 = _wcscspn(param_2,L"_.,");
      if (sVar3 == 0) {
        return 0xffffffff;
      }
      wVar1 = param_2[sVar3];
      if (local_8 == 0) {
        if (0x3f < sVar3) {
          return 0xffffffff;
        }
        if (wVar1 == L'.') {
          return 0xffffffff;
        }
        uVar5 = 0x40;
        pwVar4 = param_1;
      }
      else if (local_8 == 1) {
        if (0x3f < sVar3) {
          return 0xffffffff;
        }
        if (wVar1 == L'_') {
          return 0xffffffff;
        }
        uVar5 = 0x40;
        pwVar4 = param_1 + 0x40;
      }
      else {
        if (local_8 != 2) {
          return 0xffffffff;
        }
        if (0xf < sVar3) {
          return 0xffffffff;
        }
        if ((wVar1 != L'\0') && (wVar1 != L',')) {
          return 0xffffffff;
        }
        uVar5 = 0x10;
        pwVar4 = param_1 + 0x80;
      }
      iVar2 = FUN_0047002f(pwVar4,uVar5,param_2,sVar3);
      if (iVar2 != 0) break;
      if (wVar1 == L',') {
        return 0;
      }
      if (wVar1 == L'\0') {
        return 0;
      }
      param_2 = param_2 + sVar3 + 1;
      local_8 = local_8 + 1;
    }
  }
                    /* WARNING: Subroutine does not return */
  __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
}



// FUN_0040eff0 @ 0040eff0 size=262 callers=1

int FUN_0040eff0(void)

{
  bool bVar1;
  bool bVar2;
  LSTATUS LVar3;
  HKEY local_8;
  DWORD local_4;
  
  if (DAT_004a239a != '\0') {
    return DAT_0049d9c8;
  }
  bVar1 = 0 < DAT_0049d9c8;
  DAT_004a2390 = DAT_004a2390 + 1;
  if ((DAT_004a2390 < 9) || (999 < DAT_0049d9c8)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if ((bVar1) && (!bVar2)) {
    return DAT_0049d9c8;
  }
  LVar3 = RegOpenKeyExA((HKEY)&DAT_80000001,"Control Panel\\Desktop",0,3,&local_8);
  if (LVar3 == 0) {
    if (!bVar1) {
      local_4 = 4;
      LVar3 = RegQueryValueExA(local_8,"LowLevelHooksTimeout",(LPDWORD)0x0,(LPDWORD)0x0,
                               (LPBYTE)&DAT_0049d9c8,&local_4);
      if (LVar3 != 0) {
        DAT_0049d9c8 = -1;
      }
    }
    if (bVar2) {
      local_4 = 1000;
      if (DAT_0049d9c8 < 500) {
        local_4 = 500;
      }
      LVar3 = RegSetValueExA(local_8,"LowLevelHooksTimeout",0,4,(BYTE *)&local_4,4);
      DAT_004a239a = LVar3 == 0;
    }
    RegCloseKey(local_8);
  }
  return DAT_0049d9c8;
}



// _LcidFromHexString @ 00472e44 size=81 callers=3

/* Library Function - Single Match
    _LcidFromHexString
   
   Library: Visual Studio 2015 Release */

int __cdecl _LcidFromHexString(ushort *param_1)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = 0;
  uVar1 = *param_1;
  while (uVar1 != 0) {
    param_1 = param_1 + 1;
    if ((ushort)(uVar1 - 0x61) < 6) {
      uVar1 = uVar1 - 0x27;
    }
    else if ((ushort)(uVar1 - 0x41) < 6) {
      uVar1 = uVar1 - 7;
    }
    iVar2 = iVar2 * 0x10 + (uVar1 - 0x30);
    uVar1 = *param_1;
  }
  return iVar2;
}



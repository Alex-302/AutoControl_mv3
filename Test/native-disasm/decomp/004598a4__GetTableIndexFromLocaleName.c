// _GetTableIndexFromLocaleName @ 004598a4 size=78 callers=1

/* Library Function - Single Match
    _GetTableIndexFromLocaleName
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl _GetTableIndexFromLocaleName(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = 0xe3;
  do {
    iVar3 = (iVar2 + iVar4) / 2;
    iVar1 = ___wcsnicmp_ascii(param_1,*(ushort **)(&UNK_00481f18 + iVar3 * 8),0x55);
    if (iVar1 == 0) {
      return *(undefined4 *)(&UNK_00481f1c + iVar3 * 8);
    }
    if (iVar1 < 0) {
      iVar2 = iVar3 + -1;
    }
    else {
      iVar4 = iVar3 + 1;
    }
  } while (iVar4 <= iVar2);
  return 0xffffffff;
}



// ___wcsnicmp_ascii @ 004599c8 size=115 callers=1

/* Library Function - Single Match
    ___wcsnicmp_ascii
   
   Library: Visual Studio 2015 Release */

int __cdecl ___wcsnicmp_ascii(int param_1,ushort *param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  
  iVar2 = 0;
  if (param_3 != 0) {
    iVar2 = param_1 - (int)param_2;
    do {
      uVar3 = *(ushort *)(iVar2 + (int)param_2);
      if ((0x40 < uVar3) && (uVar3 < 0x5b)) {
        uVar3 = uVar3 + 0x20;
      }
      uVar1 = *param_2;
      if ((0x40 < uVar1) && (uVar1 < 0x5b)) {
        uVar1 = uVar1 + 0x20;
      }
      param_2 = param_2 + 1;
      param_3 = param_3 + -1;
    } while (((param_3 != 0) && (uVar3 != 0)) && (uVar3 == uVar1));
    iVar2 = (uint)uVar3 - (uint)uVar1;
  }
  return iVar2;
}



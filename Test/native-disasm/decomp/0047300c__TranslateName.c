// _TranslateName @ 0047300c size=93 callers=2

/* Library Function - Single Match
    _TranslateName
   
   Library: Visual Studio 2015 Release */

uint __cdecl _TranslateName(int param_1,int param_2,int *param_3)

{
  uint in_EAX;
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  if (-1 < param_2) {
    do {
      iVar2 = (iVar1 + param_2) / 2;
      in_EAX = __wcsicmp((wchar_t *)*param_3,*(wchar_t **)(iVar2 * 0xc + param_1));
      if (in_EAX == 0) {
        iVar1 = iVar2 * 0xc + param_1 + 4;
        *param_3 = iVar1;
        return CONCAT31((int3)((uint)iVar1 >> 8),1);
      }
      if ((int)in_EAX < 0) {
        param_2 = iVar2 + -1;
      }
      else {
        iVar1 = iVar2 + 1;
      }
    } while (iVar1 <= param_2);
  }
  return in_EAX & 0xffffff00;
}



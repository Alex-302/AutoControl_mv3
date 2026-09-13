// force_decimal_point @ 004649f9 size=92 callers=1

/* Library Function - Single Match
    void __cdecl __crt_stdio_output::force_decimal_point(char *,struct __crt_locale_pointers *
   const)
   
   Library: Visual Studio 2015 Release */

void __cdecl __crt_stdio_output::force_decimal_point(char *param_1,__crt_locale_pointers *param_2)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  bool bVar4;
  
  iVar2 = _tolower((int)*param_1);
  bVar4 = iVar2 == 0x65;
  while (!bVar4) {
    param_1 = param_1 + 1;
    iVar2 = _isdigit((uint)(byte)*param_1);
    bVar4 = iVar2 == 0;
  }
  iVar2 = _tolower((int)*param_1);
  if (iVar2 == 0x78) {
    param_1 = param_1 + 2;
  }
  bVar3 = *param_1;
  *param_1 = *(byte *)**(undefined4 **)(*(int *)param_2 + 0x88);
  do {
    param_1 = param_1 + 1;
    bVar1 = *param_1;
    *param_1 = bVar3;
    bVar3 = bVar1;
  } while (*param_1 != 0);
  return;
}



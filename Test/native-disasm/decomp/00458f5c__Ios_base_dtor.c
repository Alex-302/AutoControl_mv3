// _Ios_base_dtor @ 00458f5c size=64 callers=9

/* Library Function - Single Match
    private: static void __cdecl std::ios_base::_Ios_base_dtor(class std::ios_base *)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

void __cdecl std::ios_base::_Ios_base_dtor(ios_base *param_1)

{
  int iVar1;
  void *pvVar2;
  
  iVar1 = *(int *)(param_1 + 8);
  if ((iVar1 == 0) ||
     ((&DAT_0049ef84)[iVar1] = (&DAT_0049ef84)[iVar1] + -1, (char)(&DAT_0049ef84)[iVar1] < '\x01'))
  {
    _Tidy(param_1);
    pvVar2 = *(void **)(param_1 + 0x30);
    if (pvVar2 != (void *)0x0) {
      FUN_00402800((int)pvVar2);
      FUN_0045a6a4(pvVar2);
    }
  }
  return;
}



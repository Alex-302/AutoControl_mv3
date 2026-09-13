// __chvalidchk_l @ 0045fba3 size=42 callers=1

/* Library Function - Single Match
    __chvalidchk_l
   
   Library: Visual Studio 2015 Release */

ushort __cdecl __chvalidchk_l(int param_1,ushort param_2,undefined4 *param_3)

{
  ushort uVar1;
  ushort *puVar2;
  
  if (param_3 == (undefined4 *)0x0) {
    puVar2 = ___pctype_func();
    uVar1 = puVar2[param_1];
  }
  else {
    uVar1 = *(ushort *)(*(int *)*param_3 + param_1 * 2);
  }
  return uVar1 & param_2;
}



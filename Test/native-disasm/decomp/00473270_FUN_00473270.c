// FUN_00473270 @ 00473270 size=120 callers=5

LPVOID __cdecl FUN_00473270(LPCVOID param_1,uint param_2,uint param_3)

{
  int *piVar1;
  LPVOID pvVar2;
  SIZE_T SVar3;
  uint uVar4;
  
  if ((param_2 == 0) || (param_3 <= 0xffffffe0 / param_2)) {
    if (param_1 == (LPCVOID)0x0) {
      SVar3 = 0;
    }
    else {
      SVar3 = FUN_00476251(param_1);
    }
    uVar4 = param_2 * param_3;
    pvVar2 = __realloc_base(param_1,uVar4);
    if ((pvVar2 != (LPVOID)0x0) && (SVar3 < uVar4)) {
      _memset((void *)((int)pvVar2 + SVar3),0,uVar4 - SVar3);
    }
  }
  else {
    piVar1 = __errno();
    *piVar1 = 0xc;
    pvVar2 = (LPVOID)0x0;
  }
  return pvVar2;
}



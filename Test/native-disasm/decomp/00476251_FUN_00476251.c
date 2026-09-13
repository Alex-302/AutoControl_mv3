// FUN_00476251 @ 00476251 size=51 callers=1

SIZE_T __cdecl FUN_00476251(LPCVOID param_1)

{
  int *piVar1;
  SIZE_T SVar2;
  
  if (param_1 == (LPCVOID)0x0) {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
    return 0xffffffff;
  }
  SVar2 = HeapSize(DAT_0049fb20,0,param_1);
  return SVar2;
}



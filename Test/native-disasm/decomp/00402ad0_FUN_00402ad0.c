// FUN_00402ad0 @ 00402ad0 size=62 callers=1

byte * __thiscall FUN_00402ad0(void *this,byte *param_1,byte *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (int)param_2 - (int)param_1;
  iVar3 = 0;
  if (param_2 < param_1) {
    iVar2 = 0;
  }
  if (iVar2 != 0) {
    do {
      iVar1 = __Toupper((uint)*param_1,(_Ctypevec *)((int)this + 8));
      *param_1 = (byte)iVar1;
      iVar3 = iVar3 + 1;
      param_1 = param_1 + 1;
    } while (iVar3 != iVar2);
  }
  return param_1;
}



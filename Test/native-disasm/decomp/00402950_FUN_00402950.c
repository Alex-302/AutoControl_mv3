// FUN_00402950 @ 00402950 size=80 callers=2

byte * __thiscall FUN_00402950(void *this,byte *param_1,byte *param_2)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  if (*(undefined ***)this != std::ctype<char>::vftable) {
                    /* WARNING: Could not recover jumptable at 0x0040299e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    pbVar2 = (byte *)(*(code *)(*(undefined ***)this)[3])();
    return pbVar2;
  }
  iVar3 = (int)param_2 - (int)param_1;
  iVar4 = 0;
  if (param_2 < param_1) {
    iVar3 = 0;
  }
  if (iVar3 != 0) {
    do {
      iVar1 = __Tolower((uint)*param_1,(_Ctypevec *)((int)this + 8));
      *param_1 = (byte)iVar1;
      iVar4 = iVar4 + 1;
      param_1 = param_1 + 1;
    } while (iVar4 != iVar3);
  }
  return param_1;
}



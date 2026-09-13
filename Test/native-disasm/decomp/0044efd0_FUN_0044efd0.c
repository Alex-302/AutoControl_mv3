// FUN_0044efd0 @ 0044efd0 size=127 callers=3

byte * __fastcall
FUN_0044efd0(byte *param_1,byte *param_2,byte *param_3,byte *param_4,int param_5,uint param_6)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  bool bVar4;
  
  if ((param_6 & 0x100) != 0) {
    pbVar3 = FUN_00452ba0(param_1,param_2,param_3,param_4,param_5);
    return pbVar3;
  }
  pbVar3 = param_1;
  if ((param_6 & 0x800) != 0) {
    pbVar3 = (byte *)FUN_00452c60((char *)param_1,(char *)param_2,(char *)param_3,(char *)param_4);
    return pbVar3;
  }
  while (pbVar3 != param_2) {
    bVar4 = true;
    if (param_3 == param_4) goto LAB_0044f044;
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 1;
    bVar2 = *param_3;
    param_3 = param_3 + 1;
    if (bVar1 != bVar2) {
      return param_1;
    }
  }
  bVar4 = param_3 == param_4;
LAB_0044f044:
  if (!bVar4) {
    return param_1;
  }
  return pbVar3;
}



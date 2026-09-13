// FUN_0044ee50 @ 0044ee50 size=168 callers=2

undefined4 * __fastcall
FUN_0044ee50(undefined4 *param_1,byte *param_2,byte *param_3,byte *param_4,byte *param_5,int param_6
            ,uint param_7)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  undefined4 *puVar4;
  bool bVar5;
  
  *param_1 = param_4;
  if ((param_7 & 0x100) != 0) {
    puVar4 = (undefined4 *)FUN_00452a60(&param_7,param_2,param_3,param_4,param_5,param_6);
    *param_1 = *puVar4;
    return param_1;
  }
  pbVar3 = param_3;
  if ((param_7 & 0x800) != 0) {
    puVar4 = (undefined4 *)
             FUN_00452b30(&param_7,(char *)param_2,(char *)param_3,(char *)param_4,(char *)param_5);
    *param_1 = *puVar4;
    return param_1;
  }
  do {
    if (pbVar3 == param_4) {
      bVar5 = param_2 == param_5;
LAB_0044eee7:
      if (bVar5) {
        param_3 = pbVar3;
      }
      break;
    }
    bVar5 = true;
    if (param_2 == param_5) goto LAB_0044eee7;
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    bVar2 = *pbVar3;
    pbVar3 = pbVar3 + 1;
  } while (bVar2 == bVar1);
  *param_1 = param_3;
  return param_1;
}



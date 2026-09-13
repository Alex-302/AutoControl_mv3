// FUN_00452940 @ 00452940 size=130 callers=1

undefined4 * __fastcall
FUN_00452940(undefined4 *param_1,int param_2,byte *param_3,byte *param_4,byte *param_5,byte *param_6
            ,uint param_7)

{
  undefined4 *puVar1;
  
  *param_1 = param_4;
  if ((param_7 & 0x100) != 0) {
    puVar1 = FUN_00454da0(&param_7,param_3,param_4,param_5,param_6,param_2);
    *param_1 = *puVar1;
    return param_1;
  }
  if ((param_7 & 0x800) != 0) {
    puVar1 = FUN_00454e60(&param_7,(char *)param_3,(char *)param_4,(char *)param_5,(char *)param_6);
    *param_1 = *puVar1;
    return param_1;
  }
  puVar1 = FUN_00454ec0(&param_7,(char *)param_3,(char *)param_4,(char *)param_5,(char *)param_6);
  *param_1 = *puVar1;
  return param_1;
}



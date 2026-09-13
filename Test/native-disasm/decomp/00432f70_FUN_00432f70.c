// FUN_00432f70 @ 00432f70 size=66 callers=1

byte * FUN_00432f70(byte *param_1)

{
  byte *pbVar1;
  void *this;
  byte *local_8 [2];
  
  pbVar1 = param_1;
  FUN_00448eb0(&param_1,param_1);
  if (param_1 == DAT_004a27b4) {
    param_1 = pbVar1;
    FUN_0044a7a0(this,(int *)local_8,this,&param_1);
    param_1 = local_8[0];
  }
  return param_1 + 0xc;
}



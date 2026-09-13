// FUN_00432630 @ 00432630 size=74 callers=3

byte * __thiscall FUN_00432630(void *this,byte *param_1)

{
  undefined4 extraout_ECX;
  byte *local_14;
  byte *local_10 [3];
  
  FUN_00436020(this,(int *)&local_14,param_1);
  if (local_14 == *(byte **)((int)this + 4)) {
    local_14 = param_1;
    FUN_0044a540(this,(int *)local_10,extraout_ECX,&local_14);
    local_14 = local_10[0];
  }
  return local_14 + 0x20;
}



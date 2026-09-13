// FUN_00435380 @ 00435380 size=54 callers=1

void __thiscall FUN_00435380(void *this,byte *param_1)

{
  byte bVar1;
  byte *pbVar2;
  
  if (*param_1 == 0) {
    FUN_0043aad0(this,param_1,this,0);
    return;
  }
  pbVar2 = param_1;
  do {
    bVar1 = *pbVar2;
    pbVar2 = pbVar2 + 1;
  } while (bVar1 != 0);
  FUN_0043aad0(this,param_1,this,(int)pbVar2 - (int)(param_1 + 1));
  return;
}



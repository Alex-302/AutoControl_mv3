// FUN_0044d580 @ 0044d580 size=108 callers=1

void __thiscall FUN_0044d580(void *this,byte *param_1)

{
  byte bVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  byte *pbVar5;
  ulonglong local_10;
  undefined4 local_8;
  undefined4 local_4;
  
  bVar1 = *param_1;
  uVar3 = *(undefined4 *)(param_1 + 8);
  uVar4 = *(undefined4 *)(param_1 + 0xc);
  *param_1 = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  pbVar5 = *(byte **)((int)this + 4);
  bVar2 = *pbVar5;
  *pbVar5 = bVar1;
  local_4 = *(undefined4 *)(pbVar5 + 0xc);
  local_10 = (ulonglong)bVar2;
  local_8 = *(undefined4 *)(pbVar5 + 8);
  *(undefined4 *)(pbVar5 + 8) = uVar3;
  *(undefined4 *)(pbVar5 + 0xc) = uVar4;
  FUN_00434820((char *)&local_10);
  SetEvent((HANDLE)**(undefined4 **)((int)this + 8));
  return;
}



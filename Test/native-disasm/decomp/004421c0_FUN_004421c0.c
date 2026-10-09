// FUN_004421c0 @ 004421c0 size=64 callers=1

uint __fastcall FUN_004421c0(int param_1,char *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  char *extraout_ECX;
  char local_18 [8];
  undefined8 local_10;
  
  local_18[0] = '\0';
  local_10 = 0;
  FUN_00450f50(local_18,param_1);
  uVar1 = FUN_004441e0(extraout_ECX,param_2);
  uVar2 = FUN_00434820(local_18);
  return CONCAT31((int3)((uint)uVar2 >> 8),(char)uVar1);
}



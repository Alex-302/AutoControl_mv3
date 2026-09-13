// FUN_004454f0 @ 004454f0 size=262 callers=1

undefined4 __thiscall FUN_004454f0(void *this,undefined1 *param_1,int param_2)

{
  bool bVar1;
  short sVar2;
  uint uVar3;
  uint3 extraout_var;
  undefined2 extraout_var_00;
  undefined4 local_18;
  undefined4 local_14;
  undefined8 local_10;
  
  local_18 = *(undefined4 *)((int)this + 0x38);
  local_14 = *(undefined4 *)((int)this + 0x40);
  if (param_2 == 5) {
    uVar3 = FUN_00448280(&local_18,&local_10);
    if ((char)uVar3 != '\0') {
      *(undefined4 *)(param_1 + 8) = (undefined4)local_10;
      *(undefined4 *)(param_1 + 0xc) = local_10._4_4_;
      *param_1 = 6;
      return CONCAT31((int3)((ulonglong)local_10 >> 0x28),1);
    }
  }
  else if (param_2 == 6) {
    uVar3 = FUN_0044ae70(&local_18,&local_10);
    if ((char)uVar3 != '\0') {
      *(undefined4 *)(param_1 + 8) = (undefined4)local_10;
      *(undefined4 *)(param_1 + 0xc) = local_10._4_4_;
      *param_1 = 5;
      return CONCAT31((int3)((ulonglong)local_10 >> 0x28),1);
    }
  }
  bVar1 = FUN_0044aef0(&local_18,(double *)&local_10);
  if (bVar1) {
    *(undefined4 *)(param_1 + 8) = (undefined4)local_10;
    *(undefined4 *)(param_1 + 0xc) = local_10._4_4_;
    local_10 = *(double *)(param_1 + 8);
    *param_1 = 7;
    sVar2 = FID_conflict___dtest((double *)&local_10);
    local_10._4_4_ = CONCAT22(extraout_var_00,sVar2);
    if (0 < sVar2) {
      *param_1 = 0;
      *(undefined4 *)(param_1 + 8) = 0;
      local_10._4_4_ = 0;
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
    return CONCAT31((int3)((uint)local_10._4_4_ >> 8),1);
  }
  return (uint)extraout_var << 8;
}



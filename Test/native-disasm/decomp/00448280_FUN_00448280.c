// FUN_00448280 @ 00448280 size=86 callers=1

uint __thiscall FUN_00448280(void *this,ulonglong *param_1)

{
  int *piVar1;
  ulonglong uVar2;
  int *local_4;
  
  local_4 = (int *)0x0;
  piVar1 = __errno();
  *piVar1 = 0;
  uVar2 = FID_conflict__strtoull(*(char **)this,(char **)&local_4,10);
  *param_1 = uVar2;
  piVar1 = __errno();
  if (((*piVar1 == 0) && (piVar1 = *(int **)((int)this + 4), *(int **)this < piVar1)) &&
     (local_4 == piVar1)) {
    return CONCAT31((int3)((uint)piVar1 >> 8),1);
  }
  return (uint)piVar1 & 0xffffff00;
}



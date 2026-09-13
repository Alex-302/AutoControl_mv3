// FUN_0044ae70 @ 0044ae70 size=128 callers=1

uint __thiscall FUN_0044ae70(void *this,longlong *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  int *local_4;
  
  local_4 = (int *)0x0;
  piVar1 = __errno();
  *piVar1 = 0;
  lVar4 = FID_conflict___strtoi64(*(char **)this,(char **)&local_4,10);
  iVar3 = (int)((ulonglong)lVar4 >> 0x20);
  *param_1 = lVar4;
  if ((iVar3 != 0 && -1 < lVar4) || (-1 < lVar4)) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1 = (int *)0x1;
  }
  if ((iVar3 != 0 && -1 < lVar4) || (-1 < lVar4)) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = (int *)0x1;
  }
  if ((((piVar1 == piVar2) && (piVar2 = __errno(), *piVar2 == 0)) &&
      (piVar2 = *(int **)((int)this + 4), *(int **)this < piVar2)) && (local_4 == piVar2)) {
    return CONCAT31((int3)((uint)piVar2 >> 8),1);
  }
  return (uint)piVar2 & 0xffffff00;
}



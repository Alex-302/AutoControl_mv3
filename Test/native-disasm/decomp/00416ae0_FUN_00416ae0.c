// FUN_00416ae0 @ 00416ae0 size=240 callers=2

undefined1 * __thiscall FUN_00416ae0(void *this,undefined1 *param_1)

{
  bool bVar1;
  bool bVar2;
  SIZE_T SVar3;
  void **ppvVar4;
  void *local_38 [4];
  undefined4 local_28;
  uint local_24;
  void *local_20 [4];
  undefined4 local_10;
  uint local_c;
  
  if ((*(HGLOBAL *)this == (HGLOBAL)0x0) || (*(int *)((int)this + 4) == 0)) {
    local_24 = 0xf;
    ppvVar4 = local_38;
    local_28 = 0;
    bVar2 = false;
    bVar1 = true;
    local_38[0] = (void *)((uint)local_38[0] & 0xffffff00);
  }
  else {
    SVar3 = GlobalSize(*(HGLOBAL *)this);
    local_c = 0xf;
    local_10 = 0;
    local_20[0] = (void *)((uint)local_20[0] & 0xffffff00);
    FUN_0043ace0(local_20,*(uint **)((int)this + 4),SVar3);
    ppvVar4 = local_20;
    bVar2 = true;
    bVar1 = false;
  }
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  FUN_0043b1c0(param_1,(uint *)ppvVar4);
  if (bVar1) {
    if (0xf < local_24) {
      FUN_00402430(local_38[0],local_24 + 1,1);
    }
    local_24 = 0xf;
    local_28 = 0;
    local_38[0] = (void *)((uint)local_38[0] & 0xffffff00);
  }
  if ((bVar2) && (0xf < local_c)) {
    FUN_00402430(local_20[0],local_c + 1,1);
  }
  return param_1;
}



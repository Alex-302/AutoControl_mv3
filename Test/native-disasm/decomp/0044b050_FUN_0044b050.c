// FUN_0044b050 @ 0044b050 size=202 callers=1

void * __thiscall
FUN_0044b050(void *this,int param_1,int param_2,undefined1 *param_3,undefined1 *param_4)

{
  bool bVar1;
  undefined4 ****ppppuVar2;
  void *pvVar3;
  undefined4 ***local_28 [4];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c658;
  local_10 = ExceptionList;
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (undefined4 ***)((uint)local_28[0] & 0xffffff00);
  ExceptionList = &local_10;
  if (((int)param_4 - (int)param_3 != 0xf) &&
     (ExceptionList = &local_10, bVar1 = FUN_0043de20(local_28,(int)param_4 - (int)param_3,'\x01'),
     bVar1)) {
    local_18 = 0;
    ppppuVar2 = local_28;
    if (0xf < local_14) {
      ppppuVar2 = (undefined4 ****)local_28[0];
    }
    *(undefined1 *)ppppuVar2 = 0;
  }
  FUN_00454bb0(local_28,param_3,param_4);
  local_8 = 0;
  pvVar3 = this;
  if (0xf < *(uint *)((int)this + 0x14)) {
    pvVar3 = *(void **)this;
  }
  FUN_004401f0(this,(void *)(param_1 - (int)pvVar3),(void *)(param_2 - param_1),local_28,0,
               (void *)0xffffffff);
  if (0xf < local_14) {
    FUN_00402430(local_28[0],local_14 + 1,1);
  }
  ExceptionList = local_10;
  return this;
}



// FUN_00414d10 @ 00414d10 size=172 callers=1

uint * __fastcall FUN_00414d10(int *param_1)

{
  uint *this;
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  void *local_28 [5];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  this = (uint *)(param_1 + 5);
  ExceptionList = &local_10;
  uVar1 = FUN_00444360(this,(ushort *)&DAT_0048d5bc);
  if (uVar1 == 0) {
    puVar2 = FUN_0040bdf0(local_28,param_1);
    if (this != puVar2) {
      if (7 < (uint)param_1[10]) {
        FUN_00402430((void *)*this,param_1[10] + 1,2);
      }
      param_1[10] = 7;
      param_1[9] = 0;
      puVar3 = this;
      if (7 < (uint)param_1[10]) {
        puVar3 = (uint *)*this;
      }
      *(undefined2 *)puVar3 = 0;
      FUN_0043a920(this,puVar2);
    }
    if (7 < local_14) {
      FUN_00402430(local_28[0],local_14 + 1,2);
    }
  }
  ExceptionList = local_10;
  return this;
}



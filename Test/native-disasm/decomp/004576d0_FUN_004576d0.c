// FUN_004576d0 @ 004576d0 size=143 callers=1

void __thiscall FUN_004576d0(void *this,undefined4 *param_1)

{
  undefined4 *this_00;
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_1c;
  void *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puVar3 = param_1;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ec16;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffd8;
  ExceptionList = &local_10;
  *(undefined4 *)((int)this + 0x18) = param_1[6];
  *(undefined4 *)((int)this + 0x1c) = param_1[7];
  local_18 = this;
  FUN_0043e550((int *)((int)this + 4));
  local_8 = 0;
  this_00 = (undefined4 *)((int)this + 0xc);
  *(undefined4 *)this = *puVar3;
  param_1 = *(undefined4 **)((int)this + 4);
  iVar1 = puVar3[4];
  iVar2 = puVar3[3];
  *(undefined4 *)((int)this + 0x10) = *this_00;
  FUN_0043fa20(this_00,&local_1c,(uint *)*this_00,iVar1 - iVar2 >> 2,&param_1);
  FUN_00457e00(this,*(undefined4 **)puVar3[1],(undefined4 *)puVar3[1]);
  ExceptionList = local_10;
  return;
}



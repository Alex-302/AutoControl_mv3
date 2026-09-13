// FUN_00419030 @ 00419030 size=102 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00419030(void *this,undefined4 *param_1,undefined4 param_2)

{
  float fVar1;
  
  fVar1 = DAT_004a2848 * _DAT_0048f264;
  DAT_004a23e0 = *param_1;
  DAT_004a23e4 = param_1[1];
  *(undefined2 *)((int)this + 0x36) = 0x4901;
  *(undefined4 *)((int)this + 0x28) = param_2;
  *(undefined4 *)((int)this + 0x18) = *param_1;
  *(undefined4 *)((int)this + 0x1c) = param_1[1];
  *(undefined4 *)((int)this + 0x20) = *param_1;
  *(undefined4 *)((int)this + 0x24) = param_1[1];
  *(float *)((int)this + 0x2c) = fVar1;
  *(undefined2 *)((int)this + 0x34) = 8;
  *(undefined4 *)((int)this + 0x30) = 0;
  FUN_004195f0(this,'\0',0);
  return;
}



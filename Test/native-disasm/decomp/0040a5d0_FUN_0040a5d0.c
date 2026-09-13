// FUN_0040a5d0 @ 0040a5d0 size=123 callers=1

int __thiscall
FUN_0040a5d0(void *this,undefined4 param_1,undefined4 param_2,undefined4 *param_3,
            undefined4 *param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_8 = 0;
  local_10 = *param_4;
  local_c = param_4[1];
  local_4 = 0;
  if (param_5 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = *(undefined4 *)(param_5 + 4);
  }
  if (param_3 == (undefined4 *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *param_3;
  }
  iVar2 = GdipDrawString(*(undefined4 *)this,&DAT_0048eb40,1,uVar1,&local_10,0,uVar3);
  if (iVar2 != 0) {
    *(int *)((int)this + 4) = iVar2;
    return iVar2;
  }
  return 0;
}



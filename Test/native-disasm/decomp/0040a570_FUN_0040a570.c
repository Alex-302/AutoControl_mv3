// FUN_0040a570 @ 0040a570 size=86 callers=1

int __thiscall
FUN_0040a570(void *this,undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4
            ,undefined4 *param_5,int param_6)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_6 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = *(undefined4 *)(param_6 + 4);
  }
  if (param_5 == (undefined4 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = *param_5;
  }
  if (param_3 == (undefined4 *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *param_3;
  }
  iVar2 = GdipDrawString(*(undefined4 *)this,param_1,param_2,uVar1,param_4,uVar3,uVar4);
  if (iVar2 != 0) {
    *(int *)((int)this + 4) = iVar2;
    return iVar2;
  }
  return 0;
}



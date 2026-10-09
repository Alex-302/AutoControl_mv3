// FUN_0043f0c0 @ 0043f0c0 size=312 callers=1

int * __thiscall FUN_0043f0c0(void *this,int *param_1,char *param_2,char *param_3)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int *_String1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047df29;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 0xf;
  param_1[4] = 0;
  piVar1 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar1 = (int *)*param_1;
  }
  *(undefined1 *)piVar1 = 0;
  local_8 = 0;
  uVar2 = (int)param_3 - (int)param_2;
  uVar3 = 0;
  if (uVar2 != 0) {
    do {
      if ((uint)param_1[4] < uVar2) {
        FUN_0043aef0(param_1,uVar2 - param_1[4],'\0');
      }
      else {
        param_1[4] = uVar2;
        if ((uint)param_1[5] < 0x10) {
          *(undefined1 *)((int)param_1 + uVar2) = 0;
        }
        else {
          *(undefined1 *)(*param_1 + uVar2) = 0;
        }
      }
      piVar1 = param_1;
      if (0xf < (uint)param_1[5]) {
        piVar1 = (int *)*param_1;
      }
      _String1 = param_1;
      if (0xf < (uint)param_1[5]) {
        _String1 = (int *)*param_1;
      }
      uVar2 = __Strxfrm((char *)_String1,(char *)((int)piVar1 + param_1[4]),param_2,param_3,
                        (_Collvec *)((int)this + 8));
      uVar3 = uVar2;
    } while (((uint)param_1[4] < uVar2) && (uVar2 != 0));
  }
  if ((uint)param_1[4] < uVar3) {
    FUN_0043aef0(param_1,uVar3 - param_1[4],'\0');
    ExceptionList = local_10;
    return param_1;
  }
  param_1[4] = uVar3;
  if ((uint)param_1[5] < 0x10) {
    *(undefined1 *)((int)param_1 + uVar3) = 0;
    ExceptionList = local_10;
    return param_1;
  }
  *(undefined1 *)(*param_1 + uVar3) = 0;
  ExceptionList = local_10;
  return param_1;
}



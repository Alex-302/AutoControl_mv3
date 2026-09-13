// FUN_0042ecc0 @ 0042ecc0 size=203 callers=1

undefined1 * __cdecl FUN_0042ecc0(undefined1 *param_1)

{
  HRESULT HVar1;
  HRESULT HVar2;
  int iVar3;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d2d2;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  HVar1 = CoInitializeEx((LPVOID)0x0,2);
  local_14 = (int *)0x0;
  local_8._0_1_ = 1;
  local_8._1_3_ = 0;
  HVar2 = CoCreateInstance((IID *)&DAT_00483d24,(LPUNKNOWN)0x0,1,(IID *)&DAT_0048e760,&local_14);
  if (HVar2 == 0) {
    iVar3 = (**(code **)(*local_14 + 0xa4))(local_14);
    *param_1 = 0;
    *(undefined8 *)(param_1 + 8) = 0;
    FUN_00450f50(param_1,iVar3);
    local_8 = CONCAT31(local_8._1_3_,2);
  }
  else {
    local_8._0_1_ = 3;
    *param_1 = 0;
    FUN_004381d0(param_1 + 8,'\0');
    local_8 = CONCAT31(local_8._1_3_,4);
  }
  if (local_14 != (int *)0x0) {
    (**(code **)(*local_14 + 8))(local_14);
  }
  if (-1 < HVar1) {
    CoUninitialize();
  }
  ExceptionList = local_10;
  return param_1;
}



// FUN_0040a960 @ 0040a960 size=258 callers=5

int * __fastcall FUN_0040a960(int *param_1,undefined4 *param_2)

{
  ULONG *pUVar1;
  undefined4 *puVar2;
  HRESULT HVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined4 *local_18;
  IStream *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479d79;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = 0;
  local_8 = 0;
  HVar3 = CreateStreamOnHGlobal((HGLOBAL)0x0,1,&local_14);
  if (HVar3 == 0) {
    pUVar1 = param_2 + 4;
    if (0xf < (uint)param_2[5]) {
      param_2 = (undefined4 *)*param_2;
    }
    HVar3 = (*local_14->lpVtbl->Write)(local_14,param_2,*pUVar1,(ULONG *)0x0);
    if (HVar3 == 0) {
      piVar4 = FUN_00441370(&local_18,&local_14);
      if (param_1 != piVar4) {
        iVar6 = *piVar4;
        *piVar4 = 0;
        puVar2 = (undefined4 *)*param_1;
        *param_1 = iVar6;
        if (puVar2 != (undefined4 *)0x0) {
          (**(code **)*puVar2)(1);
        }
      }
      if (local_18 != (undefined4 *)0x0) {
        (**(code **)*local_18)(1);
      }
      iVar6 = *param_1;
      if (iVar6 != 0) {
        local_18 = (undefined4 *)0x0;
        iVar5 = GdipGetImageWidth(*(undefined4 *)(iVar6 + 4),&local_18);
        if (iVar5 != 0) {
          *(int *)(iVar6 + 8) = iVar5;
        }
        if ((local_18 == (undefined4 *)0x0) || (iVar6 = FUN_0040a7b0(*param_1), iVar6 == 0)) {
          puVar2 = (undefined4 *)*param_1;
          *param_1 = 0;
          if (puVar2 != (undefined4 *)0x0) {
            (**(code **)*puVar2)(1);
          }
        }
      }
    }
    (*local_14->lpVtbl->Release)(local_14);
    ExceptionList = local_10;
    return param_1;
  }
  ExceptionList = local_10;
  return param_1;
}



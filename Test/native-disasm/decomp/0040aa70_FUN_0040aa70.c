// FUN_0040aa70 @ 0040aa70 size=313 callers=2

int * __fastcall FUN_0040aa70(int *param_1,int param_2,undefined4 param_3)

{
  HRESULT HVar1;
  int iVar2;
  int *piVar3;
  ULARGE_INTEGER *unaff_EDI;
  STATSTG local_68;
  int *local_20;
  undefined4 local_1c;
  IStream *local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479da9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 0xf;
  param_1[4] = 0;
  piVar3 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar3 = (int *)*param_1;
  }
  *(undefined1 *)piVar3 = 0;
  local_8 = 0;
  local_1c = 1;
  local_20 = param_1;
  HVar1 = CreateStreamOnHGlobal((HGLOBAL)0x0,1,local_18);
  if (HVar1 == 0) {
    iVar2 = GdipSaveImageToStream(*(undefined4 *)(param_2 + 4),local_18[0],param_3,0);
    if (iVar2 == 0) {
      HVar1 = (*local_18[0]->lpVtbl->Stat)(local_18[0],&local_68,1);
      if (HVar1 == 0) {
        if ((uint)param_1[4] < local_68.cbSize.s.LowPart) {
          FUN_0043aef0(param_1,local_68.cbSize.s.LowPart - param_1[4],'\0');
        }
        else {
          param_1[4] = local_68.cbSize.s.LowPart;
          if ((uint)param_1[5] < 0x10) {
            *(undefined1 *)((int)param_1 + local_68.cbSize.s.LowPart) = 0;
          }
          else {
            *(undefined1 *)(*param_1 + local_68.cbSize.s.LowPart) = 0;
          }
        }
        (*local_18[0]->lpVtbl->Seek)(local_18[0],(LARGE_INTEGER)0x0,0,unaff_EDI);
        piVar3 = param_1;
        if (0xf < (uint)param_1[5]) {
          piVar3 = (int *)*param_1;
        }
        HVar1 = (*local_18[0]->lpVtbl->Read)(local_18[0],piVar3,param_1[4],(ULONG *)0x0);
        if (HVar1 != 0) {
          param_1[4] = 0;
          piVar3 = param_1;
          if (0xf < (uint)param_1[5]) {
            piVar3 = (int *)*param_1;
          }
          *(undefined1 *)piVar3 = 0;
        }
      }
    }
    else {
      *(int *)(param_2 + 8) = iVar2;
    }
    (*local_18[0]->lpVtbl->Release)(local_18[0]);
  }
  ExceptionList = local_10;
  return param_1;
}



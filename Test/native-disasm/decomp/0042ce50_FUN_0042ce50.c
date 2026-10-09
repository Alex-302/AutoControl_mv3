// FUN_0042ce50 @ 0042ce50 size=288 callers=1

undefined1 * __fastcall FUN_0042ce50(undefined1 *param_1,LPCWSTR param_2,undefined4 *param_3)

{
  DWORD *pDVar1;
  LPCWSTR pwzUrl;
  HRESULT HVar2;
  void *local_38 [5];
  uint local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  LPCWSTR local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004792a8;
  local_10 = ExceptionList;
  local_20 = 0;
  pwzUrl = param_2;
  if (7 < *(uint *)(param_2 + 10)) {
    pwzUrl = *(LPCWSTR *)param_2;
  }
  ExceptionList = &local_10;
  local_1c = param_1;
  HVar2 = FindMimeFromData((LPBC)0x0,pwzUrl,(LPVOID)0x0,0,(LPCWSTR)0x0,0x21,local_18,0);
  if (HVar2 != 0) {
    pDVar1 = param_3 + 4;
    if (0xf < (uint)param_3[5]) {
      param_3 = (undefined4 *)*param_3;
    }
    if (7 < *(uint *)(param_2 + 10)) {
      param_2 = *(LPCWSTR *)param_2;
    }
    HVar2 = FindMimeFromData((LPBC)0x0,param_2,param_3,*pDVar1,(LPCWSTR)0x0,0x23,local_18,0);
    if (HVar2 != 0) {
      *(undefined4 *)(param_1 + 0x14) = 0xf;
      *(undefined4 *)(param_1 + 0x10) = 0;
      *param_1 = 0;
      FUN_0043ace0(param_1,(uint *)&DAT_0048e75c,0);
      ExceptionList = local_10;
      return param_1;
    }
  }
  FUN_004044f0((LPSTR)local_38,local_18[0],-1,0x7fffffff);
  local_8 = 0;
  CoTaskMemFree(local_18[0]);
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  FUN_0043ade0(param_1,local_38,0,0xffffffff);
  if (0xf < local_24) {
    FUN_00402430(local_38[0],local_24 + 1,1);
  }
  ExceptionList = local_10;
  return param_1;
}



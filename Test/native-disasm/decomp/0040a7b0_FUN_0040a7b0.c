// FUN_0040a7b0 @ 0040a7b0 size=40 callers=1

undefined4 __fastcall FUN_0040a7b0(int param_1)

{
  int iVar1;
  undefined4 local_4;
  
  local_4 = 0;
  iVar1 = GdipGetImageHeight(*(undefined4 *)(param_1 + 4),&local_4);
  if (iVar1 != 0) {
    *(int *)(param_1 + 8) = iVar1;
  }
  return local_4;
}



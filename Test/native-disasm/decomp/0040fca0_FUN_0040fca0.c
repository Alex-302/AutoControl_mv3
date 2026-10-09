// FUN_0040fca0 @ 0040fca0 size=164 callers=5

UINT_PTR __fastcall FUN_0040fca0(UINT param_1,int *param_2)

{
  int iVar1;
  UINT_PTR *pUVar2;
  UINT_PTR UVar3;
  undefined4 extraout_ECX;
  int iVar4;
  UINT_PTR local_10;
  UINT_PTR *local_c;
  UINT_PTR *local_8 [2];
  
  iVar1 = *(int *)ThreadLocalStoragePointer;
  *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) + 1;
  local_10 = *(UINT_PTR *)(iVar1 + 0xc);
  iVar4 = *(int *)(iVar1 + 4) * 0x20;
  FUN_00436250(&DAT_004a2850 + iVar4,(int *)&local_c,(byte *)&local_10);
  pUVar2 = local_c;
  if (local_c == *(UINT_PTR **)(&DAT_004a2854 + iVar4)) {
    local_c = &local_10;
    FUN_0044a660(&DAT_004a2850 + iVar4,(int *)local_8,extraout_ECX,&local_c);
    pUVar2 = local_8[0];
  }
  FUN_00433380(pUVar2 + 4,param_2);
  UVar3 = SetTimer(*(HWND *)(&DAT_004a2470 + *(int *)(iVar1 + 4) * 4),local_10,param_1,FUN_0040fbc0)
  ;
  if (UVar3 == 0) {
    FUN_0040fb40(&local_10,'\x01');
  }
  return local_10;
}



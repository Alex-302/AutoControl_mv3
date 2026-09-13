// FUN_0041da10 @ 0041da10 size=81 callers=1

undefined4 FUN_0041da10(int param_1,undefined4 param_2,undefined4 param_3,int param_4,uint *param_5)

{
  char cVar1;
  
  cVar1 = 'B';
  if (param_4 < (*(int *)(param_1 + 0x14) + *(int *)(param_1 + 0xc)) / 2) {
    cVar1 = 'T';
  }
  if (*(char *)(*(int *)(param_1 + 0x18) + 0x10) != cVar1) {
    *(char *)(*(int *)(param_1 + 0x18) + 0x10) = cVar1;
    FUN_0041d510(*(HMENU *)(*(int *)(param_1 + 0x18) + 8),
                 *(ushort *)(*(int *)(param_1 + 0x18) + 0xc));
  }
  *param_5 = *(byte *)(*(int *)(param_1 + 0x18) + 0xf) & 2;
  return 0;
}



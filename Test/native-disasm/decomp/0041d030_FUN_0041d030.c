// FUN_0041d030 @ 0041d030 size=154 callers=1

void __fastcall FUN_0041d030(void *param_1,LONG *param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  bool bVar3;
  undefined4 *local_c [2];
  
  DAT_004a29bc = 0;
  DAT_004a29c0 = 0;
  DAT_004a29c4 = 0;
  puVar2 = FUN_00441fa0(local_c,param_1);
  if ((undefined4 **)puVar2 != &DAT_004a299c) {
    puVar1 = (undefined4 *)*puVar2;
    *puVar2 = 0;
    puVar2 = DAT_004a299c;
    bVar3 = DAT_004a299c != (undefined4 *)0x0;
    DAT_004a299c = puVar1;
    if (bVar3) {
      FUN_0041bff0(puVar2);
      FUN_0045a6a4(puVar2);
    }
  }
  if (local_c[0] != (undefined4 *)0x0) {
    FUN_0041bff0(local_c[0]);
    FUN_0045a6a4(local_c[0]);
  }
  FUN_0041c1c0(DAT_004a299c,param_3,*param_2,param_2[1]);
  return;
}



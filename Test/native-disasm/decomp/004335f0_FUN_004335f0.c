// FUN_004335f0 @ 004335f0 size=133 callers=2

undefined8 __fastcall FUN_004335f0(int *param_1,undefined4 param_2,int *param_3)

{
  uint *puVar1;
  void *pvVar2;
  uint uVar3;
  ulonglong uVar4;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  uVar3 = param_3[1] - *param_3 >> 1;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  if (uVar3 != 0) {
    if (0x7fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    pvVar2 = FUN_0043ec70(uVar3);
    *param_1 = (int)pvVar2;
    param_1[1] = (int)pvVar2;
    param_1[2] = *param_1 + uVar3 * 2;
    uVar3 = param_3[1] - *param_3;
    puVar1 = (uint *)*param_1;
    uVar4 = FUN_0045b0e0(puVar1,(uint *)*param_3,uVar3);
    param_2 = (undefined4)(uVar4 >> 0x20);
    param_1[1] = uVar3 + (int)puVar1;
  }
  return CONCAT44(param_2,param_1);
}



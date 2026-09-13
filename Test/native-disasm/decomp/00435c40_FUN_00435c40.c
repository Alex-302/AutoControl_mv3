// FUN_00435c40 @ 00435c40 size=83 callers=3

void __fastcall FUN_00435c40(int *param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = (int *)*param_1;
  if (piVar2 != (int *)0x0) {
    piVar1 = (int *)param_1[1];
    for (; piVar2 != piVar1; piVar2 = piVar2 + 1) {
      if ((undefined4 *)*piVar2 != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)*piVar2)(1);
      }
    }
    FUN_00402430((void *)*param_1,param_1[2] - *param_1 >> 2,4);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}



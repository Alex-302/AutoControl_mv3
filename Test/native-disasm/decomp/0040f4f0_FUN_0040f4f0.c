// FUN_0040f4f0 @ 0040f4f0 size=87 callers=1

bool FUN_0040f4f0(int param_1,int *param_2)

{
  int *piVar1;
  int *this;
  int *piVar2;
  int *piVar3;
  
  piVar1 = (int *)*param_2;
  this = (int *)param_2[1];
  piVar2 = (int *)piVar1[1];
  piVar3 = (int *)*piVar1;
  if (piVar3 != piVar2) {
    do {
      if (*piVar3 == param_1) break;
      piVar3 = piVar3 + 1;
    } while (piVar3 != piVar2);
    if ((piVar3 != piVar2) && (-1 < (int)piVar3 - *piVar1 >> 2)) {
      FUN_00432e80(this,&param_1);
    }
  }
  return (uint)(this[1] - *this >> 2) < (uint)(piVar1[1] - *piVar1 >> 2);
}



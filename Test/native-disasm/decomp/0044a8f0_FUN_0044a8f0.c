// FUN_0044a8f0 @ 0044a8f0 size=474 callers=8

void __thiscall
FUN_0044a8f0(void *this,undefined4 *param_1,char param_2,undefined4 *param_3,undefined4 param_4,
            int *param_5)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  
  if (0x4924922 < *(uint *)((int)this + 4)) {
    piVar5 = param_5 + 4;
    FUN_00434820((char *)(param_5 + 10));
    if (0xf < (uint)param_5[9]) {
      FUN_00402430((void *)*piVar5,param_5[9] + 1,1);
    }
    param_5[9] = 0xf;
    param_5[8] = 0;
    if (0xf < (uint)param_5[9]) {
      piVar5 = (int *)*piVar5;
    }
    *(undefined1 *)piVar5 = 0;
    FID_conflict__free(param_5);
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("map/set<T> too long");
  }
  *(uint *)((int)this + 4) = *(uint *)((int)this + 4) + 1;
  param_5[1] = (int)param_3;
  if (param_3 == *(undefined4 **)this) {
    (*(undefined4 **)this)[1] = param_5;
    **(undefined4 **)this = param_5;
    *(int **)(*(int *)this + 8) = param_5;
  }
  else if (param_2 == '\0') {
    param_3[2] = param_5;
    if (param_3 == *(undefined4 **)(*(int *)this + 8)) {
      *(int **)(*(int *)this + 8) = param_5;
    }
  }
  else {
    *param_3 = param_5;
    if (param_3 == (undefined4 *)**(int **)this) {
      **(int **)this = (int)param_5;
    }
  }
  cVar1 = *(char *)(param_5[1] + 0xc);
  piVar5 = param_5;
  do {
    if (cVar1 != '\0') {
      *(undefined1 *)(*(int *)(*(int *)this + 4) + 0xc) = 1;
      *param_1 = param_5;
      return;
    }
    piVar4 = (int *)piVar5[1];
    piVar3 = *(int **)piVar4[1];
    if (piVar4 == piVar3) {
      piVar3 = (int *)((undefined4 *)piVar4[1])[2];
      if ((char)piVar3[3] == '\0') goto LAB_0044aa19;
      if (piVar5 == (int *)piVar4[2]) {
        FUN_0043fd00(this,(int)piVar4);
        piVar5 = piVar4;
      }
      *(undefined1 *)(piVar5[1] + 0xc) = 1;
      *(undefined1 *)(*(int *)(piVar5[1] + 4) + 0xc) = 0;
      piVar4 = *(int **)(piVar5[1] + 4);
      piVar3 = (int *)*piVar4;
      *piVar4 = piVar3[2];
      if (*(char *)(piVar3[2] + 0xd) == '\0') {
        *(int **)(piVar3[2] + 4) = piVar4;
      }
      piVar3[1] = piVar4[1];
      if (piVar4 == *(int **)(*(int *)this + 4)) {
        *(int **)(*(int *)this + 4) = piVar3;
        piVar3[2] = (int)piVar4;
      }
      else {
        piVar2 = (int *)piVar4[1];
        if (piVar4 == (int *)piVar2[2]) {
          piVar2[2] = (int)piVar3;
          piVar3[2] = (int)piVar4;
        }
        else {
          *piVar2 = (int)piVar3;
          piVar3[2] = (int)piVar4;
        }
      }
LAB_0044aa8d:
      piVar4[1] = (int)piVar3;
    }
    else {
      if ((char)piVar3[3] != '\0') {
        if (piVar5 == (int *)*piVar4) {
          FUN_0043fca0(this,piVar4);
          piVar5 = piVar4;
        }
        *(undefined1 *)(piVar5[1] + 0xc) = 1;
        *(undefined1 *)(*(int *)(piVar5[1] + 4) + 0xc) = 0;
        piVar4 = *(int **)(piVar5[1] + 4);
        piVar3 = (int *)piVar4[2];
        piVar4[2] = *piVar3;
        if (*(char *)(*piVar3 + 0xd) == '\0') {
          *(int **)(*piVar3 + 4) = piVar4;
        }
        piVar3[1] = piVar4[1];
        if (piVar4 == *(int **)(*(int *)this + 4)) {
          *(int **)(*(int *)this + 4) = piVar3;
        }
        else {
          piVar2 = (int *)piVar4[1];
          if (piVar4 == (int *)*piVar2) {
            *piVar2 = (int)piVar3;
          }
          else {
            piVar2[2] = (int)piVar3;
          }
        }
        *piVar3 = (int)piVar4;
        goto LAB_0044aa8d;
      }
LAB_0044aa19:
      *(undefined1 *)(piVar4 + 3) = 1;
      *(undefined1 *)(piVar3 + 3) = 1;
      *(undefined1 *)(*(int *)(piVar5[1] + 4) + 0xc) = 0;
      piVar5 = *(int **)(piVar5[1] + 4);
    }
    cVar1 = *(char *)(piVar5[1] + 0xc);
  } while( true );
}



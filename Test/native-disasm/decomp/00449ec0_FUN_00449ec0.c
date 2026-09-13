// FUN_00449ec0 @ 00449ec0 size=400 callers=1

void __thiscall
FUN_00449ec0(void *this,undefined4 *param_1,char param_2,undefined4 *param_3,uint *param_4)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  
  if (0x6666664 < *(uint *)((int)this + 4)) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("map/set<T> too long");
  }
  piVar3 = FUN_00452d40(this,param_4);
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 1;
  piVar3[1] = (int)param_3;
  if (param_3 == *(undefined4 **)this) {
    (*(undefined4 **)this)[1] = piVar3;
    **(undefined4 **)this = piVar3;
    iVar4 = *(int *)this;
  }
  else {
    if (param_2 != '\0') {
      *param_3 = piVar3;
      if (param_3 == (undefined4 *)**(int **)this) {
        **(int **)this = (int)piVar3;
      }
      goto LAB_00449f18;
    }
    param_3[2] = piVar3;
    iVar4 = *(int *)this;
    if (param_3 != *(undefined4 **)(iVar4 + 8)) goto LAB_00449f18;
  }
  *(int **)(iVar4 + 8) = piVar3;
LAB_00449f18:
  cVar1 = *(char *)(piVar3[1] + 0xc);
  piVar7 = piVar3;
  do {
    if (cVar1 != '\0') {
      *(undefined1 *)(*(int *)(*(int *)this + 4) + 0xc) = 1;
      *param_1 = piVar3;
      return;
    }
    piVar6 = (int *)piVar7[1];
    piVar5 = *(int **)piVar6[1];
    if (piVar6 == piVar5) {
      piVar5 = (int *)((undefined4 *)piVar6[1])[2];
      if ((char)piVar5[3] == '\0') goto LAB_00449fad;
      if (piVar7 == (int *)piVar6[2]) {
        FUN_0043fd00(this,(int)piVar6);
        piVar7 = piVar6;
      }
      *(undefined1 *)(piVar7[1] + 0xc) = 1;
      *(undefined1 *)(*(int *)(piVar7[1] + 4) + 0xc) = 0;
      piVar6 = *(int **)(piVar7[1] + 4);
      piVar5 = (int *)*piVar6;
      *piVar6 = piVar5[2];
      if (*(char *)(piVar5[2] + 0xd) == '\0') {
        *(int **)(piVar5[2] + 4) = piVar6;
      }
      piVar5[1] = piVar6[1];
      if (piVar6 == *(int **)(*(int *)this + 4)) {
        *(int **)(*(int *)this + 4) = piVar5;
        piVar5[2] = (int)piVar6;
      }
      else {
        piVar2 = (int *)piVar6[1];
        if (piVar6 == (int *)piVar2[2]) {
          piVar2[2] = (int)piVar5;
          piVar5[2] = (int)piVar6;
        }
        else {
          *piVar2 = (int)piVar5;
          piVar5[2] = (int)piVar6;
        }
      }
LAB_0044a021:
      piVar6[1] = (int)piVar5;
    }
    else {
      if ((char)piVar5[3] != '\0') {
        if (piVar7 == (int *)*piVar6) {
          FUN_0043fca0(this,piVar6);
          piVar7 = piVar6;
        }
        *(undefined1 *)(piVar7[1] + 0xc) = 1;
        *(undefined1 *)(*(int *)(piVar7[1] + 4) + 0xc) = 0;
        piVar6 = *(int **)(piVar7[1] + 4);
        piVar5 = (int *)piVar6[2];
        piVar6[2] = *piVar5;
        if (*(char *)(*piVar5 + 0xd) == '\0') {
          *(int **)(*piVar5 + 4) = piVar6;
        }
        piVar5[1] = piVar6[1];
        if (piVar6 == *(int **)(*(int *)this + 4)) {
          *(int **)(*(int *)this + 4) = piVar5;
        }
        else {
          piVar2 = (int *)piVar6[1];
          if (piVar6 == (int *)*piVar2) {
            *piVar2 = (int)piVar5;
          }
          else {
            piVar2[2] = (int)piVar5;
          }
        }
        *piVar5 = (int)piVar6;
        goto LAB_0044a021;
      }
LAB_00449fad:
      *(undefined1 *)(piVar6 + 3) = 1;
      *(undefined1 *)(piVar5 + 3) = 1;
      *(undefined1 *)(*(int *)(piVar7[1] + 4) + 0xc) = 0;
      piVar7 = *(int **)(piVar7[1] + 4);
    }
    cVar1 = *(char *)(piVar7[1] + 0xc);
  } while( true );
}



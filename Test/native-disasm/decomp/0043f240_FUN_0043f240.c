// FUN_0043f240 @ 0043f240 size=739 callers=1

void __thiscall FUN_0043f240(void *this,undefined4 *param_1,int *param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  void *pvVar4;
  int *piVar5;
  int *_Memory;
  int *piVar6;
  int *piVar7;
  void *_Memory_00;
  uint *puVar8;
  int *piVar9;
  
  _Memory = param_2;
  FUN_0043ed80((int *)&param_2);
  piVar7 = (int *)*_Memory;
  if (*(char *)((int)piVar7 + 0xd) == '\0') {
    piVar9 = piVar7;
    if ((*(char *)(_Memory[2] + 0xd) == '\0') && (piVar9 = (int *)param_2[2], param_2 != _Memory)) {
      piVar7[1] = (int)param_2;
      *param_2 = *_Memory;
      piVar7 = param_2;
      if (param_2 != (int *)_Memory[2]) {
        piVar7 = (int *)param_2[1];
        if (*(char *)((int)piVar9 + 0xd) == '\0') {
          piVar9[1] = (int)piVar7;
        }
        *piVar7 = (int)piVar9;
        param_2[2] = _Memory[2];
        *(int **)(_Memory[2] + 4) = param_2;
      }
      if (*(int **)(*(int *)this + 4) == _Memory) {
        *(int **)(*(int *)this + 4) = param_2;
      }
      else {
        piVar6 = (int *)_Memory[1];
        if ((int *)*piVar6 == _Memory) {
          *piVar6 = (int)param_2;
        }
        else {
          piVar6[2] = (int)param_2;
        }
      }
      param_2[1] = _Memory[1];
      iVar3 = param_2[3];
      *(char *)(param_2 + 3) = (char)_Memory[3];
      *(char *)(_Memory + 3) = (char)iVar3;
      goto LAB_0043f357;
    }
  }
  else {
    piVar9 = (int *)_Memory[2];
  }
  piVar7 = (int *)_Memory[1];
  if (*(char *)((int)piVar9 + 0xd) == '\0') {
    piVar9[1] = (int)piVar7;
  }
  if (*(int **)(*(int *)this + 4) == _Memory) {
    *(int **)(*(int *)this + 4) = piVar9;
  }
  else if ((int *)*piVar7 == _Memory) {
    *piVar7 = (int)piVar9;
  }
  else {
    piVar7[2] = (int)piVar9;
  }
  if ((int *)**(int **)this == _Memory) {
    piVar6 = piVar7;
    if (*(char *)((int)piVar9 + 0xd) == '\0') {
      cVar1 = *(char *)(*piVar9 + 0xd);
      piVar2 = (int *)*piVar9;
      piVar6 = piVar9;
      while (piVar5 = piVar2, cVar1 == '\0') {
        piVar2 = (int *)*piVar5;
        cVar1 = *(char *)((int)piVar2 + 0xd);
        piVar6 = piVar5;
      }
    }
    **(int **)this = (int)piVar6;
  }
  iVar3 = *(int *)this;
  if (*(int **)(iVar3 + 8) == _Memory) {
    if (*(char *)((int)piVar9 + 0xd) == '\0') {
      cVar1 = *(char *)(piVar9[2] + 0xd);
      piVar6 = (int *)piVar9[2];
      piVar2 = piVar9;
      while (piVar5 = piVar6, cVar1 == '\0') {
        piVar6 = (int *)piVar5[2];
        cVar1 = *(char *)((int)piVar6 + 0xd);
        piVar2 = piVar5;
      }
      *(int **)(iVar3 + 8) = piVar2;
    }
    else {
      *(int **)(iVar3 + 8) = piVar7;
    }
  }
LAB_0043f357:
  if ((char)_Memory[3] == '\x01') {
    if (piVar9 != *(int **)(*(int *)this + 4)) {
      do {
        piVar6 = piVar7;
        if ((char)piVar9[3] != '\x01') break;
        piVar7 = (int *)*piVar6;
        if (piVar9 == piVar7) {
          piVar7 = (int *)piVar6[2];
          if ((char)piVar7[3] == '\0') {
            *(undefined1 *)(piVar7 + 3) = 1;
            *(undefined1 *)(piVar6 + 3) = 0;
            FUN_0043fd00(this,(int)piVar6);
            piVar7 = (int *)piVar6[2];
          }
          if (*(char *)((int)piVar7 + 0xd) == '\0') {
            if ((*(char *)(*piVar7 + 0xc) != '\x01') || (*(char *)(piVar7[2] + 0xc) != '\x01')) {
              if (*(char *)(piVar7[2] + 0xc) == '\x01') {
                *(undefined1 *)(*piVar7 + 0xc) = 1;
                *(undefined1 *)(piVar7 + 3) = 0;
                FUN_0043fca0(this,piVar7);
                piVar7 = (int *)piVar6[2];
              }
              *(char *)(piVar7 + 3) = (char)piVar6[3];
              *(undefined1 *)(piVar6 + 3) = 1;
              *(undefined1 *)(piVar7[2] + 0xc) = 1;
              FUN_0043fd00(this,(int)piVar6);
              break;
            }
LAB_0043f433:
            *(undefined1 *)(piVar7 + 3) = 0;
          }
        }
        else {
          if ((char)piVar7[3] == '\0') {
            *(undefined1 *)(piVar7 + 3) = 1;
            *(undefined1 *)(piVar6 + 3) = 0;
            FUN_0043fca0(this,piVar6);
            piVar7 = (int *)*piVar6;
          }
          if (*(char *)((int)piVar7 + 0xd) == '\0') {
            if ((*(char *)(piVar7[2] + 0xc) == '\x01') && (*(char *)(*piVar7 + 0xc) == '\x01'))
            goto LAB_0043f433;
            if (*(char *)(*piVar7 + 0xc) == '\x01') {
              *(undefined1 *)(piVar7[2] + 0xc) = 1;
              *(undefined1 *)(piVar7 + 3) = 0;
              FUN_0043fd00(this,(int)piVar7);
              piVar7 = (int *)*piVar6;
            }
            *(char *)(piVar7 + 3) = (char)piVar6[3];
            *(undefined1 *)(piVar6 + 3) = 1;
            *(undefined1 *)(*piVar7 + 0xc) = 1;
            FUN_0043fca0(this,piVar6);
            break;
          }
        }
        piVar7 = (int *)piVar6[1];
        piVar9 = piVar6;
      } while (piVar6 != *(int **)(*(int *)this + 4));
    }
    *(undefined1 *)(piVar9 + 3) = 1;
  }
  puVar8 = (uint *)(_Memory + 4);
  FUN_00434820((char *)(_Memory + 10));
  if (0xf < (uint)_Memory[9]) {
    pvVar4 = (void *)*puVar8;
    _Memory_00 = pvVar4;
    if (0xfff < _Memory[9] + 1U) {
      if (((uint)pvVar4 & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      _Memory_00 = *(void **)((int)pvVar4 - 4);
      if (pvVar4 <= _Memory_00) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)pvVar4 - (int)_Memory_00) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)pvVar4 - (int)_Memory_00)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(_Memory_00);
  }
  _Memory[9] = 0xf;
  _Memory[8] = 0;
  if (0xf < (uint)_Memory[9]) {
    puVar8 = (uint *)*puVar8;
  }
  *(undefined1 *)puVar8 = 0;
  FID_conflict__free(_Memory);
  if (*(int *)((int)this + 4) != 0) {
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + -1;
  }
  *param_1 = param_2;
  return;
}



// FUN_00437ab0 @ 00437ab0 size=1227 callers=9

void __thiscall FUN_00437ab0(void *this,undefined1 *param_1,char param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  undefined1 *puVar7;
  int iStack_10;
  uint uStack_c;
  
  switch(*param_1) {
  case 0:
    FUN_0043e0b0(*(void **)this,&DAT_0048de3c,4,0);
    return;
  case 1:
    break;
  case 2:
    if (**(int **)(param_1 + 8) == (*(int **)(param_1 + 8))[1]) {
      FUN_0043e0b0(*(void **)this,&DAT_0048de28,2,0);
      return;
    }
    if (param_2 != '\0') {
      FUN_0043e0b0(*(void **)this,&DAT_0048de2c,2,0);
      uVar5 = param_3 + param_4;
      if (*(uint *)((int)this + 0x5c) < uVar5) {
        FUN_0043abe0((void *)((int)this + 0x4c),uVar5,' ');
      }
      puVar7 = (undefined1 *)**(int **)(param_1 + 8);
      if (puVar7 != (undefined1 *)((*(int **)(param_1 + 8))[1] + -0x10)) {
        do {
          puVar3 = (undefined4 *)((int)this + 0x4c);
          if (0xf < *(uint *)((int)this + 0x60)) {
            puVar3 = (undefined4 *)*puVar3;
          }
          FUN_0043e0b0(*(void **)this,puVar3,uVar5,0);
          FUN_00437ab0(this,puVar7,'\x01',param_3,uVar5);
          FUN_0043e0b0(*(void **)this,&DAT_0048de20,2,0);
          puVar7 = puVar7 + 0x10;
        } while (puVar7 != (undefined1 *)(*(int *)(*(int *)(param_1 + 8) + 4) + -0x10));
      }
      piVar2 = (int *)((int)this + 0x4c);
      piVar4 = piVar2;
      if (0xf < *(uint *)((int)this + 0x60)) {
        piVar4 = (int *)*piVar2;
      }
      FUN_0043e0b0(*(void **)this,piVar4,uVar5,0);
      FUN_00437ab0(this,(undefined1 *)(*(int *)(*(int *)(param_1 + 8) + 4) + -0x10),'\x01',param_3,
                   uVar5);
      FUN_0043e220(*(void **)this,10);
      if (0xf < *(uint *)((int)this + 0x60)) {
        piVar2 = (int *)*piVar2;
      }
      FUN_0043e0b0(*(void **)this,piVar2,param_4,0);
      FUN_0043e220(*(void **)this,0x5d);
      return;
    }
    FUN_0043e220(*(void **)this,0x5b);
    puVar7 = (undefined1 *)**(int **)(param_1 + 8);
    if (puVar7 != (undefined1 *)((*(int **)(param_1 + 8))[1] + -0x10)) {
      do {
        FUN_00437ab0(this,puVar7,'\0',param_3,param_4);
        FUN_0043e220(*(void **)this,0x2c);
        puVar7 = puVar7 + 0x10;
      } while (puVar7 != (undefined1 *)(*(int *)(*(int *)(param_1 + 8) + 4) + -0x10));
    }
    FUN_00437ab0(this,(undefined1 *)(*(int *)(*(int *)(param_1 + 8) + 4) + -0x10),'\0',param_3,
                 param_4);
    FUN_0043e220(*(void **)this,0x5d);
    return;
  case 3:
    FUN_0043e220(*(void **)this,0x22);
    FUN_0043ce20(*(char **)(param_1 + 8));
    FUN_0043e220(*(void **)this,0x22);
    return;
  case 4:
    if (param_1[8] != '\0') {
      FUN_0043e0b0(*(void **)this,&DAT_0048cb5c,4,0);
      return;
    }
    FUN_0043e0b0(*(void **)this,"false",5,0);
    return;
  case 5:
    FUN_00442bd0(this,*(int *)(param_1 + 8),*(int *)(param_1 + 0xc));
    return;
  case 6:
    FUN_00442c90(this,*(int *)(param_1 + 8),*(uint *)(param_1 + 0xc));
    return;
  case 7:
    FUN_0043cd20(this);
    return;
  case 8:
    FUN_0043e0b0(*(void **)this,"<discarded>",0xb,0);
    return;
  default:
    return;
  }
  if (*(int *)(*(int *)(param_1 + 8) + 4) == 0) {
    FUN_0043e0b0(*(void **)this,&DAT_0048de14,2,0);
    return;
  }
  if (param_2 != '\0') {
    FUN_0043e0b0(*(void **)this,&DAT_0048de18,2,0);
    uVar5 = param_3 + param_4;
    if (*(uint *)((int)this + 0x5c) < uVar5) {
      FUN_0043abe0((void *)((int)this + 0x4c),uVar5,' ');
    }
    uStack_c = 0;
    iStack_10 = *(int *)**(undefined4 **)(param_1 + 8);
    if ((*(undefined4 **)(param_1 + 8))[1] != 1) {
      do {
        iVar1 = iStack_10;
        piVar2 = (int *)((int)this + 0x4c);
        if (0xf < *(uint *)((int)this + 0x60)) {
          piVar2 = (int *)*piVar2;
        }
        FUN_0043e0b0(*(void **)this,piVar2,uVar5,0);
        FUN_0043e220(*(void **)this,0x22);
        FUN_0043ce20((char *)(iVar1 + 0x10));
        FUN_0043e0b0(*(void **)this,&DAT_0048de1c,3,0);
        FUN_00437ab0(this,(undefined1 *)(iVar1 + 0x28),'\x01',param_3,uVar5);
        FUN_0043e0b0(*(void **)this,&DAT_0048de20,2,0);
        uVar6 = uStack_c + 1;
        uStack_c = uVar6;
        FUN_0043ed80(&iStack_10);
      } while (uVar6 < *(int *)(*(int *)(param_1 + 8) + 4) - 1U);
    }
    iVar1 = iStack_10;
    piVar2 = (int *)((int)this + 0x4c);
    piVar4 = piVar2;
    if (0xf < *(uint *)((int)this + 0x60)) {
      piVar4 = (int *)*piVar2;
    }
    FUN_0043e0b0(*(void **)this,piVar4,uVar5,0);
    FUN_0043e220(*(void **)this,0x22);
    FUN_0043ce20((char *)(iVar1 + 0x10));
    FUN_0043e0b0(*(void **)this,&DAT_0048de1c,3,0);
    FUN_00437ab0(this,(undefined1 *)(iVar1 + 0x28),'\x01',param_3,uVar5);
    FUN_0043e220(*(void **)this,10);
    if (0xf < *(uint *)((int)this + 0x60)) {
      piVar2 = (int *)*piVar2;
    }
    FUN_0043e0b0(*(void **)this,piVar2,param_4,0);
    FUN_0043e220(*(void **)this,0x7d);
    return;
  }
  FUN_0043e220(*(void **)this,0x7b);
  uStack_c = 0;
  iStack_10 = *(int *)**(undefined4 **)(param_1 + 8);
  if ((*(undefined4 **)(param_1 + 8))[1] != 1) {
    do {
      iVar1 = iStack_10;
      FUN_0043e220(*(void **)this,0x22);
      FUN_0043ce20((char *)(iVar1 + 0x10));
      FUN_0043e0b0(*(void **)this,&DAT_0048de24,2,0);
      FUN_00437ab0(this,(undefined1 *)(iVar1 + 0x28),'\0',param_3,param_4);
      FUN_0043e220(*(void **)this,0x2c);
      uVar5 = uStack_c + 1;
      uStack_c = uVar5;
      FUN_0043ed80(&iStack_10);
    } while (uVar5 < *(int *)(*(int *)(param_1 + 8) + 4) - 1U);
  }
  iVar1 = iStack_10;
  FUN_0043e220(*(void **)this,0x22);
  FUN_0043ce20((char *)(iVar1 + 0x10));
  FUN_0043e0b0(*(void **)this,&DAT_0048de24,2,0);
  FUN_00437ab0(this,(undefined1 *)(iVar1 + 0x28),'\0',param_3,param_4);
  FUN_0043e220(*(void **)this,0x7d);
  return;
}



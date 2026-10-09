// FUN_00437350 @ 00437350 size=130 callers=2

int * __thiscall FUN_00437350(void *this,int *param_1,byte *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  iVar1 = *(int *)((int)this + 0xc);
  puVar2 = *(undefined4 **)((int)this + 4);
  uVar4 = *(uint *)((int)this + 0x18) &
          ((*param_2 ^ 0x811c9dc5) * 0x1000193 ^ (uint)param_2[1]) * 0x1000193;
  puVar3 = *(undefined4 **)(iVar1 + uVar4 * 8);
  while( true ) {
    puVar5 = puVar2;
    if (*(undefined4 **)(iVar1 + uVar4 * 8) != puVar2) {
      puVar5 = (undefined4 *)**(undefined4 **)(iVar1 + uVar4 * 8 + 4);
    }
    if (puVar3 == puVar5) break;
    if (*(short *)(puVar3 + 2) == *(short *)param_2) {
      if (*(short *)param_2 != *(short *)(puVar3 + 2)) {
        puVar3 = puVar2;
      }
      *param_1 = (int)puVar3;
      return param_1;
    }
    puVar3 = (undefined4 *)*puVar3;
  }
  *param_1 = (int)puVar2;
  return param_1;
}



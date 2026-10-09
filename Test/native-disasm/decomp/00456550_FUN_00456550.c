// FUN_00456550 @ 00456550 size=156 callers=4

void __thiscall FUN_00456550(void *this,int param_1,ushort param_2,char param_3)

{
  undefined4 *puVar1;
  byte *pbVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = 0;
  do {
    if (param_2 == 0xffff) {
      if (((char)uVar3 == '_') ||
         ((*(ushort *)(*(int *)(*(int *)(*(int *)((int)this + 0xc) + 4) + 0xc) + (uVar3 & 0xff) * 2)
          & 0x107) != 0)) {
        bVar4 = true;
      }
      else {
        bVar4 = false;
      }
    }
    else {
      bVar4 = (*(ushort *)
                (*(int *)(*(int *)(*(int *)((int)this + 0xc) + 4) + 0xc) + (uVar3 & 0xff) * 2) &
              param_2) != 0;
    }
    if (bVar4 != (bool)param_3) {
      if (*(int *)(param_1 + 0x18) == 0) {
        puVar1 = operator_new(0x20);
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = 0;
        puVar1[3] = 0;
        puVar1[4] = 0;
        puVar1[5] = 0;
        puVar1[6] = 0;
        puVar1[7] = 0;
        *(undefined4 **)(param_1 + 0x18) = puVar1;
      }
      pbVar2 = (byte *)((uVar3 >> 3) + *(int *)(param_1 + 0x18));
      *pbVar2 = *pbVar2 | (byte)(1 << (uVar3 & 7));
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x100);
  return;
}



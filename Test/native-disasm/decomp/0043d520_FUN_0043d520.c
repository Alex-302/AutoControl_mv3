// FUN_0043d520 @ 0043d520 size=102 callers=1

undefined4 * __thiscall FUN_0043d520(void *this,byte *param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  byte *pbVar6;
  
  puVar4 = FUN_00442a70(this,param_1);
  if (puVar4 != *(undefined4 **)this) {
    pbVar6 = (byte *)(puVar4 + 4);
    if (0xf < (uint)puVar4[9]) {
      pbVar6 = *(byte **)pbVar6;
    }
    puVar1 = (uint *)(param_1 + 0x10);
    if (0xf < *(uint *)(param_1 + 0x14)) {
      param_1 = *(byte **)param_1;
    }
    uVar2 = puVar4[8];
    uVar3 = *puVar1;
    uVar5 = uVar2;
    if (uVar3 < uVar2) {
      uVar5 = uVar3;
    }
    uVar5 = FUN_004023d0(param_1,pbVar6,uVar5);
    if (uVar5 == 0) {
      if (uVar2 <= uVar3) {
LAB_0043d572:
        return puVar4 + 10;
      }
    }
    else if (-1 < (int)uVar5) goto LAB_0043d572;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ee4("invalid map<K, T> key");
}



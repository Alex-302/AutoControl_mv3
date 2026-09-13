// FUN_0043aad0 @ 0043aad0 size=126 callers=4

int __thiscall FUN_0043aad0(void *this,byte *param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  if (param_3 == 0) {
    return 0;
  }
  if (param_3 <= *(uint *)((int)this + 0x10)) {
    pbVar3 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      pbVar3 = *(byte **)this;
    }
    while( true ) {
      if ((*pbVar3 == *param_1) && (uVar1 = FUN_004023d0(pbVar3,param_1,param_3), uVar1 == 0)) {
        if (0xf < *(uint *)((int)this + 0x14)) {
          this = *(void **)this;
        }
        return (int)pbVar3 - (int)this;
      }
      pbVar2 = (byte *)FUN_00435400(this);
      if (pbVar3 == pbVar2) break;
      pbVar3 = pbVar3 + -1;
    }
  }
  return -1;
}



// FUN_0043ab50 @ 0043ab50 size=143 callers=6

int __thiscall FUN_0043ab50(void *this,byte *param_1,undefined4 param_2,uint param_3)

{
  byte *pbVar1;
  uint uVar2;
  byte *_Buf;
  byte *_MaxCount;
  
  if (param_3 == 0) {
    return 0;
  }
  uVar2 = *(uint *)((int)this + 0x10);
  if ((uVar2 != 0) && (param_3 <= uVar2)) {
    _MaxCount = (byte *)(uVar2 + (1 - param_3));
    _Buf = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      _Buf = *(byte **)this;
    }
    while ((_MaxCount != (byte *)0x0 &&
           (pbVar1 = _memchr(_Buf,(int)(char)*param_1,(size_t)_MaxCount), pbVar1 != (byte *)0x0))) {
      uVar2 = FUN_004023d0(pbVar1,param_1,param_3);
      if (uVar2 == 0) {
        if (0xf < *(uint *)((int)this + 0x14)) {
          this = *(void **)this;
        }
        return (int)pbVar1 - (int)this;
      }
      _MaxCount = _Buf + (int)(_MaxCount + (-1 - (int)pbVar1));
      _Buf = pbVar1 + 1;
    }
  }
  return -1;
}



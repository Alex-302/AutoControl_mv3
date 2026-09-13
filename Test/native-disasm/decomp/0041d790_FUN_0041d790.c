// FUN_0041d790 @ 0041d790 size=194 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void * __thiscall FUN_0041d790(void *this,undefined4 *param_1)

{
  UINT UVar1;
  undefined4 local_14;
  
  *(undefined4 *)((int)this + 4) = 1;
  *(undefined ***)this = &PTR_FUN_0048ece8;
  *(undefined4 *)((int)this + 0x1c) = 0xf;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined1 *)((int)this + 8) = 0;
  FUN_0043ade0((undefined1 *)((int)this + 8),param_1,0,0xffffffff);
  if (DAT_004a23d4 == 0) {
    UVar1 = RegisterClipboardFormatA("UniformResourceLocator");
    local_14 = CONCAT22(local_14._2_2_,(short)UVar1);
    _DAT_004a23fc = local_14;
    local_14 = CONCAT22(local_14._2_2_,1);
    uRam004a2400 = 0;
    uRam004a2404 = 4;
    uRam004a2408 = 0xffffffff;
    _DAT_004a240c = 1;
    _DAT_004a2420 = 1;
    _DAT_004a2410 = local_14;
    uRam004a2414 = 0;
    uRam004a2418 = 4;
    uRam004a241c = 0xffffffff;
    DAT_004a23d4 = (short)UVar1;
  }
  return this;
}



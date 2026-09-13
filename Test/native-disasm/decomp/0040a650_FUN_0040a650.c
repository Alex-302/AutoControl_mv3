// FUN_0040a650 @ 0040a650 size=265 callers=2

void * __thiscall FUN_0040a650(void *this,undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 in_XMM2_Da;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  *(undefined4 *)this = 0;
  iVar1 = GdipCreateFontFamilyFromName(param_1,0,&local_c);
  local_8 = 0;
  *(int *)((int)this + 4) = iVar1;
  uVar2 = local_c;
  if (iVar1 != 0) {
    puVar3 = DAT_004a2494;
    if (DAT_004a2494 == (undefined4 *)0x0) {
      DAT_004a2494 = &DAT_004a248c;
      uVar2 = GdipGetGenericFontFamilySansSerif(&DAT_004a248c);
      puVar3 = DAT_004a2494;
      DAT_004a2494[1] = uVar2;
    }
    iVar1 = puVar3[1];
    uVar2 = *puVar3;
    *(int *)((int)this + 4) = iVar1;
    if (iVar1 != 0) {
      GdipDeleteFontFamily(local_c);
      return this;
    }
  }
  iVar1 = GdipCreateFont(uVar2,in_XMM2_Da,0,3,this);
  *(int *)((int)this + 4) = iVar1;
  if (iVar1 != 0) {
    puVar3 = DAT_004a2494;
    if (DAT_004a2494 == (undefined4 *)0x0) {
      DAT_004a2494 = &DAT_004a248c;
      uVar2 = GdipGetGenericFontFamilySansSerif(&DAT_004a248c);
      puVar3 = DAT_004a2494;
      DAT_004a2494[1] = uVar2;
    }
    iVar1 = puVar3[1];
    uVar2 = *puVar3;
    *(int *)((int)this + 4) = iVar1;
    if (iVar1 == 0) {
      uVar2 = GdipCreateFont(uVar2,in_XMM2_Da,0,3,this);
      *(undefined4 *)((int)this + 4) = uVar2;
    }
  }
  GdipDeleteFontFamily(local_c);
  return this;
}



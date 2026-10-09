// FUN_004052c0 @ 004052c0 size=377 callers=1

/* WARNING: Removing unreachable block (ram,0x00405307) */
/* WARNING: Removing unreachable block (ram,0x00405352) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_004052c0(void)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  byte local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004793b9;
  local_10 = ExceptionList;
  _DAT_004a2580 = 0;
  DAT_004a2594 = 0xf;
  _DAT_004a2588 = 0;
  _DAT_004a258c = 0;
  DAT_004a258e = 0;
  DAT_004a2590 = 0xf;
  DAT_004a258f = 0;
  local_8 = 0;
  ExceptionList = &local_10;
  GetLocaleInfoA(0x800,0x59,(LPSTR)&DAT_004a2580,0xf);
  local_14[0] = 0;
  iVar1 = FUN_0043ab50(&DAT_004a2580,local_14,extraout_ECX,1);
  puVar2 = &DAT_004a2580;
  if (0xf < DAT_004a2594) {
    puVar2 = DAT_004a2580;
  }
  *(undefined1 *)((int)puVar2 + iVar1) = 0x2d;
  puVar2 = &DAT_004a2580;
  if (0xf < DAT_004a2594) {
    puVar2 = DAT_004a2580;
  }
  GetLocaleInfoA(0x800,0x5a,(LPSTR)((int)puVar2 + iVar1 + 1),DAT_004a2590 - (iVar1 + 1));
  local_14[0] = 0;
  uVar3 = FUN_0043ab50(&DAT_004a2580,local_14,extraout_ECX_00,1);
  if (uVar3 <= DAT_004a2590) {
    puVar2 = &DAT_004a2580;
    if (0xf < DAT_004a2594) {
      puVar2 = DAT_004a2580;
    }
    DAT_004a2590 = uVar3;
    *(undefined1 *)((int)puVar2 + uVar3) = 0;
    ExceptionList = local_10;
    return &DAT_004a2580;
  }
  FUN_0043aef0(&DAT_004a2580,uVar3 - DAT_004a2590,'\0');
  ExceptionList = local_10;
  return &DAT_004a2580;
}



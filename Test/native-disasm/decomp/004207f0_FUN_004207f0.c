// FUN_004207f0 @ 004207f0 size=863 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004207f0(void *this,undefined1 *param_1,undefined4 param_2,int *param_3)

{
  byte *pbVar1;
  int *piVar2;
  bool bVar3;
  undefined2 uVar4;
  byte *this_00;
  short *psVar5;
  UINT_PTR UVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined **local_4c;
  void *local_48;
  undefined4 *puStack_44;
  LONG LStack_40;
  LONG LStack_3c;
  undefined ***local_28;
  void *local_24;
  undefined4 *puStack_20;
  tagPOINT tStack_1c;
  undefined1 local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047bb18;
  local_10 = ExceptionList;
  local_12 = 0;
  local_11 = *(char *)((int)this + 0x1e);
  ExceptionList = &local_10;
  *(undefined1 *)((int)this + 0x1f) = 0x44;
  puVar7 = &DAT_004a2538;
  if (0xf < DAT_004a254c) {
    puVar7 = DAT_004a2538;
  }
  switch(local_11 + -1 + (uint)(byte)(*(char *)((int)puVar7 + 2) - *(char *)(puVar7 + 0xc))) {
  case 1:
    local_12 = *(undefined1 *)((int)this + 0xc);
    break;
  case 2:
  case 7:
    if (*(int *)((int)this + 0x10) == 0) {
      tStack_1c.x._0_3_ = CONCAT12(local_11,*(undefined2 *)((int)this + 0xe));
      local_48 = (void *)tStack_1c.x;
      local_28 = &local_4c;
      local_4c = &PTR_LAB_0048e8c0;
      puStack_44 = (undefined4 *)DAT_004a29e8;
      local_8 = 0;
      UVar6 = FUN_0040fca0((uint)*(ushort *)((int)this + 0xc),(int *)local_28);
      local_8 = 0xffffffff;
      *(UINT_PTR *)((int)this + 0x10) = UVar6;
      piVar2 = DAT_004a2608;
      if (local_28 != (undefined ***)0x0) {
        (*(code *)(*local_28)[4])(local_28 != &local_4c);
        piVar2 = DAT_004a2608;
      }
      for (; piVar2 != DAT_004a260c; piVar2 = piVar2 + 1) {
        if ((void *)*piVar2 == this) {
          if ((piVar2 != DAT_004a260c) && ((int)piVar2 - (int)DAT_004a2608 >> 2 != -1))
          goto switchD_00420858_default;
          break;
        }
      }
      param_3 = this;
      FUN_00432e80(&DAT_004a2608,&param_3);
    }
    break;
  case 3:
    if (*(char *)((int)this + 0xe) == '\0') {
      if ((DAT_004a264b == 'S') ||
         (uVar4 = FUN_004190a0((byte *)&DAT_004a2614), DAT_004a264c == 'B')) break;
      local_48 = (void *)CONCAT22(local_48._2_2_,uVar4);
      local_28 = &local_4c;
      local_4c = &PTR_LAB_0048f0b8;
      local_8 = 2;
      FUN_0040fab0((int *)local_28);
    }
    else {
      if (DAT_004a264b != 'S') break;
      if (200 < (uint)(DAT_004a26b4 - _DAT_004a32e8)) {
        GetCursorPos(&tStack_1c);
        DAT_004a2a48 = tStack_1c.x;
        DAT_004a2a4c = tStack_1c.y;
        _DAT_004a32e8 = DAT_004a26b4;
      }
      tStack_1c.x = DAT_004a2a48;
      tStack_1c.y = DAT_004a2a4c;
      FUN_00419030(&DAT_004a2614,&tStack_1c.x,this);
      *(undefined1 *)((int)this + 0x1f) = 0x49;
      if (3 < (uint)(DAT_004a25e4 - ram0x004a25e0)) break;
      tStack_1c.x = CONCAT22(tStack_1c.x._2_2_,DAT_004a26c2);
      tStack_1c.y = DAT_004a29e8;
      local_28 = &local_4c;
      puStack_20 = &DAT_004a2614;
      local_4c = &PTR_LAB_0048e508;
      puStack_44 = &DAT_004a2614;
      LStack_40 = tStack_1c.x;
      LStack_3c = DAT_004a29e8;
      local_8 = 1;
      local_48 = this;
      local_24 = this;
      UVar6 = FUN_0040fd50((uint)*(ushort *)((int)this + 0xc),(int *)local_28);
      *(UINT_PTR *)((int)this + 0x10) = UVar6;
    }
    FUN_0040fe40((int *)&local_4c);
    break;
  case 4:
    FUN_0040fb40((UINT_PTR *)(*param_3 + ((uint)*(ushort *)((int)this + 0xc) * 9 + 4) * 4),'\x01');
    break;
  case 5:
    puVar7 = &DAT_004a2538;
    if (0xf < DAT_004a254c) {
      puVar7 = DAT_004a2538;
    }
    *(char *)(*param_3 + 0x1f + (uint)*(ushort *)((int)this + 0xc) * 0x24) =
         *(char *)((int)puVar7 + 10) - *(char *)((int)puVar7 + 0x3e);
    break;
  case 6:
    bVar8 = *(byte *)((int)this + 0xe);
    pbVar1 = (byte *)((int)this + 0xc);
    this_00 = FUN_00433710(pbVar1);
    FUN_0041fd20(this_00,bVar8);
    if (DAT_004a25ec != DAT_004a25f0) {
      psVar5 = DAT_004a25ec;
      do {
        if (*psVar5 == *(short *)pbVar1) {
          if ((psVar5 != DAT_004a25f0) && ((int)psVar5 - (int)DAT_004a25ec >> 1 != -1))
          goto switchD_00420858_caseD_0;
          break;
        }
        psVar5 = psVar5 + 1;
      } while (psVar5 != DAT_004a25f0);
    }
    FUN_00433540(&DAT_004a25ec,(undefined2 *)pbVar1);
  case 0:
switchD_00420858_caseD_0:
    if ((DAT_004a26c2 & 0xfc00) == 0x1000) {
      DAT_0049fc44 = 1;
    }
    if ((*(char *)((int)this + 0x1e) == '\x01') &&
       ((*(char *)((int)this + 0x22) != '\0' || (bVar3 = FUN_00413200(&DAT_004a26b0), bVar3)))) {
      FUN_00432e80((void *)((int)&DAT_004a25dd + 3),(undefined4 *)((int)this + 0xc));
    }
  }
switchD_00420858_default:
  *param_1 = *(undefined1 *)((int)this + 0x21);
  param_1[1] = local_12;
  ExceptionList = local_10;
  return;
}



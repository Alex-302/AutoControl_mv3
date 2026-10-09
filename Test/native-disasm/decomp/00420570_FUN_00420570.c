// FUN_00420570 @ 00420570 size=517 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __thiscall FUN_00420570(void *this,undefined4 param_1,int *param_2)

{
  char cVar1;
  void *pvVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  bool bVar6;
  undefined4 in_EAX;
  undefined3 uVar7;
  uint uVar8;
  uint extraout_ECX;
  bool bVar9;
  ushort uVar10;
  void *this_00;
  bool local_1b;
  bool local_1a;
  int *local_18;
  
  uVar8 = (uint)this & 0xffffff00;
  local_1b = false;
  cVar5 = *(char *)((int)this + 0x1e);
  uVar7 = (undefined3)((uint)in_EAX >> 8);
  local_18 = (int *)CONCAT31(uVar7,cVar5);
  if (cVar5 == '\x04') {
    if ((DAT_004a264a != '\0') ||
       ((local_18 = (int *)CONCAT31(uVar7,DAT_004a264c), DAT_004a264c != 'B' && (DAT_004a2a18 == 0))
       )) goto LAB_00420596;
    local_1b = DAT_004a264c == 'B';
    uVar8 = CONCAT31((int3)((uint)this >> 8),local_1b);
  }
  else if (cVar5 == '\x01') {
    local_18 = ram0x004a25e0;
    if (ram0x004a25e0 != DAT_004a25e4) {
      do {
        if (*local_18 == *(int *)((int)this + 0xc)) {
          if ((local_18 != DAT_004a25e4) &&
             (local_18 = (int *)((int)local_18 - (int)ram0x004a25e0 >> 2), -1 < (int)local_18))
          goto LAB_00420596;
          break;
        }
        local_18 = local_18 + 1;
      } while (local_18 != DAT_004a25e4);
    }
    uVar8 = (uint)DAT_004a25e4 & 0xffffff00;
  }
  this_00 = *(void **)this;
  local_18 = (int *)((uint)local_18 & 0xffffff00);
  pvVar2 = *(void **)((int)this + 4);
  bVar6 = true;
  local_1a = true;
  while( true ) {
    if (this_00 == pvVar2) {
      return (int *)CONCAT31((int3)((uint)local_18 >> 8),bVar6);
    }
    if (((char)uVar8 != '\0') &&
       (((((cVar5 = *(char *)((int)this_00 + 7), cVar5 == '\x02' || (cVar5 == '\n')) ||
          (cVar5 == '\x03')) || ((cVar5 == '\r' || (cVar5 == '\f')))) ||
        ((cVar5 == '\x0e' || (cVar5 == '\x05')))))) goto LAB_0042075a;
    cVar5 = (char)local_18;
    if ((bVar6 == false) || (cVar5 != 'O')) {
      bVar6 = FUN_00420050(this_00,(int)this,uVar8,param_2);
      uVar10 = CONCAT11((bool)*(char *)((int)this_00 + 6) != bVar6,local_1a);
      uVar8 = extraout_ECX;
    }
    else {
      uVar10 = CONCAT11(1,bVar6);
    }
    bVar9 = SUB21(uVar10,0);
    bVar6 = SUB21(uVar10 >> 8,0);
    if (*(char *)((int)this_00 + 7) != '\x05') break;
    cVar1 = *(char *)((int)this_00 + 5);
    uVar7 = (undefined3)(uVar8 >> 8);
    uVar8 = CONCAT31(uVar7,cVar1);
    if ((cVar1 == 'S') && (cVar5 == '\0')) break;
    bVar3 = false;
    bVar4 = false;
    switch(cVar5) {
    case '&':
      if ((bVar9 != false) && (bVar6 != false)) goto LAB_004206b9;
LAB_004206c5:
      local_1a = false;
      break;
    case '=':
      local_1a = bVar9 == bVar6;
      break;
    case 'O':
      bVar4 = bVar9 != false;
    default:
      bVar3 = bVar4;
      local_1a = bVar6;
      break;
    case '|':
      if ((bVar9 == false) && (bVar6 == false)) goto LAB_004206c5;
LAB_004206b9:
      local_1a = true;
    }
    if (cVar1 == 'S') {
LAB_0042074c:
      local_18 = (int *)0x0;
      if (local_1a == false) {
        return (int *)0x0;
      }
LAB_00420756:
      uVar8 = CONCAT31((int3)(uVar8 >> 8),local_1b);
      bVar6 = local_1a;
    }
    else {
      uVar8 = CONCAT31(uVar7,local_1b);
      bVar6 = local_1a;
      if (!bVar3) {
        local_18 = (int *)(uint)*(byte *)((int)this_00 + 3);
      }
    }
LAB_0042075a:
    this_00 = (void *)((int)this_00 + 8);
  }
  cVar5 = *(char *)((int)this_00 + 5);
  local_18 = (int *)((uint)local_18 & 0xff);
  if (cVar5 == 'F') {
    local_18 = (int *)0x4f;
  }
  uVar8 = 0;
  if (cVar5 != 'F') {
    uVar8 = uVar10 & 0xff;
  }
  local_1a = SUB41(uVar8,0);
  if ((char)local_18 == 'O') {
    local_1a = (bool)(local_1a | bVar6);
  }
  else if (bVar6 == false) {
LAB_00420596:
    return (int *)((uint)local_18 & 0xffffff00);
  }
  if (cVar5 == 'L') goto LAB_0042074c;
  goto LAB_00420756;
}



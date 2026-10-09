// _memcmp @ 0045d228 size=5886 callers=2

/* Library Function - Single Match
    _memcmp
   
   Library: Visual Studio 2015 Release */

int __cdecl _memcmp(void *_Buf1,void *_Buf2,size_t _Size)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  if (_Size == 0) {
    return 0;
  }
  if (_Size == 1) {
    uVar3 = (uint)*(byte *)_Buf1;
    uVar1 = (uint)*(byte *)_Buf2;
LAB_0045e87d:
    if (uVar3 == uVar1) {
      return 0;
    }
    return (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
  }
  if (_Size == 2) {
    uVar3 = (uint)*(byte *)_Buf1;
    uVar1 = (uint)*(byte *)_Buf2;
    if ((uVar3 != uVar1) &&
       (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
      return iVar2;
    }
    uVar3 = (uint)*(byte *)((int)_Buf1 + 1);
    uVar1 = (uint)*(byte *)((int)_Buf2 + 1);
    goto LAB_0045e87d;
  }
  if (_Size == 3) {
    uVar3 = (uint)*(byte *)_Buf1;
    uVar1 = (uint)*(byte *)_Buf2;
    if ((uVar3 != uVar1) &&
       (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
      return iVar2;
    }
    uVar3 = (uint)*(byte *)((int)_Buf1 + 1);
    uVar1 = (uint)*(byte *)((int)_Buf2 + 1);
    if ((uVar3 != uVar1) &&
       (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
      return iVar2;
    }
    uVar3 = (uint)*(byte *)((int)_Buf1 + 2);
    uVar1 = (uint)*(byte *)((int)_Buf2 + 2);
    goto LAB_0045e87d;
  }
  if (_Size == 4) {
    uVar1 = (uint)*(byte *)_Buf2;
    uVar3 = (uint)*(byte *)_Buf1;
    if ((uVar3 != uVar1) &&
       (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
      return iVar2;
    }
    uVar3 = (uint)*(byte *)((int)_Buf1 + 1);
    uVar1 = (uint)*(byte *)((int)_Buf2 + 1);
    if ((uVar3 != uVar1) &&
       (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
      return iVar2;
    }
    uVar3 = (uint)*(byte *)((int)_Buf1 + 2);
    uVar1 = (uint)*(byte *)((int)_Buf2 + 2);
    if ((uVar3 != uVar1) &&
       (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
      return iVar2;
    }
    uVar3 = (uint)*(byte *)((int)_Buf1 + 3);
    uVar1 = (uint)*(byte *)((int)_Buf2 + 3);
    goto LAB_0045e87d;
  }
  for (; 0x1f < _Size; _Size = _Size - 0x20) {
    if (*(uint *)_Buf1 == *(uint *)_Buf2) {
      iVar2 = 0;
    }
    else {
      uVar3 = *(uint *)_Buf1 & 0xff;
      uVar1 = (uint)(byte)*(uint *)_Buf2;
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 1);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 1);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 2);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 2);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      iVar2 = 0;
      if ((uint)*(byte *)((int)_Buf1 + 3) != (uint)*(byte *)((int)_Buf2 + 3)) {
        iVar2 = (uint)(0 < (int)((uint)*(byte *)((int)_Buf1 + 3) - (uint)*(byte *)((int)_Buf2 + 3)))
                * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
    if (*(uint *)((int)_Buf1 + 4) == *(uint *)((int)_Buf2 + 4)) {
      iVar2 = 0;
    }
    else {
      uVar3 = *(uint *)((int)_Buf1 + 4) & 0xff;
      uVar1 = (uint)(byte)*(uint *)((int)_Buf2 + 4);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 5);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 5);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 6);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 6);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      iVar2 = 0;
      if ((uint)*(byte *)((int)_Buf1 + 7) != (uint)*(byte *)((int)_Buf2 + 7)) {
        iVar2 = (uint)(0 < (int)((uint)*(byte *)((int)_Buf1 + 7) - (uint)*(byte *)((int)_Buf2 + 7)))
                * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
    if (*(uint *)((int)_Buf1 + 8) == *(uint *)((int)_Buf2 + 8)) {
      iVar2 = 0;
    }
    else {
      uVar3 = *(uint *)((int)_Buf1 + 8) & 0xff;
      uVar1 = (uint)(byte)*(uint *)((int)_Buf2 + 8);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 9);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 9);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 10);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 10);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      iVar2 = 0;
      if ((uint)*(byte *)((int)_Buf1 + 0xb) != (uint)*(byte *)((int)_Buf2 + 0xb)) {
        iVar2 = (uint)(0 < (int)((uint)*(byte *)((int)_Buf1 + 0xb) -
                                (uint)*(byte *)((int)_Buf2 + 0xb))) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
    if (*(uint *)((int)_Buf1 + 0xc) == *(uint *)((int)_Buf2 + 0xc)) {
      iVar2 = 0;
    }
    else {
      uVar3 = *(uint *)((int)_Buf1 + 0xc) & 0xff;
      uVar1 = (uint)(byte)*(uint *)((int)_Buf2 + 0xc);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 0xd);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 0xd);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 0xe);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 0xe);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      iVar2 = 0;
      if ((uint)*(byte *)((int)_Buf1 + 0xf) != (uint)*(byte *)((int)_Buf2 + 0xf)) {
        iVar2 = (uint)(0 < (int)((uint)*(byte *)((int)_Buf1 + 0xf) -
                                (uint)*(byte *)((int)_Buf2 + 0xf))) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
    if (*(uint *)((int)_Buf1 + 0x10) == *(uint *)((int)_Buf2 + 0x10)) {
      iVar2 = 0;
    }
    else {
      uVar1 = (uint)(byte)*(uint *)((int)_Buf2 + 0x10);
      uVar3 = (uint)(byte)*(uint *)((int)_Buf1 + 0x10);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 0x11);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 0x11);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 0x12);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 0x12);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      iVar2 = 0;
      if ((uint)*(byte *)((int)_Buf1 + 0x13) != (uint)*(byte *)((int)_Buf2 + 0x13)) {
        iVar2 = (uint)(0 < (int)((uint)*(byte *)((int)_Buf1 + 0x13) -
                                (uint)*(byte *)((int)_Buf2 + 0x13))) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
    if (*(uint *)((int)_Buf1 + 0x14) == *(uint *)((int)_Buf2 + 0x14)) {
      iVar2 = 0;
    }
    else {
      uVar3 = *(uint *)((int)_Buf1 + 0x14) & 0xff;
      uVar1 = (uint)(byte)*(uint *)((int)_Buf2 + 0x14);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 0x15);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 0x15);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 0x16);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 0x16);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      iVar2 = 0;
      if ((uint)*(byte *)((int)_Buf1 + 0x17) != (uint)*(byte *)((int)_Buf2 + 0x17)) {
        iVar2 = (uint)(0 < (int)((uint)*(byte *)((int)_Buf1 + 0x17) -
                                (uint)*(byte *)((int)_Buf2 + 0x17))) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
    if (*(uint *)((int)_Buf1 + 0x18) == *(uint *)((int)_Buf2 + 0x18)) {
      iVar2 = 0;
    }
    else {
      uVar3 = *(uint *)((int)_Buf1 + 0x18) & 0xff;
      uVar1 = (uint)(byte)*(uint *)((int)_Buf2 + 0x18);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 0x19);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 0x19);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 0x1a);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 0x1a);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      iVar2 = 0;
      if ((uint)*(byte *)((int)_Buf1 + 0x1b) != (uint)*(byte *)((int)_Buf2 + 0x1b)) {
        iVar2 = (uint)(0 < (int)((uint)*(byte *)((int)_Buf1 + 0x1b) -
                                (uint)*(byte *)((int)_Buf2 + 0x1b))) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
    if (*(uint *)((int)_Buf1 + 0x1c) == *(uint *)((int)_Buf2 + 0x1c)) {
      iVar2 = 0;
    }
    else {
      uVar3 = *(uint *)((int)_Buf1 + 0x1c) & 0xff;
      uVar1 = (uint)(byte)*(uint *)((int)_Buf2 + 0x1c);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 0x1d);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 0x1d);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + 0x1e);
      uVar1 = (uint)*(byte *)((int)_Buf2 + 0x1e);
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      iVar2 = 0;
      if ((uint)*(byte *)((int)_Buf1 + 0x1f) != (uint)*(byte *)((int)_Buf2 + 0x1f)) {
        iVar2 = (uint)(0 < (int)((uint)*(byte *)((int)_Buf1 + 0x1f) -
                                (uint)*(byte *)((int)_Buf2 + 0x1f))) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
    _Buf1 = (void *)((int)_Buf1 + 0x20);
    _Buf2 = (void *)((int)_Buf2 + 0x20);
  }
  switch(_Size) {
  default:
    goto switchD_0045d71d_caseD_0;
  case 1:
    goto switchD_0045d71d_caseD_1;
  case 2:
    goto switchD_0045d71d_caseD_2;
  case 3:
    goto switchD_0045d71d_caseD_3;
  case 4:
    goto switchD_0045d71d_caseD_4;
  case 5:
    goto switchD_0045d71d_caseD_5;
  case 6:
    goto switchD_0045d71d_caseD_6;
  case 7:
    goto switchD_0045d71d_caseD_7;
  case 8:
    goto switchD_0045d71d_caseD_8;
  case 9:
    goto switchD_0045d71d_caseD_9;
  case 10:
    goto switchD_0045d71d_caseD_a;
  case 0xb:
    goto switchD_0045d71d_caseD_b;
  case 0xc:
    goto switchD_0045d71d_caseD_c;
  case 0xd:
    goto switchD_0045d71d_caseD_d;
  case 0xe:
    goto switchD_0045d71d_caseD_e;
  case 0xf:
    goto switchD_0045d71d_caseD_f;
  case 0x10:
    goto switchD_0045d71d_caseD_10;
  case 0x11:
    goto switchD_0045d71d_caseD_11;
  case 0x12:
    goto switchD_0045d71d_caseD_12;
  case 0x13:
    goto switchD_0045d71d_caseD_13;
  case 0x14:
    goto switchD_0045d71d_caseD_14;
  case 0x15:
    goto switchD_0045d71d_caseD_15;
  case 0x16:
    goto switchD_0045d71d_caseD_16;
  case 0x17:
    goto switchD_0045d71d_caseD_17;
  case 0x18:
    goto switchD_0045d71d_caseD_18;
  case 0x1a:
    goto switchD_0045d71d_caseD_1a;
  case 0x1b:
    goto switchD_0045d71d_caseD_1b;
  case 0x1c:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x1c));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x1c))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1c));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1b));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1b));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1a));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1a));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x19));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x19));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_18:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x18));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x18))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x18));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x17));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x17));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x16));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x16));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x15));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x15));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_14:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x14));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x14))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x14));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x13));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x13));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x12));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x12));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x11));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x11));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_10:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x10));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x10))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x10));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xf));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xf));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xe));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xe));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xd));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xd));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_c:
    if (*(int *)((int)_Buf1 + (_Size - 0xc)) == *(int *)((int)_Buf2 + (_Size - 0xc))) {
      iVar2 = 0;
    }
    else {
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xc));
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xc));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xb));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xb));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 10));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 10));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 9));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 9));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_8:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 8));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 8))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 8));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 7));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 7));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 6));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 6));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 5));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 5));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_4:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 4));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 4))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 4));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 3));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 3));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 2));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 2));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 1));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 1));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 == 0) {
switchD_0045d71d_caseD_0:
      iVar2 = 0;
    }
    return iVar2;
  case 0x1d:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x1d));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x1d))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1d));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1c));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1c));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1b));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1b));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1a));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1a));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  case 0x19:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x19));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x19))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x19));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x18));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x18));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x17));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x17));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x16));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x16));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_15:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x15));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x15))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x15));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x14));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x14));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x13));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x13));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x12));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x12));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_11:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x11));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x11))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x11));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x10));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x10));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xf));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xf));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xe));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xe));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_d:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0xd));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0xd))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xd));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xc));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xc));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xb));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xb));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 10));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 10));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_9:
    if (*(int *)((int)_Buf1 + (_Size - 9)) == *(int *)((int)_Buf2 + (_Size - 9))) {
      iVar2 = 0;
    }
    else {
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 9));
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 9));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 8));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 8));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 7));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 7));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 6));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 6));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_5:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 5));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 5))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 5));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 4));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 4));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 3));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 3));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 2));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 2));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
LAB_0045df46:
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_1:
    uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 1));
    uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 1));
    if (uVar3 == uVar1) {
      return 0;
    }
    return (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
  case 0x1e:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x1e));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x1e))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1e));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1d));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1d));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1c));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1c));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1b));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1b));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_1a:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x1a));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x1a))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1a));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x19));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x19));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x18));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x18));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x17));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x17));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_16:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x16));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x16))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x16));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x15));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x15));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x14));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x14));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x13));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x13));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_12:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x12));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x12))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x12));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x11));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x11));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x10));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x10));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xf));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xf));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_e:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0xe));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0xe))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xe));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xd));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xd));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xc));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xc));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xb));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xb));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_a:
    if (*(int *)((int)_Buf1 + (_Size - 10)) == *(int *)((int)_Buf2 + (_Size - 10))) {
      iVar2 = 0;
    }
    else {
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 10));
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 10));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 9));
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 9));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 8));
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 8));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 7));
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 7));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_6:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 6));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 6))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 6));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 5));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 5));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 4));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 4));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 3));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 3));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_2:
    if (*(short *)((int)_Buf1 + (_Size - 2)) != *(short *)((int)_Buf2 + (_Size - 2))) {
LAB_0045e7eb:
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 2));
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 2));
      if (uVar3 == uVar1) goto switchD_0045d71d_caseD_1;
      iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1;
      goto LAB_0045df46;
    }
    goto switchD_0045d71d_caseD_0;
  case 0x1f:
    if (*(int *)((int)_Buf1 + (_Size - 0x1f)) == *(int *)((int)_Buf2 + (_Size - 0x1f))) {
      iVar2 = 0;
    }
    else {
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1f));
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1f));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1e));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1e));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1d));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1d));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1c));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1c));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_1b:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x1b));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x1b))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1b));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x1a));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x1a));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x19));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x19));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x18));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x18));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_17:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x17));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x17))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x17));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x16));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x16));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x15));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x15));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x14));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x14));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_13:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0x13));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0x13))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x13));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x12));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x12));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x11));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x11));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0x10));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0x10));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_f:
    if (*(int *)((int)_Buf1 + (_Size - 0xf)) == *(int *)((int)_Buf2 + (_Size - 0xf))) {
      iVar2 = 0;
    }
    else {
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xf));
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xf));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xe));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xe));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xd));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xd));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 0xc));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xc));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_b:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 0xb));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 0xb))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 0xb));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 10));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 10));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 9));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 9));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 8));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 8));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_7:
    uVar1 = *(uint *)((int)_Buf1 + (_Size - 7));
    if (uVar1 == *(uint *)((int)_Buf2 + (_Size - 7))) {
      iVar2 = 0;
    }
    else {
      uVar1 = uVar1 & 0xff;
      uVar3 = (uint)*(byte *)((int)_Buf2 + (_Size - 7));
      if ((uVar1 != uVar3) &&
         (iVar2 = (uint)(uVar1 != uVar3 && -1 < (int)(uVar1 - uVar3)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 6));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 6));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 5));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 5));
      if ((uVar3 != uVar1) &&
         (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
        return iVar2;
      }
      uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 4));
      uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 4));
      iVar2 = 0;
      if (uVar3 != uVar1) {
        iVar2 = (uint)(0 < (int)(uVar3 - uVar1)) * 2 + -1;
      }
    }
    if (iVar2 != 0) {
      return iVar2;
    }
switchD_0045d71d_caseD_3:
    uVar3 = (uint)*(byte *)((int)_Buf1 + (_Size - 3));
    uVar1 = (uint)*(byte *)((int)_Buf2 + (_Size - 3));
    if ((uVar3 != uVar1) &&
       (iVar2 = (uint)(uVar3 != uVar1 && -1 < (int)(uVar3 - uVar1)) * 2 + -1, iVar2 != 0)) {
      return iVar2;
    }
    goto LAB_0045e7eb;
  }
}



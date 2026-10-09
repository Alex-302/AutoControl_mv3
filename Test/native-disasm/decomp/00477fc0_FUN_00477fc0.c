// FUN_00477fc0 @ 00477fc0 size=1311 callers=1

uint __fastcall FUN_00477fc0(void *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ushort in_FPUControlWord;
  undefined1 in_XMM0 [16];
  undefined1 auVar4 [16];
  undefined8 local_10;
  
  auVar4._0_8_ = in_XMM0._0_8_;
  iVar3 = in_XMM0._0_4_;
  uVar2 = in_XMM0._4_4_;
  if (((MXCSR & 0x7f80) != 0x1f80) || ((in_FPUControlWord & 0x7f) != 0x7f)) {
    local_10 = (double)CONCAT44(0x4784d3,(undefined4)local_10);
    uVar2 = FUN_004789af(param_1,iVar3,uVar2);
    return uVar2;
  }
  auVar4._8_8_ = in_XMM0._8_8_ >> 0x2c;
  uVar1 = uVar2 >> 0xc & 0x7ffff;
  if (uVar1 - 0x3fb00 < 0x3bb) {
    return uVar1 - 0x3fb00;
  }
  if (uVar1 - 0x3febb < 0x41) {
    return -(uint)(SUB161(auVar4 >> 0x3f,0) & 1) & 0x8000;
  }
  if (uVar1 - 0x3c300 < 0x3800) {
    return uVar1 - 0x3c300;
  }
  if (uVar1 - 0x3fefc < 4) {
    return in_XMM0._6_2_ & 0x8000;
  }
  if (uVar1 < 0x3ff00) {
    return uVar1;
  }
  if ((uVar2 & 0x7fffffff) != 0x3ff00000 || iVar3 != 0) {
    if ((int)(((uVar2 & 0x7fffffff) + 0x80100000) - (uint)(iVar3 == 0)) < 0) {
      local_10 = -NAN;
      iVar3 = 0x3a;
    }
    else {
      local_10 = auVar4._0_8_ + 0.0;
      iVar3 = 0x3f0;
    }
    uVar2 = ___libm_error_support
                      ((undefined8 *)&stack0xfffffff8,(undefined8 *)&stack0xfffffff8,&local_10,iVar3
                      );
    return uVar2;
  }
  return 0;
}



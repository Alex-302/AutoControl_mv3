// FUN_0046590c @ 0046590c size=487 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl FUN_0046590c(double param_1,int param_2)

{
  int iVar1;
  float10 fVar2;
  double dVar3;
  uint uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  int local_8;
  
  iVar1 = __ctrlfp();
  uVar5 = (undefined2)iVar1;
  uVar6 = (undefined2)((uint)iVar1 >> 0x10);
  uVar4 = (uint)((ulonglong)param_1 >> 0x20);
  if ((param_1._6_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = __sptype(SUB84(param_1,0),uVar4);
    if (0 < iVar1) {
      if (iVar1 < 3) goto LAB_004659b3;
      if (iVar1 == 3) {
        fVar2 = FUN_0046ccbf(param_1,(double)param_2);
        return fVar2;
      }
    }
    dVar3 = _DAT_004851a8 + param_1;
    uVar4 = 8;
    goto LAB_00465ae5;
  }
  if (param_1 == 0.0) {
LAB_004659b3:
    __ctrlfp();
    return (float10)param_1;
  }
  fVar2 = (float10)FUN_0046c79a(SUB84(param_1,0),uVar4,&local_8);
  if (param_2 < 0) {
    if (local_8 < -0x80000000 - param_2) {
LAB_00465a44:
      fVar2 = (float10)0 * fVar2;
LAB_00465a59:
      dVar3 = (double)fVar2;
      uVar4 = 0x12;
      goto LAB_00465ae5;
    }
LAB_004659fb:
    local_8 = local_8 + param_2;
    if (0xa00 < local_8) goto LAB_00465ab3;
    if (local_8 < 0x401) {
      if (local_8 < -0x9fd) goto LAB_00465a44;
      if (-0x3fe < local_8) {
        fVar2 = __set_exp((double)fVar2,(short)local_8);
        __ctrlfp();
        return (float10)(double)fVar2;
      }
      fVar2 = __set_exp((double)fVar2,(short)(local_8 + 0x600));
      goto LAB_00465a59;
    }
    fVar2 = __set_exp((double)fVar2,(short)(local_8 + -0x600));
    dVar3 = (double)fVar2;
  }
  else {
    if (local_8 <= 0x7fffffff - param_2) goto LAB_004659fb;
LAB_00465ab3:
    dVar3 = __copysign(_DAT_004868d8,(double)fVar2);
  }
  uVar4 = 0x11;
LAB_00465ae5:
  fVar2 = FUN_0046c9fd(uVar4,0x19,param_1,(double)param_2,dVar3,CONCAT22(uVar6,uVar5));
  return fVar2;
}



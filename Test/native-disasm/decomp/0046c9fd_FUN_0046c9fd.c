// FUN_0046c9fd @ 0046c9fd size=226 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

float10 __cdecl
FUN_0046c9fd(uint param_1,int param_2,undefined8 param_3,undefined8 param_4,double param_5,
            uint param_6)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  float10 fVar3;
  uint local_90 [12];
  undefined8 local_60;
  uint local_50;
  uint local_14;
  
  local_14 = DAT_0049d070 ^ (uint)&stack0xfffffff0;
  bVar1 = __handle_exc(param_1,&param_5,param_6);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    local_50 = local_50 & 0xffffffe3 | 3;
    local_60 = param_4;
    __raise_exc_ex(local_90,&param_6,param_1,param_2,(uint *)&param_3,(uint *)&param_5,0);
  }
  iVar2 = __errcode(param_1);
  bVar1 = ___acrt_has_user_matherr();
  if ((bVar1) && (iVar2 != 0)) {
    fVar3 = __umatherr(iVar2,param_2,(int)param_3,(int)((ulonglong)param_3 >> 0x20),(int)param_4,
                       (int)((ulonglong)param_4 >> 0x20),SUB84(param_5,0),
                       (int)((ulonglong)param_5 >> 0x20));
  }
  else {
    __set_errno_from_matherr(iVar2);
    __ctrlfp();
    fVar3 = (float10)param_5;
  }
  return fVar3;
}



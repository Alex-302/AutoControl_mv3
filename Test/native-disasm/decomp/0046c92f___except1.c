// __except1 @ 0046c92f size=206 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __except1
   
   Library: Visual Studio 2015 Release */

float10 __cdecl __except1(uint param_1,int param_2,undefined8 param_3,double param_4,uint param_5)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  float10 fVar3;
  uint local_90 [16];
  uint local_50;
  uint local_14;
  
  local_14 = DAT_0049d070 ^ (uint)&stack0xfffffff0;
  bVar1 = __handle_exc(param_1,&param_4,param_5);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    local_50 = local_50 & 0xfffffffe;
    __raise_exc_ex(local_90,&param_5,param_1,param_2,(uint *)&param_3,(uint *)&param_4,0);
  }
  iVar2 = __errcode(param_1);
  bVar1 = ___acrt_has_user_matherr();
  if ((bVar1) && (iVar2 != 0)) {
    fVar3 = __umatherr(iVar2,param_2,(int)param_3,(int)((ulonglong)param_3 >> 0x20),0,0,
                       SUB84(param_4,0),(int)((ulonglong)param_4 >> 0x20));
  }
  else {
    __set_errno_from_matherr(iVar2);
    __ctrlfp();
    fVar3 = (float10)param_4;
  }
  return fVar3;
}



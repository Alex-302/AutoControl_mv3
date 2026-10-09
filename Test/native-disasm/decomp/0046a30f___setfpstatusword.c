// __setfpstatusword @ 0046a30f size=128 callers=1

/* Library Function - Single Match
    __setfpstatusword
   
   Library: Visual Studio 2015 Release */

void __cdecl __setfpstatusword(uint param_1)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  
  ___get_machine_status_x87(0x1f1f001f);
  ___get_machine_status_x87(param_1);
  uVar1 = MXCSR;
  if (0 < DAT_0049f178) {
    bVar2 = ___get_machine_status_sse2(0x1f1f001f);
    bVar3 = ___get_machine_status_sse2(param_1);
    MXCSR = ~CONCAT31(extraout_var,bVar2) & uVar1 | CONCAT31(extraout_var_00,bVar3);
  }
  return;
}



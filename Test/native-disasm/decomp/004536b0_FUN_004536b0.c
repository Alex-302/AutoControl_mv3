// FUN_004536b0 @ 004536b0 size=321 callers=57

/* WARNING: Removing unreachable block (ram,0x00453734) */

void __fastcall FUN_004536b0(char *param_1,uint *param_2)

{
  char cVar1;
  double *pdVar2;
  byte *pbVar3;
  uint *puVar4;
  undefined1 local_54 [24];
  undefined1 local_3c [24];
  undefined **local_24;
  undefined8 local_20;
  undefined4 *local_18;
  undefined1 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e8e0;
  local_10 = ExceptionList;
  cVar1 = *param_1;
  switch(cVar1) {
  case '\x04':
    pbVar3 = (byte *)(param_1 + 8);
    if (cVar1 != '\x04') {
      pbVar3 = (byte *)0x0;
    }
    *param_2 = (uint)*pbVar3;
    return;
  case '\x05':
    break;
  case '\x06':
    puVar4 = (uint *)(param_1 + 8);
    if (cVar1 != '\x06') {
      puVar4 = (uint *)0x0;
    }
    *param_2 = *puVar4;
    return;
  case '\a':
    pdVar2 = (double *)(param_1 + 8);
    if (cVar1 != '\a') {
      pdVar2 = (double *)0x0;
    }
    *param_2 = (int)*pdVar2;
    return;
  default:
    ExceptionList = &local_10;
    puVar4 = (uint *)FUN_00438430(param_1,local_3c);
    local_8 = 0;
    local_18 = (undefined4 *)FUN_00442600(local_54,(uint *)"type must be number, but is ",puVar4);
    local_8 = CONCAT31(local_8._1_3_,1);
    if (0xf < (uint)local_18[5]) {
      local_18 = (undefined4 *)*local_18;
    }
    local_24 = std::exception::vftable;
    local_20 = 0;
    local_14 = 1;
    ___std_exception_copy(&local_18,(undefined4 *)&local_20);
    local_24 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_24,&DAT_0049a03c);
  }
  if ((cVar1 != '\x05') && (cVar1 != '\x06')) {
    *param_2 = uRam00000000;
    return;
  }
  *param_2 = *(uint *)(param_1 + 8);
  return;
}



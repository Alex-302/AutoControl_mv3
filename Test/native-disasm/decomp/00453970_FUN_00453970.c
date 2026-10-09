// FUN_00453970 @ 00453970 size=291 callers=13

/* WARNING: Removing unreachable block (ram,0x004539e5) */

void __fastcall FUN_00453970(char *param_1,ushort *param_2)

{
  char cVar1;
  ushort *puVar2;
  double *pdVar3;
  byte *pbVar4;
  uint *puVar5;
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
    pbVar4 = (byte *)(param_1 + 8);
    if (cVar1 != '\x04') {
      pbVar4 = (byte *)0x0;
    }
    *param_2 = (ushort)*pbVar4;
    return;
  case '\x05':
    if ((cVar1 == '\x05') || (cVar1 == '\x06')) {
      puVar2 = (ushort *)(param_1 + 8);
    }
    else {
      puVar2 = (ushort *)0x0;
    }
    break;
  case '\x06':
    puVar2 = (ushort *)(param_1 + 8);
    if (cVar1 != '\x06') {
      puVar2 = (ushort *)0x0;
    }
    break;
  case '\a':
    pdVar3 = (double *)(param_1 + 8);
    if (cVar1 != '\a') {
      pdVar3 = (double *)0x0;
    }
    *param_2 = (ushort)(int)*pdVar3;
    return;
  default:
    ExceptionList = &local_10;
    puVar5 = (uint *)FUN_00438430(param_1,local_3c);
    local_8 = 0;
    local_18 = (undefined4 *)FUN_00442600(local_54,(uint *)"type must be number, but is ",puVar5);
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
  *param_2 = *puVar2;
  return;
}



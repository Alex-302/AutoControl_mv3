// FUN_00428830 @ 00428830 size=274 callers=1

undefined1 * __cdecl FUN_00428830(undefined1 *param_1,void *param_2)

{
  undefined4 *this;
  char *pcVar1;
  uint uVar2;
  char cVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  void *local_44 [4];
  undefined4 local_34;
  uint local_30;
  char local_2c [20];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c7ac;
  local_10 = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_10;
  this = FUN_00440e70(param_2,(uint *)&DAT_0048cf30);
  pcVar1 = (char *)FUN_00434600(this,0);
  FUN_004536b0(pcVar1,&local_14);
  pcVar1 = (char *)FUN_00434600(this,1);
  uVar2 = FUN_004421c0(*(int *)(local_14 + 0x28),pcVar1);
  if ((char)uVar2 != '\0') {
    uVar5 = 6;
    pcVar1 = "params";
    local_30 = 0xf;
    local_34 = 0;
    local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
    uVar4 = 0x4288b4;
    FUN_0043ace0(local_44,(uint *)"params",6);
    local_8._0_1_ = 1;
    local_8._1_3_ = 0;
    cVar3 = '\0';
    FUN_004381d0(&stack0xffffffac,'\0');
    local_8._0_1_ = 0;
    FUN_00442200(param_2,local_2c,local_44,cVar3,uVar4,pcVar1,uVar5);
    local_8 = CONCAT31(local_8._1_3_,2);
    if (*(int **)(local_14 + 0x24) == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_00458e87();
    }
    (**(code **)(**(int **)(local_14 + 0x24) + 8))();
    FUN_00434820(local_2c);
    if (0xf < local_30) {
      FUN_00402430(local_44[0],local_30 + 1,1);
    }
  }
  local_8 = 3;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}



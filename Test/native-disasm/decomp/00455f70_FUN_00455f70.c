// FUN_00455f70 @ 00455f70 size=240 callers=1

ushort * __thiscall FUN_00455f70(void *this,char *param_1,int *param_2,int param_3,int param_4)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  undefined4 uVar4;
  char *pcVar5;
  ushort local_18 [2];
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_0047eaf1;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffd4;
  uStack_7 = 0;
  ExceptionList = &local_10;
  while( true ) {
    local_8 = 0;
    uVar4 = FUN_004383a0(&param_1,(int *)&stack0x00000014);
    if ((char)uVar4 != '\0') break;
    pcVar5 = FUN_00433bc0(&param_1);
    local_8 = 1;
    if (this != (ushort *)0x0) {
      FUN_00453970(pcVar5,local_18);
      *(ushort *)this = local_18[0];
    }
    this = (void *)((int)this + 2);
    if (*param_1 == '\x01') {
      if (*(char *)((int)param_2 + 0xd) == '\0') {
        piVar2 = (int *)param_2[2];
        if (*(char *)((int)piVar2 + 0xd) == '\0') {
          cVar1 = *(char *)(*piVar2 + 0xd);
          param_2 = piVar2;
          piVar2 = (int *)*piVar2;
          while (cVar1 == '\0') {
            cVar1 = *(char *)(*piVar2 + 0xd);
            param_2 = piVar2;
            piVar2 = (int *)*piVar2;
          }
        }
        else {
          cVar1 = *(char *)(param_2[1] + 0xd);
          piVar3 = (int *)param_2[1];
          piVar2 = param_2;
          while ((param_2 = piVar3, cVar1 == '\0' && (piVar2 == (int *)param_2[2]))) {
            cVar1 = *(char *)(param_2[1] + 0xd);
            piVar3 = (int *)param_2[1];
            piVar2 = param_2;
          }
        }
      }
    }
    else if (*param_1 == '\x02') {
      param_3 = param_3 + 0x10;
    }
    else {
      param_4 = param_4 + 1;
    }
  }
  ExceptionList = local_10;
  return this;
}



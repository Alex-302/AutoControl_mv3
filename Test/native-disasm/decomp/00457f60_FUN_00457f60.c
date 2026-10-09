// FUN_00457f60 @ 00457f60 size=379 callers=1

undefined4 * __thiscall FUN_00457f60(void *this,char *param_1,int *param_2,int param_3,int param_4)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  int *piVar6;
  int *piVar7;
  char cVar8;
  undefined4 uVar9;
  char *pcVar10;
  undefined1 *puVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  int *in_stack_00000024;
  int in_stack_00000028;
  char local_9;
  uint local_8;
  undefined4 *local_4;
  
  local_4 = this;
  uVar9 = FUN_004383a0(&param_1,(int *)&stack0x00000014);
  cVar8 = (char)uVar9;
  do {
    if (cVar8 != '\0') {
      *(int **)this = in_stack_00000024;
      *(int *)((int)this + 4) = in_stack_00000028;
      return this;
    }
    pcVar10 = FUN_00433bc0(&param_1);
    FUN_00451420(pcVar10,&local_9);
    piVar6 = in_stack_00000024;
    iVar2 = *in_stack_00000024;
    iVar14 = in_stack_00000028 - iVar2;
    iVar3 = in_stack_00000024[1];
    iVar4 = in_stack_00000024[2];
    if ((iVar3 == iVar4) && (iVar4 == iVar3)) {
      if (iVar2 - iVar3 == 1) {
                    /* WARNING: Subroutine does not return */
        FUN_00458ec4("vector<T> too long");
      }
      uVar13 = iVar4 - iVar2;
      uVar15 = (iVar3 - iVar2) + 1;
      uVar12 = 0;
      if (uVar13 <= ~(uVar13 >> 1)) {
        uVar12 = (uVar13 >> 1) + uVar13;
      }
      if (uVar15 <= uVar12) {
        uVar15 = uVar12;
      }
      FUN_0043d780(in_stack_00000024,uVar15);
    }
    if ((char *)piVar6[1] != (char *)0x0) {
      *(char *)piVar6[1] = local_9;
    }
    piVar6[1] = piVar6[1] + 1;
    puVar5 = (undefined1 *)piVar6[1];
    puVar11 = (undefined1 *)(*piVar6 + iVar14);
    puVar1 = puVar5 + -1;
    if ((puVar11 != puVar1) && (puVar1 != puVar5)) {
      local_8 = local_8 & 0xffffff00;
      FUN_00458570(puVar11,puVar1,puVar5);
    }
    in_stack_00000028 = *piVar6 + 1 + iVar14;
    if (*param_1 == '\x01') {
      if (*(char *)((int)param_2 + 0xd) == '\0') {
        piVar6 = (int *)param_2[2];
        if (*(char *)((int)piVar6 + 0xd) == '\0') {
          cVar8 = *(char *)(*piVar6 + 0xd);
          param_2 = piVar6;
          piVar6 = (int *)*piVar6;
          while (cVar8 == '\0') {
            cVar8 = *(char *)(*piVar6 + 0xd);
            param_2 = piVar6;
            piVar6 = (int *)*piVar6;
          }
        }
        else {
          cVar8 = *(char *)(param_2[1] + 0xd);
          piVar7 = (int *)param_2[1];
          piVar6 = param_2;
          while ((param_2 = piVar7, cVar8 == '\0' && (piVar6 == (int *)param_2[2]))) {
            cVar8 = *(char *)(param_2[1] + 0xd);
            piVar7 = (int *)param_2[1];
            piVar6 = param_2;
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
    uVar9 = FUN_004383a0(&param_1,(int *)&stack0x00000014);
    cVar8 = (char)uVar9;
    this = local_4;
  } while( true );
}



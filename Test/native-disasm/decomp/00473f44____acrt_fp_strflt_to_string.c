// ___acrt_fp_strflt_to_string @ 00473f44 size=188 callers=3

/* Library Function - Single Match
    ___acrt_fp_strflt_to_string
   
   Library: Visual Studio 2015 Release */

int __cdecl ___acrt_fp_strflt_to_string(uint *param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  int *piVar2;
  char *pcVar3;
  uint *puVar4;
  char cVar5;
  char *pcVar6;
  int iVar7;
  
  if ((param_1 != (uint *)0x0) && (param_2 != 0)) {
    *(undefined1 *)param_1 = 0;
    iVar7 = param_3;
    if (param_3 < 1) {
      iVar7 = 0;
    }
    if (param_2 <= iVar7 + 1U) {
      piVar2 = __errno();
      iVar7 = 0x22;
      goto LAB_00473f58;
    }
    if (param_4 != 0) {
      pcVar3 = (char *)((int)param_1 + 1);
      pcVar6 = *(char **)(param_4 + 8);
      *(undefined1 *)param_1 = 0x30;
      for (; 0 < param_3; param_3 = param_3 + -1) {
        cVar5 = *pcVar6;
        if (cVar5 == '\0') {
          cVar5 = '0';
        }
        else {
          pcVar6 = pcVar6 + 1;
        }
        *pcVar3 = cVar5;
        pcVar3 = pcVar3 + 1;
      }
      *pcVar3 = '\0';
      if ((-1 < param_3) && ('4' < *pcVar6)) {
        while (pcVar3 = pcVar3 + -1, *pcVar3 == '9') {
          *pcVar3 = '0';
        }
        *pcVar3 = *pcVar3 + '\x01';
      }
      if ((char)*param_1 == '1') {
        *(int *)(param_4 + 4) = *(int *)(param_4 + 4) + 1;
      }
      else {
        puVar4 = (uint *)((int)param_1 + 1);
        do {
          uVar1 = *puVar4;
          puVar4 = (uint *)((int)puVar4 + 1);
        } while ((char)uVar1 != '\0');
        FUN_0045b0e0(param_1,(uint *)((int)param_1 + 1),
                     (uint)((int)puVar4 + (1 - ((int)param_1 + 2))));
      }
      return 0;
    }
  }
  piVar2 = __errno();
  iVar7 = 0x16;
LAB_00473f58:
  *piVar2 = iVar7;
  FUN_00465fa2();
  return iVar7;
}



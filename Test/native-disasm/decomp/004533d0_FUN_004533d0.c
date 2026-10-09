// FUN_004533d0 @ 004533d0 size=215 callers=3

bool __thiscall FUN_004533d0(void *this,char param_1,char param_2)

{
  char cVar1;
  char cVar2;
  char ****ppppcVar3;
  char local_40;
  undefined1 local_3f [3];
  char local_3c;
  undefined1 local_3b [3];
  char ***local_38 [4];
  int local_28;
  uint local_24;
  char ***local_20 [4];
  int local_10;
  uint local_c;
  
  local_40 = param_1;
  FUN_0044da90((void *)**(undefined4 **)this,local_38,&local_40,local_3f);
  cVar1 = local_40;
  if (local_28 == 1) {
    ppppcVar3 = local_38;
    if (0xf < local_24) {
      ppppcVar3 = (char ****)local_38[0];
    }
    cVar1 = *(char *)ppppcVar3;
  }
  if (0xf < local_24) {
    FUN_00402430(local_38[0],local_24 + 1,1);
  }
  local_3c = param_2;
  local_24 = 0xf;
  local_28 = 0;
  local_38[0] = (char ***)((uint)local_38[0] & 0xffffff00);
  FUN_0044da90((void *)**(undefined4 **)this,local_20,&local_3c,local_3b);
  cVar2 = local_3c;
  if (local_10 == 1) {
    ppppcVar3 = local_20;
    if (0xf < local_c) {
      ppppcVar3 = (char ****)local_20[0];
    }
    cVar2 = *(char *)ppppcVar3;
  }
  if (0xf < local_c) {
    FUN_00402430(local_20[0],local_c + 1,1);
  }
  return cVar1 == cVar2;
}



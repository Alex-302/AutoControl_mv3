// FUN_00402e30 @ 00402e30 size=106 callers=1

undefined1 * FUN_00402e30(undefined1 *param_1,int param_2)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)std::_Syserror_map(param_2);
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  if ((char)*puVar2 == '\0') {
    FUN_0043ace0(param_1,puVar2,0);
    return param_1;
  }
  puVar3 = puVar2;
  do {
    uVar1 = *puVar3;
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((char)uVar1 != '\0');
  FUN_0043ace0(param_1,puVar2,(int)puVar3 - ((int)puVar2 + 1));
  return param_1;
}



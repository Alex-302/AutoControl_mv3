// FUN_0041d5d0 @ 0041d5d0 size=48 callers=1

void __fastcall FUN_0041d5d0(uint param_1,HMENU param_2)

{
  ushort uVar1;
  undefined *puVar2;
  
  if (param_2 == (HMENU)0x0) {
    puVar2 = FUN_00419890(param_1);
    param_2 = *(HMENU *)(puVar2 + 0x1c);
  }
  uVar1 = FUN_0041d340(param_2,param_1);
  FUN_0041d510(param_2,uVar1);
  return;
}



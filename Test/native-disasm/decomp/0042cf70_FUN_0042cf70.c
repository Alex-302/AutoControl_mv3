// FUN_0042cf70 @ 0042cf70 size=752 callers=1

void * __cdecl FUN_0042cf70(void *param_1,void *param_2)

{
  undefined4 *this;
  LPWSTR pWVar1;
  BOOL BVar2;
  DWORD DVar3;
  char *pcVar4;
  undefined8 uVar5;
  uint uVar6;
  void **ppvVar7;
  char local_c4 [16];
  undefined1 local_b4 [16];
  void *local_a4 [4];
  undefined4 local_94;
  uint local_90;
  char local_8c [8];
  undefined8 local_84;
  undefined1 local_7c [8];
  undefined8 local_74;
  void *local_6c [4];
  undefined4 local_5c;
  uint local_58;
  _FILETIME local_54;
  char local_4c [8];
  int local_44;
  int local_40;
  HANDLE local_3c;
  DWORD local_38;
  char local_34 [8];
  undefined8 local_2c;
  undefined1 local_24 [8];
  undefined8 local_1c;
  char local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047cf07;
  local_10 = ExceptionList;
  ppvVar7 = local_6c;
  local_14[0] = '\0';
  local_14[1] = '\0';
  local_14[2] = '\0';
  local_14[3] = '\0';
  ExceptionList = &local_10;
  this = FUN_00440e70(param_2,(uint *)&DAT_0048d05c);
  FUN_00440d90(this,ppvVar7);
  local_8 = 1;
  pWVar1 = FUN_00404640((LPWSTR)local_a4,(LPCSTR)local_6c);
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_00405440(&local_3c,pWVar1,'P',0);
  if (7 < local_90) {
    FUN_00402430(local_a4[0],local_90 + 1,2);
  }
  local_90 = 7;
  local_94 = 0;
  local_a4[0] = (void *)((uint)local_a4[0] & 0xffff0000);
  local_8._0_1_ = 5;
  if (0xf < local_58) {
    FUN_00402430(local_6c[0],local_58 + 1,1);
  }
  local_58 = 0xf;
  local_5c = 0;
  local_6c[0] = (void *)((uint)local_6c[0] & 0xffffff00);
  if (local_38 == 0) {
    BVar2 = GetFileTime(local_3c,(LPFILETIME)0x0,(LPFILETIME)0x0,&local_54);
    if (BVar2 != 0) {
      uVar5 = __alldiv(local_54.dwLowDateTime,local_54.dwHighDateTime,10000,0);
      local_44 = (uint)uVar5 + 0xcf499800;
      local_40 = ((int)((ulonglong)uVar5 >> 0x20) + -0xa97) - (uint)((uint)uVar5 < 0x30b66800);
      DVar3 = GetFileSize(local_3c,(LPDWORD)0x0);
      if (DVar3 != 0xffffffff) {
        local_8c[0] = '\0';
        local_84 = 0;
        FUN_00451110(local_8c,(uint *)&DAT_0048d638);
        local_7c[0] = 0;
        local_74 = 0;
        FUN_00451040(local_7c,DVar3);
        local_8._0_1_ = 6;
        FUN_00434b50(local_c4,local_8c,(char *)local_6c,'\x01','\x02');
        local_8._0_1_ = 8;
        _eh_vector_destructor_iterator_(local_8c,0x10,2,FUN_00434820);
        local_34[0] = '\0';
        local_2c = 0;
        FUN_00451110(local_34,(uint *)"modTime");
        local_24[0] = 0;
        local_1c = 0;
        FUN_0044de90(local_24,&local_44);
        local_8._0_1_ = 9;
        FUN_00434b50(local_b4,local_34,local_14,'\x01','\x02');
        local_8._0_1_ = 0xb;
        _eh_vector_destructor_iterator_(local_34,0x10,2,FUN_00434820);
        local_8 = CONCAT31(local_8._1_3_,0xc);
        FUN_00434b50(param_1,local_c4,(char *)local_a4,'\x01','\x02');
        uVar6 = 2;
        pcVar4 = local_c4;
        goto LAB_0042d230;
      }
    }
    local_38 = GetLastError();
  }
  local_34[0] = '\0';
  local_2c = 0;
  FUN_00451110(local_34,(uint *)"error");
  local_24[0] = 0;
  local_1c = 0;
  FUN_00451040(local_24,local_38);
  local_8._0_1_ = 0xd;
  FUN_00434b50(local_4c,local_34,local_14,'\x01','\x02');
  local_8._0_1_ = 0xf;
  _eh_vector_destructor_iterator_(local_34,0x10,2,FUN_00434820);
  local_8 = CONCAT31(local_8._1_3_,0x10);
  FUN_00434b50(param_1,local_4c,(char *)&local_3c,'\x01','\x02');
  uVar6 = 1;
  pcVar4 = local_4c;
LAB_0042d230:
  local_14[0] = '\x01';
  local_14[1] = '\0';
  local_14[2] = '\0';
  local_14[3] = '\0';
  local_8 = CONCAT31(local_8._1_3_,5);
  _eh_vector_destructor_iterator_(pcVar4,0x10,uVar6,FUN_00434820);
  if (local_3c != (HANDLE)0x0) {
    CloseHandle(local_3c);
  }
  ExceptionList = local_10;
  return param_1;
}



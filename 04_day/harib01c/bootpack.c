void io_hlt(void);
void write_mem8(int addr, int data);

void HariMain(void)
{

  int i;   /* 32�r�b�g�̐����^ */
  char *p; /* BYTE[...]�p�̔Ԓn */

  for( i = 0xa0000; i<=0xaffff; i++) {
    p = i;
    *p = i & 0x0f;
    /* ����� write_mem8(i, i & 0x0f); �̑���ɂȂ� */
  }

  for(;;){
	  io_hlt();
  }
}

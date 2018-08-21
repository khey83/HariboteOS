void io_hlt(void);
void write_mem8(int addr, int data);

void HariMain(void)
{

  int i;   /* 32�r�b�g�̐����^ */
  char *p; /* BYTE[...]�p�̔Ԓn */

  i = 0xa0000;
  for( i = 0; i<=0xaffff; i++) {
    p[i] = i & 0x0c;
  }

  for(;;){
	  io_hlt();
  }
}

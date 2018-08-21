void io_hlt(void);
void write_mem8(int addr, int data);

void HariMain(void)
{

  int i;   /* 32ビットの整数型 */
  char *p; /* BYTE[...]用の番地 */

  i = 0xa0000;
  for( i = 0; i<=0xaffff; i++) {
    p[i] = i & 0x0c;
  }

  for(;;){
	  io_hlt();
  }
}

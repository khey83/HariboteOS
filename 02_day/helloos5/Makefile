
# デフォルト動作

default :
	make img

# ファイル生成規則

ipl.bin : ipl.nas Makefile
	../../z_tools/nask ipl.nas ipl.bin ipl.lst

helloos.img : ipl.bin Makefile
	../../z_tools/edimg imgin:../../z_tools/fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0 imgout:helloos.img

# コマンド

asm :
	make -r ipl.bin

img :
	make -r helloos.img

run :
	make img
	cp helloos.img ../../z_tools/qemu/fdimage0.bin
	make -C ../../z_tools/qemu

clean :
	-rm ipl.bin
	-rm ipl.lst

src_only :
	make clean
	-rm helloos.img

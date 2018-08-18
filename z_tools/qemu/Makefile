QEMU		= qemu-system-i386
QEMU_ARGS	= -L . -m 32 -rtc base=localtime -vga std -boot a -drive format=raw,if=floppy,file=fdimage0.bin

default:
	$(QEMU) $(QEMU_ARGS)

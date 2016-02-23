ASM=sdasz80
AFLAGS=-p -g -o
LIB=c_ti83p

.PHONY: all clean

all: $(LIB).lib

$(LIB).lib: tios_crt0.rel ti83plus.rel fastcopy.rel
	sdar -rc $(LIB).lib tios_crt0.rel ti83plus.rel fastcopy.rel

ti83plus.rel: ti83plus.asm ti83plus.inc
	$(ASM) $(AFLAGS) ti83plus.asm

fastcopy.rel: fastcopy.asm
	$(ASM) $(AFLAGS) fastcopy.asm

tios_crt0.rel: tios_crt0.s
	$(ASM) $(AFLAGS) tios_crt0.s

clean:
	rm -f $(LIB).lib *.rel

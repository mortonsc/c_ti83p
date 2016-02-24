ASM=sdasz80
AFLAGS=-p -g -o
RELS = ti83plus.rel picvars.rel fastcopy.rel
LIB=c_ti83p.lib

.PHONY: all clean

all: $(LIB) tios_crt0.rel

$(LIB): $(RELS)
	sdar -rc $(LIB) $(RELS)

%.rel: %.asm
	$(ASM) $(AFLAGS) $<

tios_crt0.rel: tios_crt0.s
	$(ASM) $(AFLAGS) tios_crt0.s

clean:
	rm -f $(LIB) *.rel

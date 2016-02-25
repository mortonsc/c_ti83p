ASM=sdasz80
AFLAGS=-p -g -o
RELS = ti83plus.rel picvar.rel floatingpoint.rel iongraphics.rel appvar.rel
LIB=c_ti83p.lib

.PHONY: all clean

all: $(LIB) tios_crt0.rel

$(LIB): $(RELS)
	sdar -rc $(LIB) $(RELS)

tios_crt0.rel: tios_crt0.s
	$(ASM) $(AFLAGS) tios_crt0.s

%.rel: %.asm
	$(ASM) $(AFLAGS) $<

clean:
	rm -f $(LIB) *.rel

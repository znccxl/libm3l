FILES = $(shell ls  *.c )
PATHL  = $(shell pwd )
HFILES = $(shell ls  *.h  |   sed '/internal_format_type.h/d'  | sed '/libm3l_header.h/d' | sed '/format_type.h/d' | sed '/format_conversion_spec.h/d' | sed '/libm3l.h/d' | sort -df)

PWD = $(shell pwd)
OBJS=$(FILES:%.c=%.o)

CC = gcc

CFLAGS = -0
LFLAGS = 
#
#Autodependencies with GNU make
#this makefile is a modification of makefile from Scott McPeak web page, November 2001
#
main:
	@cat COPYRIGHT_NOTICE > libm3l.h
	@echo >> libm3l.h
	@echo "#ifndef   __LIBM3L_H__" >> libm3l.h
	@echo "#define   __LIBM3L_H__" >> libm3l.h

	@echo "#include " \"$$PWD/libm3l_header.h\">>libm3l.h
	@echo "#include " \"$$PWD/format_type.h\">>libm3l.h
	@echo "#include " \"$$PWD/internal_format_type.h\">>libm3l.h

	@$(foreach file,$(HFILES),  echo "#include " \"$$PWD/$(file)\">>libm3l.h;)
	@echo "#endif" >> libm3l.h

	make prog

prog: $(OBJS)


	$(CC) -shared -Wl,-soname,libm3l.so.1.0 -o libm3l.so.1.0   $(OBJS)
	ln -sf libm3l.so.1.0 libm3l.so

	ar  rcs libm3l.a    $(OBJS)

-include $(OBJS:.o=.d)

%.o: %.c
	$(CC) -c -g  -fPIC $*.c -o $*.o
	$(CC) -MM -g  -fPIC $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp
clean:
	rm -f *.o *.d

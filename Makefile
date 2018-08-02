CC = gcc -g -Os \
	-DmxCompile=1 \
	-DmxRun=1 \
	-DmxParse=1 \
	-DmxHostFunctionPrimitive=1

MODULES = \
	out/shapes.xsb \
	out/main.xsb

CMODULES = \
	out/shapes.o

XS_DIR = moddable/xs
LIB_DIR = out/xs

XS_DIRECTORIES = \
	$(XS_DIR)/includes \
	$(XS_DIR)/platforms \
	$(XS_DIR)/sources

XS_HEADERS = \
	$(XS_DIR)/platforms/lin_xs.h \
	$(XS_DIR)/platforms/xsPlatform.h \
	$(XS_DIR)/includes/xs.h \
	$(XS_DIR)/includes/xsmc.h \
	$(XS_DIR)/sources/xsCommon.h \
	$(XS_DIR)/sources/xsAll.h \
	$(XS_DIR)/sources/xsScript.h

XS_OBJECTS = \
	$(LIB_DIR)/xsAll.c.o \
	$(LIB_DIR)/xsAPI.c.o \
	$(LIB_DIR)/xsArguments.c.o \
	$(LIB_DIR)/xsArray.c.o \
	$(LIB_DIR)/xsAtomics.c.o \
	$(LIB_DIR)/xsBoolean.c.o \
	$(LIB_DIR)/xsCode.c.o \
	$(LIB_DIR)/xsCommon.c.o \
	$(LIB_DIR)/xsDataView.c.o \
	$(LIB_DIR)/xsDate.c.o \
	$(LIB_DIR)/xsDebug.c.o \
	$(LIB_DIR)/xsError.c.o \
	$(LIB_DIR)/xsFunction.c.o \
	$(LIB_DIR)/xsGenerator.c.o \
	$(LIB_DIR)/xsGlobal.c.o \
	$(LIB_DIR)/xsJSON.c.o \
	$(LIB_DIR)/xsLexical.c.o \
	$(LIB_DIR)/xsMapSet.c.o \
	$(LIB_DIR)/xsMarshall.c.o \
	$(LIB_DIR)/xsMath.c.o \
	$(LIB_DIR)/xsMemory.c.o \
	$(LIB_DIR)/xsModule.c.o \
	$(LIB_DIR)/xsNumber.c.o \
	$(LIB_DIR)/xsObject.c.o \
	$(LIB_DIR)/xsPlatforms.c.o \
	$(LIB_DIR)/xsProfile.c.o \
	$(LIB_DIR)/xsPromise.c.o \
	$(LIB_DIR)/xsProperty.c.o \
	$(LIB_DIR)/xsProxy.c.o \
	$(LIB_DIR)/xsRegExp.c.o \
	$(LIB_DIR)/xsRun.c.o \
	$(LIB_DIR)/xsScope.c.o \
	$(LIB_DIR)/xsScript.c.o \
	$(LIB_DIR)/xsSourceMap.c.o \
	$(LIB_DIR)/xsString.c.o \
	$(LIB_DIR)/xsSymbol.c.o \
	$(LIB_DIR)/xsSyntaxical.c.o \
	$(LIB_DIR)/xsTree.c.o \
	$(LIB_DIR)/xsType.c.o \
	$(LIB_DIR)/xsdtoa.c.o \
	$(LIB_DIR)/xsmc.c.o \
	$(LIB_DIR)/xsre.c.o

XSC=moddable/build/bin/lin/release/xsc
XSL=moddable/build/bin/lin/release/xsl

LIBS := out/main.o out/mc.xs.o $(XS_OBJECTS) $(CMODULES)

.PHONY: run clean distclean all

all: out/myxs

out/myxs: $(LIBS)
	$(CC) $(LIBS) -lm -o $@

out/xs/%.o: moddable/xs/sources/%
	$(CC) -std=gnu99 -Imoddable/xs/includes -Imoddable/xs/platforms -c $< -o $@

out/mc.xs.o: out/mc.xs.c out/mc.xs.h
	$(CC) -std=gnu99 -Imoddable/xs/includes -Imoddable/xs/platforms -Imoddable/xs/sources -c $< -o $@

out/main.o: src/main.c out/mc.xs.h
	$(CC) -Wall -Werror -std=c99 -Iout -Imoddable/xs/includes -Imoddable/xs/sources -Imoddable/xs/platforms -c $< -o $@

out/%.o: src/%.c src/%.h src/types.h
	$(CC) -Wall -Werror -std=c99 -Imoddable/xs/includes -c $< -o $@

out/%.xsb: src/%.js $(XSC)
	$(XSC) -c -d -e $< -o out

out/mc.xs.h: out/mc.xs.c
out/mc.xs.c: $(MODULES) $(XSL)
	$(XSL) $(MODULES) -o out -b out

run: out/myxs
	$<

clean:
	rm -f out/*.xs*

distclean:
	rm -rf out
	mkdir -p out/xs

$(XSL): $(XSC)
$(XSC):
	MODDABLE=$(PWD) $(MAKE) -C moddable/build/lin/makefiles

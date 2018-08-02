
###############################################################################
# Building moddable SDK for host, this gives us `xsc` and `xsl` tools.
###############################################################################

PLATFORM = lin
MODDABLE := $(shell pwd)/moddable
MODDABLE_MAKEFILE = $(MODDABLE)/build/makefiles/$(PLATFORM)
XSL = $(MODDABLE)/build/bin/$(PLATFORM)/release/xsl
XSC = $(MODDABLE)/build/bin/$(PLATFORM)/release/xsc

###############################################################################
# Building our app
###############################################################################

CC = gcc -g -Os # Change this to preferred compiler
OUT := $(shell pwd)/out
COMMONFLAGS = \
	-I$(MODDABLE)/xs/includes \
	-I$(MODDABLE)/xs/sources \
	-I$(MODDABLE)/xs/platforms \
	-DmxCompile=1 \
	-DmxRun=1 \
	-DmxParse=1 \
	-DmxHostFunctionPrimitive=1

MODULES = \
	$(OUT)/shapes.xsb \
	$(OUT)/main.xsb
CMODULES = \
	$(OUT)/shapes.o \
	$(OUT)/main.o
HEADERS = \
	src/shapes.h \
	src/types.h
CFLAGS = $(COMMONFLAGS) \
	-I$(OUT) \
	-Wall -Werror -std=c99 
XSMODULES = \
	$(OUT)/xs/xsAll.c.o \
	$(OUT)/xs/xsAPI.c.o \
	$(OUT)/xs/xsArguments.c.o \
	$(OUT)/xs/xsArray.c.o \
	$(OUT)/xs/xsAtomics.c.o \
	$(OUT)/xs/xsBoolean.c.o \
	$(OUT)/xs/xsCode.c.o \
	$(OUT)/xs/xsCommon.c.o \
	$(OUT)/xs/xsDataView.c.o \
	$(OUT)/xs/xsDate.c.o \
	$(OUT)/xs/xsDebug.c.o \
	$(OUT)/xs/xsError.c.o \
	$(OUT)/xs/xsFunction.c.o \
	$(OUT)/xs/xsGenerator.c.o \
	$(OUT)/xs/xsGlobal.c.o \
	$(OUT)/xs/xsJSON.c.o \
	$(OUT)/xs/xsLexical.c.o \
	$(OUT)/xs/xsMapSet.c.o \
	$(OUT)/xs/xsMarshall.c.o \
	$(OUT)/xs/xsMath.c.o \
	$(OUT)/xs/xsMemory.c.o \
	$(OUT)/xs/xsModule.c.o \
	$(OUT)/xs/xsNumber.c.o \
	$(OUT)/xs/xsObject.c.o \
	$(OUT)/xs/xsPlatforms.c.o \
	$(OUT)/xs/xsProfile.c.o \
	$(OUT)/xs/xsPromise.c.o \
	$(OUT)/xs/xsProperty.c.o \
	$(OUT)/xs/xsProxy.c.o \
	$(OUT)/xs/xsRegExp.c.o \
	$(OUT)/xs/xsRun.c.o \
	$(OUT)/xs/xsScope.c.o \
	$(OUT)/xs/xsScript.c.o \
	$(OUT)/xs/xsSourceMap.c.o \
	$(OUT)/xs/xsString.c.o \
	$(OUT)/xs/xsSymbol.c.o \
	$(OUT)/xs/xsSyntaxical.c.o \
	$(OUT)/xs/xsTree.c.o \
	$(OUT)/xs/xsType.c.o \
	$(OUT)/xs/xsdtoa.c.o \
	$(OUT)/xs/xsmc.c.o \
	$(OUT)/xs/xsre.c.o \
	$(OUT)/mc.xs.o
XSFLAGS = $(COMMONFLAGS) \
	-std=gnu99

LIBS = $(CMODULES) $(XSMODULES)


.PHONY: all run debug clean distclean

all: $(OUT)/myxs

run: $(OUT)/myxs
	clear && echo "\e[34;1mRunning myxs:\e[0m\n" && $< && echo "\n\e[32;1mDone.\e[0m"

debug: $(OUT)/myxs
	gdb $<

clean:
	rm -rf $(OUT)
	mkdir -p $(OUT)/xs

distclean: clean
	git submodule foreach git clean -xdf

$(XSL): $(XSC)
$(XSC):
	git submodule update --init $(MODDABLE)
	MODDABLE=$(MODDABLE) $(MAKE) -C $(MODDABLE_MAKEFILE)
	echo $(XSC)

$(OUT)/myxs: $(LIBS)
	$(CC) $(LIBS) -lm -o $@

$(OUT)/%.xsb: src/%.js src/%.c $(XSC)
	$(XSC) -c -d -e $< -o $(OUT)

$(OUT)/mc.xs.o: $(OUT)/mc.xs.c $(OUT)/mc.xs.h
	$(CC) $(XSFLAGS) -c $< -o $@

$(OUT)/mc.xs.h: $(OUT)/mc.xs.c
$(OUT)/mc.xs.c: $(XSL) $(MODULES)
	$(XSL) $(MODULES) -o $(OUT) -b $(OUT)

$(OUT)/xs/%.o: $(MODDABLE)/xs/sources/%
	$(CC) $(XSFLAGS) -c $< -o $@

$(OUT)/%.o: src/%.c $(HEADERS) $(OUT)/mc.xs.h
	$(CC) $(CFLAGS) -c $< -o $@

SYSTEM= $(shell uname)

all:
	$(MAKE) -C Engine -f Makefile.$(SYSTEM)
	$(MAKE) -C Demo -f Makefile.$(SYSTEM)

clean:
	$(MAKE) -C Engine -f Makefile.$(SYSTEM) clean
	$(MAKE) -C Demo -f Makefile.$(SYSTEM) clean

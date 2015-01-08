all:
	$(MAKE) -C Engine
	$(MAKE) -C Demo

clean:
	$(MAKE) -C Engine clean
	$(MAKE) -C Demo clean

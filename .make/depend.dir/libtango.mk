DEPEND_TARGETS += libtango.recursive
ECHO_TARGETS += libtango.echo
libtango.recursive:
	@echo SUPER_MAKE_DIR=/volumes/llama/home/alpine/applications/tango/               >> /volumes/llama/home/alpine/libraries/libtango/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/volumes/llama/home/alpine/applications/tango/.make >> /volumes/llama/home/alpine/libraries/libtango/.make/super
	cd /volumes/llama/home/alpine/libraries/libtango/ && make recursive && make install
	-rm /volumes/llama/home/alpine/libraries/libtango/.make/super
libtango.echo:
	@echo SUPER_MAKE_DIR=/volumes/llama/home/alpine/applications/tango/               >> /volumes/llama/home/alpine/libraries/libtango/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/volumes/llama/home/alpine/applications/tango/.make >> /volumes/llama/home/alpine/libraries/libtango/.make/super
	cd /volumes/llama/home/alpine/libraries/libtango/ && make echo
	-rm /volumes/llama/home/alpine/libraries/libtango/.make/super

DEPEND_TARGETS += libtango.recursive
ECHO_TARGETS += libtango.echo
libtango.recursive:
	@echo SUPER_MAKE_DIR=/home/lidali/alpine/applications/tango/               >> /home/lidali/alpine/libraries/libtango/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/home/lidali/alpine/applications/tango/.make >> /home/lidali/alpine/libraries/libtango/.make/super
	cd /home/lidali/alpine/libraries/libtango/ && make recursive && make install
	-rm /home/lidali/alpine/libraries/libtango/.make/super
libtango.echo:
	@echo SUPER_MAKE_DIR=/home/lidali/alpine/applications/tango/               >> /home/lidali/alpine/libraries/libtango/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/home/lidali/alpine/applications/tango/.make >> /home/lidali/alpine/libraries/libtango/.make/super
	cd /home/lidali/alpine/libraries/libtango/ && make echo
	-rm /home/lidali/alpine/libraries/libtango/.make/super

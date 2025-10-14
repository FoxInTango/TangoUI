DEPEND_TARGETS += libtango.recursive
ECHO_TARGETS += libtango.echo
libtango.recursive:
	@echo SUPER_MAKE_DIR=/Users/lidali/alpine/applications/tango/               >> /Users/lidali/alpine/libraries/libtango/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/Users/lidali/alpine/applications/tango/.make >> /Users/lidali/alpine/libraries/libtango/.make/super
	cd /Users/lidali/alpine/libraries/libtango/ && /Applications/Xcode.app/Contents/Developer/usr/bin/make recursive && /Applications/Xcode.app/Contents/Developer/usr/bin/make install
	-rm /Users/lidali/alpine/libraries/libtango/.make/super
libtango.echo:
	@echo SUPER_MAKE_DIR=/Users/lidali/alpine/applications/tango/               >> /Users/lidali/alpine/libraries/libtango/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/Users/lidali/alpine/applications/tango/.make >> /Users/lidali/alpine/libraries/libtango/.make/super
	cd /Users/lidali/alpine/libraries/libtango/ && /Applications/Xcode.app/Contents/Developer/usr/bin/make echo
	-rm /Users/lidali/alpine/libraries/libtango/.make/super

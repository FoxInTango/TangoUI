DEPEND_TARGETS += libcpp.recursive
ECHO_TARGETS += libcpp.echo
libcpp.recursive:
	@echo SUPER_MAKE_DIR=/Users/lidali/alpine/applications/tango/               >> /Users/lidali/alpine/libraries/libcpp/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/Users/lidali/alpine/applications/tango/.make >> /Users/lidali/alpine/libraries/libcpp/.make/super
	cd /Users/lidali/alpine/libraries/libcpp/ && /Applications/Xcode.app/Contents/Developer/usr/bin/make recursive && /Applications/Xcode.app/Contents/Developer/usr/bin/make install
	-rm /Users/lidali/alpine/libraries/libcpp/.make/super
libcpp.echo:
	@echo SUPER_MAKE_DIR=/Users/lidali/alpine/applications/tango/               >> /Users/lidali/alpine/libraries/libcpp/.make/super
	@echo SUPER_MAKE_CONFIG_DIR=/Users/lidali/alpine/applications/tango/.make >> /Users/lidali/alpine/libraries/libcpp/.make/super
	cd /Users/lidali/alpine/libraries/libcpp/ && /Applications/Xcode.app/Contents/Developer/usr/bin/make echo
	-rm /Users/lidali/alpine/libraries/libcpp/.make/super

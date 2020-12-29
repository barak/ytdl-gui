DESTDIR=/

build:
	cd src; \
	qmake; \
	make -j`nproc`

clean:
	cd src; \
	make clean; \
	rm ytdl_gui

install:
	#create directories
	mkdir -p $$DESTDIR/usr/bin
	mkdir -p $$DESTDIR/usr/share/applications
	for i in 16 32 64 128 256 512; do \
		mkdir -p $$DESTDIR/usr/share/icons/hicolor/$${i}x$${i}/apps; \
	done
	cp src/ytdl_gui $$DESTDIR/usr/bin
	cp resources/ytdl-gui.desktop $$DESTDIR/usr/share/applications
	for i in 16 32 64 128 256 512; do \
		cp icons/$${i}x$${i}.png $$DESTDIR/usr/share/icons/hicolor/$${i}x$${i}/apps/ytdl-gui.png; \
	done

uninstall:
	rm $$DESTDIR/usr/bin/ytdl_gui
	rm $$DESTDIR/usr/share/applications/ytdl-gui.desktop
	for i in 16 32 64 128 256 512; do \
		rm $$DESTDIR/usr/share/icons/hicolor/$${i}x$${i}/apps/ytdl-gui.png; \
	done

Debian
====================
This directory contains files used to package galileld/galilel-qt
for Debian-based Linux systems. If you compile galileld/galilel-qt yourself, there are some useful files here.

## galilel: URI support ##


galilel-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install galilel-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your galilelqt binary to `/usr/bin`
and the `../../share/pixmaps/galilel128.png` to `/usr/share/pixmaps`

galilel-qt.protocol (KDE)


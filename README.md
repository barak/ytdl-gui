# ytdl-gui
A simple-to-use, cross-platform graphical interface for yt-dlp. This is a fork of [the original youtubedl-gui by JaGoLi](https://github.com/JaGoLi/ytdl-gui) that seems to be abandoned.<br/><br/>
[![Get it on Flathub!](https://codeberg.org/impromptux/install-badges/raw/branch/main/badges/flathub/get-it-on-flathub.png)](https://flathub.org/en/apps/page.codeberg.impromptux.ytdl-gui)
[![Get it for Debian!](https://codeberg.org/impromptux/install-badges/raw/branch/main/badges/debian/get-it-for-debian-ceratopsian.png)](https://codeberg.org/impromptux/ytdl-gui/wiki/Install-on-Debian) [![Build it for ArchLinux](https://codeberg.org/impromptux/install-badges/raw/branch/main/badges/arch/build-it-for-arch-linux-dark.png)](https://codeberg.org/impromptux/ytdl-gui/wiki/Building-for-Arch-Linux) [![Get it for Alpine Linux](https://codeberg.org/impromptux/install-badges/raw/branch/main/badges/alpine/get-it-for-alpine-linux.png)](https://codeberg.org/impromptux/-/packages/alpine/youtubedl-gui/4.4.1-r0) <br/>
![youtubedl-gui-screenshot.png](https://codeberg.org/impromptux/ytdl-gui/raw/branch/master/resources/youtubedl-gui-screenshot-3.0.png) <br/>


## Installation Instructions
There are packages of the original youtubedl-gui for arch-based linux distros (using the aur) and Debian based distro.
If you prefer you can also build from sources (see below) or use flatpak to use this fork instead of the original youtubedl-gui.
### Arch linux and Manjaro
You can build it for Arch Linux and Arch Linux-based distribution by folowing the instructions [here](https://codeberg.org/impromptux/ytdl-gui/wiki/Building-for-Arch-Linux).

### Debian and Ubuntu
For a system running Debian, Ubuntu, Linux Mint, LMDE or any Debian-based linux distribution install instruction are [here](https://codeberg.org/impromptux/ytdl-gui/wiki/Install-on-Debian).

### Flatpak
It is also possible to install the application via Flatpak .<br/>
You can find the app on Flathub [here](https://flathub.org/en/apps/page.codeberg.impromptux.ytdl-gui).

### Alpine Linux
Currently, there is no package for Alpine Linux, you will need to build it from source. There are some Alpine Linux specific build instruction [here](https://codeberg.org/impromptux/ytdl-gui/wiki/Building-for-Alpine).

## HiDPI Support
This application does support HiDPI displays even though its size is fixed.
### Gnome and GTK based desktops
In order to the application to scale properly, the variable ```QT_AUTO_SCREEN_SCALE_FACTOR=1``` needs to be set.<br/>
You can set it in either ```/etc/environment```, or in your local ```.profile```, ```.bash_profile``` or ```.zshenv```
### KDE and QT based desktops
The application will scale automatically with the scaling factor chosen by the desktop environment.

## Build From Source
### Dependencies
To build this application from source, you need the basic development tools for the Qt6 framework, and a recent version of the ```yt-dlp``` binary for the application to compile and run on your system.<br/><br/>
Here is a list of build and runtime dependencies for arch linux:<br/>
```base-devel qt6-base ffmpeg yt-dlp```<br/>

For debian-based systems (including ubuntu) here is a list of dependencies:<br/>
```build-essential cmake qt6-base-dev ffmpeg yt-dlp```<br/><br/>
Since the version of ```yt-dlp``` is often not current on debian and ubuntu distros, I recommend you install it through ```pip3``` (or from backports for Debian).

### Installing
To install after having installed the correct dependencies:<br/><br/>
```git clone https://codeberg.org/impromptux/ytdl-gui.git && cd ytdl-gui```<br/>
```mkdir build && cd build```<br/>
```cmake .. && make```<br/>
```sudo make install```<br/>

## Contributing
If you want to contribute you can [fork the repo](https://codeberg.org/impromptux/ytdl-gui/fork) and open a pull request with a description of your changes.
If you have a suggestion or a bug to report you can [open an issue](https://codeberg.org/impromptux/ytdl-gui/issues)

## Contributors
- Jason Goulet-Lipman: Original youtubedl-gui
- [jrtcdbrg](https://codeberg.org/jrtcdbrg) : Estonian translations
- [Outbreak2096](https://codeberg.org/Outbreak2096) : Chinese translation
- [Contributors of youtubedl-gui](https://codeberg.org/impromptux/ytdl-gui/activity/contributors)

## TODO
- [x] Migrate to Qt6
- [x] Migrate from Youtube-dl to Yt-dlp
- [x] Add other file resolutions (360p)<br/>
- [x]Add other languages than english<br/>
[![Translations progress](https://translate.codeberg.org/widget/ytdl-gui/ytdl-gui/multi-auto.svg)](https://translate.codeberg.org/engage/ytdl-gui/)<br/>
- [x] Make ytdl-gui compatible with both Youtube-dl and Yt-dlp
- [x] Show a notification when a download finish and the windows is in the background
- [x] Write metadata for audio files
- [ ] Remove special characters from files names

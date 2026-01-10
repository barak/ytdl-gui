# ytdl-gui
A simple-to-use, cross-platform graphical interface for yt-dlp. This is a fork of [the original youtubedl-gui by JaGoLi](https://github.com/JaGoLi/ytdl-gui) that seems to be abandoned.<br/><br/>
![youtubedl-gui-screenshot.png](https://codeberg.org/impromptux/ytdl-gui/raw/branch/master/resources/youtubedl-gui-screenshot-3.0.png)<br/>


## Installation Instructions
There is are packages of the original youtubedl-gui for arch-based linux distros (using the aur) and Debian based distro.
### Arch linux and Manjaro
On any arch system with an aur helper such as ```yay```:<br/>
```yay -S youtubedl-gui```<br/>
Everything required to compile and install the application from source should be done automatically.

To try out the beta branch of this project, you can download the package ```youtubedl-gui-git``` as such:<br/>
```yay -S youtubedl-gui-git```
### Debian and Ubuntu
For a system running at least Debian 12 Bookworm or Ubuntu jammy, the application is in the distribution's standard repositories.<br/>
Simply run ```sudo apt install youtubedl-gui``` to install the GUI interface.<br/><br/>
Then, make sure ```ffmpeg``` and ```python3-pip``` are on your system too.<br/>
Finally, execute ```sudo pip3 install yt-dlp``` to get the latest version of ```yt-dlp``` on your system.
### Flatpak
It is also possible to install the application via Flatpak if there is no package for your distrubition.<br/>
However, be aware that I am not responsible for its maintenance and that the install size will be an order of magnitude bigger than simply using a package or building from source. Please also note that the Flatpak seems to be abandoned too.<br/><br/>
To install the application, run ```flatpak install flathub io.github.JaGoLi.ytdl_gui```

## HiDPI Support
This application does support HiDPI displays even though its size is fixed.
### Gnome and GTK based desktops
In order to the application to scale properly, the variable ```QT_AUTO_SCREEN_SCALE_FACTOR=1``` needs to be set.<br/>
You can set it in either ```/etc/environment```, or in your local ```.profile```, ```.bash_profile``` or ```.zshenv```
### KDE and QT based desktops
The application will scale automatically with the scaling factor chosen by the desktop environment.

## Build From Source
### Dependencies
To build this application from source, you need the basic development tools for the Qt5 framework, and a recent version of the ```yt-dlp``` binary for the application to compile and run on your system.<br/><br/>
Here is a list of build and runtime dependencies for arch linux:<br/>
```base-devel qt6-base ffmpeg yt-dlp```<br/>

For debian-based systems (including ubuntu) here is a list of dependencies:<br/>
```build-essential cmake qt-base6-dev ffmpeg yt-dlp```<br/><br/>
Since the version of ```yt-dlp``` is often not current on debian and ubuntu distros, I recommend you install it through ```pip3``` (or from backports for Debian).

### Installing
To install after having installed the correct dependencies:<br/><br/>
```git clone https://codeberg.org/impromptux/ytdl-gui.git && cd ytdl-gui```<br/>
```mkdir build && cd build```<br/>
```cmake .. && make```<br/>
```sudo make install```<br/>

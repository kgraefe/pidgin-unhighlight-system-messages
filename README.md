# Pidgin Unhighlight System Messages

[![License](https://img.shields.io/badge/License-GPLv2-blue.svg?style=flat)](COPYING)

This plugin removes the highlight flag from system messages. This works around
a bug which was introduced with Pidgin 2.10.7 and leads to a highlighted IRC
channel each time you join when you set the channel topic.


## Installation on Windows
For the binary version, extract all the contents of
`pidgin-unhighlight-system-messages` in the ZIP file either to the installation
directory of Pidgin (typically `C:\Program Files\Pidgin`) or to your .purple
user directory (typically `%APPDATA%\Roaming\.purple`).

See below for how to compile the source code version into a binary ZIP file.


## Installation on Linux
To install the plugin on Linux you need to extract a release tarball and
compile it from source:

    sudo apt-get install pidgin-dev
    ./configure
    make
    sudo make install

**Note:** By default the plugin will be installed to `/usr/local`.  If you
installed Pidgin through your package manager, it is most likely installed into
`/usr` (i.e. `which pidgin` returns `/usr/bin/pidgin`). Use
`./configure --prefix=/usr` in this case.

**Note:** When you use the repository directly or one of those auto-generated
"Source code" archives, you need to run `./autogen.sh` before running
`./configure`.


## Building on Windows
In order to build the plugin for Windows an already-compiled source tree of
Pidgin is required. Please see the [Pidgin for Windows Build
Instructions](https://developer.pidgin.im/wiki/BuildingWinPidgin) for details.

After that you need to create a file named `local.mak` that points to the
Pidgin source tree, e.g.:

    PIDGIN_TREE_TOP=$(PLUGIN_TOP)/../../pidgin-2.10.11

Now you can build the plugin:

    make -f Makefile.mingw


## Contribution
We love patches. :heart: Please fork the project, do your changes and make a
pull request.

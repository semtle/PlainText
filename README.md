PlainText
=========

PlainText is a text-based MUD game engine.

Features
--------

 * Support for both telnet (including ANSI colors, MCCP, MSDP and MSSP
   extensions) and HTML5 (WebSockets) 
 * Command-line OLC
 * Graphical HTML5 room builder, with perspective view for designing 3D areas 
 * Scripting support using JavaScript
   * New commands can be implemented in JavaScript
   * Combat is customizable through JavaScript
   * Scriptable NPCs
 * Logging of sessions (including IPs) and player commands
 * Statistics tracking
 * Basic MUD commands
   * Conversations (say, talk, tell, gtalk)
   * Buying and handling items (buy, give, drop, get)
   * Container items (put ... into, get ... from)
   * Player groups (follow, lose, disband, gtalk)
   * Basic combat (kill, attack, wield, remove)
 * Designed for minimal latency
   * Multi-threaded design
   * All game objects are in memory
   * Changes are synced to disk in separate thread

Technology
----------

 * The engine is written in C++, using the Qt toolkit.
 * A JavaScript engine is embedded for providing scripting to game objects.
 * The game is accessible over telnet (with support for ANSI colors and the MCCP,
   MSDP and MSSP extension protocols), but also hosts a web interface over HTTP
   which connects to the game using WebSockets.

Running your own server
-----------------------

### Supported platforms ###

 * Linux (tested on Gentoo Linux and openSUSE 12.2)
 * Mac OS X 10.7 and up (recently only tested on OS X 10.8)

### Dependencies ###

 * Clang 3.1 or higher, or GCC 4.7 or higher
 * Qt framework 4.7 or higher
 * Zlib development package

### Compiling ###

Run the following commands from the src/ directory:

 * qmake PlainText.pro
 * make

### Running ###

 * Set the PT_DATA_DIR environment variable to point to the data/ directory.
 * If you want to enable logging, set the PT_LOG_DIR variable to the directory
   where you want your logs to be stored.
 * Run your compiled PlainText executable.

Playing the game
----------------

**Note**: If you want to play the game using your webbrowser, you should have a
modern standards compliant browser. These are the browsers that *should* work:
 * Chrome
 * Firefox 4 or higher
 * Internet Explorer 10
 * Safari

### Connect to your own server ###

If you have just compiled your own server, you can connect to it through telnet
or using your webbrowser. The ports to connect to are displayed on the console
when you start your server.

The first character you register on your own server will automatically become an
admin.

### Connect to the demo server ###

If you do not have your own server, feel free to connect to the demo server:

 * Point your webbrowser to http://mud.yunocloud.com:8080/ *or*
 * Connect with telnet to mud.yunocloud.com on port 4801.

Creating your own game
----------------------

_Before you begin, if concepts like cloning and forking sound unfamiliar to
you, you may want to read a little introduction here:
http://learn.github.com/p/intro.html_

If you want to create your own MUD, you're more than welcome to use the code
from this project as your starting point. Please keep in mind though if you want
a complete, feature-rich codebase that you can use right away, you'd better not
use PlainText right now, as you would find it lacking in many areas.

On the other hand, if the lean, clean codebase attracts you and you do want to
use PlainText as a foundation for your game, I would kindly like to ask you to
follow the following steps in order to make the process as smooth for all as
possible...

1. If you have no GitHub account yet, create an account first. Once you have
   your own account you can fork this project for yourself (there's a Fork
   button somewhere on the top right of this page). Keeping all forks in public
   repositories will help us all to merge code between our codebases.

2. You can now clone your project to your own local machine and starting
   working on it.

2. You may want to clean up the data/ directory in your own checkout as you're
   probably going to be creating your own game world anyway.

3. If you're going to modify the deep internals of the engine, please discuss
   with me, so we can try to find a solution that will avoid diverging the
   codebases too much.

5. There are other forks from PlainText from which you may be able to draw
   inspiration or merge code:
   * FoggyText: https://github.com/arendjr/FoggyText
   * Conception: https://github.com/Lundex/Conception

### Frequently Asked Questions ###

**Q. I don't want to use character classes. How can I remove class support?**

A. Just remove all classes from the data/ directory, except one. You can
hardcode all players to use that one class in src/engine/session.cpp. See the
FoggyText project for an example: https://github.com/arendjr/FoggyText

**Q. What does the Realm class do?**

A. The Realm class handles various stuff that needs to be managed globally.
It keeps track of the in-game date/time, it keeps track of all other objects
in the realm, makes it easy to query for players, etc.. The Realm class is
also used if you need to create a new object from JavaScript:

```javascript
var newItem = Realm.createObject('item');
```

**Q. How do triggers work?**

A. Using the following command, you will get an in-game explanation about
triggers:

```
help triggers
```

(Note: The explanation is rather long and you may have to scroll up a bit to
see it all...)

**Q. I see you're using a lot of non-standard JavaScript methods. What
methods are available?**

A. In order to simplify common patterns, there's a bunch of convenience
methods defined. Many of these are provided as extensions to the standard
JavaScript objects to make their use as seemless as possible.

You can find all these methods collected here:
https://github.com/arendjr/PlainText/blob/master/src/engine/util.js

In addition, all game objects that are exposed to JavaScript have various
methods and properties that you can call from JavaScript. There are
special commands to inspect those.

This command will give you an overview of all methods of an object:

```
list-methods <object>
```

And this command gives an overview of all the properties:

```
list-properties <object>
```

**Q. I see there are properties called respawnTime and respawnTimeVariation.
How would those be used in determine when a character respawns?**

The time it takes for a character to respawn (in milliseconds) is
_respawnTime + (random number between 0.0 and 1.0) * respawnTimeVariation_.

Be careful, if respawnTime is 0 the character will be deleted when it dies
and is dead forever rather than being respawned.

**Q. What IDE do you recommended?**

A. Personally, I use Qt Creator: http://qt.digia.com/Product/Developer-Tools/

License
-------

This software is licensed under GPLv3.

For details, see LICENSE.GPL.txt.

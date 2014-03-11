OpenGL project focusing on 4.x specification.
=============================================

Targets
-------
* Too many so I'll just list the current one:
* It has come to my attention that a menu system of a sort could be a challenging task to implement, and it's also needed for future projects(Sound studio of a sort).

Features
--------
* OpenGL 3.1 compliant... except for ati.
* Can draw a your favorite .obj file (without colors, and dont include normals).
* Works on Win/Linux!
* Ability to hack it in your favourite editor {project files for Visual Studio 2013 and sublime text2 with sublimeclang}

TODO
----
* (IMPORTANT) Add some screenshots to this page as it can be taunting task to compile this. Considering hosting binaries of some versions only for windows.
* Since good base is needed for easy expanding that will be the focus for now.
* Need to implement a way to disable/enable features depending on gpu features.
* Some kind of smart way to get ati, nvidia and intel to play together nicely
with shaders. Currently opengl dependency to 3.1 means that I will hit ati bug
with reading vertex/color data in to vertex shaders.
Extension available in GLSL 3.1 and up, GL_ARB_explicit_attrib_location.

Controls
--------
* Movement with 'wasd' or arrow keys, and look with mouse.
* '1' to grab mouse.
* '2' to reload shaders.
* '3' to toggle fps limit.
* '4' to toggle particles. (currently disabled in favor of lesser opengl version for intel graphics)
* '5' to toggle fullscreen. (careful on linux(nvidia+cinerama) sets the mode for the first screen and wont revert)
* '6' to toggle movement speed.
* '7' toggle postprocessing (currently only enables FXAA)
* '8' toggle showing 'bin/shaders/glsl.fragment' file on screen for live(linux only) editing.
* '9' not implemented

Building tips
-------------

<dl>
	<dt>Linux</dt>
	<dd>Packages for gl glu libpng.
	    Works best with the latest clang++ v3.2 or g++-4.7 (or greater versions of either).
		Graphics drivers are also needed.</dd>

	<dt>Windows</dt>
	<dd>Visual Studio 2013, look at lib/README for dependencies</dd>

	<dt>OSX</dt>
	<dd>Not supported.
		Why? Mainly because I will never willingly buy an apple computer.
		I guess OSX might be easier than I thought BUT YOU need to supply me with a free mac first.</dd>
</dl>

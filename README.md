OpenGL project focusing on 4.x specification.
=============================================

Targets
-------
* Getting used to OpenGL development
* Experiment with multithreading in various tasks and study the effects of applying it.
* Physics! Very far off target.
* Machine Learning! Same as above. You got to have dreams, right?
* Making a game using this as a base.

Features
--------
* Tried with opengl3.1 (intel HD3000) and worked.
* Can draw a your favorite .obj file (without colors, and dont include normals).
* Works on Win/Linux!
* Ability to hack it in your favourite editor {project files for Visual Studio 2012 and sublime text2 with sublimeclang}

TODO
----
* Since good base is needed for easy expanding that will be the focus for now.
* Need to implement a way to disable/enable features depending on gpu features.
* Some kind of smart way to get ati, nvidia and intel to play together nicely
with shaders. Currently opengl dependency to 3.1 means that I will hit ati bug
with reading vertex/color data in to vertex shaders.
Extension available in GLSL 3.3 and up, GL_ARB_explicit_attrib_location.

Controls
--------
* Movement with 'wasd' or arrow keys, and look with mouse.
* '1' to grab mouse.
* '2' to reload shaders.
* '3' to toggle fps limit.
* '4' to toggle particles.
* '5' to toggle fullscreen. (careful on linux(nvidia+cinerama) sets the mode for the first screen and wont revert)
* '6' to toggle movement speed.

Building tips
-------------

<dl>
	<dt>Linux</dt>
	<dd>Packages for gl glu libpng.
	    Works best with the latest clang++ v3.2 or g++-4.7 (or greater versions of either).
		Graphics drivers are also needed.</dd>

	<dt>Windows</dt>
	<dd>Visual Studio 2012,
		Visual C++ Compiler November 2012 CTP (dem c++11 features)</dd>

	<dt>OSX</dt>
	<dd>Not supported.
		Why? Mainly because I will never willingly buy an apple computer.
		I guess OSX might be easier than I thought BUT YOU need to supply me with a free mac first.</dd>
</dl>

# clfe2

It's quite a funny scenario but I'm already quite used to upping version numbers without any real previous releases (lol).  
Anyways the original clfe was made as my first (yes very first) C++ project and is obviously great due the amount work I put in but also not the most optimal.
After taking an extended vacation, I had lost interest and have now started on the cooler and better version.

Key modules:
* clmath - The math library
* clutil - The utilities library
* clwind - The windowing module
* clgraph - The graphics module
* clobj - The object system

All of these modules can be used independent of each other (though a lot of functions might be missing if they are in fact used individually, especially certain clutil headers)
Within these modules, submodules may be present (like clphys for clobj)
(Most modules are currently theoretical, they do not exist outside of the mind yet lol)

Besides these modules, there is only one file they universally need: features.h, which is an intermediary header for basic system data (like which operating system, etc)
(Note: I might change this later)

(Note 2: refurbish, refine, and remake the readme after significant progress has been made)

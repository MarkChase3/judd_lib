# JUDD_LIB

## What this is exactly?
This is a library of single header independet modules, that can create big applications when used together or with others APIs.

## Why that name?
Donald Judd was a freaking cool guy, one of the first minimalistic thinkers. As this API is destined to be the simpler as possible, I decided to homage his work.

## Why C?
Because C is so freaking cool, man.
But really, C is, in my opinion, the cooler language we have.
I already made some projects in C++, js, python and even lua, some were good, some were not, but I always loved and will love C. I am very inspired on sokol, raylib and pico_headers to do this.
Another reasons are for learning, recreation and personal use.

## What are the modules?

The following are planned to the final version:

Module Name | Explanation | Current Version | Docs level
-------|--------|------|-----
judd_core | Opengl context creation and window mangement | 1.0 | High
judd_draw | Drawing operations on a opengl context | 1.0 | Few
judd_gl_load | OpengGL functions loading on few lines | 0.5 | Few
judd_img_load | Image files loading | 0.5 | Medium (single function lol)
judd_audio | To load and play audio | 0.0 | none
judd_time | To manage time | 0.0 | None
judd_ecs | Entity component system | 0.75 | Few
judd_json | Json Loading | 0.0 | None
judd_physics | To handle physics | 0.0 | None
judd_net | Networking API | 0.0 | none

0.5 versions are usbale, but can't do every thing I expected. 1.0 versions are good and you can do a good app with them easily, but probably will have more updates. 0.75 is a mid-term. 0.0 is when the module still don't exist.

Abundant documentation is when I made an walktrough on the code, a getting started, a manual and some examples. High is when it's missing 1. Medium is when the module is very simple or miss 2 or the doc types. Few miss 3 or more. None is when the module still don't exist.

I have sttrugled a few on a png decoder, because I wanted to do it in a single function, don't ask me why. Now I will throw this away and I am going to work more hardly on judd_audio, judd_json and some documentation. Expect to have most work done until end of january.

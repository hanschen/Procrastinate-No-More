Procrastinate No More
=====================

Procrastinate No More is a simple widget for the KDE Plasma Workspaces to help you avoid 
procrastination. It is inspired by a Python applet called Tomate, which you can read more
about here: https://gitorious.org/tomate/pages/Home


Description
-----------

Have you ever thought "_now_ I will start doing what I am supposed to do", only to find 
yourself doing exactly everything except that? The reason we procrastinate is often not
because of the task itself, the problem is to get started with it. Once we have passed
that stage, however, it is usually easy to just go with the flow and get work done.

Procrastinate No More can help you get past that first stage. When you click on the
widget, you make a contract with yourself to commit fully to a task for 10 minutes without 
any distractions. After 10 minutes have passed you are free to decide whether you want to 
continue working or do something else.

Why 10 minutes? It is short enough to always be doable, no matter how boring or daunting
the task might seem, while it should let you stay concentrated long enough to pick up the
flow.

Installation
------------

If possible, it is recommended that you install this widget through your package manager.
The typical procedure to compile it from source is as follows:

    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=`kde4-config --prefix` ..
    make
    make install

The last command usually requires root permissions so you probably need to use `su`/`sudo`
or similar commands.

How to use
----------

The widget can be added to the desktop, a panel or to the system tray.

1. When you want to commit yourself to a task, click on the widget. The widget becomes red.
2. Work.
3. After 10 minutes the widget turns green. Now you can either continue to work, or do
something else.
4. When you stop working, regardless if the 10 minutes have passed or not, click on the 
widget again. It is now back to its idle state (blue icon) and the tooltip tells you for
how long you worked.
5. Rinse and repeat.

Configuration options
---------------------

Procrastinate No More follows the path of its inspiration (Tomate) and tries to be as
simple as possible. For that reason it only has the most essential features and no
options you can waste time tweaking.

For those who absolutely have to change the minimum working time or the icons that 
represent the different states, see the short description below.

Change minimum working time
---------------------------

The minimum working time (10 minutes by default) is defined in `src/tomat.h` on line 46:

    enum { MIN_WORK_TIME = 10*60 }; // minimum working time in seconds

Change `10*60` to whatever time you want (given in seconds). It is necessary to recompile
the widget after making the change.

Change state icons
------------------

The icons can be defined by the Plasma Workspace theme (`widgets/work_state.svgz`).
The default icons are located in the file

    <kde prefix>/share/apps/desktoptheme/default/widgets/work_state.svgz

where `<kde prefix>` can be found with the command `kde4-config --prefix` (usually `/usr`).
The SVG file contains three icons with the following id for the different states:

- `idle`
- `working`
- `ok`

Trivia
------

- Internally Procrastinate No More goes by the name "Tomat", Swedish for tomato. The name
comes from the applet it is inspired by, Tomate, which in turn is named that way because
the concept is similar to the popular Pomodoro technique. ("Pomodoro" is tomato in
Italian.)
- The author started coding this widget just before one of his final exams.


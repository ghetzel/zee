zee [DEFUNCT]
=============

Zee was my first attempt at creating the user interface for a computer I intend to put in my car.  Originally started in 2009, I decided to write this in C++ (using Qt 4) after a great deal of wrestling with a lot of the other options I was toying around with.  This predated a lot of the more fervent hype surrounding HTML5 and Android, and it was also during a time when resources were thin but time was abundant.  For this project, I envisioned a few key factors that drove the development much of the nearly 30,000 lines of code in this project:

* Pretty: The UI had to be beautiful, responsive, and usable.  The aim was to be able to support any design I could throw at it by being extremely generic.

* Data Rich: Any piece of data made available to the system had to be universally accessible by any part of the system.  Eventually, a complex expression language would allow for data manipulation (not necessarily my own language; I explored embedding various interpreters).

* Adaptive: While the original intent was to operate on a small PC with a relatively small (800x480) screen, the UI component library was to be generic and useful enough that it could be used to express a wide array of graphics-rich applications, with a particular nod to information readouts and heads-up displays.

Scope Creep, Focus, and Planning
================================

The project started off with me teaching myself C++ from the ground up.  I was hitting Google very hard, following examples and tinkering with Qt.  I learned a lot of idioms about how Qt does things, while also expressing my own structure and coding style onto the project.  Code piled up, and basic functionality began to take shape.  It felt great.

However, as time drew on and with no end in sight, crazy idea after crazy idea began to materialize as half- or quarter-implemented stubs of code.  I would get things to a point where I could see them, poke at them, call them "good enough," then move on.  The idea was that I could finish them later, polish them in a second round.  Later, unfortunately, never came, and my interest in the project began to falter.

I went into the project fairly novice to the ways in which a project should be managed, hoping to draw on my experience with pure programming as a mechanism of support.  I lacked the discipline to write down what I wanted, to put any definition at all on the project.  I felt that if I created boundaries, that I would eventually unintentionally box myself in.  For the big project that I always wanted to embark on, limits were not an option.  The codebase grew larger still, and I kept working (albeit with more sparse commits).  Eventually, I stopped working on it entirely, accepting that the work was useful in an unconventional way, in that it taught me a great deal about my own strengths and weaknesses.

Lessons
=======

This project was (and its inciting idea still is) very important to me.  However, I became a perfectionist about the implementation.  I insisted that nobody else could have already done *exactly* what I wanted it to do, despite not having any concrete point-to-able list of target features.  I had no idea what a particular library or platform was missing, but I would dismiss them because they didn't "feel right".  In the meantime, I spent countless hours hacking away at the code, stubbing out ever-more features in a vain attempt to get things working and interacting as I desired.

I learned that I am but one person, and that my strength is in integration of disparate components.  I was single-handedly attempting to write what was turning into a full-on window manager, as well as a fully generic language for assembling any interface my whims could imagine.  It was a futile attempt, because I refused to let anybody else express "my vision".

I learned that there is power in building on what others have done.  That is, after all, the very absolute foundation of scientific discovery; the idea that a notion or the work of our predecessors can be a guiding light and useful component in new work, even if the entire lineage of the thought isn't completely original.  The idea that creating something useful has much less to do with creating something brand new than I thought it did was a big eye opener.

There's plenty more that I took from this experience, but this was the big point.  I've done enough rambling for one README, so I leave you to poke around at this project.  If there's anything I've done in here that you are interested in, please have at.  This was a learning experience for me, and I hope it can be one for you, too.




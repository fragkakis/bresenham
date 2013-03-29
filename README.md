bresenham
=========

This is an implementation of Bresenham's line algorithm.

The implementation is based on the corresponding Wikipedia entry [1], specifically on the "Simplification" variation.

The following is an example of a line from point (3,3) to point (17,7) on a 30x10 2d array.

<pre>
+++++++++++++++++++++++++++++++++++++++++
+ | | | | | | | | | | | | | | | | | | | +
+ | | | | | | | | | | | | | | | | | | | +
+ | | | | | | | | | | | | | | | | | | | +
+ | | |X|X| | | | | | | | | | | | | | | +
+ | | | | |X|X|X|X| | | | | | | | | | | +
+ | | | | | | | | |X|X|X| | | | | | | | +
+ | | | | | | | | | | | |X|X|X|X| | | | +
+ | | | | | | | | | | | | | | | |X|X| | +
+ | | | | | | | | | | | | | | | | | | | +
+ | | | | | | | | | | | | | | | | | | | +
+++++++++++++++++++++++++++++++++++++++++
</pre>

[1] http://en.wikipedia.org/wiki/Bresenham's_line_algorithm
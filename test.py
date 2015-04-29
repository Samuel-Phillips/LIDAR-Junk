#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function
from __future__ import division
from __future__ import unicode_literals
from __future__ import absolute_import
from builtins import range
from builtins import int
from builtins import map
from builtins import zip
from builtins import input
from builtins import chr
from io import open

import sys
import curses
import liblas as laser

def scale(c, minc, maxc, newmin, newmax):
    oldrang = maxc - minc
    newrang = newmax - newmin
    scal = c - minc
    scal *= newrang
    scal /= oldrang
    return scal + newmin

def yscale(yc, h):
    return scale(yc, h.min[1], h.max[1], 0, maxy)
def xscale(xc, h):
    return scale(xc, h.min[0], h.max[0], 0, maxx)

def run(scr):
        maxy, maxx = stdscr.getmaxyx()
        trap = [[0 for x in range(maxx)] for y in range(maxy)]

        f = laser.file.File(sys.argv[1], mode='r')
        h = f.header

        #for p in f:
        #    trap[yscale(p.y, h)][xscale(p.x, h)] += 1
        y = int(yscale(h.min[0], h))
        x = int(xscale(h.min[1], h))
        print(y, x)
        trap[y][x] += 1

        curtop = 0
        for row in trap:
            for col in row:
                curtop = max(curtop, col)

        stdscr.erase()
        uni = '_▁▂▃▄▅▆▇█'

        for y, row in enumerate(trap):
            for x, col in enumerate(row):
                if col > 0:
                    scal = scale(col, 0, curtop, 0, len(uni))
                    b = uni[int(scal)]
                else:
                    b = ' '
                stdscr.addstr(y, x, b)

        getch()
if __name__=='__main__':
    stdscr = curses.initscr()
    try:
        pass
    finally:
        curses.endwin()

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

def printliststat(lis):
    _min = lis[0]
    _max = lis[-1]
    median = lis[len(lis) // 2]
    q1 = lis[len(lis) // 4]
    q3 = lis[3 * len(lis) // 4]
    median = int(scale(median, _min, _max, 0, 80))
    q1 = int(scale(q1, _min, _max, 0, 80))
    q3 = int(scale(q3, _min, _max, 0, 80))
    s = '-'*(q1-1) + \
        '|' + \
        '='*(median-q1-1) + \
        '#' + \
        '='*(q3-median-1) + \
        '|' + \
        '-'*(80-q3)
    print("Min: {}\tMax: {}".format(_min, _max))
    print(s)

def getlaserfilelists(f):
    xs = []
    ys = []
    zs = []

    for p in f:
        xs.append(p.x)
        ys.append(p.y)
        zs.append(p.z)

    xs.sort()
    ys.sort()
    zs.sort()
    return (xs, ys, zs)

if __name__=='__main__':
    f = laser.file.File(sys.argv[1], mode='r')

    for lis in getlaserfilelists(f):
        printliststat(lis)

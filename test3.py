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
import locale
import liblas as laser

class XYZ(object):
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

class Viewport(object):
    def __init__(self):
        self.xo = 270000
        self.yo = 4327500
        self.ys = 2
        self.xs = 1
        self.xl = 0
        self.yl = 0
        self.zr = 250
        self.zo = 200
    def __getattr__(self, n):
        return {
            'xo': self.offset_x,
            'yo': self.offset_y,
            'ys': self.scale_y,
            'xs': self.scale_x,
            'xl': self.slope_x,
            'yl': self.slope_y,
            'zo': self.z_bottom,
            'zr': self.z_range
        }[n]
    def __setattr__(self, n, v):
        setattr(self, {
            'xo': 'offset_x',
            'yo': 'offset_y',
            'ys': 'scale_y',
            'xs': 'scale_x',
            'xl': 'slope_x',
            'yl': 'slope_y',
            'zo': 'z_bottom',
            'zr': 'z_range'
        }[n], v)


dchars = '░▒▓█'

def dostuff(lfn, code):
    lf = laser.file.File(lfn, mode='r')
#   lf = [
#           XYZ(270001, 4327500, 6),
#           XYZ(270001, 4327501, 6),
#           XYZ(270000, 4327500, 6),
#           XYZ(270000, 4327501, 6)
#       ]
    try:
        scr = curses.initscr()
        curses.cbreak()
        curses.noecho()
        curses.curs_set(0)
        curses.start_color()
        curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_BLACK)
        curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
        curses.init_pair(4, curses.COLOR_YELLOW, curses.COLOR_BLACK)
        curses.init_pair(5, curses.COLOR_GREEN, curses.COLOR_BLACK)
        curses.init_pair(6, curses.COLOR_GREEN, curses.COLOR_BLACK)
        curses.init_pair(7, curses.COLOR_CYAN, curses.COLOR_BLACK)
        curses.init_pair(8, curses.COLOR_RED, curses.COLOR_BLACK)
        curses.init_pair(9, curses.COLOR_RED, curses.COLOR_BLACK)
        curses.init_pair(10, curses.COLOR_BLUE, curses.COLOR_BLACK)
        for i in range(11, 32):
            curses.init_pair(
                    i, curses.COLOR_MAGENTA, curses.COLOR_BLACK)

        scr.keypad(True)
        
        scr.addstr(0,0, "Reading file...".encode(code))
        f = [pt for pt in lf]
        k = ''
        vp = Viewport()
        while k != ord('q'):
            process(f, scr, vp)
            k = scr.getch()
            if k == ord('h'): vp.xo -= vp.xs
            elif k == ord('l'): vp.xo += vp.xs
            elif k == ord('j'): vp.yo -= vp.ys
            elif k == ord('k'): vp.yo += vp.ys
            elif k == ord('o'):
                vp.ys *= 2
                vp.xs *= 2
            elif k == ord('O'):
                vp.ys *= 256
                vp.xs *= 256
            elif k == ord('i'):
                vp.ys /= 2
                vp.xs /= 2
            elif k == ord('s'):
                vp.yl += .1
            elif k == ord('S'):
                vp.yl += 1
            elif k == ord('a'):
                vp.yl -= .1
            elif k == ord('d'):
                vp.xl += .1
            elif k == ord('g'):
                vp.xl -= .1
            elif k == ord('t'):
                vp.zo += 10
            elif k == ord('y'):
                vp.zo -= 10
    finally:
        curses.endwin()

def inscl(v, s, e):
    return s <= v < s + e

def project(point, vp):
    px = point.x + vp.xl * point.z
    py = point.y + vp.yl * point.z
    px -= vp.xo
    py -= vp.yo
    px /= vp.xs
    py /= vp.ys
    return int(px), int(py), dchars[int((len(dchars) * (point.z - vp.zo)) // (vp.zr - vp.zo))]

def getmax(b, greater):
    m = b[0]
    for item in b[1:]:
        if greater(item, m):
            m = item
    return m

def process(f, scr, vp):
    scr.erase()
    scr.addstr(0, 0, 'Rendering...'.encode(code))
    scr.refresh()
    scr.erase()
    y, x = scr.getmaxyx()
    buckets = [[[] for xx in range(x)] for yy in range(y)]
    for pt in f:
        px, py, cc = project(pt, vp)
        if inscl(px, 0, x) and inscl(py, 0, y):
            buckets[py][px].append((pt, cc))
    for yy, br in enumerate(buckets):
        for xx, bucket in enumerate(br):
            if len(bucket) == 0:
                continue
            bigone = getmax(bucket, lambda a, b: a[0].z > b[0].z)
            try:
                scr.addstr(
                        y - yy, xx, bigone[1].encode(code),
                        curses.color_pair(
                            bigone[0].classification & 0xf + 1))
            except curses.error:
                pass
    scr.addstr(y - 1, 0, ("Scale: %10d XPos: %10d YPos: %10d XL: %10d YL: %10d" % (vp.xs, vp.xo, vp.yo, vp.xl, vp.yl)).encode(code))
    scr.refresh()

if __name__ == '__main__':
    locale.setlocale(locale.LC_ALL, '')
    code = locale.getpreferredencoding()
    dostuff(sys.argv[1], code)

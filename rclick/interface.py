import sqlite3
import json
from math import sin, cos

class Rect:
    def __init__(self, _id, x, y, sint, cost, wid, hei, sun, mny):
        self.id = _id
        self.x = x
        self.y = y
        self.sint = sint
        self.cost = cost
        self.width = wid
        self.height = hei
        self.sunlight = sun
        self.moneyval = mny

    def __getitem__(self, i):
        if isinstance(i, int):
            return [id, x, y, sint, cost, width, height, sunlight, moneyval][i]
        elif isinstance(i, str):
            return self.todict()[i]
        else:
            raise TypeError("Only str or int keys are accepted")

    def todict(self):
        return {
            "id"       = self.id,
            "x"        = self.x,
            "y"        = self.y,
            "sint"     = self.sint,
            "cost"     = self.cost,
            "width"    = self.width,
            "height"   = self.height,
            "sunlight" = self.sunlight,
            "moneyval" = self.moneyval
        }

class DB:
    def __init__(self, database):
        self.db = database
    def cursor(self):
        return close
    def addrects(self, rects):
        c = self.db.cursor()
        try:
            c.executemany("""
            INSERT INTO rooftops
            (x, y, sin_theta, cos_theta, width, height, sunlight, moneyval)
     VALUES (?, ?, ?,         ?,         ?,     ?,      ?,        ?)
      """, ((x, y, sin(rot),  cos(rot),  w,     h,      light,    money)
            for x, y, rot, w, h, light, money in rects))
            c.commit()
        finally:
            c.close()
    def addrect(self, x, y, rot, w, h, light, money):
        self.addrects((x, y, rot, w, h, light, money))

    def getrects(self, x, y):
        c = self.db.cursor()
        try:
            xk = "((? - x) * cos_theta + (? - y) * sin_theta)"
            yk = "(-(? - x) * sin_theta + (? - y) * cos_theta)"
            c.execute("""
            SELECT id, x, y, sin_theta, cos_theta, width, height,
                   sunlight, moneyval
            FROM rooftops
            WHERE 0 <= {xk} AND {xk} <= width AND 0 <= {yk} AND {yk} <= height
            """.format(xk=xk, yk=yk),
            (x, y, x, y, x, y, x, y))
            return self._cvtall(c.fetchall())
        finally:
            c.close()

    def get_near_rects(self, left, right, top, bot):
        c = self.db.cursor()
        try:
            c.execute("""
            SELECT id, x, y, sin_theta, cos_theta, width, height,
                   sunlight, moneyval
            FROM rooftops
            WHERE (x + width >= ? OR x - width <= ?)
              AND (y + height >= ? OR y - height <= ?)
            """, (left, right, top, bot))
            return self._cvtall(c.fetchall())
        finally:
            c.close()

    def _cvt(self, row):
        _id, x, y, st, ct, w, h, s, m = row
        return Rect(_id, x, y, st, ct, w, h, s, m)

    def _cvtall(self, rows):
        return [self._cvt(row) for row in rows]


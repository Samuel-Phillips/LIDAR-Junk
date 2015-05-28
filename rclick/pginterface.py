import contextlib
import collections

Rect = collections.namedtuple('Rect',   ['wktshape', 'sunlight'])
RRect = collections.namedtuple('RRect', ['wktshape', 'sunlight', 'id'])

class Rooftops:
    def __init__(self, dbconn):
        self.db = dbconn
    
    def cursor(self):
        return contextlib.closing(self.db.cursor())

    def get_rects(self, left, right, top, bot):
        left, right = sorted([left, right])
        bot, top = sorted([top, bot])

        with self.cursor() as c:
            c.execute("""
            SELECT id, ST_AsText(shape), sunlight
            FROM rooftops
            WHERE ST_Overlaps(shape, %s::geometry)
            """, 
            """POLYGON(
              {bot} {left},
              {top} {left},
              {top} {right},
              {bot} {right},
              {bot} {left})""".format(**locals()))
            return (RRect(*r) for r in c.fetchall())

    def add_rects(self, rects):
        with self.cursor() as c:
            c.executemany("""
            INSERT INTO rooftops (shape, sunlight)
            VALUES (%s, %s)
            """, rects)
            c.commit()

    def add_rect(self, rect):
        self.add_rects((rect))

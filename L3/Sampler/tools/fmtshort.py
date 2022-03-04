#!/usr/bin/env python3

import sys
import json

def title(pt):
    return f"{pt['file']}:{pt['line']} ({pt['func']})"

j = json.load(sys.stdin)
for pt in j:
    for e in pt['edges']:
        p2 = j[e['dest']]
        t1 = title(pt)
        t2 = title(p2)
        u = e['usec']
        c = e['count']
        a = round(u /c, 3)
        print(f"{t1} -> {t2}: {u} / {c} = {a}")

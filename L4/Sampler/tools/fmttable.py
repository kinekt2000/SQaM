#!/usr/bin/env python3

import sys
import json

j = json.load(sys.stdin)
print("|исх|прием|общее время|кол-во проходов|среднее время|")
print("|-:|-:|-:|-:|-:|")
for pt in j:
    for e in pt['edges']:
        p2 = j[e['dest']]
        u = e['usec']
        c = e['count']
        a = u /c
        print(f"|{pt['line']}|{p2['line']}|{u:.3f}|{c}|{a:.3f}|")

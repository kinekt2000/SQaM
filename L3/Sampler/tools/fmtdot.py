#!/usr/bin/env python3

import sys
import json
import html
from os.path import basename

def ptitle(pt):
    return f"{basename(pt['file'])}:{pt['line']} ({pt['func']})"

def etitle(t, c):
    return f"{t} / {c}"

def esc(s):
    es = s.replace('\\', '\\\\').replace('"', '\\"')
    return f'"{es}"'

def htmllines(lines):
    es = "<br/>".join(html.escape(l) for l in lines if l)
    return f"<{es}>"

def wrgraph(nodelabels, edges,
            file=sys.stdout):
    fprint = lambda *a, **kwa: print(*a, file=file, **kwa)
    fprint('digraph {')
    for i, txt in enumerate(nodelabels):
        fprint(f'  {i} [label={esc(txt)}]')
    for i, j, e in edges:
        attrs = {
            k: (round(v, 3) if isinstance(v, float) else v)
            for k, v in e.get('attrs', {}).items()
        }
        l = htmllines(
            f'{k}={v!r}' for k, v in {
                'T': round(e['usec'], 3),
                'n': e['count'],
                **attrs
            }.items()
        )
        fprint(f'  {i} -> {j} [<label>={l}]')
    fprint('}')

j = json.load(sys.stdin)
ns = []
es = []
for i, pt in enumerate(j):
    ns.append(ptitle(pt))
    for e in pt['edges']:
        es.append((i, e['dest'], e))
wrgraph(ns, es)

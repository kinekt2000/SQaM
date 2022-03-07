#!/usr/bin/env python3

import sys
import math
import json
from dataclasses import dataclass, field, replace
from typing import List, Dict, Tuple, Sequence
from itertools import takewhile, chain


@dataclass(frozen=True)
class Checkpoint:
    file: str
    line: int
    func: str

@dataclass
class RawEdge:
    src: Checkpoint
    dst: Checkpoint
    times: List[int]
    refs_start: List[int]
    refs_end: List[int]

@dataclass
class MultiEdge:
    src: Checkpoint
    dst: Checkpoint
    times: List[float]


def lines(f):
    for l in f:
        l = l.rstrip('\n')
        if not l:
            yield None
        else:
            yield json.loads(l)

def takerun(ls):
    return takewhile(lambda x: x is not None, ls)

def load_join_runs(f) -> List[RawEdge]:
    ls = lines(f)

    edges = [
        RawEdge(src=Checkpoint(**r['prev']),
                dst=Checkpoint(**r['curr']),
                times=[r['dt']],
                refs_start=[r['ref_start']],
                refs_end=[r['ref_end']])
        for r in takerun(ls)
    ]

    badruns = 0
    i = 0
    ign = False
    for r in ls:
        if r is None:
            i = 0
            ign = False
            continue
        idx, i = i, i+1
        if ign:
            continue

        e = edges[idx]
        csrc = Checkpoint(**r['prev'])
        cdst = Checkpoint(**r['curr'])
        if csrc != e.src or cdst != e.dst:
            badruns += 1
            print(f"Mismatch in run {idx}", file=sys.stderr)
            ign = True
            continue
        e.times.append(r['dt'])
        e.refs_start.append(r['ref_start'])
        e.refs_end.append(r['ref_end'])

    if badruns > 0:
        raise ValueError(f'({badruns} bad runs)')

    return edges


def avg(it):
    c = 0
    acc = 0
    for i in it:
        acc += i
        c += 1
    if c == 0:
        return 0
    return acc / c

def var(it, av):
    c = 0
    acc = 0
    for i in it:
        acc += (i - av)**2
        c += 1
    if c == 0:
        return 0
    return acc / c

def median(it):
    sl = sorted(it)
    return sl[len(sl)//2]

def median_filter(it, winsize=3):
    win = [None]*winsize
    idx = 0
    for i, x in enumerate(it):
        win[idx] = x
        idx = 0 if idx == winsize - 1 else (idx + 1)
        if i >= winsize:
            yield median(win)
    if idx > 0 and i < winsize:
        yield median(win[:idx])

def edge_times(e: RawEdge) -> Sequence[float]:
    for t, rs, re in zip(e.times, e.refs_start, e.refs_end):
        dt = t - (rs + re) * 0.5
        yield dt

def handle_edge(e: RawEdge,
                winsize=0,
                separate=False) -> MultiEdge:
    if winsize <= 0:
        times = edge_times(e)
    elif not separate:
        times = edge_times(e)
        times = median_filter(times, winsize=winsize)
    else:
        times = edge_times(replace(
            e,
            times=median_filter(e.times, winsize=winsize),
            refs_start=median_filter(e.refs_start, winsize=winsize),
            refs_end=median_filter(e.refs_end, winsize=winsize),
        ))

    ltimes = list(times)

    return MultiEdge(
        src=e.src,
        dst=e.dst,
        times=ltimes,
    )


Graph = Dict[Checkpoint, Dict[Checkpoint, List[List[float]]]]

def make_graph(edges: Sequence[MultiEdge]) -> Graph:
    graph = {}
    for e in edges:
        ed = graph.setdefault(e.src, {})
        graph.setdefault(e.dst, {})
        table = ed.setdefault(e.dst, [])
        table.append(e.times)
    return graph

def mkedge(table: List[List[float]], threesigma=False):
    alltimes = list(chain(*table))
    a = avg(alltimes)
    v = var(alltimes, a)

    if threesigma:
        at = avg(ltimes)
        v = var(ltimes, at)
        r = 3 * math.sqrt(v)
        alltimes = [
            x if (x - av)**2 < r**2 else 0
            for x in alltimes
        ]

    t_usec = sum(alltimes)
    t_count = len(alltimes)
    n_runs = len(table[0])

    return {
        'total-usec': t_usec,
        'total-count': t_count,
        'usec': t_usec / n_runs,
        'count': t_count // n_runs,
        'attrs': {
            'avg': a,
            'var': v,
            'std': math.sqrt(v),
        },
    }

def graph_to_dict(graph: Graph):
    ks = list(graph.keys())
    return [
        {
            'file': k.file,
            'line': k.line,
            'func': k.func,
            'edges': [
                {
                    'dest': ks.index(d),
                    **mkedge(table),
                }
                for d, table in graph[k].items()
            ]
        }
        for k in ks
    ]


def make_arg_parser():
    import argparse
    parser = argparse.ArgumentParser()

    parser.add_argument(
        'input_file', metavar='INPUT', type=argparse.FileType('r'),
        action='store', default="sampler.out", nargs='?',
        help='input file ("sampler.out" if omitted, stdin if "-")'
    )

    parser.add_argument(
        'output_file', metavar='OUTPUT', type=argparse.FileType('w'),
        action='store', default=sys.stdout, nargs='?',
        help='output file (stdout if omitted or "-")'
    )

    return parser

def main():
    ap = make_arg_parser()
    args = ap.parse_args(sys.argv[1:])

    raws = load_join_runs(args.input_file)
    multis = (handle_edge(e) for e in raws)
    graph = make_graph(multis)

    from os import isatty
    indent = 2 if isatty(args.output_file.fileno()) else None
    json.dump(graph_to_dict(graph), args.output_file, indent=indent)
    if indent is not None:
        print(file=args.output_file)


if __name__ == '__main__':
    main()

#!/usr/bin/python3

import os
from wrapper import QuailFS

def parse_ls(lines):
    dirs, files = [], []
    for line in lines:
        ftype, fsize, fname = line.split()
        if ftype == 'd':
            dirs.append(fname)
        else:
            files.append(fname)
    return (dirs, files)

def walk_rec(FS, root):
    lines = FS.ls(root)
    dirs, files = parse_ls(lines)
    yield (root, dirs, files)
    for d in dirs:
        yield from walk_rec(FS, os.path.join(root, d))

def walk(FS):
    return walk_rec(FS, '.')
    

def main():
    quailFS = QuailFS('../build/iQuailClient', '.')
    if not quailFS.connect('localhost', '4242'):
        print('%s' % quailFS.get_error())
        return
    for root, dirs, files in walk(quailFS):
        for name in files:
            print('file: %s' % os.path.join(root, name))
        for name in dirs:
            print('dir: %s' % os.path.join(root, name))
    quailFS.disconnect()

if __name__ == '__main__':
    main()

#!/usr/bin/python3

from wrapper import QuailFS

def main():
    quailFS = QuailFS('../build/iQuailClient', '.')
    if not quailFS.connect('localhost', '4242'):
        print('%s' % quailFS.get_error())
        return
    quailFS.get_file('hello')
    ls = quailFS.ls('dur')
    if not ls:
        print('%s' % quailFS.get_error())
    ls = quailFS.ls('.')
    if not ls:
        print('%s' % quailFS.get_error())
    else:
        for i in ls:
            print('%s' % i)
    v = quailFS.get_version()
    print('Version: %s' % v)
    vs = quailFS.list_versions()
    print('Versions:')
    for version in vs:
        print('%s' % version)
    quailFS.set_version('11.0')
    v = quailFS.get_version()
    print('Version: %s' % v)
    quailFS.disconnect()

if __name__ == '__main__':
    main()

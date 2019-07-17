#!/usr/bin/python3

from wrapper import QuailFS

def main():
    quailFS = QuailFS()
    if not quailFS.connect('localhost', '4242'):
        print('Cannot connect to server')
        return
    #quailFS.ls()
    #quailFS.get_file('hello')
    if not quailFS.get_file('hell'):
        print('%s' % quailFS.get_error())
    #quailFS.ls('dir')
    if not quailFS.ls('dur'):
        print('%s' % quailFS.get_error())
    #quailFS.list_versions()
    #quailFS.get_version()
    #quailFS.set_version('11.0')
    if not quailFS.set_version('666.0'):
        print('%s' % quailFS.get_error())
    #quailFS.get_version()
    #quailFS.ls()
    quailFS.disconnect()

if __name__ == '__main__':
    main()

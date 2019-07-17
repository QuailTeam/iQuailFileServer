#!/usr/bin/python3

from wrapper import QuailFS

def main():
    quailFS = QuailFS()
    quailFS.connect('localhost', '4242')
    quailFS.ls()
    quailFS.get_file('hello')
    quailFS.ls('dir')
    quailFS.list_versions()
    quailFS.get_version()
    quailFS.set_version('11.0')
    quailFS.get_version()
    quailFS.ls()
    quailFS.disconnect()

if __name__ == '__main__':
    main()

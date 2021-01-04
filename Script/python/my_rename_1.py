#!/usr/bin/python
import os
import sys

rootpath = os.getcwd()
dirpath = sys.argv[1]
filename = sys.argv[2]
newfilename = sys.argv[3]

print(rootpath)
print(dirpath)
print(filename)
print(newfilename)

cmd_find = 'find {} -name "{}*"'.format(dirpath, filename)
print(cmd_find)

paths = os.popen('find {} -name "{}*"'.format(dirpath, filename)).readlines()

print(paths)

for path in paths:
    cmd_sed = 'echo %s | sed "s@\(.*\)%s@\\1%s@i"' % (path.strip('\n'),
                                                      filename, newfilename)
    print(cmd_sed)
    newpath = os.popen('echo %s | sed "s@\(.*\)%s@\\1%s@i"' % (path.strip('\n'),
                                                               filename, newfilename)).readline()
    print(newpath)
    os.popen('sudo mv %s %s' % (path.strip('\n'), newpath))

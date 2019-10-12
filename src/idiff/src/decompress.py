import sys
import binascii
if len(sys.argv) != 4:
    print("this file takes three input files, the source, the target and the patch file")
    exit(-1)

source = open(sys.argv[1])
target = open(sys.argv[2], 'w')
diff = open(sys.argv[3])

for line in diff.readlines():
    if line != "\n":
        try:
            (header, arg) = line.split(':')
            if header == 'INSERT':
                (off, _, length) = arg.split()
                source.seek(int(off))
                target.write(source.read(int(length) + 1))
            elif header == 'COPY':
                target.write(arg[1])
        except Exception as e:
            print(e)
target.close()
source.close()
diff.close()

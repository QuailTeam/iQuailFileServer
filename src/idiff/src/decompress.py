import sys
import binascii

def decompress(sourcename, targetname, diffname):

    target = open(targetname, 'w+b')
    source = open(sourcename, 'rb')
    buffer = b''
    for byte in bytes_from_file(diffname):
        if byte == ord(b'\n') and len(buffer):
            try:
                (header, arg) = buffer.split(b':', maxsplit=1)
                if header == b'INSERT':
                    (off, _, length) = arg.split()
                    source.seek(int(off))
                    target.write(source.read(int(length)))
                elif header == b'COPY' and len(arg) > 1:
                    target.write(bytes([arg[1]]))
                elif header == b'COPY':
                    target.write(bytes([byte]))
            except Exception as e:
                print(e)
            buffer = b''
        else:
            buffer += bytes([byte])
    target.close()
    source.close()

def bytes_from_file(filename, chunksize=8192):
    with open(filename, "rb") as f:
        while True:
            chunk = f.read(chunksize)
            if chunk:
                for b in chunk:
                    yield b
            else:
                break

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("this file takes three input files, the source, the target and the patch file")
        exit(-1)

    decompress(sys.argv[1], sys.argv[2], sys.argv[3])

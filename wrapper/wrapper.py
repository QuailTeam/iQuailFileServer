import pexpect

class QuailFS:
    def __init__(self):
        self.pipe = None
        self.error = ''

    def _send_cmd(self, cmd):
        self.pipe.sendline(cmd)
        self.pipe.expect('> ')
        return list(self.pipe.before.splitlines())[1:]

    def _parse_error(self, lines, start='ERROR:'):
        if lines[0].startswith(start):
            self.error = lines[0]
            return True
        return True

    def connect(self, ip, port):
        args = '../build/iQuailClient' + ' ' + ip + ' ' + port
        print('connecting')
        self.pipe = pexpect.spawnu(args)
        ret = self.pipe.expect(['> ', 'Couldn\'t connect to host'])
        if ret == 1:
            return False
        return True

    def ls(self, path='.'):
        lines = self._send_cmd('LS ' + path)
        if self._parse_error(lines, 'LS failed'):
            return False
        for line in lines:
            print('%s' %line)
        return True

    def get_version(self):
        lines = self._send_cmd('VERSION GET')
        for line in lines:
            print('%s' %line)

    def list_versions(self):
        lines = self._send_cmd('VERSION LIST')
        for line in lines:
            print('%s' %line)

    def set_version(self, version):
        lines = self._send_cmd('VERSION SET ' + version)
        if self._parse_error(lines, 'Invalid command'):
            return False
        for line in lines:
            print('%s' %line)
        return True

    def get_file(self, path):
        lines = self._send_cmd('GET_FILE ' + path)
        if self._parse_error(lines, 'File not received'):
            return False
        for line in lines:
            print('%s' %line)
        return True

    def get_error(self):
        return self.error

    def disconnect(self):
        print('disconnecting')
        self.pipe.sendline('EXIT')
        self.pipe.expect(pexpect.EOF)

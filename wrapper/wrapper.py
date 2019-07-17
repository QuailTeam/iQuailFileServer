import pexpect

class QuailFS:
    def __init__(self):
        self.pipe = None

    def _send_cmd(self, cmd):
        self.pipe.sendline(cmd)
        self.pipe.expect('> ')
        return list(self.pipe.before.splitlines())[1:]

    def connect(self, ip, port):
        args = '../build/iQuailClient' + ' ' + ip + ' ' + port
        print('connecting')
        self.pipe = pexpect.spawnu(args)
        self.pipe.expect('> ')

    def ls(self, path='.'):
        lines = self._send_cmd('LS ' + path)
        for line in lines:
            print('%s' %line)

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
        for line in lines:
            print('%s' %line)

    def get_file(self, path):
        lines = self._send_cmd('GET_FILE ' + path)
        for line in lines:
            print('%s' %line)

    def disconnect(self):
        print('disconnecting')
        self.pipe.sendline('EXIT')
        self.pipe.expect(pexpect.EOF)

import tempfile
import sys
import time
import os
import subprocess

folder_test = tempfile.mkdtemp()
command_touch = "touch " + folder_test +"/test-xdiff"
subprocess.call(command_touch.split())

command ="../xdiff " + sys.argv[1] +  " " + sys.argv[2] + " " + folder_test +"/test-xdiff"
start_time = time.time()
subprocess.call(command.split())
print("--- %s seconds ---" % (time.time() - start_time))

command_tar="tar -czvf " + folder_test +"/test-xdiff.tar " + folder_test +"/test-xdiff"
subprocess.call(command_tar.split())
command_tar="tar -czvf " + folder_test +"/target.tar " + sys.argv[2]
subprocess.call(command_tar.split())

print("Size of original:")
print(os.path.getsize(folder_test +"/target.tar"))
print("Size of diff:")
print(os.path.getsize(folder_test +"/test-xdiff.tar"))
print("Compression rate:")
print(1.0 - (os.path.getsize(folder_test +"/test-xdiff.tar")*1.0)/(os.path.getsize(folder_test +"/target.tar")*1.0))

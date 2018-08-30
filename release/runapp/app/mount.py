# mount drive using sshfs
# 
import util

def main(sshfs, drive, userhost):
	print(f'Mounting {drive} {userhost}...')
	
	cmd = f'''
		"{sshfs}" {userhost}:/ {drive} 
		-orellinks -oreconnect
		-ouid=-1,gid=-1,create_umask=0007 
		-oVolumePrefix=/sshfs/{userhost}
		-ovolname=LINUX-{userhost} 
		-oFileSystemName=SSHFS 
		-oStrictHostKeyChecking=no
		-oServerAliveInterval=10 
		-oServerAliveCountMax=10000
		-oFileInfoTimeout=10000 
		-oDirInfoTimeout=10000 
		-oVolumeInfoTimeout=10000
		'''.replace('\n',' ').replace('\t','')
	print(cmd)
	util.run(cmd)

if __name__ == '__main__':
	import sys
	assert len(sys.argv) > 2 and '@' in sys.argv[2] # usage: mount.py <drive> <user@host>
	sshfs = r'C:\Program Files\SSHFS-Win\bin\sshfs.exe'
	sys.path.insert(0, os.path.dirname(sshfs))
	main(sshfs, *sys.argv[1:])
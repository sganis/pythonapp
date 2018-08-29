import subprocess

def run():
	print('Running app...')
	for t in subprocess.check_output('tasklist').decode('ascii').split('\n'):
		print(t)

	input("Press Enter to EXIT...")

if __name__ == '__main__':
	run()
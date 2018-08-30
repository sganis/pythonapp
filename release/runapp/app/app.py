import subprocess

def run():
	print('Running app...')
	print('List of first 10 running processes:')
	for i,t in enumerate(subprocess.check_output('tasklist').decode('ascii').split('\n')):
		print(t)
		if i > 9: 
			break

	input("Press Enter to EXIT...")

if __name__ == '__main__':
	run()
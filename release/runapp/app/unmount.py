# unmount drive

def main(drive):
	print(f'Unmounting {drive}...')


if __name__ == '__main__':
	import sys
	assert len(sys.argv) > 1 # usage: unmount.py <drive>
	main(sys.argv[1])
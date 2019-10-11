import glob2

srcdir = './'
objroot = '../obj/'
binroot = '../bin/'
sources = glob2.glob(srcdir + '**/*.cpp')

cflags_common = '-Wall'
linkflags_common = ''

builds = {
	'release': {
		'library': True,
		'cflags': '-O3'
	},
	'debug': {
		'cflags': '-O0 -g -ggdb'
	},
	'profile': {
		'cflags': '-O3 -pg',
		'linkflags': '-pg'
	}
}

binary = 'main'

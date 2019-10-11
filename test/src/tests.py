srcdir = './'
objroot = '../obj/'
binroot = '../bin/'

dut_srcroot = '../../src/'
dut_objroot = '../../obj/'

cflags = '--std=c++17 -Wall -O3 -pg -g -ggdb -Iinclude'
linkflags = '-pg -lpthread -lgtest -lgtest_main'

build = 'release'

test_spec = {
	'BiMap/BiMapTests' : []
}

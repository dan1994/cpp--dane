import os


####### UTILS
def collect_sources(path_list, exclude_sources):
	sources = []
	for path in path_list:
		for root, dirs, files in os.walk(path):
			sources.extend([os.path.join(root, f) for f in files if f.endswith(".cpp") and os.path.join(root, f) not in exclude_sources])
	return sources

def do_all(name, cxxflags, linkflags, libs, source_dirs, target, exclude_sources):
	target = os.path.join('build', name, target)
	source = collect_sources(source_dirs, exclude_sources)
	env = Environment(CXX='clang++', CXXFLAGS=cxxflags, LINKFLAGS=linkflags, LIBS=libs, CPPPATH=['include', 'test/include'])
	env['ENV']['TERM'] = os.environ.get('TERM')
	objs = []
	for s in source:
		# Remove file suffix
		t = os.path.join('build', name, s[: s.rfind('.')])
		objs.append(env.Object(target=t, source=s))
	program = env.Program(target=target, source=objs)
	env.Alias(name, target)
	return env

#######

CXXFLAGS_COMMON = ['-Wall', "--std=c++17"]
CXX_DEBUG_FLAGS = ['-g', '-ggdb', '-O0']
CXX_RELEASE_FLAGS = ['-O3']
LINKFLAGS_COMMON = []
LIBS_COMMON = []
LIBS_GTEST = ['pthread', 'gtest', 'gtest_main']

configs = {
	'debug': {
		'cxxflags': CXXFLAGS_COMMON + CXX_DEBUG_FLAGS,
		'linkflags': LINKFLAGS_COMMON,
		'libs': LIBS_COMMON,
		'source_dirs': ['src'],
		'target': 'dane',
		'exclude_sources': []
	},
	'release': {
		'cxxflags': CXXFLAGS_COMMON + CXX_RELEASE_FLAGS,
		'linkflags': LINKFLAGS_COMMON,
		'libs': LIBS_COMMON,
		'source_dirs': ['src'],
		'target': 'dane',
		'exclude_sources': []
	},
	'test': {
		'cxxflags': CXXFLAGS_COMMON + CXX_DEBUG_FLAGS,
		'linkflags': LINKFLAGS_COMMON,
		'libs': LIBS_COMMON + LIBS_GTEST,
		'source_dirs': ['src', 'test'],
		'target': 'gtest',
		'exclude_sources': ['src/main.cpp']
	}
}

envs = [do_all(name, **value) for name, value in configs.items()]

# Default(configs['debug']['program'])


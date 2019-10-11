import os

CXX='clang++'
CXXFLAGS_COMMON = ['-Wall', "--std=c++17", '-g', '-ggdb']
# LINKFLAGS_COMMON = []
# LIBS_COMMON = []
LIBS_GTEST = ['pthread', 'gtest', 'gtest_main']

# configs = {
# 	'debug': {
# 		'CXXFLAGS': CXXFLAGS_COMMON + ['-g'],
# 		'LINKFLAGS': LINKFLAGS_COMMON,
# 		'LIBS': LIBS_COMMON,
# 		'SourceDir': 'src',
# 		'VariantDir': 'build/debug',
# 		'target': 'dane',
# 		'source': ['main.cpp']
# 	},
# 	'release': {
# 		'CXXFLAGS': CXXFLAGS_COMMON + ['-O3'],
# 		'LINKFLAGS': LINKFLAGS_COMMON,
# 		'LIBS': LIBS_COMMON,
# 		'SourceDir': 'src',
# 		'VariantDir': 'build/release',
# 		'target': 'dane',
# 		'source': ['main.cpp']
# 	},
# 	'test': {
# 		'CXXFLAGS': CXXFLAGS_COMMON + ['-g'],
# 		'LINKFLAGS': LINKFLAGS_COMMON,
# 		'LIBS': LIBS_COMMON + LIBS_GTEST,
# 		'SourceDir': 'test',
# 		'VariantDir': 'build/test',
# 		'target': 'gtest',
# 		'source': ['tests.cpp']
# 	}
# }

# for name, config in configs.items():
# 	config['target'] = os.path.join(config['VariantDir'], config['target'])
# 	config['source'] = [os.path.join(config['VariantDir'], source) for source in config['source']]
# 	config['env'] = Environment(CXX=CXX, CXXFLAGS=config['CXXFLAGS'], LINKFLAGS=config['LINKFLAGS'], LIBS=config['LIBS'])
# 	config['env'].VariantDir(config['VariantDir'], config['SourceDir'])
# 	config['program'] = config['env'].Program(target=config['target'], source=config['source'])
# 	config['env'].Alias(name, config['target'])


# Default(configs['debug']['program'])


env = Environment(CXX=CXX, CXXFLAGS=CXXFLAGS_COMMON, LIBS=LIBS_GTEST)
programs = {}
for root, dirs, files in os.walk('src'):
	if 'impl' in dirs or 'tests' in dirs:
		programs[root] = {}
		programs[root]['sources'] = []
		if 'headers' in dirs:
			programs[root]['CPPPATH'] = os.path.join(root, 'headers')
	if root.endswith('impl') or root.endswith('tests'):
		programs[os.path.dirname(root)]['sources'].extend([os.path.join(root, f) for f in files if f.endswith('.cpp')])

print(programs)

for path, values in programs.items():
	env.Replace(CPPPATH=values['CPPPATH'])
	objs = []
	for s in values['sources']:
		objs.append(env.Object(target=s.replace('src', 'build', 1).rstrip('.cpp'), source=s))
		print('success')
	env.Program(target=path.replace('src', 'build', 1), source=objs)

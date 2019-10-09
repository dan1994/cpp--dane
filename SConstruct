import os

def coverage_builder(source_path, build_path, executable):
	def cmd_func(target, source, env):
		if not GetOption('clean'):
			os.system('utils/coverage/coverage.sh %s %s %s' % (source_path, build_path, executable))
	return Builder(action=cmd_func)

CXX='clang++'
CXXFLAGS_COMMON = ['-Wall']
CXXFLAGS_COVERGAE = ['-fprofile-arcs', '-ftest-coverage']
LINKFLAGS_COMMON = []
LINKFLAGS_COVERGAE = ['--coverage']
LIBS_COMMON = []
LIBS_GTEST = ['pthread', 'gtest', 'gtest_main']

configs = {
	'debug': {
		'CXXFLAGS': CXXFLAGS_COMMON + CXXFLAGS_COVERGAE + ['-g'],
		'LINKFLAGS': LINKFLAGS_COMMON + LINKFLAGS_COVERGAE,
		'LIBS': LIBS_COMMON,
		'SourceDir': 'src',
		'VariantDir': 'build/debug',
		'target': 'dane',
		'source': ['main.cpp'],
		'builders': [
			{
				'name': 'coverage',
				'builder': coverage_builder(os.path.abspath('src'), os.path.abspath('build/debug'), 'dane'),
				'target': os.path.abspath('build/debug/lcov.info')
			}
		]
	},
	'release': {
		'CXXFLAGS': CXXFLAGS_COMMON + ['-O3'],
		'LINKFLAGS': LINKFLAGS_COMMON,
		'LIBS': LIBS_COMMON,
		'SourceDir': 'src',
		'VariantDir': 'build/release',
		'target': 'dane',
		'source': ['main.cpp'],
		'builders': []
	},
	'test': {
		'CXXFLAGS': CXXFLAGS_COMMON + CXXFLAGS_COVERGAE + ['-g'],
		'LINKFLAGS': LINKFLAGS_COMMON + LINKFLAGS_COVERGAE,
		'LIBS': LIBS_COMMON + LIBS_GTEST,
		'SourceDir': 'test',
		'VariantDir': 'build/test',
		'target': 'gtest',
		'source': ['tests.cpp'],
		'builders': [
			{
				'name': 'coverage',
				'builder': coverage_builder(os.path.abspath('test'), os.path.abspath('build/test'), 'gtest'),
				'target': os.path.abspath('build/test/lcov.info')
			}
		]
	}
}

for name, config in configs.items():
	config['target'] = os.path.join(config['VariantDir'], config['target'])
	config['source'] = [os.path.join(config['VariantDir'], source) for source in config['source']]
	config['env'] = Environment(CXX=CXX, CXXFLAGS=config['CXXFLAGS'], LINKFLAGS=config['LINKFLAGS'], LIBS=config['LIBS'])
	config['env'].VariantDir(config['VariantDir'], config['SourceDir'], duplicate=0)
	config['program'] = config['env'].Program(target=config['target'], source=config['source'])
	for builder in config['builders']:
		config['env'].Append(BUILDERS={builder['name']: builder['builder']})
		eval("config['env'].%s(builder['target'], config['program'])" % builder['name'])
	config['env'].Alias(name, config['target'])


Default(configs['debug']['program'])

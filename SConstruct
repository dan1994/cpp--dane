env = Environment(CXX='clang++', CXXFLAGS='-Wall')

gtest_libs = ['pthread', 'gtest', 'gtest_main']

env.Program(target='build/dane', source=['src/main.cpp'])
env.Program(target='build/gtest', source=['test/tests.cpp'], LIBS=gtest_libs)

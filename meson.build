project('vecctor', 'c', version: '0.0.1', default_options:['warning_level=everything', 'b_lto=true', 'c_std=c2x'])

incdir = include_directories('include')

# subdir('src')

vecctor = both_libraries('vecctor',
	'vecctor.c',
	include_directories: incdir,
    )

subdir('examples')

subdir('tests')

test('normal use', tests)

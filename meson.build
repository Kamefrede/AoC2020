project('aoc_2020', 'c',
	default_options: [
			 'c_std=c18',
			 'c_args=-Wextra -Wall'
	]
)

add_project_arguments('-DPCRE2_CODE_UNIT_WIDTH=8', language : 'c')
add_project_arguments('-D_POSIX_C_SOURCE=200809L', language : 'c')

ssl = dependency('openssl')
pcre = dependency('libpcre2-8')

uthash_includes = ['/usr/local/include']

util_lib = static_library(
	 'util',
	 ['src/util.c'],
   include_directories: ['include'] + uthash_includes
)

utils = declare_dependency(
      	link_with: util_lib,
	include_directories : ['include'] + uthash_includes
)

executable('day1', 'src/day1.c', include_directories: uthash_includes, dependencies: [utils])
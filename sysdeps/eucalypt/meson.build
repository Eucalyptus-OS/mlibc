sysdep_supported_options = {
	'posix': true,
}

if not no_headers
	install_headers(
		'include/abi-bits/auxv.h',
		'include/abi-bits/errno.h',
		'include/abi-bits/fcntl.h',
		'include/abi-bits/mode_t.h',
		'include/abi-bits/seek-whence.ha',
		'include/abi-bits/stat.h',
		subdir: 'abi-bits',
		follow_symlinks: true
	)
endif

if not headers_only
	crt = custom_target('crt1',
		build_by_default: true,
		command: c_compiler.cmd_array() + ['-c', '-o', '@OUTPUT@', '@INPUT@'],
		input: 'crt1.S',
		output: 'crt1.o',
		install: true,
		install_dir: get_option('libdir')
	)
endif

rtld_sources += files(
	'sysdeps.cpp',
)
rtld_include_dirs += include_directories('include')

libc_sources += files(
	'entry.cpp',
	'sysdeps.cpp',
)
libc_include_dirs += include_directories('include')
sysdep_supported_options = {
	'posix': false,
}
if not no_headers
	install_headers(
		'include/abi-bits/auxv.h',
		'include/abi-bits/blkcnt_t.h',
		'include/abi-bits/blksize_t.h',
		'include/abi-bits/clockid_t.h',
		'include/abi-bits/dev_t.h',
		'include/abi-bits/errno.h',
		'include/abi-bits/fcntl.h',
		'include/abi-bits/fd_set.h',
		'include/abi-bits/fsblkcnt_t.h',
		'include/abi-bits/fsfilcnt_t.h',
		'include/abi-bits/gid_t.h',
		'include/abi-bits/ino_t.h',
		'include/abi-bits/mode_t.h',
		'include/abi-bits/nlink_t.h',
		'include/abi-bits/off_t.h',
		'include/abi-bits/pid_t.h',
		'include/abi-bits/seek-whence.h',
		'include/abi-bits/stat.h',
		'include/abi-bits/suseconds_t.h',
		'include/abi-bits/time_t.h',
		'include/abi-bits/uid_t.h',
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
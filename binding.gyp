{
	"targets": [
		{
			# have to specify 'liblib' here since gyp will remove the first one :\
			# https://github.com/TooTallNate/node-gyp/issues/128

			'target_name': 'liblibnodegit',
			"sources": [
				"src/libnodegit.cc",
				"src/repository.cc",
				"src/commit.cc"
			],
			'include_dirs': [
				'vendor/libgit2/include'
			],

			'libraries': [
				'-L<!(pwd)/vendor/libgit2/build',
				'-lgit2'
			],

			'cflags': [
				'-Wall'
			],

			'ldflags': [
				'-Wl,-rpath,\$$ORIGIN/../../vendor/libgit2/build'
			]
		}
	]
}

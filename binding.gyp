{
	"targets": [
		{
			# have to specify 'liblib' here since gyp will remove the first one :\
			# https://github.com/TooTallNate/node-gyp/issues/128

			'target_name': 'liblibnodegit',
			"sources": [
				"src/libnodegit.cc",
				"src/repository.cc"
			],
			'libraries': [
				'-lgit2'
			]

		}
	]
}

{
    'targets': [
        {
            'target_name': 'sdf',
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
            'dependencies': [
                'gyp/libmsdfgen.gyp:libmsdfgen',
            ],
            "libraries": [
               "<(module_root_dir)/vendor/msdfgen/freetype/win64/freetype"
            ],
            'sources': [
                'src/util.cc',
                'src/sdf.cc',
            ],
            'include_dirs':
            ["<!@(node -p \"require('node-addon-api').include\")"],

            'conditions': [
                ['OS=="mac"', {
                    'cflags+': ['-fvisibility=hidden'],
                    'xcode_settings': {
                        'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES',  # -fvisibility=hidden
                    }
                }]
            ]
        }
    ]
}

{
    'targets': [
        {
            'target_name': 'libmsdfgen',
            'type': 'static_library',
            'defines': [ 
                'MSDFGEN_CMAKE_BUILD'
            ],
            'include_dirs': [
                    '../vendor/msdfgen/freetype/include/',

                    '../vendor/msdfgen/include/',
                    '../vendor/msdfgen/ext/',
            ],
            'sources': [
                # From vendor/freetype/docs/INSTALL.ANY
                # This is for the default config. If we want to customize the config, we
                # need to create a custom ftconfig.h with the appropriate definitions
                # according to vendor/freetype/docs/CUSTOMIZING.

                # base components (required)
                '../vendor/msdfgen/core/*.cpp',
                '../vendor/msdfgen/ext/import-font.cpp',
                '../vendor/msdfgen/lib/lodepng.cpp',
                '../vendor/msdfgen/lib/tinyxml2.cpp',

            ],
            'direct_dependent_settings': {
                'include_dirs': [
                    '../vendor/msdfgen/include/',
                    '../vendor/msdfgen/freetype/include/',
                ],
            },
        }
    ]
}

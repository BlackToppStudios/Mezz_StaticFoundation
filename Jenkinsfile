#!groovy


stage('Checkout') {
    parallel FedoraGcc: { node('FedoraGcc') {
        checkout scm
    } },
    MacOSSierra: { node('MacOSSierra') {
        checkout scm
    } },
    RaspianJessie: { node('RaspianJessie') {
        checkout scm
    } },
    UbuntuClang: { node('UbuntuClang') {
        checkout scm
    } },
    UbuntuEmscripten: { node('UbuntuEmscripten') {
        checkout scm
    } },
    UbuntuGcc: { node('UbuntuGcc') {
        checkout scm
    } },
    windows7Mingw32: { node('windows7Mingw32') {
        checkout scm
    } },
    windows7Mingw64: { node('windows7Mingw64') {
        checkout scm
    } },
    windows7msvc: { node('windows7msvc') {
        checkout scm
    } }
}

stage('Build-Debug') {
    parallel FedoraGcc: { node('FedoraGcc') {
        sh 'mkdir -p build-debug'
        dir('build-debug') { sh """
            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/                                                              &&
            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF               &&
            ninja
        """ }
    } },
    MacOSSierra: { node('MacOSSierra') {
        sh 'mkdir -p build-debug'
        dir('build-debug') { sh """
            export MEZZ_PACKAGE_DIR=/Users/cisadmin/Code/                                                             &&
            export PATH=$PATH:/usr/local/bin/                                                                         &&
            cmake -G"Xcode" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF               &&
            cmake --build .
        """ }
    } },
    RaspianJessie: {node('RaspianJessie') {
        sh 'mkdir -p build-debug'
        // The first group of variables simulates running source ~/emsdk-portable/emsdk_env.sh as the emscripten
        // portable sdkrequires to work. The next few sets CC and CXX which CMake will use to know to use
        // the emscripten compiler. The last one sets Mezzanine specific variables so pacakges are found.
        dir('build-debug') { sh """
            export CC=gcc-6                                                                                           &&
            export CXX=g++-6                                                                                          &&
            export MEZZ_PACKAGE_DIR=/home/pi/Code/                                                                    &&
            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF               &&
            ninja
        """ }
    } },
    UbuntuClang: { node('UbuntuClang') {
        sh 'mkdir -p build-debug'
        dir('build-debug') { sh """
            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/                                                              &&
            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF               &&
            ninja
        """ }
    } },
    UbuntuEmscripten: { node('UbuntuEmscripten') {
        sh 'mkdir -p build-debug'
        // The first group of variables simulates running source ~/emsdk-portable/emsdk_env.sh as the emscripten
        // portable sdkrequires to work. The next few sets CC and CXX which CMake will use to know to use
        // the emscripten compiler. The last one sets Mezzanine specific variables so pacakges are found.
        dir('build-debug') { sh """
            export CC=emcc                                                                                            &&
            export CXX=em++                                                                                           &&
            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/                                                              &&
            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF               &&
            ninja
        """ }
    } },
    UbuntuGcc: { node('UbuntuGcc') {
        sh 'mkdir -p build-debug'
        dir('build-debug') { sh """
            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/                                                              &&
            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF               &&
            ninja
        """ }
    } },
    windows7Mingw32: { node('windows7Mingw32') {
        bat 'if not exist "build-debug" mkdir build-debug'
        dir('build-debug') {
            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
            bat 'ninja'
        }
    } },
    windows7Mingw64: { node('windows7Mingw64') {
        bat 'if not exist "build-debug" mkdir build-debug'
        dir('build-debug') {
            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
            bat 'ninja'
        }
    } },
    windows7msvc: { node('windows7msvc') {
        bat 'if not exist "build-debug" mkdir build-debug'
        dir('build-debug') {
            bat '"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_amd64 && cmake -G"Visual Studio 15 2017 Win64" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
            bat 'cmake --build .'
        }
    } }
}

stage('Test-Debug') {
    parallel  FedoraGcc: { node('FedoraGcc') {
        dir('build-debug') { sh """
            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """ }
    } },
    MacOSSierra: { node('MacOSSierra') {
        dir('build-debug') { sh """
            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:1 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:1 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """ }
    } },
    RaspianJessie: { node('RaspianJessie') {
        dir('build-debug') { sh """
           ./StaticFoundation_Tester MEZZ_Arch32:1 MEZZ_Arch64:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """}
    } },
    UbuntuClang: { node('UbuntuClang') {
        dir('build-debug') { sh """
           ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """ }
    } },
    UbuntuEmscripten: { node('UbuntuEmscripten') {
        dir('build-debug') { sh """
            export PATH=$PATH:/home/cisadmin/emsdk-portable/node/4.1.1_64bit/bin                                  &&
            node StaticFoundation_Tester.js MEZZ_CompilerIsEmscripten:1 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """ }
    } },
    UbuntuGcc: { node('UbuntuGcc') {
        dir('build-debug') { sh """
               ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """ }
    } },
    windows7Mingw32: { node('windows7Mingw32') {
        dir('build-debug') {
            bat 'StaticFoundation_Tester MEZZ_Arch32:1 MEZZ_Arch64:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0'
        }
    } },
    windows7Mingw64: { node('windows7Mingw64') {
        dir('build-debug') {
            bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0'
        }
    } },
    windows7msvc: { node('windows7msvc') {
        dir('build-debug') {
            bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:1 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:0 MEZZ_CompilerDesignMS:1'
        }
    } }
}

stage('Build-Release') {
    parallel FedoraGcc: { node('FedoraGcc') {
        sh 'mkdir -p build-Release'
        dir('build-Release') { sh """
            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/                                                              &&
            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF             &&
            ninja
        """ }
    } },
    MacOSSierra: { node('MacOSSierra') {
        sh 'mkdir -p build-Release'
        dir('build-Release') { sh """
            export MEZZ_PACKAGE_DIR=/Users/cisadmin/Code/                                                             &&
            export PATH=$PATH:/usr/local/bin/                                                                         &&
            cmake -G"Xcode" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF             &&
            cmake --build .
        """ }
    } },
    RaspianJessie: {node('RaspianJessie') {
        sh 'mkdir -p build-Release'
        // The first group of variables simulates running source ~/emsdk-portable/emsdk_env.sh as the emscripten
        // portable sdkrequires to work. The next few sets CC and CXX which CMake will use to know to use
        // the emscripten compiler. The last one sets Mezzanine specific variables so pacakges are found.
        dir('build-Release') { sh """
            export CC=gcc-6                                                                                           &&
            export CXX=g++-6                                                                                          &&
            export MEZZ_PACKAGE_DIR=/home/pi/Code/                                                                    &&
            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF             &&
            ninja
        """ }
    } },
    UbuntuClang: { node('UbuntuClang') {
        sh 'mkdir -p build-Release'
        dir('build-Release') { sh """
            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/                                                              &&
            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF             &&
            ninja
        """ }
    } },
    UbuntuEmscripten: { node('UbuntuEmscripten') {
        sh 'mkdir -p build-Release'
        // The first group of variables simulates running source ~/emsdk-portable/emsdk_env.sh as the emscripten
        // portable sdkrequires to work. The next few sets CC and CXX which CMake will use to know to use
        // the emscripten compiler. The last one sets Mezzanine specific variables so pacakges are found.
        dir('build-Release') { sh """
            export CC=emcc                                                                                            &&
            export CXX=em++                                                                                           &&
            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/                                                              &&
            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF             &&
            ninja
        """ }
    } },
    UbuntuGcc: { node('UbuntuGcc') {
        sh 'mkdir -p build-Release'
        dir('build-Release') { sh """
            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/                                                              &&
            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF             &&
            ninja
        """ }
    } },
    windows7Mingw32: { node('windows7Mingw32') {
        bat 'if not exist "build-Release" mkdir build-Release'
        dir('build-Release') {
            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
            bat 'ninja'
        }
    } },
    windows7Mingw64: { node('windows7Mingw64') {
        bat 'if not exist "build-Release" mkdir build-Release'
        dir('build-Release') {
            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
            bat 'ninja'
        }
    } },
    windows7msvc: { node('windows7msvc') {
        bat 'if not exist "build-Release" mkdir build-Release'
        dir('build-Release') {
            bat '"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_amd64 && cmake -G"Visual Studio 15 2017 Win64" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
            bat 'cmake --build .'
        }
    } }
}

stage('Test-Release') {
    parallel  FedoraGcc: { node('FedoraGcc') {
        dir('build-Release') { sh """
            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """ }
        junit '**/*.xml'
    } },
    MacOSSierra: { node('MacOSSierra') {
        dir('build-Release') { sh """
            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:1 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:1 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """ }
    } },
    RaspianJessie: { node('RaspianJessie') {
        dir('build-Release') { sh """
           ./StaticFoundation_Tester MEZZ_Arch32:1 MEZZ_Arch64:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """}
    } },
    UbuntuClang: { node('UbuntuClang') {
        dir('build-Release') { sh """
           ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """ }
    } },
    UbuntuEmscripten: { node('UbuntuEmscripten') {
        dir('build-Release') { sh """
            export PATH=$PATH:/home/cisadmin/emsdk-portable/node/4.1.1_64bit/bin                                  &&
            node StaticFoundation_Tester.js MEZZ_CompilerIsEmscripten:1 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """ }
    } },
    UbuntuGcc: { node('UbuntuGcc') {
        dir('build-Release') { sh """
               ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
        """ }
    } },
    windows7Mingw32: { node('windows7Mingw32') {
        dir('build-Release') {
            bat 'StaticFoundation_Tester MEZZ_Arch32:1 MEZZ_Arch64:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0'
        }
    } },
    windows7Mingw64: { node('windows7Mingw64') {
        dir('build-Release') {
            bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0'
        }
    } },
    windows7msvc: { node('windows7msvc') {
        dir('build-Release') {
            bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:1 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:0 MEZZ_CompilerDesignMS:1'
        }
    } }
}

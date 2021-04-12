#!groovy

pipeline {
    agent none
    options {
        buildDiscarder(logRotator(numToKeepStr:'30'))
        timeout(time: 1500, unit: 'SECONDS')
    }
    stages {

        stage('BuildTest') {
            parallel {

                stage('FedoraGcc-Debug') {
                    agent { label "FedoraGcc" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON &&
                            ninja &&
                            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:1 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0 &&
                            bash <(curl -s https://codecov.io/bash) -t ${env.CODECOV_TOKEN}
                        """ }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('FedoraGcc-Release') {
                    agent { label "FedoraGcc" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                        """ }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

                stage('MacOSAir-Debug') {
                    agent { label "MacOSAir" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            export PATH='$PATH:/usr/local/bin/' &&
                            cmake -G"Xcode" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON &&
                            cmake --build . &&
                           ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:1 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:1 MEZZ_Linux:0 MEZZ_MacOSX:1 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0 &&
                           bash <(curl -s https://codecov.io/bash) -t ${env.CODECOV_TOKEN}
                        """ }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('MacOSAir-Release') {
                    agent { label "MacOSAir" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            export PATH='$PATH:/usr/local/bin/' &&
                            cmake -G"Xcode" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            cmake --build . &&
                           ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:1 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:1 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                        """ }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

                stage('Raspbian-Debug') {
                    agent { label "Raspbian" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON &&
                            ninja &&
                            ./StaticFoundation_Tester MEZZ_Arch32:1 MEZZ_Arch64:0 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:1 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0 &&
                            bash <(curl -s https://codecov.io/bash) -t ${env.CODECOV_TOKEN}
                         """ }
                    }
                    post {
                         always {
                             junit "build-debug/**/Mezz*.xml"
                         }
                    }
                }
                stage('Raspbian-Release') {
                    agent { label "Raspbian" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            ./StaticFoundation_Tester MEZZ_Arch32:1 MEZZ_Arch64:0 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                         """ }
                    }
                    post {
                         always {
                             junit "build-release/**/Mezz*.xml"
                         }
                    }
                }

                stage('UbuntuClang-Debug') {
                    agent { label "UbuntuClang" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON &&
                            ninja  &&
                            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:1 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:1 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0 &&
                            bash <(curl -s https://codecov.io/bash) -t ${env.CODECOV_TOKEN}
                         """ }
                     }
                     post {
                         always {
                             junit "build-debug/**/Mezz*.xml"
                         }
                     }
                }
                stage('UbuntuClang-Release') {
                    agent { label "UbuntuClang" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja  &&
                            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:1 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                         """ }
                     }
                     post {
                         always {
                             junit "build-release/**/Mezz*.xml"
                         }
                     }
                }

                stage('UbuntuEmscripten-Debug') {
                    agent { label "UbuntuEmscripten" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            source ~/emsdk/emsdk_env.sh &&
                            cmake -G"Ninja" .. -DCMAKE_TOOLCHAIN_FILE=~/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_C_COMPILER=emcc -DCMAKE_CXX_COMPILER=em++ -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            node StaticFoundation_Tester.js MEZZ_CompilerIsEmscripten:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:1 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                        """ }
                    }
                    // Don't capture Emscripten logs, because it cannot make files
                }
                stage('UbuntuEmscripten-Release') {
                    agent { label "UbuntuEmscripten" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            source ~/emsdk/emsdk_env.sh &&
                            cmake -G"Ninja" .. -DCMAKE_TOOLCHAIN_FILE=~/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_C_COMPILER=emcc -DCMAKE_CXX_COMPILER=em++ -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            node StaticFoundation_Tester.js MEZZ_CompilerIsEmscripten:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:1 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                        """ }
                    }
                    // Don't capture Emscripten logs, because it cannot make files
                }

                stage('UbuntuGcc-Debug') {
                    agent { label "UbuntuGcc" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON &&
                            ninja &&
                            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:1 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0 &&
                            bash <(curl -s https://codecov.io/bash) -t ${env.CODECOV_TOKEN}
                        """ }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('UbuntuGcc-Release') {
                    agent { label "UbuntuGcc" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                        """ }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

                stage('Windows10Mingw32-Debug') {
                    agent { label "Windows10Mingw32" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-debug" mkdir build-debug'
                        dir('build-debug') {
                            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF -DMEZZ_ForceGcc32Bit=ON'
                            bat 'ninja'
                            bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:1 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0'
                        }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('Windows10Mingw32-Release') {
                    agent { label "Windows10Mingw32" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-release" mkdir build-release'
                        dir('build-release') {
                            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF -DMEZZ_ForceGcc32Bit=ON'
                            bat 'ninja'
                            bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:1 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0'
                        }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

                stage('Windows10Mingw64-Debug') {
                    agent { label "Windows10Mingw64" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-debug" mkdir build-debug'
                        dir('build-debug') {
                            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
                            bat 'ninja'
                            bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0'
                        }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('Windows10Mingw64-Release') {
                    agent { label "Windows10Mingw64" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-release" mkdir build-release'
                        dir('build-release') {
                            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
                            bat 'ninja'
                            bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0'
                        }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

                stage('Windows10MSVC-Debug') {
                    agent { label "Windows10MSVC" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-debug" mkdir build-debug'
                        dir('build-debug') {
                            bat '"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_amd64 && cmake -G"Visual Studio 16 2019" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF && cmake --build .'
                            bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:1 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:0 MEZZ_CompilerDesignMS:1'
                        }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('Windows10MSVC-Release') {
                    agent { label "Windows10MSVC" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-release" mkdir build-release'
                        dir('build-release') {
                            bat '"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_amd64 && cmake -G"Visual Studio 16 2019" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF && cmake --build .'
                            bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_ForceGcc32Bit:0 MEZZ_Trace:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:1 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:0 MEZZ_CompilerDesignMS:1'
                        }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

            } // parallel
        } // Build and Test
    } // Stages

}

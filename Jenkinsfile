#!groovy

pipeline {
    agent none
    options {
        buildDiscarder(logRotator(numToKeepStr:'30'))
    }
    stages {
        stage('Checkout') {
            parallel {
                stage('FedoraGcc') {
                    agent { label "FedoraGcc" }
                    steps { checkout scm }
                }

            }
        }

        stage('Build-Debug') {
            parallel {
                stage('FedoraGcc') {
                    agent { label "FedoraGcc" }
                    steps {
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """
                            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/ &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja
                        """ }
                    }
                }
                stage('MacOSSierra') {
                    agent { label "MacOSSierra" }
                    steps {
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """
                            export MEZZ_PACKAGE_DIR=/Users/cisadmin/Code/                                                             &&
                            export PATH=$PATH:/usr/local/bin/                                                                         &&
                            cmake -G"Xcode" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF               &&
                            cmake --build .
                        """ }
                    }
                }
                stage('RaspianJessie') {
                    agent { label "RaspianJessie" }
                    steps {
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """
                            export CC=gcc-6                                                                                           &&
                            export CXX=g++-6                                                                                          &&
                            export MEZZ_PACKAGE_DIR=/home/pi/Code/                                                                    &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF               &&
                            ninja
                        """ }
                    }
                }
                stage('UbuntuClang') {
                    agent { label "UbuntuClang" }
                    steps {
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """
                            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/                                                              &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF               &&
                            ninja
                        """ }
                    }
                }
                stage('UbuntuEmscripten') {
                    agent { label "UbuntuEmscripten" }
                    steps {
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
                    }
                }
                stage('UbuntuGcc') {
                    agent { label "UbuntuGcc" }
                    steps {
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """
                            export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/                                                              &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF               &&
                            ninja
                        """ }
                    }
                }
                stage('windows7Mingw32') {
                    agent { label "windows7Mingw32" }
                    steps {
                        bat 'if not exist "build-debug" mkdir build-debug'
                        dir('build-debug') {
                            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
                            bat 'ninja'
                        }
                    }
                }
                stage('windows7Mingw64') {
                    agent { label "windows7Mingw64" }
                    steps {
                        bat 'if not exist "build-debug" mkdir build-debug'
                        dir('build-debug') {
                            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
                            bat 'ninja'
                        }
                    }
                }
                stage('windows7msvc') {
                    agent { label "windows7msvc" }
                    steps {
                        bat 'if not exist "build-debug" mkdir build-debug'
                        dir('build-debug') {
                            bat '"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_amd64 && cmake -G"Visual Studio 15 2017 Win64" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
                            bat 'cmake --build .'
                        }
                    }
                }
            }

            stage('Test-Debug') {
                parallel {
                    stage('FedoraGcc-build') {
                        agent { label "FedoraGcc" }
                        steps {
                            dir('build-debug') { sh """
                                ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                            """ }
                        }
                    }
                    stage('MacOSSierra') {
                        agent { label "MacOSSierra" }
                        steps {
                            dir('build-debug') { sh """
                                ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:1 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:1 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                            """ }
                        }
                    }
                    stage('RaspianJessie') {
                        agent { label "RaspianJessie" }
                        steps {
                            dir('build-debug') { sh """
                               ./StaticFoundation_Tester MEZZ_Arch32:1 MEZZ_Arch64:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                            """}
                        }
                    }
                    stage('UbuntuClang') {
                        agent { label "UbuntuClang" }
                        steps {
                            dir('build-debug') { sh """
                               ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                            """ }
                        }
                    }
                    stage('UbuntuEmscripten') {
                        agent { label "UbuntuEmscripten" }
                        steps {
                            dir('build-debug') { sh """
                                node StaticFoundation_Tester.js MEZZ_CompilerIsEmscripten:1 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                            """ }
                        }
                    }
                    stage('UbuntuGcc') {
                        agent { label "UbuntuGcc" }
                        steps {
                            dir('build-debug') { sh """
                                   ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                            """ }
                        }
                    }
                    stage('windows7Mingw32') {
                        agent { label "windows7Mingw32" }
                        steps {
                            dir('build-debug') {
                                bat 'StaticFoundation_Tester MEZZ_Arch32:1 MEZZ_Arch64:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0'
                            }
                        }
                    }
                    stage('windows7Mingw64') {
                        agent { label "windows7Mingw64" }
                        steps {
                            dir('build-debug') {
                                bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0'
                            }
                        }
                    }
                    stage('windows7msvc') {
                        agent { label "windows7msvc" }
                        steps {
                            dir('build-debug') {
                                bat 'StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:1 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:0 MEZZ_Windows:1 MEZZ_CompilerDesignNix:0 MEZZ_CompilerDesignMS:1'
                            }
                        }
                    }
                }
            }
//            parallel FedoraGcc: { node('FedoraGcc') {
//                checkout scm
//            } },
//            MacOSSierra: { node('MacOSSierra') {
//                checkout scm
//            } },
//            RaspianJessie: { node('RaspianJessie') {
//                checkout scm
//            } },
//            UbuntuClang: { node('UbuntuClang') {
//                checkout scm
//            } },
//            UbuntuEmscripten: { node('UbuntuEmscripten') {
//                checkout scm
//            } },
//            UbuntuGcc: { node('UbuntuGcc') {
//                checkout scm
//            } },
//            windows7Mingw32: { node('windows7Mingw32') {
//                checkout scm
//            } },
//            windows7Mingw64: { node('windows7Mingw64') {
//                checkout scm
//            } },
//            windows7msvc: { node('windows7msvc') {
//                checkout scm
//            } }
        }

    } // stages



    //    failure (
    //        mail to: 'sqeaky@blacktoppstudios.com, makoenergy@blacktoppstudios.com',
    //             subject: "Failure - ${env.JOB_NAME}",
    //             body: "Failure - ${env.JOB_NAME} - Branch ${env.BRANCH_NAME} - Build # ${env.BUILD_NUMBER}\n\n" +
    //                   "Check console output at ${env.BUILD_URL} to view the results."
    //    }

}

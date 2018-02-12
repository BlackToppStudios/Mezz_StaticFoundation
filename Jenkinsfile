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
                stage('MacOSSierra') {
                    agent { label "MacOSSierra" }
                    steps { checkout scm }
                }
                stage('RaspianJessie') {
                    agent { label "RaspianJessie" }
                    steps { checkout scm }
                }
                stage('UbuntuClang') {
                    agent { label "UbuntuClang" }
                    steps { checkout scm }
                }
                stage('UbuntuEmscripten') {
                    agent { label "UbuntuEmscripten" }
                    steps { checkout scm }
                }
                stage('UbuntuGcc') {
                    agent { label "UbuntuGcc" }
                    steps { checkout scm }
                }
                stage('windows7Mingw32') {
                    agent { label "windows7Mingw32" }
                    steps { checkout scm }
                }
                stage('windows7Mingw64') {
                    agent { label "windows7Mingw64" }
                    steps { checkout scm }
                }
                stage('windows7msvc') {
                    agent { label "windows7msvc" }
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

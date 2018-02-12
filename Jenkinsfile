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

        stage('BuildTest-Debug') {
            parallel {
                stage('FedoraGcc') {
                    agent { label "FedoraGcc" }
                    environment {
                        MEZZ_PACKAGE_DIR = '/home/cisadmin/Code/'
                    }
                    steps {
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                        """ }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('MacOSSierra') {
                    agent { label "MacOSSierra" }
                    environment {
                        MEZZ_PACKAGE_DIR = '/home/cisadmin/Code/'
                    }
                    steps {
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """
                            export PATH='$PATH:/usr/local/bin/' &&
                            cmake -G"Xcode" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            cmake --build . &&
                           ./StaticFoundation_Tester MEZZ_Arch32:0 MEZZ_Arch64:1 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:1 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:0 MEZZ_MacOSX:1 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                        """ }
                        }
                        post {
                            always {
                                junit "build-debug/**/Mezz*.xml"
                            }
                        }
                    }
                }
                stage('RaspianJessie') {
                    agent { label "RaspianJessie" }
                    environment {
                        CC = 'gcc-6'
                        CXX = 'g++-6'
                        MEZZ_PACKAGE_DIR = '/home/pi/Code/'
                    }
                    steps {
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """
                            export MEZZ_PACKAGE_DIR=/home/pi/Code/ &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            ./StaticFoundation_Tester MEZZ_Arch32:1 MEZZ_Arch64:0 MEZZ_CompilerIsEmscripten:0 MEZZ_CompilerIsGCC:1 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_CompilerIsMsvc:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:1 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0
                         """ }
                    }
                    post {
                         always {
                             junit "build-debug/**/Mezz*.xml"
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


    } // stages



    //    failure (
    //        mail to: 'sqeaky@blacktoppstudios.com, makoenergy@blacktoppstudios.com',
    //             subject: "Failure - ${env.JOB_NAME}",
    //             body: "Failure - ${env.JOB_NAME} - Branch ${env.BRANCH_NAME} - Build # ${env.BUILD_NUMBER}\n\n" +
    //                   "Check console output at ${env.BUILD_URL} to view the results."
    //    }

}

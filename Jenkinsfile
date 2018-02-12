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
                stage('FedoraGcc-build') {
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
                    }
                }
                stage('RaspianJessie') {
                    agent { label "RaspianJessie" }
                    steps {
                    }
                }
                stage('UbuntuClang') {
                    agent { label "UbuntuClang" }
                    steps {
                    }
                }
                stage('UbuntuEmscripten') {
                    agent { label "UbuntuEmscripten" }
                    steps {
                    }
                }
                stage('UbuntuGcc') {
                    agent { label "UbuntuGcc" }
                    steps {
                    }
                }
                stage('windows7Mingw32') {
                    agent { label "windows7Mingw32" }
                    steps {
                    }
                }
                stage('windows7Mingw64') {
                    agent { label "windows7Mingw64" }
                    steps {
                    }
                }
                stage('windows7msvc') {
                    agent { label "windows7msvc" }
                    steps {
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

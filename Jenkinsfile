#!groovy

try {
    stage('Checkout') {
        parallel UbuntuEmscripten: {
            node('UbuntuEmscripten') {
                checkout scm
            }
        }//,
        // Label: {
        //     node('Executorname') {
        //         sh "shell commands here"
        //     }
        // }
    }

    stage('Build') {
        parallel UbuntuEmscripten: {
            node('UbuntuEmscripten') {
                sh """
                    source emsdk-portable/emsdk_env.sh
                 && export CC=emcc
                 && export CXX=em++
                 && export MEZZ_PACKAGE_DIR=/home/cisadmin/Code/
                 && mkdir build
                 && cd build
                 && cmake -G"Ninja" .. -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF
                 && ninja
                """
            }
        }
    }

    stage('Test') {
        parallel UbuntuEmscripten: {
            node('UbuntuEmscripten') {
                sh "node StaticFoundation_Tester.js MEZZ_CompilerIsEmscripten:1 MEZZ_CompilerIsGCC:0 MEZZ_CompilerIsClang:0 MEZZ_CompilerIsIntel:0 MEZZ_BuildDoxygen:0 MEZZ_Debug:0 MEZZ_CodeCoverage:0 MEZZ_Linux:1 MEZZ_MacOSX:0 MEZZ_Windows:0 MEZZ_CompilerDesignNix:1 MEZZ_CompilerDesignMS:0"
            }
        }
    }

    stage('SendMail') {
        notifyMail("Success!", "Build of Mezz_StaticFoundation Successful.")
    }
}
catch(buildException) {
    notifyMail("Failure!", "Build of Mezz_StaticFoundation Failed!\nException: ${buildException}")
    throw buildException
}

def notifyMail (def Status, def ExtraInfo) {
    mail to: 'sqeaky@blacktoppstudios.com, makoenergy@blacktoppstudios.com',
         subject: "${Status} - ${env.JOB_NAME}",
         body: "${Status} - ${env.JOB_NAME} - Jenkins Build ${env.BUILD_NUMBER}\n\n" +
               "${ExtraInfo}\n\n" +
               "Check console output at $BUILD_URL to view the results."
}


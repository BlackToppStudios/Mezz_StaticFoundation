project(SUBPROject)

include(Jagati.cmake)
StandardJagatiSetup()

AddJagatiLibary("${SUBPROjectBinaryDir}libSP.so")
AddJagatiConfig("MEZZ_FOO" "BAR" "")
AddJagatiConfig("MEZZ_EmptyOption" "" "")
AddJagatiConfig("MEZZ_Remarked_FOO" "BAR" "//")
AddJagatiConfig("MEZZ_EmptyOption_nope" "" "//")

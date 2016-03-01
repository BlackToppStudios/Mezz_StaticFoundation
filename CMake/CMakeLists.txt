project(SUBPROject)

include(Jagati.cmake)
StandardJagatiSetup()

AddJagatiLibary("${SUBPROjectBinaryDir}libSP.so")

AddJagatiConfig("MEZZ_FOO" "BAR" ON)
AddJagatiConfig("MEZZ_EmptyOption" "" ON)
AddJagatiConfig("MEZZ_Remarked_FOO" "BAR" OFF)
AddJagatiConfig("MEZZ_EmptyOption_nope" "" OFF)

cmake_minimum_required(VERSION 3.15)

project(SpleeterUI LANGUAGES CSharp)


include(CSharpUtilities)


add_subdirectory(${CMAKE_SOURCE_DIR}/SpleeterLib SpleeterLib)


set(SOURCE_DIR ${CMAKE_SOURCE_DIR})



#add_custom_target(RunAtStartOfBuild ALL
#    COMMAND ${CMAKE_COMMAND} -E env powershell.exe -File ${SOURCE_DIR}/SpleeterUI/build.ps1
#    WORKING_DIRECTORY ${SOURCE_DIR}/SpleeterUI
#    COMMENT "Running script.."
   
#)

#execute_process(
#    COMMAND ${CMAKE_COMMAND} -E env powershell.exe -File ${SOURCE_DIR}/SpleeterUI/copyresources.ps1
#    #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#    OUTPUT_VARIABLE FOO
#    RESULT_VARIABLE FOOR
#    ERROR_VARIABLE FOO_ER
#)

#SET(CMAKE_VS_NUGET_PACKAGE_RESTORE ON)

add_executable(SpleeterUI
    ${SOURCE_DIR}/SpleeterUI/App.xaml.cs
    ${SOURCE_DIR}/SpleeterUI/AssemblyInfo.cs
    ${SOURCE_DIR}/SpleeterUI/MainWindow.xaml.cs
    ${SOURCE_DIR}/SpleeterUI/App.xaml
    ${SOURCE_DIR}/SpleeterUI/MainWindow.xaml
    ${SOURCE_DIR}/SpleeterUI/App.config
    
)

csharp_set_designer_cs_properties(
    ${SOURCE_DIR}/SpleeterUI/AssemblyInfo.cs)


csharp_set_xaml_cs_properties(
    ${SOURCE_DIR}/SpleeterUI/App.xaml
    ${SOURCE_DIR}/SpleeterUI/App.xaml.cs
    ${SOURCE_DIR}/SpleeterUI/MainWindow.xaml
    ${SOURCE_DIR}/SpleeterUI/MainWindow.xaml.cs)

set(APP_XAML_PATH "${SOURCE_DIR}/SpleeterUI/App.xaml")
set_property(SOURCE ${APP_XAML_PATH} PROPERTY VS_XAML_TYPE "ApplicationDefinition")


target_compile_options(SpleeterUI PRIVATE "/langversion:latest")


set_target_properties(SpleeterUI PROPERTIES
    DOTNET_SDK "Microsoft.NET.Sdk"
    DOTNET_TARGET_FRAMEWORK "net6.0-windows"
    WIN32_EXECUTABLE TRUE
    VS_GLOBAL_UseWPF "true"
    VS_GLOBAL_UseWindowsForms "true"
    )
    


target_link_libraries(SpleeterUI PRIVATE SpleeterLib)



add_dependencies(SpleeterUI SpleeterLib)



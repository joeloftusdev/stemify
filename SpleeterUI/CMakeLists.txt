cmake_minimum_required(VERSION 3.15)

project(SpleeterUI LANGUAGES CSharp)


include(CSharpUtilities)


add_subdirectory(${CMAKE_SOURCE_DIR}/SpleeterLib SpleeterLib)


set(SOURCE_DIR ${CMAKE_SOURCE_DIR})


add_executable(SpleeterUI
    ${SOURCE_DIR}/SpleeterUI/App.xaml.cs
    ${SOURCE_DIR}/SpleeterUI/AssemblyInfo.cs
    ${SOURCE_DIR}/SpleeterUI/MainWindow.xaml.cs
    ${SOURCE_DIR}/SpleeterUI/App.xaml
    ${SOURCE_DIR}/SpleeterUI/MainWindow.xaml
    ${SOURCE_DIR}/SpleeterUI/App.config
    
)

set(APP_XAML_PATH "${SOURCE_DIR}/SpleeterUI/App.xaml")
set_property(SOURCE ${APP_XAML_PATH} PROPERTY VS_XAML_TYPE "ApplicationDefinition")
SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY VS_PACKAGE_REFERENCES "Serilog_2.9.0;Serilog.Sinks.Console_3.1.1")


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



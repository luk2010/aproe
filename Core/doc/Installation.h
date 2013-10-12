////////////////////////////////////////////////////////////
/**
    @file Installation.h
    @brief Installation procedure.
    @ingroup Documentation
**/
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/**
    @page Installation Installation

    ### Prerequisites

    If you do not have <a href="http://industriousone.com/premake">Premake4</a> installed on your system,
    you must have it to generate project files.

    There is a correct Linux premake4 executable in the Core/extra directory, that you can use to generate the
    files. So if you do not have it, just type in a console in the Core/extra directory :
    @code
    sudo sh install_premake4.sh
    @endcode

    The script file 'install_premake4.sh' will copy the premake4 executable in your bin directory, allowing you
    to use it everywhere.

    @note See extra/README for more details.

    ### Generating project files

    You should choose the correct project files depending on what you want to do. If you only want to build ther sources,
    just use
    @code
    premake4 [options] gmake
    @endcode

    This will generate a simple make / make install procedure that you will be able to use (you must have a valid gcc installation
    though) .

    ### Options

    There are several options you can use to generate the files. Here are a basic list :

    - --double-real : Set the Real type to double instead of float.
    - --double-angle : Set the angle_t type to double instead of float.

    @note Real and angle_t types should have the same base type for conversion.

    - --with-all : Set every '--with-*' options.
    - --with-exceptions : Compile with exceptions throwing, but only in debug mode.
    - --with-exceptassert : Compile with an assertion function that throws exceptions. The default behaviour is to print a message.
    - --with-memorytracker : Compile with a memory tracker, only in debug mode.

    - --threadsapi : You can choose to compile directly with pthread ("--threadsapi=pthread") or with a plugined api. Default value is
    pthread.

    ### Using the binaries

    You will have libraries in the bin/ directory, depending on the configuration you made. Just link your program to the library (wich must
    be in the same directory as the program) and enjoy :) !
**/
////////////////////////////////////////////////////////////

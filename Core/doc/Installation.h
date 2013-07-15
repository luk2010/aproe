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

    @section Downloading Downloading the sources

    First, open a fucking console. Then, type the following :

    @code{.sh}
    git clone git://github.com/luk2010/aproe.git aproe
    cd aproe
    @endcode

    @section Building Building the sources

    Then, ou must have premake 4.5 installed. If not, please
    install it in order to build the sources.

    @code{.sh}
    premake4 gmake
    cd projects
    make
    @endcode

    And that's all ! You should see binaries under the bin/ directory
    You can use the config argu of make to build debug or release
    configuration; i.e.

    @code{.sh}
    make config=debug
    make config=release
    @endcode

    By default config=release is used.
**/
////////////////////////////////////////////////////////////

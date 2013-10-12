////////////////////////////////////////////////////////////
/**
    @file MainPage.h
    @brief Main Page of the documentation.
    @ingroup Documentation
**/
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/**
    @mainpage Home Page

    @section Introduction

    Atlanti's Project Engine is a free Open-Source Game Engine  that provide full-featured plugin system. It aims to be
    a complete game solution, but it is still in development.

    @section Downloads

    You can download the latest source of the Engine on our Github repository.
    See <a href="https://github.com/luk2010/aproe">GitHub</a> for more informations or the \link Downloading \endlink page.

    @section Cleaning

    Just run @code premake4 clean @endcode to clean every unused files. You will have to re-run the initial premake4
    script to get the makefiles again.
    'html' folder created by Doxygen isn't destroyed during cleaning, so you'll have to remove it manually.

    @note If you generate Codeblocks project files, 'core.layout' file won't be destroyed because it was not made by the
    premake process.

    @section Works Working on the sources

    You can work on the source simply by creating the IDE's files you like ( as 'premake4 codeblocks' for
    example ) and then work on the source. Think to clean your folder before any push.

    @section Documentation

    You can build the doc if you have doxygen. Simply run doxygen in this directory. Documentation will output
    by default in the 'html' directory.
    Then open the 'index.html' file in the 'html' directory with your favorite browser.
**/
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/* Modules used in the engine. */
/**
    @defgroup Maths Maths
    @addtogroup Maths
    @brief Reroups every Maths-related class.

    @defgroup Utils Utility
    @addtogroup Utils
    @brief Regroups every class that can be used in every context, and
    hasn't any dependancy.

    @defgroup Global Global

    @defgroup Rendering Rendering
    @addtogroup Rendering
    @brief Rendering related class.

    @defgroup Core Core
    @brief The Core group contains every class relatives to
    rendering and its base.

**/
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/** @page hello_world_example Hello World Example
**/
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/** @page example_page Examples

    Here is a list of current examples, by category.

    Example Name                   | Description
    ------------------------------ | -------------
    @subpage hello_world_example   | A basic tutorial to discover the beautiful "Hello World !" sentence in the console.
    @subpage minimal_code_example  | The minimal code for any application othat use the Main object.

    - - -
**/
////////////////////////////////////////////////////////////


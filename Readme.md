# Galmetry Sandobx

## Table of Contents
1. [Descritpion](##description)
1. [Package geometry - Examples](##geometry_examples)
1. [Package algorithm - Examples](##algo_examples)
1. [Package ui - Examples](##ui_examples)
1. [Run it!](##run)
1. [Collaboration](##collaboration)

## Description <a name="description"> </a>

Hi coders! My nickname is **Gallottino**. I'm working hard to build by my self a custom library to manage geometry objects (points, vertices, edges, polygons ect..).
The repository is divided in 3 major packages:
- **ui**: in this package there are all the UI object usefull to interact with the geometry sandbox. It has built with SFML library (version: 2.5.1) and the package is *"work in progress"*.
- **geometry**: in this package there are all the classes rapresenting all the geometry stuff. If you need to model some geometric data, you can pick a class from here. 
- **algorithm**: in this package i'll put all the algorithms related to **computational geometry** topic. For now, i have alredy impemeneted two algorith: The *monotone convex hull* process and the *Belly-Ortmann Algorithm* with a custom interpretation of status BTS.

I'm studing this topic on the book **"Computational Geometry: Algorithms and Applications"** by *Mark de Berg, Otfried Cheong, Marc van Kreveld and Mark Overmars*.

## Examples - geometry package <a name="geometry_examples"> </a>
1. Create a point:

```
#include <geometry/Geometry.hpp>
...

geometry::Point2D point(20.0,50.0);
std::cout << "( " << point.x, "," << point.y << ")" << std::endl; //output: (20,50)
```

## Examples - algorithm package <a name="algo_examples"> </a>
I still need to write them. Sorry :)

## Examples - ui package <a name="ui_examples"> </a>
Same as above. X)

## Run it! <a name="run"> </a>
The project could be built with CMake. The only dependence is SFML: it is important, as said in the documentation, to use the version of SFML related to the version of compiler. I'm using **GCC MinGW 7.3.0 (SEH) - 64 bit**, but you can customize your enviroment as you like.

 In the *CMakeLists.txt* you could find a instruction like this:

```
set(SFML_DIR "C:/development_tools/SFML-2.5.1/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "C:/development_tools/SFML-2.5.1/include/")
link_directories("C:/development_tools/SFML-2.5.1/lib/")
```
Donwload the correct version of SFML in the directory that you like, but be careful to change in the previous rows the path in which you install the library.

I'm thinking to separete the geometry package from the graphic one. In future you could build only the package that you want to use.

## Collaboration <a name="collaboration"> </a>
I developed all these packages in my free time. I would like to create a professional enviroment to study or to develop custom algorithms about 2D Graphics. Do you want to collaborate with me? I appreciate any kind of help. Feel free to open a *pull request*. 
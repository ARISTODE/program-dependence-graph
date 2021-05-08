# CMake support for bzip2

[![Build status](https://ci.appveyor.com/api/projects/status/4krhvh7hhl41fyvh?svg=true)](https://ci.appveyor.com/project/sergiud/bzip2)

This repository implementes native CMake support for bzip2 with minor
modifications to original sources. A package configuration for easy integration
in own projects is also provided.

## Compilation

To compile bzip2, create a build directory and run
```bash
$ cmake <build-dir>
```
in the build directory to generate project files using the default CMake generator.

## Using bzip2 in own projects

This repository add a package configuration for bzip2 allowing to integrate
bzip2 in own projects. For this purpose, the package configuration exposes an
imported target named `BZip2::BZip2` that other targets can link to.

To consume the bzip2 package configuration, use the usual `find_package`
mechanism:
```cmake
find_package (BZip2 1.0.6 REQUIRED)

add_executable (myapp myapp.c)
target_link_libraries (myapp PRIVATE BZip2::BZip2)
```

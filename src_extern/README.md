EXTERNAL SOURCES
================

This directory contains external sources, which are used by the project.
For ease of use, they are in this repository, stripped of what is
not needed.

External sources should remain as unpatched as possible, outside the
projects own source.


gmock-1.7.0
-----------

License: BSD (http://opensource.org/licenses/BSD-3-Clause)

Homepage: https://code.google.com/p/googlemock/

Download: https://code.google.com/p/googlemock/downloads/detail?name=gmock-1.7.0.zip

Notess:
- Only the fused source
- Added a CMakeLists.txt file
- Added custom\_main.cpp
  - Supports output in CppUnit (XML) format in addition to the standard
    behaviour (JUnit format).


# WiiDevTemplate

Make sure you have installed DevkitPro-PPC either locally (see [here](https://devkitpro.org/wiki/Getting_Started)) or using Docker and pulling the correct image.

As the IDE, I recommend using CLion.
CLion should use CMake as the build system.

Add a CMake profile, choose as Toolchain either Default (if local install) or Docker.
Under Configurations, add a CMake Application:
Target: Template.elf
Executable: here you can point to either python3 or bash, depending on your autorun script
Program arguments and Working directory: depend on your script needs

To change the project's name, simply rename "Template" in "project(Template CXX C ASM)" inside of CMakeLists.txt .

If using Docker, create a Docker entry under Settings->Build,Execution,Deployment->Docker, \
then add a Docker entry in Settings->Build,Execution,Deployment->Toolchains and choose the correct image;\
use this toolchain inside of the CMake setup.

# Confectionery
Confectionery is the best build configuration system for extensively configurable applications. It is extremely lightweight. It is just one C file so you could, in theory, run gcc main.c and get Confectionery, but there are benefits that come with compiling it with the Makefile method such as a test suite (one test is known to fail), installation with make install, and being able to customize the Makefile if you want to.
# Installing Confectionery
## Dependencies
Confectionery depends on make. Yes, that's literally it. I hope your system has make already installed!
## Building
Building Confectionery is an extremely easy two-step process.
### Step 1
cd into the Confectionery directory.
``` shell
cd /path/to/Confectionery
```
### Step 2
Run make.
``` shell
make
```
### Step 3 (optional)
Run make check. This runs the test suite. One test is known to fail.
``` shell
make check
```
# Using Confectionery
There are two ways to use Confectionery. You can either build your own configuration and run it or use a preset.
## Method 1 - Building your own configuration
Building your own Confectionery configuration is almost as easy as installing Confectionery. First, you need to create the configuration options. Then, you need to create a configuration file in the same directory as the Makefile and set the configuration options to what you desire. Finally, you need to run Confectionery with your configuration file.
### Step 1 - Creating the configuration options
To create the configuration options, you need to add #ifdef and #endif to the lines of code that will be disabled or enabled by a configuration option.
``` C
#ifdef OPTION_NAME
 /* Insert code here */
#endif
```
If the options affect the Makefile instead of a C file, you must add this instead.
``` Makefile
ifeq ($(OPTION_NAME),1)
CFLAGS += /* Insert custom CFLAGS here */
endif
```
Regardless, you must add this to your Makefile so make sees the options.
``` Makefile
CFLAGS += -DOPTION_NAME=$(OPTION_NAME)
```
### Step 2 - Creating the configuration file
Open your text editor of choice to whatever you want to name your configuration file. Then, add all of your configuration options and set them to on or off in this format:
``` Confectionery
foo is on
bar is off
baz is off
qux is on
```
### Step 3 - Using the configuration
To generate a configure file, run this command.
``` shell
confectionery build configuration
```
This will generate a configure file. You can customize said configure file for your project to check for dependencies and distribute it without the original config if you want to hide your configuration and make users edit the Confectionery output files themselves or you could disclose dependencies from the start. I definitely prefer the latter. Back to the main topic, to run the configure script, you just need to run ./configure like most make projects.
### Step 4 - Building the application (for anyone wondering)
To make the application, you just need to run the holy trinity of make commands:
``` shell
make
make check
make install
```
If your project doesn't have a test suite, you can exclude the make check step. And if your project is using Ninja, all you have to run is the ninja command. (Keep in mind that I haven't tested Confectionery with Ninja yet)
## Method 2 - Using a preset
Using a preset is the easiest method to build a Confectionery application. If you haven't already created any presets, create a preset file and add your preset(s). Then, select a preset and run Confectionery on it. Finally, build your project with the preset.
### Step 1 - Creating the preset file (if one doesn't exist)
Before creating a preset file, repeat the instructions documented in step 1 of method 1. Now that all of your #ifdefs and Makefile options are set up, open your text editor of choice to whatever you want to name your preset file. Then, add your presets in this format.
``` Confectionery
[presetname]
foo is on
bar is off
baz is off
qux is on
```
Repeat for every other preset you want to add. You cannot set Makefile flags for individual presets unless you add that to the configure script.
### Step 2 - Using the preset
Run this command to generate a basic configure script.
``` shell
confectionery build presets presetname
```
### Step 3 - Building the application (for anyone wondering)
To make the application, you just need to run the holy trinity of make commands:
``` shell
make
make check
make install
```
If your project doesn't have a test suite, you can exclude the make check step. And if your project is using Ninja, all you have to run is the ninja command.
# Why Confectionery?
Confectionery is the ideal build configuration system for:
1. Extensively configurable applications where you would spend hours configuring them anyway.
2. Applications currently using Meson.
3. Applications used in embedded systems that are currently using CMake.

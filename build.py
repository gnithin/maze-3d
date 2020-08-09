# Run with: python3 build.py
import os
import platform
import sys

IS_DEBUG_MODE = False
if len(sys.argv) > 1:
    for arg in sys.argv[1:]:
        if arg == "--debug":
            IS_DEBUG_MODE = True

# (1)==================== COMMON CONFIGURATION OPTIONS ======================= #
COMPILER="clang++ -std=c++14"   # The compiler we want to use 
                                #(You may try g++ if you have trouble)
SOURCE="./src/*.cpp"    # Where the source code lives
EXECUTABLE="lab"        # Name of the final executable
# ======================= COMMON CONFIGURATION OPTIONS ======================= #

# (2)=================== Platform specific configuration ===================== #
# For each platform we need to set the following items
ARGUMENTS=""            # Arguments needed for our program (Add others as you see fit)
INCLUDE_DIR=""          # Which directories do we want to include.
LIBRARIES=""            # What libraries do we want to include

if platform.system()=="Linux":
    ARGUMENTS="-D LINUX" # -D is a #define sent to preprocessor
    INCLUDE_DIR="-I./include/ -I./thirdparty/glm/"
    LIBRARIES="-lSDL2 -ldl"
elif platform.system()=="Darwin":
    ARGUMENTS="-D MAC" # -D is a #define sent to the preprocessor.
    INCLUDE_DIR="-I./include/ -I/Library/Frameworks/SDL2.framework/Headers -I./thirdparty/old/glm"
    LIBRARIES="-F/Library/Frameworks -framework SDL2"
elif platform.system()=="Windows":
    COMPILER="g++ -std=c++14" # Note we use g++ here as it is more likely what you have
    ARGUMENTS="-D MINGW -std=c++14 -static-libgcc -static-libstdc++" 
    INCLUDE_DIR="-I./include/ -I./thirdparty/old/glm/"
    EXECUTABLE="lab.exe"
    LIBRARIES="-lmingw32 -lSDL2main -lSDL2 -mwindows"

if IS_DEBUG_MODE:
    ARGUMENTS += " -D MAZE_DEBUG_MODE"
# (2)=================== Platform specific configuration ===================== #

# (3)====================== Building the Executable ========================== #
# Build a string of our compile commands that we run in the terminal
compileString=COMPILER+" "+ARGUMENTS+" -o "+EXECUTABLE+" "+" "+INCLUDE_DIR+" "+SOURCE+" "+LIBRARIES
# Print out the compile string
# This is the command you can type
print("============v (Command running on terminal) v===========================")
print("Compilng on: "+platform.system())
print(compileString)
print("========================================================================")
# Run our command
ret = os.system(compileString)
exit(1 if ret != 0 else 0)
# ========================= Building the Executable ========================== #


# Why am I not using Make?
# 1.)   I want total control over the system. 
#       Occassionally I want to have some logic
#       in my compilation process (like searching for missing files).
# 2.)   Realistically our projects are 'small' enough 
#       this will not matter.
# 3.)   Feel free to implement your own make files or autogenerate it from this
#       script
# 4.)   It is handy to know Python


# For VIM users, you can generate a .clang_complete file to help
# with auto complete if you like.
# See more: https://vimawesome.com/plugin/clang-complete
def make_clang_complete_file():
    fp = open(".clang_complete","w+")
    fp.write(ARGUMENTS+"\n")
    includes = INCLUDE_DIR.split(" ")
    for i in includes:
        fp.write(i+"\n")
    fp.close()

# Uncomment the line below to generate a .clang_complete file in the root
# directory.
make_clang_complete_file()

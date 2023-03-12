import os
import shutil
from helpers import architectures, architecture_aliases, is_vanilla_clang, using_clang

EnsureSConsVersion(3, 0, 0)
EnsurePythonVersion(3, 6)

customs = ["custom.py"]
opts = Variables(customs, ARGUMENTS)
opts.Add(BoolVariable("lto", "Link-time optimization", False))
opts.Add(EnumVariable("platform", "Target platform", "native_sdl",
                      ("linux_sdl", "windows_sdl", "native_sdl",
                       "linux_term", "windows_term", "native_term",
                       "web", "tools")))
opts.Add(EnumVariable("arch", "CPU architecture", "auto",
         ["auto"] + architectures, architecture_aliases))
opts.Add(
    EnumVariable(
        "optimize", "Optimization level", "speed_trace", (
            "none", "custom", "debug", "speed", "speed_trace", "size")
    )
)
opts.Add(BoolVariable("clang", "Use clang", False))

opts.Add(BoolVariable("tests", "Build tests", False))

common_flags = ["-pipe", "-Wall", "-Wextra", "-pedantic"]

env = Environment(CCFLAGS=common_flags, LINKFLAGS=common_flags,
                  CPPPATH=['src', 'build', 'thirdparty'])
opts.Update(env)
env.msvc = False

if env.msvc:
    if env["optimize"] == "speed" or env["optimize"] == "speed_trace":
        env.Append(CCFLAGS=["/O2"])
        env.Append(LINKFLAGS=["/OPT:REF"])
    elif env["optimize"] == "size":
        env.Append(CCFLAGS=["/O1"])
        env.Append(LINKFLAGS=["/OPT:REF"])
    elif env["optimize"] == "debug" or env["optimize"] == "none":
        env.Append(CCFLAGS=["/Od"])
else:
    if using_clang(env) and not is_vanilla_clang(env):
        env.Append(LINKFLAGS=["-Wl,-S", "-Wl,-x", "-Wl,-dead_strip"])
    else:
        env.Append(LINKFLAGS=["-s"])

    if env["optimize"] == "speed":
        env.Append(CCFLAGS=["-O3"])
    elif env["optimize"] == "speed_trace":
        env.Append(CCFLAGS=["-O2"])
    elif env["optimize"] == "size":
        env.Append(CCFLAGS=["-Os"])
    elif env["optimize"] == "debug":
        env.Append(CCFLAGS=["-Og"])
    elif env["optimize"] == "none":
        env.Append(CCFLAGS=["-O0"])

if not env.msvc:
    env.Prepend(CFLAGS=["-std=gnu11"])
    env.Prepend(CXXFLAGS=["-std=gnu++17"])
else:
    env.Prepend(CCFLAGS=["/std:c++17"])

if env["lto"]:
    if not env.msvc:
        env.Prepend(CFLAGS=["-flto"])
        env.Prepend(CXXFLAGS=["-flto"])
        env.Prepend(LINKFLAGS=["-flto"])
    else:
        env.Prepend(CCFLAGS=["/GL"])
        env.Prepend(LINKFLAGS=["/LTCG"])

if env["clang"]:
    clang_options = {
        "CC": "clang",
        "CXX": "clang++",
        "LD": "lld",
        "AR": "llvm-ar",
        "STRIP": "llvm-strip",
        "RANLIB": "llvm-ranlib"
    }
    env.Replace(**clang_options)

if env["platform"] == "web":
    emcc_options = {
        "CC": "emcc",
        "CXX": "em++",
        "LD": "emcc",
        "AR": "emar",
        "STRIP": "emstrip",
        "RANLIB": "emranlib"
    }
    env.Replace(**emcc_options)

env_tool = env.Clone()
env_app = env.Clone()

if not env["platform"] == "web":
    env_tool.Program(target='build/tools/png2c', source='tools/png2c.c',
                     LINKFLAGS='$LINKFLAGS -lm')
    env_tool.Program(target='build/tools/obj2c', source='tools/obj2c.c',
                     LINKFLAGS='$LINKFLAGS -lm')
    env_tool.Program(target='build/tools/font2c', source='tools/font2c.c', CCFLAGS='$CCFLAGS -I/usr/include/freetype2 -I/usr/include/libpng16 -L/usr/local/lib',
                     LINKFLAGS='$LINKFLAGS -lm -I/usr/include/freetype2 -I/usr/include/libpng16 -L/usr/local/lib -lfreetype')

if not os.path.exists("build"):
    os.mkdir("build")
if not os.path.exists("build/assets"):
    os.mkdir("build/assets")

os.system("./build/tools/png2c -n tsodinPog -o ./build/assets/tsodinPog.c ./assets/tsodinPog.png")
os.system(
    "./build/tools/png2c -n Lena_112 -o ./build/assets/Lena_112.c ./assets/Lena_112.png")
os.system("./build/tools/png2c -n tsodinCup -o ./build/assets/tsodinCup.c ./assets/tsodinCup.png")
os.system(
    "./build/tools/png2c -n oldstone -o ./build/assets/oldstone.c ./assets/oldstone.png")
os.system("./build/tools/png2c -n lavastone -o ./build/assets/lavastone.c ./assets/lavastone.png")
os.system("./build/tools/obj2c -o ./build/assets/tsodinCupLowPoly.c ./assets/tsodinCupLowPoly.obj")
os.system(
    "./build/tools/obj2c -s 0.40 -o ./build/assets/utahTeapot.c ./assets/utahTeapot.obj")
os.system("./build/tools/font2c -o ./build/assets/testFont.c -n test_font ./html/fonts/LibreBaskerville-Regular.ttf")

if env["tests"]:
    env_tool.Program(target='build/test', source='test.c',
                     LINKFLAGS='$LINKFLAGS -lm -fsanitize=memory', CCFLAGS='$CCFLAGS -fsanitize=memory')

suffix = "." + env["platform"]
suffix += "." + env["arch"]

env_app["OBJSUFFIX"] = suffix + env_app["OBJSUFFIX"]

if os.name == "nt":
    env_app["LIBSUFFIXES"] += [env_app["LIBSUFFIX"]]
else:
    env_app["LIBSUFFIXES"] += [env_app["LIBSUFFIX"], env_app["SHLIBSUFFIX"]]
env_app["LIBSUFFIX"] = suffix + env_app["LIBSUFFIX"]
env_app["SHLIBSUFFIX"] = suffix + env_app["SHLIBSUFFIX"]


def get_files(path):
    for file in os.listdir(path):
        if os.path.isfile(os.path.join(path, file)):
            if file.endswith('.c'):
                yield file


if not env["platform"] == "tools":
    if env["platform"] == "native_sdl":
        for file in get_files("demos"):
            env_app.Program(target='build/demos/' + file.replace('.c', '') + '.sdl', source=(os.path.join("demos", file)),
                            LINKFLAGS='$LINKFLAGS -lm -lSDL2', CCFLAGS='$CCFLAGS -fno-builtin -DVC_PLATFORM=VC_SDL_PLATFORM')

    elif env["platform"] == "native_term":
        for file in get_files("demos"):
            env_app.Program(target='build/demos/' + file.replace('.c', '') + '.term', source=(os.path.join("demos", file)),
                            LINKFLAGS='$LINKFLAGS -lm', CCFLAGS='$CCFLAGS -fno-builtin -DVC_PLATFORM=VC_TERM_PLATFORM -D_XOPEN_SOURCE=600')

    elif env["platform"] == "web":
        os.environ["EMSCRIPTEN_ROOT"] = os.path.dirname(WhereIs("emcc"))
        env_app.Tool("emscripten", toolpath=[os.path.dirname(
            WhereIs("emcc")) + "/tools/scons/site_scons/site_tools/emscripten"])
        for file in get_files("demos"):
            env_app.Program(target='build/demos/' + file.replace('.c', '') + '.wasm', source=(os.path.join("demos", file)),
                            LINKFLAGS='$LINKFLAGS -Wl,--no-entry -Wl,--export=vc_render -Wl,--export=__heap_base -lm -lSDL2 -sFILESYSTEM=0 -sUSE_SDL=2 -sMALLOC=emmalloc -sALLOW_MEMORY_GROWTH -sLEGACY_GL_EMULATION', CCFLAGS='$CCFLAGS -fno-builtin --closure=1 --no-standard-libraries -DVC_PLATFORM=VC_WASM_PLATFORM')
            shutil.copyfile('build/demos/' + file.replace('.c', '') + '.wasm', 'html/wasm/' + file.replace('.c', '') + '.wasm')

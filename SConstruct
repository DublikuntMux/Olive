#!/usr/bin/env python

import os
import platform
import re
import shutil
import subprocess
import sys

EnsureSConsVersion(3, 0, 0)
EnsurePythonVersion(3, 6)

architectures = ["x86_32", "x86_64", "arm32", "arm64"]
architecture_aliases = {
    "x86": "x86_32",
    "x64": "x86_64",
    "amd64": "x86_64",
}


def detect_arch():
    host_machine = platform.machine().lower()
    if host_machine in architectures:
        return host_machine
    elif host_machine in architecture_aliases.keys():
        return architecture_aliases[host_machine]
    elif "86" in host_machine:
        return "x86_32"
    else:
        print("Unsupported CPU architecture: " + host_machine)
        print("Falling back to x86_64.")
        return "x86_64"


def is_vanilla_clang(env):
    if not using_clang(env):
        return False
    try:
        version = subprocess.check_output(
            [env.subst(env["CXX"]), "--version"]).strip().decode("utf-8")
    except (subprocess.CalledProcessError, OSError):
        print("Couldn't parse CXX environment variable to infer compiler version.")
        return False
    return not version.startswith("Apple")


def get_compiler_version(env):
    if not env.msvc:
        try:
            version = subprocess.check_output(
                [env.subst(env["CXX"]), "--version"]).strip().decode("utf-8")
        except (subprocess.CalledProcessError, OSError):
            print("Couldn't parse CXX environment variable to infer compiler version.")
            return None
    else:  # TODO: Implement for MSVC
        return None
    match = re.search(
        "(?:(?<=version )|(?<=\) )|(?<=^))"
        "(?P<major>\d+)"
        "(?:\.(?P<minor>\d*))?"
        "(?:\.(?P<patch>\d*))?"
        "(?:-(?P<metadata1>[0-9a-zA-Z-]*))?"
        "(?:\+(?P<metadata2>[0-9a-zA-Z-]*))?"
        "(?: (?P<date>[0-9]{8}|[0-9]{6})(?![0-9a-zA-Z]))?",
        version,
    )
    if match is not None:
        return match.groupdict()
    else:
        return None


def using_clang(env):
    return "clang" in os.path.basename(env["CC"])


customs = ["custom.py"]
opts = Variables(customs, ARGUMENTS)
opts.Add(BoolVariable("lto", "Link-time optimization", False))
opts.Add(EnumVariable("target", "Target for build", "native_sdl", ("linux_sdl", "windows_sdl",
         "native_sdl", "linux_term", "windows_term", "native_term", "web", "tools", "prepare", "tests")))
opts.Add(EnumVariable("arch", "CPU architecture", "auto",
         ["auto"] + architectures, architecture_aliases))
opts.Add(EnumVariable("optimize", "Optimization level", "speed_trace",
         ("none", "custom", "debug", "speed", "speed_trace", "size")))
opts.Add(BoolVariable("clang", "Use clang", False))

common_flags = ["-pipe", "-Wall", "-Wextra", "-pedantic"]
env = Environment(CCFLAGS=common_flags, LINKFLAGS=common_flags, CPPPATH=[
                  'src', 'build', 'thirdparty', 'include'], COMPILATIONDB_USE_ABSPATH=True)
env.Tool('compilation_db')
env.CompilationDatabase()
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

    if env["target"] == "web":
        env.Append(CCFLAGS=["-Os"])
    else:
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

if env["target"] == "web":
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

if not env["target"] == "prepare":
    def get_source(path):
        for file in os.listdir(path):
            if os.path.isfile(os.path.join(path, file)):
                if file.endswith('.c'):
                    yield file
    lib_src = []
    list_dir = ["src", "src/base", "src/math"]

    for dir in list_dir:
        for file in get_source(dir):
            lib_src.append(os.path.join(dir, file))

    if not env["target"] == "web":
        if os.path.exists("build/libs/libolive.so"):
            os.remove("build/libs/libolive.so")
        if env["target"] == "native_sdl" or "native_term":
            env_app.StaticLibrary(
                target='build/libs/olive', source=lib_src, CCFLAGS='$CCFLAGS -march=native')
        else:
            env_app.StaticLibrary(target='build/libs/olive', source=lib_src)
    else:
        if os.path.exists("build/libs/libolive.a"):
            os.remove("build/libs/libolive.a")
        os.environ["EMSCRIPTEN_ROOT"] = os.path.dirname(WhereIs("emcc"))
        env_app.Tool("emscripten", toolpath=[os.path.dirname(
            WhereIs("emcc")) + "/tools/scons/site_scons/site_tools/emscripten"])
        env_app.SharedLibrary(target='build/libs/olive',
                              source=lib_src, LIBPATH='build/libs')

if env["target"] == "tests":
    env_tool.Program(target='build/test', source='test.c',
                     LIBPATH='build/libs', LIBS=['m', 'olive'])

elif env["target"] == "tools":
    env_tool.Program(target='build/tools/png2c',
                     source='tools/png2c.c', LIBS=['m'])
    env_tool.Program(target='build/tools/obj2c',
                     source='tools/obj2c.c')
    env_tool.Program(target='build/tools/font2c', source='tools/font2c.c', CCFLAGS='$CCFLAGS -I/usr/include/freetype2 -I/usr/include/libpng16',
                     LINKFLAGS='$LINKFLAGS -I/usr/include/freetype2 -I/usr/include/libpng16', LIBS=['freetype'], LIBPATH=['/usr/local/lib'])

elif env["target"] == "prepare":
    if not os.path.exists("build"):
        os.mkdir("build")
    if not os.path.exists("build/assets"):
        os.mkdir("build/assets")

    if os.name == 'nt':
        os.system(
            "./build/tools/png2c.exe -n tsodinPog -o ./build/assets/tsodinPog.h ./assets/tsodinPog.png")
        os.system(
            "./build/tools/png2c.exe -n Lena_112 -o ./build/assets/Lena_112.h ./assets/Lena_112.png")
        os.system(
            "./build/tools/png2c.exe -n tsodinCup -o ./build/assets/tsodinCup.h ./assets/tsodinCup.png")
        os.system(
            "./build/tools/png2c.exe -n oldstone -o ./build/assets/oldstone.h ./assets/oldstone.png")
        os.system(
            "./build/tools/png2c.exe -n lavastone -o ./build/assets/lavastone.h ./assets/lavastone.png")
        os.system(
            "./build/tools/obj2c.exe -o ./build/assets/tsodinCupLowPoly.h ./assets/tsodinCupLowPoly.obj")
        os.system(
            "./build/tools/obj2c.exe -s 0.40 -o ./build/assets/utahTeapot.h ./assets/utahTeapot.obj")
        os.system(
            "./build/tools/font2c -o ./build/assets/testFont.h -n test_font ./html/fonts/LibreBaskerville-Regular.ttf")
    else:
        os.system(
            "./build/tools/png2c -n tsodinPog -o ./build/assets/tsodinPog.h ./assets/tsodinPog.png")
        os.system(
            "./build/tools/png2c -n Lena_112 -o ./build/assets/Lena_112.h ./assets/Lena_112.png")
        os.system(
            "./build/tools/png2c -n tsodinCup -o ./build/assets/tsodinCup.h ./assets/tsodinCup.png")
        os.system(
            "./build/tools/png2c -n oldstone -o ./build/assets/oldstone.h ./assets/oldstone.png")
        os.system(
            "./build/tools/png2c -n lavastone -o ./build/assets/lavastone.h ./assets/lavastone.png")
        os.system(
            "./build/tools/obj2c -o ./build/assets/tsodinCupLowPoly.h ./assets/tsodinCupLowPoly.obj")
        os.system(
            "./build/tools/obj2c -s 0.40 -o ./build/assets/utahTeapot.h ./assets/utahTeapot.obj")
        os.system(
            "./build/tools/font2c -o ./build/assets/testFont.h -n test_font ./html/fonts/LibreBaskerville-Regular.ttf")

elif env["target"] == "native_sdl":
    for file in get_source("demos"):
        env_app.Program(target='build/demos/' + file.replace('.c', '') + '.sdl', source=(os.path.join("demos", file)), LIBPATH='build/libs',
                        LIBS=['m', 'SDL2', 'olive'], CCFLAGS='$CCFLAGS -fno-builtin -DVC_PLATFORM=VC_SDL_PLATFORM -march=native')

elif env["target"] == "linux_sdl":
    host_is_64_bit = sys.maxsize > 2**32
    if host_is_64_bit and env["arch"] == "x86_32":
        env.Append(CCFLAGS=["-m32"])
        env.Append(LINKFLAGS=["-m32", "-L/usr/lib/i386-linux-gnu"])
    elif not host_is_64_bit and env["arch"] == "x86_64":
        env.Append(CCFLAGS=["-m64"])
        env.Append(LINKFLAGS=["-m64", "-L/usr/lib/i686-linux-gnu"])

    for file in get_source("demos"):
        env_app.Program(target='build/demos/' + file.replace('.c', '') + '.sdl', source=(os.path.join("demos", file)),
                        LIBPATH='build/libs', LIBS=['m', 'SDL2', 'olive'], CCFLAGS='$CCFLAGS -fno-builtin -DVC_PLATFORM=VC_SDL_PLATFORM')

elif env["target"] == "windows_sdl":
    msvc_arch_aliases = {"x86_32": "x86", "arm32": "arm"}
    if env["arch"] in msvc_arch_aliases.keys():
        env["TARGET_ARCH"] = msvc_arch_aliases[env["arch"]]
    else:
        env["TARGET_ARCH"] = env["arch"]

    for file in get_source("demos"):
        env_app.Program(target='build/demos/' + file.replace('.c', '') + '.sdl', source=(os.path.join("demos", file)),
                        LIBPATH='build/libs', LIBS=['m', 'SDL2', 'olive'], CCFLAGS='$CCFLAGS /fno-builtin /DVC_PLATFORM=VC_SDL_PLATFORM')

elif env["target"] == "native_term":
    for file in get_source("demos"):
        env_app.Program(target='build/demos/' + file.replace('.c', '') + '.term', source=(os.path.join("demos", file)), LIBPATH='build/libs',
                        LIBS=['m', 'olive'], CCFLAGS='$CCFLAGS -fno-builtin -DVC_PLATFORM=VC_TERM_PLATFORM -D_XOPEN_SOURCE=600 -march=native')

elif env["target"] == "linux_term":
    host_is_64_bit = sys.maxsize > 2**32
    if host_is_64_bit and env["arch"] == "x86_32":
        env.Append(CCFLAGS=["-m32"])
        env.Append(LINKFLAGS=["-m32", "-L/usr/lib/i386-linux-gnu"])
    elif not host_is_64_bit and env["arch"] == "x86_64":
        env.Append(CCFLAGS=["-m64"])
        env.Append(LINKFLAGS=["-m64", "-L/usr/lib/i686-linux-gnu"])

    for file in get_source("demos"):
        env_app.Program(target='build/demos/' + file.replace('.c', '') + '.term', source=(os.path.join("demos", file)),
                        LIBPATH='build/libs', LIBS=['m', 'olive'], CCFLAGS='$CCFLAGS -fno-builtin -DVC_PLATFORM=VC_TERM_PLATFORM -D_XOPEN_SOURCE=600')

elif env["target"] == "windows_term":
    msvc_arch_aliases = {"x86_32": "x86", "arm32": "arm"}
    if env["arch"] in msvc_arch_aliases.keys():
        env["TARGET_ARCH"] = msvc_arch_aliases[env["arch"]]
    else:
        env["TARGET_ARCH"] = env["arch"]

    for file in get_source("demos"):
        env_app.Program(target='build/demos/' + file.replace('.c', '') + '.term', source=(os.path.join("demos", file)),
                        LIBPATH='build/libs', LIBS=['m', 'olive'], CCFLAGS='$CCFLAGS /fno-builtin /DVC_PLATFORM=VC_TERM_PLATFORM /D_XOPEN_SOURCE=600')

elif env["target"] == "web":
    os.environ["EMSCRIPTEN_ROOT"] = os.path.dirname(WhereIs("emcc"))
    env_app.Tool("emscripten", toolpath=[os.path.dirname(
        WhereIs("emcc")) + "/tools/scons/site_scons/site_tools/emscripten"])
    for file in get_source("demos"):
        env_app.Program(target='build/demos/' + file.replace('.c', '') + '.wasm', source=(os.path.join("demos", file)), LIBPATH='build/libs', LIBS=[
                        'm', 'SDL', 'olive'], LINKFLAGS='$LINKFLAGS -Wl,--no-entry -Wl,--export=vc_render -Wl,--export=__heap_base -sFILESYSTEM=0 -sUSE_SDL=2 -sMALLOC=emmalloc -sALLOW_MEMORY_GROWTH -sLEGACY_GL_EMULATION', CCFLAGS='$CCFLAGS -fno-builtin --closure=1 --no-standard-libraries -DVC_PLATFORM=VC_WASM_PLATFORM')

        if os.path.exists('build/demos/' + file.replace('.c', '') + '.wasm'):
            shutil.copyfile('build/demos/' + file.replace('.c', '') +
                            '.wasm', 'html/wasm/' + file.replace('.c', '') + '.wasm')

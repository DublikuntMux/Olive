import os
import platform
import re
import subprocess

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
    """
    Returns an array of version numbers as ints: [major, minor, patch].
    The return array should have at least two values (major, minor).
    """
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

import subprocess
from distutils.core import setup, Extension


def pkgconfig(flag, package):
    p = subprocess.Popen(['pkg-config', flag, package],
                             stdout=subprocess.PIPE)
    return p.stdout.read().split()

mod = Extension('bulletphysics',
                    sources = ['src/bulletphysics.cpp', 'src/DbvtBroadphase.cpp'],
                    extra_compile_args=pkgconfig('--cflags', 'bullet'),
                    extra_link_args=pkgconfig('--libs', 'bullet'))

setup(name = 'bulletphysics',
       version = '0.1',
       description = 'python wrapper for bulletphysics library',
       ext_modules = [mod])

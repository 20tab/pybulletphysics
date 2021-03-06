import subprocess
from distutils.core import setup, Extension


def pkgconfig(flag, package):
    p = subprocess.Popen(['pkg-config', flag, package],
                         stdout=subprocess.PIPE)
    return p.stdout.read().split()


mod = Extension('bulletphysics',
                sources=['src/bulletphysics.cpp',
                         'src/DbvtBroadphase.cpp',
                         'src/DefaultCollisionConfiguration.cpp',
                         'src/CollisionDispatcher.cpp',
                         'src/SequentialImpulseConstraintSolver.cpp',
                         'src/DiscreteDynamicsWorld.cpp',
                         'src/Vector3.cpp',
                         'src/Quaternion.cpp',
                         'src/CollisionShape.cpp',
                         'src/StaticPlaneShape.cpp',
                         'src/SphereShape.cpp',
                         'src/Transform.cpp',
                         'src/DefaultMotionState.cpp',
                         'src/RigidBodyConstructionInfo.cpp',
                         'src/RigidBody.cpp',
                         'src/BoxShape.cpp',
                         'src/PersistentManifold.cpp',
                         'src/VehicleTuning.cpp',
                         'src/WheelInfo.cpp',
                         'src/DefaultVehicleRaycaster.cpp',
                         'src/RaycastVehicle.cpp',
                         'src/CompoundShape.cpp',
                         'src/CylinderShape.cpp',
                ],
                extra_compile_args=pkgconfig('--cflags', 'bullet'),
                extra_link_args=pkgconfig('--libs', 'bullet'))

setup(
    name='bulletphysics',
    version='0.1',
    description='python wrapper for bulletphysics library',
    ext_modules=[mod],
    author='20tab S.r.l.',
    author_email='info@20tab.com',
    url='https://github.com/20tab/pybulletphysics',
    license='MIT License'
)

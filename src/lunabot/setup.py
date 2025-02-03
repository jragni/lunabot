from setuptools import setup

setup(
    name='lunabot',
    version='0.0.1',
    packages=['lunabot'],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + 'my_mixed_package']),
        ('share/' + 'lunabot', ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    author='Jhensen Ray Agni',
    author_email='jhensenrayagni@gmail.com',
    maintainer='Jhensen Ray Agni',
    maintainer_email='jhensenrayagni@gmail.com',
    description='A mixed C++ and Python ROS2 package',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
          "inference_node = lunabot.inference_node:main",
        ],
    },
)

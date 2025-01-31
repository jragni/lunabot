from setuptools import setup

setup(
    name='my_mixed_package',
    version='0.0.1',
    packages=['my_mixed_package'],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + 'my_mixed_package']),
        ('share/' + 'my_mixed_package', ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    author='Your Name',
    author_email='your@email.com',
    maintainer='Your Name',
    maintainer_email='your@email.com',
    description='A mixed C++ and Python ROS2 package',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        ],
    },
)

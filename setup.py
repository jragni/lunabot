from setuptools import find_packages, setup

package_name = 'lunabot'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='lunabot',
    maintainer_email='lunabot@todo.todo',
    description='Package for controlling the lunabot',
    license='APACHE 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'motor_node = lunabot.motor_node:main'
        ],
    },
)

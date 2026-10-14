from setuptools import find_packages
from setuptools import setup

setup(
    name='zfc_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('zfc_interfaces', 'zfc_interfaces.*')),
)

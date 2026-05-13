from setuptools import find_packages
from setuptools import setup

setup(
    name='charuco_detector_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('charuco_detector_interfaces', 'charuco_detector_interfaces.*')),
)

from distutils.core import setup, Extension

module = Extension('demangler', sources=['demangle.cpp'])
setup(name="Demangler",
      version="0.2",
      description="A demangler package for gcc 3.x and gcc 4.x",
      author="Rakholiya Jenish",
      author_email="rakholiyajenish.07@gmail.com",
      long_description=".. image:: https://travis-ci.org/P4N74/demangler.svg?branch=master\
    :target: https://travis-ci.org/P4N74/demangler",
      keywords="demangle gcc",
      license="MIT",
      scripts=['_demangler.py'],
      url="https://github.com/P4N74/demangler",
      ext_modules=[module])

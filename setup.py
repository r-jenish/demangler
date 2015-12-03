from distutils.core import setup, Extension

module = Extension('_demangler', sources=['demangle.cpp'])
setup(name="Demangler",
      version="0.1",
      description="A demangler package for gcc 3.x and gcc 4.x",
      author="Rakholiya Jenish",
      author_email="rakholiyajenish.07@gmail.com",
      keywords="demangle gcc",
      license="MIT",
      scripts=['demangler.py'],
      ext_modules=[module])

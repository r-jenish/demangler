GCC Name Demangler
==================
---

> Demangle even the most complex gcc mangled names, with absolute ease

*GCC Name Demangler* is a module written in Python that can be used to demangle identifiers that were mangled by GCC 3.x and above.

Usage
-----

```
from demangler import demangle
print demangle(<mangled_name>)
```

Setup
-----

```
sudo apt-get install g++ python-dev
python setup.py install
```



License
-------

[MIT License](http://jenish.mit-license.org/)

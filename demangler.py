from _demangler import demangle
__all__ = ['demangle']
if __name__ == '__main__':
    from sys import argv, stdin
    if len(argv) > 1:
        for arg in argv[1:]:
            print(demangle(arg))
    else:
        for arg in stdin:
            print(demangle(arg[:-1]))

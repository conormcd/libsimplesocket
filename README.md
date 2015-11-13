# A simple wrapper around socket(2), connect(2) and close(2)

This is so that those system calls can be called from JNA which can only call
into shared libraries.

# superlumic
A performant, secure, and cross-platform command-line password manager. Implemented in [C++](https://en.wikipedia.org/wiki/C%2B%2B) and [C](https://en.wikipedia.org/wiki/C_(programming_language)) with [tiny-AES-c](https://github.com/kokke/tiny-AES-c), superlumic allows you to create, save, dump (to csv), and load encrypted password lists. Once loaded, you can create, read, update, delete, and reorder the passwords in each password list. The lists themselves are later encrypted with AES-256 (CTR mode) and a user-provided password.

## Usage
An example encrypted password file can be found at [encrypted.txt](encrypted.txt). The password is `password`.
```shell
$ git clone git@github.com:slightlyskepticalpotat/superlumic.git
$ cd superlumic
$ make
g++ *.hpp
g++ -fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2 *.cpp -o superlumic -Wl,-z,now -Wl,-z,relro
$ ./superlumic --help
Usage: ./superlumic [password file]
$ ./superlumic
```

## Security
The makefile specifies the same flags that Hardened Gentoo uses. Below are some of the compiler instructions:
```
Position Independent Executable: yes
Stack protected: yes
Read-only relocations: yes
Immediate binding: yes
Control flow integrity: yes
```

The build process should also be reasonably deterministic. On `g++ (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0`:
```shell
$ sha256sum superlumic
acb377edf969f0014e708de94d50f4c16551a10f6c9b300ee7a12c493a6e2399  superlumic
```

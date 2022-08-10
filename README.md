# superlumic
A performant, secure, and cross-platform command-line password manager. Implemented in [C++](https://en.wikipedia.org/wiki/C%2B%2B) and [C](https://en.wikipedia.org/wiki/C_(programming_language)) with [tiny-AES-c](https://github.com/kokke/tiny-AES-c), superlumic allows you to create, save, and load encrypted password lists. Once loaded, you can create, read, update, delete, and reorder the passwords in each password list. The lists themselves are later encrypted with AES-256 (CTR mode) and a user-provided password.

## Usage
An example encrypted password file can be found at [encrypted.txt](encrypted.txt). The password is `password`.
```shell
$ make
$ ./superlumic
```

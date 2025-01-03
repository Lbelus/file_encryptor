# file_encryptor
Cpp class to perform a XOR encryption on a file. 
Declare an fxor object with the file path, your password and the read size;
```cpp
fxor(const std::string& file, const int key, const int chunk_size)
```
Call .encrypt() to encrypt your file and .encrypt() to decrypt it.

```cpp
int main()
{
    fxor xor_obj("text.txt", 1234, 256);
    xor_obj.encrypt();
    return EXIT_SUCCESS;
}
```

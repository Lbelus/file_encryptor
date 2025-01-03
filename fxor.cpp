#include <unistd.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>


class fxor 
{
private:
    const int key;
    std::string file;
    int fd_write;
    int fd_read;
    const int chunk_size;

    int open_file(const char* file_c_str)
    {
        fd_read     = open(file_c_str, O_RDONLY);
        fd_write    = open(file_c_str, O_RDWR | O_SYNC);
        if (fd_write < 0 || fd_read < 0)
        {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    char* encrypt_chunk(char* chunk, size_t size, int key)
    {
        size_t index =  0;
        while (chunk[index] != '\0')
        {
            chunk[index] ^= key;
            index += 1;
        }
        return chunk;
    }
    void close_fd(int fd)
    {
        if (fd >= 0)
        {
            close(fd);
        }
    }

public:

    fxor(const std::string& file, const int key, const int chunk_size)
    : file(file), key(key), chunk_size(chunk_size)
    {
        if (open_file(file.c_str()) == EXIT_FAILURE)
        {
            throw std::invalid_argument("Could not open file");
        }
    }
    
    char encrypt()
    {
        char* buffer = NULL;
        buffer = (char*)malloc(sizeof(char) * (chunk_size + 1));
        if (buffer == NULL)
        {
            std::cerr << "Mem alloc failled on chunk buffer";
            return EXIT_FAILURE;
        }
        int byte_count = 0;
        while ((byte_count = read(fd_read, buffer, chunk_size)))
        {
            buffer[byte_count + 1] = '\0';
            buffer = encrypt_chunk(buffer, byte_count, key);
            write(fd_write, buffer, byte_count);
        }
        free(buffer);
        return EXIT_SUCCESS;
    }
    
    ~fxor()
    {
        close_fd(fd_read);
        close_fd(fd_write);
    }
};

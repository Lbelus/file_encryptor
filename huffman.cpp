#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#define MAX_ALPHABET 256

class huffman_coding
{
private:
    std::string file;
    int fd_read = 0;
    int chunk_size;
    int frequency[MAX_ALPHABET] = {0};
    int active_size = 0;

public:
    huffman_coding(const std::string& file, const int chunk_size)
    : file(file), chunk_size(chunk_size)
    {
        if (open_file(file.c_str()) == EXIT_FAILURE)
        {
            throw std::invalid_argument("Could not open file");
        }
    }

    int set_frequency(const char* chunk, size_t size)
    {
        if (chunk == NULL || size <= 0)
        {
            return EXIT_FAILURE;
        }
        size_t index =  0;
        char ch = 0;
        while (chunk[index] != '\0')
        {
            if ((int)(ch = chunk[index]) > MAX_ALPHABET)
            {
                return EXIT_FAILURE;
            }
            frequency[ch] += 1;
            index += 1;
        }
        return EXIT_SUCCESS;
    }

    int set_active()
    {
        size_t index = 0;
        while (index < MAX_ALPHABET)
        {
            if (frequency[index] > 0)
            {
                active_size += 1;
            }
            index += 1;
        }
        return EXIT_SUCCESS;
    }

    int open_file(const char* file_c_str)
    {
        fd_read = open(file_c_str, O_RDONLY);
        if (fd_read < 0)
        {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    char get_chunk()
    {
        char* buffer = NULL;
        buffer = (char*)malloc(sizeof(char) * (chunk_size + 1));
        if (buffer == NULL)
        {
            std::cerr << "Mem alloc failled on chunk buffer";
            return EXIT_FAILURE;
        }
        int byte_count = 0;
        int retval = 0;
        while ((byte_count = read(fd_read, buffer, chunk_size)))
        {
            buffer[byte_count + 1] = '\0';
            retval = set_frequency(buffer, byte_count);
            if (retval)
            {
                free(buffer);
                return EXIT_FAILURE;
            }
        }
        free(buffer);
        return EXIT_SUCCESS;
    }

    ~huffman_coding();
};







int main()
{

    return EXIT_SUCCESS;
}

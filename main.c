#include <stdio.h>
#include <stdlib.h>
// #include <png.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>  // for getopt
#include <getopt.h>
// int read_png_to_buffer(const char *filename, uint8_t **out_buffer, int *width, int *height, int *channels) {
//     FILE *fp = fopen(filename, "rb");
//     if (!fp) {
//         perror("File open failed");
//         return 0;
//     }

//     uint8_t header[8];
//     fread(header, 1, 8, fp);
//     if (!png_check_sig(header, 8)) {
//         fprintf(stderr, "Not a valid PNG file\n");
//         fclose(fp);
//         return 0;
//     }

//     png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//     if (!png_ptr) {
//         fclose(fp);
//         return 0;
//     }

//     png_infop info_ptr = png_create_info_struct(png_ptr);
//     if (!info_ptr) {
//         png_destroy_read_struct(&png_ptr, NULL, NULL);
//         fclose(fp);
//         return 0;
//     }

//     if (setjmp(png_jmpbuf(png_ptr))) {
//         fprintf(stderr, "libpng error during init_io\n");
//         png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
//         fclose(fp);
//         return 0;
//     }

//     png_init_io(png_ptr, fp);
//     png_set_sig_bytes(png_ptr, 8);

//     png_read_info(png_ptr, info_ptr);

//     *width = png_get_image_width(png_ptr, info_ptr);
//     *height = png_get_image_height(png_ptr, info_ptr);
//     png_byte color_type = png_get_color_type(png_ptr, info_ptr);
//     png_byte bit_depth  = png_get_bit_depth(png_ptr, info_ptr);

//     if (bit_depth == 16)
//         png_set_strip_16(png_ptr);

//     if (color_type == PNG_COLOR_TYPE_PALETTE)
//         png_set_palette_to_rgb(png_ptr);

//     if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
//         png_set_expand_gray_1_2_4_to_8(png_ptr);

//     if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
//         png_set_tRNS_to_alpha(png_ptr);

//     if (color_type == PNG_COLOR_TYPE_RGB ||
//         color_type == PNG_COLOR_TYPE_GRAY ||
//         color_type == PNG_COLOR_TYPE_PALETTE)
//         png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);

//     if (color_type == PNG_COLOR_TYPE_GRAY ||
//         color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
//         png_set_gray_to_rgb(png_ptr);

//     png_read_update_info(png_ptr, info_ptr);

//     int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
//     *channels = rowbytes / *width;

//     *out_buffer = (uint8_t *)malloc(rowbytes * (*height));
//     if (!*out_buffer) {
//         fprintf(stderr, "Memory allocation failed\n");
//         png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
//         fclose(fp);
//         return 0;
//     }

//     png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * (*height));
//     for (int y = 0; y < *height; y++)
//         row_pointers[y] = *out_buffer + y * rowbytes;

//     png_read_image(png_ptr, row_pointers);

//     free(row_pointers);
//     png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
//     fclose(fp);
//     return 1;
// }

// int write_png_from_buffer(const char *filename, uint8_t *buffer, int width, int height, int channels) {
//     if (channels != 4) {
//         fprintf(stderr, "Only 4-channel RGBA output is supported\n");
//         return 0;
//     }

//     FILE *fp = fopen(filename, "wb");
//     if (!fp) {
//         perror("File open for writing failed");
//         return 0;
//     }

//     png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//     if (!png_ptr) {
//         fclose(fp);
//         return 0;
//     }

//     png_infop info_ptr = png_create_info_struct(png_ptr);
//     if (!info_ptr) {
//         png_destroy_write_struct(&png_ptr, NULL);
//         fclose(fp);
//         return 0;
//     }

//     if (setjmp(png_jmpbuf(png_ptr))) {
//         fprintf(stderr, "libpng error during writing\n");
//         png_destroy_write_struct(&png_ptr, &info_ptr);
//         fclose(fp);
//         return 0;
//     }

//     png_init_io(png_ptr, fp);

//     png_set_IHDR(
//         png_ptr,
//         info_ptr,
//         width,
//         height,
//         8,                          // bit depth
//         PNG_COLOR_TYPE_RGBA,        // color type
//         PNG_INTERLACE_NONE,
//         PNG_COMPRESSION_TYPE_DEFAULT,
//         PNG_FILTER_TYPE_DEFAULT
//     );

//     png_write_info(png_ptr, info_ptr);

//     png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
//     int rowbytes = width * channels;
//     for (int y = 0; y < height; y++) {
//         row_pointers[y] = buffer + y * rowbytes;
//     }

//     png_write_image(png_ptr, row_pointers);
//     png_write_end(png_ptr, NULL);

//     free(row_pointers);
//     png_destroy_write_struct(&png_ptr, &info_ptr);
//     fclose(fp);
//     return 1;
// }
// void write_png() {
//     uint8_t *buffer = NULL;
//     int w, h, c;

//     char* password = "Password123!";
    
//     if (read_png_to_buffer("image.png", &buffer, &w, &h, &c)) {
//         int k = 0;
//         int bit = 7;
//         int redact = 0;

//         for (int i = 0; i < w * h * c; i+=c) {
//             uint8_t r = buffer[i];
//             uint8_t g = buffer[i+1];
//             uint8_t b = buffer[i+2];
//             uint8_t a = buffer[i+3];

//             if (password[k] == '\0') {
//                 redact = 1;
//             }

//             unsigned char c = password[k];
//             if (bit >= 0) {
//                 int bb = (c >> bit) & 1;
//                 switch ((bit + k) % 4)
//                 {
//                 case 0:
//                     r = (r & ~1) | bb;
//                     break;
//                 case 1:
//                     g = (g & ~1) | bb;
//                     break;
//                 case 2:
//                     b = (b & ~1) | bb;
//                     break;
//                 case 3:
//                     a = (a & ~1) | bb;
//                     break;
//                 default:
//                     break;
//                 }

//                 bit-=1;
//             } else {
//                 if (redact == 1) break;
//                 bit = 7;
//                 k += 1;
//             }

//             buffer[i]   = r;
//             buffer[i+1] = g;
//             buffer[i+2] = b;
//             buffer[i+3] = a;
//         }

//         if (write_png_from_buffer("output.png", buffer, w, h, c)) {
//             printf("Wrote output.png successfully!\n");
//         } else {
//             fprintf(stderr, "Failed to write PNG.\n");
//         }

//         free(buffer);
//     }
// }
// void read_png() {
//     uint8_t *buffer = NULL;
//     int w, h, ch;

//     char password[100] = "";
    
//     if (read_png_to_buffer("output.png", &buffer, &w, &h, &ch)) {
//         int k = 0;
//         int bit = 7;

//         unsigned char c = 0;
//         for (int i = 0; i < w * h * ch; i+=ch) {
//             uint8_t r = buffer[i];
//             uint8_t g = buffer[i+1];
//             uint8_t b = buffer[i+2];
//             uint8_t a = buffer[i+3];
            
//             if (bit >= 0) {
//                 switch ((bit + k) % 4)
//                 {
//                 case 0:
//                     c = (c & ~(1 << bit)) | ((r & 1) << bit);
//                     break;
//                 case 1:
//                     c  = (c & ~(1 << bit)) | ((g & 1) << bit);
//                     break;
//                 case 2:
//                     c  = (c & ~(1 << bit)) | ((b & 1) << bit);
//                     break;
//                 case 3:
//                     c  = (c & ~(1 << bit)) | ((a & 1) << bit);
//                     break;
//                 default:
//                     break;
//                 }

//                 bit-=1;
//             } else {
//                 if (c == '\0') break;

//                 printf("%c \n", c);

//                 size_t len = strlen(password);
//                 password[len] = c;
//                 password[len + 1] = '\0'; 

//                 bit = 7;
//                 k += 1;
//             }
//         }

//         free(buffer);
//     }
//     printf("%s\n", password);
// }
#define WAV_HEADER_SIZE 44  // Standard PCM WAV header

uint8_t* load_wav_binary(const char* filename, size_t* out_size) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open WAV file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    if (size <= WAV_HEADER_SIZE) {
        fclose(file);
        fprintf(stderr, "Invalid or too small WAV file\n");
        return NULL;
    }

    uint8_t* buffer = (uint8_t*)malloc(size);
    if (!buffer) {
        fclose(file);
        perror("Failed to allocate memory");
        return NULL;
    }

    size_t read = fread(buffer, 1, size, file);
    fclose(file);

    if (read != (size_t)size) {
        fprintf(stderr, "Failed to read entire WAV file\n");
        free(buffer);
        return NULL;
    }

    *out_size = size;
    return buffer;
}

int save_wav_binary(const char* filename, const uint8_t* buffer, size_t size) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open output WAV file");
        return -1;
    }

    size_t written = fwrite(buffer, 1, size, file);
    fclose(file);
    return (written == size) ? 0 : -1;
}
void write_wav(const char* input, const char* output, const char* filename, const int hidden_bits) {
    char* extension = strrchr(filename, '.');
    size_t ext_len_chars = 0;

    if (extension != NULL && *(extension + 1) != '\0') {
        extension++;
        ext_len_chars = strlen(extension);
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long original_size = ftell(file);
    rewind(file);

    unsigned char* hide = malloc(original_size);
    if (!hide) {
        perror("Failed to allocate buffer");
        fclose(file);
        return;
    }

    size_t bytesRead = fread(hide, 1, original_size, file);
    if (bytesRead != original_size) {
        perror("Failed to read the complete file");
        free(hide);
        fclose(file);
        return;
    }

    size_t wav_size;
    uint8_t* buffer = load_wav_binary(input, &wav_size);
    if (!buffer) {
        free(hide);
        fclose(file);
        return;
    }

    size_t wav_capacity_bits = (wav_size - WAV_HEADER_SIZE) / 2 * hidden_bits;
    size_t payload_bits      = (original_size + ext_len_chars + 1 + 8) * 8;

    printf("Wav capacity: %d bytes\n", wav_capacity_bits / 8);
    printf("Payload size: %d bytes\n", payload_bits / 8);

    if ((payload_bits + 8) > wav_capacity_bits) {
        fprintf(stderr, "Payload too big for cover WAV\n");
        free(hide);
        free(buffer);
        fclose(file);
        return;
    }

    // Prepare payload: 4-byte length header + payload data
    uint32_t payload_len = (uint32_t)original_size;
    unsigned char* payload_with_size = malloc(ext_len_chars + 1 + 4 + original_size);
    if (!payload_with_size) {
        perror("Failed to allocate size buffer");
        free(hide);
        free(buffer);
        fclose(file);
        return;
    }

    payload_with_size[0] = payload_len & 0xFF;
    payload_with_size[1] = (payload_len >> 8) & 0xFF;
    payload_with_size[2] = (payload_len >> 16) & 0xFF;
    payload_with_size[3] = (payload_len >> 24) & 0xFF;

    payload_with_size[4] = ext_len_chars;

    for (int i = 0; i < ext_len_chars; i++) {
        payload_with_size[5 + i] = extension[i];
    }

    memcpy(payload_with_size + 4 + 1 + ext_len_chars, hide, original_size);

    size_t full_payload_bits = (1 + 4 + original_size + ext_len_chars) * 8;

    size_t j = 0;
    int bit = 7;
    int k = 0;
    int counter = 0;

    size_t bit_index = 0;

    for (size_t i = WAV_HEADER_SIZE; i + 1 < wav_size && bit_index < 8; i += 2) {
        int16_t sample = buffer[i] | (buffer[i + 1] << 8);
        unsigned char b0 = (hidden_bits >> (7 - bit_index)) & 1;
        sample = (sample & ~1) | b0;
        buffer[i] = sample & 0xFF;
        buffer[i + 1] = (sample >> 8) & 0xFF;
        bit_index++;
    }

    bit_index = 0;

    for (size_t i = WAV_HEADER_SIZE + 16; i + 1 < wav_size && bit_index < full_payload_bits; i += 2) {
        int16_t sample = buffer[i] | (buffer[i + 1] << 8);

        for (int b = hidden_bits - 1; b >= 0; --b) {
            if (bit_index < full_payload_bits) {
                unsigned char payload_bit = (payload_with_size[bit_index / 8] >> (7 - (bit_index % 8))) & 1;
                sample = (sample & ~(1 << b)) | (payload_bit << b);
                bit_index++;
            }
        }

        buffer[i]     = sample & 0xFF;
        buffer[i + 1] = (sample >> 8) & 0xFF;
    }

    if (save_wav_binary(output, buffer, wav_size) != 0) {
        fprintf(stderr, "Failed to save WAV file\n");
    } else {
        printf("Saved hidden size of %d bytes\n", bit_index/8);
    }

    free(buffer);
    free(hide);
    free(payload_with_size);
    fclose(file);
}

int read_wav(const char* input, const char* output) {
    size_t wav_size;
    uint8_t* buffer = load_wav_binary(input, &wav_size);
    if (!buffer) return 1;
    int bit = 7, k = 0;

    size_t byte_index = 0;

    unsigned char* size_buf = malloc(5);
    memset(size_buf, 0, 5);
    unsigned char hidden_bits = 0;

    size_t bit_index = 0;

    for (size_t i = WAV_HEADER_SIZE; i + 1 < wav_size && bit_index < 8; i += 2) {
        int16_t sample = buffer[i] | (buffer[i + 1] << 8);
        unsigned char b0 = sample & 1;
        hidden_bits |= (b0 << (7 - bit_index));
        bit_index++;
    }

    bit_index = 0;
    for (size_t i = WAV_HEADER_SIZE + 16; i + 1 < wav_size && bit_index < 40; i += 2) {
        int16_t sample = buffer[i] | (buffer[i + 1] << 8);

        for (int b = hidden_bits - 1; b >= 0; --b) {
            if (bit_index < 40) {
                unsigned char extracted_bit = (sample >> b) & 1;
                size_buf[bit_index / 8] |= (extracted_bit << (7 - (bit_index % 8)));
                bit_index++;
            } else {
                break;
            }
        }
    }

    int8_t extension_len = size_buf[4];


    unsigned char* extension = malloc(extension_len);
    memset(extension, 0, extension_len);

    bit_index = 0;
    for (size_t i = WAV_HEADER_SIZE + 16 + 40; i + 1 < wav_size && bit_index < (extension_len * 8); i += 2) {
        int16_t sample = buffer[i] | (buffer[i + 1] << 8);

        for (int b = hidden_bits - 1; b >= 0; --b) {
            if (bit_index < (extension_len * 8)) {
                unsigned char extracted_bit = (sample >> b) & 1;
                extension[bit_index / 8] |= (extracted_bit << (7 - (bit_index % 8)));
                bit_index++;
            } else {
                break;
            }
        }
    }

    size_t filename_len = strlen(output);
    char* result = malloc(filename_len + 1 + extension_len + 1);
    if (!result) return 0;

    memcpy(result, output, filename_len);
    result[filename_len] = '.';
    memcpy(result + filename_len + 1, extension, extension_len);
    result[filename_len + 1 + extension_len] = '\0';

    uint32_t decoded_payload_size = size_buf[0]
                                  | (size_buf[1] << 8)
                                  | (size_buf[2] << 16)
                                  | (size_buf[3] << 24);

    unsigned char* hidden = malloc(decoded_payload_size);
    memset(hidden, 0, decoded_payload_size);

    size_t payload_bit_index = 0;
    size_t total_payload_bits = decoded_payload_size * 8;

    for (size_t i = WAV_HEADER_SIZE + 16 + 40 + extension_len * 8 * 2; i + 1 < wav_size && payload_bit_index < total_payload_bits; i += 2) {
        int16_t sample = buffer[i] | (buffer[i + 1] << 8);

        for (int b = hidden_bits - 1; b >= 0; --b) {
            if (payload_bit_index < total_payload_bits) {
                unsigned char extracted_bit = (sample >> b) & 1;
                hidden[payload_bit_index / 8] |= (extracted_bit << (7 - (payload_bit_index % 8)));
                payload_bit_index++;
            } else {
                break;
            }
        }
    }

    if (payload_bit_index > 0) {
        FILE* out = fopen(result, "wb");
        if (!out) {
            perror("Failed to write output file");
            free(hidden);
            free(buffer);
            return 1;
        }
        fwrite(hidden, 1, (payload_bit_index / 8), out);
        fclose(out);
        printf("Successfully wrote %zu bytes to %s\n", (payload_bit_index / 8), result);
    }

    free(hidden);
    free(buffer);
}

int read_wav_script(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_wav_path> <output_file_path>\n", argv[0]);
        return 1;
    }

    const char* input_path = argv[1];
    const char* output_path = argv[2];

    read_wav(input_path, output_path);
}

int write_wav_script(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_wav_path> <output_wav_path> <file_to_hide_path> <bits_to_hide_in>\n", argv[0]);
        return 1;
    }

    const char* input_path = argv[1];
    const char* output_path = argv[2];
    const char* hidden_path = argv[3];
    const int hidden_bits  = atoi(argv[4]);

    write_wav(input_path, output_path, hidden_path, hidden_bits);
}


#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_RESET   "\033[0m"

// Your function prototypes
struct arguments {
    bool read_mode;
    bool write_mode;
    const char *input_file;
    const char *output_file;
    const char *file_to_hide_path;
    const char *bits_to_hide_in;
};

int main(int argc, char *argv[]) {
    struct arguments args = {0};

    static struct option long_options[] = {
        {"read",              no_argument,       0, 'r'},
        {"write",             no_argument,       0, 'w'},
        {"input_file",        required_argument, 0, 'i'},
        {"output_file",       required_argument, 0, 'o'},
        {"file_to_hide_path", required_argument, 0, 'f'},
        {"bits_to_hide_in",   required_argument, 0, 'b'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "rwi:o:f:b:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'r': args.read_mode = true; break;
            case 'w': args.write_mode = true; break;
            case 'i': args.input_file = optarg; break;
            case 'o': args.output_file = optarg; break;
            case 'f': args.file_to_hide_path = optarg; break;
            case 'b': args.bits_to_hide_in = optarg; break;
            default:
                fprintf(stderr, COLOR_RED "Error:" COLOR_RESET " Unknown option.\n");
                exit(EXIT_FAILURE);
        }
    }

    // Validate mutually exclusive read/write
    if ((args.read_mode && args.write_mode) || (!args.read_mode && !args.write_mode)) {
        fprintf(stderr, COLOR_RED "Error:" COLOR_RESET " Specify exactly one of --read or --write.\n");
        exit(EXIT_FAILURE);
    }

    // Check required arguments
    char missing[256] = {0};
    bool has_missing = false;

    if (args.read_mode) {
        if (!args.input_file) {
            strcat(missing, "--input_file");
            has_missing = true;
        }
        if (!args.output_file) {
            if (has_missing) strcat(missing, ", ");
            strcat(missing, "--output_file");
            has_missing = true;
        }
    } else if (args.write_mode) {
        if (!args.input_file) {
            strcat(missing, "--input_file");
            has_missing = true;
        }
        if (!args.output_file) {
            if (has_missing) strcat(missing, ", ");
            strcat(missing, "--output_file");
            has_missing = true;
        }
        if (!args.file_to_hide_path) {
            if (has_missing) strcat(missing, ", ");
            strcat(missing, "--file_to_hide_path");
            has_missing = true;
        }
        if (!args.bits_to_hide_in) {
            if (has_missing) strcat(missing, ", ");
            strcat(missing, "--bits_to_hide_in");
            has_missing = true;
        }
    }

    if (has_missing) {
        fprintf(stderr, COLOR_RED "Error:" COLOR_RESET
                " Missing required option%s in %s mode: %s\n",
                strchr(missing, ',') ? "s" : "",
                args.read_mode ? "read" : "write",
                missing);
        exit(EXIT_FAILURE);
    }

    // Proceed to call appropriate function
    if (args.write_mode) {
        write_wav(args.input_file, args.output_file, args.file_to_hide_path, atoi(args.bits_to_hide_in));
    } else if (args.read_mode) {
        read_wav(args.input_file, args.output_file);
    }

    return EXIT_SUCCESS;
}
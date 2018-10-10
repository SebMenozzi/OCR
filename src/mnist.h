#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define TRAIN_IMAGE "./data/mnist/train-images-idx3-ubyte"
#define TRAIN_LABEL "./data/mnist/train-labels-idx1-ubyte"
#define TEST_IMAGE "./data/mnist/t10k-images-idx3-ubyte"
#define TEST_LABEL "./data/mnist/t10k-labels-idx1-ubyte"

/*
#define TRAIN_IMAGE "./data/emnist/letters/emnist-letters-test-images-idx3-ubyte"
#define TRAIN_LABEL "./data/emnist/letters/emnist-letters-test-labels-idx1-ubyte"
#define TEST_IMAGE "./data/emnist/letters/emnist-letters-train-images-idx3-ubyte"
#define TEST_LABEL "./data/emnist/letters/emnist-letters-train-labels-idx1-ubyte"
*/

#define SIZE 784 // 28x28 (784) pixels
#define NUM_TRAIN 60000 // 60,000 training images
#define NUM_TEST 10000 // 10,000 testing images
#define LEN_INFO_IMAGE 4
#define LEN_INFO_LABEL 2

#define MAX_IMAGESIZE 1280
#define MAX_BRIGHTNESS 255
#define MAX_FILENAME 256
#define MAX_NUM_OF_IMAGES 1

unsigned char image[MAX_NUM_OF_IMAGES][MAX_IMAGESIZE][MAX_IMAGESIZE];
int width[MAX_NUM_OF_IMAGES];
int height[MAX_NUM_OF_IMAGES];

int info_image[LEN_INFO_IMAGE];
int info_label[LEN_INFO_LABEL];

unsigned char train_image_char[NUM_TRAIN][SIZE]; // char[60000][784]
unsigned char test_image_char[NUM_TEST][SIZE]; // char[10000][784]
unsigned char train_label_char[NUM_TRAIN][1]; // char[60000][1]
unsigned char test_label_char[NUM_TEST][1]; // char[10000][1]

double train_image[NUM_TRAIN][SIZE]; // double[60000][784]
double test_image[NUM_TEST][SIZE]; // double[10000][784]
int train_label[NUM_TRAIN]; // int[60000]
int test_label[NUM_TEST]; // int[10000]


void FlipLong(unsigned char * ptr)
{
    register unsigned char val;

    // Swap 1st and 4th bytes
    val = *(ptr);
    *(ptr) = *(ptr+3);
    *(ptr+3) = val;

    // Swap 2nd and 3rd bytes
    ptr += 1;
    val = *(ptr);
    *(ptr) = *(ptr+1);
    *(ptr+1) = val;
}


void read_mnist_char(char *file_path, int num_data, int len_info, int arr_n, unsigned char data_char[][arr_n], int info_arr[])
{
    int i, fd;
    unsigned char *ptr;

    if ((fd = open(file_path, O_RDONLY)) == -1) {
        fprintf(stderr, "Couldn't open image file");
        exit(-1);
    }

    read(fd, info_arr, len_info * sizeof(int));

    // read-in information about size of data
    for (i = 0; i < len_info; i++) {
        ptr = (unsigned char *) (info_arr + i);
        FlipLong(ptr);
        ptr = ptr + sizeof(int);
    }

    // read-in mnist numbers (pixels|labels)
    for (i = 0; i < num_data; i++) {
        read(fd, data_char[i], arr_n * sizeof(unsigned char));
    }

    close(fd);
}


void image_char2double(int num_data, unsigned char data_image_char[][SIZE], double data_image[][SIZE])
{
    for (int i = 0; i < num_data; i++) {
      for (int j = 0; j < SIZE; j++) {
        data_image[i][j]  = (double) data_image_char[i][j] / 255.0;
      }
    }
}


void label_char2int(int num_data, unsigned char data_label_char[][1], int data_label[])
{
    for (int i = 0; i < num_data; i++) {
      data_label[i]  = (int) data_label_char[i][0];
    }
}


void load_mnist()
{
    read_mnist_char(TRAIN_IMAGE, NUM_TRAIN, LEN_INFO_IMAGE, SIZE, train_image_char, info_image);
    image_char2double(NUM_TRAIN, train_image_char, train_image);

    read_mnist_char(TEST_IMAGE, NUM_TEST, LEN_INFO_IMAGE, SIZE, test_image_char, info_image);
    image_char2double(NUM_TEST, test_image_char, test_image);

    read_mnist_char(TRAIN_LABEL, NUM_TRAIN, LEN_INFO_LABEL, 1, train_label_char, info_label);
    label_char2int(NUM_TRAIN, train_label_char, train_label);

    read_mnist_char(TEST_LABEL, NUM_TEST, LEN_INFO_LABEL, 1, test_label_char, info_label);
    label_char2int(NUM_TEST, test_label_char, test_label);
}

#include "mnist.h"

void OCR()
{
    load_mnist();

    for (size_t i = 0; i < 784; i++) {
        printf("%1.1f ", test_image[0][i]);
        if ((i+1) % 28 == 0) putchar('\n');
    }

    printf("label: %d\n", test_label[0]);

    //save_mnist_pgm(test_image, 0);

    //print_mnist_pixel(test_image, NUM_TEST);
    //print_mnist_label(NUM_TEST);
}

#ifndef CONFIG_H
#define CONFIG_H

#define TRAINING_DATA_PATH "data/training_data"
#define TRAINING_DATA_SEG_PATH "data/training_data/from_segmentation"
#define RAW_CHARACTERS_PATH "data/raw_characters"

#define NB_HIDDEN 20

// 6 special characters + 10 digits + 52 letters => 68
#define CHARACTERS ")(,.!?0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define NB_CHARACTERS 68
#define SIZE 20

#endif

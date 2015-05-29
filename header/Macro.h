#ifndef __MACRO_H__
#define __MACRO_H__

//the number of array to save the time sequence info
//it should larger than any data sequence!!
#define TIME_CONTAINER 500  

#define MAX_NUM_DATA 9999999

#define NUM_DATA_DUMP 1
#define NUM_DATA_MINI_DUMP 10 //times to dump in one epoch (include the end of epoch)

#define MAX_BPTT_LAYERS 5

#define TRAIN_MEMORY_INIT

#define DATA_RANGE 0.01
#define ANS_TRUNCATE 

//Cost Function: you can ONLY choose one of them: CROSS_ENTROPY / SQUARE_ERROR
#define CROSS_ENTROPY
//#define SQUARE_ERROR


//hw3 Prediction: you can only choose one of them: MAX_INNER_RPODUCT / MIN_DISTANCE
//#define MAX_INNER_PRODUCT
//#define MIN_DISTANCE
//#define MIN_COS_DISTANCE
#define MIN_SQUARE_ERROR
//#define ONE_OF_N
#define MAX_MATCHING

#endif //__MACRO_H__

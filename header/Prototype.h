#ifndef __PROTOTYPE_H__
#define __PROTOTYPE_H__



MatrixXd* Load_Data(const char* filename, MatrixXd *data, int* );

MatrixXd* Load_Data_Hw3(const char* filename, MatrixXd *data, int Blank_Pos[], int *ptr_num_data);
MatrixXd* Load_Answer(const char* filename, MatrixXd *answer, int *ptr_num_data);
MatrixXd* HW3_MakingAnswers(MatrixXd*, MatrixXd*, int);

/*
MatrixXd* Load_Parameters
(const char dir_path[], const char setting_file[], const char pars_file[], const char mem_file[],
, MatrixXd
*/

#endif //__PROTOTYPE_H__

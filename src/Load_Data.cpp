#include "General.h"

MatrixXd* Load_Data(const char* filename, MatrixXd *data, int *ptr_num_data)
{
    ifstream fin(filename);
    FILE *File;
    File = fopen(filename, "r");
    char str[10000];
    string s;
    int max_n = 10000;

    fgets(str, max_n, File);  getline(fin, s);
    fgets(str, max_n, File);  getline(fin, s);


    sscanf(str, "%d", ptr_num_data);
    (*ptr_num_data) = min (*ptr_num_data, MAX_NUM_DATA);

    int num_data = *ptr_num_data;
    
    data = new MatrixXd [num_data];

    int row;
    int col;

    for (int i=0; i<num_data; i++)
    {
        cout<<"Load Data: "<<i<<" / "<<num_data<<endl;
        fgets(str, max_n, File); getline(fin, s);
        fgets(str, max_n, File); getline(fin, s);
        fgets(str, max_n, File); getline(fin, s);
        sscanf(str, "%d", &row); 

        fgets(str, max_n, File); getline(fin, s);
        fgets(str, max_n, File); getline(fin, s);
        sscanf(str, "%d", &col); 
        
        fgets(str, max_n, File); getline(fin, s);

        data[i] = MatrixXd::Constant(row, col, 0);

        for (int j=0; j<row; j++)
        {
            fgets(str, max_n, File);
            for (int k=0; k<col; k++)
                fin>>data[i](j,k);
        }
        getline(fin, s);

    }

    fclose(File);
    fin.close();

    return data;
}

MatrixXd* Load_Answer(const char* filename, MatrixXd *data, int *ptr_num_data)
{
    //the only difference is the length of file (we skip the first word)
    ifstream fin(filename);
    FILE *File;
    File = fopen(filename, "r");
    char str[10000];
    string s;
    int max_n = 10000;

    fgets(str, max_n, File);  getline(fin, s);
    fgets(str, max_n, File);  getline(fin, s);


    sscanf(str, "%d", ptr_num_data);
    (*ptr_num_data) = min (*ptr_num_data, MAX_NUM_DATA);

    int num_data = *ptr_num_data;
    
    data = new MatrixXd [num_data];

    int row;
    int col;

    for (int i=0; i<num_data; i++)
    {
        cout<<"Load Data: "<<i<<" / "<<num_data<<endl;
        fgets(str, max_n, File); getline(fin, s);
        fgets(str, max_n, File); getline(fin, s);
        fgets(str, max_n, File); getline(fin, s);
        sscanf(str, "%d", &row); 

        fgets(str, max_n, File); getline(fin, s);
        fgets(str, max_n, File); getline(fin, s);
        sscanf(str, "%d", &col); 
        
        fgets(str, max_n, File); getline(fin, s);

        data[i] = MatrixXd::Constant(row-1, col, 0);

        double garbage;

        for (int j=0; j<row; j++)
        {
            fgets(str, max_n, File);

            for (int k=0; k<col; k++)
            {
                if (j ==0)
                    fin>>garbage;
                else
                    fin>>data[i](j-1,k);
            }
        }
        getline(fin, s);

    }

    fclose(File);
    fin.close();

    return data;
}



MatrixXd* Load_Data_Hw3(const char* filename, MatrixXd *data, int Blank_Pos[], int *ptr_num_data)
{
    ifstream fin(filename);
    FILE *File;
    File = fopen(filename, "r");
    char str[10000];
    string s;
    int max_n = 10000;

    fgets(str, max_n, File);  getline(fin, s);
    fgets(str, max_n, File);  getline(fin, s);

    //cout<<"str:"<<str<<endl;

    sscanf(str, "%d", ptr_num_data);
    (*ptr_num_data) = min (*ptr_num_data, MAX_NUM_DATA);

    int num_data = *ptr_num_data;
    //cout<<"num_data:"<<num_data<<endl;
    
    data = new MatrixXd [num_data];
    //Blank_Pos = new int [num_data];

    int row;
    int col;

    for (int i=0; i<num_data; i++)
    {
        cout<<"Load Data: "<<i<<" / "<<num_data<<endl;
        fgets(str, max_n, File); getline(fin, s); //-----
        fgets(str, max_n, File); getline(fin, s); //rows:
        fgets(str, max_n, File); getline(fin, s); 
        sscanf(str, "%d", &row); 

        fgets(str, max_n, File); getline(fin, s); //cols:
        fgets(str, max_n, File); getline(fin, s); 
        sscanf(str, "%d", &col); 

        fgets(str, max_n, File); getline(fin, s); //blank position
        fgets(str, max_n, File); getline(fin, s); 
        sscanf(str, "%d", Blank_Pos+i); 
        
        fgets(str, max_n, File); getline(fin, s);

        data[i] = MatrixXd::Constant(row, col, 0);

        for (int j=0; j<row; j++)
        {
            fgets(str, max_n, File);
            for (int k=0; k<col; k++)
                fin>>data[i](j,k);
        }
        getline(fin, s);
    }

    fclose(File);
    fin.close();

    return data;
}

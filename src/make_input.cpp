#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#define SIZE 2000 
using std::string;
using std::cout;
using std::endl;
using std::ios;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::map;
using std::pair;
using std::getline;
using std::vector;
using std::find;

typedef map<string, float*> feature_map;

const char train_txt[] = "preprocess/preprocessed_files/RAW_TRAIN_INPUT.TXT";
const char test_with_brac[] = "preprocess/preprocessed_files/RAW_TEST_INPUT_WITH_BRACKETS.TXT";
const char input_txt_path[] = "input_files/input.txt";
const char train_vec[] = "preprocess/word_vectors_files/TRAIN_VEC.TXT";
const char test_vec[] = "preprocess/word_vectors_files/TEST_VEC.TXT";

//int get_test_map(feature_map*);
int get_test_num();
void get_test_array(string*);
int get_train_map(feature_map*, string*, int len);
void simple_guess(feature_map*, int);
void make_input_txt(feature_map*, int);
int get_num_of_lines(const char*);
void check_vec();
float square(float, float);
bool input_f = false;
bool test_f = false;
bool guess_f = false;

int main(int argc, char* argv[]){
    if(strcmp(argv[1], "input")==0){
        input_f = true;
    }
    else if(strcmp(argv[1], "test")==0){
        test_f = true; 
    }
    else if(strcmp(argv[1], "guess")==0){
        guess_f = true;
    }

    feature_map* train_map = new feature_map;
    int num_of_words = get_test_num(); // how many words in testing_data
    string* ptr = new string[num_of_words];
    get_test_array(ptr);
    
    int l1 = get_train_map(train_map, ptr, num_of_words); // l1 = length 1, length of word vector
    if(test_f){
        cout<<"Make two files for validation\n";
        simple_guess(train_map, l1);
    }else if(guess_f){
        cout<<"Simple guess\n";
        simple_guess(train_map, l1);
    }else if(input_f){
        cout<<"Make input.txt\n";
        make_input_txt(train_map, l1);
    }
    else{
        cout<<"Need option... input or test or guess.\n";
        // check_vec();
    }
    
    return 0;
}

int get_test_num(){
    char* line = new char[SIZE];
    string string_line;
    const char* delim = " ";
    char* token;
    int word_num;
    ifstream test(test_vec);
    getline(test,string_line); // first line
    strcpy(line, string_line.c_str()); // from string to char array
    token = strtok(line, delim);  // first part
    word_num = atoi(token); // get number of testing words
    test.close();
    return word_num;
}

void get_test_array(string* a_ptr){
    char* line = new char[SIZE];
    string string_line;
    const char* delim = " ";
    char* token;
    ifstream test(test_vec);
    getline(test,string_line); // first line
    int c = 0;
    while(getline(test,string_line)){
        strcpy(line, string_line.c_str()); // from string to char array
        token = strtok(line, delim); // the word
        string word(token);
        cout << word << endl;
        a_ptr[c] = word;
        c++;
    }
    test.close();
}
/*
int get_test_map(feature_map* test_map){
    char* line = new char[SIZE];
    string string_line;
    const char* delim = " ";
    char* token;
    int feature_length;
    ifstream test(test_vec);
    getline(test,string_line); // first line
    cout << vec[0] << endl;
    strcpy(line, string_line.c_str()); // from string to char array
    token = strtok(line, delim);  // first part
    token = strtok(NULL, delim);  // second part
    feature_length = atoi(token); //(token - '0') % 48;
    //cout << feature_length << endl;
    while(getline(test,string_line)){
        strcpy(line, string_line.c_str()); // from string to char array
        float* feature  = new float [feature_length]; // add to map
        token = strtok(line, delim); // the word
        string word(token);
        cout << word << endl;
        test_map->insert(pair<string,float*>(word, feature));
        for(int count = 0; count < feature_length; count++) {
            token = strtok(NULL, delim); // extract features
            feature[count] = atof(token);
        }
    }
    return feature_length;
}*/

void check_vec(){
    char* line = new char[SIZE];
    string string_line;
    const char* delim = " ";
    char* token;
    int feature_length;
    ifstream train(train_vec);
    getline(train,string_line); // first line
    strcpy(line, string_line.c_str()); // from string to char array
    token = strtok(line, delim);  // first part
    token = strtok(NULL, delim);  // second part
    feature_length = atoi(token); //(token - '0') % 48;
    while(getline(train,string_line)){
        float total = 0;
        strcpy(line, string_line.c_str()); // from string to char array
        float* feature  = new float [feature_length]; // add to map
        token = strtok(line, delim); // the word
        for(int count = 0; count < feature_length; count++) {
            token = strtok(NULL, delim); // extract features
            total += atof(token) * atof(token);
        }
        cout<<total<<endl;
    }
    train.close();
}

int get_train_map(feature_map* train_map, string* vec, int len){
    char* line = new char[SIZE];
    string string_line;
    const char* delim = " ";
    char* token;
    int feature_length;
    ifstream train(train_vec);
    getline(train,string_line); // first line
    strcpy(line, string_line.c_str()); // from string to char array
    token = strtok(line, delim);  // first part
    token = strtok(NULL, delim);  // second part
    feature_length = atoi(token); //(token - '0') % 48;
    //cout << feature_length << endl;
    while(getline(train,string_line)){
        strcpy(line, string_line.c_str()); // from string to char array
        float* feature  = new float [feature_length]; // add to map
        token = strtok(line, delim); // the word
        string word(token);
        string* p;
        p = find(vec, vec + len, word);
        // vector<string>::iterator it = find(vec->begin(), vec->end(), word);
        //if(it != vec->end()){ // Training file contain this word
        if(p != vec + len){ // Training file contain this word
            cout <<"Found \""<< word<<"\"!"<< endl;
            train_map->insert(pair<string,float*>(word, feature));
            for(int count = 0; count < feature_length; count++) {
                token = strtok(NULL, delim); // extract features
                feature[count] = atof(token);
            }
        }
        else{
            // put in "others" section
            cout<<"There is no \""<<word<<"\" in Testing_Data"<<endl;
            p = find(vec, vec+len, "OTHERS");
            if(p != vec+len){ // already has OTHERS
                for(int count = 0; count < feature_length; count++) {
                    token = strtok(NULL, delim); // extract features
                    // feature[count] = (feature[count] + atof(token)) / 2;
                    feature[count] = (feature[count]*feature[count] + atof(token)*atof(token));
                }
            }
            else{
                train_map->insert(pair<string,float*>("OTHERS", feature));
                for(int count = 0; count < feature_length; count++) {
                    token = strtok(NULL, delim); // extract features
                    feature[count] = atof(token);
                }
            }
        }
    }
    train.close();
    return feature_length;
}

void simple_guess(feature_map* train_map, int word_vec_size){ // simply use word vector to guess answer
    char* line = new char[SIZE];
    string string_line;
    const char* delim = " ";
    const char* brack_delim_l = "[";
    const char* brack_delim_r = "]";
    char* token;
    char* first;
    char* op_word;
    float* op_word_arr;
    char* last;
    int count = 0;
    int q_count = 0;
    int largest_op = 0;
    int number_of_data = 1040; //1040 questions
    float largest_result;
    vector<float*> fptr_vec;
    ifstream test_b(test_with_brac);
    fstream guess_csv;
    fstream test_op;
    fstream test_q;
    if(guess_f){
        guess_csv.open("guess.CSV", ios::out);
        guess_csv<<"Id,Answer"<<endl;
    }else if (test_f){
        test_op.open("input_files/test_option.txt", ios::out);
        test_q.open("input_files/test_question.txt", ios::out);
        test_op<<"number of data:"<<endl<<number_of_data<<endl<<"-----"<<endl;
        test_q<<"number of data:"<<endl<<number_of_data<<endl<<"-----"<<endl;
    }
    while(getline(test_b,string_line)){
        if(count == 0){
            int words_in_sentences = 0;
            int words_before_op = 0;
            largest_result = 1000000000;
            // first line, read all words, store vector
            strcpy(line, string_line.c_str()); // from string to char array
            first = strtok(line, brack_delim_l); // part before [
            op_word = strtok(NULL,brack_delim_r);
            last = strtok(NULL,brack_delim_r);
            token = strtok(first,delim); // get first word
            while(token != NULL){
                words_in_sentences++;
                words_before_op++;
                string str_tok(token);
                feature_map::iterator it = train_map->find(str_tok);
                if(it == train_map->end()){
                    it = train_map->find("OTHERS");
                }
                fptr_vec.push_back(it->second); 
                token = strtok(NULL,delim); // get words
            }
            token = strtok(last,delim);
            while(token != NULL){
                words_in_sentences++;
                string str_tok(token);
                feature_map::iterator it = train_map->find(str_tok);
                if(it == train_map->end()){
                    it = train_map->find("OTHERS");
                }
                fptr_vec.push_back(it->second); 
                token = strtok(NULL,delim); // get words
            }
            if(test_f){
                test_op<<"rows:\n5\ncols:\n"<<word_vec_size<<"\n-----"<<endl;
                test_q<<"rows:\n"<<words_in_sentences<<"\ncols:\n"<<word_vec_size<<"\nposition:\n"<<words_before_op<<"\n-----"<<endl;
            }
            words_in_sentences = 0;
            words_before_op = 0;
        }
        else{
            strcpy(line, string_line.c_str()); // from string to char array
            first = strtok(line, brack_delim_l); // part before [
            op_word = strtok(NULL,brack_delim_r);
        }

        string op_word_str(op_word);
        feature_map::iterator it;
        it = train_map->find(op_word);
        if (it == train_map->end()){
            it = train_map->find("OTHERS"); // for others
        }
        op_word_arr = it->second;
        if(test_f){
            for(int i = 0; i < word_vec_size; i++) {
                test_op<<op_word_arr[i]<<" ";
            }
            test_op<<endl;
        }
        // nultiply the word vectors
        float result = 0;
        int make_sure_words = 0;
        vector<float*>::iterator fptr_iter;
        for(fptr_iter = fptr_vec.begin();fptr_iter != fptr_vec.end(); fptr_iter++){ // all words
            make_sure_words ++;
            for (int i = 0; i < word_vec_size; i++) { // one of the words
                // result += (*fptr_iter)[i] * op_word_arr[i];
                result += square((*fptr_iter)[i], op_word_arr[i]); // smaller better
                if(count == 0 && test_f){
                    test_q<<(*fptr_iter)[i]<<" ";
                }
            }
            result = sqrt(result); // root
            if(count == 0 && test_f)test_q<<endl;
            //if(result > largest_result){
            if(result < largest_result){ // smaller better
                largest_op = count;
                largest_result = result;
                result = 0;
            }
        }
        make_sure_words = 0;
        count++;
        if(count == 5){
            q_count++;
            // write output
            if(guess_f){
                if(largest_op == 0)guess_csv<<q_count<<",a"<<endl;
                else if(largest_op == 1)guess_csv<<q_count<<",b"<<endl;
                else if(largest_op == 2)guess_csv<<q_count<<",c"<<endl;
                else if(largest_op == 3)guess_csv<<q_count<<",d"<<endl;
                else if(largest_op == 4)guess_csv<<q_count<<",e"<<endl;
            }
            count = 0;
            largest_op = 0;
            largest_result = 0;
            fptr_vec.clear(); // different sentences
            if(test_f){
                test_op<<"-----"<<endl;
                test_q<<"-----"<<endl;
            }
        }
    }
    guess_csv.close();
    test_b.close();
    test_op.close();
    test_q.close();
}

void make_input_txt(feature_map* train_map, int length){
    char* line = new char[SIZE];
    string string_line;
    const char* delim = " ";
    char* token;
    int words_in_sentences = 0; // how many words in a sentence
    float* ptr;
    vector<float*> fptr_vec;
    int number_of_lines = get_num_of_lines(train_txt);
    ifstream train(train_txt);
    ofstream input_txt(input_txt_path);
    input_txt<<"number of data:"<<endl<<number_of_lines<<endl<<"-----"<<endl;
    while(getline(train,string_line)){
        strcpy(line, string_line.c_str()); // from string to char array
        token = strtok(line, delim);
        while(token != NULL){
            words_in_sentences++;    
            string word_str(token);
            feature_map::iterator it;
            it = train_map->find(word_str);
            if (it == train_map->end()){
                it = train_map->find("OTHERS"); // for others
            }
            ptr = it->second;
            fptr_vec.push_back(ptr); // store the float array of this word
            token = strtok(NULL, delim); // next word
        }
        input_txt<<"rows:"<<endl<<words_in_sentences<<endl<<"cols:"<<endl<<length<<endl<<"-----"<<endl;
        vector<float*>::iterator it;
        for(it = fptr_vec.begin(); it < fptr_vec.end(); it++){
            for (int i = 0; i < length; i++) {
                if(i == length - 1) input_txt<<(*it)[i]<<endl;
                else{
                    input_txt<<(*it)[i]<<" ";
                }
            }
        }
        input_txt<<"-----"<<endl;
        words_in_sentences = 0;
        fptr_vec.clear();
    }
    train.close();
    input_txt.close();
}
int get_num_of_lines(const char* file){
    ifstream in(file);
    string str;
    int n = 0;
    while(getline(in, str)){
        n++;
    }
    in.close();
    return n;
}
float square(float a, float b){
    return ((a-b) * (a-b));
}

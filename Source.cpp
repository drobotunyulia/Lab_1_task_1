#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <stdarg.h>

using namespace std;

bool is_substr(string str, string substr);
vector<string> search_str(bool (*is_substr_ptr)(string, string), string substr, size_t count, ...);
void load_file(const string file_name, string& buffer);

int main()
{
    cout << "Laba 1 Task 1\nDrobotun Yulia M8o-210B-20\n" << endl << endl;
    string substr = "k\nk";
    int counter = 3;
    cout << "Files:\n";
    string str_1 = "C:/3_sem/Laba_1/task_1/file_1.txt";
    string str_2 = "C:/3_sem/Laba_1/task_1/file_2.txt";
    string str_3 = "C:/3_sem/Laba_1/task_1/file_3.txt";
    
    vector<string> file_collection = search_str(is_substr, substr, counter, str_1, str_2, str_3);
    for (int i = 0; i < file_collection.size(); i++)
    {
        cout << file_collection[i] << endl;//вывод
    }
    return 0;
}

void load_file(const string file_name, string& buffer)
{
    ifstream input_file(file_name);
    char temp;
    while (input_file.get(temp))
    {
        buffer.push_back(temp);
    }
    input_file.close();
}

vector<string> search_str(bool (*is_substr_ptr)(string, string), string substr, size_t count, ...)
{
    vector<string> out_vector; 
    string buffer;
    va_list factor;
    va_start(factor, count);
    for (size_t i = 0; i < count; i++)
    {
        buffer = "";
        string file_name = va_arg(factor, string);
        load_file(file_name, buffer);
        if (is_substr_ptr(buffer, substr))
            out_vector.push_back(file_name);
    }
    return out_vector;
}


bool is_substr(string str, string substr)
{
    unsigned int curr_len = 0;
    unsigned int counter = 0;
    if (substr.length() > str.length())
        return true;
    for (unsigned long long i = 0; i < str.length(); i++)
    {
        if (str[i] == substr[counter])
        {
            curr_len = curr_len + 1;
            for (unsigned long long j = i + 1; j < str.length() && counter < substr.length(); j++)
            {
                counter = counter + 1;
                if (str[j] == substr[counter])
                {
                    curr_len = curr_len + 1;
                }
            }
        }
        if (curr_len == substr.length())
        {
            return true;
        }
        counter = 0;
        curr_len = 0;
    }
    return false;
}
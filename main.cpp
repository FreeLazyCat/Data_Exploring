#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

struct DATASTRUCT
{
    int id;
    double longitude, latitude, height;
};

const int DATASIZE = 500000;

bool compare_longitude(const DATASTRUCT x, const DATASTRUCT y) {
    return x.longitude < y.longitude;
}

bool compare_latitude(const DATASTRUCT x, const DATASTRUCT y) {
    return x.latitude < y.latitude;
}
bool compare_height(const DATASTRUCT x, const DATASTRUCT y) {
    return x.height < y.height;
}

bool compare_id(const DATASTRUCT x, const DATASTRUCT y) {
    return x.id < y.id;
}

void extractData(vector<DATASTRUCT> & data, string input_line)
{
    size_t sz1, sz2, sz3;
    DATASTRUCT newData;
    newData.id = stoi(input_line, &sz1);
    newData.longitude = stod(input_line.substr(sz1+1), &sz2);
    newData.latitude = stod(input_line.substr(sz1+sz2+2), &sz3);
    newData.height = stod(input_line.substr(sz1+sz2+sz3+3));

    data.push_back(newData);
}

double getSum(vector<DATASTRUCT> data, size_t data_size, int mode){
    double sum = 0;
    switch (mode){
        case 0:
            for (size_t i = 0 ; i < data_size; i++)
                sum += data[i].longitude;
            return sum;
        case 1:
            for (size_t i = 0 ; i < data_size; i++)
                sum += data[i].latitude;
            return sum;
        case 2:
            for (size_t i = 0 ; i < data_size; i++)
                sum += data[i].height;
            return sum;
        default:
            return 0;
    }
}

void exploreData(vector<DATASTRUCT> data, size_t data_size, int mode, double &maxValue, double &minValue,
                 double &midValue, double &aveValue)
{
    switch (mode){
        case 0:         // longitude
            sort(data.begin(), data.end(), compare_longitude);
            maxValue = data[data_size-1].longitude;
            minValue = data[0].longitude;
            midValue = data[data_size/2].longitude;
            aveValue = getSum(data, data_size, mode) / data_size;
            break;
        case 1:         // latitude
            sort(data.begin(), data.end(), compare_latitude);
            maxValue = data[data_size-1].latitude;
            minValue = data[0].latitude;
            midValue = data[data_size/2].latitude;
            aveValue = getSum(data, data_size, mode) / data_size;
            break;
        case 2:         // height
            sort(data.begin(), data.end(), compare_height);
            maxValue = data[data_size-1].height;
            minValue = data[0].height;
            midValue = data[data_size/2].height;
            aveValue = getSum(data, data_size, mode) / data_size;
            break;
        default:
            return;
    }
}

int main()
{
    string line;
    vector<DATASTRUCT> inputData;
    size_t data_size = 0;
    ifstream inFile("/home/advanced/ClionProjects/data_exploring/data.txt");
    while (getline(inFile, line)){
        extractData(inputData, line);
    }

    data_size = inputData.size();

    DATASTRUCT maxValue, minValue, midValue, aveValue;
    exploreData(inputData, data_size, 0, maxValue.longitude, minValue.longitude, midValue.longitude, aveValue.longitude);
    exploreData(inputData, data_size, 1, maxValue.latitude, minValue.latitude, midValue.latitude, aveValue.latitude);
    exploreData(inputData, data_size, 2, maxValue.height, minValue.height, midValue.height, aveValue.height);

    printf("longitude : %.6lf  %.6lf  %.6lf  %.6lf\n",  maxValue.longitude, minValue.longitude, midValue.longitude, aveValue.longitude);
    printf("latitude : %.6lf  %.6lf  %.6lf  %.6lf\n",  maxValue.latitude, minValue.latitude, midValue.latitude, aveValue.latitude);
    printf("height : %.6lf  %.6lf  %.6lf  %.6lf\n",  maxValue.height, minValue.height, midValue.height, aveValue.height);

    // ID
    sort(inputData.begin(), inputData.end(), compare_id);
    int preID=-1, ID_number=0;
    for (size_t i = 0; i < data_size; i++)
        if (inputData[i].id != preID){
            preID = inputData[i].id;
            ID_number++;
        }
    printf("ID number : %d\n", ID_number);
    printf("average %.6lf data per ID\n", 1.0 * data_size / ID_number);
    return 0;
}
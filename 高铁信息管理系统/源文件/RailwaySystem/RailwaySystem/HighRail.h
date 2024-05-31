#pragma once
#include"List_1.h"
Status WriteFile(HRailList& railList, const char* file);
Status AddTrain(HRailList& railList, const char* file);
Status StopTrain(HRailList& railList, const char* file);
Status SearchTrain(HRailList& railList);
Status ModifyTrain(HRailList& railList, const char* file);
Status ReadTrainFromFile(HRailList& railList, const char* file);
Status PrintTrainInfo(HRailList& railList);


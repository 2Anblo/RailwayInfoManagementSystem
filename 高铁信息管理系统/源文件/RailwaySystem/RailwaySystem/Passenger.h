#pragma once
#include"List_2.h"
Status WriteFilePass(PassList& PList, const char* file);
Status AddPassenger(PassList& PList, const char* file);
Status DeletePassenger(PassList& PList, const char* file);
Status SearchPassenger(PassList& PList);
Status ModifyPassenger(PassList& PList, const char* file);
Status ReadPassengersFromFile(PassList& PList, const char* file);
Status PrintPassengerInfo(PassList& PList);
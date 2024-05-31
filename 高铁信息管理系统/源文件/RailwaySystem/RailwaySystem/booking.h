#pragma once
#include "List_3.h"
Status ReadFromBooking(BList& blist,HRailList& hrList,const char* file);
Status WriteBooking(BList& blist, const char* file);
Status AddBooking(BList& blist, HRailList& railList, const char* fileRail, const char* file);
Status DeleteBooking(BList& blist, const char* file);
Status SearchBookingTicket(BList& blist);
Status SearchLeftTicket(HRailList& railList);
Status PrintBookingInfo(BList& blist);
Status GenerateOrderNum(BList& blist);
Status PrintTicketInfo(BList& blist);
Status PrintTicketInfoToFile(BList& blist);
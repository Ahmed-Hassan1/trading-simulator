#pragma once

#include "OrderBook.h"
#include "Wallet.h"
#include "MarketAnalysis.h"

class Bot
{
    public:
        Bot();
        
        /** Call this to start the Bot */
        void init();

        /** Passes the bid order to the market, receives the decision on when to open a bid order from MarketAnalysis class */
        void makeBid();

        /** Passes the ask order to the market, receives the decision on when to open a ask order from MarketAnalysis class */
        void makeAsk();

        /** Categorizes the live orders into Bids and Asks, gets the highest bid and lowest ask for each pair then sends all this information to the MarketAnalysis class to process a prediction */
        void liveOrderBook();

        /** Goes to the next time frame, matches any orders send by the bot to the current time frame, calls the process function within wallet to process any matches */
        void nextTimeFrame();

    private:
    std::string currentTime;

    OrderBook orderBook{"20200317.csv"};
    //OrderBook orderBook{"20200601.csv"};
    Wallet wallet;

    MarketAnalysis predictor;
};
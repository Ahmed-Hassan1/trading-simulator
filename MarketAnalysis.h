#pragma once

#include <vector>
#include <map>
#include "OrderBookEntry.h"

/** The prediction of future prices and decision making is based on Simple Moving Average of the prices.
    
*/

class MarketAnalysis
{

    public:
    MarketAnalysis();

    /** Calculates the simple moving average by averaging the prices of each time frame and taking the decision with each time frame 
    Input1 (Bids or Asks) of the live orderbook
    Input2 (the currency string to ease working with the map data structure*/
    void simpleMovingAverage(std::vector<OrderBookEntry> currentOrders,std::string currency);

    /** Checks if the current live price is better than the average to take a Bid order 
    Input1 (string of the pair to check the its location in the map data structure*/
    std::string takeBid(std::string pair);
    /** Checks if the current live price is better than the average to take a Ask order
    Input1 (string of the pair to check the its location in the map data structure*/
    std::string takeAsk(std::string pair);

    std::vector<OrderBookEntry> marketLiveBids;
    std::vector<OrderBookEntry> marketLiveAsks;
    std::map<std::string, double> lowestAsk;
    std::map<std::string, double> highestBid;
    std::vector<std::string> currencyPairs;

    std::map<std::string, double> currenciesAsksAverages;
    std::map<std::string, int> totalAsksOrders;
    std::map<std::string, double> totalAsksSums;

    std::map<std::string, double> currenciesBidsAverages;
    std::map<std::string, int> totalBidsOrders;
    std::map<std::string, double> totalBidsSums;

    
};
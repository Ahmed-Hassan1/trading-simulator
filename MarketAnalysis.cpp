#include <iostream>
#include <time.h>
#include "MarketAnalysis.h"


MarketAnalysis::MarketAnalysis()
{

}

// This is analyzes the market and decides when and what to BUY
std::string MarketAnalysis::takeBid(std::string pair)
{
    if (lowestAsk[pair] <= currenciesAsksAverages[pair])      
    {
        return pair + "," + std::to_string(lowestAsk[pair]*1.01) + "," + std::to_string(1);
    }
    return "";
}

// This is analyzes the market and decides when and what to SELL
std::string MarketAnalysis::takeAsk(std::string pair)
{ 
    if (highestBid[pair] >= currenciesBidsAverages[pair])
    {
        return pair + "," + std::to_string(highestBid[pair]*0.99) + "," + std::to_string(1);
    }
    return "";
}

// Calculate a simple moving average, takes the live market bids or asks and builds the moving average over time. Takes the currency string to sort and look for them in the map.
void MarketAnalysis::simpleMovingAverage(std::vector<OrderBookEntry> currentOrders, std::string currency)
{
    if (currentOrders[0].orderType == OrderBookType::ask)
    {
        //total Ask orders in the market so far for each currency
        totalAsksOrders[currency] = totalAsksOrders[currency] + currentOrders.size();

        //total sums for all the Ask orders
        for (OrderBookEntry& order : currentOrders)
        {
            totalAsksSums[currency] = totalAsksSums[currency] + order.price;
        }

        //the average of the price of each currency's Ask from the start of the sim to the current time frame
        currenciesAsksAverages[currency] = (double)(totalAsksSums[currency] / totalAsksOrders[currency]);
    }
    
    if (currentOrders[0].orderType == OrderBookType::bid)
    {
        //total Bid orders in the market so far for each currency
        totalBidsOrders[currency] = totalBidsOrders[currency] + currentOrders.size();

        //total sums for all the Bid orders
        for (OrderBookEntry& order : currentOrders)
        {
            totalBidsSums[currency] = totalBidsSums[currency] + order.price;
        }

        //the average of the price of each currency's Bid from the start of the sim to the current time frame
        currenciesBidsAverages[currency] = (double)(totalBidsSums[currency] / totalBidsOrders[currency]);
    }
}
#include <chrono>

#include "Bot.h"



Bot::Bot()
{

}

void Bot::init()
{
    // Gets the earliest time in the orderbook
    currentTime = orderBook.getEarliestTime();

    // Fills the wallet with currency
    wallet.insertCurrency("BTC", 1000);
    wallet.insertCurrency("ETH", 1000);
    wallet.insertCurrency("USDT", 1000);
    wallet.insertCurrency("DOGE", 1000);
    std::cout << "Starting the bot simulation" << std::endl;
    // loops through all the time frames until it is done processing the entire csv file
    while(currentTime!="")
    {
        liveOrderBook();
        makeBid();
        makeAsk();
        nextTimeFrame();
    }

    // After finishing prints the content of the wallet at the end of the simulation
    std::cout << wallet.toString() << std::endl;
}



//Passes the BUY order to the market
void Bot::makeBid()
{
    for (std::string const& p : predictor.currencyPairs)
    {
        // Checks if there is any decision received from the MarketAnalysis class
        if (predictor.takeBid(p) != "")
        {
            //takes the decision in the form of an order input, then tokenize it.
            std::string input = predictor.takeBid(p);
            std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
            if (tokens.size() != 3)
            {
                std::cout << "Bot::makeBid Bad input! " << input << std::endl;
            }
            else
            {
                try
                {
                    // Creates a bid order from the tokneized order
                    OrderBookEntry obe = CSVReader::stringsToOBE(
                        tokens[1],
                        tokens[2],
                        currentTime,
                        tokens[0],
                        OrderBookType::bid
                        );
                    obe.username = "botuser";

                    // Checks if the wallet has enough currency then inserts it into the market
                    if (wallet.canFulfillOrder(obe))
                    {
                        //std::cout << "Wallet looks good. " << std::endl;
                        orderBook.insertOrder(obe);
                    }
                    else
                    {
                        //std::cout << "Wallet has insufficient funds . " << std::endl;
                    }
                }
                catch (const std::exception& e)
                {
                    //std::cout << " MerkelMain::enterBid Bad input " << std::endl;
                }
            }

        }
        
    }
}


//Passes the SELL order to the market
void Bot::makeAsk()
{
    for (std::string const& p : predictor.currencyPairs)
    {
        // Checks if there is any decision received from the MarketAnalysis class
        if (predictor.takeAsk(p) != "")
        {
            //takes the decision in the form of an order input, then tokenize it.
            std::string input = predictor.takeAsk(p);
            std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
            if (tokens.size() != 3)
            {
                std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
            }
            else {
                try {
                    // Creates an ask order from the tokneized order
                    OrderBookEntry obe = CSVReader::stringsToOBE(
                        tokens[1],
                        tokens[2],
                        currentTime,
                        tokens[0],
                        OrderBookType::ask
                        );
                    obe.username = "botuser";

                    // Checks if the wallet has enough currency then inserts it into the market
                    if (wallet.canFulfillOrder(obe))
                    {
                        //std::cout << "Wallet looks good. " << std::endl;
                        orderBook.insertOrder(obe);
                    }
                    else {
                        //std::cout << "Wallet has insufficient funds . " << std::endl;
                    }
                }
                catch (const std::exception& e)
                {
                    //std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
                }
            }
        }


    }
    
}


// Prepares information to be passed to the MarketAnalysis class. Details below
void Bot::liveOrderBook()
{
    // Caches all the known currencies to be passed to the MarketAnalysis class
    predictor.currencyPairs = orderBook.getKnownProducts();
    for (std::string const& p : predictor.currencyPairs)
    {
        //gets the live orders in the current time frame and categorizes them into Bids and Asks
        predictor.marketLiveBids = orderBook.getOrders(OrderBookType::bid,p,currentTime);
        predictor.marketLiveAsks = orderBook.getOrders(OrderBookType::ask,p,currentTime);

        //This if prevents checking an empty vector to prevent crashing the program
        if (predictor.marketLiveBids.size() != 0 || predictor.marketLiveAsks.size() != 0)
        {
            // Gets the highest Bids and lowest Asks and stores them in the MarketAnalysis to help in the decision making process
            predictor.highestBid[p] = orderBook.getHighPrice(predictor.marketLiveBids);
            predictor.lowestAsk[p] = orderBook.getLowPrice(predictor.marketLiveAsks);

            // Calls the function that process all the information provided
            predictor.simpleMovingAverage(predictor.marketLiveBids, p);
            predictor.simpleMovingAverage(predictor.marketLiveAsks, p);
        }
        


    }
}

// Moves to the next time frame and process any new orders passed to the market
void Bot::nextTimeFrame()
{
    //std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        //std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        //std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            //std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl; 
            if (sale.username == "botuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
            
        }       
    }
    currentTime = orderBook.getNextTimeBot(currentTime);
}
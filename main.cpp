#include "Wallet.h"
#include <iostream>
#include "MerkelMain.h"
#include "Bot.h"


#include <time.h>

int main()
{   

    //MerkelMain app{};
    //app.init();

    Bot botApp{};
    botApp.init();
    
    /*
    std::string s = "ETH/BTC";
    Wallet x;
    x.insertCurrency("BTC", 10);
    x.insertCurrency("ETH", 10000);

    std::string order= s + "," + std::to_string(0.2 * 1.1);


    std::cout << order + "," + std::to_string(1);
    */
}

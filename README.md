# trading-simulator

It is a basic trading simulator that uses an analysis class to make a decision for a buy or a sell of a currency. It uses a csv file that contains historical data for price and trades. 

It pareses historical Order Data in a csv file in this format: TimeStamp,	Currency Pair, bid or ask order, price,	Quantity

It creates a market based on the current bid or ask orders currently available at the time of timestamp, then it moves through the timestamp in order and the simulator then uses an analysis model that can be customized to trade against the current market prices.
Then at the end it shows the ending result of the strategy used.


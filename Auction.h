
#ifndef HOARDINGCPPVERSION_AUCTION_H
#define HOARDINGCPPVERSION_AUCTION_H

class Auction{
public:
  void set_highestbid(int x){
    highestbid = x;
  }
  int get_highestbid(){
    return highestbid;
  }
  void set_newbid(int x){
    newbid = x;
  }
  int get_newbid(){
    return newbid;
  }


void set_auction_has_max_bidder(bool x ){
 auction_has_max_bidder = x;
}
bool get_auction_has_max_bidder(){
  return auction_has_max_bidder;
}


private:
  int highestbid;
  int newbid;

  bool auction_has_max_bidder;
};
#endif

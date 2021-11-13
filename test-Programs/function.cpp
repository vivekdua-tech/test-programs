//
//  function.cpp
//  test-Programs
//
//  Created by vidua on 12/6/19.
//  Copyright © 2019 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <functional>
#include <vector>
//#include <boost/dynamic_bitset.hpp>
#include <cmath>
#include <memory>




using namespace std;

typedef function<int(int&, int&)> funcType;


int addition(int &x, int &y) {
    return x + y;
}

int substraction(int &x, int &y) {
    return x - y;
}

//
 // @brief Returns the number of trailing zeros for the given num
 //
uint16_t getTrailingZero(uint32_t num) {
    if (num & 0x1) {
        return 0;
     }

      num = num ^ (num & (num - 1));
      return log2(num);
  }

  //
 // @brief Get the optimal number of {data, mask} pair for the given
  //        range of values. So the TCAM usage is optimized.
  //
  void createOptimalRangeDataMask(uint32_t min, uint32_t max)
{
      /// If last bit is 1, then the last bit cannot be a wildcard
      if (min & 0x1) {
          cout << "Data: 0x" << std::hex << min << "Mask: 0x"<< UINT32_MAX << std::endl;
          min++;
      }

      while (min <= max) {
          uint16_t tZero = getTrailingZero(min);
          //
          // Wildcard the tZero bits if we don't cross the max.
          // Else, reduce tZero one by one until we can wildcard them
          //
          if (((1 << tZero) + min - 1) <= max) {
              uint32_t mask = UINT32_MAX << tZero;
              cout << "Data: 0x" << std::hex << min << "Mask: 0x"<< std::hex << mask << std::endl;
              min += (1 << tZero);
          } else {
              while (tZero) {
                  tZero--;
                  if (((1 << tZero) + min - 1) <= max) {
                      uint32_t mask = UINT32_MAX << tZero;
                      cout << "Data: 0x" << std::hex << min << "Mask: 0x"<< std::hex << mask << std::endl;
                      min += (1 << tZero);
                  }
              }
          }
      }
      return;
  }

#define power2(i) (0x1 << (i))

void rangeToTcamSets(uint32_t min,
                    uint32_t max,
                    uint16_t numMatchBits)
{
    uint64_t mask = (1 << numMatchBits) - 1;
    if (min == max) {
        cout << "Data: 0x" << std::hex << min << "Mask: 0x"<< std::hex << mask << std::endl;
        return;
    }
    //
    // Using Direct Range to Prefix algorithm to convert to data-mask pair
    // Note: Other algorithms can be explored later on which could lead to
    // lesser entries
    //
    uint8_t i;
    uint64_t tmp = 0;
    while (min < max) {
        for (i = 0; i < numMatchBits; ++i) {
            tmp = power2(i + 1);
            if ((min % tmp) || ((min + tmp - 1) > max)) {
                break;
            }
        }
        
        cout << "Data: 0x" << std::hex << min << "Mask: 0x"<< std::hex
             << (mask ^ (power2(i) - 1)) << std::endl;
        min += power2(i);
    }
}






int main() {
    
    const std::shared_ptr<int> s1 = std::make_shared<int>(10);
    const std::shared_ptr<int> s2 = std::make_shared<int>(20);
    
    std::shared_ptr<int> s3 = s1;
    s3 = s2;
    
    
    
    
    
    
    
    
#if 0
    vector<funcType> fnVec;
    boost::dynamic_bitset<> bs(384, 12);
    
    fnVec.push_back(addition);
    fnVec.push_back(substraction);
    
    int x = 3;
    int y = 2;
    
    for_each(fnVec.begin(), fnVec.end(), [&](funcType fn)
             { cout << "answer is:" << fn(x, y);});
    boost::dynamic_bitset<> temp(4, 12);

    
    bs = (bs << 64);
    //temp.resize(bs.size());
    //bs = bs | temp;
    //bs = ((bs << 4) | temp);
    
    //bs = bs | boost::dynamic_bitset<>(bs.size(), 100);
    
    vector<unsigned long> result;
    boost::to_block_range(bs, std::back_inserter(result));
    
    for (auto entry : result) {
        cout << " entry: " << hex << entry;
    }
    
    cout << "size is " << bs.count();
    auto first = bs.find_first();
    auto next = first;
    cout << "the first value is:" << first;
    for (int i = 1; i < bs.count(); i++) {
        next = bs.find_next(next);
        cout << " the value is: " << next;
    }
    cout << "the ulong value is " << bs.to_ulong();
#endif
}

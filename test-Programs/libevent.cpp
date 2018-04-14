//
//  libevent.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/13/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include "libevent.hpp"



event_base *sb = event_base_new();

event *t = event_new(eb, sockfd, EV_READ | EV_PERSIST,
                     acceptConnCb, nullptr);

event_add(t, nullptr);

event_base_dispatch(eb);



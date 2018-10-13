//
//  leaderBoard.cpp
//  test-Programs
//
//  Created by vidua on 9/29/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//
#include <iostream>
#include <vector>

using namespace std;

vector<string> split_string(string);

// Return the inserted-index for the insert element - Use BS
int insertAfterIndex(int score, vector<int> scores) {
    
    int low = 0;
    int high = scores.size() - 1;
    
    while (low <= high) {
        
        int mid = abs(low + (high - low)/2);
        if (scores[mid] == score) {
            return mid;
        }
        if (low == high) {
            if (scores[mid] > score) {
                return mid;
            } else {
                return mid - 1;
            }
        }
        if (score > scores[mid]) {
            high = mid - 1 < low ? low : mid - 1;
        } else {
            low = mid + 1 > high ? high : mid + 1;
        }
    }
    return low;
}



// Complete the climbingLeaderboard function below.
vector<int> climbingLeaderboard(vector<int> scores, vector<int> alice) {
    
    // Constraint checks
    if (!scores.size() ||
        scores.size() > 200000 ||
        !alice.size() ||
        alice.size() > 2000000) {
        return vector<int>();
    }
    // Figure out the rankings first
    int prevScore = -1;
    int rank = 0;
    vector<int> rankVec;
    for (auto i : scores) {
        if (i < 0 ||
            i > 1000000000) {
            return vector<int>();
        }
        if (prevScore == -1) {
            rankVec.push_back(++rank);
        } else {
            if (i > prevScore) {
                // failed constraint check
                return vector<int>();
            }
            if (prevScore == i) {
                rankVec.push_back(rank);
            } else {
                rankVec.push_back(++rank);
            }
        }
        prevScore = i;
    }
    
    // Rankings done - Do BS on the scores vector to figure out the ranks
    // If score == left , rank = rankVec[left-index];
    // If score == right, rank = rankVec[right-index];
    // If score > left and < right,...
    vector<int> aliceRanks;
    int prevAliceScore = -1;
    for (auto i : alice) {
        if (i < 0 ||
            i > 1000000000 ||
            i < prevAliceScore) {
            return vector<int>();
        }
        int index = insertAfterIndex(i, scores);
        if (index == -1) {
            rank = 1;
        } else {
            rank = (scores[index] == i)? rankVec[index] : rankVec[index] + 1;
        }
        aliceRanks.push_back(rank);
        prevAliceScore = i;
    }
    
    return aliceRanks;
}

int main()
{
    int scores_count = 200;

    
    string scores_temp_temp;
    
    scores_temp_temp = "997 988 981 966 957 937 933 930 929 928 927 926 922 920 916 915 903 896 887 874 872 866 863 863 860 859 858 857 857 847 847 842 830 819 815 809 803 797 796 794 794 789 785 783 778 772 765 765 764 757 755 751 744 740 737 733 730 730 724 716 710 709 691 690 684 677 676 653 652 650 625 620 619 602 587 587 585 583 571 568 568 556 552 546 541 540 538 531 530 529 527 506 504 501 498 493 493 492 489 482 475 468 457 452 445 442 441 438 435 435 433 430 429 427 422 422 414 408 404 400 396 394 387 384 380 379 374 371 369 369 369 368 366 365 363 354 351 341 337 336 328 325 318 316 314 307 306 302 287 282 281 277 276 271 246 238 236 230 229 229 228 227 220 212 199 194 179 173 171 168 150 144 136 125 125 124 122 118 98 98 95 92 88 85 70 68 61 60 59 44 43 35 32 30 28 23 20 13 12 12";
    
    vector<string> scores_temp = split_string(scores_temp_temp);
    
    vector<int> scores(scores_count);
    
    for (int i = 0; i < scores_count; i++) {
        int scores_item = stoi(scores_temp[i]);
        
        scores[i] = scores_item;
    }
    
    int alice_count = 50;
    
    string alice_temp_temp = "83 129 140 184 198 300 312 325 341 344 349 356 370 405 423 444 465 471 491 500 506 508 539 543 569 591 607 612 614 623 645 670 689 726 744 747 764 773 777 787 805 811 819 829 841 905 918 918 955 997";
    
    vector<string> alice_temp = split_string(alice_temp_temp);
    
    vector<int> alice(alice_count);
    
    for (int i = 0; i < alice_count; i++) {
        int alice_item = stoi(alice_temp[i]);
        
        alice[i] = alice_item;
    }
    
    vector<int> result = climbingLeaderboard(scores, alice);
    
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        
        if (i != result.size() - 1) {
            cout << "\n";
        }
    }
    
    cout << "\n";
    
    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });
    
    input_string.erase(new_end, input_string.end());
    
    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }
    
    vector<string> splits;
    char delimiter = ' ';
    
    size_t i = 0;
    size_t pos = input_string.find(delimiter);
    
    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));
        
        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }
    
    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));
    
    return splits;
}

#define CATCH_CONFIG_MAIN
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lib/catch/catch.hpp"
#include "../tree.hpp"


TEST_CASE("Insertion stress test", "[Stress Tests]")
{
    clock_t start, end;
    double sum, average;
    int i, j, interval;
    string j_str;
    Tree<int> * t;
    vector<double> insertion_time;


    for(i = 0; i < 10; i++) {
        interval = i * 100000;
        sum = 0;
        average = 0;

        t = new Tree<int>();

        for(j = 0; j < interval; j++) {
            j_str = to_string(j);
            start = clock();
            t->insert(j_str, j);
            end = clock();

            sum += (end - start);
        }

        average = sum / j;
        insertion_time.push_back(average);
        delete t;
    }

    printf("-----------------------------------------\n");
    for(i = 0; i < insertion_time.size(); i++) {
        printf("average insertion time: %8f level: %d\n", insertion_time[i], i);
    }
    printf("-----------------------------------------\n");
}

TEST_CASE("Lookup stress test", "[Stress Tests]")
{
    clock_t start, end;
    double sum, average;
    int i, j, interval;
    string j_str;
    Tree<int> * t;
    vector<double> insertion_time;


    for(i = 0; i < 10; i++) {
        interval = i * 100000;
        sum = 0;
        average = 0;

        t = new Tree<int>();

        for(j = 0; j < interval; j++) {
            j_str = to_string(j);
            t->insert(j_str, j);
            start = clock();
            t->search(j_str);
            end = clock();

            sum += (end - start);
        }

        average = sum / j;
        insertion_time.push_back(average);
        delete t;
    }

    printf("------------------------------------------------\n");
    for(i = 0; i < insertion_time.size(); i++) {
        printf("average lookup time: %8f level: %d n: %d\n",
            insertion_time[i], i, i * 100000);
    }
    printf("------------------------------------------------\n");
}

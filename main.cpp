// headers
#include "generator.hpp"
#include "ds/treaps.hpp"
#include "ds/skip_lists.hpp"
#include "ds/redblack.hpp"

#include <fstream>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std;
using namespace chrono;

// output files
ofstream ftreap("output_treap.csv");
ofstream fskiplist("output_skiplist.csv");
ofstream fredblack("output_redblack.csv");

int main()
{
    ftreap << "Test, Num_numbers, Operation, Time, Result\n";
    fskiplist << "Test, Num_numbers, Operation, Time, Result\n";
    fredblack << "Test, Num_numbers, Operation, Time, Result\n";

    // number of tests
    int num_tests;
    cout << "Number of tests: ";
    cin >> num_tests;

    for (int test = 0; test < num_tests; test++)
    {
        // number of operations
        unsigned int num_operations = Generator_Numar(1, 10000);
        cout << "Test " << test << "\nNumber of operations: " << num_operations << endl;

        vector<long long> numbers; // vector from which numbers are taken for the insert operation
        int i = 0;                 // index into the numbers vector

        // create data structures
        ptr_Treap treap = nullptr;
        SkipList<long long> skiplist;
        Tree redblack;

        if (test < num_tests / 5)
            Generator_Numere_Sortate_Crescator<long long>(LONG_MIN, LONG_MAX, 40000, numbers); // Sorted ascending
        else if (test < num_tests * 2 / 5)
            Generator_Numere_Sortate_Descrescator<long long>(LONG_MIN, LONG_MAX, 40000, numbers); // Sorted descending
        else if (test < num_tests * 3 / 5)
            Generator_Numere_Random_Uniform<long long>(LONG_MIN, LONG_MAX, 40000, numbers); // Uniform random
        else if (test < num_tests * 4 / 5)
            Generator_Numere_Random_Gaussian<long long>(LONG_MIN, LONG_MAX, 40000, numbers); // Gaussian random
        else
            Generator_Numere_Random_Inverted_Gaussian<long long>(LONG_MIN, LONG_MAX, 40000, numbers); // Inverted Gaussian random
        
        for (int op = 0; op < num_operations; op++)
        {
            int operation = Generator_Numar(1, 10);
            cout << operation << endl;

            // choose operation
            switch (operation)
            {
            case 1: // insert
            case 2:
            case 3:
            case 4:
            {
                long long number = numbers[i++];

                // treap
                auto start = high_resolution_clock::now();
                insert(treap, number);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap) << ", " << operation << ", " << duration.count() << endl;

                // skip list
                start = high_resolution_clock::now();
                skiplist.insert(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operation << ", " << duration.count() << endl;

                // red-black tree
                start = high_resolution_clock::now();
                redblack.insert(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operation << ", " << duration.count() << endl;
            }
            break;

            case 5: // delete
            {
                int number = Generator_Numar(LONG_MIN, LONG_MAX);

                // treap
                auto start = high_resolution_clock::now();
                treap = erase(treap, number);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap)  << ", " << operation << ", " << duration.count() << endl;

                // skip list
                start = high_resolution_clock::now();
                skiplist.delete_value(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operation << ", " << duration.count() << endl;

                // red-black tree
                start = high_resolution_clock::now();
                redblack.deleteRBNode(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operation << ", " << duration.count() << endl;
            }
            break;

            case 6: // search
            {
                int number = Generator_Numar(LONG_MIN, LONG_MAX);

                // treap
                auto start = high_resolution_clock::now();
                auto result1 = find(treap, number);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                if (result1 == 0)
                    ftreap << test + 1 << ", " << size(treap)  << ", " << operation << ", " << duration.count() << ", not found" << endl;
                else
                    ftreap << test + 1 << ", " << size(treap)  << ", " << operation << ", " << duration.count() << ", found" << endl;

                // skip list
                start = high_resolution_clock::now();
                auto result2 = skiplist.search(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                if (result2 == nullptr)
                    fskiplist << test + 1 << ", " << skiplist.size() << ", " << operation << ", " << duration.count() << ", not found" << endl;
                else
                    fskiplist << test + 1 << ", " << skiplist.size() << ", " << operation << ", " << duration.count() << ", found" << endl;

                // red-black tree
                start = high_resolution_clock::now();
                auto result3 = redblack.search(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                if (result3 == 0)
                    fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operation << ", " << duration.count() << ", not found" << endl;
                else
                    fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operation << ", " << duration.count() << ", found" << endl;
            }
            break;

            case 7: // range
            {
                int x = Generator_Numar(LONG_MIN, LONG_MAX);
                int y = Generator_Numar(LONG_MIN, LONG_MAX);

                // treap
                vector<long long> out;
                auto start = high_resolution_clock::now();
                range(treap, x, y, out);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap)  << ", " << operation << ", " << duration.count() << endl;

                // skip list
                start = high_resolution_clock::now();
                auto result = skiplist.Interval(x, y);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operation << ", " << duration.count() << endl;

                // red-black tree
                out.clear();
                start = high_resolution_clock::now();
                redblack.rangeQuery(x, y, out);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operation << ", " << duration.count() << endl;
            }
            break;

            case 8: // successor
            {
                int number = Generator_Numar(LONG_MIN, LONG_MAX);

                // treap
                auto start = high_resolution_clock::now();
                auto result1 = ceil(treap, number);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap)  << ", " << operation << "," << duration.count() << "," << result1 << endl;

                // skip list
                start = high_resolution_clock::now();
                auto result2 = skiplist.lowest_greater_than(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operation << ", " << duration.count() << "," << result2 << endl;

                // red-black tree
                start = high_resolution_clock::now();
                auto result3 = redblack.successor(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operation << ", " << duration.count() << "," << result3 << endl;
            }
            break;

            case 9: // predecessor
            {
                int number = Generator_Numar(LONG_MIN, LONG_MAX);

                // treap
                auto start = high_resolution_clock::now();
                auto result1 = floor(treap, number);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap)  << ", " << operation << ", " << duration.count() << "," << result1 << endl;

                // skip list
                start = high_resolution_clock::now();
                auto result2 = skiplist.largest_lower_by(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operation << ", " << duration.count() << "," << result2 << endl;

                // red-black tree
                start = high_resolution_clock::now();
                auto result3 = redblack.predecessor(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operation << ", " << duration.count() << "," << result3 << endl;
            }
            break;

            case 10: // union
            {
                int num_numbers = Generator_Numar(1, 50000);

                // treap
                ptr_Treap treap2;
                treap2 = generare_random_treap(num_numbers);
                auto start = high_resolution_clock::now();
                treap = reunion(treap, treap2);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap) << ", " << operation << ", " << duration.count() << endl;

                // skip list
                SkipList<long long> skiplist2;
                skiplist2 = skiplist2.generare_random_skiplist(num_numbers);
                start = high_resolution_clock::now();
                skiplist = skiplist.union_list(skiplist2);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operation << ", " << duration.count() << endl;

                // red-black tree
                Tree redblack2;
                redblack2.generateRandomRBTree(num_numbers);
                start = high_resolution_clock::now();
                redblack.unionWith(redblack2);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operation << ", " << duration.count() << endl;
            }
            break;
            }
        }
        ftreap << endl;
        fskiplist << endl;
        fredblack << endl;
    }

    ftreap.close();
    fskiplist.close();
    fredblack.close();

    return 0;
}

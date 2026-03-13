// headings
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

// fisiere de output
ofstream ftreap("output_treap.csv");
ofstream fskiplist("output_skiplist.csv");
ofstream fredblack("output_redblack.csv");

int main()
{
    ftreap << "Test, Nr_numere, Operatie, Timp, Rezultat\n";
    fskiplist << "Test, Nr_numere, Operatie, Timp, Rezultat\n";
    fredblack << "Test, Nr_numere, Operatie, Timp, Rezultat\n";

    // numar teste
    int nr_teste;
    cout << "Numar teste: ";
    cin >> nr_teste;

    for (int test = 0; test < nr_teste; test++)
    {
        // numar operatii
        unsigned int nr_operatii = Generator_Numar(1, 10000);
        cout << "Test " << test << "\nNumar operatii: " << nr_operatii << endl;

        vector<long long> numbers; // vectorul din care se vor lua numerele la operatia de inserare
        int i = 0;                 // index pentru vectorul de numere

        // se creeaza structurile de date
        ptr_Treap treap = nullptr;
        SkipList<long long> skiplist;
        Tree redblack;

        if (test < nr_teste / 5)
            Generator_Numere_Sortate_Crescator<long long>(LONG_MIN, LONG_MAX, 40000, numbers);
        else if (test < nr_teste * 2 / 5)
            Generator_Numere_Sortate_Descrescator<long long>(LONG_MIN, LONG_MAX, 40000, numbers);
        else if (test < nr_teste * 3 / 5)
            Generator_Numere_Random_Uniform<long long>(LONG_MIN, LONG_MAX, 40000, numbers);
        else if (test < nr_teste * 4 / 5)
            Generator_Numere_Random_Gaussian<long long>(LONG_MIN, LONG_MAX, 40000, numbers);
        else
            Generator_Numere_Random_Inverted_Gaussian<long long>(LONG_MIN, LONG_MAX, 40000, numbers);
        
        for (int op = 0; op < nr_operatii; op++)
        {
            int operatie = Generator_Numar(1, 10);
            cout << operatie << endl;

            // alegem operatia
            switch (operatie)
            {
            case 1: // inserare
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
                ftreap << test + 1 << ", " << size(treap) << ", " << operatie << ", " << duration.count() << endl;

                // skip list
                start = high_resolution_clock::now();
                skiplist.insert(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operatie << ", " << duration.count() << endl;

                // red-black tree
                start = high_resolution_clock::now();
                redblack.insert(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operatie << ", " << duration.count() << endl;
            }
            break;

            case 5: // stergere
            {
                long long number = Generator_Numar(LONG_MIN, LONG_MAX);

                // treap
                auto start = high_resolution_clock::now();
                treap = erase(treap, number);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap)  << ", " << operatie << ", " << duration.count() << endl;

                // skip list
                start = high_resolution_clock::now();
                skiplist.delete_value(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operatie << ", " << duration.count() << endl;

                // red-black tree
                start = high_resolution_clock::now();
                redblack.deleteRBNode(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operatie << ", " << duration.count() << endl;
            }
            break;

            case 6: // cautare
            {
                long long number = Generator_Numar(LONG_MIN, LONG_MAX);

                // treap
                auto start = high_resolution_clock::now();
                auto result1 = find(treap, number);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                if (result1 == 0)
                    ftreap << test + 1 << ", " << size(treap)  << ", " << operatie << ", " << duration.count() << ", not found" << endl;
                else
                    ftreap << test + 1 << ", " << size(treap)  << ", " << operatie << ", " << duration.count() << ", found" << endl;

                // skip list
                start = high_resolution_clock::now();
                auto result2 = skiplist.search(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                if (result2 == nullptr)
                    fskiplist << test + 1 << ", " << skiplist.size() << ", " << operatie << ", " << duration.count() << ", not found" << endl;
                else
                    fskiplist << test + 1 << ", " << skiplist.size() << ", " << operatie << ", " << duration.count() << ", found" << endl;

                // red-black tree
                start = high_resolution_clock::now();
                auto result3 = redblack.search(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                if (result3 == 0)
                    fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operatie << ", " << duration.count() << ", not found" << endl;
                else
                    fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operatie << ", " << duration.count() << ", found" << endl;
            }
            break;

            case 7: // interval
            {
                long long x = Generator_Numar(LONG_MIN, LONG_MAX);
                long long y = Generator_Numar(LONG_MIN, LONG_MAX);

                // treap
                vector<long long> out;
                auto start = high_resolution_clock::now();
                range(treap, x, y, out);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap)  << ", " << operatie << ", " << duration.count() << endl;

                // skip list
                start = high_resolution_clock::now();
                auto result = skiplist.Interval(x, y);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operatie << ", " << duration.count() << endl;

                // red-black tree
                out.clear();
                start = high_resolution_clock::now();
                redblack.rangeQuery(x, y, out);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operatie << ", " << duration.count() << endl;
            }
            break;

            case 8: // succesor
            {
                long long number = Generator_Numar(LONG_MIN, LONG_MAX);

                // treap
                auto start = high_resolution_clock::now();
                auto result1 = treap_ceil(treap, number);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap)  << ", " << operatie << "," << duration.count() << "," << result1 << endl;

                // skip list
                start = high_resolution_clock::now();
                auto result2 = skiplist.lowest_greater_than(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operatie << ", " << duration.count() << "," << result2 << endl;

                // red-black tree
                start = high_resolution_clock::now();
                auto result3 = redblack.successor(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operatie << ", " << duration.count() << "," << result3 << endl;
            }
            break;

            case 9: // predecesor
            {
                long long number = Generator_Numar(LONG_MIN, LONG_MAX);

                // treap
                auto start = high_resolution_clock::now();
                auto result1 = treap_floor(treap, number);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap)  << ", " << operatie << ", " << duration.count() << "," << result1 << endl;

                // skip list
                start = high_resolution_clock::now();
                auto result2 = skiplist.largest_lower_by(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operatie << ", " << duration.count() << "," << result2 << endl;

                // red-black tree
                start = high_resolution_clock::now();
                auto result3 = redblack.predecessor(number);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operatie << ", " << duration.count() << "," << result3 << endl;
            }
            break;

            case 10: // reuniune
            {
                int nr_numere_union = Generator_Numar(1, 50000);

                // treap
                ptr_Treap treap2;
                treap2 = generare_random_treap(nr_numere_union);
                auto start = high_resolution_clock::now();
                treap = reunion(treap, treap2);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                ftreap << test + 1 << ", " << size(treap) << ", " << operatie << ", " << duration.count() << endl;

                // skip list
                SkipList<long long> skiplist2;
                skiplist2 = skiplist2.generare_random_skiplist(nr_numere_union);
                start = high_resolution_clock::now();
                skiplist = skiplist.union_list(skiplist2);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fskiplist << test + 1 << ", " << skiplist.size() << ", " << operatie << ", " << duration.count() << endl;

                // red-black tree
                Tree redblack2;
                redblack2.generateRandomRBTree(nr_numere_union);
                start = high_resolution_clock::now();
                redblack.unionWith(redblack2);
                stop = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(stop - start);
                fredblack << test + 1 << ", " << redblack.countNodes() << ", " << operatie << ", " << duration.count() << endl;
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

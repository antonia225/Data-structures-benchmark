#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <type_traits>
using namespace std;

template <typename T>
void Generator_Numere_Sortate_Crescator(T minim, T maxim, int nr_numere, vector<T>& numbers)
{
    numbers.clear();
    if (nr_numere == 0)
        return;

    if (maxim < minim)
        swap(maxim, minim);

    if (minim == maxim)
    {
        for (unsigned long long i = 0; i < nr_numere; i++) 
            numbers.push_back(minim);
        return;
    }
    else
    {   
        mt19937 rng(random_device{}());
        uniform_real_distribution<double> random(1.5, 2.5);
        double scalar = random(rng);
        if constexpr (is_floating_point<T>::value)
        {
            uniform_real_distribution<T> dist(0, static_cast<T>((static_cast<double>(maxim) - static_cast<double>(minim)) / nr_numere * scalar));
            T current = minim;
            for (long long i = 0; i < nr_numere; i++) 
            {
                T next = current + dist(rng);
                if (next > maxim) next = maxim;
                numbers.push_back(next);
                current = next;
            }
        }
        else
        {
            double range = (static_cast<double>(maxim) - static_cast<double>(minim)) / nr_numere * scalar;
            T step = static_cast<T>(range) > 1 ? static_cast<T>(range) : 1;
            uniform_int_distribution<T> dist(0, step);
            T current = minim;
            for (long long i = 0; i < nr_numere; i++) 
            {
                T next = current + dist(rng);
                if (next > maxim) next = maxim;
                numbers.push_back(next);
                current = next;
            }
        }
    }
}

template <typename T>
void Generator_Numere_Sortate_Descrescator(T minim, T maxim, int nr_numere, vector<T>& numbers)
{
    numbers.clear();
    if (nr_numere == 0)
        return;

    if (maxim < minim)
        swap(maxim, minim);

    if (minim == maxim)
    {
        for (unsigned long long i = 0; i < nr_numere; i++) 
            numbers.push_back(minim);
        return;
    }
    else
    {   
        mt19937 rng(random_device{}());
        uniform_real_distribution<double> random(1.5, 2.5);
        double scalar = random(rng);
        if constexpr (is_floating_point<T>::value)
        {
            uniform_real_distribution<T> dist(0, static_cast<T>((static_cast<double>(maxim) - static_cast<double>(minim)) / nr_numere * scalar));
            T current = maxim;
            for (long long i = 0; i < nr_numere; i++) 
            {
                T next = current - dist(rng);
                if (next < minim) next = minim;
                numbers.push_back(next);
                current = next;
            }
        }
        else
        {
            double range = (static_cast<double>(maxim) - static_cast<double>(minim)) / nr_numere * scalar;
            T step = static_cast<T>(range) > 1 ? static_cast<T>(range) : 1;
            uniform_int_distribution<T> dist(0, step);
            T current = maxim;
            for (long long i = 0; i < nr_numere; i++) 
            {
                T next = current - dist(rng);
                if (next < minim) next = minim;
                numbers.push_back(next);
                current = next;
            }
        }
    }
}

template <typename T>
void Generator_Numere_Random_Uniform(T minim, T maxim, int nr_numere, vector<T>& numbers)
{
    numbers.clear();
    if (nr_numere == 0)
        return;

    if (maxim < minim)
        swap(maxim, minim);

    if (minim == maxim)
    {
        for (unsigned long long i = 0; i < nr_numere; i++) 
            numbers.push_back(minim);
        return;
    }
    else
    {
        mt19937 rng(random_device{}());
        if constexpr (is_floating_point<T>::value)
        {
            uniform_real_distribution<T> dist(minim, maxim);
            for (unsigned long long i = 0; i < nr_numere; i++)
                numbers.push_back(dist(rng));
        }
        else
        {
            uniform_int_distribution<T> dist(minim, maxim);
            for (unsigned long long i = 0; i < nr_numere; i++)
                numbers.push_back(dist(rng));
        }
    }   
}

template <typename T>
void Generator_Numere_Random_Gaussian(T minim, T maxim, int nr_numere, vector<T>& numbers)
{
    numbers.clear();
    if (nr_numere == 0)
        return;

    if (maxim < minim)
        swap(maxim, minim);

    if (minim == maxim)
    {
        for (unsigned long long i = 0; i < nr_numere; i++) 
            numbers.push_back(minim);
        return;
    }
    else
    {
        double diferenta = static_cast<double>(maxim) - static_cast<double>(minim);
        mt19937 rng(random_device{}());
        uniform_real_distribution<double> dev(0, diferenta / 6);
        uniform_real_distribution<double> mean(diferenta * 0.2, diferenta * 0.8);
        double mean1 = mean(rng) + static_cast<double>(minim);
        double dev1 = dev(rng);
        normal_distribution<double> gaus(mean1, dev1);

        if constexpr (is_floating_point<T>::value)
        {
            for (unsigned long long i = 0; i < nr_numere; i++)
            {
                T value = static_cast<T>(gaus(rng));
                if (value < minim)
                    value = minim;
                if (value > maxim)
                    value = maxim;
                numbers.push_back(value);
            }
        }
        else
        {
            for (unsigned long long i = 0; i < nr_numere; i++)
            {
                T value = static_cast<T>(round(gaus(rng)));
                if (value < minim)
                    value = minim;
                if (value > maxim)
                    value = maxim;
                numbers.push_back(value);
            }
        }
    }
}

template <typename T>
void Generator_Numere_Random_Inverted_Gaussian(T minim, T maxim, int nr_numere, vector<T>& numbers)
{
    numbers.clear();
    if (nr_numere == 0)
        return;

    if (maxim < minim)
        swap(maxim, minim);

    if (minim == maxim)
    {
        for (unsigned long long i = 0; i < nr_numere; i++)
            numbers.push_back(minim);
    }
    else
    {
        mt19937 rng(random_device{}());
        uniform_real_distribution<double> dev(0, (static_cast<double>(maxim) - static_cast<double>(minim)) / 6);
        double dev1 = dev(rng);
        normal_distribution<double> gaus(0, dev1);
        bernoulli_distribution weight(0.5);

        if constexpr (is_floating_point<T>::value)
        {
            for (unsigned long long i = 0; i < nr_numere; i++)
            {
                T value;
                if (weight(rng))
                {
                    value = static_cast<T>(abs(gaus(rng)) + minim);
                    numbers.push_back(value);
                }
                else
                {
                    value = static_cast<T>(maxim - abs(gaus(rng)));
                    numbers.push_back(value);
                }
            }
        }
        else
        {
            for (unsigned long long i = 0; i < nr_numere; i++)
            {
                T value;
                if (weight(rng))
                {
                    value = static_cast<T>(round(abs(gaus(rng))) + minim);
                    numbers.push_back(value);
                }
                else
                {
                    value = static_cast<T>(maxim - round(abs(gaus(rng))));
                    numbers.push_back(value);
                }
            }
        }
    }
}

short int Generator_Operatie()
{
    static mt19937 rd(random_device{}());                       
    static uniform_int_distribution<short int> dist(1, 7);    
    return dist(rd); 
}

template <typename T>
T Generator_Numar(T minim, T maxim)
{
    static mt19937 rd(random_device{}());                       
    uniform_int_distribution<T> dist(minim, maxim);    
    return dist(rd); 
}

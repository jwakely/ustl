// This file is part of the uSTL library, an STL implementation.
//
// Copyright (c) 2005 by Mike Sharov <msharov@users.sourceforge.net>
// This file is free software, distributed under the MIT License.

#include "stdtest.h"
#include "../umultimap.h"

using empmap_t = multimap<int,string>;
using citer_t = empmap_t::const_iterator;

static void PrintEntries (citer_t first, citer_t last)
{
    for (citer_t i = first; i < last; ++ i)
	cout << i->second << "\t- $" << i->first << endl;
}

inline static void PrintEntries (const empmap_t& m)
    { PrintEntries (m.begin(), m.end()); }

static void TestMultiMap (void)
{
    empmap_t employees;
    employees.insert (make_pair (27000, string("Dave"))); 
    employees.insert (make_pair (27000, string("Jim"))); 
    employees.insert (make_pair (99000, string("BigBoss"))); 
    employees.insert (make_pair (47000, string("Gail"))); 
    employees.emplace (make_pair (15000, string("Dumb")));
    employees.insert ({47000, "Barbara"});
    employees.insert (make_pair (47000, string("Mary"))); 

    cout << "As-inserted listing:\n";
    PrintEntries (employees);

    cout << "Alphabetical listing:\n";
    sort (employees);
    PrintEntries (employees);

    empmap_t::range_t middles = employees.equal_range (47000);
    cout << "Employees making $" << middles.first->first << ":";
    empmap_t::const_iterator i;
    for (i = middles.first; i < middles.second; ++ i)
	cout << " " << i->second;
    cout << endl;

    cout << employees.find(27000)->second << " makes $27000\n";

    cout << "There are " << employees.count (27000) << " low-paid employees\n";

    cout << "Firing all low-paid employees:\n";
    employees.erase (27000);
    PrintEntries (employees);

    cout << "Firing dumb employees:\n";
    employees.erase (employees.begin(), employees.begin() + 1);
    PrintEntries (employees);
}

StdTestMain (TestMultiMap)

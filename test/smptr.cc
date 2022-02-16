// This file is part of the uSTL library, an STL implementation.
//
// Copyright (c) 2016 by Mike Sharov <msharov@users.sourceforge.net>
// This file is free software, distributed under the MIT License.

#include "stdtest.h"

struct LoggedObj {
    LoggedObj (int v = 0)	:_v(v) { cout.format ("LoggedObj ctor %d\n", v); }
    ~LoggedObj (void)		{ cout.format ("LoggedObj dtor %d\n", _v); }
private:
    int _v;
};

static void TestSmartPtrs (void)
{
    auto plo = make_unique<LoggedObj> (42);
    auto ploa = make_unique<LoggedObj[]> (3);
    auto plosm = make_shared<LoggedObj> (72);
    shared_ptr<LoggedObj> plos;
    plos.swap (plosm);
    auto exprint = make_scope_exit ([]{ cout.format ("~scope_exit\n"); });
    auto uniqres = make_unique_resource (4, [](int v) { cout.format ("Closing resource %d\n", v); });
}

StdTestMain (TestSmartPtrs)

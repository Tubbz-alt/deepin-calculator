#ifndef UT_SCIENTIFICMODULE_H
#define UT_SCIENTIFICMODULE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QTest>

#include "src/dsettings.h"

class Ut_ScientificModule : public ::testing::Test
{
public:
    Ut_ScientificModule();
};

#endif // UT_SCIENTIFICMODULE_H

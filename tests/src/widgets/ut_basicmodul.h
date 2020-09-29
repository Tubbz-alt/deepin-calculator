#ifndef UT_BASICMODUL_H
#define UT_BASICMODUL_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QTest>

#include "src/memorypublic.h"
#include "src/dsettings.h"

class Ut_BasicModul : public ::testing::Test
{
public:
    Ut_BasicModul();

public:
    virtual void SetUp();

    virtual void TearDown();

protected:
};

#endif // UT_BASICMODUL_H

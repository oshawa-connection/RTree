#pragma once
#include <stdio.h>
#include "types.h"

static void iAssertEqual(int expected, int actual);

static void fAssertEqual(float expected, float actual, float tolerance);

static void AssertTrue(bool value);

void testSuite();
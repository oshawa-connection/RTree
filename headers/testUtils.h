#pragma once
#include <stdio.h>
#include "types.h"
/**
 * add messages
 * */
static void iAssertEqual(int expected, int actual, char * message);

static void fAssertEqual(float expected, float actual, float tolerance, char * message);

static void AssertTrue(bool value);

void testSuite();
#ifndef PARSE_H
#define PARSE_H

#include "tokenize.h"

struct Token *shuntingYard(const struct Token *tokens);

#endif

#pragma once
#include "InputTypes.h"
#include "InternalTypes.h"

void PrintBattlefieldToConsole(const Battlefield&);
Battlefield ConvertGameData(const Path&, const Battlefield&);
void RunTD(const Battlefield&, const Turrets&, const IncomingWaves&);
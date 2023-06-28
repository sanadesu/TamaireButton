#pragma once
#include <iostream>
#include <fstream>
#include "json.hpp"
namespace Json
{
	nlohmann::json Load(std::string fileName);
};


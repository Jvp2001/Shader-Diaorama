#pragma once
#include "CoreMinimal.h"
#include <functional>
template <typename T>
using TDioramaPropertyChangeSignature = std::function<void(T, T)>;


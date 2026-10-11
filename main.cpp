#include <iostream>

static constexpr int PlaneCount = 2;
static constexpr int TierCount = 3;

static constexpr int TankCapacity[PlaneCount] = {300, 1000};
static constexpr int TempTankCapacity[PlaneCount] = {0, 100};
static constexpr int WeightLimit[PlaneCount][TierCount] =
{
    {750, 1500, 2000},
    {1000, 2000, 3000}
};

static constexpr int Consumption[PlaneCount][TierCount] =
{
    {1, 4, 7},
    {2, 4, 6}
};

static int GetConsumption(const int plane, const int cargoWeight)
{
    for (int i = 0; i < TierCount; ++i)
    {
        if (cargoWeight <= WeightLimit[plane][i])
        {
            return Consumption[plane][i];
        }
    }
    return -1;
}

static int GetMinRefuel(const int plane, const int distAB, const int distBC, const int cargoWeight)
{
    const int Rate = GetConsumption(plane, cargoWeight);
    if (Rate < 0) return -1;

    const int FuelAB = distAB * Rate;
    const int FuelBC = distBC * Rate;

    if (FuelAB > TankCapacity[plane] + TempTankCapacity[plane]) return -1;

    const int TempUsed = FuelAB < TempTankCapacity[plane] ? FuelAB : TempTankCapacity[plane];
    const int TempLeft = TempTankCapacity[plane] - TempUsed;
    const int MainLeft = TankCapacity[plane] - (FuelAB - TempUsed);

    const int NeedFromMain = FuelBC > TempLeft ? FuelBC - TempLeft : 0;
    if (NeedFromMain > TankCapacity[plane]) return -1;

    const int Refuel = NeedFromMain - MainLeft;
    return Refuel > 0 ? Refuel : 0;
}

int main(int argc, char* argv[])
{
    int PlaneNum = 0;
    int DistAB = 0;
    int DistBC = 0;
    int CargoWeight = 0;

    std::cout << "Plane number: ";
    std::cin >> PlaneNum;
    std::cout << "A to B: ";
    std::cin >> DistAB;
    std::cout << "B to C: ";
    std::cin >> DistBC;
    std::cout << "Cargo weight: ";
    std::cin >> CargoWeight;

    if (PlaneNum != 1 && PlaneNum != 2)
    {
        std::cout << "Error\n";
        return 0;
    }

    const int Refuel = GetMinRefuel(PlaneNum - 1, DistAB, DistBC, CargoWeight);
    if (Refuel < 0)
        std::cout << "Not flying\n";
    else
        std::cout << "Min refuel: " << Refuel << " l\n";

    return 0;
}

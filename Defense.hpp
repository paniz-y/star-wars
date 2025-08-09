#ifndef DEFENSE_HPP
#define DEFENSE_HPP
#include <utility>
class Defense
{
public:
    Defense();
    void setRatio(int ratio);
    int getRatio() const;
    void defend();
    // bool operator==(const Defense otherDefense) const
    // {
    //     return (coordinatesForDefense == otherDefense.coordinatesForDefense) && (defenseRatio == otherDefense.defenseRatio);
    // }
    // friend struct std::hash<Defense>;
    // friend class EnemyCity;
private:
    std::pair<int, int> coordinatesForDefense;
    int defenseRatio;
};
// namespace std
// {
//     template <>
//     struct hash<Defense>
//     {
//         size_t operator()(const Defense &defense) const
//         {
//             auto tuple = std::tie(defense.coordinatesForDefense.first, defense.coordinatesForDefense.second);
//             return hash<decltype(tuple)>()(tuple);
//         }
//     };
// }
// struct HashForPair {
//     template <typename T1, typename T2>
//     std::size_t operator()(const std::pair<T1, T2>& p) const {
//         std::size_t h1 = std::hash<T1>{}(p.first);
//         std::size_t h2 = std::hash<T2>{}(p.second);
//         return h1 ^ (h2 << 1);
//     }
// };
#endif

#include <iostream>
#include <string>
#include <utility>

std::pair<int,int> kPosition = {0,0};

enum Bearing{
    NORTH,
    SOUTH,
    EAST,
    WEST,
};

class Robot{
public:
    /**
     * @brief Construct a new Robot object for default
     * 
     */
    Robot(): position({0,0}){};

    /**
     * @brief Construct a new Robot object
     * 
     * @param pos 
     */
    Robot(std::pair<int,int> pos){
        position.first = pos.first;
        position.second = pos.second;
    }

    /**
     * @brief Dado una accion tipo char la transforma a tipo enumerate
     * 
     * @param action 
     * @return Bearing 
     */
    Bearing GetAction(char action){
        switch (action)
        {
        case 'n':
            return Bearing::NORTH;
            break;
        case 's':
            return Bearing::SOUTH;
            break;
        case 'e':
            return Bearing::EAST;
            break;
        case 'w':
            return Bearing::WEST;
            break;
        default:
            return Bearing::NORTH; // Por defecto indico que se mueva al norte
        }
    }

    /**
     * @brief Traduce la accion enumerate en movimiento
     * 
     * @param action 
     */
    void MakeMove(Bearing action){
        switch (action)
        {
        case Bearing::NORTH:
            position.second--;
            break;
        case Bearing::SOUTH:
            position.second++;
            break;
        case Bearing::EAST:
            position.first++;
            break;
        case Bearing::WEST:
            position.first--;
            break;
        }
    }

    /**
     * @brief Get the position pair object
     * 
     * @return std::pair<int,int> 
     */
    std::pair<int,int> get_position_pair(){
        return this->position;
    }

    /**
     * @brief Get the position string object
     * 
     * @return std::string 
     */
    std::string get_position_string(){
        std::string cadena = "";
        cadena += "(" + std::to_string(position.first) + ", " + std::to_string(position.second) + ")";
        return cadena;
    }

private:
    std::pair<int,int> position;
};

/** @brief Robot Client main function */
int main() {
  const std::pair<int, int> kPosition{0, 0};
  const Bearing kBearing {Bearing::NORTH};
  Robot robot{kPosition};
  std::string sequence;
  getline(std::cin, sequence);
  for (const auto& movement : sequence) {
    robot.MakeMove(robot.GetAction(movement));
  }
  std::cout << robot.get_position_string() << std::endl;
  return 0;
}
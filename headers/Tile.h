/**
 * James Bouchat
 * 10-21-2023
 * Tile.h
 */

#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
private:
   sf::RectangleShape tile;
   sf::Color color;

   sf::RectangleShape* topNeighbor;
   sf::RectangleShape* rightNeighbor;
   sf::RectangleShape* bottomNeighbor;
   sf::RectangleShape* leftNeighbor;
public:
   // Constructors & Destructors
   Tile(sf::Color c)
      : tile(sf::Vector2f(5, 5)), color(c)
   {
      tile.setFillColor(color);

      topNeighbor = nullptr;
      rightNeighbor = nullptr;
      bottomNeighbor = nullptr;
      leftNeighbor = nullptr;
   }

   ~Tile()
   {
      delete topNeighbor;
      delete rightNeighbor;
      delete bottomNeighbor;
      delete leftNeighbor;
   }

   // Getters & Setters
   void setTopNeighbor(sf::RectangleShape& tn)
   {
      topNeighbor = &tn;
   }

   void setRightNeighbor(sf::RectangleShape& rn)
   {
      rightNeighbor = &rn;
   }

   void setBottomNeighbor(sf::RectangleShape& bn)
   {
      bottomNeighbor = &bn;
   }

   void setLeftNeighbor(sf::RectangleShape& ln)
   {
      leftNeighbor = &ln;
   }

   void setColor(sf::Color c)
   {
      color = c;
      tile.setFillColor(color);
   }

   void setPosition(int i, int j)
   {
      tile.setPosition(i, j);
   }

   sf::RectangleShape* getTopNeighbor() const
   {
      return topNeighbor;
   }
   sf::RectangleShape* getRightNeighbor() const
   {
      return rightNeighbor;
   }
   sf::RectangleShape* getBottomNeighbor() const
   {
      return bottomNeighbor;
   }
   sf::RectangleShape* getLeftNeighbor() const
   {
      return leftNeighbor;
   }

   sf::Color& getColor()
   {
      return color;
   }

   sf::RectangleShape& getTile()
   {
      return tile;
   }
   
   // Overloads
   friend std::ostream& operator << (std::ostream& outs, const Tile& tile)
   {
      outs << std::left;
      if(tile.getTopNeighbor() != nullptr)
         outs << "Top Neighbor: " << tile.getTopNeighbor()->getFillColor().toInteger();
      if(tile.getRightNeighbor() != nullptr)
         outs << "Right Neighbor: " << tile.getRightNeighbor()->getFillColor().toInteger();
      if(tile.getBottomNeighbor() != nullptr)
         outs << "Bottom Neighbor: " << tile.getBottomNeighbor()->getFillColor().toInteger();
      if(tile.getLeftNeighbor() != nullptr)     
         outs << "Left Neighbor: " << tile.getLeftNeighbor()->getFillColor().toInteger();
      return outs;
   }

};

#endif

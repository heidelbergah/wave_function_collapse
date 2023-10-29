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

   sf::Color* topNeighborColor;
   sf::Color* rightNeighborColor;
   sf::Color* bottomNeighborColor;
   sf::Color* leftNeighborColor;

   unsigned WIDTH;
   unsigned HEIGHT;
public:
   // Constructors & Destructors
   Tile(sf::Color c, unsigned WIDTH = 5, unsigned HEIGHT = 5)
      : tile(sf::Vector2f(WIDTH, HEIGHT)), color(c)
   {
      tile.setFillColor(color);

      topNeighborColor = nullptr;
      rightNeighborColor = nullptr;
      bottomNeighborColor = nullptr;
      leftNeighborColor = nullptr;

      this->WIDTH = WIDTH;
      this->HEIGHT = HEIGHT;
   }

   // Getters & Setters
   void setTopNeighborColor(sf::Color& tnc)
   {
      topNeighborColor = &tnc;
   }

   void setRightNeighborColor(sf::Color& rnc)
   {
      rightNeighborColor = &rnc;
   }

   void setBottomNeighborColor(sf::Color& bnc)
   {
      bottomNeighborColor = &bnc;
   }

   void setLeftNeighborColor(sf::Color& lnc)
   {
      leftNeighborColor = &lnc;
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

   sf::Color* getTopNeighborColor() const
   {
      return topNeighborColor;
   }
   sf::Color* getRightNeighborColor() const
   {
      return rightNeighborColor;
   }
   sf::Color* getBottomNeighborColor() const
   {
      return bottomNeighborColor;
   }
   sf::Color* getLeftNeighborColor() const
   {
      return leftNeighborColor;
   }

   sf::Color& getColor()
   {
      return color;
   }

   sf::RectangleShape& getTile()
   {
      return tile;
   }

   unsigned getWidth() const
   {
      return WIDTH;
   }

   unsigned getHeight() const
   {
      return HEIGHT;
   }
   
   // Overloads
   friend std::ostream& operator << (std::ostream& outs, const Tile& tile)
   {
      outs << std::left;
      if(tile.getTopNeighborColor() != nullptr)
         outs << "Top Neighbor: " << tile.getTopNeighborColor()->toInteger() << std::endl;
      if(tile.getRightNeighborColor() != nullptr)
         outs << "Right Neighbor: " << tile.getRightNeighborColor()->toInteger() << std::endl;
      if(tile.getBottomNeighborColor() != nullptr)
         outs << "Bottom Neighbor: " << tile.getBottomNeighborColor()->toInteger() << std::endl;
      if(tile.getLeftNeighborColor() != nullptr)     
         outs << "Left Neighbor: " << tile.getLeftNeighborColor()->toInteger() << std::endl;
      return outs;
   }

};

#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include "headers/Tile.h"

void setNeighbors(std::vector<std::vector<Tile>>& tiles, unsigned h = 200, unsigned w = 200)
{
   for(int i = 0; i < h; i+=5)
   {
      for(int j = 0; j < w; j+=5)
      {
         int iIndex = i/5, jIndex = j/5;
         if(iIndex < 0) // Top neighbor exists
         {
            tiles[iIndex][jIndex].setTopNeighbor(tiles[iIndex-1][jIndex].getTile());
         }
         if(iIndex == (h/200)-1) // Bottom neighbor exists
         {
            tiles[iIndex][jIndex].setBottomNeighbor(tiles[iIndex+1][jIndex].getTile());
         }
         if(jIndex < 0) // Left neighbor exists
         {
            tiles[iIndex][jIndex].setLeftNeighbor(tiles[iIndex][jIndex-1].getTile());
         }
         if(jIndex == (w/200)-1) // Right neighbor exists
         {
            tiles[iIndex][jIndex].setRightNeighbor(tiles[iIndex][jIndex+1].getTile());
         }
      }
   }
}

std::vector<std::vector<Tile>> randomTiles(std::vector<sf::Color>& colors, unsigned HEIGHT = 200, unsigned WIDTH = 200)
{
   std::vector<std::vector<Tile>> tiles;
   for(int i = 0; i < HEIGHT; i+=5)
   {
      std::vector<Tile> row;
      for(int j = 0; j < WIDTH; j+=5)
      {
         int randomColorIndex = rand() % colors.size();
         Tile tile(colors[randomColorIndex]);
         tile.setPosition(j, i);
         row.push_back(tile);
      }
      tiles.push_back(row);
   }

   setNeighbors(tiles);
   return tiles;
}

std::vector<std::vector<Tile>> customTiles(std::vector<sf::Color>& colors)
{
   /** INPUT CUSOM COLORS HERE **/
   std::vector<std::vector<unsigned>> tileColors = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {2, 2, 2, 2},
    {3, 3, 3, 3},
    {0, 1, 2, 3}
   };
   /*****************************/

   std::vector<std::vector<Tile>> tiles;
   for(int i = 0; i < tileColors.size(); ++i)
   {
      std::vector<Tile> row;
      for(int j = 0; j < tileColors[i].size(); ++j)
      {
         Tile tile(colors[tileColors[i][j]]);
         tile.setPosition(j*5, i*5);
         row.push_back(tile);
      }
      tiles.push_back(row);
   }

   setNeighbors(tiles, tiles.size()*5, tiles[0].size()*5);
   return tiles;
}

int main()
{
   const unsigned WIDTH = 200, HEIGHT = 200;
   sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Wave Function Collapse");

   srand(time(NULL));

   std::vector<sf::Color> colors;
   colors.push_back(sf::Color::White);
   colors.push_back(sf::Color::Black);
   colors.push_back(sf::Color::Green);
   colors.push_back(sf::Color::Blue);

   std::vector<std::vector<Tile>> tiles = customTiles(colors);

   while(window.isOpen())
   {
      sf::Event event;
      while(window.pollEvent(event))
      {
         if(event.type == sf::Event::Closed)
         {
            window.close();
         }
      }

      window.clear();
      for(int i = 0; i < tiles.size(); ++i)
         for(int j = 0; j < tiles[i].size(); ++j)
            window.draw(tiles[i][j].getTile());
      window.display();

   }

   return 0;
}
